#!/usr/bin/env python3

import subprocess
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
VALIDATOR = ROOT / "tools" / "validate_trunk_sort.py"


class TrunkSortValidatorTests(unittest.TestCase):
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
        self.assertIn("validate_trunk_sort: ok", result.stdout)

    def test_compressed_trunk_preserves_sort_order(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_trunk_sort import (  # noqa: E402
            _extract_function_body,
            _extract_if_block,
        )

        source = (ROOT / "src_custom" / "trunk_hooks.c").read_text(encoding="utf-8")
        apply_body = _extract_function_body(source, "ApplyTrunkSortCardList")
        hide_block = _extract_if_block(apply_body, "TrunkHidesUnownedCards()")

        self.assertIn("FinalizeVisibleTrunkSortCardList", hide_block)
        self.assertNotIn("RebuildVisibleTrunkCardList();", hide_block)

    def test_sort_pipeline_uses_compressed_count(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_trunk_sort import _extract_function_body  # noqa: E402

        source = (ROOT / "src_custom" / "trunk_hooks.c").read_text(encoding="utf-8")
        default_sort = _extract_function_body(source, "TrunkMenuDefaultSort__Replacement")

        self.assertIn("gCardSortContext.cardCount = GetTrunkSortCardCount();", default_sort)
        self.assertLess(
            default_sort.index("SortCardsAccordingToContext();"),
            default_sort.index("ApplyTrunkSortCardList();"),
        )
        self.assertLess(
            default_sort.index("ApplyTrunkSortCardList();"),
            default_sort.index("gCardSortContext.cardCount = 0;"),
        )

    def test_dynamic_trunk_sort_modes_use_total_qty(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_trunk_sort import (  # noqa: E402
            TRUNK_DYNAMIC_SORT_MODES,
            _extract_function_body,
        )

        source = (ROOT / "src_custom" / "card_sort_hooks.c").read_text(encoding="utf-8")
        owned_qty_body = _extract_function_body(source, "GetOwnedQtyForDynamicSort")

        self.assertIn("sortMode >= 45 && sortMode <= 54", owned_qty_body)
        self.assertIn("gTotalCardQty", owned_qty_body)
        self.assertEqual(len(TRUNK_DYNAMIC_SORT_MODES), 10)

    def test_dynamic_sort_reads_compressed_card_list(self):
        sys.path.insert(0, str(ROOT / "tools"))
        from validate_trunk_sort import _extract_function_body  # noqa: E402

        source = (ROOT / "src_custom" / "card_sort_hooks.c").read_text(encoding="utf-8")
        build_body = _extract_function_body(source, "BuildDynamicShopOrTrunkSort")

        self.assertIn("gCardSortContext.cardCount", build_body)
        self.assertIn("gCardSortContext.cards[i]", build_body)


if __name__ == "__main__":
    unittest.main()
