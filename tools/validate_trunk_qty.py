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

    try:
        increment_body = _extract_function_body(source, "TrunkMenu_IncrementTrunkQty")
    except ValueError as exc:
        return [f"{path}: {exc}"]

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
        errors.extend(validate_trunk_hooks(_read(TRUNK_HOOKS_C), TRUNK_HOOKS_C))

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
