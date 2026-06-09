#!/usr/bin/env python3
"""Create a placeholder indexed PNG for the custom title screen background."""

from __future__ import annotations

from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
OUT_DIR = ROOT / "src_custom" / "assets" / "title_screens"

WIDTH = 240
HEIGHT = 160
PLACEHOLDER_RGB = (32, 48, 96)


def main() -> int:
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    out_path = OUT_DIR / "title_screen.png"
    if out_path.is_file():
        print(f"generate_title_screen_placeholders: skip existing {out_path.name}")
        return 0

    image = Image.new("P", (WIDTH, HEIGHT))
    palette = [0, 0, 0, *PLACEHOLDER_RGB]
    while len(palette) < 256 * 3:
        palette.extend((0, 0, 0))
    image.putpalette(palette)
    image.paste(1, (0, 0, WIDTH, HEIGHT))
    image.save(out_path)
    print("generate_title_screen_placeholders: wrote title_screen.png")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
