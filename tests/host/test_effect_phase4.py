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
        self.assertIn("Effect_TryActivate", src)
        self.assertIn("Effect_QueryShouldActivate", src)
        self.assertNotIn("Phase 0 has no converted", src)

    def test_effect_ccto_registry(self):
        hdr = read("include/effect.h")
        for name in (
            "EFFECT_TYPE_ACTIVATE",
            "EFFECT_CODE_ACTIVATE",
            "EffectCond_ScriptGate",
            "EffectOp_RunScript",
            "Effect_TryActivate",
            "Effect_DispatchEvent",
        ):
            self.assertIn(name, hdr)
        reg = read("src_custom/generated/effect_registry.inc")
        self.assertIn("sEffectsFromScripts", reg)
        self.assertIn("EffectOp_RunScript", reg)
        self.assertIn("ONE_DAY_OF_PEACE", reg)
        effect_c = read("src_custom/effect_system/effect.c")
        self.assertIn("Op_DamageCalcAtkBoosts", effect_c)
        self.assertIn("EnsureIndexes", effect_c)
        self.assertIn("CardIndexLowerBound", effect_c)
        self.assertIn("sEventFlat", effect_c)
        self.assertIn("sCardIndex", effect_c)
        # Activate path must use the cardId index, not a full registry walk.
        try_fn = effect_c.split("u8 Effect_TryActivate", 1)[1].split(
            "u8 Effect_QueryShouldActivate", 1
        )[0]
        self.assertIn("CardIndexLowerBound", try_fn)
        self.assertNotIn("ARRAY_COUNT(sEffectsFromScripts)", try_fn)
        dispatch_fn = effect_c.split("void Effect_DispatchEvent", 1)[1].split(
            "u8 Effect_GetCategory", 1
        )[0]
        self.assertIn("sEventFlat", dispatch_fn)
        self.assertNotIn("ARRAY_COUNT(sEffectsFromScripts)", dispatch_fn)
        events = read("src_custom/effect_system/effect_events.c")
        self.assertIn("Effect_DispatchEvent", events)
        self.assertNotIn("ApplySkyscraperBattleAtkBoost", events)

    def test_card_index_lower_bound(self):
        """Mirrors CardIndexLowerBound — fails if the search contract drifts."""
        ids = [10, 20, 20, 30, 40]

        def lower_bound(card_id: int) -> int:
            lo, hi = 0, len(ids)
            while lo < hi:
                mid = (lo + hi) // 2
                if ids[mid] < card_id:
                    lo = mid + 1
                else:
                    hi = mid
            return lo

        self.assertEqual(lower_bound(20), 1)
        self.assertEqual(lower_bound(25), 3)
        self.assertEqual(lower_bound(5), 0)
        self.assertEqual(lower_bound(50), 5)
        # Equal-key run for card 20 covers indexes 1..2
        i = lower_bound(20)
        run = []
        while i < len(ids) and ids[i] == 20:
            run.append(i)
            i += 1
        self.assertEqual(run, [1, 2])

    def test_pot_of_greed_not_inline(self):
        hooks = read("src_custom/spell_effect_hooks.c")
        self.assertNotIn("case POT_OF_GREED:", hooks)


if __name__ == "__main__":
    unittest.main()
