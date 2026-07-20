"""Phase 3 effect events + OPT."""

from __future__ import annotations

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(rel: str) -> str:
    return (ROOT / rel).read_text(encoding="utf-8")


class TestEffectPhase3(unittest.TestCase):
    def test_event_api(self):
        hdr = read("include/effect_events.h")
        for name in (
            "EFFECT_EVENT_ON_SUMMON",
            "EFFECT_EVENT_ON_DESTROY",
            "EFFECT_EVENT_ON_BATTLE_DESTROY",
            "EFFECT_EVENT_ON_DAMAGE_CALC",
            "EFFECT_EVENT_ON_TURN_STANDBY",
            "EFFECT_EVENT_ON_LEAVE_FIELD",
            "EffectEvent_Subscribe",
            "EffectEvent_Emit",
            "EffectEvent_OnTurnBoundary",
            "EffectOpt_IsUsed",
            "EffectOpt_MarkUsed",
            "EffectOpt_ClearAll",
        ):
            self.assertIn(name, hdr)

    def test_ram_symbols(self):
        ram = read("asm/ram_map_ewram.s")
        self.assertIn("gEffectEventHandlers", ram)
        self.assertIn("gEffectOptUsedIds", ram)
        self.assertIn("gEffectOptUsedCount", ram)

    def test_emit_sites(self):
        helpers = read("src_custom/duel_helpers.c")
        self.assertIn("EFFECT_EVENT_ON_SUMMON", helpers)
        self.assertIn("EFFECT_EVENT_ON_DESTROY", helpers)
        self.assertIn("EFFECT_EVENT_ON_LEAVE_FIELD", helpers)

        battle = read("src_custom/battle_damage_hooks.c")
        self.assertIn("EFFECT_EVENT_ON_BATTLE_DESTROY", battle)

        turn = read("src_custom/turn_effect_hooks.c")
        self.assertIn("EffectEvent_OnTurnBoundary", turn)

    def test_opt_pilots(self):
        call = read("src_custom/spell_effects/amazoness_call.c")
        self.assertIn("EffectOpt_IsUsed(AMAZONESS_CALL)", call)
        self.assertIn("EffectOpt_MarkUsed(AMAZONESS_CALL)", call)
        self.assertNotIn("sAmazonessCallUsedThisTurn", call)

        burst = read("src_custom/spell_effects/d_burst.c")
        self.assertIn("EffectOpt_IsUsed(D_BURST)", burst)
        self.assertIn("EffectOpt_MarkUsed(D_BURST)", burst)
        self.assertNotIn("sDBurstUsedThisTurn", burst)


if __name__ == "__main__":
    unittest.main()
