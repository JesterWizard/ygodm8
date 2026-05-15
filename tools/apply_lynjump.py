#!/usr/bin/env python3

import pathlib
import re
import struct
import subprocess
import sys


ROOT = pathlib.Path(__file__).resolve().parent.parent
ORG_RE = re.compile(r"ORG\s+\$([0-9A-Fa-f]+)")
WORD_RE = re.compile(r"WORD\s+(.+)")
POIN_RE = re.compile(r"POIN\s+(\w+)")
ROM_PATCH_LIMIT = 0x0A000000 - 0x08000000


def fmt_range(start: int, end: int) -> str:
    return f"0x{start:X}-0x{end:X} ({end - start} bytes)"


def load_symbols(elf_path: pathlib.Path):
    output = subprocess.check_output(["arm-none-eabi-nm", "-g", str(elf_path)], text=True)
    symbols = {}
    for line in output.splitlines():
        parts = line.strip().split()
        if len(parts) == 3:
            addr, sym_type, name = parts
            value = int(addr, 16)
            if sym_type in {"T", "t"}:
                value |= 1
            symbols[name] = value
    return symbols


def checked_write(rom: bytearray, start: int, data: bytes, owners: dict[int, str], owner: str):
    end = start + len(data)
    if start < 0 or end > len(rom):
        raise ValueError(f"{owner} writes outside ROM bounds: 0x{start:X}-0x{end:X}")
    if end > ROM_PATCH_LIMIT:
        raise ValueError(f"{owner} writes past ROM patch limit: 0x{start:X}-0x{end:X}")

    for offset in range(start, end):
        previous = owners.get(offset)
        if previous is not None and previous != owner:
            raise ValueError(
                f"{owner} overlaps ROM patch byte 0x{offset:X} in {fmt_range(start, end)} already written by {previous}"
            )

    rom[start:end] = data
    for offset in range(start, end):
        owners[offset] = owner


def apply_event(event_path: pathlib.Path, rom: bytearray, symbols, owners: dict[int, str]):
    cursor = None

    for raw_line in event_path.read_text().splitlines():
        line = raw_line.split("//", 1)[0].strip()
        if not line or line in {"PUSH", "POP"}:
            continue

        match = ORG_RE.fullmatch(line)
        if match:
            cursor = int(match.group(1), 16)
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
            for token in match.group(1).split():
                value = int(token[1:], 16) if token.startswith("$") else int(token, 0)
                checked_write(
                    rom,
                    cursor,
                    struct.pack("<I", value),
                    owners,
                    f"{event_path}:{line}",
                )
                cursor += 4
            continue

        match = POIN_RE.fullmatch(line)
        if match:
            if cursor is None:
                raise ValueError(f"POIN before ORG in {event_path}")
            name = match.group(1)
            if name not in symbols:
                raise KeyError(f"symbol {name} not found for {event_path}")
            checked_write(
                rom,
                cursor,
                struct.pack("<I", symbols[name]),
                owners,
                f"{event_path}:POIN {name}",
            )
            cursor += 4
            continue

        raise ValueError(f"unsupported line in {event_path}: {raw_line}")


def main() -> int:
    if len(sys.argv) != 3:
        print("usage: apply_lynjump.py <elf> <rom>", file=sys.stderr)
        return 1

    elf_path = ROOT / sys.argv[1]
    rom_path = ROOT / sys.argv[2]
    symbols = load_symbols(elf_path)
    rom = bytearray(rom_path.read_bytes())
    owners = {}

    for event_path in ROOT.rglob("LynJump.event"):
        apply_event(event_path, rom, symbols, owners)

    rom_path.write_bytes(rom)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
