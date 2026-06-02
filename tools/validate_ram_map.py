#!/usr/bin/env python3
"""Validate flash allocations in asm/ram_map.s do not overlap."""

from __future__ import annotations

import re
import sys
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RAM_MAP = ROOT / "asm" / "ram_map.s"

FLASH_TOP = 0x0E000000
FLASH_BOTTOM = 0x0E008000
FLASH_SIZE = FLASH_BOTTOM - FLASH_TOP

SET_ARRAY_RE = re.compile(
    r"SET_ARRAY\s+(\w+),\s*(0x[0-9A-Fa-f]+),\s*(0x[0-9A-Fa-f]+)"
)
SET_DATA_RE = re.compile(r"SET_DATA\s+(\w+),\s*(0x[0-9A-Fa-f]+)")
KERNEL_FLASH_RE = re.compile(r"_kernel_malloc_flash\s+(\w+),\s*(\S+)")
SET_EQU_RE = re.compile(r"\.set\s+(\w+),\s*(0x[0-9A-Fa-f]+)")
INCLUDE_EQU_RE = re.compile(r"\.equ\s+(\w+),\s*(0x[0-9A-Fa-f]+)", re.IGNORECASE)

FLASH_BOUNDARY_SYMBOLS = {
    "FreeFlashSpaceTop",
    "FreeFlashSpaceBottom",
    "UsedFreeFlashSpaceTop",
    "gCustomCardQtyFlashPrimaryStart",
    "gCustomCardQtyFlashBackupStart",
    "gCostSeedFlashPrimary",
    "gCostSeedFlashBackup",
}

REQUIRED_FLASH_SYMBOLS = {
    "gSaveSlotPrimary": 0x747,
    "gSaveSlotBackup": 0x747,
    "gPlayerDeck2CardsFlashPrimary": 0x50,
    "gPlayerDeck3CardsFlashPrimary": 0x50,
    "gPlayerDeckSaveMagicFlashPrimary": 1,
}


@dataclass(frozen=True)
class Region:
    name: str
    start: int
    end: int

    @property
    def size(self) -> int:
        return self.end - self.start


def load_size_constants(ram_map_text: str) -> dict[str, int]:
    constants: dict[str, int] = {"PLAYER_DECK_CARD_BYTES": 0x50}
    sizes_inc = ROOT / "generated" / "card_memory_sizes.inc"
    if sizes_inc.is_file():
        for line in sizes_inc.read_text().splitlines():
            match = INCLUDE_EQU_RE.search(line)
            if match:
                constants[match.group(1)] = int(match.group(2), 16)
    for line in ram_map_text.splitlines():
        match = SET_EQU_RE.search(line.split("@", 1)[0].strip())
        if match:
            constants[match.group(1)] = int(match.group(2), 16)
    return constants


def resolve_size(token: str, constants: dict[str, int]) -> int:
    if token.startswith("0x") or token.startswith("0X"):
        return int(token, 16)
    if token.isdigit():
        return int(token, 10)
    if token not in constants:
        raise SystemExit(f"unknown flash allocation size token: {token}")
    return constants[token]


def parse_regions(text: str) -> list[Region]:
    regions: list[Region] = []
    primary_cursor: int | None = None
    backup_cursor: int | None = None
    constants = load_size_constants(text)

    for line in text.splitlines():
        stripped = line.split("@", 1)[0].strip()
        if not stripped:
            continue

        if stripped.startswith("SET_DATA gCustomCardQtyFlashPrimaryStart"):
            match = SET_DATA_RE.search(stripped)
            if match:
                primary_cursor = int(match.group(2), 16)
            continue
        if stripped.startswith("SET_DATA gCustomCardQtyFlashBackupStart"):
            match = SET_DATA_RE.search(stripped)
            if match:
                backup_cursor = int(match.group(2), 16)
            continue

        array_match = SET_ARRAY_RE.search(stripped)
        if array_match:
            name, start_s, size_s = array_match.groups()
            start = int(start_s, 16)
            size = int(size_s, 16)
            regions.append(Region(name, start, start + size))
            continue

        data_match = SET_DATA_RE.search(stripped)
        if data_match and "_kernel_malloc" not in stripped:
            name, value_s = data_match.groups()
            start = int(value_s, 16)
            if FLASH_TOP <= start < FLASH_BOTTOM:
                regions.append(Region(name, start, start + 1))
            continue

        if stripped.startswith("_kernel_malloc_flash "):
            flash_match = KERNEL_FLASH_RE.search(stripped)
            if not flash_match:
                continue
            name, size_token = flash_match.groups()
            size = resolve_size(size_token, constants)
            if primary_cursor is None or backup_cursor is None:
                raise SystemExit("flash cursor not initialized before _kernel_malloc_flash")
            regions.append(Region(f"{name}FlashPrimary", primary_cursor, primary_cursor + size))
            regions.append(Region(f"{name}FlashBackup", backup_cursor, backup_cursor + size))
            primary_cursor += size
            backup_cursor += size

    return regions


def flash_regions(regions: list[Region]) -> list[Region]:
    return [
        region
        for region in regions
        if FLASH_TOP <= region.start < FLASH_BOTTOM and region.name not in FLASH_BOUNDARY_SYMBOLS
    ]


def find_overlaps(regions: list[Region]) -> list[tuple[Region, Region]]:
    ordered = sorted(regions, key=lambda region: (region.start, region.end))
    overlaps: list[tuple[Region, Region]] = []
    for index, left in enumerate(ordered):
        for right in ordered[index + 1 :]:
            if right.start >= left.end:
                break
            overlaps.append((left, right))
    return overlaps


def main() -> int:
    text = RAM_MAP.read_text()
    regions = flash_regions(parse_regions(text))
    if not regions:
        print("validate_ram_map: no flash regions parsed", file=sys.stderr)
        return 1

    overlaps = find_overlaps(regions)
    if overlaps:
        for left, right in overlaps:
            print(
                f"flash overlap: {left.name} {left.start:#x}-{left.end:#x} "
                f"vs {right.name} {right.start:#x}-{right.end:#x}",
                file=sys.stderr,
            )
        return 1

    max_end = max(region.end for region in regions)
    if max_end > FLASH_BOTTOM:
        print(
            f"flash usage exceeds window: end={max_end:#x} limit={FLASH_BOTTOM:#x}",
            file=sys.stderr,
        )
        return 1

    by_name = {region.name: region for region in regions}
    for symbol, expected_size in REQUIRED_FLASH_SYMBOLS.items():
        region = by_name.get(symbol)
        if region is None:
            print(f"missing expected flash symbol: {symbol}", file=sys.stderr)
            return 1
        if region.size != expected_size:
            print(
                f"{symbol} size mismatch: expected {expected_size:#x}, got {region.size:#x}",
                file=sys.stderr,
            )
            return 1

    used = max_end - FLASH_TOP
    print(f"validate_ram_map: ok ({len(regions)} regions, {used:#x}/{FLASH_SIZE:#x} bytes used)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
