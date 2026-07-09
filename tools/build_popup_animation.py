#!/usr/bin/env python3
"""Build a GBA summon-popup animation from a 240x160 indexed PNG.

Generates C include files with LZ77 tile data, palette, and OAM metadata
that get compiled into the ROM.  No post-build binary patching.

Usage:
    python3 tools/build_popup_animation.py src_custom/assets/popup_animations/yubel.png yubel

Output:
    src_custom/generated/popup_yubel_data.inc
"""

from __future__ import annotations

import os
import struct
import sys
from pathlib import Path
from typing import NamedTuple

try:
    import numpy as np
    from PIL import Image
    from sklearn.cluster import KMeans
except ImportError as exc:  # pragma: no cover
    raise SystemExit(
        "build_popup_animation.py requires Pillow, numpy and scikit-learn"
    ) from exc

ROOT = Path(__file__).resolve().parents[1]
GENERATED_DIR = ROOT / "src_custom" / "generated"

# ---------------------------------------------------------------------------
# Constants
# ---------------------------------------------------------------------------

SCREEN_W = 240
SCREEN_H = 160
TILE_SIZE = 8
MAX_TILES = 512          # 32KB OBJ VRAM / 64 bytes per 8bpp tile
MAX_SPRITES = 128
MAX_PALETTE_BANKS = 1    # 8bpp uses single 256-color palette
COLORS_PER_BANK = 256    # 8bpp mode
TRANSPARENT_IDX = 0

OBJ_SIZES: dict[tuple[int, int], tuple[int, int]] = {
    (0, 0): (8, 8),    (0, 1): (16, 16),  (0, 2): (32, 32),
    (1, 0): (16, 8),   (1, 1): (32, 8),   (1, 2): (32, 16),
    (2, 0): (8, 16),   (2, 1): (8, 32),   (2, 2): (16, 32),
}

REVERSE_OBJ_SHAPES: dict[tuple[int, int], tuple[int, int]] = {
    (w, h): (shape, size)
    for (shape, size), (w, h) in OBJ_SIZES.items()
}

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def rgb_to_rgb555(r: int, g: int, b: int) -> int:
    return ((b >> 3) << 10) | ((g >> 3) << 5) | (r >> 3)


def color_dist(c1: tuple[int, int, int], c2: tuple[int, int, int]) -> int:
    return sum((a - b) ** 2 for a, b in zip(c1, c2))


def find_nearest_palette_index(
    rgb: tuple[int, int, int], palette: list[tuple[int, int, int]]
) -> int:
    best = 0
    best_err = color_dist(rgb, palette[0])
    for i in range(1, len(palette)):
        err = color_dist(rgb, palette[i])
        if err < best_err:
            best_err = err
            best = i
    return best


# ---------------------------------------------------------------------------
# LZ77 compressor (mode 0x10)  — simple greedy implementation
# ---------------------------------------------------------------------------

def lz77_compress(data: bytes) -> bytes:
    """GBA LZ77 mode-0x10 compressor (simple greedy)."""
    dst = bytearray()
    dst.append(0x10)
    dst.extend(struct.pack("<I", len(data))[:3])
    src = 0
    while src < len(data):
        flags = 0
        block = bytearray()
        for i in range(8):
            if src >= len(data):
                block.append(0)
                continue
            best_len = 0
            best_off = 0
            search_start = max(0, src - 4096)
            for off in range(search_start, src):
                length = 0
                while (
                    length < 18
                    and src + length < len(data)
                    and data[off + length] == data[src + length]
                ):
                    length += 1
                if length > best_len:
                    best_len = length
                    best_off = src - off
            if best_len >= 3:
                flags |= 1 << (7 - i)
                info = ((best_len - 3) << 12) | ((best_off - 1) & 0xFFF)
                block.extend(struct.pack(">H", info))
                src += best_len
            else:
                block.append(data[src])
                src += 1
        dst.append(flags)
        dst.extend(block)
    return bytes(dst)


# ---------------------------------------------------------------------------
# Image processing
# ---------------------------------------------------------------------------

