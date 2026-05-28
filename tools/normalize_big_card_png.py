#!/usr/bin/env python3
"""
Normalize custom 80x80 big card PNGs for the GBA card-detail pipeline.

Vanilla CopyCardArtDataToBuffers forces palette index 0 to color 0x0000 (black).
Photoshop "Save for Web" often places opaque edge colors on index 0 while still
enabling transparency, which makes those pixels render black in-game.

This script:
  1. Remaps opaque index-0 pixels to the closest existing palette entry.
  2. Sets palette entry 0 to black (reserved for transparency / empty tiles).
  3. Optionally softens high-contrast halos by replacing body-colored pixels that
     touch glow palette indices with the nearest glow index.
"""

from __future__ import annotations

import argparse
import math
import pathlib
import sys

from PIL import Image

# Creature body blues on Chain Energy; extend as needed for other cards.
DEFAULT_BODY_INDICES = frozenset({5, 6, 7, 8, 9, 10})
DEFAULT_GLOW_INDICES = frozenset({60, 61, 62, 63})


def color_distance_sq(a: tuple[int, int, int], b: tuple[int, int, int]) -> int:
    return sum((x - y) ** 2 for x, y in zip(a, b))


def palette_rgb(palette: list[int], index: int) -> tuple[int, int, int]:
    base = index * 3
    return palette[base], palette[base + 1], palette[base + 2]


def closest_palette_index(
    palette: list[int], target: tuple[int, int, int], exclude: frozenset[int]
) -> int:
    best_index = 1
    best_distance = math.inf
    for index in range(64):
        if index in exclude:
            continue
        distance = color_distance_sq(target, palette_rgb(palette, index))
        if distance < best_distance:
            best_distance = distance
            best_index = index
    return best_index


def remap_opaque_index_zero(image: Image.Image) -> int:
    palette = image.getpalette()
    if palette is None:
        return 0

    pixels = list(image.get_flattened_data())
    if 0 not in pixels:
        return 0

    replacement = closest_palette_index(palette, palette_rgb(palette, 0), frozenset({0}))
    remapped = 0
    new_pixels = []
    for pixel in pixels:
        if pixel == 0:
            new_pixels.append(replacement)
            remapped += 1
        else:
            new_pixels.append(pixel)

    palette[0:3] = [0, 0, 0]
    image.putpalette(palette)
    image.putdata(new_pixels)
    return remapped


def soften_glow_halos(
    image: Image.Image,
    glow_indices: frozenset[int],
    body_indices: frozenset[int],
    radius: int,
) -> int:
    pixels = list(image.get_flattened_data())
    width, height = image.size
    glow_coords = [
        (x, y)
        for y in range(height)
        for x in range(width)
        if pixels[y * width + x] in glow_indices
    ]
    if not glow_coords:
        return 0

    changed = 0
    for y in range(height):
        for x in range(width):
            index = pixels[y * width + x]
            if index not in body_indices:
                continue

            nearest_glow = None
            nearest_dist_sq = (radius + 1) ** 2
            for gx, gy in glow_coords:
                dist_sq = (gx - x) ** 2 + (gy - y) ** 2
                if dist_sq <= radius * radius and dist_sq < nearest_dist_sq:
                    nearest_dist_sq = dist_sq
                    nearest_glow = pixels[gy * width + gx]

            if nearest_glow is not None:
                pixels[y * width + x] = nearest_glow
                changed += 1

    image.putdata(pixels)
    return changed


def normalize_png(
    path: pathlib.Path,
    *,
    soften_halos: bool,
    halo_radius: int,
    body_indices: frozenset[int],
    glow_indices: frozenset[int],
) -> None:
    image = Image.open(path).convert("P")
    remapped = remap_opaque_index_zero(image)
    softened = 0
    if soften_halos:
        softened = soften_glow_halos(image, glow_indices, body_indices, halo_radius)

    image.save(path)
    print(
        f"{path}: remapped {remapped} index-0 pixels"
        + (f", softened {softened} halo pixels" if soften_halos else "")
    )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("png", type=pathlib.Path, nargs="+")
    parser.add_argument(
        "--soften-halos",
        action="store_true",
        help="Replace body-colored pixels adjacent to glow indices",
    )
    parser.add_argument("--halo-radius", type=int, default=2)
    parser.add_argument(
        "--body-indices",
        type=int,
        nargs="*",
        default=sorted(DEFAULT_BODY_INDICES),
    )
    parser.add_argument(
        "--glow-indices",
        type=int,
        nargs="*",
        default=sorted(DEFAULT_GLOW_INDICES),
    )
    args = parser.parse_args()

    body = frozenset(args.body_indices)
    glow = frozenset(args.glow_indices)
    for png_path in args.png:
        if not png_path.exists():
            print(f"Missing file: {png_path}", file=sys.stderr)
            return 1
        normalize_png(
            png_path,
            soften_halos=args.soften_halos,
            halo_radius=args.halo_radius,
            body_indices=body,
            glow_indices=glow,
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
