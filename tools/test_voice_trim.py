#!/usr/bin/env python3
"""Tests for custom voice edge silence trimming."""

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import generate_voices as gv  # noqa: E402


class VoiceSilenceTrimTests(unittest.TestCase):
    def test_trims_leading_and_trailing(self):
        pcm8 = bytes([0, 0, 5, 10, 20, 0, 0])
        trimmed = gv.trim_silence_edges_pcm8(pcm8, threshold=4)
        self.assertEqual(trimmed, bytes([5, 10, 20]))

    def test_all_silence_unchanged(self):
        pcm8 = bytes([0, 0, 0])
        self.assertEqual(gv.trim_silence_edges_pcm8(pcm8, threshold=8), pcm8)

    def test_disabled_via_manifest(self):
        pcm8 = bytes([0, 10, 0])
        manifest = {"trim_silence": False}
        entry = {}
        self.assertEqual(gv.apply_silence_trim(pcm8, manifest, entry), pcm8)

    def test_per_clip_threshold(self):
        pcm8 = bytes([2, 10, 2])
        manifest = {"trim_silence": True, "trim_silence_threshold": 8}
        entry = {"trim_silence_threshold": 4}
        self.assertEqual(gv.apply_silence_trim(pcm8, manifest, entry), bytes([10]))

    def test_dpcm_round_trip_after_trim(self):
        pcm8 = bytes([0, 0, 236, 40, 60, 0, 0, 0])  # 236 == -20 as s8
        trimmed = gv.trim_silence_edges_pcm8(pcm8, threshold=8)
        payload = gv.encode_dpcm_pcm8_validated(trimmed)
        gv.validate_dpcm_payload(trimmed, payload)


if __name__ == "__main__":
    unittest.main()
