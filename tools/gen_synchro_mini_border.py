#!/usr/bin/env python3
"""Generate a white/silver mini card border for synchro monsters.
Uses the Effect monster mini border as template. Compose copies bytes as
8bpp palette indices: keep 0 (transparent) and 159 (black outline), remap
chrome accents to 1 (near-white)."""
import struct

ROM_PATH = "baserom.gba"
OUT_BORDER = "src_custom/assets/cards/frames/synchro_mini.4bpp"
PTR_OFFSET = 0xE17F48

with open(ROM_PATH, "rb") as f:
    f.seek(PTR_OFFSET)
    ptrs = [struct.unpack_from("<I", f.read(4))[0] for _ in range(9)]

start = ptrs[1] - 0x08000000  # COLOR_EFFECT
size = ptrs[2] - ptrs[1]

with open(ROM_PATH, "rb") as f:
    f.seek(start)
    border = bytearray(f.read(size))

# Match vanilla: 0 = holes, 159 = black outer/inner rings, accents → white.
# ponytail: index 0 is transparent at runtime — chrome uses 1, not 0.
for i, b in enumerate(border):
    if b not in (0, 159):
        border[i] = 1

with open(OUT_BORDER, "wb") as f:
    f.write(border)

print(f"Wrote {OUT_BORDER} ({len(border)} bytes)")
print(f"  zeros={border.count(0)} white={border.count(1)} black={border.count(159)}")
assert border.count(159) == 692 and border.count(0) == 128
