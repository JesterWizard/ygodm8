#!/usr/bin/env python3

import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
GREAT_MAJU_EFFECT = ROOT / "src_custom" / "permanent_effects" / "great_maju_garzett.c"


def great_maju_stats_from_tribute(tribute_atk, tribute_def):
    return tribute_atk * 2, tribute_def * 2


class GreatMajuGarzettTests(unittest.TestCase):
    def test_doubles_single_tribute_stats(self):
        atk, def_ = great_maju_stats_from_tribute(600, 600)
        self.assertEqual((atk, def_), (1200, 1200))

    def test_sums_multiple_tributes_before_doubling(self):
        total_atk = 600 + 800
        total_def = 600 + 700
        atk, def_ = great_maju_stats_from_tribute(total_atk, total_def)
        self.assertEqual((atk, def_), (2800, 2600))

    def test_zero_tribute_stays_zero(self):
        atk, def_ = great_maju_stats_from_tribute(0, 0)
        self.assertEqual((atk, def_), (0, 0))

    def test_finish_tribute_summon_refreshes_field_stat_overlays(self):
        source = GREAT_MAJU_EFFECT.read_text()
        finish_body = re.search(
            r"void FinishGreatMajuGarzettTributeSummon\([^)]*\)\s*\{(.*?)^\}",
            source,
            re.S | re.M,
        )
        self.assertIsNotNone(finish_body)
        self.assertIn("RefreshFieldMonsterStatOverlays();", finish_body.group(1))


if __name__ == "__main__":
    unittest.main()
