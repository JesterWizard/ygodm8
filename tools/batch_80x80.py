#!/usr/bin/env python3
"""Batch-process card art from 512x512 sources to 80x80 indexed PNG.

Matches Mini Photoshop defaults: stretch resize, selective median-cut palette,
64 colors (minus one slot when alpha is present), PNG output.

Default folders:
  src_custom/assets/cards/512x512  (input)
  src_custom/assets/cards/80x80    (output)

Skips files whose output already exists unless --force is passed.
"""

from __future__ import annotations

import argparse
import sys
from dataclasses import dataclass
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
CARD_ASSET_ROOT = ROOT / "src_custom/assets/cards"
DEFAULT_INPUT_DIR = CARD_ASSET_ROOT / "512x512"
DEFAULT_OUTPUT_DIR = CARD_ASSET_ROOT / "80x80"

SUPPORTED_EXTENSIONS = {".png", ".gif", ".bmp"}
TARGET_SIZE = (80, 80)
DEFAULT_COLOR_COUNT = 64


@dataclass
class ColorBucket:
    r: int
    g: int
    b: int
    count: int


def has_transparency(image: Image.Image) -> bool:
    rgba = image.convert("RGBA")
    _, _, _, alpha = rgba.split()
    return alpha.getextrema()[0] < 255


def compute_local_variance(rgba: Image.Image) -> list[float]:
    w, h = rgba.size
    pixels = rgba.load()
    variance = [0.0] * (w * h)

    for y in range(h):
        for x in range(w):
            _, _, _, a = pixels[x, y]
            if a < 128:
                variance[y * w + x] = 0.5
                continue

            r0, g0, b0, _ = pixels[x, y]
            total = 0.0
            count = 0
            for dy in (-1, 0, 1):
                for dx in (-1, 0, 1):
                    if dx == 0 and dy == 0:
                        continue
                    nx, ny = x + dx, y + dy
                    if nx < 0 or ny < 0 or nx >= w or ny >= h:
                        continue
                    _, _, _, na = pixels[nx, ny]
                    if na < 128:
                        continue
                    r1, g1, b1, _ = pixels[nx, ny]
                    total += abs(r0 - r1) + abs(g0 - g1) + abs(b0 - b1)
                    count += 1

            variance[y * w + x] = 1.0 if count == 0 else 1.0 + total / (count * 3.0)

    return variance


def build_histogram(rgba: Image.Image, has_alpha: bool, selective: bool) -> list[ColorBucket]:
    w, h = rgba.size
    pixels = rgba.load()
    variance = compute_local_variance(rgba) if selective else None
    buckets: dict[int, ColorBucket] = {}

    for y in range(h):
        for x in range(w):
            r, g, b, a = pixels[x, y]
            if has_alpha and a < 128:
                continue

            weight = max(1, round(variance[y * w + x])) if selective else 1
            key = (r << 16) | (g << 8) | b
            bucket = buckets.get(key)
            if bucket is None:
                buckets[key] = ColorBucket(r, g, b, weight)
            else:
                bucket.count += weight

    return list(buckets.values())


class ColorNode:
    __slots__ = ("buckets", "range")

    def __init__(self, buckets: list[ColorBucket], range_: int) -> None:
        self.buckets = buckets
        self.range = range_

    @classmethod
    def from_buckets(cls, buckets: list[ColorBucket]) -> ColorNode:
        min_r = min(b.r for b in buckets)
        max_r = max(b.r for b in buckets)
        min_g = min(b.g for b in buckets)
        max_g = max(b.g for b in buckets)
        min_b = min(b.b for b in buckets)
        max_b = max(b.b for b in buckets)
        range_ = max(max_r - min_r, max_g - min_g, max_b - min_b)
        return cls(buckets, range_)

    def split(self) -> tuple[ColorNode, ColorNode]:
        min_r = min(b.r for b in self.buckets)
        max_r = max(b.r for b in self.buckets)
        min_g = min(b.g for b in self.buckets)
        max_g = max(b.g for b in self.buckets)
        min_b = min(b.b for b in self.buckets)
        max_b = max(b.b for b in self.buckets)
        r_range = max_r - min_r
        g_range = max_g - min_g
        b_range = max_b - min_b

        if r_range >= g_range and r_range >= b_range:
            axis = 0
        elif g_range >= b_range:
            axis = 1
        else:
            axis = 2

        key = (lambda b: b.r) if axis == 0 else ((lambda b: b.g) if axis == 1 else (lambda b: b.b))
        sorted_buckets = sorted(self.buckets, key=key)
        mid = len(sorted_buckets) // 2
        return (
            ColorNode.from_buckets(sorted_buckets[:mid]),
            ColorNode.from_buckets(sorted_buckets[mid:]),
        )

    def average_color(self) -> tuple[int, int, int]:
        total_r = total_g = total_b = total_count = 0
        for bucket in self.buckets:
            total_r += bucket.r * bucket.count
            total_g += bucket.g * bucket.count
            total_b += bucket.b * bucket.count
            total_count += bucket.count

        if total_count == 0:
            return (0, 0, 0)

        return (
            total_r // total_count,
            total_g // total_count,
            total_b // total_count,
        )


