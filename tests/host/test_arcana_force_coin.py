#!/usr/bin/env python3
"""Arcana Force coin unk4 must not collide with Special Summon marker (unk4=2)."""

from pathlib import Path
import re
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
COIN_H = ROOT / "include" / "arcana_force_coin.h"
HELPERS = ROOT / "src_custom" / "duel_helpers.c"


class TestArcanaForceCoinEncoding(unittest.TestCase):
    def test_tails_is_not_special_summon_marker(self):
        text = COIN_H.read_text()
        heads = re.search(r"#define\s+ARCANA_FORCE_COIN_HEADS\s+(\d+)", text)
        tails = re.search(r"#define\s+ARCANA_FORCE_COIN_TAILS\s+(\d+)", text)
        self.assertIsNotNone(heads)
        self.assertIsNotNone(tails)
        self.assertEqual(int(heads.group(1)), 1)
        self.assertEqual(int(tails.group(1)), 3)

    def test_announce_helper_exists(self):
        coin_c = (ROOT / "src_custom/permanent_effects/arcana_force_coin.c").read_text()
        self.assertIn("ArcanaForce_AnnounceCoinResult", coin_c)
        self.assertIn("Coin result: Heads!", coin_c)
        self.assertIn("Coin result: Tails!", coin_c)

    def test_ss_helper_runs_arcana_coin_hooks(self):
        text = HELPERS.read_text()
        self.assertIn("TryArcanaForceOnSummonCoinHooks(summonZone)", text)
        self.assertIn("zone->unk4 = 2", text)


if __name__ == "__main__":
    sys.exit(0 if unittest.main(verbosity=2, exit=False).result.wasSuccessful() else 1)
