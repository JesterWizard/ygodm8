#!/usr/bin/env python3
"""Duelist deck manifest validation and codegen shared by generate_duelist_decks.py."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_DECK_SIZE = 40


class DeckManifestValidationError(Exception):
    """Raised when a duelist deck manifest fails validation."""


def _fail(message: str) -> None:
    raise DeckManifestValidationError(message)


def load_duelist_ids(overworld_h: Path | None = None) -> dict[str, int]:
    text = (overworld_h or ROOT / "include/overworld.h").read_text()
    match = re.search(r"\benum\s+DuelistId\s*\{(.*?)\};", text, re.DOTALL)
    if not match:
        _fail("enum DuelistId not found in include/overworld.h")

    constants: dict[str, int] = {}
    value = 0
    for raw_item in match.group(1).split(","):
        item = raw_item.strip()
        if not item:
            continue
        name, _, explicit = item.partition("=")
        name = name.strip()
        if explicit:
            value = int(explicit.strip(), 0)
        constants[name] = value
        value += 1
    return constants


def resolve_duelist_id(raw_id, duelist_ids: dict[str, int]) -> tuple[int, str, str]:
    if isinstance(raw_id, int):
        return raw_id, str(raw_id), str(raw_id)
    if raw_id not in duelist_ids:
        _fail(f"unknown duelist_id {raw_id!r}")
    return duelist_ids[raw_id], raw_id, raw_id


def validate_cards(cards: list, deck_size: int, duelist_ref: str) -> list[str]:
    if not isinstance(cards, list):
        _fail(f"{duelist_ref}: cards must be a list")
    if len(cards) != deck_size:
        _fail(f"{duelist_ref}: expected {deck_size} cards, got {len(cards)}")
    for card in cards:
        if not isinstance(card, str) or not card:
            _fail(f"{duelist_ref}: invalid card name {card!r}")
    return cards


def render_deck_array(symbol: str, cards: list[str]) -> list[str]:
    lines = [f"static const u16 {symbol}[{len(cards)}] APPEND_RODATA = {{"]
    for index in range(0, len(cards), 4):
        chunk = cards[index : index + 4]
        lines.append("  " + ", ".join(chunk) + ",")
    lines.append("};")
    return lines


def generate_deck_manifest_source(manifest: dict, duelist_ids: dict[str, int] | None = None) -> str:
    duelist_ids = duelist_ids or load_duelist_ids()
    max_duelists = int(manifest.get("max_duelists", 192))
    deck_size = int(manifest.get("deck_size", DEFAULT_DECK_SIZE))

    lines: list[str] = []
    deck_symbols: dict[int, tuple[str, str]] = {}

    for entry in manifest["duelist_decks"]:
        duelist_id, duelist_ref, symbol_suffix = resolve_duelist_id(entry["duelist_id"], duelist_ids)
        cards = validate_cards(entry["cards"], deck_size, duelist_ref)
        if duelist_id < 0 or duelist_id >= max_duelists:
            _fail(f"duelist_id {duelist_ref} outside max_duelists {max_duelists}")
        if duelist_id in deck_symbols:
            _fail(f"duplicate duelist_id {duelist_ref}")
        deck_symbols[duelist_id] = (duelist_ref, symbol_suffix)
        lines.extend(render_deck_array(f"sDuelist{symbol_suffix}Deck", cards))
        lines.append("")

    lines.append(f"static const u16 *const sManifestDuelDecks[{max_duelists}] APPEND_RODATA = {{")
    for duelist_id in range(max_duelists):
        if duelist_id in deck_symbols:
            duelist_ref, symbol_suffix = deck_symbols[duelist_id]
            lines.append(f"  [{duelist_ref}] = sDuelist{symbol_suffix}Deck,")
        else:
            lines.append(f"  [{duelist_id}] = NULL,")
    lines.append("};")
    lines.append("")
    lines.extend(
        [
            "const u16 *GetManifestDuelDeck(u16 opponent) {",
            "  if (opponent >= ARRAY_COUNT(sManifestDuelDecks))",
            "    return NULL;",
            "  return sManifestDuelDecks[opponent];",
            "}",
            "",
        ]
    )
    return "\n".join(lines)
