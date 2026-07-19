#!/usr/bin/env python3
"""Card manifest validation shared by add_card_art.py and host tests."""

from __future__ import annotations

import json
import re
from pathlib import Path

CARD_STATE_PATH = Path(__file__).resolve().parent / ".card_state"

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
OPTIONAL_STATS_KEYS = {
    "description",
    "activation_description",
    "effect_texts",
    "lock_after_activation",
    "customFieldSpell",
    "effect_usage",
    "selectableOnce",
    "is_tuner",
}
ALLOWED_EFFECT_USAGE = {
    "once",
    "once_per_turn",
    "multiple_per_turn",
    "continuous",
}
ASSET_ENTRY_KEYS = {"big_art", "big_palette", "mini_art"}
ALLOWED_ENTRY_KEYS = {"card_const", "card_name", "trunk_card"} | REQUIRED_STATS_KEYS | OPTIONAL_STATS_KEYS | ASSET_ENTRY_KEYS

# Canonical per-card key order — do not reorder or reformat without explicit user approval.
MANIFEST_CARD_KEY_ORDER = (
    "card_const",
    "card_name",
    "atk",
    "def",
    "level",
    "attribute",
    "type",
    "color",
    "is_tuner",
    "monsterEffect",
    "spellEffect",
    "trapEffect",
    "cost",
    "password",
    "description",
    "activation_description",
    "effect_texts",
    "trunk_card",
    "customFieldSpell",
    "lock_after_activation",
    "effect_usage",
    "big_art",
    "big_palette",
    "mini_art",
)


class ManifestValidationError(Exception):
    """Raised when a card manifest fails validation."""


def card_const_to_pascal(card_const: str) -> str:
    return "".join(part.capitalize() for part in card_const.lower().split("_") if part)


def description_symbol(card_const: str) -> str:
    return f"gDescription_{card_const_to_pascal(card_const)}"


def activation_description_symbol(card_const: str) -> str:
    return f"gActivationDescription_{card_const_to_pascal(card_const)}"


def effect_text_symbol(card_const: str, effect_id: str) -> str:
    return (
        f"gActivationDescription_{card_const_to_pascal(card_const)}"
        f"_{card_const_to_pascal(effect_id)}"
    )


def order_card_entry(item: dict) -> dict:
    ordered: dict = {}
    for key in MANIFEST_CARD_KEY_ORDER:
        if key in item:
            ordered[key] = item[key]
    for key in item:
        if key not in ordered:
            ordered[key] = item[key]
    return ordered


def format_password_inline(password: list[int]) -> str:
    return "[" + ", ".join(str(digit) for digit in password) + "]"


def _format_description_block(description: dict, indent: str) -> list[str]:
    lines = [f'{indent}"symbol": {json.dumps(description["symbol"])},']
    pages = description["pages"]
    # One prose string; generator auto-paginates for the vanilla detail layout.
    if isinstance(pages, str):
        lines.append(f'{indent}"pages": {json.dumps(pages)}')
    else:
        lines.append(f'{indent}"pages": [')
        for index, page in enumerate(pages):
            comma = "," if index < len(pages) - 1 else ""
            lines.append(f"{indent}  {json.dumps(page)}{comma}")
        lines.append(f"{indent}]")
    return lines


