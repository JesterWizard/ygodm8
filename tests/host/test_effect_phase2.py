"""Phase 2 effect conditions + selectors."""

from __future__ import annotations

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(rel: str) -> str:
    return (ROOT / rel).read_text(encoding="utf-8")


class TestEffectPhase2(unittest.TestCase):
    def test_condition_registry(self):
        hdr = read("include/effect_conditions.h")
        for name in (
            "EFFECT_COND_OPP_BACKROW_SPELL_TRAP",
            "EFFECT_COND_ACTIVE_FACE_UP_SPELL",
            "EFFECT_COND_OPP_MONSTER",
            "EffectCond_Get",
            "EffectCond_Eval",
            "EffectCond_ActiveFaceUpSpell",
            "EffectCond_OppBackrowSpellTrap",
        ):
            self.assertIn(name, hdr)
        src = read("src_custom/effect_system/effect_conditions.c")
        self.assertIn("sEffectConds", src)

    def test_selector_registry(self):
        hdr = read("include/effect_selectors.h")
        for name in (
            "EffectSel_FirstOnField",
            "EffectSel_ExistsOnField",
            "EffectSel_AiPickFirst",
            "EffectSel_ExistsByCond",
            "EffectSel_FirstByCond",
        ):
            self.assertIn(name, hdr)

    def test_pilots_use_conditions(self):
        burst = read("src_custom/spell_effects/d_burst.c")
        self.assertIn("EffectCond_ActiveFaceUpSpell", burst)
        self.assertIn("EffectSel_ExistsByCond", burst)
        self.assertIn("EffectSel_AiPickFirst", burst)
        self.assertNotIn("IsFaceUpSpellTarget", burst)

        spirit = read("src_custom/permanent_effects/dragon_spirit_of_white.c")
        self.assertIn("EffectCond_OppBackrowSpellTrap", spirit)
        self.assertIn("EffectSel_ExistsByCond", spirit)
        self.assertNotIn("IsOppSpellTrapTarget", spirit)


if __name__ == "__main__":
    unittest.main()