def load_and_quantize(png_path: Path) -> tuple[np.ndarray, list[list[tuple[int, int, int]]], np.ndarray]:
    """Load PNG, make green transparent, quantize to 5 palette banks."""
    img = Image.open(png_path).convert("P")
    if img.size != (SCREEN_W, SCREEN_H):
        raise SystemExit(f"Expected 240x160, got {img.size}")
    pixels = np.array(img)
    pal = np.array(img.getpalette(), dtype=np.uint8).reshape(-1, 3)
    num_pal = len(pal)

    # Detect green and near-black background indices
    bg_indices: set[int] = set()
    for i in range(num_pal):
        r, g, b = pal[i]
        if g > 200 and r < 50 and b < 50:
            bg_indices.add(i)
        if r < 20 and g < 20 and b < 20:
            bg_indices.add(i)
    print(f"  Transparent bg indices: {bg_indices}")

    # Collect non-background pixels
    mask = np.ones_like(pixels, dtype=bool)
    for gi in bg_indices:
        mask &= pixels != gi
    non_green_px = pixels[mask]
    if non_green_px.size == 0:
        raise SystemExit("Image is entirely transparent")

    unique_indices = np.unique(non_green_px)
    unique_rgb = pal[unique_indices]
    print(f"  Unique non-transparent colors: {len(unique_rgb)}")

    # Reduce to 75 colors via k-means
    target = MAX_PALETTE_BANKS * (COLORS_PER_BANK - 1)
    if len(unique_rgb) > target:
        kmeans = KMeans(n_clusters=target, random_state=42, n_init=10)
        kmeans.fit(unique_rgb)
        centroids = kmeans.cluster_centers_.astype(np.uint8)
    else:
        centroids = unique_rgb

    # Group 75 centroids into 5 groups of 15
    group_kmeans = KMeans(n_clusters=MAX_PALETTE_BANKS, random_state=42, n_init=10)
    group_kmeans.fit(centroids)
    group_labels = group_kmeans.labels_

    # Build 5 palettes (16 colors each, index 0 = black/transparent)
    palettes: list[list[tuple[int, int, int]]] = []
    for bank in range(MAX_PALETTE_BANKS):
        bank_centroids = centroids[group_labels == bank]
        n = len(bank_centroids)
        if n > COLORS_PER_BANK - 1:
            sub = KMeans(n_clusters=COLORS_PER_BANK - 1, random_state=42, n_init=10)
            sub.fit(bank_centroids)
            bank_colors = sub.cluster_centers_.astype(np.uint8)
        else:
            bank_colors = bank_centroids

        # Pad to 15 colors
        pad = COLORS_PER_BANK - 1 - len(bank_colors)
        if pad > 0:
            bank_colors = np.vstack([bank_colors, np.zeros((pad, 3), dtype=np.uint8)])

        palette = [(0, 0, 0)]  # index 0 = transparent black
        for c in bank_colors:
            palette.append(tuple(int(v) for v in c))
        palettes.append(palette)

    # Assign each 8x8 tile to a bank
    h_tiles = SCREEN_H // TILE_SIZE
    w_tiles = SCREEN_W // TILE_SIZE
    tile_banks = np.full((h_tiles, w_tiles), -1, dtype=np.int32)
    for ty in range(h_tiles):
        for tx in range(w_tiles):
            tile = pixels[ty * TILE_SIZE : (ty + 1) * TILE_SIZE,
                          tx * TILE_SIZE : (tx + 1) * TILE_SIZE]
            tile_mask = np.ones_like(tile, dtype=bool)
            for gi in bg_indices:
                tile_mask &= tile != gi
            if not np.any(tile_mask):
                continue
            tile_rgb = pal[tile[tile_mask]]

            best_bank = 0
            best_err = float("inf")
            for bank, palette in enumerate(palettes):
                err = sum(
                    color_dist(tuple(int(v) for v in rgb), palette[find_nearest_palette_index(tuple(int(v) for v in rgb), palette)])
                    for rgb in tile_rgb
                )
                if err < best_err:
                    best_err = err
                    best_bank = bank
            tile_banks[ty, tx] = best_bank

    # Remap pixels
    new_pixels = np.zeros_like(pixels)
    for ty in range(h_tiles):
        for tx in range(w_tiles):
            bank = tile_banks[ty, tx]
            if bank < 0:
                continue
            palette = palettes[bank]
            for y in range(ty * TILE_SIZE, (ty + 1) * TILE_SIZE):
                for x in range(tx * TILE_SIZE, (tx + 1) * TILE_SIZE):
                    idx = pixels[y, x]
                    if idx in bg_indices:
                        new_pixels[y, x] = 0
                    else:
                        rgb = tuple(int(v) for v in pal[idx])
                        new_pixels[y, x] = find_nearest_palette_index(rgb, palette)

    return new_pixels, palettes, tile_banks


