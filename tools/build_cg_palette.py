#!/usr/bin/env python3
"""Build a 256-color BG palette blob for event CGs (slots 32-255)."""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

from PIL import Image

from cg_remap import PALETTE_OFFSET, build_cg_index_remap, rgb888_to_bgr555


def build_cg_palette_png(path: Path) -> bytes:
    image = Image.open(path)
    if image.mode != "P":
        raise ValueError(f"{path.name}: expected indexed PNG (mode P)")

    palette = image.getpalette()
    if palette is None:
        raise ValueError(f"{path.name}: missing palette")

    pixels = list(image.get_flattened_data())
    remap = build_cg_index_remap(pixels)

    out = bytearray(512)
    for author_index, slot in remap.items():
        base = author_index * 3
        if base + 2 >= len(palette):
            color = (0, 0, 0)
        else:
            color = tuple(palette[base : base + 3])
        struct.pack_into("<H", out, slot * 2, rgb888_to_bgr555(*color))

    max_used_slot = max(remap.values()) if remap else PALETTE_OFFSET - 1
    for slot in range(max_used_slot + 1, 256):
        if struct.unpack_from("<H", out, slot * 2)[0] != 0:
            raise ValueError(f"{path.name}: unused palette slot {slot} is non-zero")

    return bytes(out)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input_png", type=Path)
    parser.add_argument("output_gbapal", type=Path)
    args = parser.parse_args()

    try:
        data = build_cg_palette_png(args.input_png)
    except (OSError, ValueError) as exc:
        print(exc, file=sys.stderr)
        return 1

    args.output_gbapal.write_bytes(data)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
