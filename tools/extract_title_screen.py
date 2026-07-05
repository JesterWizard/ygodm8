#!/usr/bin/env python3
"""Export vanilla title screen BG3 art from ROM as a 240x160 indexed PNG."""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
ROM_BASE = 0x08000000
G8E0CD9C = 0x08E0CD9C
G8E0CDA0 = 0x08E0CDA0
G8E0CDA4 = 0x08E0CDA4
TITLE_WIDTH = 30
TITLE_HEIGHT = 20
TILE_BYTES = 64
MAP_ENTRIES = TITLE_WIDTH * TITLE_HEIGHT
DEFAULT_OUT = ROOT / "src_custom" / "assets" / "title_screens" / "title_screen_vanilla_export.png"


def rom_offset(rom_addr: int) -> int:
    return rom_addr - ROM_BASE


def read_rom_u32(rom: bytes, rom_addr: int) -> int:
    return struct.unpack_from("<I", rom, rom_offset(rom_addr))[0]


def lz77_decompress(comp: bytes) -> tuple[bytes, int]:
    if comp[0] != 0x10:
        raise ValueError(f"expected LZ77 header 0x10, got {comp[0]:#x}")

    out_size = comp[1] | (comp[2] << 8) | (comp[3] << 16)
    out = bytearray(out_size)
    src = 4
    dst = 0

    while dst < out_size:
        flags = comp[src]
        src += 1
        for bit in range(8):
            if dst >= out_size:
                break
            if flags & (0x80 >> bit):
                byte1 = comp[src]
                byte2 = comp[src + 1]
                src += 2
                length = (byte1 >> 4) + 3
                disp = (((byte1 & 0x0F) << 8) | byte2) + 1
                for _ in range(length):
                    out[dst] = out[dst - disp]
                    dst += 1
            else:
                out[dst] = comp[src]
                src += 1
                dst += 1

    return bytes(out), src


def bgr555_to_rgb888(word: int) -> tuple[int, int, int]:
    r = (word & 0x1F) << 3
    g = ((word >> 5) & 0x1F) << 3
    b = ((word >> 10) & 0x1F) << 3
    return r | (r >> 5), g | (g >> 5), b | (b >> 5)


def load_language_assets(rom: bytes, language: int) -> tuple[bytes, bytes, list[int]]:
    if not 0 <= language <= 4:
        raise ValueError(f"language must be 0-4, got {language}")

    tiles_ptr = read_rom_u32(rom, G8E0CD9C + language * 4)
    palette_ptr = read_rom_u32(rom, G8E0CDA0 + language * 4)
    tilemap_ptr = read_rom_u32(rom, G8E0CDA4 + language * 4)

    tiles_off = rom_offset(tiles_ptr)
    raw_tiles, _ = lz77_decompress(rom[tiles_off:])

    palette_off = rom_offset(palette_ptr)
    palette_blob = rom[palette_off : palette_off + 512]

    map_off = rom_offset(tilemap_ptr)
    entries = struct.unpack_from(f"<{MAP_ENTRIES}H", rom, map_off)
    tile_ids = [entry & 0x3FF for entry in entries]

    max_tile = max(tile_ids)
    needed = (max_tile + 1) * TILE_BYTES
    if needed > len(raw_tiles):
        raise SystemExit(
            f"tilemap references tile {max_tile}, but decompressed tileset is "
            f"{len(raw_tiles)} bytes ({len(raw_tiles) // TILE_BYTES} tiles)"
        )

    return raw_tiles, palette_blob, tile_ids


def render_indexed_png(raw_tiles: bytes, palette_blob: bytes, tile_ids: list[int]) -> Image.Image:
    palette_rgb: list[int] = []
    for index in range(256):
        word = struct.unpack_from("<H", palette_blob, index * 2)[0]
        palette_rgb.extend(bgr555_to_rgb888(word))

    image = Image.new("P", (TITLE_WIDTH * 8, TITLE_HEIGHT * 8))
    image.putpalette(palette_rgb + [0] * (768 - len(palette_rgb)))

    pixels: list[int] = []
    for row in range(TITLE_HEIGHT):
        for py in range(8):
            for col in range(TITLE_WIDTH):
                tile_id = tile_ids[row * TITLE_WIDTH + col]
                tile = raw_tiles[tile_id * TILE_BYTES : tile_id * TILE_BYTES + TILE_BYTES]
                pixels.extend(tile[py * 8 : py * 8 + 8])

    image.putdata(pixels)
    return image


def extract_title_screen(rom: bytes, language: int = 0) -> Image.Image:
    raw_tiles, palette_blob, tile_ids = load_language_assets(rom, language)
    return render_indexed_png(raw_tiles, palette_blob, tile_ids)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--rom",
        type=Path,
        default=None,
        help="ROM to read (default: ygodm8.gba, else baserom.gba)",
    )
    parser.add_argument(
        "--language",
        type=int,
        default=0,
        help="Language index 0-4 (default: 0 English)",
    )
    parser.add_argument(
        "--out",
        type=Path,
        default=DEFAULT_OUT,
        help=f"Output PNG path (default: {DEFAULT_OUT.relative_to(ROOT)})",
    )
    args = parser.parse_args()

    rom_path = args.rom
    if rom_path is None:
        for candidate in (ROOT / "ygodm8.gba", ROOT / "baserom.gba"):
            if candidate.is_file():
                rom_path = candidate
                break
    if rom_path is None or not rom_path.is_file():
        raise SystemExit("missing ROM: pass --rom or build ygodm8.gba / baserom.gba")

    sys.path.insert(0, str(ROOT / "tools"))
    from validate_title_screen import validate_title_png  # noqa: E402

    image = extract_title_screen(rom_path.read_bytes(), args.language)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    image.save(args.out)

    errors = validate_title_png(args.out)
    if errors:
        for message in errors:
            print(message, file=sys.stderr)
        return 1

    print(f"extract_title_screen: ok ({args.out.relative_to(ROOT)}, language {args.language})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
