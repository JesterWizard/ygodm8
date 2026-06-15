#!/usr/bin/env python3

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EFFECT = ROOT / "src_custom" / "spell_effects" / "graceful_dice.c"
MANIFEST = ROOT / "tools" / "card_data_manifest.json"


class GracefulDiceTests(unittest.TestCase):
    def test_multiplies_low_atk_monsters_by_dice_roll(self):
        source = EFFECT.read_text()
        self.assertIn("GRACEFUL_DICE_MAX_ATK 500", source)
        self.assertIn("RandRangeU8(1, 6)", source)
        self.assertIn("diceRoll - 1", source)
        self.assertIn("AddRiryokuAtkDelta", source)
        self.assertIn("Duel_ShowEffectText(GRACEFUL_DICE)", source)

    def test_manifest_describes_custom_effect(self):
        manifest = MANIFEST.read_text()
        self.assertIn("500 or less ATK have their ATK multiplied", manifest)
        self.assertNotIn("gain ATK/DEF equal to the result x 100", manifest)

    def test_get_final_stage_leaves_zone_for_set_final_stat(self):
        hooks = (ROOT / "src_custom" / "code_803F02C_hooks.c").read_text()
        body = extract_function_body(hooks, "GetFinalStage__Replacement")
        self.assertIn("gSetFinalStatZone = zone", body)
        self.assertNotIn("gSetFinalStatZone = NULL", body)


def extract_function_body(source: str, function_name: str) -> str:
    import re

    pattern = rf"(?:void|u8|int) {re.escape(function_name)}\([^)]*\)\s*\{{"
    match = re.search(pattern, source)
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


if __name__ == "__main__":
    unittest.main()