def format_card_entry(item: dict, base_indent: str = "    ") -> list[str]:
    ordered = order_card_entry(item)
    keys = list(ordered.keys())
    inner = base_indent + "  "
    lines = [f"{base_indent}{{"]

    for index, key in enumerate(keys):
        value = ordered[key]
        comma = "," if index < len(keys) - 1 else ""

        if key == "password":
            lines.append(f'{inner}"password": {format_password_inline(value)}{comma}')
        elif key in ("description", "activation_description"):
            lines.append(f'{inner}"{key}": {{')
            lines.extend(_format_description_block(value, inner + "  "))
            lines.append(f"{inner}}}{comma}")
        elif key == "effect_texts":
            lines.append(f'{inner}"effect_texts": {{')
            effect_ids = list(value.keys())
            for effect_index, effect_id in enumerate(effect_ids):
                effect_comma = "," if effect_index < len(effect_ids) - 1 else ""
                effect = value[effect_id]
                pages = effect["pages"] if isinstance(effect, dict) else (
                    [effect] if isinstance(effect, str) else list(effect)
                )
                if len(pages) == 1:
                    lines.append(
                        f'{inner}  "{effect_id}": {json.dumps(pages[0])}{effect_comma}'
                    )
                else:
                    lines.append(f'{inner}  "{effect_id}": [')
                    for page_index, page in enumerate(pages):
                        page_comma = "," if page_index < len(pages) - 1 else ""
                        lines.append(f"{inner}    {json.dumps(page)}{page_comma}")
                    lines.append(f"{inner}  ]{effect_comma}")
            lines.append(f"{inner}}}{comma}")
        elif isinstance(value, bool):
            lines.append(f'{inner}"{key}": {"true" if value else "false"}{comma}')
        elif isinstance(value, str):
            lines.append(f'{inner}"{key}": {json.dumps(value)}{comma}')
        else:
            lines.append(f'{inner}"{key}": {json.dumps(value)}{comma}')

    lines.append(f"{base_indent}}}")
    return lines


def dump_manifest_json(manifest: dict) -> str:
    cards = manifest["cards"]
    lines = ["{", '  "cards": [']
    for index, item in enumerate(cards):
        lines.extend(format_card_entry(item))
        if index < len(cards) - 1:
            lines[-1] = lines[-1] + ","
    lines.append("  ]")
    lines.append("}")
    return "\n".join(lines) + "\n"


def write_card_state(manifest: dict) -> None:
    """Write a tiny .card_state file so agents skip reading the 18k-line manifest."""
    cards = manifest["cards"]
    total = len(cards)
    max_cost = max(c["cost"] for c in cards) if cards else 0
    last = cards[-1] if cards else {}
    CARD_STATE_PATH.write_text(
        f"# auto-generated by write_card_state\n"
        f"total_cards={total}\n"
        f"next_cost={max_cost + 1}\n"
        f"last_card={last.get('card_const', '')}\n"
        f"last_name={last.get('card_name', '')}\n"
    )


def write_manifest(path: Path | str, manifest: object) -> None:
    path = Path(path)
    validated = validate_manifest(manifest)
    path.write_text(dump_manifest_json(validated))
    write_card_state(validated)


def normalize_description_block(card_const: str, description: dict, *, activation: bool) -> dict:
    if not isinstance(description, dict):
        raise TypeError("description must be a dict")
    pages = description.get("pages")
    if isinstance(pages, str):
        prose = " ".join(pages.split())
        if not prose:
            raise ValueError("description.pages must be a non-empty string")
    elif isinstance(pages, list) and pages:
        # Legacy multi-page arrays → one prose string (generator paginates).
        parts = [" ".join(page.split()) for page in pages if isinstance(page, str) and page.strip()]
        if not parts:
            raise ValueError("description.pages must be a non-empty string (or legacy string array)")
        prose = " ".join(parts)
    else:
        raise ValueError("description.pages must be a non-empty string (or legacy string array)")
    symbol = description.get("symbol")
    if symbol is None:
        symbol = activation_description_symbol(card_const) if activation else description_symbol(card_const)
    elif not isinstance(symbol, str) or not symbol:
        raise ValueError("description.symbol must be a non-empty string when present")
    return {"symbol": symbol, "pages": prose}


