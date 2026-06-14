#!/usr/bin/env python3

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

from ram_map_layout import (  # noqa: E402
    Allocation,
    load_size_constants,
    simulate_bump,
    validate_allocation_alignment,
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

    def test_alignment_rejects_odd_u16_allocation(self):
        constants = load_size_constants()
        allocs = [
            Allocation("leading_byte", "1", 1),
            Allocation("misaligned_u16", "2", 2),
        ]
        regions, _ = simulate_bump(allocs, 0x03007E00, 0x03001678, constants)
        errors = validate_allocation_alignment(regions, "IWRAM")
        self.assertEqual(len(errors), 1)
        self.assertIn("misaligned_u16", errors[0])

    def test_alignment_accepts_padded_u16_allocation(self):
        constants = load_size_constants()
        allocs = [
            Allocation("leading_byte", "1", 1),
            Allocation("alignment_pad", "1", 2),
            Allocation("aligned_u16", "2", 3),
        ]
        regions, _ = simulate_bump(allocs, 0x03007E00, 0x03001678, constants)
        errors = validate_allocation_alignment(regions, "IWRAM")
        self.assertEqual(errors, [])

    def test_repo_has_no_misaligned_u16_allocations(self):
        errors = validate_ram_map_layout()
        alignment_errors = [error for error in errors if "2-byte aligned" in error]
        self.assertEqual(alignment_errors, [], msg="\n".join(alignment_errors))


if __name__ == "__main__":
    unittest.main()
