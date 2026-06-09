#!/usr/bin/env python3

import struct
import sys
import unittest
import zlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from make_ups import (  # noqa: E402
    UPS_MAGIC,
    UPS_TRAILER_SIZE,
    apply_patch,
    build_patch,
    decode_vlq,
    encode_vlq,
)

BASEROM = ROOT / "baserom.gba"
ROM = ROOT / "ygodm8.gba"
PATCH = ROOT / "ygodm8.ups"


class UpsCodecTests(unittest.TestCase):
    def test_vlq_roundtrip(self):
        for value in (0, 1, 127, 128, 16383, 16384, 1_000_000):
            with self.subTest(value=value):
                encoded = encode_vlq(value)
                decoded, offset = decode_vlq(encoded)
                self.assertEqual(decoded, value)
                self.assertEqual(offset, len(encoded))

    def test_build_patch_has_trailer_crcs(self):
        source = b"vanilla"
        target = b"patched"
        patch = build_patch(source, target)

        self.assertTrue(patch.startswith(UPS_MAGIC))
        self.assertGreaterEqual(len(patch), len(UPS_MAGIC) + UPS_TRAILER_SIZE)

        source_crc, target_crc, patch_crc = struct.unpack_from("<III", patch, len(patch) - 12)
        self.assertEqual(source_crc, zlib.crc32(source) & 0xFFFFFFFF)
        self.assertEqual(target_crc, zlib.crc32(target) & 0xFFFFFFFF)
        self.assertEqual(patch_crc, zlib.crc32(patch[:-4]) & 0xFFFFFFFF)

    def test_apply_patch_roundtrip_small_buffers(self):
        cases = [
            (b"", b""),
            (b"same", b"same"),
            (b"abcdef", b"abcXef"),
            (b"short", b"short-but-longer"),
            (b"\x00" * 8, b"\x00\x01\x00\x00\x00\x00\x00\xFF"),
        ]
        for source, target in cases:
            with self.subTest(source=source, target=target):
                patch = build_patch(source, target)
                self.assertEqual(apply_patch(source, patch), target)

    def test_apply_patch_rejects_bad_source_size(self):
        patch = build_patch(b"abcd", b"abcX")
        with self.assertRaisesRegex(ValueError, "source size mismatch"):
            apply_patch(b"abc", patch)

    def test_apply_patch_rejects_bad_crc(self):
        source = b"source"
        target = b"target"
        patch = bytearray(build_patch(source, target))
        patch[-8] ^= 0xFF
        with self.assertRaisesRegex(ValueError, "CRC mismatch"):
            apply_patch(source, bytes(patch))


class UpsBuildArtifactTests(unittest.TestCase):
    @unittest.skipUnless(BASEROM.is_file() and ROM.is_file(), "requires baserom.gba and ygodm8.gba")
    def test_built_rom_roundtrips_through_generated_patch(self):
        source = BASEROM.read_bytes()
        target = ROM.read_bytes()
        patch = build_patch(source, target)
        self.assertEqual(apply_patch(source, patch), target)

    @unittest.skipUnless(
        BASEROM.is_file() and ROM.is_file() and PATCH.is_file(),
        "requires baserom.gba, ygodm8.gba, and ygodm8.ups",
    )
    def test_makefile_ups_artifact_matches_target(self):
        source = BASEROM.read_bytes()
        target = ROM.read_bytes()
        patch = PATCH.read_bytes()
        self.assertEqual(apply_patch(source, patch), target)


if __name__ == "__main__":
    unittest.main()
