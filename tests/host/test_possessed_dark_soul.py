import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EFFECT = ROOT / "src_custom" / "activated_effects" / "possessed_dark_soul.c"


class TestPossessedDarkSoul(unittest.TestCase):
    def test_effect_wires_self_tribute_and_mass_control(self):
        source = EFFECT.read_text()
        self.assertIn("PossessedDarkSoulSelfZone", source)
        self.assertIn("gFixedZones[gMonEffect.row][gMonEffect.zone]", source)
        self.assertIn("CopyCard(dst, src)", source)
        self.assertIn("Duel_NotifyMonsterZoneChanged(dst)", source)
        self.assertIn("Duel_ShowEffectTextTyped(POSSESSED_DARK_SOUL, 2)", source)
        self.assertIn("Duel_DestroyZone(selfZone, ACTIVE_DUELIST, FALSE)", source)
        self.assertIn("willChangeSides = FALSE", source)
        self.assertIn("EmptyZonesAfterSelfTribute() > 0", source)


if __name__ == "__main__":
    unittest.main()
