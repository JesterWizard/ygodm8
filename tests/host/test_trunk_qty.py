#!/usr/bin/env python3

import subprocess
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
VALIDATOR = ROOT / "tools" / "validate_trunk_qty.py"


class TrunkQtyValidatorTests(unittest.TestCase):
    def test_validator_passes_on_repo(self):
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
        self.assertIn("validate_trunk_qty: ok", result.stdout)

    def test_increment_helper_uses_custom_trunk_storage(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_trunk_qty import _extract_function_body  # noqa: E402

        source = (ROOT / "src_custom" / "trunk_hooks.c").read_text(encoding="utf-8")
        increment_body = _extract_function_body(source, "TrunkMenu_IncrementTrunkQty")

        self.assertIn("GetTrunkQtyForCard", increment_body)
        self.assertIn("SetTrunkQtyForCard", increment_body)
        self.assertIn("TRUNK_CARD_LIMIT", increment_body)

    def test_deck_menu_returns_cards_through_increment_helper(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_trunk_qty import _extract_function_body  # noqa: E402

        source = (ROOT / "src_custom" / "deck_menu_hooks.c").read_text(encoding="utf-8")
        move_one = _extract_function_body(source, "MoveSelectedCardToTrunk")
        move_all = _extract_function_body(source, "MoveAllCardsToTrunk")

        self.assertIn("TrunkMenu_IncrementTrunkQty", move_one)
        self.assertIn("TrunkMenu_IncrementTrunkQty", move_all)
        self.assertNotIn("AddCardToTrunk", move_one)
        self.assertNotIn("AddCardToTrunk", move_all)


if __name__ == "__main__":
    unittest.main()
