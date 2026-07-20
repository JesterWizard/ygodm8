#!/usr/bin/env python3
"""Simulate asm/ram_map.s bump allocations and validate layout safety."""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RAM_MAP = ROOT / "asm" / "ram_map.s"
CARD_COUNTS_H = ROOT / "include/constants/card_counts.h"
CARD_IDS_H = ROOT / "include/constants/card_ids.h"
CARD_MEMORY_SIZES_INC = ROOT / "generated/card_memory_sizes.inc"

INCLUDE_EQU_RE = re.compile(r"\.equ\s+(\w+),\s*(0x[0-9A-Fa-f]+)", re.IGNORECASE)
SET_EQU_RE = re.compile(r"\.set\s+(\w+),\s*(0x[0-9A-Fa-f]+)")
DEFINE_RE = re.compile(r"#define\s+(\w+)\s+(0x[0-9A-Fa-f]+)")
MALLOC_EWRAM_ARRAY_RE = re.compile(r"_kernel_malloc_ewram_array\s+(\w+),\s*(\S+)")
MALLOC_EWRAM_RE = re.compile(r"_kernel_malloc_ewram\s+(\w+),\s*(\S+)")
MALLOC_IWRAM_RE = re.compile(r"_kernel_malloc\s+(\w+),\s*(\S+)")
INCLUDE_RE = re.compile(r'^\s*\.include\s+"([^"]+)"')


def read_ram_map_text(root: Path | None = None) -> str:
    """Return asm/ram_map.s with .include fragments expanded (for validators)."""
    root = root or ROOT
    entry = root / "asm" / "ram_map.s"
    if not entry.is_file():
        raise FileNotFoundError(entry)
    return _expand_asm_includes(entry.read_text(encoding="utf-8"), entry.parent, root)


def _expand_asm_includes(text: str, base_dir: Path, root: Path) -> str:
    out: list[str] = []
    for line in text.splitlines():
        match = INCLUDE_RE.match(line)
        if not match:
            out.append(line)
            continue
        rel = match.group(1)
        for candidate in (base_dir / rel, root / rel):
            if candidate.is_file():
                out.append(
                    _expand_asm_includes(
                        candidate.read_text(encoding="utf-8"),
                        candidate.parent,
                        root,
                    )
                )
                break
        else:
            raise FileNotFoundError(f"ram map include not found: {rel} (from {base_dir})")
    return "\n".join(out)


@dataclass(frozen=True)
class Allocation:
    name: str
    size_token: str
    line_no: int


@dataclass(frozen=True)
class Region:
    name: str
    start: int
    end: int
    size_token: str

    @property
    def size(self) -> int:
        return self.end - self.start


QTY_CLUSTER_MEMBERS = {
    "gCustomTrunkCardQty",
    "gCustomShopCardQty",
    "gCustomPlayerTempCardQty",
    "gCostEntropyState",
    "gCustomTotalCardQty",
    "gCustomShopTempCardQty",
}

CARD_COUNT_SIZE_TOKENS = {
    "CUSTOM_SHOP_CARD_LIST_BYTES",
    "TRUNK_MENU_CUSTOM_CARD_BYTES",
    "TRUNK_MENU_SORT_LIST_BYTES",
    "CARD_COST_TABLE_BYTES",
}


def load_size_constants() -> dict[str, int]:
    constants: dict[str, int] = {"PLAYER_DECK_CARD_BYTES": 0x50}

    if CARD_MEMORY_SIZES_INC.is_file():
        for line in CARD_MEMORY_SIZES_INC.read_text(encoding="utf-8").splitlines():
            match = INCLUDE_EQU_RE.search(line)
            if match:
                constants[match.group(1)] = int(match.group(2), 16)

    if CARD_COUNTS_H.is_file():
        for line in CARD_COUNTS_H.read_text(encoding="utf-8").splitlines():
            match = DEFINE_RE.search(line)
            if match:
                constants[match.group(1)] = int(match.group(2), 16)

    if RAM_MAP.is_file():
        for line in read_ram_map_text().splitlines():
            match = SET_EQU_RE.search(line.split("@", 1)[0].strip())
            if match:
                constants[match.group(1)] = int(match.group(2), 16)

    return constants


