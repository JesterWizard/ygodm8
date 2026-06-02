#!/usr/bin/env python3

import json
import struct
import sys
import unittest
import wave
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import generate_voices as gv  # noqa: E402

from tests.support.golden import assert_matches_golden  # noqa: E402

FIXTURE_WAV = ROOT / "src_custom" / "assets" / "voices" / "test_fixtures" / "test_turn.wav"
VOICE_MANIFEST = ROOT / "tests" / "fixtures" / "voice_manifest_minimal.json"


class VoiceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        FIXTURE_WAV.parent.mkdir(parents=True, exist_ok=True)
        if not FIXTURE_WAV.is_file():
            with wave.open(str(FIXTURE_WAV), "w") as handle:
                handle.setnchannels(1)
                handle.setsampwidth(2)
                handle.setframerate(21024)
                samples = [0] * 64 + [6000] * 128 + [0] * 64
                handle.writeframes(b"".join(struct.pack("<h", sample) for sample in samples))

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
        pcm8 = bytes([0, 0, 236, 40, 60, 0, 0, 0])
        trimmed = gv.trim_silence_edges_pcm8(pcm8, threshold=8)
        payload = gv.encode_dpcm_pcm8_validated(trimmed)
        gv.validate_dpcm_payload(trimmed, payload)

    def test_validate_note_encoder(self):
        gv.validate_note_encoder()

    def test_golden_dpcm_payload(self):
        pcm8 = bytes([0, 0, 236, 40, 60, 0, 0, 0])
        trimmed = gv.trim_silence_edges_pcm8(pcm8, threshold=8)
        payload = gv.encode_dpcm_pcm8_validated(trimmed)
        hex_lines = "\n".join(payload[i : i + 16].hex() for i in range(0, len(payload), 16))
        assert_matches_golden(hex_lines + "\n", "voices/dpcm_trimmed_sample.hex")

    def test_validate_clip_fixture(self):
        manifest = json.loads(VOICE_MANIFEST.read_text())
        entry = manifest["clips"][0]
        gv.validate_clip(
            entry,
            ai_ids={},
            opponent_ids={"DUELIST_YUGI_001": 1},
            card_ids={"BLUE_EYES_WHITE_DRAGON": 1},
            sample_rate=manifest["sample_rate"],
            manifest=manifest,
        )


if __name__ == "__main__":
    unittest.main()
