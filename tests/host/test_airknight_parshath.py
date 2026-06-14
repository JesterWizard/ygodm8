#!/usr/bin/env python3

import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


class AirknightParshathTests(unittest.TestCase):
    def test_draw_locks_monsters_after_normal_summon(self):
        source = (ROOT / "src_custom/battle_effects/airknight_parshath.c").read_text()

        self.assertIn("TryDrawingCard(duelist)", source)
        self.assertIn("gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked", source)
        self.assertIn("LockMonsterCardsInRow(ACTIVE_DUELIST_HAND)", source)


if __name__ == "__main__":
    unittest.main()
