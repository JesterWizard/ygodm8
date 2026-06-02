#!/usr/bin/env python3
"""Validate duel popup textbox clear behavior in custom hooks."""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

HOOKS_C = ROOT / "src_custom" / "code_8041C94_hooks.c"
DUEL_TEXTBOX_C = ROOT / "src" / "duel" / "duel_textbox.c"
DUEL_TEXTBOX_H = ROOT / "include" / "duel_textbox.h"

DUEL_TEXTBOX_CLEAR_ROWS = (
    "                            ",
    "                            ",
    "                            ",
    "                             ",
)
DUEL_TEXTBOX_CLEAR_TEXT = "".join(DUEL_TEXTBOX_CLEAR_ROWS)
DUEL_TEXTBOX_CLEAR_LEN = len(DUEL_TEXTBOX_CLEAR_TEXT)
DUEL_TEXTBOX_TILE_DEST = "0x88A0"
DUEL_TEXTBOX_COPY_FLAGS = "0x101"
SUB_8041C94_SYMBOL = "sub_8041C94"
SUB_8041C94_ADDRESS = 0x08041C94
MIN_CLEAR_SPACES = 84


def _extract_c_string_literals(block: str) -> str:
    parts = re.findall(r'"((?:[^"\\]|\\.)*)"', block, flags=re.DOTALL)
    return "".join(parts)


