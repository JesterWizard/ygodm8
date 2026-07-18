#!/usr/bin/env python3

import json
import struct
import sys
import unittest
import wave
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import generate_music as gm  # noqa: E402
import generate_voices as gv  # noqa: E402

FIXTURE_WAV = ROOT / "tests" / "fixtures" / "test_loop.wav"
FIXTURE_WAV_8BIT = ROOT / "tests" / "fixtures" / "test_loop_8bit.wav"
MUSIC_MANIFEST = ROOT / "tests" / "fixtures" / "music_manifest_minimal.json"


class MusicTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        FIXTURE_WAV.parent.mkdir(parents=True, exist_ok=True)
        if not FIXTURE_WAV.is_file():
            with wave.open(str(FIXTURE_WAV), "w") as handle:
                handle.setnchannels(1)
                handle.setsampwidth(2)
                handle.setframerate(21024)
                samples = [0] * 128 + [8000] * 256 + [0] * 128
                handle.writeframes(b"".join(struct.pack("<h", sample) for sample in samples))
        if not FIXTURE_WAV_8BIT.is_file():
            with wave.open(str(FIXTURE_WAV_8BIT), "w") as handle:
                handle.setnchannels(1)
                handle.setsampwidth(1)
                handle.setframerate(21024)
                samples = [128] * 128 + [192] * 256 + [128] * 128
                handle.writeframes(bytes(samples))

    def test_plan_note_gates_covers_track(self):
        total = gm.max_note_sample_capacity() * 3 + 12000
        notes = gm.plan_note_gates(total)
        self.assertGreater(len(notes), 1)
        covered = 0
        for note in notes:
            extra = note[4] if len(note) == 5 else None
            cap = int(gv.estimate_note_sample_capacity(note[0], note[3], extra))
            self.assertGreater(cap, 0)
            covered += cap
        self.assertGreaterEqual(covered, total)

    def test_wait_commands_encode_requested_ticks(self):
        waits = gm.build_wait_commands(934)
        total = sum(gv.M4A_NOTE_LENGTH_TABLE[cmd - 0x81] for cmd in waits)
        self.assertEqual(total, 934)
        self.assertEqual(waits, bytes([0xB0] * 9 + [0xA7, 0x82]))

    def test_tie_wait_ticks_match_track_duration(self):
        ticks = gm.music_wait_ticks_for_samples(1288785)
        samples = ticks * gv.M4A_NOTE_CAPACITY_A
        self.assertLess(abs(samples - 1288785), 64)

    def test_validate_track_fixture(self):
        manifest = json.loads(MUSIC_MANIFEST.read_text())
        entry = manifest["tracks"][0]
        pcm8, rate = gv.read_wav_mono_pcm8(FIXTURE_WAV, manifest["sample_rate"], 0)
        pcm8 = gm.apply_music_silence_trim(pcm8, manifest, entry)
        pcm8 = gv.apply_pcm8_edge_fade(pcm8, fade_samples=48)
        self.assertEqual(rate, manifest["sample_rate"])
        self.assertTrue(pcm8)

    def test_accepts_8bit_wav_fixture(self):
        pcm8, rate = gv.read_wav_mono_pcm8(FIXTURE_WAV_8BIT, 21024, 0)
        self.assertEqual(rate, 21024)
        self.assertEqual(len(pcm8), 512)
        self.assertEqual(gv.pcm8_sample_value(pcm8[0]), 0)
        self.assertGreater(max(gv.pcm8_sample_value(byte) for byte in pcm8), 0)

    def test_tone_patches_avoid_player_table(self):
        patches = json.loads(
            (ROOT / "src_custom/generated/music_rom_patches.json").read_text()
        )
        for entry in patches.get("tone_patches", []):
            org = entry["org"]
            self.assertLessEqual(
                org + 12,
                gv.M4A_PLAYER_TABLE_ORG,
                f"tone patch at 0x{org:X} overlaps g8AFBD0C",
            )

    def test_no_tone_table_patches(self):
        """Private voicegroups replaced global tone patches (Game Shop key-split fix)."""
        for name in ("music_rom_patches.json", "voice_rom_patches.json"):
            patches = json.loads((ROOT / "src_custom/generated" / name).read_text())
            self.assertEqual(
                patches.get("tone_patches", []),
                [],
                f"{name} must not patch the global tone table",
            )

    def test_layout_max_tone_index(self):
        self.assertEqual(gv.M4A_TONE_INDEX_LAYOUT_MAX, 217)

    def test_music_part_track_uses_voice_tempo(self):
        assets = ROOT / "src_custom/generated/music_assets_generated.s"
        if not assets.is_file():
            self.skipTest("music assets not generated")
        self.assertIn(".byte 0xBC, 0x00, 0xBB, 20", assets.read_text())

    def test_encode_note_covers_segment(self):
        for count in (48211, gm.max_note_sample_capacity()):
            note = gm.encode_bgm_part_track_note(count)
            extra = note[4] if len(note) == 5 else None
            cap = gv.estimate_note_sample_capacity(note[0], note[3], extra)
            self.assertGreaterEqual(cap, count)

    def test_music_uses_bgm_player(self):
        patches = json.loads(
            (ROOT / "src_custom/generated/music_rom_patches.json").read_text()
        )
        for entry in patches.get("song_patches", []):
            self.assertEqual(entry["player"], gm.M4A_BGM_SONG_PLAYER)
        for entry in patches.get("mode_patches", []):
            self.assertEqual(entry["mode"], gm.M4A_BGM_SONG_MODE)

    def test_generated_single_tied_dpcm_wave(self):
        assets = ROOT / "src_custom/generated/music_assets_generated.s"
        if not assets.is_file():
            self.skipTest("music assets not generated")
        text = assets.read_text()
        part_text = text[text.index("CustomMusic_hyperdrive_Part:") :]
        self.assertIn("CustomMusic_hyperdrive_Wave:", text)
        self.assertNotIn("CustomMusic_hyperdrive_Wave0:", text)
        self.assertIn(".byte 0xCF, 60, 127", part_text)
        self.assertIn(".byte 0xCE, 60", part_text)
        self.assertIn(".byte 0xB2", part_text)
        self.assertIn(".word CustomMusic_hyperdrive_LoopStart", part_text)
        self.assertNotIn(".byte 0xDC", part_text)
        self.assertIn(f".hword {gv.M4A_WAVE_TYPE_DPCM}, 0", text)

    def test_music_codec_default_is_dpcm(self):
        manifest = json.loads(MUSIC_MANIFEST.read_text())
        entry = manifest["tracks"][0]
        self.assertEqual(gm.music_codec_for(manifest, entry), gm.MUSIC_CODEC_DPCM)
        self.assertEqual(gm.music_wave_type_for(gm.MUSIC_CODEC_DPCM), gv.M4A_WAVE_TYPE_DPCM)

    def test_music_uses_private_voicegroup(self):
        assets = ROOT / "src_custom/generated/music_assets_generated.s"
        if not assets.is_file():
            self.skipTest("music assets not generated")
        text = assets.read_text()
        self.assertIn("CustomMusic_hyperdrive_Tone:", text)
        self.assertIn(".word CustomMusic_hyperdrive_Tone", text)
        self.assertNotIn(f".word 0x{gv.M4A_TONE_GROUP_PTR:08X}", text)

    def test_game_shop_keysplits_match_baserom(self):
        """Regression: tone-table patches used to corrupt Game Shop key-split maps."""
        baserom = ROOT / "baserom.gba"
        built = ROOT / "ygodm8.gba"
        if not built.is_file():
            self.skipTest("ygodm8.gba not built")
        base = baserom.read_bytes()
        rom = built.read_bytes()
        # Shop voicegroup keysplit keytable pointers (ToneData bytes 8-11).
        for instr, ktab in (
            (89, 0xAFB920),
            (100, 0xAFB86C),
            (101, 0xAFB8CC),
            (102, 0xAFB920),
        ):
            self.assertEqual(
                base[ktab : ktab + 128],
                rom[ktab : ktab + 128],
                f"Game Shop keysplit instr {instr} keytable corrupted",
            )

    def test_default_song_id_base_after_voices(self):
        header = ROOT / "include" / "constants" / "custom_voices_generated.h"
        if not header.is_file():
            self.skipTest("voice header required")
        match = __import__("re").search(
            r"#define CUSTOM_VOICE_SONG_ID_MAX (\d+)", header.read_text()
        )
        self.assertIsNotNone(match)
        self.assertEqual(gm.default_song_id_base(), int(match.group(1)) + 1)


if __name__ == "__main__":
    unittest.main()
