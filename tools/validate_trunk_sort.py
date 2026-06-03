#!/usr/bin/env python3
"""Validate compressed trunk list sorting (hide_unowned + dynamic sort)."""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

TRUNK_HOOKS_C = ROOT / "src_custom" / "trunk_hooks.c"
CARD_SORT_HOOKS_C = ROOT / "src_custom" / "card_sort_hooks.c"
RUNTIME_H = ROOT / "configs" / "runtime.h"

TRUNK_DYNAMIC_SORT_MODES = tuple(range(45, 55))


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


def _extract_if_block(body: str, condition: str) -> str:
    match = re.search(
        rf"if\s*\(\s*{re.escape(condition)}\s*\)\s*\{{",
        body,
    )
    if not match:
        raise ValueError(f"missing if ({condition}) block")

    start = match.end()
    depth = 1
    index = start
    while index < len(body) and depth:
        char = body[index]
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
        index += 1

    if depth:
        raise ValueError(f"unterminated if ({condition}) block")

    return body[start : index - 1]


def validate_trunk_hooks(source: str, path: Path) -> list[str]:
    errors: list[str] = []

    try:
        apply_body = _extract_function_body(source, "ApplyTrunkSortCardList")
    except ValueError as exc:
        return [f"{path}: {exc}"]

    try:
        hide_apply_block = _extract_if_block(apply_body, "TrunkHidesUnownedCards()")
    except ValueError as exc:
        errors.append(f"{path}: ApplyTrunkSortCardList: {exc}")
        hide_apply_block = ""

    if hide_apply_block:
        if "RebuildVisibleTrunkCardList();" in hide_apply_block:
            errors.append(
                f"{path}: ApplyTrunkSortCardList must not rebuild the visible list "
                "after sorting; that discards dynamic/vanilla sort order on compressed "
                "trunk lists"
            )
        if "FinalizeVisibleTrunkSortCardList" not in hide_apply_block:
            errors.append(
                f"{path}: ApplyTrunkSortCardList must call "
                "FinalizeVisibleTrunkSortCardList when hiding unowned cards"
            )
        if "gCardSortContext.cardCount" not in hide_apply_block:
            errors.append(
                f"{path}: ApplyTrunkSortCardList must preserve sort length via "
                "gCardSortContext.cardCount for compressed trunk lists"
            )

    for helper in ("FinalizeVisibleTrunkSortCardList", "GetTrunkSortCardCount"):
        if helper not in source:
            errors.append(f"{path}: missing helper {helper}")

    try:
        finalize_body = _extract_function_body(source, "FinalizeVisibleTrunkSortCardList")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        finalize_body = ""

    if finalize_body:
        if "RebuildVisibleTrunkCardList();" in finalize_body:
            errors.append(
                f"{path}: FinalizeVisibleTrunkSortCardList must not call "
                "RebuildVisibleTrunkCardList"
            )
        for symbol in ("SetTrunkVisibleCounts", "ClampTrunkCursorToVisibleList"):
            if symbol not in finalize_body:
                errors.append(
                    f"{path}: FinalizeVisibleTrunkSortCardList must call {symbol}"
                )

    try:
        sort_count_body = _extract_function_body(source, "GetTrunkSortCardCount")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        sort_count_body = ""

    if sort_count_body:
        if (
            "TrunkHidesUnownedCards() || gRuntimeConfig.dynamic_card_shop_and_trunk_sorting"
            not in sort_count_body
        ):
            errors.append(
                f"{path}: GetTrunkSortCardCount must treat hide-unowned and dynamic "
                "sorting as compressed-list modes"
            )
        if "return GetTrunkCardCount();" not in sort_count_body:
            errors.append(
                f"{path}: GetTrunkSortCardCount must return GetTrunkCardCount() for "
                "compressed/dynamic trunk sorting"
            )
        if "return NUM_TRUE_CARDS;" not in sort_count_body:
            errors.append(
                f"{path}: GetTrunkSortCardCount must keep NUM_TRUE_CARDS only for the "
                "full vanilla trunk path"
            )

    try:
        build_sort_body = _extract_function_body(source, "BuildTrunkSortCardList")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        build_sort_body = ""

    if build_sort_body:
        if "TrunkHidesUnownedCards()" not in build_sort_body:
            errors.append(
                f"{path}: BuildTrunkSortCardList must branch on TrunkHidesUnownedCards()"
            )
        elif "return;" not in build_sort_body:
            errors.append(
                f"{path}: BuildTrunkSortCardList must return early when hiding unowned "
                "cards so sorting uses the pre-built compressed list"
            )

    for sort_entry in (
        "TrunkMenuDefaultSort__Replacement",
        "ApplyNewSortMode__Replacement",
    ):
        try:
            entry_body = _extract_function_body(source, sort_entry)
        except ValueError as exc:
            errors.append(f"{path}: {exc}")
            continue

        sort_pos = entry_body.find("SortCardsAccordingToContext();")
        apply_pos = entry_body.find("ApplyTrunkSortCardList();")
        clear_pos = entry_body.find("gCardSortContext.cardCount = 0;")

        if sort_pos < 0 or apply_pos < 0 or clear_pos < 0:
            errors.append(
                f"{path}: {sort_entry} must call SortCardsAccordingToContext, "
                "ApplyTrunkSortCardList, then clear gCardSortContext.cardCount"
            )
            continue

        if not (sort_pos < apply_pos < clear_pos):
            errors.append(
                f"{path}: {sort_entry} must apply sorted cards before clearing "
                "gCardSortContext.cardCount"
            )

        for needle in (
            "gCardSortContext.cards = gTrunkMenuSortCards;",
            "gCardSortContext.cardCount = GetTrunkSortCardCount();",
            "SortCardsAccordingToContext();",
            "ApplyTrunkSortCardList();",
        ):
            if needle not in entry_body:
                errors.append(f"{path}: {sort_entry} missing `{needle}`")

    return errors


