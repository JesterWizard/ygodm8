#!/usr/bin/env python3

import subprocess
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
VALIDATOR = ROOT / "tools" / "validate_duel_b_menu.py"
GBA = ROOT / "ygodm8.gba"
HOOKS = ROOT / "src_custom" / "duel_b_menu_hooks.c"


class DuelBMenuValidatorTests(unittest.TestCase):
    def test_template_has_baked_surrender_away_from_draw_coords(self):
        sys_path = str(ROOT / "tools")
        if sys_path not in __import__("sys").path:
            __import__("sys").path.insert(0, sys_path)

        from validate_duel_b_menu import (  # noqa: E402
            EXPECTED_OPTION_LABELS,
            GOLDEN_TEMPLATE_SURRENDER_CELLS,
            read_template_cells,
        )

        self.assertTrue(GBA.is_file(), "requires built ygodm8.gba")
        cells = read_template_cells(GBA)
        surrender = EXPECTED_OPTION_LABELS[3]
        draw_cells = {
            (surrender.row_top, surrender.col),
            (surrender.row_bottom, surrender.col),
        }
        self.assertFalse(draw_cells & GOLDEN_TEMPLATE_SURRENDER_CELLS)
        for row, col in GOLDEN_TEMPLATE_SURRENDER_CELLS:
            self.assertGreaterEqual(cells[(row, col)], 168)

    @unittest.skipUnless(GBA.is_file(), "requires built ygodm8.gba")
    def test_validator_passes_on_repo(self):
        result = subprocess.run(
            ["python3", str(VALIDATOR)],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
        self.assertEqual(result.returncode, 0, msg=result.stderr or result.stdout)

    def test_simulated_tilemap_moves_surrender_off_template(self):
        sys_path = str(ROOT / "tools")
        if sys_path not in __import__("sys").path:
            __import__("sys").path.insert(0, sys_path)

        from validate_duel_b_menu import (  # noqa: E402
            EXPECTED_OPTION_LABELS,
            GOLDEN_TEMPLATE_SURRENDER_CELLS,
            read_template_cells,
            simulate_post_draw_tilemap,
        )

        self.assertTrue(GBA.is_file(), "requires built ygodm8.gba")
        template = read_template_cells(GBA)
        simulated = simulate_post_draw_tilemap(template)
        surrender = EXPECTED_OPTION_LABELS[3]

        self.assertGreaterEqual(template[(9, 0)], 168)
        self.assertLess(simulated[(9, 0)], 168)
        self.assertGreaterEqual(simulated[(surrender.row_top, surrender.col)], 148)
        self.assertFalse(
            {
                (row, col)
                for row, col in GOLDEN_TEMPLATE_SURRENDER_CELLS
                if simulated[(row, col)] >= 168
            }
        )

    def test_table_driven_label_draw(self):
        source = HOOKS.read_text(encoding="utf-8")
        self.assertIn("sBMenuOptionLabels", source)
        self.assertIn("DrawBMenuAllOptionLabels", source)
        self.assertIn("B_MENU_LABEL_TILE_TURN_END_TOP 108", source)
        self.assertIn("B_MENU_LABEL_TILE_DISCARD_TOP 128", source)
        self.assertIn("B_MENU_LABEL_TILE_SURRENDER_TOP 148", source)
        self.assertIn("HighlightBMenuOption(highlightedOption)", source)
        self.assertIn("g8DF811C[i]", source)
        self.assertIn("0xE8DC", source)
        self.assertNotIn("DrawBMenuFixedLabels", source)


if __name__ == "__main__":
    unittest.main()
