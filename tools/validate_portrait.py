#!/usr/bin/env python3
"""Validate custom dialogue portrait PNGs for the GBA portrait pipeline."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
PORTRAIT_DIR = ROOT / "src_custom" / "assets" / "portraits"
PORTRAIT_WIDTH = 64
PORTRAIT_HEIGHT = 64
PORTRAIT_SIZE = PORTRAIT_WIDTH * PORTRAIT_HEIGHT
SHIFTED_MIN = 0xC1
SHIFTED_MAX = 0xFF

sys.path.insert(0, str(ROOT / "tools"))

from normalize_portrait_png import normalize_portrait  # noqa: E402
from offset_portrait_8bpp import offset_portrait_bytes  # noqa: E402


def discover_portrait_pngs(directory: Path = PORTRAIT_DIR) -> list[Path]:
    if not directory.is_dir():
        return []
    return sorted(path for path in directory.glob("*.png") if path.is_file())


def linear_to_tiled_8bpp(pixels: list[int], width: int = PORTRAIT_WIDTH) -> bytes:
    """Match gbagfx ConvertToTiles8Bpp for 64x64, metatile 1x1, 8bpp."""
    height = len(pixels) // width
    tiles_wide = width // 8
    out = bytearray(PORTRAIT_SIZE)
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


def validate_palette_index_zero_black(image: Image.Image) -> list[str]:
    palette = image.getpalette()
    if palette is None:
        return ["indexed PNG must include a palette"]
    if palette[0:3] != [0, 0, 0]:
        return [
            "palette index 0 must be black (0,0,0) for OBJ transparency; "
            "run tools/normalize_portrait_png.py or fix the source PNG"
        ]
    return []


def validate_png_layout(image: Image.Image, label: str) -> list[str]:
    errors: list[str] = []

    if image.size != (PORTRAIT_WIDTH, PORTRAIT_HEIGHT):
        errors.append(
            f"{label}: expected {PORTRAIT_WIDTH}x{PORTRAIT_HEIGHT}, got {image.size[0]}x{image.size[1]}"
        )

    if image.mode != "P":
        errors.append(f"{label}: expected indexed PNG (mode P), got {image.mode!r}")

    pixels = list(image.get_flattened_data())
    if len(pixels) != PORTRAIT_SIZE:
        errors.append(f"{label}: expected {PORTRAIT_SIZE} pixels, got {len(pixels)}")
        return errors

    max_index = max(pixels) if pixels else 0
    if max_index > 63:
        errors.append(f"{label}: palette index {max_index} exceeds maximum supported index 63")

    errors.extend(f"{label}: {msg}" for msg in validate_palette_index_zero_black(image))
    return errors


def validate_shifted_tiles(shifted: bytes, label: str) -> list[str]:
    errors: list[str] = []

    if len(shifted) != PORTRAIT_SIZE:
        errors.append(f"{label}: expected {PORTRAIT_SIZE} shifted bytes, got {len(shifted)}")
        return errors

    for offset, value in enumerate(shifted):
        if value == 0:
            continue
        if value < SHIFTED_MIN or value > SHIFTED_MAX:
            errors.append(
                f"{label}: byte 0x{value:02X} at offset {offset} is outside OBJ range "
                f"0x{SHIFTED_MIN:02X}..0x{SHIFTED_MAX:02X} (index 0 must stay transparent)"
            )
            break

    if 0xC0 in shifted:
        errors.append(
            f"{label}: tile byte 0xC0 is reserved; use index 0 for transparency and indices 1..63 for colors"
        )

    return errors


def validate_portrait_png(path: Path) -> list[str]:
    label = path.name
    errors: list[str] = []

    try:
        source = Image.open(path)
    except OSError as exc:
        return [f"{label}: cannot open PNG ({exc})"]

    errors.extend(validate_png_layout(source, label))

    unchanged = source.copy()
    if normalize_portrait(unchanged):
        errors.append(
            f"{label}: palette must already reserve index 0 for black transparency "
            "(do not rely on build-time normalization to fix palette order)"
        )

    normalized = source.copy()
    normalize_portrait(normalized)
    errors.extend(validate_png_layout(normalized, f"{label} (normalized)"))

    pixels = list(normalized.get_flattened_data())
    tiled = linear_to_tiled_8bpp(pixels)
    try:
        shifted = offset_portrait_bytes(tiled)
    except ValueError as exc:
        errors.append(f"{label}: {exc}")
        return errors

    errors.extend(validate_shifted_tiles(shifted, f"{label} (shifted)"))
    return errors


def validate_all(paths: list[Path] | None = None) -> list[str]:
    portrait_paths = paths if paths is not None else discover_portrait_pngs()
    if not portrait_paths:
        return [f"no portrait PNGs found under {PORTRAIT_DIR}"]

    errors: list[str] = []
    for path in portrait_paths:
        errors.extend(validate_portrait_png(path))
    return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "portraits",
        nargs="*",
        type=Path,
        help="Portrait PNG paths (default: all under src_custom/assets/portraits/)",
    )
    args = parser.parse_args()

    paths = args.portraits if args.portraits else None
    errors = validate_all(paths)
    if errors:
        for message in errors:
            print(message, file=sys.stderr)
        return 1

    count = len(args.portraits) if args.portraits else len(discover_portrait_pngs())
    print(f"validate_portrait: ok ({count} portrait(s))")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