def median_cut(buckets: list[ColorBucket], max_colors: int) -> list[tuple[int, int, int]]:
    if not buckets:
        return [(0, 0, 0)]

    if len(buckets) <= max_colors:
        return [(b.r, b.g, b.b) for b in buckets]

    nodes = [ColorNode.from_buckets(buckets)]
    while len(nodes) < max_colors:
        nodes.sort(key=lambda n: n.range, reverse=True)
        node = nodes[0]
        if len(node.buckets) <= 1:
            break
        nodes.pop(0)
        left, right = node.split()
        nodes.extend((left, right))

    return [node.average_color() for node in nodes]


def build_selective_palette(rgba: Image.Image, color_count: int, has_alpha: bool) -> list[tuple[int, int, int, int]]:
    palette_slots = color_count - 1 if has_alpha else color_count
    colors = median_cut(build_histogram(rgba, has_alpha, selective=True), max(1, palette_slots))
    palette = [(r, g, b, 255) for r, g, b in colors]
    if has_alpha:
        palette.append((0, 0, 0, 0))
    return palette


def color_distance(a: tuple[int, int, int, int], b: tuple[int, int, int, int]) -> int:
    return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2 + (a[2] - b[2]) ** 2


def quantize_to_indexed(rgba: Image.Image, palette: list[tuple[int, int, int, int]], has_alpha: bool) -> Image.Image:
    w, h = rgba.size
    pixels = rgba.load()
    transparent_index = len(palette) - 1 if has_alpha else 0
    search_limit = len(palette) - 1 if has_alpha else len(palette)

    indexed = Image.new("P", (w, h))
    flat_palette: list[int] = []
    for r, g, b, a in palette:
        flat_palette.extend((r, g, b))
    while len(flat_palette) < 768:
        flat_palette.extend((0, 0, 0))
    indexed.putpalette(flat_palette)

    index_pixels = indexed.load()
    for y in range(h):
        for x in range(w):
            r, g, b, a = pixels[x, y]
            if has_alpha and a < 128:
                index_pixels[x, y] = transparent_index
                continue

            pixel = (r, g, b, 255)
            best = 0
            best_dist = color_distance(pixel, palette[0])
            for i in range(1, search_limit):
                dist = color_distance(pixel, palette[i])
                if dist < best_dist:
                    best_dist = dist
                    best = i
            index_pixels[x, y] = best

    return indexed


def process_image(source: Image.Image, size: tuple[int, int], color_count: int) -> Image.Image:
    rgba = source.convert("RGBA")
    resized = rgba.resize(size, Image.Resampling.BILINEAR)
    alpha = has_transparency(resized)
    palette = build_selective_palette(resized, color_count, alpha)
    return quantize_to_indexed(resized, palette, alpha)


def collect_input_files(input_dir: Path) -> list[Path]:
    files = [
        path
        for path in input_dir.iterdir()
        if path.is_file() and path.suffix.lower() in SUPPORTED_EXTENSIONS
    ]
    return sorted(files, key=lambda p: p.name.lower())


def parse_args(argv: list[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Resize card art from 512x512 to 80x80 with selective palette and bilinear filtering."
    )
    parser.add_argument(
        "input_dir",
        nargs="?",
        type=Path,
        default=DEFAULT_INPUT_DIR,
        help=f"Folder containing 512x512 source images (default: {DEFAULT_INPUT_DIR.relative_to(ROOT)})",
    )
    parser.add_argument(
        "output_dir",
        nargs="?",
        type=Path,
        default=DEFAULT_OUTPUT_DIR,
        help=f"Folder for 80x80 PNG output (default: {DEFAULT_OUTPUT_DIR.relative_to(ROOT)})",
    )
    parser.add_argument(
        "--size",
        type=int,
        nargs=2,
        metavar=("W", "H"),
        default=TARGET_SIZE,
        help=f"Output dimensions (default: {TARGET_SIZE[0]} {TARGET_SIZE[1]})",
    )
    parser.add_argument(
        "--colors",
        type=int,
        default=DEFAULT_COLOR_COUNT,
        help=f"Palette size 2-256 (default: {DEFAULT_COLOR_COUNT})",
    )
    parser.add_argument(
        "--force",
        action="store_true",
        help="Reprocess even when the output file already exists",
    )
    return parser.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv or sys.argv[1:])
    input_dir = args.input_dir.resolve()
    output_dir = args.output_dir.resolve()
    size = tuple(args.size)
    color_count = max(2, min(256, args.colors))

    if not input_dir.is_dir():
        print(f"Input folder not found: {input_dir}", file=sys.stderr)
        return 1

    output_dir.mkdir(parents=True, exist_ok=True)
    files = collect_input_files(input_dir)
    if not files:
        print(f"No supported images found in {input_dir}")
        return 0

    print(f"Input:  {input_dir}")
    print(f"Output: {output_dir}\n")

    processed = skipped = errors = 0
    for path in files:
        output_path = output_dir / f"{path.stem}.png"
        if output_path.exists() and not args.force:
            print(f"skip  {path.name}")
            skipped += 1
            continue

        try:
            with Image.open(path) as image:
                result = process_image(image, size, color_count)
                result.save(output_path, format="PNG", optimize=True)
            print(f"done  {path.name} -> {output_path.name}")
            processed += 1
        except Exception as exc:
            print(f"error {path.name}: {exc}", file=sys.stderr)
            errors += 1

    print(f"\nProcessed: {processed}, skipped: {skipped}, errors: {errors}")
    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
