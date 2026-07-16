#!/usr/bin/env python3
"""Generate a white/silver mini card border for synchro monsters.
Uses the Effect monster mini border as template. Compose copies bytes as
8bpp palette indices: keep 0 (transparent) and 159 (black); remap the three
effect chrome accents onto a white/silver ramp already in mini.pal."""
import struct

ROM_PATH = "baserom.gba"
OUT_BORDER = "src_custom/assets/cards/frames/synchro_mini.4bpp"
PTR_OFFSET = 0xE17F48

# Effect accent indices → white/silver ramp (mini.pal, no new colors).
# Counts match vanilla: light×120, mid×56, dark×28.
ACCENT_REMAP = {
    29: 1,   # light  — (255,255,246) near-white
    70: 16,  # mid    — (222,222,255) cool silver
    117: 52, # dark   — (189,189,189) gray
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

from collections import Counter
hist = Counter(border)
print(f"Wrote {OUT_BORDER} ({len(border)} bytes)")
print(f"  {dict(sorted(hist.items()))}")
assert hist[0] == 128 and hist[159] == 692
assert hist[1] == 120 and hist[16] == 56 and hist[52] == 28
