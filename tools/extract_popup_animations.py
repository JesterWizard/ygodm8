#!/usr/bin/env python3
"""Export overworld full-art popup animation frames to indexed PNGs.

Reads the built ROM (ygodm8.gba) and extracts the resting frame of each
registered summon-animation graphic as a 240x160 RGBA PNG.

Usage:
    python3 tools/extract_popup_animations.py

Output goes to src_custom/assets/popup_animations/.
"""

from __future__ import annotations

import os
import struct
import sys
from pathlib import Path

try:
    from PIL import Image
except ImportError as exc:  # pragma: no cover
    raise SystemExit("extract_popup_animations.py requires Pillow") from exc

ROOT = Path(__file__).resolve().parents[1]
ROM_PATH = ROOT / "ygodm8.gba"
OUT_DIR = ROOT / "src_custom" / "assets" / "popup_animations"

# ---------------------------------------------------------------------------
# GBA helpers
# ---------------------------------------------------------------------------

def read_ptr(rom: bytes, off: int) -> int:
    val = struct.unpack_from("<I", rom, off)[0]
    return val - 0x08000000 if val & 0x08000000 else val


def gba_rgb555_to_rgb888(color: int) -> tuple[int, int, int]:
    r = color & 0x1F
    g = (color >> 5) & 0x1F
    b = (color >> 10) & 0x1F
    return (r << 3, g << 3, b << 3)


def lz77_decompress(data: bytes) -> bytes:
    """GBA LZ77 decompressor (mode 0x10)."""
    if data[0] != 0x10:
        return data
    size = struct.unpack_from("<I", data, 0)[0] >> 8
    dst = bytearray(size)
    src = 4
    dst_off = 0
    while dst_off < size:
        flags = data[src]
        src += 1
        for _ in range(8):
            if dst_off >= size:
                break
            if flags & 0x80:
                info = struct.unpack_from(">H", data, src)[0]
                src += 2
                length = ((info >> 12) & 0xF) + 3
                offset = (info & 0xFFF) + 1
                for _ in range(length):
                    dst[dst_off] = dst[dst_off - offset]
                    dst_off += 1
            else:
                dst[dst_off] = data[src]
                src += 1
                dst_off += 1
            flags <<= 1
    return bytes(dst)


