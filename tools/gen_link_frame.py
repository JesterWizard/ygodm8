#!/usr/bin/env python3
"""Link frame = darkened Obelisk blue (big palette + mini border).

Big card: copy Obelisk's 20-color frame palette, darken chrome slots 1–9,
keep system text/star colors 10–19.

Mini: copy Obelisk mini border tiles; remap the three chrome accents to
darker blues already in the shared mini palette (g89A781C).
"""
import struct
from collections import Counter
from pathlib import Path

ROM = Path("baserom.gba")
OUT_PAL = Path("src_custom/assets/cards/frames/link.gbapal")
OUT_MINI = Path("src_custom/assets/cards/frames/link_mini.4bpp")

COLOR_OBELISK = 6
# Obelisk mini accents → medium navy (lighter than prior passes).
MINI_ACCENT_REMAP = {
    87: 137,  # face  — (88,96,216)
    129: 120,  # mid   — (80,128,224)
    142: 105,  # light — (40,176,248)
}


def gba(r, g, b):
    return (b // 8) << 10 | (g // 8) << 5 | (r // 8)


def darken_obelisk_slot(c, factor=0.72):
    """Pull Obelisk chrome toward navy without killing blue dominance."""
    r, g, b = c & 0x1F, (c >> 5) & 0x1F, (c >> 10) & 0x1F
    # Keep a bit more blue than r/g so it stays "link blue" not gray.
    r = max(0, int(r * factor * 0.85))
    g = max(0, int(g * factor * 0.9))
    b = max(4, int(b * (factor + 0.12)))
    if b < r + 2:
        b = min(31, r + 4)
    return r | (g << 5) | (b << 10)


def main():
    rom = ROM.read_bytes()
    pal_ptrs = [struct.unpack_from("<I", rom, 0xE137C4 + i * 4)[0] for i in range(9)]
    ob_off = pal_ptrs[COLOR_OBELISK] - 0x08000000
    ob = [struct.unpack_from("<H", rom, ob_off + i * 2)[0] for i in range(20)]

    link = list(ob)
    for i in range(1, 10):
        link[i] = darken_obelisk_slot(ob[i])
    # Slot 0 stays near-black; 10–19 keep vanilla text/star system colors.

    OUT_PAL.write_bytes(b"".join(struct.pack("<H", c) for c in link))
    print(f"Wrote {OUT_PAL}")
    for i, c in enumerate(link):
        r, g, b = c & 0x1F, (c >> 5) & 0x1F, (c >> 10) & 0x1F
        tag = " chrome" if 1 <= i <= 9 else (" sys" if i >= 10 else "")
        print(f"  [{i:2d}] {c:04X} RGB({r*8:3d},{g*8:3d},{b*8:3d}){tag}")

    border_ptrs = [struct.unpack_from("<I", rom, 0xE17F48 + i * 4)[0] for i in range(9)]
    start = border_ptrs[COLOR_OBELISK] - 0x08000000
    size = border_ptrs[COLOR_OBELISK + 1] - border_ptrs[COLOR_OBELISK]
    border = bytearray(rom[start : start + size])
    for i, b in enumerate(border):
        if b in MINI_ACCENT_REMAP:
            border[i] = MINI_ACCENT_REMAP[b]
    OUT_MINI.write_bytes(border)
    hist = Counter(border)
    print(f"Wrote {OUT_MINI} ({len(border)} bytes) hist={dict(sorted(hist.items()))}")
    assert hist[0] == 128 and hist[159] == 692


if __name__ == "__main__":
    main()
