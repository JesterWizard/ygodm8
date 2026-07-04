"""Host checks for Executor Makyura trap set/activate effect."""

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text()


class TestExecutorMakyura(unittest.TestCase):
    def test_manifest_entry(self):
        manifest = read("tools/card_data_manifest.json")
        self.assertIn('"card_const": "EXECUTOR_MAKYURA"', manifest)
        self.assertIn('"popup_1": "This turn, you can activate eligible Trap Cards from your hand."', manifest)

    def test_graveyard_send_arms_effect(self):
        passive = read("src_custom/card_passive_hooks.c")
        tribute = read("src_custom/embodiment_of_apophis_hooks.c")
        self.assertIn("TryArmExecutorMakyuraOnGraveyardSend(turn, zone->id)", passive)
        self.assertIn("TryShowPendingExecutorMakyuraPopup()", passive)
        self.assertIn("TryArmExecutorMakyuraOnGraveyardSendFixed(turn, cardId)", tribute)
        self.assertIn("TryShowPendingExecutorMakyuraPopup()", tribute)

    def test_popup_deferred_until_after_graveyard_clear(self):
        source = read("src_custom/permanent_effects/executor_makyura.c")
        arm_fn = source.split("void TryArmExecutorMakyuraOnGraveyardSendFixed")[1].split(
            "void TryShowPendingExecutorMakyuraPopup"
        )[0]
        self.assertIn("gExecutorMakyuraPendingPopup = TRUE", arm_fn)
        self.assertNotIn("Duel_ShowCardEffectText", arm_fn)
        self.assertIn("TryShowPendingExecutorMakyuraPopup()", read("src_custom/card_passive_hooks.c"))

    def test_uses_card_effect_text_popup(self):
        source = read("src_custom/permanent_effects/executor_makyura.c")
        self.assertIn("Duel_ShowCardEffectText(EXECUTOR_MAKYURA, CARD_EFFECT_TEXT_EXECUTOR_MAKYURA_POPUP_1)", source)

    def test_allows_royal_decree_manual_activation(self):
        source = read("src_custom/permanent_effects/executor_makyura.c")
        self.assertIn("case TRAP_ROYAL_DECREE:", source)
        self.assertIn("case ROYAL_DECREE:", source)
        self.assertNotIn("return trapEffect != 0", source)

    def test_hand_uses_set_flow_not_direct_activation(self):
        hand_hooks = read("src_custom/code_8043EF4_hooks.c")
        self.assertNotIn("TryActivateExecutorMakyuraTrapFromHand", hand_hooks)
        self.assertIn("sub_80442AC();", hand_hooks)

    def test_backrow_activation_wired(self):
        source = read("src_custom/code_8043EF4_hooks.c")
        self.assertIn("TryActivateExecutorMakyuraTrapFromBackrow(gDuelCursor.currentY, gDuelCursor.currentX)", source)

    def test_jar_of_greed_backrow_only(self):
        source = read("src_custom/permanent_effects/executor_makyura.c")
        self.assertIn("ActivateJarOfGreedFromZone(originZone, ACTIVE_DUELIST)", source)
        self.assertIn("ActivateMakyuraContinuousTrap", source)
        self.assertIn("case SOLEMN_WISHES:", source)

    def test_turn_state_reset(self):
        turn_hooks = read("src_custom/turn_effect_hooks.c")
        self.assertIn("ResetExecutorMakyuraTurnState()", turn_hooks)
        ram_map = read("asm/ram_map_iwram.s")
        self.assertIn("gExecutorMakyuraActivePlayer", ram_map)
        self.assertIn("gExecutorMakyuraPendingPopup", ram_map)


if __name__ == "__main__":
    unittest.main()
