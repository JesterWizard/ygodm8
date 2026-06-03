#!/usr/bin/env python3

import subprocess
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
VALIDATOR = ROOT / "tools" / "validate_lynjump.py"
BAD_FIXTURE = ROOT / "tests" / "fixtures" / "lynjump_init_duelist_bad.event"
EVENT = ROOT / "src_custom" / "LynJump.event"
ELF = ROOT / "ygodm8.elf"
ROM = ROOT / "ygodm8.gba"

sys.path.insert(0, str(ROOT / "tools"))

from lynjump_layout import (  # noqa: E402
    expected_poin_org,
    get_duelist_level_rom_prologue,
    iter_hook_poin_sites,
    validate_poin_entry_collisions,
)

DECK_MENU_SYMBOLS = {
    "InitDuelistLevel": 0x0801D724,
    "GetDuelistLevel": 0x0801D730,
    "IncreaseDuelistLevel": 0x0801D73C,
    "ShouldDuelistLevelIncrease": 0x0801D760,
}


class LynJumpLayoutTests(unittest.TestCase):
    def test_default_poin_overwrites_adjacent_get_duelist_level(self):
        errors = validate_poin_entry_collisions([BAD_FIXTURE], DECK_MENU_SYMBOLS)
        self.assertTrue(
            any("GetDuelistLevel" in error for error in errors),
            msg=errors,
        )

    def test_repo_init_duelist_level_poin_avoids_get_duelist_level(self):
        sites = [
            site
            for site in iter_hook_poin_sites(EVENT)
            if site.replacement_name == "InitDuelistLevel__Replacement"
        ]
        self.assertEqual(len(sites), 1)
        site = sites[0]
        self.assertEqual(site.hook_org, 0x1D724)
        self.assertEqual(site.poin_org, expected_poin_org(0x1D724, 0x40))
        self.assertNotEqual(site.poin_org, 0x1D730)

        errors = validate_poin_entry_collisions([EVENT], DECK_MENU_SYMBOLS)
        self.assertFalse(
            any("GetDuelistLevel" in error for error in errors),
            msg=errors,
        )

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

    @unittest.skipUnless(ROM.is_file(), "requires built ygodm8.gba")
    def test_get_duelist_level_rom_entry_is_intact(self):
        prologue = get_duelist_level_rom_prologue(ROM)
        self.assertEqual(prologue, 0x4801)

    @unittest.skipUnless(ELF.is_file(), "requires linked ygodm8.elf")
    def test_validator_passes_with_elf_symbols(self):
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


if __name__ == "__main__":
    unittest.main()
