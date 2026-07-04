"""Host checks for The Supremacy Sun manifest and standby revival effect."""

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text()


class TestTheSupremacySun(unittest.TestCase):
    def test_manifest_entry(self):
        manifest = read("tools/card_data_manifest.json")
        self.assertIn('"card_const": "THE_SUPREMACY_SUN"', manifest)
        self.assertIn('"password": [5, 1, 4, 0, 2, 9, 0, 8]', manifest)
        self.assertIn("Cannot be Special Summoned except by its own effect", manifest)

    def test_standby_revive_effect(self):
        source = read("src_custom/turn_effects/the_supremacy_sun.c")
        self.assertIn("MarkTheSupremacySunDestroyedFromField", source)
        self.assertIn("TheSupremacySun_TryResolveStandbyRevive", source)
        self.assertIn("Duel_DiscardFromHand(turnDuelist, 1, NULL", source)
        self.assertIn("gTheSupremacySunOwnEffectSummon = TRUE", source)
        self.assertIn("Duel_ShowEffectTextTyped(THE_SUPREMACY_SUN, 9)", source)
        self.assertIn("zone->isFaceUp", source)

    def test_special_summon_block_and_bypass(self):
        helpers = read("src_custom/duel_helpers.c")
        self.assertIn("THE_SUPREMACY_SUN", helpers)
        self.assertIn("gTheSupremacySunOwnEffectSummon", helpers)
        self.assertIn("MarkTheSupremacySunDestroyedFromField", helpers)

    def test_graveyard_send_hooks_arm_revive(self):
        gy_send = read("src_custom/activated_effects/graveyard_draw_on_destroy.c")
        apophis = read("src_custom/embodiment_of_apophis_hooks.c")
        battle = read("src_custom/battle_damage_hooks.c")
        self.assertIn("MarkTheSupremacySunDestroyedFromField(zone)", gy_send)
        self.assertIn("MarkTheSupremacySunDestroyedFromField(zone)", apophis)
        self.assertIn("MarkTheSupremacySunDestroyedFromField(zone)", battle)

    def test_standby_window_not_cleared_on_opponent_turn(self):
        source = read("src_custom/turn_effects/the_supremacy_sun.c")
        resolve_body = source.split("void TheSupremacySun_TryResolveStandbyRevive(void)")[1]
        self.assertNotIn("hadWindow", resolve_body)
        self.assertIn("if (WhoseTurn() != d)", resolve_body)
        self.assertNotIn("for (d = 0; d < 2; d++) {\n    gTheSupremacySunArmed[d] = FALSE;", resolve_body)

    def test_turn_hooks_wired(self):
        hooks = read("src_custom/turn_effect_hooks.c")
        self.assertIn("TheSupremacySun_AgeStandbyFlags", hooks)
        self.assertIn("TheSupremacySun_TryResolveStandbyRevive", hooks)


if __name__ == "__main__":
    unittest.main()
