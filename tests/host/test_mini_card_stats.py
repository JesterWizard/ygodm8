#!/usr/bin/env python3

import json
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MINI_CARD_HOOKS = ROOT / "src_custom" / "mini_card_hooks.c"
MANIFEST = ROOT / "tools" / "card_data_manifest.json"

NON_MONSTER_TYPES = {"TYPE_SPELL", "TYPE_TRAP", "TYPE_RITUAL"}


def extract_function_body(source: str, function_name: str) -> str:
    match = re.search(rf"void {re.escape(function_name)}\([^)]*\)\s*\{{", source)
    if match is None:
        raise AssertionError(f"Could not find function {function_name}")

    start = match.end()
    depth = 1
    index = start
    while index < len(source) and depth:
        char = source[index]
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
        index += 1

    return source[start : index - 1]


class MiniCardStatOverlayTests(unittest.TestCase):
    def test_duel_stat_overlay_guard_uses_card_type_group(self):
        source = MINI_CARD_HOOKS.read_text()

        self.assertIn("ShouldShowMiniCardCombatStats", source)
        self.assertIn("GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER", source)
        self.assertIn("EmbodimentOfApophisZoneIsMonsterForm(zone)", source)

        for function_name in (
            "sub_80572A8__Replacement",
            "sub_805733C__Replacement",
        ):
            body = extract_function_body(source, function_name)
            self.assertIn("ShouldShowMiniCardCombatStats(arg1)", body)
            self.assertNotIn("gCardInfo.spellEffect != SPELL_EFFECT_MONSTER", body)

    def test_custom_spell_and_trap_cards_are_not_monster_type(self):
        manifest = json.loads(MANIFEST.read_text())
        custom_start = next(
            index
            for index, item in enumerate(manifest["cards"])
            if item["card_const"] == "SORCERER_OF_DARK_MAGIC"
        )

        spell_trap_cards = [
            item
            for item in manifest["cards"][custom_start:]
            if item["type"] in NON_MONSTER_TYPES
        ]
        self.assertTrue(spell_trap_cards, "Expected custom spell/trap cards past card 800.")

        for item in spell_trap_cards:
            with self.subTest(card_const=item["card_const"]):
                self.assertIn(item["type"], NON_MONSTER_TYPES)
                self.assertEqual(
                    item["atk"],
                    65535,
                    "Non-monster cards should keep placeholder ATK so duel overlays stay hidden.",
                )
                self.assertEqual(
                    item["def"],
                    65535,
                    "Non-monster cards should keep placeholder DEF so duel overlays stay hidden.",
                )


if __name__ == "__main__":
    unittest.main()
