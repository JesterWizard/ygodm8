#!/usr/bin/env python3
"""Extract all 61 vanilla map backgrounds as separate ground/roof PNG renders.

Reads baserom.gba, decompresses LZ77 tilesets, reads 8bpp tilemaps and
palettes, renders each layer separately, and writes to
src_custom/assets/maps/map_XX_{ground,roof}.png.

The GBA overworld uses 8bpp (256-color) BG mode (REG_BGxCNT bit 7 set).
Tiles are 64 bytes each (1 byte per pixel).

The GBA BG palette is assembled at runtime from two sources:
  - Font palette (g82ADC8C): 16 colors → indices 0-15
  - Map palette (g8E11CD0[map_id]): 240 colors → indices 16-255
The combined 256-color palette is copied to PLTT (0x05000000).
Pixel values in tile data directly index this palette.

Gamma: GBA RGB555 values are linear. Modern sRGB monitors apply ~2.2 gamma,
so we apply inverse gamma (^0.455) for correct display.
"""

from __future__ import annotations

import struct
import sys
from pathlib import Path

try:
    from PIL import Image
except ImportError:
    print("error: Pillow (PIL) is required — pip install Pillow")
    sys.exit(1)

ROOT = Path(__file__).resolve().parents[1]
ROM_PATH = ROOT / "baserom.gba"
OUT_DIR = ROOT / "src_custom" / "assets" / "maps"

ROM_BASE = 0x08000000
MAP_COUNT = 61
TILEMAP_W = 32
TILEMAP_H = 32
TILE_SIZE = 8
TILE_BYTES_8BPP = 64  # 8 rows × 8 bytes
PAL_BG_SIZE = 256     # 256 colors in GBA BG palette

# ROM symbol addresses
SYM_MAP_TILESETS = 0x08E119F4       # u32*[] — LZ77-compressed tileset ptrs
SYM_LOW_LAYER_TILEMAPS = 0x08E11AE8  # u16*[] — ground tilemap ptrs
SYM_HIGH_LAYER_TILEMAPS = 0x08E11BDC # u16*[] — roof tilemap ptrs
SYM_PALETTES = 0x08E11CD0            # u16*[] — 240-color map palette ptrs

# Font palette (16 colors, bank 0 of GBA BG palette)
FONT_PALETTE_ADDR = 0x082ADC8C

# Special cases
CABLE_CAR_MAP_ID = 0x29
CABLE_CAR_TILEMAP_ADDR = 0x0841D91C  # BG3 cable car window overlay

GAMMA = 2.2


def rom_offset(addr: int) -> int:
    return addr - ROM_BASE


def read_ptr_table(rom: bytes, addr: int, count: int) -> list[int]:
    off = rom_offset(addr)
    return [struct.unpack_from("<I", rom, off + i * 4)[0] for i in range(count)]


def lz77_decompress(data: bytes) -> bytes:
    assert data[0] == 0x10, f"Not LZ77 data: magic={data[0]:#x}"
    uncomp_size = data[1] | (data[2] << 8) | (data[3] << 16)
    result = bytearray()
    pos = 4
    while len(result) < uncomp_size:
        flags = data[pos]
        pos += 1
        for bit in range(7, -1, -1):
            if len(result) >= uncomp_size:
                break
            if not (flags & (1 << bit)):
                result.append(data[pos])
                pos += 1
            else:
                block_byte0 = data[pos]
                block_byte1 = data[pos + 1]
                pos += 2
                count = (block_byte0 >> 4) + 3
                offset = ((block_byte0 & 0xF) << 8) | block_byte1
                offset += 1
                for _ in range(count):
                    result.append(result[-offset])
    return bytes(result[:uncomp_size])


def read_tilemap(rom: bytes, ptr: int) -> list[list[int]]:
    off = rom_offset(ptr)
    raw = struct.unpack_from(f"<{TILEMAP_W * TILEMAP_H}H", rom, off)
    return [list(raw[i * TILEMAP_W:(i + 1) * TILEMAP_W]) for i in range(TILEMAP_H)]


def _gba555_to_srgb(entries: list[int]) -> list[tuple[int, int, int]]:
    inv_gamma = 1.0 / GAMMA
    colors = []
    for e in entries:
        r5 = e & 0x1F
        g5 = (e >> 5) & 0x1F
        b5 = (e >> 10) & 0x1F
        r = int(((r5 / 31.0) ** inv_gamma) * 255 + 0.5)
        g = int(((g5 / 31.0) ** inv_gamma) * 255 + 0.5)
        b = int(((b5 / 31.0) ** inv_gamma) * 255 + 0.5)
        colors.append((r, g, b))
    return colors


