#!/usr/bin/env python3
"""Validate The Grand Jupiter manifest and effect wiring."""

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text()


class TestTheGrandJupiter(unittest.TestCase):
    def test_manifest_entry(self):
        manifest = read("tools/card_data_manifest.json")
        self.assertIn('"card_const": "THE_GRAND_JUPITER"', manifest)
        self.assertIn('"monsterEffect": "MONSTER_EFFECT_THE_GRAND_JUPITER"', manifest)
        self.assertIn('"effect_usage": "once_per_turn"', manifest)

    def test_effect_places_absorbed_monsters_in_controller_backrow(self):
        source = read("src_custom/activated_effects/the_grand_jupiter.c")
        self.assertIn("ControllerBackrowForJupiter", source)
        self.assertIn("StoreEquipLink", source)
        self.assertIn("gCardData_NEW[cardId].atk", source)
        self.assertIn("SumEquipOriginalAtkForJupiterZone", source)
        self.assertIn("ApplyTheGrandJupiterEquipAtkBonus", source)
        self.assertIn("gGrandJupiterEquipJupiterRow", source)
        self.assertIn("MarkGrandJupiterAbsorbUsedThisTurn", source)
        self.assertIn("MarkGrandJupiterEndPhaseUsedThisTurn", source)
        self.assertIn("zone->unkThree", source)
        self.assertIn("GRAND_JUPITER_END_PHASE_USED", source)
        self.assertIn("equipZone->id = monsterId", source)
        self.assertIn("ClearZone(targetZone)", source)

    def test_end_phase_targets_equipped_backrow_monster(self):
        source = read("src_custom/activated_effects/the_grand_jupiter.c")
        backrow = read("src_custom/code_8043EF4_hooks.c")
        self.assertIn("IsGrandJupiterEquipZone", source)
        self.assertIn("SpecialSummonEquippedMonster", source)
        self.assertIn("CARD_EFFECT_TEXT_THE_GRAND_JUPITER_POPUP_2", source)
        self.assertIn("ActivateGrandJupiterEquippedMonster", backrow)

    def test_effect_menu_only_runs_absorb(self):
        source = read("src_custom/activated_effects/the_grand_jupiter.c")
        hooks = read("src_custom/monster_effect_hooks.c")
        self.assertIn("ShowGrandJupiterPopup(CARD_EFFECT_TEXT_THE_GRAND_JUPITER_POPUP_1)", source)
        self.assertIn("DUEL_CURSOR_THE_GRAND_JUPITER_ABSORB_TARGET", source)
        self.assertIn("TrySelectTheGrandJupiterAbsorbTarget", source)
        self.assertIn("sub_8041E70(PLAYER_HAND, targetRow)", source)
        self.assertNotIn("BeginEndPhaseSummonEffect", source)
        self.assertIn("CanActivateTheGrandJupiterAbsorb", source)
        self.assertIn("CanActivateGrandJupiterEquippedMonster", source)
        self.assertIn("MarkGrandJupiterAbsorbUsedThisTurn(zone)", source)
        self.assertIn("MarkMonsterEffectUsed(jupiterZone)", source)
        self.assertNotIn("zone->id != THE_GRAND_JUPITER", hooks)


if __name__ == "__main__":
    unittest.main()