# ---------------------------------------------------------------------------
# Sprite packing
# ---------------------------------------------------------------------------

class Sprite(NamedTuple):
    x: int
    y: int
    w: int
    h: int
    shape: int
    size: int
    bank: int
    tiles: list[int]


def pack_sprites(tile_banks: np.ndarray) -> list[Sprite]:
    """Pack non-transparent tiles into the fewest valid GBA OBJ sprites."""
    h_tiles = SCREEN_H // TILE_SIZE
    w_tiles = SCREEN_W // TILE_SIZE
    used = np.zeros((h_tiles, w_tiles), dtype=bool)
    sprites: list[Sprite] = []

    size_order = sorted(OBJ_SIZES.items(), key=lambda kv: kv[1][0] * kv[1][1], reverse=True)

    for ty in range(h_tiles):
        for tx in range(w_tiles):
            if used[ty, tx] or tile_banks[ty, tx] < 0:
                continue
            bank = int(tile_banks[ty, tx])

            best_w, best_h = TILE_SIZE, TILE_SIZE
            best_shape, best_size = (0, 0)
            for (shape, size), (sw, sh) in size_order:
                tw = sw // TILE_SIZE
                th = sh // TILE_SIZE
                if tx + tw > w_tiles or ty + th > h_tiles:
                    continue
                ok = True
                for dy in range(th):
                    for dx in range(tw):
                        if used[ty + dy, tx + dx] or tile_banks[ty + dy, tx + dx] != bank:
                            ok = False
                            break
                    if not ok:
                        break
                if ok:
                    best_w, best_h = sw, sh
                    best_shape, best_size = shape, size
                    break

            tw = best_w // TILE_SIZE
            th = best_h // TILE_SIZE
            for dy in range(th):
                for dx in range(tw):
                    used[ty + dy, tx + dx] = True

            sprites.append(
                Sprite(
                    x=tx * TILE_SIZE,
                    y=ty * TILE_SIZE,
                    w=best_w,
                    h=best_h,
                    shape=best_shape,
                    size=best_size,
                    bank=bank,
                    tiles=[],
                )
            )

    return sprites


# ---------------------------------------------------------------------------
# Tile encoding
# ---------------------------------------------------------------------------

def encode_8bpp_tile(pixels: np.ndarray) -> bytes:
    """Encode an 8x8 tile to 64 bytes of 8bpp data."""
    out = bytearray(64)
    for row in range(8):
        for col in range(8):
            out[row * 8 + col] = int(pixels[row, col]) & 0xFF
    return bytes(out)


