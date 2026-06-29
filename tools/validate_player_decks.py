#!/usr/bin/env python3
"""Validate multiple player deck layout and switch/save invariants."""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from ram_map_layout import read_ram_map_text  # noqa: E402

RAM_MAP = ROOT / "asm" / "ram_map.s"
PLAYER_DECKS_C = ROOT / "src_custom" / "player_decks" / "player_decks.c"
PLAYER_DECKS_H = ROOT / "include" / "player_decks.h"
TRUNK_HOOKS_C = ROOT / "src_custom" / "trunk_hooks.c"
SAVE_HOOKS_C = ROOT / "src_custom" / "code_800AC64_hooks.c"
CARD_HOOKS_C = ROOT / "src_custom" / "card_hooks.c"

PLAYER_DECK_CARD_BYTES = 0x50
PLAYER_DECK1_SAVE_BUFFER_OFFSET = 0x332
NUM_TOTAL_CARDS = 0x0341

EWRAM_ARRAY_RE = re.compile(
    r"_kernel_malloc_ewram_array\s+(\w+),\s*(\S+)"
)
EWRAM_RE = re.compile(r"_kernel_malloc_ewram\s+(\w+),\s*(0x[0-9A-Fa-f]+|\d+)")

FORBIDDEN_SYMBOLS = (
    "gPlayerDeckSaveStaging",
    "LoadDeck1FromVanillaStorage",
    "SaveDeck1ToStaging",
    "Deck1StagingIsValid",
    "LoadDeck1FromSaveBuffer",
    "MarkDeck1StagingValid",
    "PLAYER_DECK1_STAGING_MAGIC",
)

REQUIRED_EWRAM_ARRAYS = (
    "gPlayerDeck1Cards",
    "gPlayerDeck2Cards",
    "gPlayerDeck3Cards",
)

REQUIRED_EWRAM_BYTES = ("gPlayerDeckSaveRestoreActiveDeck",)

REQUIRED_FLASH_MALLOC = (
    "gPlayerDeck2Cards",
    "gPlayerDeck3Cards",
    "gActiveDeckIndex",
    "gPlayerDeckSaveMagic",
)

REQUIRED_HOOK_CALLS = {
    SAVE_HOOKS_C: (
        "PlayerDecks_OnSaveSlotWrite();",
        "PlayerDecks_OnSaveSlotRead();",
    ),
    CARD_HOOKS_C: (
        "PlayerDecks_PrepareVanillaSaveBuffer();",
        "PlayerDecks_RestoreAfterVanillaSaveBuffer();",
    ),
}


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


def validate_ram_map(root: Path) -> list[str]:
    errors: list[str] = []
    path = root / RAM_MAP.relative_to(ROOT)
    if not path.is_file():
        return [f"missing {path}"]

    text = read_ram_map_text(root)
    ewram_arrays: dict[str, str] = {}
    ewram_bytes: set[str] = set()

    for line in text.splitlines():
        stripped = line.split("@", 1)[0].strip()
        match = EWRAM_ARRAY_RE.search(stripped)
        if match:
            ewram_arrays[match.group(1)] = match.group(2)
            continue
        match = EWRAM_RE.search(stripped)
        if match:
            ewram_bytes.add(match.group(1))

    for name in REQUIRED_EWRAM_ARRAYS:
        if name not in ewram_arrays:
            errors.append(f"{path}: missing EWRAM array {name}")
        elif ewram_arrays[name] != "PLAYER_DECK_CARD_BYTES":
            errors.append(
                f"{path}: {name} must use PLAYER_DECK_CARD_BYTES "
                f"(found size token {ewram_arrays[name]!r})"
            )

    for name in REQUIRED_EWRAM_BYTES:
        if name not in ewram_bytes:
            errors.append(f"{path}: missing EWRAM byte {name}")

    if "gPlayerDeckSaveStaging" in text:
        errors.append(
            f"{path}: gPlayerDeckSaveStaging was removed; use gPlayerDeck1Cards "
            "and gPlayerDeckSaveRestoreActiveDeck"
        )

    for name in REQUIRED_FLASH_MALLOC:
        if f"_kernel_malloc_flash {name}," not in text:
            errors.append(f"{path}: missing flash allocation _kernel_malloc_flash {name}")

    return errors


