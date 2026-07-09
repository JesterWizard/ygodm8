#!/usr/bin/env python3
"""Normalize a popup-animation PNG so palette index 0 is the background/transparent color.

Usage:
    python3 tools/normalize_popup_png.py <input.png> [output.png]
    python3 tools/normalize_popup_png.py <input.png> --bg R G B [output.png]

If --bg is omitted, the background color is auto-detected from the four corners
of the image (they must all match).  The detected color becomes palette index 0
and its pixel value is replaced with black (0,0,0) so the hardware treats it as
fully transparent.

The script also collapses any duplicate palette entries so every opaque color
gets exactly one index.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path
from typing import Tuple

try:
    from PIL import Image
except ImportError as exc:  # pragma: no cover
    raise SystemExit("normalize_popup_png.py requires Pillow") from exc


def detect_background_from_corners(img: Image.Image) -> Tuple[int, int, int]:
    """Return the RGB color found at all four corners."""
    w, h = img.size
    corners = [
        img.getpixel((0, 0)),
        img.getpixel((w - 1, 0)),
        img.getpixel((0, h - 1)),
        img.getpixel((w - 1, h - 1)),
    ]
    # Handle RGBA by looking only at RGB
    corners_rgb = [(r, g, b)[:3] for r, g, b, *_ in corners]
    if len(set(corners_rgb)) != 1:
        raise SystemExit(
            f"Corners do not agree on background color: {corners_rgb}\n"
            "Use --bg R G B to specify the background color explicitly."
        )
    return corners_rgb[0]


def normalize_png(
    src_path: Path,
    dst_path: Path,
    bg_rgb: Tuple[int, int, int] | None = None,
) -> None:
    # Convert any input (P, RGB, RGBA) to RGBA for uniform processing
    img = Image.open(src_path).convert("RGBA")
    w, h = img.size

    # Auto-detect background if not provided
    if bg_rgb is None:
        bg_rgb = detect_background_from_corners(img)
        print(f"Detected background color: {bg_rgb}")

    # Determine a background tolerance (for chroma-key screens that have
    # compression-artifact variations around a single target color).
    bg_r, bg_g, bg_b = bg_rgb
    is_bg = lambda r, g, b: (
        abs(r - bg_r) <= 60
        and abs(g - bg_g) <= 60
        and abs(b - bg_b) <= 60
    )

    # Build a clean palette
    # Index 0 = background (stored as black for hardware transparency)
    # Indices 1..N = unique opaque colors
    palette: list[Tuple[int, int, int]] = [(0, 0, 0)]  # index 0 = black / transparent
    color_to_index: dict[Tuple[int, int, int], int] = {}

    # Scan image and collect unique opaque colors
    for y in range(h):
        for x in range(w):
            r, g, b, a = img.getpixel((x, y))
            # Treat background-like colors as transparent regardless of alpha
            if is_bg(r, g, b) or a < 128:
                continue
            rgb = (r, g, b)
            if rgb not in color_to_index:
                idx = len(palette)
                if idx > 255:
                    raise SystemExit(
                        f"Too many unique colors ({idx}) after removing background. "
                        "Max 255 opaque colors + 1 transparent."
                    )
                palette.append(rgb)
                color_to_index[rgb] = idx

    print(f"Unique opaque colors: {len(color_to_index)} (palette size: {len(palette)})")

    # Create new indexed image
    out = Image.new("P", (w, h), 0)
    flat_pal = [0] * 768
    for i, (r, g, b) in enumerate(palette):
        flat_pal[i * 3 + 0] = r
        flat_pal[i * 3 + 1] = g
        flat_pal[i * 3 + 2] = b
    out.putpalette(flat_pal)

    # Remap pixels
    for y in range(h):
        for x in range(w):
            r, g, b, a = img.getpixel((x, y))
            if is_bg(r, g, b) or a < 128:
                out.putpixel((x, y), 0)
            else:
                out.putpixel((x, y), color_to_index[(r, g, b)])

    out.save(dst_path)
    print(f"Saved normalized PNG: {dst_path}")


def main() -> int:
    parser = argparse.ArgumentParser(description="Normalize popup PNG palette")
    parser.add_argument("input", type=Path, help="Input PNG")
    parser.add_argument("-o", "--output", type=Path, help="Output PNG (default: overwrite input)")
    parser.add_argument("--bg", type=str, metavar="R,G,B",
                        help="Background RGB color, e.g. 0,255,0")
    args = parser.parse_args()

    if not args.input.is_file():
        raise SystemExit(f"Input not found: {args.input}")

    out_path = args.output or args.input
    bg_rgb: Tuple[int, int, int] | None = None
    if args.bg:
        parts = [int(p.strip()) for p in args.bg.split(",")]
        if len(parts) != 3 or any(p < 0 or p > 255 for p in parts):
            raise SystemExit("--bg must be three comma-separated integers 0-255, e.g. --bg 0,255,0")
        bg_rgb = tuple(parts)  # type: ignore[assignment]

    normalize_png(args.input, out_path, bg_rgb)
    return 0


if __name__ == "__main__":
    sys.exit(main())
