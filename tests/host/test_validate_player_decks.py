#!/usr/bin/env python3

import subprocess
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
VALIDATOR = ROOT / "tools" / "validate_player_decks.py"
ELF = ROOT / "ygodm8.elf"


class PlayerDecksValidatorTests(unittest.TestCase):
    def test_validator_passes_on_repo_sources(self):
        result = subprocess.run(
            ["python3", str(VALIDATOR)],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
        self.assertEqual(
            result.returncode,
            0,
            msg=result.stderr or result.stdout,
        )
        self.assertIn("validate_player_decks: ok", result.stdout)

    def test_switch_invariants(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_player_decks import validate_switch_invariants  # noqa: E402

        self.assertEqual(validate_switch_invariants(), [])

    def test_get_deck_cards_backing_covers_all_decks(self):
        source = (ROOT / "src_custom" / "player_decks" / "player_decks.c").read_text(
            encoding="utf-8"
        )
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_player_decks import _extract_function_body  # noqa: E402

        body = _extract_function_body(source, "GetDeckCardsBacking")
        for symbol in ("gPlayerDeck1Cards", "gPlayerDeck2Cards", "gPlayerDeck3Cards"):
            self.assertIn(symbol, body)

    @unittest.skipUnless(ELF.is_file(), "requires linked ygodm8.elf")
    def test_elf_deck_symbols(self):
        result = subprocess.run(
            ["python3", str(VALIDATOR), "--elf", str(ELF)],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
        self.assertEqual(
            result.returncode,
            0,
            msg=result.stderr or result.stdout,
        )


if __name__ == "__main__":
    unittest.main()