def validate_player_decks_c(root: Path) -> list[str]:
    errors: list[str] = []
    path = root / PLAYER_DECKS_C.relative_to(ROOT)
    if not path.is_file():
        return [f"missing {path}"]

    source = _read(path)

    for token in FORBIDDEN_SYMBOLS:
        if token in source:
            errors.append(f"{path}: forbidden legacy symbol {token}")

    if f"#define PLAYER_DECK1_SAVE_BUFFER_OFFSET {PLAYER_DECK1_SAVE_BUFFER_OFFSET:#x}" not in source.replace(
        "0X", "0x"
    ) and f"#define PLAYER_DECK1_SAVE_BUFFER_OFFSET 0x{PLAYER_DECK1_SAVE_BUFFER_OFFSET:x}" not in source:
        errors.append(
            f"{path}: PLAYER_DECK1_SAVE_BUFFER_OFFSET must be "
            f"{PLAYER_DECK1_SAVE_BUFFER_OFFSET:#x}"
        )

    try:
        backing_body = _extract_function_body(source, "GetDeckCardsBacking")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        backing_body = ""

    if backing_body:
        for symbol in ("gPlayerDeck1Cards", "gPlayerDeck2Cards", "gPlayerDeck3Cards"):
            if symbol not in backing_body:
                errors.append(f"{path}: GetDeckCardsBacking must return {symbol}")

    try:
        save_body = _extract_function_body(source, "SaveDeckCardsToBacking")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        save_body = ""

    if save_body and "GetDeckCardsBacking(deckIndex)" not in save_body.replace(" ", ""):
        if "GetDeckCardsBacking(deckIndex)" not in save_body:
            errors.append(
                f"{path}: SaveDeckCardsToBacking must use GetDeckCardsBacking for all decks"
            )

    try:
        load_body = _extract_function_body(source, "LoadDeckCardsFromBacking")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        load_body = ""

    if load_body:
        if "GetDeckCardsBacking(deckIndex)" not in load_body:
            errors.append(
                f"{path}: LoadDeckCardsFromBacking must load via GetDeckCardsBacking"
            )
        if "SanitizeDeckCards(gDeckMenu.cards)" not in load_body:
            errors.append(f"{path}: LoadDeckCardsFromBacking must sanitize gDeckMenu.cards")

    try:
        sync_in_body = _extract_function_body(source, "SyncDeck1FromSaveSlotMenu")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        sync_in_body = ""

    if sync_in_body and "gPlayerDeck1Cards" not in sync_in_body:
        errors.append(f"{path}: SyncDeck1FromSaveSlotMenu must copy into gPlayerDeck1Cards")

    try:
        sync_out_body = _extract_function_body(source, "SyncDeck1ToSaveBuffer")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        sync_out_body = ""

    if sync_out_body and "gPlayerDeck1Cards" not in sync_out_body:
        errors.append(f"{path}: SyncDeck1ToSaveBuffer must copy from gPlayerDeck1Cards")

    try:
        set_active_body = _extract_function_body(source, "PlayerDecks_SetActiveAndLoad")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        set_active_body = ""

    if set_active_body:
        if "if (deckIndex != gActiveDeckIndex)" not in set_active_body.replace(" ", ""):
            if "if (deckIndex != gActiveDeckIndex)" not in set_active_body:
                errors.append(
                    f"{path}: PlayerDecks_SetActiveAndLoad must skip reload when "
                    "deckIndex == gActiveDeckIndex"
                )
        if set_active_body.count("PlayerDecks_FlushActive();") < 1:
            errors.append(
                f"{path}: PlayerDecks_SetActiveAndLoad must flush before switching decks"
            )

    try:
        prepare_body = _extract_function_body(source, "PlayerDecks_PrepareVanillaSaveBuffer")
    except ValueError as exc:
        errors.append(f"{path}: {exc}")
        prepare_body = ""

    if prepare_body:
        if "CopyDeckCards(gDeckMenu.cards, gPlayerDeck1Cards)" not in prepare_body:
            errors.append(
                f"{path}: PlayerDecks_PrepareVanillaSaveBuffer must copy "
                "gPlayerDeck1Cards into gDeckMenu when another deck is active"
            )
        if "IsCompleteDeck(sDeck1Cards)" in prepare_body or "IsCompleteDeck(gPlayerDeck1Cards)" in prepare_body:
            errors.append(
                f"{path}: PlayerDecks_PrepareVanillaSaveBuffer must not gate deck 1 "
                "restore on IsCompleteDeck"
            )
        if "gPlayerDeckSaveRestoreActiveDeck" not in prepare_body:
            errors.append(
                f"{path}: PlayerDecks_PrepareVanillaSaveBuffer must store "
                "gPlayerDeckSaveRestoreActiveDeck"
            )

    if "gPlayerDeckSaveRestoreActiveDeck" not in source:
        errors.append(f"{path}: must use gPlayerDeckSaveRestoreActiveDeck")

    return errors


