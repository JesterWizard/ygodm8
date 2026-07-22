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
            "EFFECT_EVENT_ON_LP_GAIN",
            "EFFECT_EVENT_ON_LP_LOSS",
            "EFFECT_EVENT_ON_CARD_ACTIVATE",
            "EffectEvent_Subscribe",
            "EffectEvent_Emit",
            "EffectEvent_EmitLpChange",
            "EffectEvent_EmitCardActivate",
            "EffectEvent_RequestActivationNegate",
            "EffectEvent_ConsumeActivationNegate",
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
        self.assertIn("gEffectActivationNegated", ram)
        self.assertIn("960", ram)  # 10 events * 24 subscribers * 4

    def test_emit_sites(self):
        helpers = read("src_custom/duel_helpers.c")
        self.assertIn("EFFECT_EVENT_ON_SUMMON", helpers)
        self.assertIn("EFFECT_EVENT_ON_DESTROY", helpers)
        self.assertIn("EFFECT_EVENT_ON_LEAVE_FIELD", helpers)
        self.assertIn("EffectEvent_EmitLpChange", helpers)

        battle = read("src_custom/battle_damage_hooks.c")
        self.assertIn("EFFECT_EVENT_ON_BATTLE_DESTROY", battle)

        turn = read("src_custom/turn_effect_hooks.c")
        self.assertIn("EffectEvent_OnTurnBoundary", turn)

        spell = read("src_custom/spell_effect_hooks.c")
        self.assertIn("EffectEvent_EmitCardActivate", spell)
        self.assertIn("EffectEvent_ConsumeActivationNegate", spell)

    def test_opt_pilots(self):
        call = read("src_custom/spell_effects/amazoness_call.c")
        self.assertIn("EffectOpt_IsUsed(AMAZONESS_CALL)", call)
        self.assertIn("EffectOpt_MarkUsed(AMAZONESS_CALL)", call)
        self.assertNotIn("sAmazonessCallUsedThisTurn", call)

        burst = read("src_custom/spell_effects/d_burst.c")
        self.assertIn("EffectOpt_IsUsed(D_BURST)", burst)
        self.assertIn("EffectOpt_MarkUsed(D_BURST)", burst)
        self.assertNotIn("sDBurstUsedThisTurn", burst)

    def test_lp_gain_pilot(self):
        aroma = read("src_custom/activated_effects/aroma_lp_gain.c")
        self.assertIn("EFFECT_EVENT_ON_LP_GAIN", aroma)
        self.assertIn("AromaLpGain_EnsureInit", aroma)
        self.assertIn("AROMAGE_BERGAMOT", aroma)
        self.assertIn("AROMAGE_CANANGA", aroma)
        self.assertIn("AROMAGE_JASMINE", aroma)

        events = read("src_custom/effect_system/effect_events.c")
        self.assertIn("AromaLpGain_EnsureInit", events)


if __name__ == "__main__":
    unittest.main()
