#!/usr/bin/env python3

import pathlib
import sys


TILE_SIZE = 32
SOURCE_TILE_WIDTH = 16
SOURCE_TILE_HEIGHT = 8
HALF_TILE_WIDTH = 8
OBJ_TILE_ROW_STRIDE = 0x400
RIGHT_HALF_ROW_OFFSET = 0x100


def main() -> int:
    if len(sys.argv) != 3:
        print("usage: repack_128x64_obj.py INPUT.4bpp OUTPUT.4bpp", file=sys.stderr)
        return 2

    src_path = pathlib.Path(sys.argv[1])
    dst_path = pathlib.Path(sys.argv[2])
    data = src_path.read_bytes()

    expected_size = SOURCE_TILE_WIDTH * SOURCE_TILE_HEIGHT * TILE_SIZE
    if len(data) != expected_size:
        print(f"expected {expected_size} bytes, got {len(data)} from {src_path}", file=sys.stderr)
        return 1

    out = bytearray(OBJ_TILE_ROW_STRIDE * (SOURCE_TILE_HEIGHT - 1) + RIGHT_HALF_ROW_OFFSET * 2)
    for y in range(SOURCE_TILE_HEIGHT):
        row_base = y * OBJ_TILE_ROW_STRIDE
        for x in range(HALF_TILE_WIDTH):
            left_src = (y * SOURCE_TILE_WIDTH + x) * TILE_SIZE
            right_src = (y * SOURCE_TILE_WIDTH + HALF_TILE_WIDTH + x) * TILE_SIZE
            left_dst = row_base + x * TILE_SIZE
            right_dst = row_base + RIGHT_HALF_ROW_OFFSET + x * TILE_SIZE
            out[left_dst:left_dst + TILE_SIZE] = data[left_src:left_src + TILE_SIZE]
            out[right_dst:right_dst + TILE_SIZE] = data[right_src:right_src + TILE_SIZE]

    dst_path.write_bytes(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