def validate_headers_and_hooks(root: Path) -> list[str]:
    errors: list[str] = []

    header_path = root / PLAYER_DECKS_H.relative_to(ROOT)
    if header_path.is_file():
        header = _read(header_path)
        if "gPlayerDeck1Cards" not in header:
            errors.append(f"{header_path}: missing extern gPlayerDeck1Cards")
        if "gPlayerDeckSaveStaging" in header:
            errors.append(f"{header_path}: remove gPlayerDeckSaveStaging")
        if "gPlayerDeckSaveRestoreActiveDeck" not in header:
            errors.append(f"{header_path}: missing gPlayerDeckSaveRestoreActiveDeck")
    else:
        errors.append(f"missing {header_path}")

    trunk_path = root / TRUNK_HOOKS_C.relative_to(ROOT)
    if trunk_path.is_file():
        trunk = _read(trunk_path)
        if "gPlayerDeckSaveStaging" in trunk:
            errors.append(f"{trunk_path}: must use gPlayerDeck1Cards, not gPlayerDeckSaveStaging")
        if "gPlayerDeck1Cards" not in trunk:
            errors.append(f"{trunk_path}: inactive deck 1 totals must read gPlayerDeck1Cards")
    else:
        errors.append(f"missing {trunk_path}")

    for hook_path, calls in REQUIRED_HOOK_CALLS.items():
        path = root / hook_path.relative_to(ROOT)
        if not path.is_file():
            errors.append(f"missing {path}")
            continue
        text = _read(path)
        for call in calls:
            if call not in text:
                errors.append(f"{path}: missing required call {call}")

    return errors


