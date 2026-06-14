#!/usr/bin/env python3

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOLL = ROOT / "src_custom" / "spell_effects" / "toll.c"
MANIFEST = ROOT / "tools" / "card_data_manifest.json"


class TollTests(unittest.TestCase):
    def test_attack_cost_scales_with_face_up_toll_copies_not_monsters(self):
        source = TOLL.read_text()
        self.assertIn("CountFaceUpTollsOnField", source)
        self.assertIn("IsActivatedTollZone(gFixedZones[row][i])", source)
        self.assertNotIn("CountActiveDuelistMonsters", source)
        self.assertNotIn("ACTIVE_DUELIST_MONSTER_ROW", source)

    def test_manifest_describes_flat_attack_cost(self):
        manifest = MANIFEST.read_text()
        self.assertIn("Each player must pay 500LP to declare an attack", manifest)
        self.assertNotIn("500LP per monster when attacking", manifest)


if __name__ == "__main__":
    unittest.main()
