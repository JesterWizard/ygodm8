#!/usr/bin/env python3

import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
KAISER_SEA_HORSE = ROOT / "src_custom" / "permanent_effects" / "kaiser_sea_horse.c"
TRIBUTE_HOOKS = ROOT / "src_custom" / "tribute_hooks.c"
AI_TRIBUTE_HOOKS = ROOT / "src_custom" / "ai_tribute_hooks.c"


class DoubleCostonTests(unittest.TestCase):
    def test_records_dark_bonus_when_hand_has_dark_monster(self):
        source = KAISER_SEA_HORSE.read_text()
        self.assertIn("HandHasDarkMonsterNeedingTwoTributes", source)
        self.assertIn("RecordDoubleCostonDarkBonusPaid(1);", source)

    def test_scans_hand_for_dark_attribute_monsters(self):
        source = KAISER_SEA_HORSE.read_text()
        self.assertIn("ATTRIBUTE_SHADOW", source)
        self.assertIn("gFixedZones[PLAYER_HAND]", source)
        self.assertIn("CardQualifiesForDoubleCostonDarkBonus", source)

    def test_dark_bonus_only_reduces_dark_hand_counters(self):
        source = TRIBUTE_HOOKS.read_text()
        self.assertIn("CardQualifiesForDoubleCostonDarkBonus(summonCardId)", source)
        self.assertIn("paidTributes += GetDoubleCostonDarkBonusPaid();", source)

    def test_ai_one_tribute_dark_summon_reports_one_required(self):
        source = TRIBUTE_HOOKS.read_text()
        self.assertIn("AdjustRequiredTributesForDoubleCoston", source)
        self.assertIn("AiUsesDoubleCostonForOneTributeDarkSummon", source)

    def test_pending_survives_reset_num_tributes(self):
        source = TRIBUTE_HOOKS.read_text()
        self.assertNotIn("ClearPendingTributeSummonCardId();", source)

    def test_ai_records_two_paid_tributes_for_double_coston(self):
        source = AI_TRIBUTE_HOOKS.read_text()
        self.assertIn("AiUsesDoubleCostonForOneTributeDarkSummon()", source)
        self.assertIn("SetPendingSummonTributeCount(2);", source)


if __name__ == "__main__":
    unittest.main()
