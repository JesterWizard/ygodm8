#!/usr/bin/env python3
"""Validate custom title screen PNG for the 8bpp title background pipeline."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
TITLE_DIR = ROOT / "src_custom" / "assets" / "title_screens"
TITLE_WIDTH = 240
TITLE_HEIGHT = 160
TITLE_SIZE = TITLE_WIDTH * TITLE_HEIGHT
MAX_COLORS = 256
REQUIRED_STEM = "title_screen"


def default_png_path(directory: Path = TITLE_DIR) -> Path:
    return directory / f"{REQUIRED_STEM}.png"


def validate_png_layout(image: Image.Image, label: str) -> list[str]:
    errors: list[str] = []

    if image.size != (TITLE_WIDTH, TITLE_HEIGHT):
        errors.append(
            f"{label}: expected {TITLE_WIDTH}x{TITLE_HEIGHT}, got {image.size[0]}x{image.size[1]}"
        )

    if image.mode != "P":
        errors.append(f"{label}: expected indexed PNG (mode P), got {image.mode!r}")

    pixels = list(image.get_flattened_data())
    if len(pixels) != TITLE_SIZE:
        errors.append(f"{label}: expected {TITLE_SIZE} pixels, got {len(pixels)}")
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


def validate_title_png(path: Path) -> list[str]:
    label = path.name
    try:
        with Image.open(path) as image:
            return validate_png_layout(image, label)
    except OSError as exc:
        return [f"{label}: cannot open PNG ({exc})"]


def validate_all(path: Path | None = None) -> list[str]:
    title_path = path if path is not None else default_png_path()
    if not title_path.is_file():
        return [f"missing required title screen PNG: {title_path}"]
    return validate_title_png(title_path)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "screen",
        nargs="?",
        type=Path,
        help="Title screen PNG path (default: title_screen.png)",
    )
    args = parser.parse_args()

    errors = validate_all(args.screen)
    if errors:
        for message in errors:
            print(message, file=sys.stderr)
        return 1

    print("validate_title_screen: ok")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
