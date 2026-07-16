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

# Remap all colored pixels to white (0) or near-white (1).
# Index 0 = 0x7FFF pure white, index 1 = 0x7BFF near-white.
remap = {
    0: 0,   # white (keep)
    1: 1,   # near-white (keep)
    2: 1,   # → near-white
    3: 0,   # → white
    4: 1,   # → near-white
    5: 0,   # → white
    6: 0,   # → white
    7: 1,   # → near-white
    8: 0,   # → white
    9: 0,   # → white
    10: 1,  # → near-white
    11: 0,  # → white
    12: 1,  # → near-white
    13: 0,  # → white
    14: 1,  # → near-white
    15: 0,  # → white
}

for i, b in enumerate(border):
    hi = remap.get(b >> 4, b >> 4)
    lo = remap.get(b & 0x0F, b & 0x0F)
    border[i] = (hi << 4) | lo

with open(OUT_BORDER, "wb") as f:
    f.write(border)

print(f"Wrote {OUT_BORDER} ({len(border)} bytes) from effect card template")
