#!/usr/bin/env python3

"""Validate that ComputeFinalStage wires the Orichalcos +1 stage boost."""

import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

COMPUTE_FINAL_STAGE_SOURCE = ROOT / "src_custom" / "code_803F02C_hooks.c"
ORICHALCOS_FIELD_EFFECT = ROOT / "src_custom" / "field_spell_effects" / "seal_of_orichalcos.c"
FIELD_SPELL_EFFECT_HOOKS = ROOT / "src_custom" / "field_spell_effect_hooks.c"
DUEL_OPP_HAND_HOOKS = ROOT / "src_custom" / "duel_opponent_hand_scroll_hooks.c"
MINI_CARD_HOOKS = ROOT / "src_custom" / "mini_card_hooks.c"


def extract_function_body(source: str, function_name: str) -> str:
    pattern = rf"(?:void|u8|int|s8)\s*{re.escape(function_name)}\s*\([^)]*\)\s*\{{"
    match = re.search(pattern, source)
    if match is None:
        raise AssertionError(f"Could not find function {function_name}")
    start = match.end()
    depth = 1
    index = start
    while index < len(source) and depth:
        char = source[index]
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
        index += 1
    return source[start : index - 1]


class OrichalcosStageBoostTests(unittest.TestCase):
    def test_compute_final_stage_checks_orichalcos(self):
        source = COMPUTE_FINAL_STAGE_SOURCE.read_text()
        body = extract_function_body(source, "ComputeFinalStage")

        self.assertIn("gActiveCustomFieldSpellId == CUSTOM_FIELD_SPELL_SEAL_OF_ORICHALCOS", body)
        self.assertIn("GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER", body)
        self.assertIn("GetDuelistForZone(zone) == gActiveFieldSpellController", body)
        self.assertIn("gActiveFieldSpellController != FIELD_SPELL_CONTROLLER_NONE", body)
        self.assertIn("!IsWorldSuppressionNegatingFieldSpell(SEAL_OF_ORICHALCOS)", body)
        self.assertIn("stage++", body)

    def test_get_final_stage_replacement_calls_compute_final_stage(self):
        source = COMPUTE_FINAL_STAGE_SOURCE.read_text()
        body = extract_function_body(source, "GetFinalStage__Replacement")

        self.assertIn("ComputeFinalStage(zone)", body)
        self.assertIn("gSetFinalStatZone = zone", body)

    def test_runtime_sets_correct_controller(self):
        source = FIELD_SPELL_EFFECT_HOOKS.read_text()
        body = extract_function_body(source, "RunFieldSpellActivation")

        self.assertIn("gActiveCustomFieldSpellId = customSpellId", body)
        self.assertIn("gActiveFieldSpellController = WhoseTurn()", body)

    def test_effect_activate_seal_of_orichalcos_calls_activate(self):
        source = ORICHALCOS_FIELD_EFFECT.read_text()
        body = extract_function_body(source, "EffectActivateSealOfOrichalcos")

        self.assertIn("ActivateCustomFieldSpell", body)
        self.assertIn("CUSTOM_FIELD_SPELL_SEAL_OF_ORICHALCOS", body)

    def test_mini_card_stat_refresh_uses_compute_final_stage(self):
        source = MINI_CARD_HOOKS.read_text()

        # RefreshFieldMonsterStatOverlays uses ComputeFinalStage
        refresh_body = extract_function_body(source, "RefreshFieldMonsterStatOverlays")
        self.assertIn("ComputeFinalStage(zone)", refresh_body)
        self.assertIn("sub_80572A8(tilePtr, zone)", refresh_body)
        self.assertIn("sub_805733C(tilePtr, zone)", refresh_body)

        # RefreshAllFieldCardTiles also uses ComputeFinalStage for player row
        all_body = extract_function_body(source, "RefreshAllFieldCardTiles")
        self.assertIn("ComputeFinalStage(zone)", all_body)

    def test_display_card_info_bar_uses_apply_field_zone_stats(self):
        source = DUEL_OPP_HAND_HOOKS.read_text()
        body = extract_function_body(source, "DisplayCardInfoBar__Replacement")
        self.assertIn("ApplyFieldZoneStatsToCardInfo", body)


if __name__ == "__main__":
    unittest.main()
