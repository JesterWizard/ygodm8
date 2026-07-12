#!/usr/bin/env python3
"""
Scan a folder for PNGs and shift all palette colors down by one index.
Palette index 0 is set to #00ff00; the old last palette entry is discarded.
"""

from __future__ import annotations

import argparse
import pathlib
import sys

from PIL import Image


def process_png(path: pathlib.Path) -> str:
    try:
        image = Image.open(path)
    except Exception as exc:
        return f"  Could not open: {exc}"

    if image.mode != "P":
        return "  Skipped (not palette-based)"

    palette = image.getpalette()
    if palette is None:
        return "  Skipped (no palette found)"

    num_colors = len(palette) // 3
    trans_idx: int | None = image.info.get("transparency")  # type: ignore[assignment]

    # Read original pixel data
    pixels = list(image.get_flattened_data())

    # --- Shift palette ---
    # new[0] = #00ff00, new[i] = old[i-1] for i = 1..N-1, old[N-1] discarded
    new_palette = [0, 255, 0]
    for i in range(1, num_colors):
        base = (i - 1) * 3
        new_palette.extend(palette[base : base + 3])

    # --- Remap pixels ---
    # ponytail: pixels that were at old index N-1 are clamped to N-1.
    # Upgrade path: extend the palette by 1 slot instead.
    new_pixels = [min(v + 1, num_colors - 1) for v in pixels]

    # --- Build new image ---
    new_img = Image.new("P", image.size)
    new_img.putpalette(new_palette)
    new_img.putdata(new_pixels)

    # --- Handle transparency (tRNS chunk) ---
    # Old index 0 transparent -> shift to new index 1; new index 0 = opaque
    new_trans: int | None = None
    if trans_idx is not None:
        if trans_idx == 0:
            new_trans = 1
        elif trans_idx < num_colors:
            new_trans = trans_idx + 1

    if new_trans is not None and new_trans < num_colors:
        # Bake transparency into RGBA so the saved PNG has correct alpha
        rgb = new_img.convert("RGB")
        alpha_data = [0 if p == new_trans else 255 for p in new_pixels]
        alpha = Image.new("L", image.size)
        alpha.putdata(alpha_data)
        rgba = Image.merge("RGBA", (*rgb.split(), alpha))
        rgba.save(path, format="PNG")
    else:
        new_img.save(path, format="PNG")

    # Count how many pixels actually changed value
    remapped = sum(1 for a, b in zip(pixels, new_pixels) if a != b)
    return f"  Shifted {num_colors} colors, remapped {remapped} pixels"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("folder", type=pathlib.Path, help="Folder to scan for PNGs")
    args = parser.parse_args()

    folder = args.folder

    if not folder.is_dir():
        print(f"Error: not a valid directory: {folder}", file=sys.stderr)
        return 1

    pngs = sorted(folder.glob("*.png"))
    if not pngs:
        print(f"No PNGs found in {folder}")
        return 0

    for png_path in pngs:
        result = process_png(png_path)
        print(f"{png_path}:{result}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
