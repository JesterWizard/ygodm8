#!/usr/bin/env python3

import pathlib
import sys

from PIL import Image

from cg_remap import build_cg_index_remap, remap_cg_bytes

CG_WIDTH = 240
CG_HEIGHT = 160
CG_SIZE = CG_WIDTH * CG_HEIGHT


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


def offset_cg_png_bytes(png_path: pathlib.Path, data: bytes) -> bytes:
    if len(data) != CG_SIZE:
        raise ValueError(
            f"expected a {CG_WIDTH}x{CG_HEIGHT} 8bpp CG ({CG_SIZE} bytes), got {len(data)} bytes"
        )

    image = Image.open(png_path)
    if image.size != (CG_WIDTH, CG_HEIGHT):
        raise ValueError(
            f"{png_path.name}: expected {CG_WIDTH}x{CG_HEIGHT}, got {image.size[0]}x{image.size[1]}"
        )

    palette = image.getpalette()
    if palette is None:
        raise ValueError(f"{png_path.name}: missing palette")

    pixels = list(image.get_flattened_data())
    tiled = linear_to_tiled_8bpp(pixels)
    remap = build_cg_index_remap(pixels)
    return remap_cg_bytes(tiled, remap)


def main() -> int:
    if len(sys.argv) != 4:
        print("usage: offset_cg_8bpp.py INPUT.png INPUT.8bpp OUTPUT.8bpp", file=sys.stderr)
        return 2

    png_path = pathlib.Path(sys.argv[1])
    src_path = pathlib.Path(sys.argv[2])
    dst_path = pathlib.Path(sys.argv[3])
    dst_path.write_bytes(offset_cg_png_bytes(png_path, src_path.read_bytes()))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