def _read(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def _extract_assignment_block(source: str, marker: str) -> str:
    start = source.index(marker) + len(marker)
    end = source.index(";", start)
    return source[start:end]


def extract_hook_clear_text(source: str) -> str:
    block = _extract_assignment_block(source, "sTextboxClearSpaces[] APPEND_RODATA =")
    return _extract_c_string_literals(block)


def extract_vanilla_clear_text(source: str) -> str:
    block = _extract_assignment_block(source, "gText_Spaces[] = _(")
    return _extract_c_string_literals(block)


def extract_function_body(source: str, name: str) -> str:
    match = re.search(rf"void {re.escape(name)}\([^)]*\)\s*\{{", source)
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


def validate_sources(root: Path = ROOT) -> list[str]:
    errors: list[str] = []

    hooks_path = root / HOOKS_C.relative_to(ROOT)
    duel_textbox_path = root / DUEL_TEXTBOX_C.relative_to(ROOT)
    duel_textbox_header = root / DUEL_TEXTBOX_H.relative_to(ROOT)

    if not hooks_path.is_file():
        return [f"missing {hooks_path}"]

    hooks_source = _read(hooks_path)
    hook_clear = extract_hook_clear_text(hooks_source)

    if len(hook_clear) < MIN_CLEAR_SPACES:
        errors.append(
            f"{hooks_path}: sTextboxClearSpaces is too short "
            f"({len(hook_clear)} chars; need at least {MIN_CLEAR_SPACES})"
        )

    if hook_clear != DUEL_TEXTBOX_CLEAR_TEXT:
        errors.append(
            f"{hooks_path}: sTextboxClearSpaces must match vanilla gText_Spaces "
            f"({DUEL_TEXTBOX_CLEAR_LEN} spaces across four rows)"
        )

    if "ClearDuelPopupTextboxTiles();" not in hooks_source:
        errors.append(f"{hooks_path}: missing ClearDuelPopupTextboxTiles helper")

    clear_helper = extract_function_body(hooks_source, "ClearDuelPopupTextboxTiles")
    if DUEL_TEXTBOX_TILE_DEST not in clear_helper:
        errors.append(
            f"{hooks_path}: ClearDuelPopupTextboxTiles must write to "
            f"gBgVram.cbb0 + {DUEL_TEXTBOX_TILE_DEST}"
        )
    if "sTextboxClearSpaces" not in clear_helper:
        errors.append(
            f"{hooks_path}: ClearDuelPopupTextboxTiles must use sTextboxClearSpaces"
        )
    if DUEL_TEXTBOX_COPY_FLAGS not in clear_helper:
        errors.append(
            f"{hooks_path}: ClearDuelPopupTextboxTiles must pass flag "
            f"{DUEL_TEXTBOX_COPY_FLAGS}"
        )

    try:
        replacement_body = extract_function_body(
            hooks_source, "WaitForTextboxAdvanceInput__Replacement"
        )
    except ValueError as exc:
        errors.append(str(exc))
        replacement_body = ""

    if replacement_body:
        ai_block_match = re.search(
            r"if \(DebugAiMode_IsBothSides\(\) == TRUE\)\s*\{(.*?)\n\s*return;",
            replacement_body,
            flags=re.DOTALL,
        )
        if not ai_block_match:
            errors.append(
                f"{hooks_path}: missing DebugAiMode_IsBothSides auto-advance block"
            )
        elif "ClearDuelPopupTextboxTiles();" not in ai_block_match.group(1):
            errors.append(
                f"{hooks_path}: AI both-sides auto-advance must call "
                "ClearDuelPopupTextboxTiles()"
            )

        button_block_match = re.search(
            r"if \(gNewButtons & \(A_BUTTON \| B_BUTTON \| R_BUTTON\)\)\s*\{(.*?)\n\s*\} else",
            replacement_body,
            flags=re.DOTALL,
        )
        if not button_block_match:
            errors.append(
                f"{hooks_path}: missing A/B/R dismiss block in "
                "WaitForTextboxAdvanceInput__Replacement"
            )
        elif "ClearDuelPopupTextboxTiles();" not in button_block_match.group(1):
            errors.append(
                f"{hooks_path}: A/B/R dismiss must call ClearDuelPopupTextboxTiles()"
            )

    if duel_textbox_path.is_file():
        duel_source = _read(duel_textbox_path)
        vanilla_clear = extract_vanilla_clear_text(duel_source)
        if vanilla_clear != DUEL_TEXTBOX_CLEAR_TEXT:
            errors.append(
                f"{duel_textbox_path}: unexpected gText_Spaces layout; "
                "update DUEL_TEXTBOX_CLEAR_TEXT in validator"
            )
        if "ClearDuelPopupTextboxTiles" in duel_source:
            errors.append(
                f"{duel_textbox_path}: ClearDuelPopupTextboxTiles must stay in "
                f"{hooks_path.name} to preserve fixed ROM addresses"
            )

    if duel_textbox_header.is_file():
        header_source = _read(duel_textbox_header)
        if "ClearDuelPopupTextboxTiles" in header_source:
            errors.append(
                f"{duel_textbox_header}: do not export ClearDuelPopupTextboxTiles; "
                "keep clear logic in custom hooks only"
            )

    return errors


def validate_elf(elf_path: Path, nm_path: str = "arm-none-eabi-nm") -> list[str]:
    errors: list[str] = []

    if not elf_path.is_file():
        return [f"missing ELF for ROM layout check: {elf_path}"]

    result = subprocess.run(
        [nm_path, str(elf_path)],
        capture_output=True,
        text=True,
        check=False,
    )
    if result.returncode != 0:
        return [result.stderr or result.stdout or f"{nm_path} failed"]

    symbol_address = None
    for line in result.stdout.splitlines():
        parts = line.split()
        if len(parts) >= 3 and parts[2] == SUB_8041C94_SYMBOL:
            symbol_address = int(parts[0], 16)
            break

    if symbol_address is None:
        errors.append(f"{elf_path}: symbol {SUB_8041C94_SYMBOL} not found")
    elif symbol_address != SUB_8041C94_ADDRESS:
        errors.append(
            f"{elf_path}: {SUB_8041C94_SYMBOL} is at "
            f"0x{symbol_address:08X}, expected 0x{SUB_8041C94_ADDRESS:08X}"
        )

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

    print("validate_duel_popup_textbox: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
