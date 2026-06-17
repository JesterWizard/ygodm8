#!/usr/bin/env python3

import json
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MINI_CARD_HOOKS = ROOT / "src_custom" / "mini_card_hooks.c"
CARD_HOOKS = ROOT / "src_custom" / "card_hooks.c"
HOURGLASS_EFFECT = ROOT / "src_custom" / "activated_effects" / "hourglass_of_life.c"
MANIFEST = ROOT / "tools" / "card_data_manifest.json"

NON_MONSTER_TYPES = {"TYPE_SPELL", "TYPE_TRAP", "TYPE_RITUAL"}
# Trap cards that intentionally carry monster ATK/DEF for tokens they summon.
NON_MONSTER_STAT_EXCEPTIONS = {"OJAMA_TRIO"}


def extract_function_body(source: str, function_name: str) -> str:
    pattern = rf"(?:void|u8) {re.escape(function_name)}\([^)]*\)\s*\{{"
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


class MiniCardStatOverlayTests(unittest.TestCase):
    def test_field_stat_overlay_uses_field_zone_stats(self):
        source = MINI_CARD_HOOKS.read_text()

        for function_name in (
            "sub_80572A8__Replacement",
            "sub_805733C__Replacement",
        ):
            body = extract_function_body(source, function_name)
            with self.subTest(function_name=function_name):
                self.assertIn("ZoneShowsCombatStats(arg1)", body)
                self.assertIn("ApplyFieldZoneStatsToCardInfo(arg1)", body)
                self.assertNotIn("SetFinalStat(&gStatMod)", body)
                self.assertNotIn("gCardInfo.spellEffect != SPELL_EFFECT_MONSTER", body)

    def test_shared_combat_stat_gate_uses_card_type_group(self):
        card_hooks = CARD_HOOKS.read_text()
        mini_card_hooks = MINI_CARD_HOOKS.read_text()

        self.assertIn("ZoneShowsCombatStats", card_hooks)
        self.assertIn("GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER", card_hooks)
        self.assertIn("EmbodimentOfApophisZoneIsMonsterForm(zone)", card_hooks)

        apply_body = extract_function_body(card_hooks, "ApplyFieldZoneStatsToCardInfo")
        self.assertIn("ZoneShowsCombatStats(zone)", apply_body)
        self.assertIn("GetStageModifiedStat_Hook", apply_body)
        self.assertIn("ComputeFinalStage(zone)", apply_body)
        self.assertIn("gSetFinalStatZone = NULL", apply_body)
        self.assertNotIn("SetFinalStat(&statMod)", apply_body)
        self.assertNotIn("GetFinalStage(zone)", apply_body)
        self.assertNotIn("gCardInfo.spellEffect != SPELL_EFFECT_MONSTER", apply_body)

        set_final_body = extract_function_body(card_hooks, "SetFinalStat__Replacement")
        self.assertIn("ApplyGreatMajuGarzettStatsToCardInfo(ptr)", set_final_body)
        self.assertIn("GetTypeGroup(ptr->card) == TYPE_GROUP_MONSTER", set_final_body)
        self.assertIn("gSetFinalStatZone->id == ptr->card", set_final_body)
        self.assertIn("ComputeFinalStage(gSetFinalStatZone)", set_final_body)
        self.assertNotIn("GetFinalStage(gSetFinalStatZone)", set_final_body)
        self.assertNotIn("gCardInfo.spellEffect == SPELL_EFFECT_MONSTER", set_final_body)

        self.assertNotIn("ShouldShowMiniCardCombatStats", mini_card_hooks)

    def test_hourglass_refreshes_field_stat_overlays(self):
        source = HOURGLASS_EFFECT.read_text()
        self.assertIn("Duel_IncrementPermStageOnDuelistMonsters(ACTIVE_DUELIST)", source)
        self.assertIn("Duel_ChangeLp(ACTIVE_DUELIST, -1000, TRUE)", source)
        self.assertIn("Duel_RefreshMonsterStatOverlays();", source)
        text_pos = source.index("Duel_ShowEffectTextTyped(HOURGLASS_OF_LIFE, 2);")
        self.assertIn("Duel_IncrementPermStageOnDuelistMonsters(ACTIVE_DUELIST)", source[:text_pos])
        self.assertIn("Duel_RefreshMonsterStatOverlays();", source[:text_pos])

    def test_refresh_field_monster_stat_overlays_updates_atk_and_def_tiles(self):
        source = MINI_CARD_HOOKS.read_text()
        body = extract_function_body(source, "RefreshFieldMonsterStatOverlays")

        self.assertIn("sub_80572A8(tilePtr, zone)", body)
        self.assertIn("sub_805733C(tilePtr, zone)", body)
        self.assertIn("StampFieldCardStage(tilePtr, ComputeFinalStage(zone))", body)

    def test_battle_action_stats_resync_from_field_zones(self):
        card_hooks = CARD_HOOKS.read_text()
        fairy_box = (ROOT / "src_custom" / "trap_effects" / "fairy_box.c").read_text()

        refresh_body = extract_function_body(card_hooks, "RefreshPendingBattleActionStatsFromZones")
        helper_body = extract_function_body(card_hooks, "RefreshActionCardStatsFromZone")
        self.assertIn("ApplyFieldZoneStatsToCardInfo(zone)", helper_body)
        self.assertIn("sActionData.playerCardAtkOrLifePointsMod", refresh_body)
        self.assertIn("sActionData.opponentCardAtkOrLifePointsMod", refresh_body)
        self.assertIn("RefreshPendingBattleActionStatsFromZones();", fairy_box)

    def test_custom_spell_and_trap_cards_are_not_monster_type(self):
        manifest = json.loads(MANIFEST.read_text())
        custom_start = next(
            index
            for index, item in enumerate(manifest["cards"])
            if item["card_const"] == "SORCERER_OF_DARK_MAGIC"
        )

        spell_trap_cards = [
            item
            for item in manifest["cards"][custom_start:]
            if item["type"] in NON_MONSTER_TYPES
        ]
        self.assertTrue(spell_trap_cards, "Expected custom spell/trap cards past card 800.")

        for item in spell_trap_cards:
            if item["card_const"] in NON_MONSTER_STAT_EXCEPTIONS:
                continue
            with self.subTest(card_const=item["card_const"]):
                self.assertIn(item["type"], NON_MONSTER_TYPES)
                self.assertEqual(
                    item["atk"],
                    65535,
                    "Non-monster cards should keep placeholder ATK so duel overlays stay hidden.",
                )
                self.assertEqual(
                    item["def"],
                    65535,
                    "Non-monster cards should keep placeholder DEF so duel overlays stay hidden.",
                )


if __name__ == "__main__":
    unittest.main()
