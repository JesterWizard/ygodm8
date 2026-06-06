#!/usr/bin/env python3
"""Validate custom event CG PNGs for the GBA CG pipeline."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
CG_DIR = ROOT / "src_custom" / "assets" / "cgs"
CG_WIDTH = 240
CG_HEIGHT = 160
CG_SIZE = CG_WIDTH * CG_HEIGHT

sys.path.insert(0, str(ROOT / "tools"))

from cg_remap import MAX_CG_AUTHOR_INDEX, MAX_CG_COLORS, PALETTE_OFFSET, build_cg_index_remap  # noqa: E402
from offset_cg_8bpp import offset_cg_png_bytes  # noqa: E402


def discover_cg_pngs(directory: Path = CG_DIR) -> list[Path]:
    if not directory.is_dir():
        return []
    return sorted(path for path in directory.glob("*.png") if path.is_file())


def linear_to_tiled_8bpp(pixels: list[int], width: int = CG_WIDTH) -> bytes:
    height = len(pixels) // width
    tiles_wide = width // 8
    out = bytearray(CG_SIZE)
    tile_index = 0

    for tile_y in range(height // 8):
        for tile_x in range(tiles_wide):
            base = tile_index * 64
            for row in range(8):
                src_y = tile_y * 8 + row
                for col in range(8):
                    src_x = tile_x * 8 + col
                    out[base + row * 8 + col] = pixels[src_y * width + src_x]
            tile_index += 1

    return bytes(out)


def validate_png_layout(image: Image.Image, label: str) -> list[str]:
    errors: list[str] = []

    if image.size != (CG_WIDTH, CG_HEIGHT):
        errors.append(
            f"{label}: expected {CG_WIDTH}x{CG_HEIGHT}, got {image.size[0]}x{image.size[1]}"
        )

    if image.mode != "P":
        errors.append(f"{label}: expected indexed PNG (mode P), got {image.mode!r}")

    pixels = list(image.get_flattened_data())
    if len(pixels) != CG_SIZE:
        errors.append(f"{label}: expected {CG_SIZE} pixels, got {len(pixels)}")
        return errors

    used = sorted(set(pixels))
    if max(used, default=0) > MAX_CG_AUTHOR_INDEX:
        errors.append(
            f"{label}: palette index {max(used)} exceeds max author index "
            f"{MAX_CG_AUTHOR_INDEX}"
        )

    if len(used) > MAX_CG_COLORS:
        errors.append(
            f"{label}: uses {len(used)} palette indices; max supported is {MAX_CG_COLORS}"
        )

    return errors


def validate_shifted_tiles(shifted: bytes, remap: dict[int, int], label: str) -> list[str]:
    errors: list[str] = []

    if len(shifted) != CG_SIZE:
        errors.append(f"{label}: expected {CG_SIZE} shifted bytes, got {len(shifted)}")
        return errors

    expected_min = PALETTE_OFFSET
    expected_max = PALETTE_OFFSET + MAX_CG_AUTHOR_INDEX
    for offset, value in enumerate(shifted):
        if value < expected_min or value > expected_max:
            errors.append(
                f"{label}: byte 0x{value:02X} at offset {offset} is outside BG range "
                f"0x{expected_min:02X}..0x{expected_max:02X}"
            )
            break

    if not errors and remap:
        observed_max = max(shifted)
        expected_max_used = max(remap.values())
        if observed_max != expected_max_used:
            errors.append(
                f"{label}: shifted max 0x{observed_max:02X} != expected 0x{expected_max_used:02X}"
            )

    return errors


def validate_cg_png(path: Path) -> list[str]:
    label = path.name
    errors: list[str] = []

    try:
        source = Image.open(path)
    except OSError as exc:
        return [f"{label}: cannot open PNG ({exc})"]

    errors.extend(validate_png_layout(source, label))
    if errors:
        return errors

    pixels = list(source.get_flattened_data())
    tiled = linear_to_tiled_8bpp(pixels)
    try:
        shifted = offset_cg_png_bytes(path, tiled)
    except ValueError as exc:
        errors.append(f"{label}: {exc}")
        return errors

    remap = build_cg_index_remap(pixels)
    errors.extend(validate_shifted_tiles(shifted, remap, f"{label} (shifted)"))
    return errors


def validate_all(paths: list[Path] | None = None) -> list[str]:
    cg_paths = paths if paths is not None else discover_cg_pngs()
    if not cg_paths:
        return [f"no CG PNGs found under {CG_DIR}"]

    errors: list[str] = []
    for path in cg_paths:
        errors.extend(validate_cg_png(path))
    return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "cgs",
        nargs="*",
        type=Path,
        help="CG PNG paths (default: all under src_custom/assets/cgs/)",
    )
    args = parser.parse_args()

    paths = args.cgs if args.cgs else None
    errors = validate_all(paths)
    if errors:
        for message in errors:
            print(message, file=sys.stderr)
        return 1

    count = len(args.cgs) if args.cgs else len(discover_cg_pngs())
    print(f"validate_cg: ok ({count} CG(s))")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
