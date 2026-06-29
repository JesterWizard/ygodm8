import unittest
from pathlib import Path


class ExpandedGraveyardTests(unittest.TestCase):
    def test_single_ewram_buffer_only(self):
        root = Path(__file__).resolve().parents[2]
        source = (root / "src_custom/expanded_graveyard.c").read_text()
        ram = (root / "asm/ram_map_ewram.s").read_text()
        sim_hooks = (root / "src_custom/ai_simulation_hooks.c").read_text()
        lynjump = (root / "src_custom/LynJump.event").read_text()

        self.assertIn("gExpandedGraveyard", ram)
        self.assertNotIn("gAiSimGraveyardScratch", ram)
        self.assertNotIn("gExpandedGraveyardCount", ram)
        self.assertIn("CountFromArray", source)
        self.assertIn("return gAiSimInBatch", (root / "include/ai_sim.h").read_text())
        self.assertIn("AI_SIM_GY_CANDIDATE_SNAPSHOT_OFF", sim_hooks)
        self.assertIn("AiSimBatchGraveyardSave", sim_hooks)
        self.assertIn("GraveyardExpand_RefreshDisplay", source)
        self.assertIn("GraveyardExpand_ClearOpponentAfterSimIfFirstTurn", source)
        self.assertIn("DECK_SIZE - 5", source)
        self.assertIn("POIN PlaceMonsterCardInZone__Replacement", lynjump)


if __name__ == "__main__":
    unittest.main()
