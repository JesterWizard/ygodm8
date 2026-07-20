"""Phase 5 effect metadata for AI."""

from __future__ import annotations

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(rel: str) -> str:
    return (ROOT / rel).read_text(encoding="utf-8")


class TestEffectPhase5(unittest.TestCase):
    def test_meta_api(self):
        hdr = read("include/effect_scripts.h")
        self.assertIn("EffectMeta_GetCategory", hdr)
        self.assertIn("EffectMeta_HasConvertedScript", hdr)
        self.assertIn("EffectScript_FindAny", hdr)

    def test_meta_impl(self):
        src = read("src_custom/effect_system/effect_scripts.c")
        self.assertIn("EffectMeta_GetCategoryLegacy", src)
        self.assertIn("SPELL_EFFECT_RAIGEKI", src)
        self.assertIn("SPELL_EFFECT_POT_OF_GREED", src)

    def test_ai_modifier_wired(self):
        mods = read("src_custom/ai_decision/ai_modifiers.c")
        self.assertIn("AiMod_EffectSemantics", mods)
        self.assertIn("EffectMeta_GetCategory", mods)
        self.assertIn("EFFECT_META_DRAW", mods)
        self.assertIn("EFFECT_META_DESTROY", mods)
        self.assertIn("EFFECT_META_BURN", mods)


if __name__ == "__main__":
    unittest.main()
