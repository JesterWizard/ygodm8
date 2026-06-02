#!/usr/bin/env python3

import json
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from duelist_deck_validate import (  # noqa: E402
    DeckManifestValidationError,
    generate_deck_manifest_source,
    validate_cards,
)

from tests.support.golden import assert_matches_golden  # noqa: E402

FIXTURE = ROOT / "tests" / "fixtures" / "duelist_deck_manifest_minimal.json"


class DuelistDeckTests(unittest.TestCase):
    def test_validate_cards_requires_exact_size(self):
        with self.assertRaises(DeckManifestValidationError):
            validate_cards(["BLUE_EYES_WHITE_DRAGON"], 40, "test")

    def test_rejects_duplicate_duelist(self):
        manifest = json.loads(FIXTURE.read_text())
        manifest["duelist_decks"].append(dict(manifest["duelist_decks"][0]))
        with self.assertRaises(DeckManifestValidationError):
            generate_deck_manifest_source(manifest)

    def test_golden_generated_deck_source(self):
        manifest = json.loads(FIXTURE.read_text())
        output = generate_deck_manifest_source(manifest)
        assert_matches_golden(output, "duelist_decks/minimal_generated.inc")


if __name__ == "__main__":
    unittest.main()
