#!/usr/bin/env python3
"""
Normalize custom 80x80 big card PNGs for the GBA card-detail pipeline.

Vanilla CopyCardArtDataToBuffers forces palette index 0 to color 0x0000 (black).
Photoshop "Save for Web" often places opaque edge colors on index 0 while still
enabling transparency, which makes those pixels render black in-game.

This script:
  1. Trims oversized PLTE chunks (e.g. Photoshop's 256 slots) down to 64 entries
     when pixel data only uses indices 0-63, so gbagfx emits a valid 64-color
     .gbapal without re-quantizing the art.
  2. Remaps opaque index-0 pixels to the closest existing palette entry.
  3. Sets palette entry 0 to black (reserved for transparency / empty tiles).
  4. Pads palettes with fewer than 64 entries up to 64 slots for the GBA pipeline.
  5. Optionally softens high-contrast halos by replacing body-colored pixels that
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
TARGET_PALETTE_COLORS = 64


def color_distance_sq(a: tuple[int, int, int], b: tuple[int, int, int]) -> int:
    return sum((x - y) ** 2 for x, y in zip(a, b))


def palette_rgb(palette: list[int], index: int) -> tuple[int, int, int]:
    base = index * 3
    return palette[base], palette[base + 1], palette[base + 2]


def closest_palette_index(
    palette: list[int], target: tuple[int, int, int], exclude: frozenset[int]
) -> int:
    num_colors = len(palette) // 3
    best_index = 1
    best_distance = math.inf
    for index in range(num_colors):
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


def trim_palette_to_64(image: Image.Image) -> int:
    """Shrink an oversized PLTE chunk to 64 entries without re-quantizing pixels.

    Photoshop "Save for Web" often writes 256 palette slots even when only the
    first 64 are referenced. gbagfx copies the full PLTE size, which breaks the
    64/112-color .gbapal validation in add_card_art.py.

    Returns the number of trailing palette entries removed. Raises SystemExit when
    pixel data references an index at or above 64 (extended-palette art must not be
    trimmed here).
    """
    palette = image.getpalette()
    if palette is None:
        return 0

    num_colors = len(palette) // 3
    if num_colors <= TARGET_PALETTE_COLORS:
        return 0

    pixels = list(image.get_flattened_data())
    if pixels:
        max_index = max(pixels)
        if max_index >= TARGET_PALETTE_COLORS:
            raise SystemExit(
                f"Cannot trim palette from {num_colors} to {TARGET_PALETTE_COLORS} entries: "
                f"pixel data uses index {max_index}. Use <= {TARGET_PALETTE_COLORS - 1} "
                "opaque indices or the extended big-card palette path."
            )

    image.putpalette(palette[: TARGET_PALETTE_COLORS * 3])
    return num_colors - TARGET_PALETTE_COLORS


def pad_palette_to_64(image: Image.Image) -> int:
    """Pad palettes with fewer than 64 entries up to the GBA big-art size.

    Some export tools omit unused trailing slots. Returns the number of entries added.
    """
    palette = image.getpalette()
    num_colors = len(palette) // 3 if palette else 0
    if num_colors >= TARGET_PALETTE_COLORS:
        return 0
    added = TARGET_PALETTE_COLORS - num_colors
    image.putpalette(palette + [0, 0, 0] * added)
    return added


def normalize_png(
    path: pathlib.Path,
    *,
    soften_halos: bool,
    halo_radius: int,
    body_indices: frozenset[int],
    glow_indices: frozenset[int],
) -> None:
    image = Image.open(path).convert("P")
    trimmed = trim_palette_to_64(image)
    remapped = remap_opaque_index_zero(image)
    padded = pad_palette_to_64(image)
    softened = 0
    if soften_halos:
        softened = soften_glow_halos(image, glow_indices, body_indices, halo_radius)

    image.save(path, format="PNG", optimize=True)
    parts = [f"remapped {remapped} index-0 pixels"]
    if trimmed:
        parts.append(f"trimmed {trimmed} palette entries")
    if padded:
        parts.append(f"padded {padded} palette entries")
    if soften_halos:
        parts.append(f"softened {softened} halo pixels")
    print(f"{path}: {', '.join(parts)}")


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
