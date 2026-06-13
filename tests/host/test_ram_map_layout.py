#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from ram_map_layout import (  # noqa: E402
    Allocation,
    validate_card_growth,
    validate_qty_cluster_integrity,
    validate_ram_map_layout,
)


class RamMapLayoutTests(unittest.TestCase):
    def test_repo_layout_passes(self):
        errors = validate_ram_map_layout()
        self.assertEqual(errors, [])

    def test_qty_cluster_rejects_interleaved_effect_state(self):
        allocs = [
            Allocation("gCustomTrunkCardQty", "CUSTOM_CARD_QTY_BYTES", 1),
            Allocation("gGreatMajuGarzettBoardStats", "0x64", 2),
            Allocation("gCustomShopTempCardQty", "CUSTOM_CARD_QTY_BYTES", 3),
        ]
        errors = validate_qty_cluster_integrity(allocs)
        self.assertTrue(errors)
        self.assertIn("gGreatMajuGarzettBoardStats", errors[0])

    def test_card_growth_simulation_passes_for_repo(self):
        errors = validate_card_growth(
            __import__("ram_map_layout").parse_region_allocations(
                (ROOT / "asm/ram_map.s").read_text(encoding="utf-8"),
                "ewram",
            ),
            total_cards=0x038D,
            custom_start=0x0321,
        )
        self.assertEqual(errors, [])


if __name__ == "__main__":
    unittest.main()
