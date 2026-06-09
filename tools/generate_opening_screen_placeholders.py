#!/usr/bin/env python3
"""Create placeholder indexed PNGs for the three boot opening screens."""

from __future__ import annotations

from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
OUT_DIR = ROOT / "src_custom" / "assets" / "opening_screens"

WIDTH = 240
HEIGHT = 160

PLACEHOLDER_COLORS = (
    (24, 32, 96),
    (96, 24, 32),
    (24, 96, 48),
)


def write_placeholder(index: int, rgb: tuple[int, int, int]) -> None:
    image = Image.new("P", (WIDTH, HEIGHT))
    palette = [0, 0, 0, *rgb]
    while len(palette) < 256 * 3:
        palette.extend((0, 0, 0))
    image.putpalette(palette)
    image.paste(1, (0, 0, WIDTH, HEIGHT))
    out_path = OUT_DIR / f"opening_screen_{index}.png"
    image.save(out_path)


def main() -> int:
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    for index, rgb in enumerate(PLACEHOLDER_COLORS, start=1):
        out_path = OUT_DIR / f"opening_screen_{index}.png"
        if out_path.is_file():
            print(f"generate_opening_screen_placeholders: skip existing {out_path.name}")
            continue
        write_placeholder(index, rgb)
        print(f"generate_opening_screen_placeholders: wrote opening_screen_{index}.png")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
