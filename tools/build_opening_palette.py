#!/usr/bin/env python3
"""Build a 256-color BG palette blob for 8bpp opening screens."""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

from PIL import Image

from cg_remap import rgb888_to_bgr555

MAX_OPENING_COLORS = 256


def build_opening_palette_png(path: Path) -> bytes:
    image = Image.open(path)
    if image.mode != "P":
        raise ValueError(f"{path.name}: expected indexed PNG (mode P)")

    palette = image.getpalette()
    if palette is None:
        raise ValueError(f"{path.name}: missing palette")

    out = bytearray(512)
    for slot in range(MAX_OPENING_COLORS):
        base = slot * 3
        if base + 2 < len(palette):
            color = tuple(palette[base : base + 3])
        else:
            color = (0, 0, 0)
        struct.pack_into("<H", out, slot * 2, rgb888_to_bgr555(*color))

    return bytes(out)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input_png", type=Path)
    parser.add_argument("output_gbapal", type=Path)
    args = parser.parse_args()

    try:
        data = build_opening_palette_png(args.input_png)
    except (OSError, ValueError) as exc:
        print(exc, file=sys.stderr)
        return 1

    args.output_gbapal.write_bytes(data)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
