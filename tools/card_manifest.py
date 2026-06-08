#!/usr/bin/env python3
"""Card manifest validation shared by add_card_art.py and host tests."""

from __future__ import annotations

import re

REQUIRED_STATS_KEYS = {
    "atk",
    "def",
    "cost",
    "attribute",
    "level",
    "type",
    "color",
    "monsterEffect",
    "spellEffect",
    "trapEffect",
    "password",
}
OPTIONAL_STATS_KEYS = {"description", "activation_description", "lock_after_activation", "customFieldSpell", "effect_usage"}
ALLOWED_EFFECT_USAGE = {
    "once",
    "once_per_turn",
    "multiple_per_turn",
    "continuous",
}
ASSET_ENTRY_KEYS = {"big_art", "big_palette", "mini_art"}
ALLOWED_ENTRY_KEYS = {"card_const", "card_name", "trunk_card"} | REQUIRED_STATS_KEYS | OPTIONAL_STATS_KEYS | ASSET_ENTRY_KEYS


class ManifestValidationError(Exception):
    """Raised when a card manifest fails validation."""


def _fail(message: str) -> None:
    raise ManifestValidationError(message)


def validate_manifest(manifest: object) -> dict:
    if not isinstance(manifest, dict):
        _fail("Manifest must be a JSON object with a top-level 'cards' array.")
    cards = manifest.get("cards")
    if not isinstance(cards, list):
        _fail("Manifest must contain a top-level 'cards' array.")
    description_pages_max = 3

    seen_consts: set[str] = set()
    validated = []
    for index, item in enumerate(cards):
        if not isinstance(item, dict):
            _fail(f"cards[{index}] must be an object.")

        card_const = item.get("card_const")
        card_name = item.get("card_name")
        if not isinstance(card_const, str) or not re.fullmatch(r"[A-Z0-9_]+", card_const):
            _fail(f"cards[{index}].card_const must be an uppercase constant name.")
        if not isinstance(card_name, str) or not card_name:
            _fail(f"cards[{index}].card_name must be a non-empty string.")
        if card_const in seen_consts:
            _fail(f"Duplicate card_const in manifest: {card_const}")
        seen_consts.add(card_const)

        extra = sorted(set(item.keys()) - ALLOWED_ENTRY_KEYS)
        if extra:
            _fail(f"cards[{index}] has unknown keys: {', '.join(extra)}")

        missing = sorted(REQUIRED_STATS_KEYS - item.keys())
        if missing:
            _fail(f"cards[{index}] is missing required keys: {', '.join(missing)}")

        stats = {
            key: item[key]
            for key in REQUIRED_STATS_KEYS | OPTIONAL_STATS_KEYS | ASSET_ENTRY_KEYS
            if key in item
        }

        for key in ("atk", "def", "cost", "level"):
            if not isinstance(stats[key], int):
                _fail(f"cards[{index}].{key} must be an integer.")

        for key in ("monsterEffect", "spellEffect", "trapEffect"):
            if not isinstance(stats[key], (int, str)):
                _fail(f"cards[{index}].{key} must be an integer or a C enum-style identifier string.")

        for key in ("color", "type", "attribute"):
            if not isinstance(stats[key], (str, int)):
                _fail(f"cards[{index}].{key} must be a C enum-style identifier (string) or integer.")

        password = stats.get("password")
        if not isinstance(password, list) or len(password) != 8 or not all(
            isinstance(d, int) and 0 <= d <= 15 for d in password
        ):
            _fail(f"cards[{index}].password must be an array of 8 integers (0-15).")

        for desc_key in ("description", "activation_description"):
            if desc_key not in stats:
                continue
            description = stats[desc_key]
            if not isinstance(description, dict):
                _fail(f"cards[{index}].{desc_key} must be an object when present.")
            symbol = description.get("symbol")
            pages = description.get("pages")
            if not isinstance(symbol, str) or not symbol:
                _fail(f"cards[{index}].{desc_key}.symbol must be a non-empty string.")
            if not isinstance(pages, list) or not all(isinstance(page, str) and page for page in pages):
                _fail(f"cards[{index}].{desc_key}.pages must be an array of non-empty strings.")
            min_pages = 1 if desc_key == "activation_description" else 2
            if len(pages) < min_pages or len(pages) > description_pages_max:
                _fail(
                    f"cards[{index}].{desc_key}.pages must contain between "
                    f"{min_pages} and {description_pages_max} strings."
                )

        for key in ASSET_ENTRY_KEYS:
            if key in stats and not isinstance(stats[key], str):
                _fail(f"cards[{index}].{key} must be a string when present.")
        if "trunk_card" in item and not isinstance(item["trunk_card"], bool):
            _fail(f"cards[{index}].trunk_card must be a boolean when present.")
        if "lock_after_activation" in item and not isinstance(item["lock_after_activation"], bool):
            _fail(f"cards[{index}].lock_after_activation must be a boolean when present.")
        effect_usage = item.get("effect_usage")
        if effect_usage is not None and effect_usage not in ALLOWED_EFFECT_USAGE:
            _fail(
                f"cards[{index}].effect_usage must be one of: "
                f"{', '.join(sorted(ALLOWED_EFFECT_USAGE))}."
            )
        custom_field_spell = item.get("customFieldSpell")
        if custom_field_spell is not None and not isinstance(custom_field_spell, str):
            _fail(f"cards[{index}].customFieldSpell must be a string when present.")

        validated.append(
            {
                "card_const": card_const,
                "card_name": card_name,
                **stats,
                **({"trunk_card": item["trunk_card"]} if "trunk_card" in item else {}),
                **({"customFieldSpell": custom_field_spell} if custom_field_spell is not None else {}),
            }
        )

    return {"cards": validated}