def decode_tile_4bpp(tile_data: bytes) -> list[list[int]]:
    """Decode a single 4bpp 8x8 tile."""
    pixels = [[0] * 8 for _ in range(8)]
    for row in range(8):
        for col in range(0, 8, 2):
            byte = tile_data[row * 4 + col // 2]
            pixels[row][col + 1] = byte & 0x0F
            pixels[row][col] = (byte >> 4) & 0x0F
    return pixels


# ---------------------------------------------------------------------------
# GBA OBJ size lookup  (shape, size) -> (width, height)
# ---------------------------------------------------------------------------

OBJ_SIZES: dict[tuple[int, int], tuple[int, int]] = {
    (0, 0): (8, 8),    (0, 1): (16, 16),  (0, 2): (32, 32),  (0, 3): (64, 64),
    (1, 0): (16, 8),   (1, 1): (32, 8),   (1, 2): (32, 16),  (1, 3): (64, 32),
    (2, 0): (8, 16),   (2, 1): (8, 32),   (2, 2): (16, 32),  (2, 3): (32, 64),
}

# ---------------------------------------------------------------------------
# Coordinate decoders (approximate the vanilla clamping functions)
# ---------------------------------------------------------------------------

def calc_x(unk2: int) -> int:
    temp = unk2
    if temp >= 0x1BF:
        ret = temp & 0x1FF
    elif temp <= 0xF0:
        ret = temp & 0x1FF
    else:
        ret = 0x1C0
    return ret & 0x1FF


def calc_y(unk0: int) -> int:
    temp = unk0 & 0xFF
    if temp >= 192:
        ret = temp & 0xFF
    elif temp <= 160:
        ret = temp & 0xFF
    else:
        ret = 192
    return ret


# ---------------------------------------------------------------------------
# Reconstruct charblock 5 exactly as sub_804FA28 does
# ---------------------------------------------------------------------------

def reconstruct_cbb5(src: bytes) -> bytes:
    """Reconstruct the 16KB OBJ charblock 5 from decompressed LZ77 data.

    Vanilla ``sub_804FA28`` copies the 14336 bytes of popup tile data into
    ``gBgVram.cbb5`` with a fixed interleaved stride so that the hardware
    2-D tile map (32 tiles wide) lines up with the OAM frame data.
    """
    cbb5 = bytearray(0x4000)  # 16 KB = one charblock
    src_off = 0
    # Loop 1 – 16 chunks to even 0x400 offsets
    for i in range(16):
        dest_off = i * 0x400
        cbb5[dest_off : dest_off + 512] = src[src_off : src_off + 512]
        src_off += 512
    # Loop 2 – 12 chunks to odd 0x400 offsets (starting at 0x200)
    src_off = 16 * 512  # 0x2000
    for i in range(12):
        dest_off = 0x200 + i * 0x400
        cbb5[dest_off : dest_off + 512] = src[src_off : src_off + 512]
        src_off += 512
    return bytes(cbb5)


# ---------------------------------------------------------------------------
# Extraction core
# ---------------------------------------------------------------------------

def extract_graphic(rom: bytes, gid: int, effect_type: int) -> Image.Image:
    tile_ptr = read_ptr(rom, 0x0FC4440 + gid * 4)
    pal_ptr = read_ptr(rom, 0x0FC452C + gid * 4)
    frame_ptr = read_ptr(rom, 0x0FC4618 + gid * 4)

    raw_tiles = lz77_decompress(rom[tile_ptr:])
    tile_data = reconstruct_cbb5(raw_tiles)

    # 80 palette entries = 5 OBJ palette banks (loaded at bank 7)
    palette: list[tuple[int, int, int]] = []
    for i in range(80):
        color = struct.unpack_from("<H", rom, pal_ptr + i * 2)[0]
        palette.append(gba_rgb555_to_rgb888(color))

    # ---- pick the best (fullest) frame ----------------------------------
    if effect_type == 3:
        best_oam_ptr = 0
        best_num = 0
        for j in range(20):
            ptr = read_ptr(rom, frame_ptr + j * 4)
            if ptr == 0:
                break
            num = rom[ptr + 1]
            oam = read_ptr(rom, ptr + 4)
            if num > best_num:
                best_num = num
                best_oam_ptr = oam
    else:
        group_ptr = read_ptr(rom, frame_ptr)
        best_oam_ptr = 0
        best_num = 0
        for j in range(50):
            dur = rom[group_ptr + j * 8]
            num = rom[group_ptr + j * 8 + 1]
            if dur == 0:
                break
            oam = read_ptr(rom, group_ptr + j * 8 + 4)
            if num > best_num:
                best_num = num
                best_oam_ptr = oam

    # ---- render ----------------------------------------------------------
    canvas = Image.new("RGBA", (240, 160), (0, 0, 0, 0))
    pix = canvas.load()

    for i in range(best_num):
        base = best_oam_ptr + i * 8
        attr0 = struct.unpack_from("<H", rom, base)[0]
        attr1 = struct.unpack_from("<H", rom, base + 2)[0]
        attr2 = struct.unpack_from("<H", rom, base + 4)[0]

        y = calc_y(attr0)
        x = calc_x(attr1)

        shape = (attr0 >> 14) & 3
        size = (attr1 >> 14) & 3
        w, h = OBJ_SIZES.get((shape, size), (8, 8))

        hardware_tile = attr2 & 0x3FF
        pal_bank = (attr2 >> 12) & 0xF
        local_tile = hardware_tile - 512  # charblock 5 base

        tiles_w = w // 8
        tiles_h = h // 8
        for ty in range(tiles_h):
            for tx in range(tiles_w):
                # Hardware uses 2-D mapping: 32 tiles per row
                tidx = local_tile + ty * 32 + tx
                if tidx < 0 or tidx * 32 >= len(tile_data):
                    continue
                tile_bytes = tile_data[tidx * 32 : (tidx + 1) * 32]
                tile_px = decode_tile_4bpp(tile_bytes)
                for py in range(8):
                    for pxx in range(8):
                        pixel = tile_px[py][pxx]
                        if pixel == 0:
                            continue
                        pal_idx = (pal_bank - 7) * 16 + pixel
                        if pal_idx < 0 or pal_idx >= len(palette):
                            continue
                        color = palette[pal_idx]
                        cx = x + tx * 8 + pxx
                        cy = y + ty * 8 + py
                        if 0 <= cx < 240 and 0 <= cy < 160:
                            pix[cx, cy] = color + (255,)

    return canvas


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

GRAPHICS: tuple[tuple[int, str, int], ...] = (
    (7,  "red_eyes_black_dragon",              3),
    (8,  "dark_magician",                      4),
    (9,  "blue_eyes_white_dragon",             3),
    (12, "harpie_lady_sisters",                4),
    (14, "jinzo",                              3),
    (16, "master_of_dragon_soldier",           3),
    (29, "slifer_the_sky_dragon",              4),
    (30, "obelisk_the_tormentor",              4),
    (31, "the_winged_dragon_of_ra",            4),
    (57, "the_winged_dragon_of_ra_phoenix_mode", 4),
)


def main() -> int:
    if not ROM_PATH.is_file():
        raise SystemExit(f"ROM not found: {ROM_PATH}")

    rom = ROM_PATH.read_bytes()
    OUT_DIR.mkdir(parents=True, exist_ok=True)

    for gid, name, etype in GRAPHICS:
        img = extract_graphic(rom, gid, etype)
        out_path = OUT_DIR / f"{name}.png"
        img.save(out_path)
        print(f"wrote {out_path.relative_to(ROOT)}")

    return 0


if __name__ == "__main__":
    sys.exit(main())
