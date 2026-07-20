"""Effect data system follow-ups: OPT migrate, Phase 4b, events, scripts."""

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
        src = read("src_custom/effect_system/effect_scripts.c")
        self.assertIn('../generated/effect_scripts_table.inc', src)
        self.assertIn("EFFECT_SCRIPT_REQUIRE_COND", read("include/effect_scripts.h"))
        self.assertIn("EFFECT_SCRIPT_DESTROY_FIRST_BY_COND", read("include/effect_scripts.h"))

    def test_legacy_meta_expanded(self):
        src = read("src_custom/effect_system/effect_scripts.c")
        self.assertIn("SPELL_EFFECT_HEAVY_STORM", src)
        self.assertIn("SPELL_EFFECT_HARPIES_FEATHER_DUSTER", src)
        self.assertIn("SPELL_EFFECT_RESTRUCTER_REVOLUTION", src)

    def test_on_damage_calc_emitted(self):
        src = read("src_custom/card_hooks.c")
        self.assertIn("EFFECT_EVENT_ON_DAMAGE_CALC", src)

    def test_field_change_event(self):
        hdr = read("include/effect_events.h")
        self.assertIn("EFFECT_EVENT_ON_FIELD_CHANGE", hdr)
        self.assertIn("EffectEvent_EnsureInit", hdr)
        events = read("src_custom/effect_system/effect_events.c")
        self.assertIn("Duel_CheckRivalryOfWarlordsAfterFieldChange", events)
        helpers = read("src_custom/duel_helpers.c")
        self.assertIn("EFFECT_EVENT_ON_FIELD_CHANGE", helpers)


if __name__ == "__main__":
    unittest.main()
