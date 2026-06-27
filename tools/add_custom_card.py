#!/usr/bin/env python3
"""Scaffold a custom card manifest entry from YGOProDeck and local art."""

from __future__ import annotations

import argparse
import json
import re
import sys
import textwrap
import urllib.error
import urllib.parse
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from card_manifest import (  # noqa: E402
    activation_description_symbol,
    description_symbol,
    load_manifest_json,
    order_card_entry,
    validate_manifest,
    write_manifest,
)

MANIFEST_PATH = ROOT / "tools" / "card_data_manifest.json"
ART_DIR = ROOT / "src_custom" / "assets" / "cards" / "80x80"
RUNTIME_CONFIG_C = ROOT / "configs" / "runtime.c"
PROGRESS_PATH = ROOT / "src_custom" / "assets" / "cards" / "CARD_PROGRESS.md"
YGO_API = "https://db.ygoprodeck.com/api/v7/cardinfo.php"

ATTRIBUTE_MAP = {
    "DARK": "ATTRIBUTE_SHADOW",
    "LIGHT": "ATTRIBUTE_LIGHT",
    "FIRE": "ATTRIBUTE_FIRE",
    "WATER": "ATTRIBUTE_WATER",
    "WIND": "ATTRIBUTE_WIND",
    "EARTH": "ATTRIBUTE_EARTH",
    "DIVINE": "ATTRIBUTE_DIVINE",
}

RACE_MAP = {
    "Dragon": "TYPE_DRAGON",
    "Spellcaster": "TYPE_SPELLCASTER",
    "Zombie": "TYPE_ZOMBIE",
    "Warrior": "TYPE_WARRIOR",
    "Beast-Warrior": "TYPE_BEAST_WARRIOR",
    "Beast": "TYPE_BEAST",
    "Winged Beast": "TYPE_WINGED_BEAST",
    "Fiend": "TYPE_FIEND",
    "Fairy": "TYPE_FAIRY",
    "Insect": "TYPE_INSECT",
    "Dinosaur": "TYPE_DINOSAUR",
    "Fish": "TYPE_FISH",
    "Reptile": "TYPE_REPTILE",
    "Sea Serpent": "TYPE_SEA_SERPENT",
    "Machine": "TYPE_MACHINE",
    "Thunder": "TYPE_THUNDER",
    "Aqua": "TYPE_AQUA",
    "Pyro": "TYPE_PYRO",
    "Rock": "TYPE_ROCK",
    "Plant": "TYPE_PLANT",
}

COLOR_BY_FRAME = {
    "normal": "NORMAL_CARD",
    "effect": "EFFECT_CARD",
    "fusion": "FUSION_CARD",
    "ritual": "RITUAL_CARD",
    "spell": "SPELL_CARD",
    "trap": "TRAP_CARD",
}


def card_name_to_const(name: str) -> str:
    slug = re.sub(r"[^A-Za-z0-9]+", "_", name.strip()).strip("_").upper()
    if not slug:
        raise SystemExit(f"Could not derive card_const from name: {name!r}")
    return slug


def passcode_to_password(passcode: int) -> list[int]:
    digits = str(passcode)
    if len(digits) != 8 or not digits.isdigit():
        raise SystemExit(f"Expected 8-digit passcode, got {passcode}")
    return [int(d) for d in digits]


def _fetch_cards(**params: str) -> list[dict]:
    url = f"{YGO_API}?{urllib.parse.urlencode(params)}"
    request = urllib.request.Request(url, headers={"User-Agent": "ygodm8-add-custom-card/1.0"})
    try:
        with urllib.request.urlopen(request, timeout=30) as response:
            payload = json.load(response)
    except urllib.error.URLError as exc:
        raise SystemExit(f"YGOProDeck request failed: {exc}") from exc

    cards = payload.get("data")
    if not cards:
        raise SystemExit(f"No card found for {params}")
    return cards


def fetch_card_by_const(card_const: str) -> dict:
    cards = _fetch_cards(fname=card_const.replace("_", " "))
    for card in cards:
        if card_name_to_const(card["name"]) == card_const:
            return card
    if len(cards) == 1:
        return cards[0]
    raise SystemExit(f"Could not uniquely match CARD_CONST {card_const} from YGOProDeck")


def fetch_card(*, name: str | None = None, passcode: int | None = None, fname: str | None = None) -> dict:
    params: dict[str, str] = {}
    if passcode is not None:
        params["id"] = str(passcode)
    elif name is not None:
        params["name"] = name
    elif fname is not None:
        params["fname"] = fname
    else:
        raise SystemExit("Need card name, passcode, or fname")

    return _fetch_cards(**params)[0]


def frame_kind(card_type: str) -> str:
    lowered = card_type.lower()
    for key in ("normal", "effect", "fusion", "ritual", "spell", "trap"):
        if key in lowered:
            return key
    raise SystemExit(f"Unsupported card type from API: {card_type!r}")


