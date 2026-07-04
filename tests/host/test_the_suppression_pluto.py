"""Host checks for The Suppression Pluto manifest and on-summon steal effect."""

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text()


class TestTheSuppressionPluto(unittest.TestCase):
    def test_manifest_entry(self):
        manifest = read("tools/card_data_manifest.json")
        self.assertIn('"card_const": "THE_SUPPRESSION_PLUTO"', manifest)
        self.assertIn('"password": [2, 4, 4, 1, 3, 2, 9, 9]', manifest)
        self.assertIn("take control of 1 Spell/Trap Card your opponent controls", manifest)

    def test_on_summon_steal_effect(self):
        source = read("src_custom/activated_effects/the_suppression_pluto.c")
        self.assertIn("TryTheSuppressionPlutoOnMonsterPlacement", source)
        self.assertIn("TakeControlOfSpellTrap", source)
        self.assertIn("OpponentBackrowFixedRow", source)
        self.assertIn("ControllerBackrowFixedRow", source)
        self.assertIn("Duel_ShowEffectTextTyped(THE_SUPPRESSION_PLUTO, 2)", source)

    def test_placement_hooks_wired(self):
        helpers = read("src_custom/duel_helpers.c")
        placement = read("src_custom/code_8043EF4_hooks.c")
        self.assertIn("TryTheSuppressionPlutoOnMonsterPlacement", helpers)
        self.assertIn("TryTheSuppressionPlutoOnMonsterPlacement", placement)


if __name__ == "__main__":
    unittest.main()
