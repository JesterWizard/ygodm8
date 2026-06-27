#!/usr/bin/env python3
"""Suggest a cost for a new card based on similar existing cards in the manifest.

Usage:
  python3 tools/suggest_card_cost.py --level 4 --atk 1900 --def 1200 --color EFFECT_CARD
  python3 tools/suggest_card_cost.py --level 4 --atk 65535 --def 65535 --color SPELL_CARD
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MANIFEST_PATH = ROOT / "tools" / "card_data_manifest.json"
CARD_STATE_PATH = ROOT / "tools" / ".card_state"


def load_manifest() -> list[dict]:
    with MANIFEST_PATH.open() as f:
        return json.load(f)["cards"]


def suggest_cost(cards: list[dict], target: dict) -> tuple[int, list[dict]]:
    best_cost = 150
    best_score: int | None = None
    matches: list[tuple[int, dict]] = []

    for item in cards:
        score = 0
        if item.get("color") != target["color"]:
            score += 100
        score += abs(item.get("level", 0) - target["level"]) * 10
        score += abs(item.get("atk", 0) - target["atk"]) // 100
        score += abs(item.get("def", 0) - target["def"]) // 100
        matches.append((score, item))
        if best_score is None or score < best_score:
            best_score = score
            best_cost = item["cost"]

    top = sorted(matches, key=lambda x: x[0])[:5]
    return best_cost, [m[1] for m in top]


def main() -> int:
    parser = argparse.ArgumentParser(description="Suggest a card cost from similar manifest entries.")
    parser.add_argument("--level", type=int, default=0)
    parser.add_argument("--atk", type=int, default=65535)
    parser.add_argument("--defense", "--def", type=int, default=65535, dest="defense",
                        help="DEF stat (use --defense to avoid Python keyword conflict)")
    parser.add_argument("--color", default="EFFECT_CARD",
                        help="NORMAL_CARD/EFFECT_CARD/SPELL_CARD/TRAP_CARD/FUSION_CARD")
    args = parser.parse_args()

    cards = load_manifest()
    target = {"color": args.color, "level": args.level, "atk": args.atk, "def": args.defense}
    cost, top = suggest_cost(cards, target)

    print(f"Suggested cost: {cost}")
    print(f"Top {len(top)} similar cards in manifest:")
    print(f"  {'Cost':>5}  {'Level':>5}  {'ATK':>5}  {'DEF':>5}  {'Color':<16}  {'Name'}")
    print(f"  {'-'*5}  {'-'*5}  {'-'*5}  {'-'*5}  {'-'*16}  {'-'*30}")
    for c in top:
        print(f"  {c['cost']:>5}  {c.get('level', 0):>5}  {c.get('atk', 0):>5}  {c.get('def', 0):>5}  {c.get('color', ''):<16}  {c.get('card_name', '')[:30]}")

    if CARD_STATE_PATH.is_file():
        state = CARD_STATE_PATH.read_text()
        print(f"\nState ({CARD_STATE_PATH.name}):")
        for line in state.splitlines():
            if line.strip() and not line.startswith("#"):
                print(f"  {line}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
