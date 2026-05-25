#!/usr/bin/env python3

import argparse
import subprocess
import sys
from pathlib import Path


WHITE = "\033[37m"
YELLOW = "\033[33m"
RED = "\033[31m"
RESET = "\033[0m"


def load_symbols(elf: Path, nm: str) -> dict[str, int]:
    try:
        output = subprocess.check_output([nm, "-n", str(elf)], text=True)
    except FileNotFoundError:
        raise SystemExit(f"Could not find nm tool: {nm}")
    except subprocess.CalledProcessError as exc:
        raise SystemExit(f"{nm} failed with exit code {exc.returncode}")

    symbols = {}
    for line in output.splitlines():
        parts = line.split()
        if len(parts) >= 3:
            try:
                symbols[parts[2]] = int(parts[0], 16)
            except ValueError:
                pass
    return symbols


def require(symbols: dict[str, int], name: str) -> int:
    try:
        return symbols[name]
    except KeyError:
        raise SystemExit(f"Missing required symbol in ELF: {name}")


def merge_ranges(ranges: list[tuple[int, int]]) -> list[tuple[int, int]]:
    merged = []
    for start, end in sorted((a, b) for a, b in ranges if b > a):
        if not merged or start > merged[-1][1]:
            merged.append((start, end))
        else:
            merged[-1] = (merged[-1][0], max(merged[-1][1], end))
    return merged


def flash_used(symbols: dict[str, int], start: int, end: int) -> int:
    ranges = []
    for name, range_end in symbols.items():
        if not name.endswith("End"):
            continue
        range_start = symbols.get(name[:-3])
        if range_start is None:
            continue
        if range_start < end and range_end > start:
            ranges.append((max(range_start, start), min(range_end, end)))

    for name in ("gCostSeedFlashPrimary", "gCostSeedFlashBackup"):
        addr = symbols.get(name)
        if addr is not None and start <= addr < end:
            ranges.append((addr, addr + 1))

    return sum(range_end - range_start for range_start, range_end in merge_ranges(ranges))


def color_for(percent: float, enabled: bool) -> str:
    if not enabled:
        return ""
    if percent >= 90.0:
        return RED
    if percent >= 50.0:
        return YELLOW
    return WHITE


def fmt_size(value: int) -> str:
    return f"0x{value:04X} ({value:5d})"


def print_row(name: str, used: int, total: int, color: bool) -> None:
    free = total - used
    percent = (used * 100.0 / total) if total else 0.0
    row_color = color_for(percent, color)
    reset = RESET if row_color else ""
    print(
        f"{row_color}{name:<6}  {fmt_size(used):>14}  {fmt_size(total):>14}  "
        f"{fmt_size(free):>14}  {percent:6.2f}%{reset}"
    )


def main() -> int:
    parser = argparse.ArgumentParser(description="Report custom free-space usage for IWRAM, EWRAM, and SRAM.")
    parser.add_argument("elf", type=Path, help="Built ELF file to inspect")
    parser.add_argument("--nm", default="arm-none-eabi-nm", help="nm executable to use")
    parser.add_argument("--no-color", action="store_true", help="Disable ANSI color")
    args = parser.parse_args()

    symbols = load_symbols(args.elf, args.nm)

    iwram_top = require(symbols, "FreeRamSpaceTop")
    iwram_bottom = require(symbols, "FreeRamSpaceBottom")
    iwram_used_top = require(symbols, "UsedFreeRamSpaceTop")

    ewram_top = require(symbols, "FreeEwramSpaceTop")
    ewram_bottom = require(symbols, "FreeEwramSpaceBottom")
    ewram_used_top = require(symbols, "UsedFreeEwramSpaceTop")

    flash_top = require(symbols, "FreeFlashSpaceTop")
    flash_bottom = require(symbols, "FreeFlashSpaceBottom")

    print("Region          Used           Total           Free    Usage")
    print_row("IWRAM", iwram_bottom - iwram_used_top, iwram_bottom - iwram_top, not args.no_color)
    print_row("EWRAM", ewram_bottom - ewram_used_top, ewram_bottom - ewram_top, not args.no_color)
    print_row("SRAM", flash_used(symbols, flash_top, flash_bottom), flash_bottom - flash_top, not args.no_color)
    return 0


if __name__ == "__main__":
    sys.exit(main())
