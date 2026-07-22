#!/usr/bin/env python3

import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
NEPTUNE_EFFECT = ROOT / "src_custom" / "permanent_effects" / "the_tyrant_neptune.c"
DUEL_HELPERS = ROOT / "src_custom" / "duel_helpers.c"
DUEL_HELPERS_H = ROOT / "include" / "duel_helpers.h"


def neptune_stats_from_tribute(tribute_atk, tribute_def):
    return tribute_atk, tribute_def


class TheTyrantNeptuneTests(unittest.TestCase):
    def test_uses_original_tribute_stats_without_doubling(self):
        atk, def_ = neptune_stats_from_tribute(2500, 2000)
        self.assertEqual((atk, def_), (2500, 2000))

    def test_sums_multiple_tributes(self):
        atk, def_ = neptune_stats_from_tribute(600 + 800, 600 + 700)
        self.assertEqual((atk, def_), (1400, 1300))

    def test_zero_tribute_stays_zero(self):
        atk, def_ = neptune_stats_from_tribute(0, 0)
        self.assertEqual((atk, def_), (0, 0))

    def test_capture_uses_printed_original_stats(self):
        source = NEPTUNE_EFFECT.read_text()
        capture_body = re.search(
            r"void TryCaptureTheTyrantNeptuneTributeFromZone\([^)]*\)\s*\{(.*?)^\}",
            source,
            re.S | re.M,
        )
        self.assertIsNotNone(capture_body)
        self.assertIn("SetCardInfo(cardId);", capture_body.group(1))
        self.assertNotIn("SetFinalStat", capture_body.group(1))

    def test_finish_opens_gy_effect_copy_picker(self):
        source = NEPTUNE_EFFECT.read_text()
        finish_body = re.search(
            r"void FinishTheTyrantNeptuneTributeSummon\([^)]*\)\s*\{(.*?)^\}",
            source,
            re.S | re.M,
        )
        self.assertIsNotNone(finish_body)
        body = finish_body.group(1)
        self.assertIn("TryCopyEffectFromTributedMonsters", body)
        self.assertIn("RefreshFieldMonsterStatOverlays();", body)
        self.assertIn("UpdateDuelGfxExceptField();", body)
        self.assertLess(
            body.index("UpdateDuelGfxExceptField();"),
            body.index("ShowTheTyrantNeptuneActivationText();"),
        )

    def test_finish_requires_captured_tribute_stats(self):
        source = NEPTUNE_EFFECT.read_text()
        finish_body = re.search(
            r"void FinishTheTyrantNeptuneTributeSummon\([^)]*\)\s*\{(.*?)^\}",
            source,
            re.S | re.M,
        )
        self.assertIsNotNone(finish_body)
        body = finish_body.group(1)
        self.assertIn("gTheTyrantNeptuneTributeCount", body)
        self.assertNotIn("gNumTributes != 0", body)

    def test_set_pending_true_does_not_clear_captured_stats(self):
        source = NEPTUNE_EFFECT.read_text()
        set_body = re.search(
            r"void SetTheTyrantNeptunePendingSummon\([^)]*\)\s*\{(.*?)^\}",
            source,
            re.S | re.M,
        )
        self.assertIsNotNone(set_body)
        body = set_body.group(1)
        self.assertIn("if (!pending)", body)
        self.assertNotIn("else if", body)

    def test_tracks_tribute_ids_for_trunk_selection(self):
        source = NEPTUNE_EFFECT.read_text()
        self.assertIn("StoreTributeId", source)
        self.assertIn("LoadTributedEffectMonsterMenu", source)
        self.assertIn("PlayerPickCopiedEffectCard", source)
        self.assertIn("DeckMenu_BeginDuelTrunkView", source)
        self.assertIn("EFFECT_CARD", source)

    def test_trunk_picker_saves_deck_before_overwriting_gdeckmenu(self):
        source = NEPTUNE_EFFECT.read_text()
        player_pick = re.search(
            r"static u16 PlayerPickCopiedEffectCard\(void\)\s*\{(.*?)^\}",
            source,
            re.S | re.M,
        )
        self.assertIsNotNone(player_pick)
        body = player_pick.group(1)
        save_at = body.index("savedDeckMenu")
        load_at = body.index("LoadTributedEffectMonsterMenu")
        self.assertLess(save_at, load_at)

    def test_neptune_uses_generic_copied_passive_api(self):
        neptune = NEPTUNE_EFFECT.read_text()
        helpers_h = DUEL_HELPERS_H.read_text()
        helpers_c = DUEL_HELPERS.read_text()
        self.assertIn("Duel_CopiedPassiveAtkBonus", neptune)
        self.assertNotIn("LYRILUSC_INDEPENDENT_NIGHTINGALE", neptune)
        self.assertNotIn("THEBAN_NIGHTMARE", neptune)
        self.assertIn("Duel_EffectHostCardId", helpers_h)
        self.assertIn("Duel_ZoneEffectCardId", helpers_h)
        self.assertIn("Duel_ZoneHasEffectOfCard", helpers_h)
        self.assertIn("Duel_CopiedPassiveAtkBonus", helpers_h)
        self.assertIn("Duel_BeginCopiedEffectIdentity", helpers_h)
        self.assertIn("sCopiedPassiveAtkBonuses", helpers_c)

    def test_neptune_applies_stage_to_dynamic_stats(self):
        """Stage comes from ApplyFieldZoneStats after dynamic path (Hourglass etc.)."""
        card_hooks = (ROOT / "src_custom" / "card_hooks.c").read_text()
        apply_match = re.search(
            r"void ApplyFieldZoneStatsToCardInfo\([^)]*\)\s*\{",
            card_hooks,
        )
        self.assertIsNotNone(apply_match)
        start = apply_match.end()
        depth = 1
        index = start
        while index < len(card_hooks) and depth:
            if card_hooks[index] == "{":
                depth += 1
            elif card_hooks[index] == "}":
                depth -= 1
            index += 1
        apply_body = card_hooks[start : index - 1]
        dyn_pos = apply_body.index("Duel_TryApplyDynamicZoneStats(zone)")
        after_dyn = apply_body[dyn_pos : dyn_pos + 500]
        self.assertIn("ComputeFinalStage(zone)", after_dyn)
        self.assertIn("GetStageModifiedStat_Hook", after_dyn)
        helpers_h = DUEL_HELPERS_H.read_text()
        self.assertIn("Duel_StageModifiedStat", helpers_h)

    def test_passives_register_copied_atk_bonus(self):
        nightingale = (
            ROOT / "src_custom" / "activated_effects" / "lyrilusc_independent_nightingale.c"
        ).read_text()
        theban = (ROOT / "src_custom" / "permanent_effects" / "theban_nightmare.c").read_text()
        helpers_c = DUEL_HELPERS.read_text()
        self.assertIn("LyriluscIndependentNightingale_CopiedAtkBonus", nightingale)
        self.assertIn("Duel_EffectHostCardId", nightingale)
        self.assertIn("Duel_ZoneHasEffectOfCard", nightingale)
        self.assertNotIn("the_tyrant_neptune.h", nightingale)
        self.assertIn("ThebanNightmare_CopiedAtkBonus", theban)
        self.assertNotIn("the_tyrant_neptune.h", theban)
        self.assertIn("LyriluscIndependentNightingale_CopiedAtkBonus", helpers_c)
        self.assertIn("ThebanNightmare_CopiedAtkBonus", helpers_c)


if __name__ == "__main__":
    unittest.main()
