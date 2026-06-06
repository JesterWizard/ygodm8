#!/usr/bin/env python3
"""Generate a simple 240x160 indexed test CG PNG."""

from __future__ import annotations

import argparse
from pathlib import Path

from PIL import Image


def build_test_image() -> Image.Image:
    palette = [(0, 0, 0)]
    for i in range(1, 17):
        palette.append((i * 12, 32, 160 - i * 8))

    image = Image.new("P", (240, 160))
    image.putpalette([channel for rgb in palette for channel in rgb] + [0] * (768 - len(palette) * 3))

    pixels = []
    for y in range(160):
        for x in range(240):
            band = min(15, (x * 16) // 240 + 1)
            pixels.append(band)
    image.putdata(pixels)
    return image


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "output",
        nargs="?",
        type=Path,
        default=Path("src_custom/assets/cgs/test_placeholder.png"),
    )
    args = parser.parse_args()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    build_test_image().save(args.output)
    print(f"generate_test_cg_png: wrote {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
