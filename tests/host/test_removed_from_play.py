import unittest
from pathlib import Path


class RemovedFromPlayTests(unittest.TestCase):
    def test_ewram_and_api_wiring(self):
        root = Path(__file__).resolve().parents[2]
        ram = (root / "asm/ram_map_ewram.s").read_text()
        source = (root / "src_custom/removed_from_play.c").read_text()
        hooks = (root / "src_custom/code_803F02C_hooks.c").read_text()
        helpers = (root / "src_custom/duel_helpers.c").read_text()

        self.assertIn("gRemovedFromPlay", ram)
        self.assertIn("0xA0", ram.split("gRemovedFromPlay")[1][:80])
        self.assertIn("REMOVED_FROM_PLAY_CAPACITY 40", (root / "include/removed_from_play.h").read_text())
        self.assertIn("RemovedFromPlay_PushZone", helpers)
        self.assertIn("Duel_BanishGraveyardAtFixed", helpers)
        self.assertIn("RemovedFromPlay_Init", hooks)
        self.assertIn("Duel_RemovedFromPlayViewer_Open(DUEL_PLAYER)", hooks)
        self.assertIn("Duel_RemovedFromPlayViewer_Open(DUEL_OPPONENT)", hooks)


if __name__ == "__main__":
    unittest.main()
