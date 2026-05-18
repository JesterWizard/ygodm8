#!/usr/bin/env python3

import pathlib
import struct
import sys
import zlib


ROOT = pathlib.Path(__file__).resolve().parent.parent


def encode_vlq(value: int) -> bytes:
    if value < 0:
        raise ValueError("UPS offsets must be non-negative")

    out = bytearray()
    while True:
        chunk = value & 0x7F
        value >>= 7
        if value == 0:
            out.append(0x80 | chunk)
            return bytes(out)
        out.append(chunk)
        value -= 1


def iter_changes(source: bytes, target: bytes):
    limit = max(len(source), len(target))
    index = 0

    while index < limit:
        source_byte = source[index] if index < len(source) else 0
        target_byte = target[index] if index < len(target) else 0
        if source_byte == target_byte:
            index += 1
            continue

        start = index
        block = bytearray()
        while index < limit:
            source_byte = source[index] if index < len(source) else 0
            target_byte = target[index] if index < len(target) else 0
            if source_byte == target_byte:
                break
            block.append(source_byte ^ target_byte)
            index += 1

        yield start, bytes(block)


def build_patch(source: bytes, target: bytes) -> bytes:
    patch = bytearray()
    patch.extend(b"UPS1")
    patch.extend(encode_vlq(len(source)))
    patch.extend(encode_vlq(len(target)))

    cursor = 0
    for start, block in iter_changes(source, target):
        patch.extend(encode_vlq(start - cursor))
        patch.extend(block)
        patch.append(0x00)
        cursor = start + len(block) + 1

    patch.extend(struct.pack("<I", zlib.crc32(source) & 0xFFFFFFFF))
    patch.extend(struct.pack("<I", zlib.crc32(target) & 0xFFFFFFFF))
    patch.extend(struct.pack("<I", zlib.crc32(patch) & 0xFFFFFFFF))
    return bytes(patch)


def main() -> int:
    if len(sys.argv) != 4:
        print("usage: make_ups.py <source> <target> <output>", file=sys.stderr)
        return 1

    source_path = ROOT / sys.argv[1]
    target_path = ROOT / sys.argv[2]
    output_path = ROOT / sys.argv[3]

    source = source_path.read_bytes()
    target = target_path.read_bytes()
    output_path.write_bytes(build_patch(source, target))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
