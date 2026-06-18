import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EFFECT = ROOT / "src_custom" / "activated_effects" / "dice_jar.c"


class DiceJarTests(unittest.TestCase):
    def test_flip_rerolls_ties_and_scales_damage(self):
        source = EFFECT.read_text()
        self.assertIn("DICE_JAR_MAX_DAMAGE 6000", source)
        self.assertIn("while (activeRoll == inactiveRoll)", source)
        self.assertIn("winnerRoll * 500", source)
        self.assertIn("Duel_ShowEffectTextTyped(DICE_JAR, 2)", source)


if __name__ == "__main__":
    unittest.main()
