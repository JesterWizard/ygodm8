#!/usr/bin/env python3

import json
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from card_manifest import ManifestValidationError, validate_manifest  # noqa: E402
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

    def test_golden_card_ids_header(self):
        manifest = validate_manifest(json.loads(FIXTURE.read_text()))
        output = card_art.render_card_ids_header(manifest)
        assert_matches_golden(output, "cards/card_ids_header.inc")


if __name__ == "__main__":
    unittest.main()
