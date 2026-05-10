#!/usr/bin/env python3

import pathlib
import re
import sys


ROOT = pathlib.Path(__file__).resolve().parent.parent
CHECK_RE = re.compile(r"LYN_REPLACE_CHECK\((\w+)\);")
POIN_RE = re.compile(r"POIN\s+(\w+)")


def marker_name(name: str) -> str:
    if name.endswith("__Replacement"):
        return name[:-13]
    return name


def iter_c_files():
    for path in ROOT.rglob("*.c"):
        if "build" in path.parts:
            continue
        yield path


def sibling_event(path: pathlib.Path) -> pathlib.Path:
    return path.with_name("LynJump.event")


def checked_names(path: pathlib.Path):
    return CHECK_RE.findall(path.read_text())


def poin_names(path: pathlib.Path):
    return POIN_RE.findall(path.read_text())


def main() -> int:
    errors = []

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
            marker = f"LYN_REPLACE_CHECK({name});"
            if not any(marker in text for text in texts):
                errors.append(f"{name} referenced in {event_file} but no sibling .c contains {marker}")

    if errors:
        for error in errors:
            print(f"[ERROR] {error}", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
