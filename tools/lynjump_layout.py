#!/usr/bin/env python3
"""Parse LynJump.event hooks and detect POIN placement bugs."""

from __future__ import annotations

import pathlib
import re
import subprocess
from dataclasses import dataclass

ROOT = pathlib.Path(__file__).resolve().parent.parent
ROM_BASE = 0x08000000
STANDARD_HOOK_SIZE = 12
POIN_RE = re.compile(r"POIN\s+(\w+)")
ORG_RE = re.compile(r"ORG\s+\$([0-9A-Fa-f]+)")
WORD_RE = re.compile(r"WORD\s+(.+)")
MAP_SYMBOL_RE = re.compile(r"^\s+0x([0-9A-Fa-f]+)\s+(\w+)\s*$")


@dataclass(frozen=True)
class HookPoinSite:
    event_path: pathlib.Path
    hook_org: int
    replacement_name: str
    poin_org: int
    ldr_pc_offset: int


def marker_name(name: str) -> str:
    if name.endswith("__Replacement"):
        return name[:-13]
    return name


def ldr_pc_immediate(word: int) -> int | None:
    """Return the imm12 byte offset from ARM ``LDR Rd, [pc, #imm]``."""
    if (word & 0x0FFF0000) != 0x059F0000:
        return None
    return word & 0xFFF


def iter_hook_poin_sites(event_path: pathlib.Path):
    hook_org: int | None = None
    cursor: int | None = None
    ldr_pc_offset = 0

    for raw_line in event_path.read_text().splitlines():
        line = raw_line.split("//", 1)[0].strip()
        if not line or line in {"PUSH", "POP"}:
            if line == "POP":
                hook_org = None
                cursor = None
                ldr_pc_offset = 0
            continue

        match = ORG_RE.fullmatch(line)
        if match:
            org = int(match.group(1), 16)
            if hook_org is None:
                hook_org = org
            cursor = org
            continue

        if line.startswith("ALIGN"):
            if cursor is None:
                raise ValueError(f"ALIGN before ORG in {event_path}")
            align = int(line.split()[1], 0)
            cursor = (cursor + (align - 1)) & ~(align - 1)
            continue

        match = WORD_RE.fullmatch(line)
        if match:
            if cursor is None:
                raise ValueError(f"WORD before ORG in {event_path}")
            tokens = match.group(1).split()
            if len(tokens) >= 3:
                third = int(tokens[2][1:], 16) if tokens[2].startswith("$") else int(tokens[2], 0)
                imm = ldr_pc_immediate(third)
                if imm is not None:
                    ldr_pc_offset = imm
            for _token in tokens:
                cursor += 4
            continue

        match = POIN_RE.fullmatch(line)
        if match:
            if hook_org is None or cursor is None:
                raise ValueError(f"POIN before hook ORG in {event_path}")
            yield HookPoinSite(
                event_path=event_path,
                hook_org=hook_org,
                replacement_name=match.group(1),
                poin_org=cursor,
                ldr_pc_offset=ldr_pc_offset,
            )
            hook_org = None
            cursor = None
            ldr_pc_offset = 0
            continue

        raise ValueError(f"unsupported line in {event_path}: {raw_line}")


def load_function_entries_from_nm(elf_path: pathlib.Path) -> dict[str, int]:
    output = subprocess.check_output(
        ["arm-none-eabi-nm", "-g", str(elf_path)],
        text=True,
    )
    entries: dict[str, int] = {}
    for line in output.splitlines():
        parts = line.strip().split()
        if len(parts) != 3:
            continue
        addr, sym_type, name = parts
        if sym_type not in {"T", "t"}:
            continue
        entries[name] = int(addr, 16) & ~1
    return entries


def load_function_entries_from_map(map_path: pathlib.Path) -> dict[str, int]:
    entries: dict[str, int] = {}
    for line in map_path.read_text().splitlines():
        match = MAP_SYMBOL_RE.match(line)
        if not match:
            continue
        addr = int(match.group(1), 16)
        name = match.group(2)
        entries[name] = addr
    return entries


def load_function_entries(root: pathlib.Path = ROOT) -> dict[str, int]:
    elf_path = root / "ygodm8.elf"
    if elf_path.is_file():
        return load_function_entries_from_nm(elf_path)

    map_path = root / "ygodm8.map"
    if map_path.is_file():
        return load_function_entries_from_map(map_path)

    return {}


def expected_poin_org(hook_org: int, ldr_pc_offset: int) -> int:
    return hook_org + STANDARD_HOOK_SIZE + ldr_pc_offset


def validate_poin_entry_collisions(
    event_files,
    function_entries: dict[str, int],
) -> list[str]:
    errors: list[str] = []
    entry_by_rom = {addr - ROM_BASE: name for name, addr in function_entries.items()}

    for event_path in event_files:
        for site in iter_hook_poin_sites(event_path):
            hooked_name = marker_name(site.replacement_name)

            expected = expected_poin_org(site.hook_org, site.ldr_pc_offset)
            if site.ldr_pc_offset and site.poin_org != expected:
                errors.append(
                    f"{site.replacement_name} hook in {site.event_path} places POIN at "
                    f"${site.poin_org:X}, but LDR [pc, #{site.ldr_pc_offset}] loads from ${expected:X}"
                )

            victim = entry_by_rom.get(site.poin_org)
            if victim is not None and victim != hooked_name:
                errors.append(
                    f"{hooked_name} hook POIN at ${site.poin_org:X} overwrites entry of {victim}"
                )

    return errors


def get_duelist_level_rom_prologue(rom_path: pathlib.Path) -> int | None:
    """Return the first halfword at GetDuelistLevel if the ROM is present."""
    if not rom_path.is_file():
        return None
    rom = rom_path.read_bytes()
    offset = 0x1D730
    if offset + 2 > len(rom):
        return None
    return rom[offset] | (rom[offset + 1] << 8)
