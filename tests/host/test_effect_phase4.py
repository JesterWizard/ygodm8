"""Phase 4 effect scripts (C tables)."""

from __future__ import annotations

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(rel: str) -> str:
    return (ROOT / rel).read_text(encoding="utf-8")


class TestEffectPhase4(unittest.TestCase):
    def test_script_api(self):
        hdr = read("include/effect_scripts.h")
        for name in (
            "EFFECT_SCRIPT_DRAW",
            "EFFECT_SCRIPT_CHANGE_LP",
            "EFFECT_SCRIPT_DESTROY_ACTIVATING_SPELL",
            "EffectScript_Find",
            "EffectScript_Run",
            "EFFECT_META_DRAW",
        ):
            self.assertIn(name, hdr)

    def test_scripts_table(self):
        src = read("src_custom/effect_system/effect_scripts.c")
        table = read("src_custom/generated/effect_scripts_table.inc")
        self.assertIn('../generated/effect_scripts_table.inc', src)
        self.assertIn("ONE_DAY_OF_PEACE", table)
        self.assertIn("POT_OF_GREED", table)
        self.assertIn("GRAND_CONVERGENCE", table)
        self.assertIn("sEffectScripts", table)
        self.assertIn("TrySpiritOfThePotOfGreedAfterPotOfGreed", table)

    def test_dispatch_uses_scripts(self):
        src = read("src_custom/effect_system/effect_dispatch.c")
        self.assertIn("EffectScript_Find", src)
        self.assertIn("EffectScript_Run", src)
        self.assertNotIn("Phase 0 has no converted", src)

    def test_pot_of_greed_not_inline(self):
        hooks = read("src_custom/spell_effect_hooks.c")
        self.assertNotIn("case POT_OF_GREED:", hooks)


if __name__ == "__main__":
    unittest.main()
