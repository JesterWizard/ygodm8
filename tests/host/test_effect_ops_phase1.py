"""Phase 1 effect ops: registry + pilot composition via Op_*."""

from __future__ import annotations

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(rel: str) -> str:
    return (ROOT / rel).read_text(encoding="utf-8")


class TestEffectOpsPhase1(unittest.TestCase):
    def test_op_registry_api(self):
        hdr = read("include/effect_ops.h")
        for name in (
            "EFFECT_OP_DRAW",
            "EFFECT_OP_MILL",
            "EFFECT_OP_DESTROY_ZONE",
            "EFFECT_OP_CHANGE_LP",
            "EFFECT_OP_SEARCH_DECK_BY_ID",
            "EffectOp_Run",
            "Op_Draw",
            "Op_DestroyZone",
            "Op_ChangeLp",
            "Op_SearchDeckById",
        ):
            self.assertIn(name, hdr)

    def test_ops_wrap_duel_helpers(self):
        src = read("src_custom/effect_system/effect_ops.c")
        self.assertIn("Duel_DrawCards", src)
        self.assertIn("Duel_DestroyZone", src)
        self.assertIn("Duel_ChangeLp", src)
        self.assertIn("Duel_AddDeckCardToHand", src)
        self.assertIn("sEffectOps", src)

    def test_pilots_use_ops(self):
        cases = {
            "src_custom/spell_effects/one_day_of_peace.c": ("Op_Draw", "Op_DestroyZone"),
            "src_custom/spell_effects/grand_convergence.c": (
                "Op_ChangeLp",
                "Op_DestroyAllMonstersInRow",
                "Op_DestroyZone",
            ),
            "src_custom/spell_effects/d_burst.c": ("Op_DestroyZone", "Op_Draw"),
        }
        for path, ops in cases.items():
            text = read(path)
            with self.subTest(path=path):
                self.assertIn('#include "effect_ops.h"', text)
                for op in ops:
                    self.assertIn(op, text)
                # Composition demos should not call the wrapped Duel_* for those paths
                if "one_day_of_peace" in path:
                    self.assertNotIn("Duel_DrawCards", text)
                    self.assertNotIn("Duel_DestroyZone", text)
                if "grand_convergence" in path:
                    self.assertNotIn("Duel_ChangeLp", text)
                    self.assertNotIn("Duel_DestroyAllMonstersMatching", text)


if __name__ == "__main__":
    unittest.main()
