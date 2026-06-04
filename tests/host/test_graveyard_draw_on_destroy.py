#!/usr/bin/env python3

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
CARD_NONE = 0
SANGAN = 0x0030
WITCH_OF_THE_BLACK_FOREST = 0x023E
ACTIVE_DUELIST = 0
INACTIVE_DUELIST = 1
FLAG_GRAVEYARD_PLAYER = 1


def card_triggers(card_id: int) -> bool:
    return card_id in (SANGAN, WITCH_OF_THE_BLACK_FOREST)


class PermanentGraveyardDrawModel:
    """Host-side model of graveyard rows 6/7 permanent-effect timing."""

    def __init__(self):
        self.graveyard = {ACTIVE_DUELIST: CARD_NONE, INACTIVE_DUELIST: CARD_NONE}
        self.hide_effect_text = False
        self.defer_battle = False
        self.hand_size = {ACTIVE_DUELIST: 0, INACTIVE_DUELIST: 0}
        self.resolved = []

    def send_to_graveyard(self, card_id: int, duelist: int):
        self.graveyard[duelist] = card_id

    def battle_destroy(self, card_id: int, duelist: int):
        self.send_to_graveyard(card_id, duelist)
        if card_triggers(card_id):
            self.defer_battle = True

    def should_activate(self, turn_row: int, card_id: int) -> bool:
        if self.defer_battle:
            return False
        if turn_row not in (6, 7):
            return False
        if not card_triggers(card_id):
            return False
        if turn_row == 7:
            return self.graveyard[INACTIVE_DUELIST] == card_id
        return self.graveyard[ACTIVE_DUELIST] == card_id

    def activate(self, turn_row: int, card_id: int, fixed_duelist: int):
        if not self.should_activate(turn_row, card_id):
            return
        if self.hand_size[fixed_duelist] < 5:
            self.hand_size[fixed_duelist] += 1
        self.graveyard[ACTIVE_DUELIST if turn_row == 6 else INACTIVE_DUELIST] = CARD_NONE
        self.resolved.append(("draw", fixed_duelist, card_id))
        if not self.hide_effect_text:
            self.resolved.append(("text", fixed_duelist, card_id))

    def try_activating_permanent_effects(self):
        for turn_row, duelist, fixed in (
            (6, ACTIVE_DUELIST, 0),
            (7, INACTIVE_DUELIST, 1),
        ):
            card_id = self.graveyard[duelist]
            if card_id == CARD_NONE:
                continue
            if self.should_activate(turn_row, card_id):
                self.activate(turn_row, card_id, fixed)

    def finish_battle_ui(self):
        self.defer_battle = False


class GraveyardDrawOnDestroyTests(unittest.TestCase):
    def test_graveyard_scan_after_battle_matches_phoenix_timing(self):
        model = PermanentGraveyardDrawModel()
        model.send_to_graveyard(SANGAN, ACTIVE_DUELIST)
        model.try_activating_permanent_effects()
        self.assertEqual(
            model.resolved,
            [("draw", 0, SANGAN), ("text", 0, SANGAN)],
        )

    def test_battle_destruction_waits_for_battle_ui(self):
        model = PermanentGraveyardDrawModel()
        model.battle_destroy(SANGAN, ACTIVE_DUELIST)
        model.try_activating_permanent_effects()
        self.assertEqual(model.resolved, [])
        self.assertTrue(model.defer_battle)

        model.finish_battle_ui()
        model.try_activating_permanent_effects()
        self.assertEqual(
            model.resolved,
            [("draw", 0, SANGAN), ("text", 0, SANGAN)],
        )

    def test_source_wires_battle_defer_and_finish(self):
        perm = (ROOT / "src_custom/permanent_effect_hooks.c").read_text()
        effect = (ROOT / "src_custom/activated_effects/graveyard_draw_on_destroy.c").read_text()
        battle = (ROOT / "src_custom/battle_damage_hooks.c").read_text()
        attack = (ROOT / "src_custom/code_8043EF4_hooks.c").read_text()
        gfx = (ROOT / "src_custom/code_8041C94_hooks.c").read_text()

        self.assertIn("gDeferGraveyardDrawBattleResolve", effect)
        self.assertIn("FinishGraveyardDrawBattleResolve", attack)
        self.assertIn("FinishGraveyardDrawBattleResolve", gfx)
        self.assertIn("CardDefersGraveyardEffectUntilBattleFinish", battle)
        self.assertIn("ShouldActivateGraveyardDrawOnDestroy", perm)
        self.assertIn("ActivateCardEffectText", effect)


if __name__ == "__main__":
    unittest.main()