def validate_card_sort_hooks(source: str, path: Path) -> list[str]:
    errors: list[str] = []

    try:
        sort_context_body = _extract_function_body(
            source, "SortCardsAccordingToContext__Replacement"
        )
    except ValueError as exc:
        return [f"{path}: {exc}"]

    if "dynamic_card_shop_and_trunk_sorting" not in sort_context_body:
        errors.append(
            f"{path}: SortCardsAccordingToContext__Replacement must gate on "
            "dynamic_card_shop_and_trunk_sorting"
        )
    for needle in (
        "BuildDynamicShopOrTrunkSort();",
        "CopySortedCardsBack();",
    ):
        if needle not in sort_context_body:
            errors.append(
                f"{path}: SortCardsAccordingToContext__Replacement missing `{needle}`"
            )

    try:
        owned_qty_body = _extract_function_body(source, "GetOwnedQtyForDynamicSort")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        owned_qty_body = ""

    if owned_qty_body:
        if "sortMode >= 45 && sortMode <= 54" not in owned_qty_body:
            errors.append(
                f"{path}: GetOwnedQtyForDynamicSort must handle trunk sort modes 45-54"
            )
        elif "gTotalCardQty" not in owned_qty_body:
            errors.append(
                f"{path}: trunk dynamic sorts (modes 45-54) must use gTotalCardQty"
            )

    try:
        build_dynamic_body = _extract_function_body(source, "BuildDynamicShopOrTrunkSort")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        build_dynamic_body = ""

    if build_dynamic_body:
        if "gCardSortContext.cardCount" not in build_dynamic_body:
            errors.append(
                f"{path}: BuildDynamicShopOrTrunkSort must iterate "
                "gCardSortContext.cardCount entries"
            )
        if "gCardSortContext.cards[i]" not in build_dynamic_body:
            errors.append(
                f"{path}: BuildDynamicShopOrTrunkSort must read card ids from "
                "gCardSortContext.cards"
            )

    try:
        copy_back_body = _extract_function_body(source, "CopySortedCardsBack")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        copy_back_body = ""

    if copy_back_body and "gCardSortContext.cards[i]" not in copy_back_body:
        errors.append(
            f"{path}: CopySortedCardsBack must write sorted ids back to "
            "gCardSortContext.cards"
        )

    switch_body_match = re.search(
        r"static u8 GetDynamicSortKind\(u8 sortMode\)\s*\{.*?switch \(sortMode\)\s*\{(.*?)\n\s*return DYNAMIC_SORT_NONE;",
        source,
        flags=re.DOTALL,
    )
    if not switch_body_match:
        errors.append(f"{path}: missing GetDynamicSortKind switch table")
    else:
        switch_body = switch_body_match.group(1)
        for mode in TRUNK_DYNAMIC_SORT_MODES:
            if f"case {mode}:" not in switch_body:
                errors.append(
                    f"{path}: GetDynamicSortKind missing trunk sort mode case {mode}"
                )

    return errors


def validate_runtime_header(source: str, path: Path) -> list[str]:
    errors: list[str] = []
    for field in (
        "hide_unowned_trunk_cards",
        "dynamic_card_shop_and_trunk_sorting",
    ):
        if field not in source:
            errors.append(f"{path}: missing runtime config field {field}")
    return errors


def validate_sources(root: Path = ROOT) -> list[str]:
    errors: list[str] = []

    trunk_path = root / TRUNK_HOOKS_C.relative_to(ROOT)
    sort_path = root / CARD_SORT_HOOKS_C.relative_to(ROOT)
    runtime_path = root / RUNTIME_H.relative_to(ROOT)

    if not trunk_path.is_file():
        errors.append(f"missing {trunk_path}")
    else:
        errors.extend(validate_trunk_hooks(_read(trunk_path), trunk_path))

    if not sort_path.is_file():
        errors.append(f"missing {sort_path}")
    else:
        errors.extend(validate_card_sort_hooks(_read(sort_path), sort_path))

    if runtime_path.is_file():
        errors.extend(validate_runtime_header(_read(runtime_path), runtime_path))
    else:
        errors.append(f"missing {runtime_path}")

    return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT)
    args = parser.parse_args()

    errors = validate_sources(args.root)
    if errors:
        for message in errors:
            print(message, file=sys.stderr)
        return 1

    print("validate_trunk_sort: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