def build_cbb5_tiles(
    new_pixels: np.ndarray,
    tile_banks: np.ndarray,
    sprites: list[Sprite],
    palettes: list[list[tuple[int, int, int]]],
) -> tuple[bytes, list[Sprite]]:
    """Build the 32KB OBJ VRAM tile blob and assign tile indices to sprites."""
    h_tiles = SCREEN_H // TILE_SIZE
    w_tiles = SCREEN_W // TILE_SIZE

    # OBJ VRAM is 32KB (charblocks 4+5), 8bpp tiles = 64 bytes each
    obj_vram = bytearray(0x8000)
    occupied = np.zeros(MAX_TILES, dtype=bool)  # 1D mapping: 512 tiles linear (8bpp)

    total_tile_area = sum((spr.w // TILE_SIZE) * (spr.h // TILE_SIZE) for spr in sprites)
    print(f"  Total tile area: {total_tile_area} tiles (max {MAX_TILES})")

    # Sort sprites by area descending for better bin packing
    sprites = sorted(sprites, key=lambda s: (s.w // TILE_SIZE) * (s.h // TILE_SIZE), reverse=True)

    def find_fit_linear(num_tiles: int) -> int:
        # Find a contiguous run of num_tiles free slots
        for start in range(MAX_TILES - num_tiles + 1):
            if not np.any(occupied[start : start + num_tiles]):
                return start
        raise SystemExit(f"Cannot fit {num_tiles} contiguous tiles in OBJ VRAM (1D mapping)")

    updated_sprites: list[Sprite] = []
    for spr in sprites:
        num_tiles = (spr.w // TILE_SIZE) * (spr.h // TILE_SIZE)
        start_idx = find_fit_linear(num_tiles)
        occupied[start_idx : start_idx + num_tiles] = True

        tiles: list[int] = []
        tile_offset = 0
        for ty in range(spr.h // TILE_SIZE):
            for tx in range(spr.w // TILE_SIZE):
                abs_ty = spr.y // TILE_SIZE + ty
                abs_tx = spr.x // TILE_SIZE + tx
                tile_pixels = new_pixels[
                    abs_ty * TILE_SIZE : (abs_ty + 1) * TILE_SIZE,
                    abs_tx * TILE_SIZE : (abs_tx + 1) * TILE_SIZE,
                ]
                tile_bytes = encode_8bpp_tile(tile_pixels)
                idx = start_idx + tile_offset
                obj_vram[idx * 64 : (idx + 1) * 64] = tile_bytes
                tiles.append(idx)
                tile_offset += 1

        updated_sprites.append(spr._replace(tiles=tiles))

    used = int(np.sum(occupied))
    print(f"  Used {used} tiles ({used * 64} bytes)")
    return bytes(obj_vram), updated_sprites


# ---------------------------------------------------------------------------
# C code generation
# ---------------------------------------------------------------------------

def generate_c_data(
    name: str,
    cbb5: bytes,
    palettes: list[list[tuple[int, int, int]]],
    sprites: list[Sprite],
    out_path: Path,
) -> None:
    """Write C include file with LZ77 tiles, palette, and OAM data."""
    lz_tiles = lz77_compress(cbb5)
    print(f"  LZ77: {len(cbb5)} -> {len(lz_tiles)} bytes")

    # Build palette blob (256 colors for 8bpp)
    pal_entries = []
    for bank in range(MAX_PALETTE_BANKS):
        for i in range(COLORS_PER_BANK):
            r, g, b = palettes[bank][i]
            pal_entries.append(rgb_to_rgb555(r, g, b))

    # Build OAM blob
    oam_entries = []
    for spr in sprites:
        attr0 = (spr.y & 0xFF) | (1 << 13) | ((spr.shape & 3) << 14)  # bit 13 = 8bpp
        attr1 = (spr.x & 0x1FF) | ((spr.size & 3) << 14)
        # 8bpp ignores palette bank bits; tile index is direct
        attr2 = spr.tiles[0]
        oam_entries.append(attr0)
        oam_entries.append(attr1)
        oam_entries.append(attr2)
        oam_entries.append(0)  # padding

    # Split tiles into cbb4 (first 16KB) and cbb5 (second 16KB) halves
    cbb4_half = cbb5[:0x4000]
    cbb5_half = cbb5[0x4000:]
    lz_cbb4 = lz77_compress(cbb4_half)
    lz_cbb5 = lz77_compress(cbb5_half)
    print(f"  LZ77 cbb4: {len(cbb4_half)} -> {len(lz_cbb4)} bytes")
    print(f"  LZ77 cbb5: {len(cbb5_half)} -> {len(lz_cbb5)} bytes")

    # Write the .inc file
    upper = name.upper()
    lines = [
        f"/* Auto-generated popup animation data for {name} */",
        f"#ifndef GUARD_POPUP_{upper}_DATA",
        f"#define GUARD_POPUP_{upper}_DATA",
        "",
        '#include "configs/runtime.h"',
        "",
        f"#define POPUP_{upper}_NUM_SPRITES {len(sprites)}",
        f"#define POPUP_{upper}_DURATION 50",
        "",
        f"static const unsigned char gPopup{upper.title().replace('_', '')}TilesCbb4[] APPEND_RODATA = {{",
    ]
    for i in range(0, len(lz_cbb4), 12):
        row = ", ".join(f"0x{b:02X}" for b in lz_cbb4[i : i + 12])
        lines.append(f"    {row},")
    lines.append("};")
    lines.append("")

    lines.append(f"static const unsigned char gPopup{upper.title().replace('_', '')}TilesCbb5[] APPEND_RODATA = {{")
    for i in range(0, len(lz_cbb5), 12):
        row = ", ".join(f"0x{b:02X}" for b in lz_cbb5[i : i + 12])
        lines.append(f"    {row},")
    lines.append("};")
    lines.append("")

    lines.append(f"static const unsigned short gPopup{upper.title().replace('_', '')}Palette[] APPEND_RODATA = {{")
    for i in range(0, len(pal_entries), 8):
        row = ", ".join(f"0x{w:04X}" for w in pal_entries[i : i + 8])
        lines.append(f"    {row},")
    lines.append("};")
    lines.append("")

    lines.append(f"static const unsigned short gPopup{upper.title().replace('_', '')}Oam[] APPEND_RODATA = {{")
    for i in range(0, len(oam_entries), 8):
        row = ", ".join(f"0x{w:04X}" for w in oam_entries[i : i + 8])
        lines.append(f"    {row},")
    lines.append("};")
    lines.append("")
    lines.append(f"#endif // GUARD_POPUP_{upper}_DATA")
    lines.append("")

    out_path.write_text("\n".join(lines))
    print(f"  Wrote {out_path.relative_to(ROOT)}")


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main() -> int:
    if len(sys.argv) != 3:
        print("usage: build_popup_animation.py <240x160.png> <name>", file=sys.stderr)
        return 2

    png_path = Path(sys.argv[1])
    name = sys.argv[2]

    print(f"=== Building popup animation: {name} ===")
    print(f"  Input: {png_path}")

    print("=== 1. Load and quantize ===")
    new_pixels, palettes, tile_banks = load_and_quantize(png_path)

    print("=== 2. Pack sprites ===")
    non_empty_tiles = np.sum(tile_banks >= 0)
    print(f"  Non-empty tiles: {non_empty_tiles}")
    sprites = pack_sprites(tile_banks)
    print(f"  Sprites: {len(sprites)} (max {MAX_SPRITES})")
    size_counts = {}
    for s in sprites:
        k = (s.w, s.h)
        size_counts[k] = size_counts.get(k, 0) + 1
    print(f"  Sprite sizes: {size_counts}")
    if len(sprites) > MAX_SPRITES:
        raise SystemExit(f"Too many sprites: {len(sprites)} (max {MAX_SPRITES})")

    print("=== 3. Build OBJ VRAM tiles ===")
    obj_vram, sprites = build_cbb5_tiles(new_pixels, tile_banks, sprites, palettes)

    print("=== 4. Generate C data ===")
    GENERATED_DIR.mkdir(parents=True, exist_ok=True)
    out_path = GENERATED_DIR / f"popup_{name}_data.inc"
    generate_c_data(name, obj_vram, palettes, sprites, out_path)

    print(f"\nDone. Include in summon_animations.c:")
    print(f'  #include "generated/popup_{name}_data.inc"')
    print(f"  case YUBEL: return POPUP_ANIM_YUBEL;")
    return 0


if __name__ == "__main__":
    sys.exit(main())
