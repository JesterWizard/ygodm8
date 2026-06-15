#!/usr/bin/env python3

import json
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from card_manifest import ManifestValidationError, format_json_decode_error, load_manifest_json, validate_manifest  # noqa: E402
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


if __name__ == "__main__":
    unittest.main()
