#!/usr/bin/env python3
"""Bootstrap tools/duelist_deck_manifest.json from src/data/decks.c and enum DuelistId."""

from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DECKS_C = ROOT / "src/data/decks.c"
OVERWORLD_H = ROOT / "include/overworld.h"
OUT = ROOT / "tools/duelist_deck_manifest.json"
DECK_SIZE = 40


def load_duelist_ids() -> list[str]:
    text = OVERWORLD_H.read_text()
    match = re.search(r"\benum\s+DuelistId\s*\{(.*?)\};", text, re.DOTALL)
    if not match:
        raise SystemExit("enum DuelistId not found in include/overworld.h")

    names: list[str] = []
    value = 0
    for raw_item in match.group(1).split(","):
        item = raw_item.strip()
        if not item:
            continue
        name, _, explicit = item.partition("=")
        name = name.strip()
        if explicit:
            value = int(explicit.strip(), 0)
        while len(names) <= value:
            names.append(f"__MISSING_{len(names)}__")
        names[value] = name
        value += 1
    return names


def parse_decks() -> dict[int, list[str]]:
    text = DECKS_C.read_text()
    decks: dict[int, list[str]] = {}
    pattern = re.compile(
        r"const\s+u16\s+Deck(\d+)\[\]\s*=\s*\{(.*?)\};",
        re.DOTALL,
    )
    for match in pattern.finditer(text):
        deck_id = int(match.group(1))
        body = match.group(2)
        cards = [token.strip() for token in body.split(",") if token.strip()]
        if len(cards) != DECK_SIZE:
            raise SystemExit(f"Deck{deck_id} has {len(cards)} cards, expected {DECK_SIZE}")
        decks[deck_id] = cards
    return decks


def main() -> None:
    duelist_ids = load_duelist_ids()
    decks = parse_decks()
    max_duelists = len(duelist_ids)

    missing_decks = [i for i in range(max_duelists) if i not in decks]
    if missing_decks:
        raise SystemExit(f"missing DeckN arrays for duelist ids: {missing_decks[:8]}{'...' if len(missing_decks) > 8 else ''}")

    extra_decks = sorted(deck_id for deck_id in decks if deck_id >= max_duelists)
    if extra_decks:
        raise SystemExit(f"unexpected DeckN arrays above max duelist id: {extra_decks[:8]}")

    manifest = {
        "max_duelists": max_duelists,
        "deck_size": DECK_SIZE,
        "notes": [
            "Authoritative opponent deck lists keyed by DUELIST_* from include/overworld.h.",
            "Deck index N matches enum value N (same mapping as src/data/decks.c DeckN).",
            "Regenerate src_custom/generated/duelist_decks_generated.inc with tools/generate_duelist_decks.py.",
            "Bootstrap this file from vanilla decks via: python3 tools/extract_duelist_deck_manifest.py",
        ],
        "duelist_decks": [
            {
                "duelist_id": duelist_ids[deck_id],
                "cards": decks[deck_id],
            }
            for deck_id in range(max_duelists)
        ],
    }

    OUT.write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"wrote {OUT} ({max_duelists} duelists)")


if __name__ == "__main__":
    main()
