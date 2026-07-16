#!/usr/bin/env python3
"""Generate a white/silver mini card border for synchro monsters.
Uses the Effect monster mini card border as template, recolored to white."""
import struct

ROM_PATH = "baserom.gba"
OUT_BORDER = "src_custom/assets/cards/frames/synchro_mini.4bpp"
PTR_OFFSET = 0xE17F48

with open(ROM_PATH, "rb") as f:
    f.seek(PTR_OFFSET)
    ptrs = [struct.unpack_from("<I", f.read(4))[0] for _ in range(9)]

# Use COLOR_EFFECT (index 1) as template
start = ptrs[1] - 0x08000000
size = ptrs[2] - ptrs[1]

with open(ROM_PATH, "rb") as f:
    f.seek(start)
    border = bytearray(f.read(size))

# Remap to near-white (1). Index 0 is forced transparent at runtime, so a
# visible synchro frame must not use 0 for the ring (ponytail: ceiling =
# no true white ring until a non-transparent white is added to mini.pal).
remap = {i: 1 for i in range(16)}
remap[0] = 0  # keep existing transparent holes

for i, b in enumerate(border):
    hi = remap.get(b >> 4, b >> 4)
    lo = remap.get(b & 0x0F, b & 0x0F)
    border[i] = (hi << 4) | lo

with open(OUT_BORDER, "wb") as f:
    f.write(border)

print(f"Wrote {OUT_BORDER} ({len(border)} bytes) from effect card template")
