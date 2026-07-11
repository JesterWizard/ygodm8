#!/usr/bin/env python3
"""Test description page wrapping."""
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from add_card_art import wrap_description_page

tests = {
    'LADD': [
        "Cannot be Special Summoned.",
        "Also DARK-Attribute. Once per",
        "Chain, when a card effect is",
        "activated: loses 500 ATK/DEF",
        "and negates. When destroyed:",
        "target 1 GY monster; destroy",
        "all your cards, SS that target.",
    ],
}

for card, pages in tests.items():
    print(f"--- {card} ({len(pages)} pages) ---")
    for i, p in enumerate(pages):
        try:
            wrap_description_page(p)
            print(f"  page {i}: OK ({repr(p[:40])}...)")
        except SystemExit as e:
            print(f"  page {i}: FAIL - {e}")
