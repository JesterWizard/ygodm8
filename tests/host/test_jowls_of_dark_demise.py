import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EFFECT = ROOT / "src_custom" / "activated_effects" / "jowls_of_dark_demise.c"


class TestJowlsOfDarkDemise(unittest.TestCase):
    def test_effect_wires_control_and_direct_attack(self):
        source = EFFECT.read_text()
        self.assertIn("willChangeSides = TRUE", source)
        self.assertIn("CanJowlsControlledMonsterAttackDirectly", source)
        self.assertIn("Duel_ShowEffectTextTyped(JOWLS_OF_DARK_DEMISE, 2)", source)
        self.assertIn("TakeControlFromOpponentFixedCol", source)
        self.assertIn("gFixedZones[OPPONENT_MONSTER_ROW]", source)


if __name__ == "__main__":
    unittest.main()