def wrap_effect_text(text: str, *, page_count: int = 3, width: int = 27) -> list[str]:
    wrapped = textwrap.wrap(text.strip(), width=width)
    if not wrapped:
        return ["", ""]
    if len(wrapped) <= 2:
        return wrapped if len(wrapped) >= 2 else [wrapped[0], ""]
    if page_count <= 2:
        midpoint = max(1, len(wrapped) // 2)
        return [" ".join(wrapped[:midpoint]), " ".join(wrapped[midpoint:])]

    chunk = max(1, (len(wrapped) + 2) // 3)
    pages = []
    for start in range(0, len(wrapped), chunk):
        pages.append(" ".join(wrapped[start : start + chunk]))
    return pages[:3]


def suggest_cost(manifest: dict, entry: dict) -> int:
    best_cost = 150
    best_score = None
    for item in manifest["cards"]:
        score = 0
        if item.get("color") != entry["color"]:
            score += 100
        score += abs(item.get("level", 0) - entry["level"]) * 10
        score += abs(item.get("atk", 0) - entry["atk"]) // 100
        score += abs(item.get("def", 0) - entry["def"]) // 100
        if best_score is None or score < best_score:
            best_score = score
            best_cost = item["cost"]
    return best_cost


def build_manifest_entry(api_card: dict, manifest: dict) -> dict:
    frame = frame_kind(api_card["type"])
    color = COLOR_BY_FRAME[frame]
    card_name = api_card["name"]
    card_const = card_name_to_const(card_name)
    passcode = int(api_card["id"])
    password = passcode_to_password(passcode)

    if frame in ("spell", "trap"):
        entry = order_card_entry({
            "card_const": card_const,
            "card_name": card_name,
            "atk": 65535,
            "def": 65535,
            "level": 0,
            "attribute": 0,
            "type": "TYPE_TRAP" if frame == "trap" else "TYPE_SPELL",
            "color": color,
            "monsterEffect": 0,
            "spellEffect": 2,
            "trapEffect": 0,
            "cost": suggest_cost(manifest, {"color": color, "level": 0, "atk": 65535, "def": 65535}),
            "password": password,
            "description": {
                "pages": wrap_effect_text(api_card.get("desc", card_name)),
            },
            "activation_description": {
                "pages": [api_card.get("desc", card_name)[:120]],
            },
        })
        return entry

    race = api_card.get("race")
    card_type = RACE_MAP.get(race)
    if card_type is None:
        raise SystemExit(f"Unsupported monster race from API: {race!r}")

    attribute = ATTRIBUTE_MAP.get(api_card.get("attribute", ""))
    if attribute is None:
        raise SystemExit(f"Unsupported attribute from API: {api_card.get('attribute')!r}")

    atk = int(api_card["atk"]) if api_card["atk"] is not None else 0
    def_ = int(api_card["def"]) if api_card["def"] is not None else 0
    level = int(api_card["level"])

    entry = order_card_entry({
        "card_const": card_const,
        "card_name": card_name,
        "atk": atk,
        "def": def_,
        "level": level,
        "attribute": attribute,
        "type": card_type,
        "color": color,
        "monsterEffect": 0,
        "spellEffect": 2,
        "trapEffect": 0,
        "cost": suggest_cost(manifest, {"color": color, "level": level, "atk": atk, "def": def_}),
        "password": password,
        "description": {
            "pages": wrap_effect_text(api_card.get("desc", card_name)),
        },
    })
    if color == "EFFECT_CARD":
        entry["activation_description"] = {
            "pages": [api_card.get("desc", card_name)[:120]],
        }
        entry = order_card_entry(entry)
    return entry


def finalize_entry(entry: dict) -> dict:
    validated = validate_manifest({"cards": [entry]})["cards"][0]
    return validated


def parse_progress_todo(card_const: str) -> str | None:
    if not PROGRESS_PATH.is_file():
        return None
    for line in PROGRESS_PATH.read_text().splitlines():
        match = re.match(r"- \[ \] `([A-Z0-9_]+)` — `([a-z0-9_]+\.png)`", line)
        if match and match.group(1) == card_const:
            return match.group(1)
    return None


def art_path_for(entry: dict) -> Path:
    return ART_DIR / f"{entry['card_const'].lower()}.png"


def set_runtime_hand(hand_slot: int, card_const: str) -> None:
    if hand_slot < 1 or hand_slot > 5:
        raise SystemExit("--runtime-hand must be between 1 and 5")
    text = RUNTIME_CONFIG_C.read_text()
    field = f".card_in_hand_{hand_slot}"
    pattern = rf"({re.escape(field)}\s*=\s*)[A-Z0-9_]+"
    if not re.search(pattern, text):
        raise SystemExit(f"Could not find {field} in {RUNTIME_CONFIG_C}")
    updated = re.sub(pattern, rf"\g<1>{card_const}", text, count=1)
    RUNTIME_CONFIG_C.write_text(updated)


def append_manifest(entry: dict) -> None:
    manifest = load_manifest_json(MANIFEST_PATH)
    if not isinstance(manifest, dict) or not isinstance(manifest.get("cards"), list):
        raise SystemExit(f"Unexpected manifest shape in {MANIFEST_PATH}")
    if any(item.get("card_const") == entry["card_const"] for item in manifest["cards"]):
        raise SystemExit(f"{entry['card_const']} is already in the manifest")
    manifest["cards"].append(entry)
    write_manifest(MANIFEST_PATH, manifest)


def main() -> int:
    parser = argparse.ArgumentParser(description="Scaffold a custom card manifest entry.")
    parser.add_argument("name", nargs="?", help="Card name (YGOProDeck exact match)")
    parser.add_argument("--passcode", type=str, help="8-digit passcode / card id (string, preserves leading zeros)")
    parser.add_argument("--from-progress", dest="from_progress", metavar="CARD_CONST")
    parser.add_argument("--write", action="store_true", help="Append entry to card_data_manifest.json")
    parser.add_argument("--no-desc", action="store_true", help="Use stub descriptions instead of API card text")
    parser.add_argument("--runtime-hand", type=int, metavar="N", help="Set configs/runtime.c card_in_hand_N")
    args = parser.parse_args()

    manifest = load_manifest_json(MANIFEST_PATH)
    if not isinstance(manifest, dict):
        raise SystemExit("Manifest must be an object")

    lookup_name = args.name
    lookup_passcode = int(args.passcode) if args.passcode is not None else None
    if args.from_progress:
        if parse_progress_todo(args.from_progress) is None:
            print(f"Warning: {args.from_progress} not found in CARD_PROGRESS todo list", file=sys.stderr)
        lookup_name = None
        lookup_passcode = None
        api_card = fetch_card_by_const(args.from_progress)
        entry = finalize_entry(build_manifest_entry(api_card, manifest))

        if args.no_desc:
            stub = "Custom card."
            entry["description"] = {"pages": [stub, ""]}
            if "activation_description" in entry:
                entry["activation_description"] = {"pages": [stub]}
            entry = finalize_entry(entry)

        art_path = art_path_for(entry)
        art_status = "OK" if art_path.is_file() else "MISSING"
        print(json.dumps(entry, indent=2))
        print(f"\nART: {art_path.relative_to(ROOT)} — {art_status}", file=sys.stderr)
        print(f"Description symbol: {description_symbol(entry['card_const'])}", file=sys.stderr)
        if "activation_description" in entry:
            print(f"Activation symbol: {activation_description_symbol(entry['card_const'])}", file=sys.stderr)
        if args.write:
            append_manifest(entry)
            print(f"Appended {entry['card_const']} to {MANIFEST_PATH.relative_to(ROOT)}", file=sys.stderr)
        if args.runtime_hand is not None:
            if not args.write:
                print("Warning: --runtime-hand without --write updates runtime only", file=sys.stderr)
            set_runtime_hand(args.runtime_hand, entry["card_const"])
            print(f"Set card_in_hand_{args.runtime_hand} = {entry['card_const']}", file=sys.stderr)
        return 0

    if lookup_name is None and lookup_passcode is None:
        parser.error("Provide card name, --passcode, or --from-progress CARD_CONST")

    api_card = fetch_card(name=lookup_name if lookup_passcode is None else None, passcode=lookup_passcode)
    entry = finalize_entry(build_manifest_entry(api_card, manifest))

    if args.no_desc:
        stub = "Custom card."
        entry["description"] = {"pages": [stub, ""]}
        if "activation_description" in entry:
            entry["activation_description"] = {"pages": [stub]}
        entry = finalize_entry(entry)

    art_path = art_path_for(entry)

    print(json.dumps(entry, indent=2))
    art_status = "OK" if art_path.is_file() else "MISSING"
    print(f"\nART: {art_path.relative_to(ROOT)} — {art_status}", file=sys.stderr)
    print(f"Description symbol: {description_symbol(entry['card_const'])}", file=sys.stderr)
    if "activation_description" in entry:
        print(f"Activation symbol: {activation_description_symbol(entry['card_const'])}", file=sys.stderr)

    if args.write:
        append_manifest(entry)
        print(f"Appended {entry['card_const']} to {MANIFEST_PATH.relative_to(ROOT)}", file=sys.stderr)
    if args.runtime_hand is not None:
        if not args.write:
            print("Warning: --runtime-hand without --write updates runtime only", file=sys.stderr)
        set_runtime_hand(args.runtime_hand, entry["card_const"])
        print(f"Set card_in_hand_{args.runtime_hand} = {entry['card_const']}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
