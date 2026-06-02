#!/usr/bin/env python3
"""
Ensure dialogue portrait PNGs reserve palette index 0 for transparency.

Portrait tile byte 0 is hardware-transparent. Source PNG index 0 must be black;
indices 1..63 map to OBJ palette slots 0xC1..0xFF at build time. Editors often place black on
the last index (e.g. 63) instead, which renders as an opaque black border.
"""

from __future__ import annotations

import argparse
import pathlib
import sys

from PIL import Image


def find_black_index(palette: list[int], color_count: int) -> int | None:
    for index in range(color_count):
        base = index * 3
        if palette[base : base + 3] == [0, 0, 0]:
            return index
    return None


def swap_palette_entries(palette: list[int], a: int, b: int) -> None:
    base_a = a * 3
    base_b = b * 3
    palette[base_a : base_a + 3], palette[base_b : base_b + 3] = (
        palette[base_b : base_b + 3],
        palette[base_a : base_a + 3],
    )


def normalize_portrait(image: Image.Image) -> bool:
    if image.mode != "P":
        raise ValueError(f"expected indexed PNG (mode P), got {image.mode!r}")

    palette = image.getpalette()
    if palette is None:
        raise ValueError("indexed image has no palette")

    color_count = len(palette) // 3
    black_index = find_black_index(palette, color_count)
    changed = False

    if black_index is None:
        if palette[0:3] != [0, 0, 0]:
            palette[0:3] = [0, 0, 0]
            image.putpalette(palette)
            changed = True
        return changed

    if black_index == 0:
        if palette[0:3] != [0, 0, 0]:
            palette[0:3] = [0, 0, 0]
            image.putpalette(palette)
            changed = True
        return changed

    swap_palette_entries(palette, 0, black_index)
    image.putpalette(palette)

    width, height = image.size
    pixel_access = image.load()
    for y in range(height):
        for x in range(width):
            pixel = pixel_access[x, y]
            if pixel == 0:
                pixel_access[x, y] = black_index
            elif pixel == black_index:
                pixel_access[x, y] = 0
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=pathlib.Path)
    parser.add_argument("output", type=pathlib.Path, nargs="?")
    args = parser.parse_args()

    output = args.output or args.input
    image = Image.open(args.input)
    changed = normalize_portrait(image)
    if changed or output != args.input:
        output.parent.mkdir(parents=True, exist_ok=True)
        image.save(output)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
