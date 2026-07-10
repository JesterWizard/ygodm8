#!/usr/bin/env python3
"""Build a GBA summon-popup animation from a 240x160 indexed PNG.

Generates a C include file with raw 8bpp tiles (38400 bytes) and a 256-entry
BG palette (512 bytes).  The data is compiled directly into the ROM and
DMA'd to hardware charblock 0 during the popup animation -- no LZ77,
no VRAM mirror save/restore needed.

Usage:
    python3 tools/build_popup_animation.py path/to/input.png name

Output:
    src_custom/generated/popup_{name}_data.inc
"""

from __future__ import annotations

import os
import struct
import sys
from pathlib import Path

try:
    from PIL import Image
except ImportError as exc:
    raise SystemExit(
        "build_popup_animation.py requires Pillow"
    ) from exc

ROOT = Path(__file__).resolve().parents[1]
GENERATED_DIR = ROOT / "src_custom" / "generated"

SCREEN_W = 240
SCREEN_H = 160
TILE_SIZE = 8
TILES_X = SCREEN_W // TILE_SIZE   # 30
TILES_Y = SCREEN_H // TILE_SIZE   # 20
TILE_COUNT = TILES_X * TILES_Y     # 600
TILE_BYTES_8BPP = 64              # 8x8 × 1 byte per pixel
UNCOMPRESSED_SIZE = TILE_COUNT * TILE_BYTES_8BPP  # 38400

DEFAULT_HOLD_FRAMES = 120


def rgb555(r: int, g: int, b: int) -> int:
    return ((b >> 3) << 10) | ((g >> 3) << 5) | (r >> 3)


def build_popup(png_path: Path, name: str, hold_frames: int = DEFAULT_HOLD_FRAMES) -> str:
    im = Image.open(png_path).convert("RGB")
    if im.size != (SCREEN_W, SCREEN_H):
        raise SystemExit(
            f"Input image must be {SCREEN_W}x{SCREEN_H}, got {im.size}"
        )

    # Quantize to 256 colors using PIL's adaptive palette
    pim = im.quantize(colors=256, method=Image.Quantize.MEDIANCUT)
    raw_pal = pim.getpalette()  # flat list [R,G,B, ...], may be shorter than 768
    # Pad to exactly 256 palette entries (black for unused slots)
    full_pal = list(raw_pal) if raw_pal else []
    while len(full_pal) < 768:
        full_pal.extend([0, 0, 0])
    px = pim.load()  # pixel access: px[x, y] → palette index

    # --- palette (256 entries, 2 bytes each = 512) ---
    pal_u16 = []
    for i in range(256):
        r = full_pal[i * 3]
        g = full_pal[i * 3 + 1]
        b = full_pal[i * 3 + 2]
        pal_u16.append(rgb555(r, g, b))

    # --- tiles (600 × 64 bytes = 38400) ---
    tiles = bytearray()
    for ty in range(TILES_Y):
        for tx in range(TILES_X):
            for py in range(TILE_SIZE):
                for px_coord in range(TILE_SIZE):
                    tiles.append(px[tx * TILE_SIZE + px_coord, ty * TILE_SIZE + py])

    assert len(tiles) == UNCOMPRESSED_SIZE

    # --- generate C data ---
    name_upper = name.upper()
    lines = [
        f'#ifndef POPUP_{name_upper}_DATA_INC',
        f'#define POPUP_{name_upper}_DATA_INC',
        '',
        f'#define POPUP_{name_upper}_DURATION {hold_frames}',
        '',
        f'static const u16 gPopup{name.title()}Palette[256] APPEND_ASSET = {{',
    ]

    # Palette byteswapped for little-endian GBA
    for i, c in enumerate(pal_u16):
        sep = "," if i < 255 else ""
        # GBA stores palette in native u16 (little-endian in ROM)
        lines.append(f"    (u16)0x{c:04X}{sep}")
    lines.append("};")
    lines.append("")
    lines.append(f"static const u8 gPopup{name.title()}Tiles[{UNCOMPRESSED_SIZE}] APPEND_ASSET = {{")

    for i in range(0, len(tiles), 16):
        chunk = tiles[i : i + 16]
        hex_vals = ", ".join(f"0x{b:02X}" for b in chunk)
        is_last = (i + 16 >= UNCOMPRESSED_SIZE)
        sep = "," if not is_last else ""
        lines.append(f"    {hex_vals}{sep}")

    lines.append("};")
    lines.append("")
    lines.append(f"#endif // POPUP_{name_upper}_DATA_INC")
    lines.append("")

    return "\n".join(lines) + "\n"


def main() -> None:
    if len(sys.argv) < 3:
        print("Usage: python3 tools/build_popup_animation.py path/to/input.png name [hold_frames]",
              file=sys.stderr)
        sys.exit(1)

    png_path = Path(sys.argv[1])
    if not png_path.exists():
        print(f"Error: {png_path} not found", file=sys.stderr)
        sys.exit(1)

    name = sys.argv[2]
    hold_frames = int(sys.argv[3]) if len(sys.argv) > 3 else DEFAULT_HOLD_FRAMES

    code = build_popup(png_path, name, hold_frames)

    out_name = f"popup_{name}_data.inc"
    out_path = GENERATED_DIR / out_name
    with open(out_path, "w") as f:
        f.write(code)

    print(f"Wrote {out_path} ({UNCOMPRESSED_SIZE + 512} bytes data, {hold_frames} hold frames)")
    print()
    print(f"Next steps:")
    print(f"  1. #include \"generated/{out_name}\"")
    print(f"  2. case YOUR_CARD_ID: return POPUP_ANIM_YOUR_CARD;")


if __name__ == "__main__":
    main()
