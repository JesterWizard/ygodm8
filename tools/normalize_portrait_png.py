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


def normalize_portrait_file(
    input_path: pathlib.Path, output_path: pathlib.Path | None = None
) -> bool:
    output = output_path or input_path
    image = Image.open(input_path)
    changed = normalize_portrait(image)
    if changed or output != input_path:
        output.parent.mkdir(parents=True, exist_ok=True)
        image.save(output)
    return changed


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=pathlib.Path, help="PNG file or directory of PNGs")
    parser.add_argument(
        "output",
        type=pathlib.Path,
        nargs="?",
        help="output file or directory (default: in-place)",
    )
    args = parser.parse_args()

    input_path = args.input
    if input_path.is_dir():
        if args.output is not None and not args.output.is_dir():
            print(f"{args.output}: output must be a directory", file=sys.stderr)
            return 1
        pngs = sorted(path for path in input_path.glob("*.png") if path.is_file())
        if not pngs:
            print(f"no PNG files found in {input_path}", file=sys.stderr)
            return 1
        for png in pngs:
            out = (args.output / png.name) if args.output is not None else png
            normalize_portrait_file(png, out)
        return 0

    if not input_path.is_file():
        print(f"{input_path}: not a file or directory", file=sys.stderr)
        return 1
    if args.output is not None and args.output.is_dir():
        print(f"{args.output}: output must be a file when input is a file", file=sys.stderr)
        return 1

    normalize_portrait_file(input_path, args.output)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
