"""Host checks for AI normal-spell activation target gating."""

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text()


class TestAiSpellTargets(unittest.TestCase):
    def test_feather_duster_requires_opponent_backrow(self):
        source = read("src_custom/ai_spell_targets.c")
        self.assertIn("SPELL_EFFECT_HARPIES_FEATHER_DUSTER", source)
        self.assertIn("INACTIVE_DUELIST_BACKROW", source)

    def test_force_activation_uses_shared_helper(self):
        hooks = read("src_custom/ai_hooks.c")
        self.assertIn("AiNormalSpellHasActivationTargets(zone->id)", hooks)
        self.assertNotIn("SetNormalSpellHasActivationTargets", hooks)

    def test_fast_ai_rejects_targetless_normal_spell_activation(self):
        source = read("src_custom/ai_sim_fast.c")
        self.assertIn("AiNormalSpellHasActivationTargets(cardId)", source)
        self.assertIn("Duel_IsCardActivationBlocked(cardId)", source)

    def test_fast_ai_prune_reject_classes(self):
        source = read("src_custom/ai_sim_fast.c")
        hooks = read("src_custom/ai_hooks.c")
        self.assertIn("AiSimRejectEmptyTributes", source)
        self.assertIn("AiSimRejectNoopPosition", source)
        self.assertIn("AiSimRejectIllegalAttack", source)
        self.assertIn("AiSimIsWithTrapAction", source)
        self.assertIn("AiSimScanBoard", source)
        self.assertIn("AiSimMarkLethalFound", source)
        self.assertIn("AiSimTryRecordLightAttack", source)
        self.assertIn("AiSimLightFaceUpAttackPriority", source)
        self.assertIn("AI_FAST_FULL_SIM_BUDGET", source)
        self.assertIn("Board_PreferredEmptyMonsterTurnCol", source)
        self.assertIn("summoningBlocked", source)
        self.assertIn("AiSimQuickReject", source)
        self.assertNotIn("AiSimFastHeuristicScore", source)
        self.assertIn("AiSimQuickReject(i)", hooks)
        self.assertIn("AiSimTryRecordLightAttack", hooks)
        self.assertIn("AiSimFullSimBudget", hooks)
        self.assertNotIn("AiSimulateAllCandidateActionsFast", hooks)

    def test_fast_ai_skips_gy_refresh_on_turn(self):
        main = read("src_custom/ai_main_hooks.c")
        self.assertIn("RefreshDisplay", main)
        self.assertIn("!gRuntimeConfig.fast_ai", main)
        self.assertIn("gHideEffectText = 1", main)

    def test_normal_spell_targets_respect_activation_block(self):
        source = read("src_custom/ai_spell_targets.c")
        self.assertIn("Duel_IsCardActivationBlocked(cardId)", source)

    def test_ai_spell_activation_skips_blocked_cards(self):
        hooks = read("src_custom/ai_spell_hooks.c")
        self.assertIn("Duel_IsCardActivationBlocked(spellId)", hooks)
        self.assertIn("Duel_IsCardActivationBlocked(cardId)", hooks)

    def test_ai_simulation_saves_wicked_avatar_lock(self):
        source = read("src_custom/ai_simulation_hooks.c")
        self.assertIn("gAiSimSavedTheWickedAvatarLockFixedDuelist", source)
        self.assertIn("gTheWickedAvatarLockTurnsRemaining = gAiSimSavedTheWickedAvatarLockTurnsRemaining", source)

    def test_wicked_avatar_lock_arms_on_tribute_placement(self):
        hooks = read("src_custom/code_8043EF4_hooks.c")
        self.assertIn("FinishTheWickedAvatarTributeSummon(", hooks)
        avatar = read("src_custom/permanent_effects/the_wicked_avatar.c")
        self.assertNotIn("GetPendingTributeSummonCardId() != THE_WICKED_AVATAR", avatar)

    def test_wicked_avatar_lock_not_gated_on_tribute_count(self):
        avatar = read("src_custom/permanent_effects/the_wicked_avatar.c")
        self.assertIn("FinishTheWickedAvatarTributeSummon(", avatar)
        self.assertNotIn("GetPendingSummonTributeCount()", avatar)
        self.assertNotIn("GetNumRequiredTributesWithCostDown", avatar)

    def test_wicked_avatar_lock_decrements_using_whose_turn(self):
        avatar = read("src_custom/permanent_effects/the_wicked_avatar.c")
        self.assertIn("OtherDuelist(WhoseTurn())", avatar)
        self.assertNotIn("FixedDuelistForTurnDuelist(INACTIVE_DUELIST)", avatar)


if __name__ == "__main__":
    unittest.main()
