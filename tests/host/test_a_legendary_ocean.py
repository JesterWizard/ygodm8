#!/usr/bin/env python3

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


class ALegendaryOceanTests(unittest.TestCase):
    def test_helpers_wired_in_stat_and_tribute_paths(self):
        card_hooks = (ROOT / "src_custom/card_hooks.c").read_text()
        tribute_hooks = (ROOT / "src_custom/tribute_hooks.c").read_text()
        info_bar = (ROOT / "src_custom/duel_opponent_hand_scroll_hooks.c").read_text()
        effect_hooks = (ROOT / "src_custom/field_spell_effect_hooks.c").read_text()
        effect = (ROOT / "src_custom/field_spell_effects/a_legendary_ocean.c").read_text()

        self.assertIn("ApplyLegendaryOceanFieldStatBoostForZone", card_hooks)
        self.assertIn("GetLegendaryOceanAdjustedLevel", card_hooks)
        self.assertIn("ApplyCardInfoBarLevelOverrides", card_hooks)
        self.assertIn("ApplyLegendaryOceanFieldStatBoostForZone(zone)", card_hooks)
        self.assertIn("ApplyLegendaryOceanFieldStatBoostForZone(gSetFinalStatZone)", card_hooks)
        self.assertNotIn("ZoneIsOnBoardField", card_hooks)
        self.assertNotIn("FinishApplyFieldZoneStatsToCardInfo", card_hooks)
        self.assertIn("Duel_RefreshMonsterStatOverlays();", effect_hooks)
        self.assertIn("ApplyCardInfoBarLevelOverrides(gCardInfo.id)", info_bar)
        self.assertIn("GetLegendaryOceanAdjustedLevel", tribute_hooks)
        self.assertIn("ActivateCustomFieldSpell(CUSTOM_FIELD_SPELL_A_LEGENDARY_OCEAN)", effect)

    def test_is_water_monster_does_not_call_set_card_info(self):
        source = (ROOT / "src_custom/a_legendary_ocean.c").read_text()
        body = source.split("static u8 IsWaterMonster", 1)[1].split("\n}", 1)[0]
        self.assertNotRegex(body, r"\bSetCardInfo\s*\(")
        self.assertNotRegex(body, r"\bGetTypeGroup\s*\(")
        self.assertIn("card->attribute == ATTRIBUTE_WATER", body)
        self.assertIn("Duel_FindFixedMonsterZone", source)


if __name__ == "__main__":
    unittest.main()