def validate_switch_invariants() -> list[str]:
    errors: list[str] = []

    sys_path = str(ROOT / "tools")
    if sys_path not in sys.path:
        sys.path.insert(0, sys_path)

    from player_deck_persist import (  # noqa: E402
        CARD_NONE,
        PLAYER_DECK_CARD_COUNT,
        simulate_save_slot_read,
        switch_active_deck,
    )

    def make_deck(base: int, count: int = PLAYER_DECK_CARD_COUNT) -> list[int]:
        deck = [CARD_NONE] * PLAYER_DECK_CARD_COUNT
        for i in range(min(count, PLAYER_DECK_CARD_COUNT)):
            deck[i] = base + i
        return deck

    deck1 = make_deck(0x0100, 40)
    deck2 = make_deck(0x0200, 24)
    deck3 = make_deck(0x0300, 15)
    empty3 = [CARD_NONE] * PLAYER_DECK_CARD_COUNT

    menu, b1, b2, b3, active = switch_active_deck(
        deck1, deck1, deck2, empty3, 1, 2, NUM_TOTAL_CARDS
    )
    if b1 != deck1:
        errors.append("switch invariant failed: leaving deck 1 must preserve gPlayerDeck1Cards")
    menu, b1, b2, b3, active = switch_active_deck(
        menu, b1, b2, b3, active, 1, NUM_TOTAL_CARDS
    )
    if menu != deck1:
        errors.append("switch invariant failed: deck 1 -> deck 2 -> deck 1 must restore deck 1")

    menu, b1, b2, b3, active = deck1[:], deck1[:], deck2[:], deck3[:], 1
    for target in (2, 3, 1, 3, 2, 1):
        expected = {1: deck1, 2: deck2, 3: deck3}[target]
        menu, b1, b2, b3, active = switch_active_deck(
            menu, b1, b2, b3, active, target, NUM_TOTAL_CARDS
        )
        if menu != expected or active != target:
            errors.append(
                f"switch invariant failed: active deck {target} must load its backing store"
            )

    edited = make_deck(0x0150, 40)
    menu, b1, _, _, _ = switch_active_deck(
        edited, deck1, deck2, deck3, 1, 1, NUM_TOTAL_CARDS
    )
    if menu != edited or b1 != deck1:
        errors.append(
            "switch invariant failed: selecting the same deck must not reload from backing"
        )

    menu, b1, b2, b3, active = simulate_save_slot_read(
        deck1, deck2, deck3, 2, NUM_TOTAL_CARDS
    )
    if active != 1 or menu != deck1 or b1 != deck1:
        errors.append(
            "save-read invariant failed: incomplete deck 2 must fall back to deck 1"
        )

    return errors


def validate_elf(elf_path: Path, nm_path: str = "arm-none-eabi-nm") -> list[str]:
    errors: list[str] = []

    if not elf_path.is_file():
        return [f"missing ELF for layout check: {elf_path}"]

    result = subprocess.run(
        [nm_path, str(elf_path)],
        capture_output=True,
        text=True,
        check=False,
    )
    if result.returncode != 0:
        return [result.stderr or result.stdout or f"{nm_path} failed"]

    symbols: dict[str, int] = {}
    for line in result.stdout.splitlines():
        parts = line.split()
        if len(parts) >= 3:
            symbols[parts[2]] = int(parts[0], 16)

    for name in REQUIRED_EWRAM_ARRAYS:
        end_name = f"{name}End"
        if name not in symbols:
            errors.append(f"{elf_path}: missing symbol {name}")
            continue
        if end_name in symbols:
            size = symbols[end_name] - symbols[name]
            if size != PLAYER_DECK_CARD_BYTES:
                errors.append(
                    f"{elf_path}: {name} size is {size:#x}, expected "
                    f"{PLAYER_DECK_CARD_BYTES:#x}"
                )

    if "gPlayerDeckSaveStaging" in symbols:
        errors.append(f"{elf_path}: gPlayerDeckSaveStaging must not be linked")

    if "gPlayerDeckSaveRestoreActiveDeck" not in symbols:
        errors.append(f"{elf_path}: missing symbol gPlayerDeckSaveRestoreActiveDeck")

    return errors


def validate_sources(root: Path = ROOT) -> list[str]:
    errors: list[str] = []
    errors.extend(validate_ram_map(root))
    errors.extend(validate_player_decks_c(root))
    errors.extend(validate_headers_and_hooks(root))
    errors.extend(validate_switch_invariants())
    return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT)
    parser.add_argument("--elf", type=Path, default=None)
    parser.add_argument("--nm", default="arm-none-eabi-nm")
    args = parser.parse_args()

    errors = validate_sources(args.root)
    if args.elf is not None:
        errors.extend(validate_elf(args.elf, args.nm))

    if errors:
        for message in errors:
            print(message, file=sys.stderr)
        return 1

    print("validate_player_decks: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
