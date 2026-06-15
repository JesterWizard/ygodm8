#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import add_custom_card as add_card  # noqa: E402
from card_manifest import validate_manifest  # noqa: E402


class AddCustomCardTests(unittest.TestCase):
    def test_build_manifest_entry_effect_monster(self):
        api_card = {
            "id": 53530069,
            "name": "Spirit of the Breeze",
            "type": "Effect Monster",
            "race": "Fairy",
            "attribute": "WIND",
            "atk": 0,
            "def": 1800,
            "level": 3,
            "desc": (
                "As long as this card remains in face-up Attack Position on your side of the field, "
                "increase your Life Points by 1000 points during each of your Standby Phases."
            ),
        }
        manifest = {"cards": []}
        entry = add_card.finalize_entry(add_card.build_manifest_entry(api_card, manifest))
        self.assertEqual(entry["card_const"], "SPIRIT_OF_THE_BREEZE")
        self.assertEqual(entry["description"]["symbol"], "gDescription_SpiritOfTheBreeze")
        self.assertEqual(entry["color"], "EFFECT_CARD")
        self.assertEqual(entry["password"], [5, 3, 5, 3, 0, 0, 6, 9])

    def test_card_name_to_const(self):
        self.assertEqual(add_card.card_name_to_const("Battle Footballer"), "BATTLE_FOOTBALLER")


if __name__ == "__main__":
    unittest.main()
