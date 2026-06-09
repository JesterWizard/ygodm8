#!/usr/bin/env python3

import pathlib
import struct
import sys
import zlib

ROOT = pathlib.Path(__file__).resolve().parent.parent
UPS_MAGIC = b"UPS1"
UPS_TRAILER_SIZE = 12


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


def decode_vlq(data: bytes, offset: int = 0) -> tuple[int, int]:
    value = 0
    shift = 1
    while offset < len(data):
        byte = data[offset]
        offset += 1
        value += (byte & 0x7F) * shift
        if byte & 0x80:
            return value, offset
        shift <<= 7
        value += shift
    raise ValueError("truncated UPS variable-length quantity")


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
    patch.extend(UPS_MAGIC)
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


def apply_patch(source: bytes, patch: bytes) -> bytes:
    if not patch.startswith(UPS_MAGIC):
        raise ValueError("not a UPS patch")

    offset = len(UPS_MAGIC)
    source_size, offset = decode_vlq(patch, offset)
    target_size, offset = decode_vlq(patch, offset)

    if len(source) != source_size:
        raise ValueError(
            f"source size mismatch: expected {source_size} bytes, got {len(source)}"
        )

    result = bytearray(source)
    if len(result) < target_size:
        result.extend(b"\x00" * (target_size - len(result)))
    elif len(result) > target_size:
        result = bytearray(result[:target_size])

    cursor = 0
    patch_body_end = len(patch) - UPS_TRAILER_SIZE
    while offset < patch_body_end:
        rel_offset, offset = decode_vlq(patch, offset)
        cursor += rel_offset
        while offset < patch_body_end:
            byte = patch[offset]
            offset += 1
            if byte == 0:
                break
            if cursor >= len(result):
                raise ValueError(f"UPS patch writes past target size at offset {cursor}")
            result[cursor] ^= byte
            cursor += 1
        cursor += 1

    stored_source_crc, stored_target_crc, stored_patch_crc = struct.unpack_from(
        "<III", patch, patch_body_end
    )
    if (zlib.crc32(source) & 0xFFFFFFFF) != stored_source_crc:
        raise ValueError("UPS source CRC mismatch")
    if (zlib.crc32(result) & 0xFFFFFFFF) != stored_target_crc:
        raise ValueError("UPS target CRC mismatch")
    if (zlib.crc32(patch[:-4]) & 0xFFFFFFFF) != stored_patch_crc:
        raise ValueError("UPS patch CRC mismatch")

    return bytes(result)


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
