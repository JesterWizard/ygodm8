#!/usr/bin/env python3

import json
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from card_manifest import ManifestValidationError, dump_manifest_json, format_password_inline, format_json_decode_error, load_manifest_json, order_card_entry, validate_manifest, write_manifest  # noqa: E402
import add_card_art as card_art  # noqa: E402

from tests.support.golden import assert_matches_golden  # noqa: E402

FIXTURE = ROOT / "tests" / "fixtures" / "card_manifest_minimal.json"


class CardManifestTests(unittest.TestCase):
    def test_minimal_fixture_validates(self):
        manifest = json.loads(FIXTURE.read_text())
        validated = validate_manifest(manifest)
        self.assertEqual(len(validated["cards"]), 4)

    def test_rejects_duplicate_card_const(self):
        manifest = json.loads(FIXTURE.read_text())
        manifest["cards"].append(dict(manifest["cards"][1]))
        with self.assertRaises(ManifestValidationError):
            validate_manifest(manifest)

    def test_rejects_invalid_password(self):
        manifest = json.loads(FIXTURE.read_text())
        manifest["cards"][1]["password"] = [16, 0, 0, 0, 0, 0, 0, 0]
        with self.assertRaises(ManifestValidationError):
            validate_manifest(manifest)

    def test_rejects_invalid_effect_usage(self):
        manifest = json.loads(FIXTURE.read_text())
        manifest["cards"][1]["effect_usage"] = "every_turn"
        with self.assertRaises(ManifestValidationError):
            validate_manifest(manifest)

    def test_load_manifest_json_reports_syntax_error_context(self):
        bad_json = '{\n  "cards": [\n    {\n      "card_const": "BAD_CARD",\n    }\n  ]\n}\n'
        with self.assertRaises(json.JSONDecodeError) as ctx:
            json.loads(bad_json)
        message = format_json_decode_error("tools/card_data_manifest.json", bad_json, ctx.exception)
        self.assertIn("Invalid JSON in tools/card_data_manifest.json", message)
        self.assertIn("line 5", message)
        self.assertIn("BAD_CARD", message)
        self.assertIn("Nearest card entry above error: BAD_CARD", message)
        self.assertIn("^", message)

        with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False) as handle:
            handle.write(bad_json)
            bad_path = Path(handle.name)
        try:
            with self.assertRaises(ManifestValidationError) as ctx:
                load_manifest_json(bad_path)
            self.assertIn("Invalid JSON in", str(ctx.exception))
            self.assertIn("^", str(ctx.exception))
        finally:
            bad_path.unlink()

    def test_golden_card_ids_header(self):
        manifest = validate_manifest(json.loads(FIXTURE.read_text()))
        output = card_art.render_card_ids_header(manifest)
        assert_matches_golden(output, "cards/card_ids_header.inc")

    def test_derives_description_symbols(self):
        manifest = {
            "cards": [
                {
                    "card_const": "SPIRIT_OF_THE_BREEZE",
                    "card_name": "Spirit of the Breeze",
                    "atk": 0,
                    "def": 1800,
                    "cost": 150,
                    "attribute": "ATTRIBUTE_WIND",
                    "level": 3,
                    "type": "TYPE_FAIRY",
                    "color": "EFFECT_CARD",
                    "monsterEffect": 0,
                    "spellEffect": 2,
                    "trapEffect": 0,
                    "password": [5, 3, 5, 3, 0, 0, 6, 9],
                    "description": {
                        "pages": [
                            "As long as this card remains in face-up",
                            "Attack Position, gain 1000 LP during",
                            "each of your Standby Phases.",
                        ]
                    },
                    "activation_description": {
                        "pages": ["Gain 1000 LP during your Standby Phase."],
                    },
                }
            ]
        }
        validated = validate_manifest(manifest)["cards"][0]
        self.assertEqual(validated["description"]["symbol"], "gDescription_SpiritOfTheBreeze")
        self.assertEqual(
            validated["activation_description"]["symbol"],
            "gActivationDescription_SpiritOfTheBreeze",
        )

    def test_manifest_dump_uses_canonical_key_order_and_inline_password(self):
        manifest = validate_manifest(json.loads(FIXTURE.read_text()))
        text = dump_manifest_json(manifest)
        self.assertIn('"password": [8, 9, 6, 3, 1, 1, 3, 9]', text)
        self.assertNotIn('"password": [\n', text)
        entry = manifest["cards"][1]
        self.assertEqual(
            list(entry.keys()),
            [
                "card_const",
                "card_name",
                "atk",
                "def",
                "level",
                "attribute",
                "type",
                "color",
                "monsterEffect",
                "spellEffect",
                "trapEffect",
                "cost",
                "password",
            ],
        )

    def test_order_card_entry_matches_manifest_key_order(self):
        entry = order_card_entry(
            {
                "password": [1, 2, 3, 4, 5, 6, 7, 8],
                "card_const": "EXAMPLE",
                "card_name": "Example",
                "atk": 1,
                "def": 2,
                "level": 3,
                "attribute": 0,
                "type": 0,
                "color": "NORMAL_CARD",
                "monsterEffect": 0,
                "spellEffect": 2,
                "trapEffect": 0,
                "cost": 4,
            }
        )
        self.assertEqual(list(entry.keys())[:4], ["card_const", "card_name", "atk", "def"])
        self.assertEqual(format_password_inline(entry["password"]), "[1, 2, 3, 4, 5, 6, 7, 8]")


if __name__ == "__main__":
    unittest.main()
