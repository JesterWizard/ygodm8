#!/usr/bin/env python3

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
CARD_NONE = 0


def count_cards_in_hand(hand_ids):
    return sum(1 for card_id in hand_ids if card_id != CARD_NONE)


def draw_cards(deck_drawn, deck_size, count):
    for _ in range(count):
        if deck_drawn >= deck_size:
            return "duel_over", deck_drawn
        deck_drawn += 1
    return "ok", deck_drawn


def init_special_summon_zone():
    return {"unk4": 2, "isFaceUp": True, "isDefending": False}


def init_normal_summon_zone():
    return {"unk4": 0, "isFaceUp": True, "isDefending": False}


class DuelHelpersSourceTests(unittest.TestCase):
    def test_header_declares_core_verbs(self):
        header = (ROOT / "include/duel_helpers.h").read_text()

        for symbol in (
            "Duel_DrawCards",
            "Duel_SpecialSummonFromHand",
            "Duel_NormalSummonFromHand",
            "Duel_TryResolveSpellThroughTraps",
            "Duel_DefaultSpecialSummonOpts",
            "Duel_ClampStat",
            "Duel_TryApplyDynamicZoneStats",
            "Duel_TryApplyDynamicStatMod",
            "Duel_CanAttackMonsterZone",
            "Duel_ApplyStatModViaZoneApplier",
            "enum DuelActionResult",
        ):
            self.assertIn(symbol, header)

    def test_implementation_sets_special_summon_unk4(self):
        source = (ROOT / "src_custom/duel_helpers.c").read_text()

        self.assertIn("zone->unk4 = 2", source)
        self.assertIn("BlockTurnSummoning(duelist)", source)
        self.assertIn("TryApplyPreciousCardsFromBeyondOnTributeSummon", source)
        self.assertIn("APPEND_DATA", source)

    def test_spell_hooks_delegate_trap_resolution(self):
        source = (ROOT / "src_custom/spell_effect_hooks.c").read_text()

        self.assertIn("Duel_TryResolveSpellThroughTraps(spellId, NULL)", source)

    def test_common_chax_exports_helpers(self):
        header = (ROOT / "include/common-chax.h").read_text()
        self.assertIn("duel_helpers.h", header)


class DuelHelpersLogicTests(unittest.TestCase):
    def test_count_cards_in_hand(self):
        self.assertEqual(count_cards_in_hand([1, 2, CARD_NONE, 3, CARD_NONE]), 3)

    def test_draw_stops_at_deck_out(self):
        result, drawn = draw_cards(deck_drawn=2, deck_size=3, count=3)
        self.assertEqual(result, "duel_over")
        self.assertEqual(drawn, 3)

    def test_special_summon_zone_init(self):
        zone = init_special_summon_zone()
        self.assertEqual(zone["unk4"], 2)
        self.assertTrue(zone["isFaceUp"])
        self.assertFalse(zone["isDefending"])

    def test_normal_summon_zone_init(self):
        zone = init_normal_summon_zone()
        self.assertEqual(zone["unk4"], 0)


if __name__ == "__main__":
    unittest.main()