def format_json_decode_error(path: Path | str, text: str, exc: json.JSONDecodeError) -> str:
    path = Path(path)
    lines = text.splitlines()
    lineno = exc.lineno
    colno = exc.colno

    parts = [
        f"Invalid JSON in {path}:",
        f"  {exc.msg} (line {lineno}, column {colno}, char {exc.pos})",
        "",
        "Context:",
    ]

    start = max(0, lineno - 3)
    end = min(len(lines), lineno + 2)
    for line_index in range(start, end):
        line_number = line_index + 1
        marker = ">>>" if line_number == lineno else "   "
        parts.append(f"  {marker} {line_number:5d}| {lines[line_index]}")
        if line_number == lineno:
            caret_prefix = f"  {marker} {line_number:5d}| "
            caret = " " * max(0, colno - 1) + "^"
            parts.append(f"{' ' * len(caret_prefix)}{caret}")

    for line_index in range(lineno - 1, -1, -1):
        match = re.search(r'"card_const"\s*:\s*"([^"]+)"', lines[line_index])
        if match:
            parts.extend(["", f"Nearest card entry above error: {match.group(1)}"])
            break

    return "\n".join(parts)


def load_manifest_json(path: Path | str) -> object:
    path = Path(path)
    text = path.read_text()
    try:
        return json.loads(text)
    except json.JSONDecodeError as exc:
        raise ManifestValidationError(format_json_decode_error(path, text, exc)) from exc


def _fail(message: str) -> None:
    raise ManifestValidationError(message)


def validate_manifest(manifest: object) -> dict:
    if not isinstance(manifest, dict):
        _fail("Manifest must be a JSON object with a top-level 'cards' array.")
    cards = manifest.get("cards")
    if not isinstance(cards, list):
        _fail("Manifest must contain a top-level 'cards' array.")
    description_pages_max = 5

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
            try:
                description = normalize_description_block(
                    card_const,
                    description,
                    activation=(desc_key == "activation_description"),
                )
            except ValueError as exc:
                _fail(f"cards[{index}].{desc_key}: {exc}")
            # pages is prose (string); vanilla page count is decided at emit time.
            if not isinstance(description["pages"], str) or not description["pages"]:
                _fail(f"cards[{index}].{desc_key}.pages must be a non-empty string.")
            stats[desc_key] = description

        if "effect_texts" in stats:
            effect_texts = stats["effect_texts"]
            if not isinstance(effect_texts, dict) or not effect_texts:
                _fail(f"cards[{index}].effect_texts must be a non-empty object when present.")
            normalized_effects: dict = {}
            for effect_id, effect in effect_texts.items():
                if not isinstance(effect_id, str) or not re.fullmatch(r"[a-z][a-z0-9_]*", effect_id):
                    _fail(
                        f"cards[{index}].effect_texts keys must be lowercase identifiers "
                        f"(got {effect_id!r})."
                    )
                if isinstance(effect, str):
                    pages = [effect]
                elif isinstance(effect, list):
                    pages = effect
                elif isinstance(effect, dict) and isinstance(effect.get("pages"), list):
                    # Legacy { "pages": [...] } — normalize away.
                    pages = effect["pages"]
                else:
                    _fail(
                        f"cards[{index}].effect_texts.{effect_id} must be a string "
                        f"or an array of strings."
                    )
                if (
                    not pages
                    or len(pages) > description_pages_max
                    or not all(isinstance(page, str) and page for page in pages)
                ):
                    _fail(
                        f"cards[{index}].effect_texts.{effect_id} must contain between "
                        f"1 and {description_pages_max} non-empty strings."
                    )
                normalized_effects[effect_id] = {
                    "symbol": effect_text_symbol(card_const, effect_id),
                    "pages": pages,
                }
            stats["effect_texts"] = normalized_effects

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
            order_card_entry(
                {
                    "card_const": card_const,
                    "card_name": card_name,
                    **stats,
                    **({"trunk_card": item["trunk_card"]} if "trunk_card" in item else {}),
                    **({"customFieldSpell": custom_field_spell} if custom_field_spell is not None else {}),
                }
            )
        )

    return {"cards": validated}
