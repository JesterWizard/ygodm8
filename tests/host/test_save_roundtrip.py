#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from player_deck_persist import (  # noqa: E402
    PLAYER_DECK_SAVE_MAGIC,
    deserialize_flash_record,
    is_complete_deck,
    magic_is_valid,
    serialize_flash_record,
)

FIXTURE_BIN = ROOT / "tests" / "fixtures" / "saves" / "player_decks_primary.bin"
NUM_TOTAL_CARDS = 0x0341


class PlayerDeckPersistTests(unittest.TestCase):
    def test_round_trip_bytes(self):
        deck2 = [1] * 40
        deck3 = [2] * 40
        blob = serialize_flash_record(deck2, deck3, active_deck_index=2)
        out2, out3, active, magic = deserialize_flash_record(blob)
        self.assertEqual(out2, deck2)
        self.assertEqual(out3, deck3)
        self.assertEqual(active, 2)
        self.assertEqual(magic, PLAYER_DECK_SAVE_MAGIC)

    def test_magic_and_complete_deck(self):
        self.assertTrue(magic_is_valid(PLAYER_DECK_SAVE_MAGIC))
        self.assertFalse(magic_is_valid(0))
        complete = [1] * 40
        self.assertTrue(is_complete_deck(complete, NUM_TOTAL_CARDS))
        self.assertFalse(is_complete_deck([0] * 40, NUM_TOTAL_CARDS))

    def test_golden_fixture_round_trip(self):
        FIXTURE_BIN.parent.mkdir(parents=True, exist_ok=True)
        if not FIXTURE_BIN.is_file():
            deck = [0x0001] * 40
            FIXTURE_BIN.write_bytes(serialize_flash_record(deck, deck, active_deck_index=1))
        blob = FIXTURE_BIN.read_bytes()
        deck2, deck3, active, magic = deserialize_flash_record(blob)
        self.assertEqual(deserialize_flash_record(blob), (deck2, deck3, active, magic))
        self.assertTrue(magic_is_valid(magic))


if __name__ == "__main__":
  unittest.main()
