#!/usr/bin/env python3
"""Validate custom-card trunk quantity helpers stay wired for deck↔trunk moves."""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

TRUNK_HOOKS_C = ROOT / "src_custom" / "trunk_hooks.c"
DECK_MENU_HOOKS_C = ROOT / "src_custom" / "deck_menu_hooks.c"
CARD_HOOKS_C = ROOT / "src_custom" / "card_hooks.c"
SAVE_HOOKS_C = ROOT / "src_custom" / "code_800AC64_hooks.c"
CARD_SHOP_HOOKS_C = ROOT / "src_custom" / "card_shop_hooks.c"
CARD_COUNTS_H = ROOT / "include/constants/card_counts.h"


def _read(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def _extract_function_body(source: str, name: str) -> str:
    match = re.search(
        rf"(?:static\s+)?(?:[\w\s\*]+?\b{re.escape(name)})\([^)]*\)\s*\{{",
        source,
    )
    if not match:
        raise ValueError(f"missing function {name}")

    start = match.end()
    depth = 1
    index = start
    while index < len(source) and depth:
        char = source[index]
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
        index += 1

    if depth:
        raise ValueError(f"unterminated function body for {name}")

    return source[start : index - 1]


def validate_trunk_hooks(source: str, path: Path) -> list[str]:
    errors: list[str] = []

    if "SanitizeCustomCardQtyBuffers" not in source:
        errors.append(
            f"{path}: must define SanitizeCustomCardQtyBuffers to zero "
            "custom-card qty padding and prevent phantom cards"
        )

    try:
        increment_body = _extract_function_body(source, "TrunkMenu_IncrementTrunkQty")
    except ValueError as exc:
        return errors + [f"{path}: {exc}"]

    if "GetTrunkQtyForCard" not in increment_body:
        errors.append(
            f"{path}: TrunkMenu_IncrementTrunkQty must read trunk qty via "
            "GetTrunkQtyForCard so custom cards use gCustomTrunkCardQty"
        )
    if "SetTrunkQtyForCard" not in increment_body:
        errors.append(
            f"{path}: TrunkMenu_IncrementTrunkQty must write trunk qty via "
            "SetTrunkQtyForCard so custom cards use gCustomTrunkCardQty"
        )
    if "TRUNK_CARD_LIMIT" not in increment_body:
        errors.append(
            f"{path}: TrunkMenu_IncrementTrunkQty must clamp to TRUNK_CARD_LIMIT"
        )

    return errors


def validate_phantom_card_guards(source: str, path: Path, function_name: str) -> list[str]:
    errors: list[str] = []

    try:
        body = _extract_function_body(source, function_name)
    except ValueError as exc:
        return [f"{path}: {exc}"]

    if "SanitizeCustomCardQtyBuffers" not in body:
        errors.append(
            f"{path}: {function_name} must call SanitizeCustomCardQtyBuffers "
            "so stale flash padding cannot create phantom custom cards"
        )

    return errors


def validate_card_counts_header(path: Path) -> list[str]:
    errors: list[str] = []

    if not path.is_file():
        return [f"missing {path}"]

    source = _read(path)
    for macro in ("NUM_TOTAL_CARDS", "NUM_CUSTOM_CARDS", "CUSTOM_CARD_QTY_BYTES"):
        if macro not in source:
            errors.append(f"{path}: must define {macro}")

    match = re.search(
        r"#define NUM_CUSTOM_CARDS\s+0x([0-9A-Fa-f]+).*?"
        r"#define CUSTOM_CARD_QTY_BYTES\s+0x([0-9A-Fa-f]+)",
        source,
        re.S,
    )
    if match:
        custom_cards = int(match.group(1), 16)
        qty_bytes = int(match.group(2), 16)
        if qty_bytes < custom_cards:
            errors.append(
                f"{path}: CUSTOM_CARD_QTY_BYTES (0x{qty_bytes:04X}) must be "
                f">= NUM_CUSTOM_CARDS (0x{custom_cards:04X})"
            )

    return errors


def validate_deck_menu_hooks(source: str, path: Path) -> list[str]:
    errors: list[str] = []

    if re.search(r"\bAddCardToTrunk\s*\(", source):
        errors.append(
            f"{path}: deck menu must not call vanilla AddCardToTrunk; "
            "use TrunkMenu_IncrementTrunkQty for custom-card trunk storage"
        )

    for function_name in ("MoveSelectedCardToTrunk", "MoveAllCardsToTrunk"):
        try:
            body = _extract_function_body(source, function_name)
        except ValueError as exc:
            errors.append(f"{path}: {exc}")
            continue

        if "TrunkMenu_IncrementTrunkQty" not in body:
            errors.append(
                f"{path}: {function_name} must call TrunkMenu_IncrementTrunkQty "
                "when returning cards to the trunk"
            )

    return errors


def validate() -> list[str]:
    errors: list[str] = []

    if not TRUNK_HOOKS_C.is_file():
        errors.append(f"missing {TRUNK_HOOKS_C}")
    else:
        trunk_source = _read(TRUNK_HOOKS_C)
        errors.extend(validate_trunk_hooks(trunk_source, TRUNK_HOOKS_C))
        errors.extend(
            validate_phantom_card_guards(
                trunk_source, TRUNK_HOOKS_C, "InitTrunkCards__Replacement"
            )
        )

    if not CARD_HOOKS_C.is_file():
        errors.append(f"missing {CARD_HOOKS_C}")
    else:
        errors.extend(
            validate_phantom_card_guards(
                _read(CARD_HOOKS_C), CARD_HOOKS_C, "sub_803519C__Replacement"
            )
        )

    if not SAVE_HOOKS_C.is_file():
        errors.append(f"missing {SAVE_HOOKS_C}")
    else:
        errors.extend(
            validate_phantom_card_guards(
                _read(SAVE_HOOKS_C), SAVE_HOOKS_C, "SyncCustomCardQtyToFlashBuffers"
            )
        )

    if not CARD_SHOP_HOOKS_C.is_file():
        errors.append(f"missing {CARD_SHOP_HOOKS_C}")
    else:
        errors.extend(
            validate_phantom_card_guards(
                _read(CARD_SHOP_HOOKS_C),
                CARD_SHOP_HOOKS_C,
                "InitNewGameShopCards__Replacement",
            )
        )

    errors.extend(validate_card_counts_header(CARD_COUNTS_H))

    if not DECK_MENU_HOOKS_C.is_file():
        errors.append(f"missing {DECK_MENU_HOOKS_C}")
    else:
        errors.extend(validate_deck_menu_hooks(_read(DECK_MENU_HOOKS_C), DECK_MENU_HOOKS_C))

    return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.parse_args()

    errors = validate()
    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        return 1

    print("validate_trunk_qty: ok")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