def resolve_size(token: str, constants: dict[str, int]) -> int:
    if token.startswith(("0x", "0X")):
        return int(token, 16)
    if token.isdigit():
        return int(token, 10)
    if token not in constants:
        raise ValueError(f"unknown allocation size token: {token}")
    return constants[token]


def card_memory_sizes(total_cards: int, custom_start: int) -> dict[str, int]:
    custom_cards = max(0, total_cards - custom_start)
    # Keep in sync with tools/add_card_art.py custom_card_qty_bytes_for().
    qty = max(custom_cards, 0x200)
    qty = (qty + 3) & ~3  # multiple of 4: trunk u16 + SortableEntry u64 alignment
    return {
        "CUSTOM_CARD_QTY_BYTES": qty,
        "TRUNK_MENU_CUSTOM_CARD_BYTES": custom_cards * 2,
        "TRUNK_MENU_SORT_LIST_BYTES": (custom_start + custom_cards) * 2,
        "CUSTOM_SHOP_CARD_ROWS": (total_cards + 6) // 7,
        "CUSTOM_SHOP_CARD_LIST_ENTRIES": ((total_cards + 6) // 7) * 7 + 1,
        "CUSTOM_SHOP_CARD_LIST_BYTES": (((total_cards + 6) // 7) * 7 + 1) * 2,
        "CARD_COST_TABLE_BYTES": total_cards * 2,
        "SORTABLE_ENTRIES_BYTES": total_cards * 12,
        "NUM_TOTAL_CARDS": total_cards,
        "NUM_CUSTOM_CARDS": custom_cards,
    }


def read_card_layout_constants() -> tuple[int, int]:
    counts = {}
    if CARD_COUNTS_H.is_file():
        for line in CARD_COUNTS_H.read_text(encoding="utf-8").splitlines():
            match = DEFINE_RE.search(line)
            if match:
                counts[match.group(1)] = int(match.group(2), 16)

    custom_start = 0x321
    if CARD_IDS_H.is_file():
        for line in CARD_IDS_H.read_text(encoding="utf-8").splitlines():
            match = DEFINE_RE.search(line)
            if match and match.group(1) == "NUM_CARDS":
                custom_start = int(match.group(2), 16)

    total_cards = counts.get("NUM_TOTAL_CARDS")
    if total_cards is None:
        raise ValueError(f"missing NUM_TOTAL_CARDS in {CARD_COUNTS_H}")
    return total_cards, custom_start


def parse_region_allocations(text: str, region: str) -> list[Allocation]:
    if region == "ewram":
        start_marker = "@ EWRAM free space"
        end_marker = "@ Flash storage (SRAM)"
        line_res = ((MALLOC_EWRAM_ARRAY_RE, "array"), (MALLOC_EWRAM_RE, "scalar"))
    elif region == "iwram":
        start_marker = "@ IWRAM free space"
        end_marker = "@ EWRAM free space"
        line_res = ((MALLOC_IWRAM_RE, "scalar"),)
    else:
        raise ValueError(region)

    active = False
    allocs: list[Allocation] = []
    for line_no, line in enumerate(text.splitlines(), start=1):
        if start_marker in line:
            active = True
            continue
        if not active:
            continue
        if end_marker in line:
            break

        stripped = line.split("@", 1)[0].strip()
        if not stripped or stripped.startswith("."):
            continue
        for pattern, _kind in line_res:
            match = pattern.search(stripped)
            if match:
                allocs.append(Allocation(match.group(1), match.group(2), line_no))
                break
    return allocs


def simulate_bump(
    allocs: list[Allocation],
    space_bottom: int,
    space_top: int,
    constants: dict[str, int],
    *,
    align: int = 1,
) -> tuple[list[Region], int]:
    """Simulate downward bump allocation.

    EWRAM macros apply ``& ~3`` after every subtract (align=4). IWRAM does not.
    """
    cursor = space_bottom
    regions: list[Region] = []
    align_mask = ~(align - 1) if align > 1 else None
    for alloc in allocs:
        size = resolve_size(alloc.size_token, constants)
        cursor -= size
        if align_mask is not None:
            cursor &= align_mask
        regions.append(Region(alloc.name, cursor, cursor + size, alloc.size_token))
    return regions, cursor


def find_overlaps(regions: list[Region]) -> list[tuple[Region, Region]]:
    ordered = sorted(regions, key=lambda region: (region.start, region.end))
    overlaps: list[tuple[Region, Region]] = []
    for index, left in enumerate(ordered):
        for right in ordered[index + 1 :]:
            if right.start >= left.end:
                break
            overlaps.append((left, right))
    return overlaps


def validate_qty_cluster_integrity(allocs: list[Allocation]) -> list[str]:
    errors: list[str] = []
    qty_indices = [
        index
        for index, alloc in enumerate(allocs)
        if alloc.size_token == "CUSTOM_CARD_QTY_BYTES"
    ]
    if not qty_indices:
        return ["missing CUSTOM_CARD_QTY_BYTES allocations in EWRAM map"]

    first = qty_indices[0]
    last = qty_indices[-1]
    for index in range(first, last + 1):
        alloc = allocs[index]
        if alloc.size_token == "CUSTOM_CARD_QTY_BYTES":
            continue
        if alloc.name in QTY_CLUSTER_MEMBERS:
            continue
        errors.append(
            f"{RAM_MAP}:{alloc.line_no}: {alloc.name} must not sit inside the "
            "CUSTOM_CARD_QTY_BYTES cluster; keep effect scratch after "
            "gCustomShopTempCardQty"
        )
    return errors


def validate_card_count_regions_before_qty(allocs: list[Allocation]) -> list[str]:
    errors: list[str] = []
    first_qty = next(
        (index for index, alloc in enumerate(allocs) if alloc.size_token == "CUSTOM_CARD_QTY_BYTES"),
        None,
    )
    if first_qty is None:
        return errors

    for index, alloc in enumerate(allocs):
        if index >= first_qty:
            break
        if alloc.size_token not in CARD_COUNT_SIZE_TOKENS:
            continue
        if alloc.name != "gCustomShopCardList":
            errors.append(
                f"{RAM_MAP}:{alloc.line_no}: card-count-sized {alloc.name} must stay "
                "before the CUSTOM_CARD_QTY_BYTES block so growth shifts away from "
                "qty padding"
            )
    return errors


def validate_allocation_alignment(
    regions: list[Region],
    region_name: str,
) -> list[str]:
    """Flag u16-sized bump allocations that land on odd addresses."""
    errors: list[str] = []
    for region in regions:
        if region.size != 2 or region.start % 2 == 0:
            continue
        errors.append(
            f"{RAM_MAP}: {region.name} ({region_name}) size-2 allocation at "
            f"{region.start:#x} is not 2-byte aligned; add a 1-byte pad in "
            "asm/ram_map.s before it"
        )
    return errors


def validate_region(
    region_name: str,
    allocs: list[Allocation],
    space_bottom: int,
    space_top: int,
    constants: dict[str, int],
    *,
    align: int = 1,
) -> list[str]:
    errors: list[str] = []
    try:
        regions, used_top = simulate_bump(
            allocs, space_bottom, space_top, constants, align=align
        )
    except ValueError as exc:
        return [str(exc)]

    if used_top < space_top:
        errors.append(
            f"{region_name} overflow: used down to {used_top:#x}, limit {space_top:#x}"
        )

    for left, right in find_overlaps(regions):
        errors.append(
            f"{region_name} overlap: {left.name} {left.start:#x}-{left.end:#x} "
            f"vs {right.name} {right.start:#x}-{right.end:#x}"
        )
    return errors


def validate_card_growth(allocs: list[Allocation], total_cards: int, custom_start: int) -> list[str]:
    errors: list[str] = []
    ewram_bottom = 0x02040000
    ewram_top = 0x02025840
    iwram_bottom = 0x03007E00
    iwram_top = 0x03001678

    for label, candidate_total in (("current", total_cards), ("+1 card", total_cards + 1)):
        constants = load_size_constants()
        constants.update(card_memory_sizes(candidate_total, custom_start))
        errors.extend(
            validate_region(
                f"EWRAM ({label})",
                allocs,
                ewram_bottom,
                ewram_top,
                constants,
                align=4,
            )
        )
        errors.extend(
            validate_region(
                f"IWRAM ({label})",
                parse_region_allocations(read_ram_map_text(), "iwram"),
                iwram_bottom,
                iwram_top,
                constants,
            )
        )
    return errors


def elf_regions(symbols: dict[str, int], bottom: int, top: int) -> list[Region]:
    regions: list[Region] = []
    for name, end in symbols.items():
        if not name.endswith("End"):
            continue
        start = symbols.get(name[:-3])
        if start is None:
            continue
        if start < bottom or start >= top:
            continue
        if end <= start:
            continue
        regions.append(Region(name[:-3], start, end, "elf"))
    return regions


def validate_elf_layout(symbols: dict[str, int]) -> list[str]:
    errors: list[str] = []
    checks = (
        ("IWRAM", 0x03000000, 0x03008000),
        ("EWRAM", 0x02000000, 0x02040000),
        ("SRAM", 0x0E000000, 0x0E008000),
    )
    for label, bottom, top in checks:
        regions = elf_regions(symbols, bottom, top)
        for left, right in find_overlaps(regions):
            errors.append(
                f"ELF {label} overlap: {left.name} {left.start:#x}-{left.end:#x} "
                f"vs {right.name} {right.start:#x}-{right.end:#x}"
            )
    return errors


def validate_ram_map_layout() -> list[str]:
    if not RAM_MAP.is_file():
        return [f"missing {RAM_MAP}"]

    text = read_ram_map_text()
    ewram_allocs = parse_region_allocations(text, "ewram")
    iwram_allocs = parse_region_allocations(text, "iwram")
    constants = load_size_constants()

    errors: list[str] = []
    errors.extend(validate_qty_cluster_integrity(ewram_allocs))
    errors.extend(validate_card_count_regions_before_qty(ewram_allocs))
    try:
        ewram_regions, _ = simulate_bump(
            ewram_allocs, 0x02040000, 0x02025840, constants, align=4
        )
        iwram_regions, _ = simulate_bump(iwram_allocs, 0x03007E00, 0x03001678, constants)
    except ValueError as exc:
        errors.append(str(exc))
        ewram_regions = []
        iwram_regions = []
    else:
        errors.extend(validate_allocation_alignment(ewram_regions, "EWRAM"))
        errors.extend(validate_allocation_alignment(iwram_regions, "IWRAM"))
    errors.extend(
        validate_region(
            "EWRAM", ewram_allocs, 0x02040000, 0x02025840, constants, align=4
        )
    )
    errors.extend(
        validate_region("IWRAM", iwram_allocs, 0x03007E00, 0x03001678, constants)
    )

    try:
        total_cards, custom_start = read_card_layout_constants()
    except ValueError as exc:
        errors.append(str(exc))
    else:
        errors.extend(validate_card_growth(ewram_allocs, total_cards, custom_start))

    return errors


def validate_layout(symbols: dict[str, int] | None = None) -> list[str]:
    errors = validate_ram_map_layout()
    if symbols:
        errors.extend(validate_elf_layout(symbols))
    return errors
