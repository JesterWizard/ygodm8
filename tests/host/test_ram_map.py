#!/usr/bin/env python3

import subprocess
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
VALIDATOR = ROOT / "tools" / "validate_ram_map.py"


class RamMapValidatorTests(unittest.TestCase):
    def test_validate_ram_map_exits_zero(self):
        result = subprocess.run(
            ["python3", str(VALIDATOR)],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
        self.assertEqual(result.returncode, 0, msg=result.stderr or result.stdout)


if __name__ == "__main__":
    unittest.main()
