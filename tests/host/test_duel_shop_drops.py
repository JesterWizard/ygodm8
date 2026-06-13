#!/usr/bin/env python3

import subprocess
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
VALIDATOR = ROOT / "tools" / "validate_duel_shop_drops.py"


class DuelShopDropValidatorTests(unittest.TestCase):
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
        self.assertIn("validate_duel_shop_drops: ok", result.stdout)

    def test_custom_cards_share_shop_roll_pool(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_duel_shop_drops import _extract_function_body  # noqa: E402

        source = (ROOT / "src_custom" / "code_801EF30_hooks.c").read_text(
            encoding="utf-8"
        )
        roll_body = _extract_function_body(source, "sub_8020050__Replacement")

        self.assertIn("PickUniformRewardCard(gCustomTrunkCards", roll_body)
        self.assertIn("enable_custom_cards_past_800", roll_body)

    def test_popup_rolls_and_displays_in_one_pass(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_duel_shop_drops import _extract_function_body  # noqa: E402

        source = (ROOT / "src_custom" / "code_801EF30_hooks.c").read_text(
            encoding="utf-8"
        )
        display_body = _extract_function_body(source, "DisplayDuelShopDropText")
        loop_index = display_body.index("RunDuelShopDropLoop")
        popup_index = display_body.index("sub_8041C94")

        self.assertLess(loop_index, popup_index)

    def test_lynjump_redirects_shop_roll_hook(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_duel_shop_drops import _lynjump_poin_at_org  # noqa: E402

        event = (ROOT / "src_custom" / "LynJump.event").read_text(encoding="utf-8")
        self.assertEqual(
            _lynjump_poin_at_org(event, "20050"),
            "sub_8020050__Replacement",
        )


if __name__ == "__main__":
    unittest.main()
