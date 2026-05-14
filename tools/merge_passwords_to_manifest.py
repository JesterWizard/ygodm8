#!/usr/bin/env python3
"""
Extract card passwords from src/card_passwords.c and merge them
into tools/card_data_manifest.json.
"""

import json
import re
import pathlib

ROOT = pathlib.Path(__file__).resolve().parents[1]
PASSWORDS_C = ROOT / "src/card_passwords.c"
MANIFEST = ROOT / "tools/card_data_manifest.json"


def parse_passwords(source: str) -> dict[str, list[int]]:
    passwords = {}

    pattern = re.compile(
        r"^\s*\[([A-Z0-9_]+)\]\s*=\s*\{([\d,\s]+)\}",
        re.MULTILINE
    )

    for match in pattern.finditer(source):
        const_name = match.group(1)
        digits_str = match.group(2)
        digits = [int(d.strip()) for d in digits_str.split(",") if d.strip()]
        if len(digits) == 8:
            passwords[const_name] = digits

    return passwords


def main():
    source = PASSWORDS_C.read_text()
    passwords = parse_passwords(source)
    print(f"Parsed {len(passwords)} passwords from {PASSWORDS_C.name}")

    manifest = json.loads(MANIFEST.read_text())
    cards = manifest["cards"]

    updated = 0
    missing = 0
    for card in cards:
        const = card["card_const"]
        if const in passwords:
            card["password"] = passwords[const]
            updated += 1
        else:
            card["password"] = [15, 15, 15, 15, 15, 15, 15, 14]
            missing += 1

    MANIFEST.write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"Updated {updated} cards, added defaults for {missing} missing")
    print(f"Written to {MANIFEST}")


if __name__ == "__main__":
    main()
