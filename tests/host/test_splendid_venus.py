#!/usr/bin/env python3

"""Validate Splendid Venus stage debuff and negation immunity wiring."""

import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

COMPUTE_FINAL_STAGE_SOURCE = ROOT / "src_custom" / "code_803F02C_hooks.c"
SPLENDID_VENUS_SOURCE = ROOT / "src_custom" / "permanent_effects" / "splendid_venus.c"
DUEL_HELPERS_SOURCE = ROOT / "src_custom" / "duel_helpers.c"
NEGATION_IMMUNITY_SOURCE = ROOT / "src_custom" / "negation_immunity.c"
TRAP_EFFECT_HOOKS_SOURCE = ROOT / "src_custom" / "trap_effect_hooks.c"


def extract_function_body(source: str, function_name: str) -> str:
    pattern = rf"(?:void|u8|int|s8|enum\s+\w+\s+\w+\s+|enum\s+\w+\s+)\s*{re.escape(function_name)}\s*\([^)]*\)\s*\{{"
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


class TestSplendidVenus(unittest.TestCase):
    def test_compute_final_stage_applies_venus_stage_adjust(self):
        body = extract_function_body(
            COMPUTE_FINAL_STAGE_SOURCE.read_text(), "ComputeFinalStage"
        )
        self.assertIn("SplendidVenus_AdjustStage", body)

    def test_venus_stage_adjust_uses_fairy_type_gate(self):
        body = extract_function_body(
            SPLENDID_VENUS_SOURCE.read_text(), "SplendidVenus_AdjustStage"
        )
        self.assertIn("TYPE_FAIRY", body)
        self.assertIn("stage - 1", body)

    def test_spell_trap_chain_respects_venus_protection(self):
        helpers = DUEL_HELPERS_SOURCE.read_text()
        providers = NEGATION_IMMUNITY_SOURCE.read_text()
        self.assertIn("Duel_DuelistActivationsProtectedFromNegation", helpers)
        self.assertIn("Duel_IsOriginActivationProtectedFromNegation", helpers)
        self.assertNotIn("SplendidVenus", helpers)
        self.assertIn("TheSplendidVenus_DuelistHasNegationImmunity", providers)
        spell_start = helpers.find("Duel_TryResolveSpellThroughTrapsEx")
        trap_start = helpers.find("Duel_TryResolveTrapThroughTraps")
        self.assertNotEqual(spell_start, -1)
        self.assertNotEqual(trap_start, -1)
        spell_body = helpers[spell_start : helpers.find("\n}", spell_start) + 2]
        trap_body = helpers[trap_start : helpers.find("\n}", trap_start) + 2]
        self.assertIn("Duel_IsOriginActivationProtectedFromNegation", spell_body)
        self.assertIn("Duel_IsOriginActivationProtectedFromNegation", trap_body)

    def test_is_trap_triggered_skips_protected_origin(self):
        source = TRAP_EFFECT_HOOKS_SOURCE.read_text()
        start = source.find("IsTrapTriggered__Replacement")
        self.assertNotEqual(start, -1)
        body = source[start : source.find("\n}", start) + 2]
        self.assertIn("Duel_IsOriginActivationProtectedFromNegation", body)


if __name__ == "__main__":
    unittest.main()
