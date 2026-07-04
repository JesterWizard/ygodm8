"""Host checks for The Blazing Mars manifest and field burn effect."""

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text()


class TestTheBlazingMars(unittest.TestCase):
    def test_manifest_entry(self):
        manifest = read("tools/card_data_manifest.json")
        self.assertIn('"card_const": "THE_BLAZING_MARS"', manifest)
        self.assertIn('"monsterEffect": "MONSTER_EFFECT_THE_BLAZING_MARS"', manifest)
        self.assertIn('"password": [1, 5, 0, 3, 3, 5, 2, 5]', manifest)
        self.assertIn('"effect_usage": "once_per_turn"', manifest)
        self.assertIn('"popup_2":', manifest)

    def test_field_burn_effect(self):
        source = read("src_custom/activated_effects/the_blazing_mars.c")
        self.assertIn("CARD_EFFECT_TEXT_THE_BLAZING_MARS_POPUP_2", source)
        self.assertIn("SendOtherMonstersToGrave", source)
        self.assertIn("THE_BLAZING_MARS_BURN_PER_MONSTER", source)
        self.assertIn("Duel_ChangeLp(INACTIVE_DUELIST, -damage", source)
        self.assertIn("gFixedZones[gMonEffect.row]", source)
        self.assertIn("CanUseMonsterEffect(zone)", source)

    def test_banish_special_summon_stubbed(self):
        source = read("src_custom/activated_effects/the_blazing_mars.c")
        self.assertIn("CanSpecialSummonTheBlazingMarsFromHandOrGrave", source)
        self.assertIn("return FALSE", source)

    def test_monster_effect_hooks_wired(self):
        hooks = read("src_custom/monster_effect_hooks.c")
        self.assertIn("MONSTER_EFFECT_THE_BLAZING_MARS", hooks)
        self.assertIn("CanActivateTheBlazingMars", hooks)
        self.assertIn("ActivateTheBlazingMarsEffect", hooks)

    def test_face_up_menu_whitelist(self):
        hooks = read("src_custom/monster_effect_hooks.c")
        self.assertIn("|| zone->id == THE_BLAZING_MARS", hooks)

    def test_uses_standard_once_per_turn_mark(self):
        hooks = read("src_custom/monster_effect_hooks.c")
        activate_body = hooks.split("static void ActivateMonsterEffectBody", 1)[1]
        mark_pos = activate_body.index("MarkMonsterEffectUsed(zone);")
        mars_pos = activate_body.index("ActivateTheBlazingMarsEffect();")
        self.assertLess(mark_pos, mars_pos)


if __name__ == "__main__":
    unittest.main()
