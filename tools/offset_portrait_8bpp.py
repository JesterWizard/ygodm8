#!/usr/bin/env python3

import pathlib
import sys

PORTRAIT_SIZE = 64 * 64
PALETTE_OFFSET = 0xC0
MAX_PORTRAIT_COLORS = 64


def offset_portrait_bytes(data: bytes) -> bytes:
    if len(data) != PORTRAIT_SIZE:
        raise ValueError(
            f"expected a 64x64 8bpp portrait ({PORTRAIT_SIZE} bytes), got {len(data)} bytes"
        )

    max_index = max(data) if data else 0
    if max_index >= MAX_PORTRAIT_COLORS:
        raise ValueError(
            f"portrait uses palette index {max_index}; max supported index is 63"
        )

    # OBJ index 0 is transparent. Palette data is loaded at 0xC0..0xFF, so source
    # indices 1..63 map to tile bytes 0xC1..0xFF (vanilla never uses 0xC0 in tiles).
    return bytes((pixel + PALETTE_OFFSET if pixel else 0) for pixel in data)


def main() -> int:
    if len(sys.argv) != 3:
        print("usage: offset_portrait_8bpp.py INPUT.8bpp OUTPUT.8bpp", file=sys.stderr)
        return 2

    src_path = pathlib.Path(sys.argv[1])
    dst_path = pathlib.Path(sys.argv[2])
    dst_path.write_bytes(offset_portrait_bytes(src_path.read_bytes()))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
