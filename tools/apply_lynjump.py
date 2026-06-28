#!/usr/bin/env python3

import json
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
    output = subprocess.check_output(["arm-none-eabi-nm", str(elf_path)], text=True)
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


def load_elf_section(elf_path: pathlib.Path, section_name: str) -> tuple[int, bytes]:
    output = subprocess.check_output(["arm-none-eabi-readelf", "-W", "-S", str(elf_path)], text=True)
    for line in output.splitlines():
        if section_name not in line or "PROGBITS" not in line:
            continue
        parts = line.split()
        # [ N] .name TYPE ADDR OFF SIZE ...
        addr = int(parts[4], 16)
        off = int(parts[5], 16)
        size = int(parts[6], 16)
        data = elf_path.read_bytes()[off : off + size]
        return addr, data
    raise KeyError(f"ELF section {section_name!r} not found in {elf_path}")


def relocate_voice_pcm_rom(rom: bytearray, elf_path: pathlib.Path, owners: dict[int, str]):
    try:
        vma, data = load_elf_section(elf_path, ".voice_pcm_rom")
    except KeyError:
        return
    if not data:
        return
    start = vma - 0x08000000
    checked_write(rom, start, data, owners, "voice_pcm_rom relocation")


def apply_m4a_rom_patches(rom: bytearray, symbols: dict, owners: dict[int, str], patch_path: pathlib.Path):
    if not patch_path.exists():
        return

    data = json.loads(patch_path.read_text())
    owner = str(patch_path)

    def resolve_symbol(entry, symbol_key, offset_key):
        name = entry[symbol_key]
        if name not in symbols:
            raise KeyError(f"voice patch missing symbol {name!r}")
        address = symbols[name]
        if offset_key in entry:
            address += entry[offset_key]
        return address

    for entry in data.get("tone_patches", []):
        org = entry["org"]
        if org + 12 > 0xAFBD0C:
            tone = (org - 0xAFB2CC) // 12
            raise ValueError(
                f"{owner}: tone patch {tone} at 0x{org:X} overlaps m4a player table (g8AFBD0C)"
            )
        wave = resolve_symbol(entry, "wave_symbol", "wave_offset")
        payload = struct.pack("<III", 0x00003C08, wave, 0x00FF00FF)
        checked_write(rom, entry["org"], payload, owners, owner)

    for entry in data.get("song_patches", []):
        header = resolve_symbol(entry, "header_symbol", "header_offset")
        payload = struct.pack("<II", header, entry["player"])
        checked_write(rom, entry["org"], payload, owners, owner)

    for entry in data.get("mode_patches", []):
        checked_write(
            rom,
            entry["org"],
            bytes([entry["mode"]]),
            owners,
            owner,
        )


def apply_m4a_hq_mixer_patches(rom: bytearray, symbols: dict, owners: dict[int, str]):
    """Retarget m4a init to copy the HQ mixer blob into linker-placed IWRAM."""
    start_name = "M4aHqMixerIwramStart"
    end_name = "M4aHqMixerIwramEnd"
    buffer_name = "MixerBuffer"
    if start_name not in symbols or end_name not in symbols or buffer_name not in symbols:
        return

    src = symbols[start_name]
    if src & 1:
        src &= ~1

    dst = symbols[buffer_name]
    if dst & 1:
        dst &= ~1

    rom_size = symbols[end_name] - src
    if rom_size & 1:
        rom_size &= ~1

    word_count = (rom_size + 3) // 4

    owner = "m4a_hq_mixer:sub_80595C4 CpuSet"
    checked_write(rom, 0x59618, struct.pack("<I", src), owners, owner)
    checked_write(rom, 0x5961C, struct.pack("<I", dst), owners, owner)
    checked_write(rom, 0x59620, struct.pack("<I", 0x04000000 | word_count), owners, owner)
    checked_write(
        rom,
        0x58988,
        struct.pack("<I", dst | 1),
        owners,
        "m4a_hq_mixer:SoundMain IWRAM entry",
    )


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

    relocate_voice_pcm_rom(rom, elf_path, owners)
    apply_m4a_rom_patches(
        rom, symbols, owners, ROOT / "src_custom/generated/music_rom_patches.json"
    )
    apply_m4a_rom_patches(
        rom, symbols, owners, ROOT / "src_custom/generated/voice_rom_patches.json"
    )
    apply_m4a_hq_mixer_patches(rom, symbols, owners)

    rom_path.write_bytes(rom)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
