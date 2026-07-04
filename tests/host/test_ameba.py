import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
AMEBA = ROOT / "src_custom" / "permanent_effects" / "ameba.c"
GFX_HOOKS = ROOT / "src_custom" / "field_spell_gfx_hooks.c"
DUEL_HELPERS = ROOT / "src_custom" / "duel_helpers.c"
AI_SIM = ROOT / "src_custom" / "ai_simulation_hooks.c"
AI_SPELL_TARGETS = ROOT / "src_custom" / "ai_spell_targets.c"


class TestAmeba(unittest.TestCase):
    def test_control_switch_deals_damage_to_new_controller(self):
        source = AMEBA.read_text()
        self.assertIn("AMEBA_CONTROL_SWITCH_DAMAGE 2000", source)
        self.assertIn("Duel_NotifyMonsterControlSwitched", source)
        self.assertIn("Duel_FixedDuelistForMonsterRow(newFixedRow)", source)
        self.assertIn("Duel_FlushMonsterControlSwitchEffects", source)
        self.assertIn("gAmebaFlushing", source)

    def test_ai_sim_does_not_leave_stale_pending_burns(self):
        ameba = AMEBA.read_text()
        sim = AI_SIM.read_text()
        self.assertIn("gHideEffectText == TRUE", ameba)
        self.assertIn("gAiSimSavedAmebaPendingCount", sim)
        self.assertIn("gAmebaPendingCount = gAiSimSavedAmebaPendingCount", sim)

    def test_flush_deferred_until_effect_resolve_ends(self):
        gfx = GFX_HOOKS.read_text()
        helpers = DUEL_HELPERS.read_text()
        self.assertIn("!Duel_IsSpellEffectResolving()", gfx)
        self.assertIn("!Duel_IsMonsterEffectResolving()", gfx)
        self.assertIn("Duel_FlushMonsterControlSwitchEffects();", gfx)
        self.assertLess(
            gfx.index("RunVanillaUpdateDuelGfxExceptField();"),
            gfx.index("Duel_FlushMonsterControlSwitchEffects();"),
        )
        self.assertIn("return sSpellEffectResolveDepth > 0;", helpers)
        self.assertNotIn("gTrapEffectData.trapCardId", helpers.split("Duel_IsSpellEffectResolving")[1][:120])

    def test_control_switch_hooks_queue_without_extra_gfx(self):
        creature_swap = (ROOT / "src_custom" / "spell_effects" / "creature_swap.c").read_text()
        brain_control = (ROOT / "src_custom" / "spell_effects" / "brain_control.c").read_text()
        self.assertIn("Duel_NotifyMonsterControlSwitched", creature_swap)
        self.assertNotIn("Duel_FlushMonsterControlSwitchEffects", creature_swap)
        self.assertNotIn("UpdateDuelGfxExceptField();", brain_control)
        self.assertNotIn("Duel_FlushMonsterControlSwitchEffects", brain_control)

    def test_ai_skips_mind_control_spells_without_targets(self):
        source = AI_SPELL_TARGETS.read_text()
        self.assertIn("SPELL_EFFECT_CHANGE_OF_HEART", source)
        self.assertIn("SPELL_EFFECT_BRAIN_CONTROL", source)
        self.assertIn("INACTIVE_DUELIST_MONSTER_ROW", source)


if __name__ == "__main__":
    unittest.main()
