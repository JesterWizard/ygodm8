import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EFFECT = ROOT / "src_custom" / "spell_effects" / "swords_of_revealing_light.c"
HOOKS = ROOT / "src_custom" / "code_803F02C_hooks.c"
DUEL_MAIN_HOOKS = ROOT / "src_custom" / "duel_main_hooks.c"
LYNJUMP = ROOT / "src_custom" / "LynJump.event"


class SwordsOfRevealingLightTests(unittest.TestCase):
    def test_activation_clears_effect_text_state(self):
        source = EFFECT.read_text()
        self.assertIn("Duel_ShowEffectText(SWORDS_OF_REVEALING_LIGHT)", source)
        self.assertIn("ResetCardEffectTextData();", source)

    def test_decrement_uses_zone_blocked_duelist(self):
        source = HOOKS.read_text()
        self.assertIn("FindActiveSorlZone", source)
        self.assertIn("GetSorlBlockedDuelistByZone(sorlZone)", source)
        self.assertNotIn("GetBlockedDuelistForSorlCounter", source)
        self.assertNotIn("GetSorlZoneForBlockedDuelist", source)

    def test_decrement_runs_after_blocked_duelist_turn(self):
        source = DUEL_MAIN_HOOKS.read_text()
        hooks = HOOKS.read_text()
        self.assertIn("Sorl_TryDecrementAfterTurnEnd()", source)
        self.assertIn("gSorlSkipDecrementAfterActivation", hooks)
        self.assertIn("Sorl_MarkActivatedThisTurn", hooks)

    def test_decrement_uses_fixed_duelist_battle_state(self):
        source = HOOKS.read_text()
        self.assertIn("gDuel.duelistbattleState[blockedDuelist].sorlTurns", source)
        self.assertIn("gDuel.duelistbattleState[WhoseTurn()].sorlTurns", source)

    def test_remain_text_shows_turn_count(self):
        hooks = HOOKS.read_text()
        effect = EFFECT.read_text()
        lynjump = LYNJUMP.read_text()
        self.assertIn("#0more turn#1", hooks)
        self.assertIn("#0more turns#1", hooks)
        self.assertIn("Sorl_MarkActivatedThisTurn();", effect)
        self.assertIn("TryDisplaySorlTurnsRemainingText__Replacement", hooks)
        self.assertIn("Sorl_ShowTurnsRemainingText(turns)", hooks)
        self.assertIn("ORG $2549C", lynjump)
        self.assertIn("TryDisplaySorlTurnsRemainingText__Replacement", lynjump)


if __name__ == "__main__":
    unittest.main()
