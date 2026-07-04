"""Host checks for The Despair Uranus ATK boost and Spell/Trap protection."""

import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def read(path: str) -> str:
    return (ROOT / path).read_text()


def extract_function_body(source: str, name: str) -> str:
    match = re.search(rf"(?:void|u8) {re.escape(name)}\([^)]*\)\s*\{{(.*?)^\}}", source, re.S | re.M)
    assert match, f"missing {name}"
    return match.group(1)


class TestTheDespairUranus(unittest.TestCase):
    def test_manifest_entry(self):
        manifest = read("tools/card_data_manifest.json")
        self.assertIn('"card_const": "THE_DESPAIR_URANUS"', manifest)
        self.assertIn('"password": [3, 2, 5, 8, 8, 8, 0, 5]', manifest)
        self.assertIn('"type": "TYPE_ROCK"', manifest)

    def test_runtime_hand(self):
        runtime = read("configs/runtime.c")
        self.assertIn("THE_DESPAIR_URANUS", runtime)

    def test_atk_boost_counts_face_up_spell_traps(self):
        source = read("src_custom/permanent_effects/the_despair_uranus.c")
        body = extract_function_body(source, "ApplyTheDespairUranusAtkBoost")
        self.assertIn("CountFaceUpSpellTrapsForDuelist", body)
        self.assertIn("DESPAIR_URANUS_ATK_PER_SPELL_TRAP", body)
        self.assertNotIn("GetTypeGroup(", source)
        self.assertIn("gCardData_NEW", source)

    def test_card_hooks_apply_atk_boost(self):
        source = read("src_custom/card_hooks.c")
        self.assertIn("ApplyTheDespairUranusAtkBoost(zone)", source)

    def test_spell_trap_destroy_immunity_wired(self):
        passive = read("src_custom/card_passive_hooks.c")
        self.assertIn("IsTheDespairUranusProtectingZoneFromEffectDestroy(zone)", passive)

        body = extract_function_body(read("src_custom/permanent_effects/the_despair_uranus.c"),
                                     "IsTheDespairUranusProtectingZoneFromEffectDestroy")
        self.assertIn("IsDespairUranusInMonsterZone", body)
        self.assertIn("IsCardEffectDestroyContext", body)
        self.assertIn("zone->isFaceUp", body)


if __name__ == "__main__":
    unittest.main()
