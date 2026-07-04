"""Host checks for The Tripper Mercury tribute summon and stat drain."""

import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text()


def extract_function_body(source: str, name: str) -> str:
    match = re.search(rf"void {re.escape(name)}\([^)]*\)\s*\{{(.*?)^\}}", source, re.S | re.M)
    assert match, f"missing {name}"
    return match.group(1)


class TestTheTripperMercury(unittest.TestCase):
    def test_manifest_entry(self):
        manifest = read("tools/card_data_manifest.json")
        self.assertIn('"card_const": "THE_TRIPPER_MERCURY"', manifest)
        self.assertIn('"password": [0, 3, 9, 1, 2, 0, 6, 4]', manifest)

    def test_tribute_summon_activation(self):
        source = read("src_custom/permanent_effects/the_tripper_mercury.c")
        self.assertIn("FinishTheTripperMercuryTributeSummon", source)
        self.assertIn("CARD_EFFECT_TEXT_THE_TRIPPER_MERCURY_POPUP_1", source)
        self.assertIn("CARD_EFFECT_TEXT_THE_TRIPPER_MERCURY_POPUP_2", source)
        self.assertIn("ShowTheTripperMercuryDrainText", source)
        self.assertIn("TRIPPER_MERCURY_TRIBUTE_COUNT", source)

    def test_placement_hook_wired(self):
        source = read("src_custom/code_8043EF4_hooks.c")
        self.assertIn("FinishTheTripperMercuryTributeSummon(", source)

    def test_opponent_atk_drain_uses_original_atk(self):
        body = extract_function_body(source := read("src_custom/permanent_effects/the_tripper_mercury.c"),
                                     "ApplyTheTripperMercuryOpponentAtkDrain")
        self.assertIn("SetCardInfo(zone->id)", body)
        self.assertIn("originalAtk = gCardInfo.atk", body)

    def test_card_hooks_apply_drain(self):
        source = read("src_custom/card_hooks.c")
        self.assertIn("ApplyTheTripperMercuryOpponentAtkDrain(zone)", source)

    def test_second_attack_unlock_wired(self):
        source = read("src_custom/code_8043EF4_hooks.c")
        self.assertIn("TryUnlockTheTripperMercuryForSecondAttack", source)


if __name__ == "__main__":
    unittest.main()
