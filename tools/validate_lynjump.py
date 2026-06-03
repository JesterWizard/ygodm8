#!/usr/bin/env python3

import pathlib
import re
import subprocess
import sys


ROOT = pathlib.Path(__file__).resolve().parent.parent
CHECK_RE = re.compile(r"LYN_REPLACE_CHECK\((\w+)\)|LYN_REPLACEMENT\((\w+)\)")
POIN_RE = re.compile(r"POIN\s+(\w+)")
ORG_RE = re.compile(r"ORG\s+\$([0-9A-Fa-f]+)")
SECTION_RE = re.compile(
    r"\[\s*\d+\]\s+(\S+)\s+\S+\s+([0-9A-Fa-f]+)\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+\S+\s+([A-Z]+)"
)
ROM_BASE = 0x08000000
BASE_ROM_LIMIT = 0x09000020
MAX_ROM_LIMIT = 0x0A000000
APPEND_SECTIONS = {
    ".append_text",
    ".append_rodata",
    ".append_assets",
    ".append_data",
}


def marker_name(name: str) -> str:
    if name.endswith("__Replacement"):
        return name[:-13]
    return name


def fmt_range(start: int, end: int) -> str:
    return f"0x{start:X}-0x{end:X} ({end - start} bytes)"


def iter_c_files():
    for path in ROOT.rglob("*.c"):
        if "build" in path.parts:
            continue
        yield path


def sibling_event(path: pathlib.Path) -> pathlib.Path:
    return path.with_name("LynJump.event")


def checked_names(path: pathlib.Path):
    names = []
    for raw_line in path.read_text().splitlines():
        line = raw_line.split("//", 1)[0]
        for match in CHECK_RE.findall(line):
            names.extend(name for name in match if name)
    return names


def poin_names(path: pathlib.Path):
    names = []
    for raw_line in path.read_text().splitlines():
        line = raw_line.split("//", 1)[0]
        names.extend(POIN_RE.findall(line))
    return names


def load_symbols():
    elf_path = ROOT / "ygodm8.elf"
    if not elf_path.exists():
        return {}

    output = subprocess.check_output(
        ["arm-none-eabi-nm", "-g", str(elf_path)],
        text=True,
    )
    symbols = {}
    for line in output.splitlines():
        parts = line.strip().split()
        if len(parts) != 3:
            continue
        addr, _sym_type, name = parts
        symbols[name] = int(addr, 16)
    return symbols


def iter_event_hooks(path: pathlib.Path):
    hook_org = None

    for raw_line in path.read_text().splitlines():
        line = raw_line.split("//", 1)[0].strip()
        if not line or line in {"PUSH", "POP"}:
            if line == "POP":
                hook_org = None
            continue

        match = ORG_RE.fullmatch(line)
        if match:
            org = int(match.group(1), 16)
            if hook_org is None:
                hook_org = org
            continue

        match = POIN_RE.fullmatch(line)
        if match and hook_org is not None:
            yield hook_org, match.group(1)
            hook_org = None


def load_sections():
    elf_path = ROOT / "ygodm8.elf"
    if not elf_path.exists():
        return []

    output = subprocess.check_output(
        ["readelf", "-S", str(elf_path)],
        text=True,
    )
    sections = []
    for line in output.splitlines():
        match = SECTION_RE.search(line)
        if not match:
            continue
        name, addr_hex, size_hex, flags = match.groups()
        sections.append((name, int(addr_hex, 16), int(size_hex, 16), flags))
    return sections


def main() -> int:
    errors = []
    symbols = load_symbols()
    sections = load_sections()
    seen_orgs = {}

    for c_file in iter_c_files():
        names = checked_names(c_file)
        if not names:
            continue

        event_file = sibling_event(c_file)
        if not event_file.exists():
            for name in names:
                errors.append(f"missing sibling LynJump.event for {name} in {c_file}")
            continue

        event_names = {marker_name(name) for name in poin_names(event_file)}
        for name in names:
            if name not in event_names:
                errors.append(f"{name} marked in {c_file} but not referenced in {event_file}")

    for event_file in ROOT.rglob("LynJump.event"):
        c_files = list(event_file.parent.glob("*.c"))
        texts = [path.read_text() for path in c_files]

        for name in poin_names(event_file):
            name = marker_name(name)
            markers = (f"LYN_REPLACE_CHECK({name})", f"LYN_REPLACEMENT({name})")
            if not any(any(marker in text for marker in markers) for text in texts):
                errors.append(
                    f"{name} referenced in {event_file} but no sibling .c contains one of {markers}"
                )

        for org, name in iter_event_hooks(event_file):
            base_name = marker_name(name)
            prev = seen_orgs.get(org)
            if prev is not None:
                errors.append(
                    f"duplicate hook ORG ${org:X} in {event_file}; already used by {prev}"
                )
            else:
                seen_orgs[org] = f"{event_file}:{name}"

            if base_name not in symbols:
                continue

            expected_org = symbols[base_name] - ROM_BASE
            if org != expected_org:
                errors.append(
                    f"{base_name} hook in {event_file} patches ORG ${org:X}, expected ${expected_org:X}"
                )

    for name, addr, size, flags in sections:
        if "A" not in flags or size == 0:
            continue
        if addr < ROM_BASE or addr >= MAX_ROM_LIMIT:
            continue
        end = addr + size
        if end > MAX_ROM_LIMIT:
            errors.append(
                f"allocated section {name} crosses max ROM limit: {fmt_range(addr, end)} exceeds 0x{MAX_ROM_LIMIT:X}"
            )
            continue

        if name == ".text" and end > BASE_ROM_LIMIT:
            errors.append(
                f"base .text crosses append boundary: {fmt_range(addr, end)} exceeds 0x{BASE_ROM_LIMIT:X}"
            )

        if name in APPEND_SECTIONS and addr < BASE_ROM_LIMIT:
            errors.append(
                f"append section {name} starts inside base ROM region: {fmt_range(addr, end)} starts before 0x{BASE_ROM_LIMIT:X}"
            )

    if errors:
        for error in errors:
            print(f"[ERROR] {error}", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
