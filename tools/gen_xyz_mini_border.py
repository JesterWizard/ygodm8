#!/usr/bin/env python3
"""Generate a black mini card border for XYZ monsters.
Uses the Effect monster mini border as template. Compose copies bytes as
8bpp palette indices: keep 0 (transparent) and 159 (black outline); remap
the three effect chrome accents so black is the base fill and lighter grays
form the bevel/pattern (inverse of the synchro light→dark ramp)."""
import struct
from collections import Counter

ROM_PATH = "baserom.gba"
OUT_BORDER = "src_custom/assets/cards/frames/xyz_mini.4bpp"
PTR_OFFSET = 0xE17F48

# Effect accents → black base + lighter bevel (mini.pal, no new colors).
# Template roles: 29=face×120, 70=mid×56, 117=dark accent×28.
# Invert so the face is near-black and accents read as the pattern.
ACCENT_REMAP = {
    29: 159,  # face  — near-black base
    70: 154,  # mid   — (32,65,65) dark gray bevel
    117: 115, # light — (123,131,123) charcoal pattern highlight
}

with open(ROM_PATH, "rb") as f:
    f.seek(PTR_OFFSET)
    ptrs = [struct.unpack_from("<I", f.read(4))[0] for _ in range(9)]

start = ptrs[1] - 0x08000000  # COLOR_EFFECT
size = ptrs[2] - ptrs[1]

with open(ROM_PATH, "rb") as f:
    f.seek(start)
    border = bytearray(f.read(size))

for i, b in enumerate(border):
    if b in ACCENT_REMAP:
        border[i] = ACCENT_REMAP[b]

with open(OUT_BORDER, "wb") as f:
    f.write(border)

hist = Counter(border)
print(f"Wrote {OUT_BORDER} ({len(border)} bytes)")
print(f"  {dict(sorted(hist.items()))}")
assert hist[0] == 128
assert hist[159] == 692 + 120  # outline + black face
assert hist[154] == 56 and hist[115] == 28