def build_bg_palette(rom: bytes, palette_ptr: int) -> list[tuple[int, int, int]]:
    """Build the 256-color GBA BG palette as the game does at runtime.

    The game copies:
      1. Font palette (16 colors from g82ADC8C) → gPaletteBuffer[0..15]
      2. Map palette (240 colors from g8E11CD0[map_id]) → gPaletteBuffer[16..255]

    Returns a list of 256 RGB888 tuples with sRGB gamma correction.
    """
    font_off = rom_offset(FONT_PALETTE_ADDR)
    font_raw = struct.unpack_from("<16H", rom, font_off)

    map_off = rom_offset(palette_ptr)
    map_raw = struct.unpack_from("<240H", rom, map_off)

    font_pal = _gba555_to_srgb(font_raw)
    map_pal = _gba555_to_srgb(map_raw)
    return font_pal + map_pal


def decompress_tileset(rom: bytes, ptr: int) -> bytes:
    off = rom_offset(ptr)
    return lz77_decompress(rom[off:])


def decode_8bpp_tile(tileset: bytes, tile_idx: int) -> list[list[int]]:
    start = tile_idx * TILE_BYTES_8BPP
    tile = tileset[start:start + TILE_BYTES_8BPP]
    pixels = []
    for row in range(TILE_SIZE):
        pixels.append(list(tile[row * TILE_SIZE:(row + 1) * TILE_SIZE]))
    return pixels


def render_map(tileset: bytes, tilemap: list[list[int]],
               palette: list[tuple[int, int, int]]) -> Image.Image:
    """Render a 256×256 image from 8bpp tileset + tilemap + 256-color palette."""
    img_w = TILEMAP_W * TILE_SIZE
    img_h = TILEMAP_H * TILE_SIZE
    img = Image.new("RGB", (img_w, img_h))
    for ty in range(TILEMAP_H):
        for tx in range(TILEMAP_W):
            entry = tilemap[ty][tx]
            tile_idx = entry & 0x3FF
            hflip = bool(entry & 0x400)
            vflip = bool(entry & 0x800)

            if tile_idx == 0:
                continue

            tile_pixels = decode_8bpp_tile(tileset, tile_idx)

            for py in range(TILE_SIZE):
                for px in range(TILE_SIZE):
                    sx = px if not hflip else (TILE_SIZE - 1 - px)
                    sy = py if not vflip else (TILE_SIZE - 1 - py)
                    pix_val = tile_pixels[sy][sx]
                    if pix_val < len(palette):
                        img.putpixel((tx * TILE_SIZE + px, ty * TILE_SIZE + py),
                                     palette[pix_val])
    return img


def main() -> None:
    if not ROM_PATH.exists():
        print(f"error: {ROM_PATH} not found")
        sys.exit(1)

    rom = ROM_PATH.read_bytes()
    OUT_DIR.mkdir(parents=True, exist_ok=True)

    tileset_ptrs = read_ptr_table(rom, SYM_MAP_TILESETS, MAP_COUNT)
    low_tilemap_ptrs = read_ptr_table(rom, SYM_LOW_LAYER_TILEMAPS, MAP_COUNT)
    high_tilemap_ptrs = read_ptr_table(rom, SYM_HIGH_LAYER_TILEMAPS, MAP_COUNT)
    palette_ptrs = read_ptr_table(rom, SYM_PALETTES, MAP_COUNT)
    cable_car_tilemap = read_tilemap(rom, CABLE_CAR_TILEMAP_ADDR)

    for map_id in range(MAP_COUNT):
        print(f"Rendering map {map_id}...")

        tileset = decompress_tileset(rom, tileset_ptrs[map_id])
        low_tilemap = read_tilemap(rom, low_tilemap_ptrs[map_id])
        high_tilemap = read_tilemap(rom, high_tilemap_ptrs[map_id])
        palette = build_bg_palette(rom, palette_ptrs[map_id])

        ground_img = render_map(tileset, low_tilemap, palette)
        roof_img = render_map(tileset, high_tilemap, palette)

        ground_path = OUT_DIR / f"map_{map_id:02d}_ground.png"
        ground_img.save(ground_path)

        roof_path = OUT_DIR / f"map_{map_id:02d}_roof.png"
        roof_img.save(roof_path)

        roof_nz = sum(1 for y in range(roof_img.height) for x in range(roof_img.width)
                      if roof_img.getpixel((x, y)) != (0, 0, 0))
        print(f"  -> {ground_path.name}, {roof_path.name} (roof: {roof_nz} px)")

        if map_id == CABLE_CAR_MAP_ID:
            cable_img = render_map(tileset, cable_car_tilemap, palette)
            cable_path = OUT_DIR / f"map_{map_id:02d}_cable.png"
            cable_img.save(cable_path)
            print(f"  -> {cable_path.name}")

    print(f"\nDone — {MAP_COUNT} maps rendered to {OUT_DIR}")


if __name__ == "__main__":
    main()
