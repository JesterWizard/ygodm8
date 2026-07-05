#!/usr/bin/env python3
"""Export overworld millennium-item OBJ frames to indexed PNGs for the status menu."""

from __future__ import annotations

import struct
import sys
from pathlib import Path

try:
    from PIL import Image
except ImportError as exc:  # pragma: no cover
    raise SystemExit("export_millennium_item_pngs.py requires Pillow") from exc

ROOT = Path(__file__).resolve().parents[1]
ENTITIES = ROOT / "src" / "overworld" / "entities"
OUT_DIR = ROOT / "src_custom" / "assets" / "millenium_items"
PALETTE_PATH = ENTITIES / "palette.gbapal"
OBJ_VRAM_TILE_STRIDE = 28
FRAME_TILE_OFFSET = 0
FRAME_SRC_STRIDE = 0x180
FRAME_GROUP_BYTES = 128
FRAME_GROUPS = 4

ITEMS: tuple[tuple[str, str], ...] = (
    ("puzzle", "117.4bpp"),
    ("ring", "120.4bpp"),
    ("key", "118.4bpp"),
    ("scale", "121.4bpp"),
    ("rod", "116.4bpp"),
    ("eye", "119.4bpp"),
    ("necklace", "115.4bpp"),
)


def gba_rgb555_to_rgb888(color: int) -> tuple[int, int, int]:
    r = color & 0x1F
    g = (color >> 5) & 0x1F
    b = (color >> 10) & 0x1F
    return (r << 3, g << 3, b << 3)


def load_entity_palette_bank(bank: int) -> list[tuple[int, int, int]]:
    data = PALETTE_PATH.read_bytes()
    colors: list[tuple[int, int, int]] = []
    for index in range(16):
        offset = (bank * 16 + index) * 2
        word = struct.unpack_from("<H", data, offset)[0]
        colors.append(gba_rgb555_to_rgb888(word))
    return colors


def decode_tile_pixels(tile_data: bytes) -> list[list[int]]:
    pixels = [[0] * 8 for _ in range(8)]
    for row in range(8):
        for col in range(0, 8, 2):
            byte = tile_data[row * 4 + col // 2]
            pixels[row][col] = byte & 0x0F
            pixels[row][col + 1] = (byte >> 4) & 0x0F
    return pixels


def blit_tile(image: Image.Image, tile_data: bytes, x0: int, y0: int) -> None:
    pixels = decode_tile_pixels(tile_data)
    for y in range(8):
        for x in range(8):
            image.putpixel((x0 + x, y0 + y), pixels[y][x])


def load_obj_frame(blob: bytes, frame_tile_offset: int) -> bytes:
    out = bytearray(4096)
    src_base = frame_tile_offset * 32
    dest = 0
    for group in range(FRAME_GROUPS):
        src = src_base + group * FRAME_SRC_STRIDE
        out[dest : dest + FRAME_GROUP_BYTES] = blob[src : src + FRAME_GROUP_BYTES]
        dest += OBJ_VRAM_TILE_STRIDE * 32
    return bytes(out)


def export_item_png(stem: str, source_name: str, palette_rgb: list[tuple[int, int, int]]) -> None:
    blob = (ENTITIES / source_name).read_bytes()
    obj_vram = load_obj_frame(blob, FRAME_TILE_OFFSET)
    image = Image.new("P", (32, 32))
    flat_palette: list[int] = []
    for red, green, blue in palette_rgb:
        flat_palette.extend((red, green, blue))
    flat_palette.extend([0, 0, 0] * (256 - len(palette_rgb)))
    image.putpalette(flat_palette)

    row_starts = [group * OBJ_VRAM_TILE_STRIDE for group in range(4)]
    for row, tile_row in enumerate(row_starts):
        for col in range(4):
            tile_index = tile_row + col
            tile_data = obj_vram[tile_index * 32 : tile_index * 32 + 32]
            blit_tile(image, tile_data, col * 8, row * 8)

    OUT_DIR.mkdir(parents=True, exist_ok=True)
    out_path = OUT_DIR / f"{stem}.png"
    image.save(out_path)
    print(f"wrote {out_path.relative_to(ROOT)}")


def main() -> int:
    palette_rgb = load_entity_palette_bank(6)
    for stem, source_name in ITEMS:
        source_path = ENTITIES / source_name
        if not source_path.is_file():
            raise SystemExit(f"missing source sprite: {source_path}")
        export_item_png(stem, source_name, palette_rgb)
    return 0


if __name__ == "__main__":
    sys.exit(main())
