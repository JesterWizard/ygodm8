#!/usr/bin/env python3

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EFFECT = ROOT / "src_custom" / "spell_effects" / "precious_cards_from_beyond.c"
CODE_HOOKS = ROOT / "src_custom" / "code_8043EF4_hooks.c"
AI_HOOKS = ROOT / "src_custom" / "ai_tribute_hooks.c"
SPELL_HOOKS = ROOT / "src_custom" / "spell_effect_hooks.c"
MANIFEST = ROOT / "tools" / "card_data_manifest.json"


class PreciousCardsFromBeyondTests(unittest.TestCase):
    def test_draws_when_two_or_more_tributes_required(self):
        source = EFFECT.read_text()
        self.assertIn("PRECIOUS_CARDS_FROM_BEYOND_MIN_TRIBUTES", source)
        self.assertIn("GetNumRequiredTributes(summonCardId)", source)
        self.assertIn("GetPendingSummonTributeCount()", source)
        self.assertIn("TryDrawingCard(duelist)", source)

    def test_ignores_zero_tribute_summons_like_swift_gaia(self):
        source = EFFECT.read_text()
        self.assertIn("paidTributes < PRECIOUS_CARDS_FROM_BEYOND_MIN_TRIBUTES", source)

    def test_wired_through_tribute_summon_hooks(self):
        self.assertIn(
            "TryApplyPreciousCardsFromBeyondOnTributeSummon",
            CODE_HOOKS.read_text(),
        )
        self.assertIn(
            "TryApplyPreciousCardsFromBeyondOnTributeSummon",
            AI_HOOKS.read_text(),
        )

    def test_spell_activation_is_registered(self):
        self.assertIn("PRECIOUS_CARDS_FROM_BEYOND", SPELL_HOOKS.read_text())
        self.assertIn("EffectPreciousCardsFromBeyond", SPELL_HOOKS.read_text())

    def test_activated_zone_cannot_be_selected_again(self):
        hooks = CODE_HOOKS.read_text()
        self.assertIn("IsActivatedPreciousCardsFromBeyondZone(zone)", hooks)
        self.assertIn("zone->isLocked = TRUE", EFFECT.read_text())

    def test_manifest_entry_exists(self):
        manifest = MANIFEST.read_text()
        self.assertIn('"card_const": "PRECIOUS_CARDS_FROM_BEYOND"', manifest)
        self.assertIn('"cost": 150', manifest)


if __name__ == "__main__":
    unittest.main()
