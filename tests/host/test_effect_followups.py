"""Effect data system follow-ups: OPT, Phase 4b, field/damage events, burns."""

from __future__ import annotations

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(rel: str) -> str:
    return (ROOT / rel).read_text(encoding="utf-8")


class TestEffectFollowups(unittest.TestCase):
    def test_no_append_data_opt_flags(self):
        hits = []
        for path in (ROOT / "src_custom").rglob("*.c"):
            text = path.read_text(encoding="utf-8")
            if "UsedThisTurn APPEND_DATA" in text:
                hits.append(str(path.relative_to(ROOT)))
        self.assertEqual(hits, [])

    def test_phase4b_manifest_and_generator(self):
        self.assertTrue((ROOT / "tools/effect_scripts_manifest.json").is_file())
        gen = read("tools/generate_effect_scripts.py")
        self.assertIn("effect_scripts_table.inc", gen)
        table = read("src_custom/generated/effect_scripts_table.inc")
        self.assertIn("ANCIENT_LEAF", table)
        self.assertIn("ONE_DAY_OF_PEACE", table)
        self.assertIn("SPARKS", table)
        self.assertIn("BURN_THROUGH_TRAPS", table)
        self.assertIn("METEOR_OF_DESTRUCTION", table)
        src = read("src_custom/effect_system/effect_scripts.c")
        self.assertIn('../generated/effect_scripts_table.inc', src)
        hdr = read("include/effect_scripts.h")
        self.assertIn("EFFECT_SCRIPT_REQUIRE_COND", hdr)
        self.assertIn("EFFECT_SCRIPT_DESTROY_FIRST_BY_COND", hdr)
        self.assertIn("EFFECT_SCRIPT_BURN_THROUGH_TRAPS", hdr)
        self.assertIn("EFFECT_SCRIPT_HEAL_THROUGH_TRAPS", hdr)
        self.assertIn("MOOYAN_CURRY", table)
        self.assertIn("HEAL_THROUGH_TRAPS", table)
        self.assertIn("DARK_HOLE", table)
        self.assertIn("RAIGEKI", table)
        self.assertIn("FUSION_SAGE", table)
        self.assertIn("WARRIOR_ELIMINATION", table)
        self.assertIn("HARPIES_FEATHER_DUSTER", table)
        self.assertIn("GOBLIN_THIEF", table)
        self.assertIn("UPSTART_GOBLIN", table)
        self.assertIn("RAIN_OF_MERCY", table)
        self.assertIn("HEAVY_STORM", table)
        self.assertIn("FINAL_DESTINY", table)
        self.assertIn("CRUSH_CARD", table)
        self.assertIn("RESTRUCTER_REVOLUTION", table)
        self.assertIn("BECKON_TO_DARKNESS", table)
        self.assertIn("DESTROY_ALL_HAND_EXCEPT_GODS", table)
        self.assertIn("DESTROY_MONSTERS_FINAL_ATK_GTE", table)
        self.assertIn("BURN_PER_OPP_HAND_CARD", table)
        self.assertIn("APPLY_STOP_DEFENSE", table)
        self.assertIn("AMAZONESS_FIGHTING_SPIRIT", table)
        self.assertIn("THUNDER_CRASH", table)
        self.assertIn("CHAOS_GREED", table)
        self.assertIn("ACTIVATE_CONTINUOUS_ZONE", table)
        self.assertIn("MILL_DECK_DIFFERENCE_TO_OPP", table)
        self.assertIn("DESTROY_INACTIVE_MONSTERS_THROUGH_TRAPS", table)
        self.assertIn("SEARCH_DECK_BY_ID", table)
        self.assertIn("DESTROY_ALL_MONSTERS_OF_TYPE", table)
        self.assertIn("STEAL_LP_THROUGH_TRAPS", table)
        self.assertIn("Duel_TryResolveBurnSpellThroughTraps", src)
        self.assertNotIn("sBurnThroughTrapsSpellId", src)

    def test_legacy_meta_expanded(self):
        src = read("src_custom/effect_system/effect_scripts.c")
        self.assertIn("SPELL_EFFECT_HEAVY_STORM", src)
        self.assertIn("SPELL_EFFECT_HARPIES_FEATHER_DUSTER", src)
        self.assertIn("SPELL_EFFECT_RESTRUCTER_REVOLUTION", src)
        self.assertIn("SPELL_EFFECT_MOOYAN_CURRY", src)
        self.assertIn("EFFECT_META_HEAL", read("include/effect_scripts.h"))

    def test_on_damage_calc_subscribed(self):
        src = read("src_custom/card_hooks.c")
        self.assertIn("EFFECT_EVENT_ON_DAMAGE_CALC", src)
        self.assertNotIn("ApplySkyscraperBattleAtkBoost", src)
        events = read("src_custom/effect_system/effect_events.c")
        self.assertIn("Effect_DispatchEvent", events)
        self.assertIn("EFFECT_EVENT_ON_FIELD_CHANGE", events)
        effect_c = read("src_custom/effect_system/effect.c")
        self.assertIn("ApplySkyscraperBattleAtkBoost", effect_c)
        self.assertIn("ApplyElementalHeroInfernoBattleAtkBoost", effect_c)
        self.assertIn("ApplyAmazonessFightingSpiritBattleAtkBoost", effect_c)
        self.assertTrue((ROOT / "src_custom/battle_effects/amazoness_fighting_spirit.c").is_file())
        battle = read("src_custom/battle_damage_hooks.c")
        self.assertIn("ApplyContinuousDestructionPunchBattleEffect", battle)

    def test_field_change_event(self):
        hdr = read("include/effect_events.h")
        self.assertIn("EFFECT_EVENT_ON_FIELD_CHANGE", hdr)
        self.assertIn("EffectEvent_EnsureInit", hdr)
        events = read("src_custom/effect_system/effect_events.c")
        self.assertIn("Duel_CheckRivalryOfWarlordsAfterFieldChange", events)
        helpers = read("src_custom/duel_helpers.c")
        self.assertIn("EFFECT_EVENT_ON_FIELD_CHANGE", helpers)
        # Direct Check* call sites outside the event bus / wrappers should be gone
        leftover = []
        for path in (ROOT / "src_custom").rglob("*.c"):
            if path.name in ("effect_events.c", "duel_helpers.c"):
                continue
            text = path.read_text(encoding="utf-8")
            if "Duel_CheckLevelLimitAreaBAfterFieldChange" in text:
                leftover.append(str(path.relative_to(ROOT)))
        self.assertEqual(leftover, [])


if __name__ == "__main__":
    unittest.main()
