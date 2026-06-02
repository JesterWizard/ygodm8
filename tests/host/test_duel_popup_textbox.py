#!/usr/bin/env python3

import subprocess
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
VALIDATOR = ROOT / "tools" / "validate_duel_popup_textbox.py"
ELF = ROOT / "ygodm8.elf"


class DuelPopupTextboxValidatorTests(unittest.TestCase):
    def test_source_clear_rules(self):
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

    def test_golden_clear_buffer_length(self):
        sys_path = str(ROOT)
        if sys_path not in __import__("sys").path:
            __import__("sys").path.insert(0, str(ROOT / "tools"))

        from validate_duel_popup_textbox import (  # noqa: E402
            DUEL_TEXTBOX_CLEAR_LEN,
            DUEL_TEXTBOX_CLEAR_TEXT,
            extract_hook_clear_text,
            extract_vanilla_clear_text,
        )

        hooks_source = (ROOT / "src_custom" / "code_8041C94_hooks.c").read_text(
            encoding="utf-8"
        )
        duel_source = (ROOT / "src" / "duel" / "duel_textbox.c").read_text(
            encoding="utf-8"
        )

        hook_clear = extract_hook_clear_text(hooks_source)
        vanilla_clear = extract_vanilla_clear_text(duel_source)

        self.assertEqual(DUEL_TEXTBOX_CLEAR_LEN, 113)
        self.assertEqual(hook_clear, DUEL_TEXTBOX_CLEAR_TEXT)
        self.assertEqual(vanilla_clear, DUEL_TEXTBOX_CLEAR_TEXT)
        self.assertGreaterEqual(len(hook_clear), 84)

    def test_dismiss_paths_call_clear_helper(self):
        sys_path = str(ROOT / "tools")
        if sys_path not in __import__("sys").path:
            __import__("sys").path.insert(0, sys_path)

        from validate_duel_popup_textbox import extract_function_body  # noqa: E402

        hooks_source = (ROOT / "src_custom" / "code_8041C94_hooks.c").read_text(
            encoding="utf-8"
        )
        replacement_body = extract_function_body(
            hooks_source, "WaitForTextboxAdvanceInput__Replacement"
        )

        self.assertIn("ClearDuelPopupTextboxTiles();", replacement_body)
        self.assertEqual(replacement_body.count("ClearDuelPopupTextboxTiles();"), 2)

    @unittest.skipUnless(ELF.is_file(), "requires linked ygodm8.elf")
    def test_sub_8041C94_rom_address(self):
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
