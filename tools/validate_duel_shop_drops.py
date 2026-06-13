#!/usr/bin/env python3
"""Validate duel win shop drop hooks: custom pool roll, popup parity, LynJump wiring."""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

HOOKS_C = ROOT / "src_custom" / "code_801EF30_hooks.c"
LYNJUMP_EVENT = ROOT / "src_custom" / "LynJump.event"
CARD_TRUNK_INC = ROOT / "src_custom" / "generated" / "card_trunk_generated.inc"


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


def _lynjump_poin_at_org(source: str, org_hex: str) -> str | None:
    blocks = re.split(r"\bPOP\b", source)
    org_pattern = re.compile(rf"ORG\s+\${org_hex}\b", re.IGNORECASE)
    poin_pattern = re.compile(r"POIN\s+(\w+)")

    for block in blocks:
        if not org_pattern.search(block):
            continue
        match = poin_pattern.search(block)
        if match:
            return match.group(1)
    return None


def validate_hooks(source: str, path: Path) -> list[str]:
    errors: list[str] = []

    if "LYN_REPLACE_CHECK(sub_8020050)" not in source:
        errors.append(f"{path}: missing LYN_REPLACE_CHECK(sub_8020050)")

    try:
        roll_body = _extract_function_body(source, "sub_8020050__Replacement")
    except ValueError as exc:
        return errors + [f"{path}: {exc}"]

    for needle in (
        "gDuelData.duelist.shopCards",
        "RandRangeU16(0, 29999)",
        "enable_custom_cards_past_800",
        "gCustomTrunkCards",
        "NUM_CUSTOM_TRUNK_CARDS",
        "PickUniformRewardCard",
        "vanillaMaxChance / 4",
    ):
        if needle not in roll_body:
            errors.append(
                f"{path}: sub_8020050__Replacement must include `{needle}` "
                "so custom trunk cards share the shop drop pool"
            )

    try:
        loop_body = _extract_function_body(source, "RunDuelShopDropLoop")
    except ValueError as exc:
        return errors + [f"{path}: {exc}"]

    for needle in (
        "sub_8020050()",
        "GetShopCardQty(cardId)",
        "AddCardQtyToShop2(cardId, 1)",
        "WasShopDropRolledThisWin",
    ):
        if needle not in loop_body:
            errors.append(f"{path}: RunDuelShopDropLoop must call `{needle}`")

    try:
        display_body = _extract_function_body(source, "DisplayDuelShopDropText")
    except ValueError as exc:
        return errors + [f"{path}: {exc}"]

    if "RunDuelShopDropLoop(ids, qtys, &count)" not in display_body:
        errors.append(
            f"{path}: DisplayDuelShopDropText must roll and add shop stock "
            "via RunDuelShopDropLoop before building popup text"
        )
    if "AppendCardShopDropLine" not in display_body:
        errors.append(
            f"{path}: DisplayDuelShopDropText must use literal card names "
            "via AppendCardShopDropLine"
        )
    if re.search(r"AppendCardShopDropToken|sub_8041C94\([^)]*arg1", display_body):
        errors.append(
            f"{path}: DisplayDuelShopDropText must not use duel textbox #2/#3 "
            "card-name tokens; popup lists up to three distinct cards"
        )
    if "sub_8041C94(textBuffer, 0, 0, 0, 0)" not in display_body:
        errors.append(
            f"{path}: DisplayDuelShopDropText must call sub_8041C94 with zero args"
        )

    try:
        handle_win_body = _extract_function_body(source, "HandleWin__Replacement")
    except ValueError as exc:
        return errors + [f"{path}: {exc}"]

    if (
        "if (gRuntimeConfig.show_duel_shop_card_drops != TRUE)\n"
        "    AddCardDropsToShop__Replacement();"
    ) not in handle_win_body:
        errors.append(
            f"{path}: HandleWin__Replacement must add shop drops early only when "
            "the popup is disabled"
        )
    if "DisplayDuelShopDropText();" not in handle_win_body:
        errors.append(
            f"{path}: HandleWin__Replacement must call DisplayDuelShopDropText "
            "in the victory reward sequence"
        )

    return errors


def validate_lynjump(source: str, path: Path) -> list[str]:
    errors: list[str] = []
    target = _lynjump_poin_at_org(source, "20050")

    if target != "sub_8020050__Replacement":
        errors.append(
            f"{path}: expected POIN sub_8020050__Replacement at ORG $20050, "
            f"found {target!r}"
        )

    return errors


def validate_card_trunk_inc(source: str, path: Path) -> list[str]:
    errors: list[str] = []

    if "gCustomTrunkCards" not in source:
        errors.append(f"{path}: missing gCustomTrunkCards table for shop drop pool")
    if "NUM_CUSTOM_TRUNK_CARDS" not in source:
        errors.append(f"{path}: missing NUM_CUSTOM_TRUNK_CARDS")

    return errors


def validate() -> list[str]:
    errors: list[str] = []

    if not HOOKS_C.is_file():
        errors.append(f"missing {HOOKS_C}")
    else:
        errors.extend(validate_hooks(_read(HOOKS_C), HOOKS_C))

    if not LYNJUMP_EVENT.is_file():
        errors.append(f"missing {LYNJUMP_EVENT}")
    else:
        errors.extend(validate_lynjump(_read(LYNJUMP_EVENT), LYNJUMP_EVENT))

    if not CARD_TRUNK_INC.is_file():
        errors.append(f"missing {CARD_TRUNK_INC}")
    else:
        errors.extend(validate_card_trunk_inc(_read(CARD_TRUNK_INC), CARD_TRUNK_INC))

    return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.parse_args()

    errors = validate()
    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        return 1

    print("validate_duel_shop_drops: ok")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
