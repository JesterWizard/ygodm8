#!/usr/bin/env python3
"""Validate custom opening screen PNGs for the boot splash pipeline."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
OPENING_DIR = ROOT / "src_custom" / "assets" / "opening_screens"
OPENING_WIDTH = 240
OPENING_HEIGHT = 160
OPENING_SIZE = OPENING_WIDTH * OPENING_HEIGHT
MAX_COLORS = 256
REQUIRED_STEMS = ("opening_screen_1", "opening_screen_2", "opening_screen_3")


def discover_opening_pngs(directory: Path = OPENING_DIR) -> list[Path]:
    return [directory / f"{stem}.png" for stem in REQUIRED_STEMS]


def validate_png_layout(image: Image.Image, label: str) -> list[str]:
    errors: list[str] = []

    if image.size != (OPENING_WIDTH, OPENING_HEIGHT):
        errors.append(
            f"{label}: expected {OPENING_WIDTH}x{OPENING_HEIGHT}, got {image.size[0]}x{image.size[1]}"
        )

    if image.mode != "P":
        errors.append(f"{label}: expected indexed PNG (mode P), got {image.mode!r}")

    pixels = list(image.get_flattened_data())
    if len(pixels) != OPENING_SIZE:
        errors.append(f"{label}: expected {OPENING_SIZE} pixels, got {len(pixels)}")
        return errors

    used = sorted(set(pixels))
    if max(used, default=0) >= MAX_COLORS:
        errors.append(
            f"{label}: palette index {max(used)} exceeds max author index {MAX_COLORS - 1}"
        )

    if len(used) > MAX_COLORS:
        errors.append(
            f"{label}: uses {len(used)} palette indices; max supported is {MAX_COLORS}"
        )

    if image.getpalette() is None:
        errors.append(f"{label}: indexed PNG is missing a palette")

    return errors


def validate_opening_png(path: Path) -> list[str]:
    label = path.name
    try:
        with Image.open(path) as image:
            return validate_png_layout(image, label)
    except OSError as exc:
        return [f"{label}: cannot open PNG ({exc})"]


def validate_all(paths: list[Path] | None = None) -> list[str]:
    opening_paths = paths if paths is not None else discover_opening_pngs()
    errors: list[str] = []

    for path in opening_paths:
        if not path.is_file():
            errors.append(f"missing required opening screen PNG: {path}")
            continue
        errors.extend(validate_opening_png(path))

    return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "screens",
        nargs="*",
        type=Path,
        help="Opening screen PNG paths (default: the three required files)",
    )
    args = parser.parse_args()

    paths = args.screens if args.screens else None
    errors = validate_all(paths)
    if errors:
        for message in errors:
            print(message, file=sys.stderr)
        return 1

    count = len(args.screens) if args.screens else len(REQUIRED_STEMS)
    print(f"validate_opening_screen: ok ({count} screen(s))")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
