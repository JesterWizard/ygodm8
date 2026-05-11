#!/usr/bin/env python3

import argparse
import json
import pathlib
import re
from dataclasses import dataclass


ROOT = pathlib.Path(__file__).resolve().parents[1]
ASSET_ROOT = ROOT / "src/hooks/assets/cards"
BIG_DIR = ASSET_ROOT / "80x80"
MINI_DIR = ASSET_ROOT / "24x24"
GENERATED_DIR = ROOT / "src/hooks/generated"
GENERATED_ASSET_INC = GENERATED_DIR / "card_art_generated.inc"
GENERATED_NAME_INC = GENERATED_DIR / "card_name_generated.inc"
GENERATED_DATA_INC = GENERATED_DIR / "card_data_generated.inc"
GENERATED_DATA_SRC = GENERATED_DIR / "card_data_hooks.c"
CARD_IDS_H = ROOT / "include/constants/card_ids.h"
CUSTOM_CARD_MANIFEST = ROOT / "tools/card_art_manifest.json"
REQUIRED_STATS_KEYS = {
    "atk",
    "def",
    "cost",
    "attribute",
    "level",
    "type",
    "color",
    "monsterEffect",
    "spellEffect",
    "trapEffect",
}
OPTIONAL_STATS_KEYS = {"description"}
ALLOWED_ENTRY_KEYS = {"card_const", "card_name"} | REQUIRED_STATS_KEYS | OPTIONAL_STATS_KEYS


@dataclass(frozen=True)
class CardArtEntry:
    stem: str
    card_const: str
    card_name: str
    big_huff: pathlib.Path
    big_pal: pathlib.Path
    mini_lz: pathlib.Path
    stats: dict


def to_symbol(stem: str, suffix: str) -> str:
    parts = [part for part in re.split(r"[^A-Za-z0-9]+", stem) if part]
    return "s" + "".join(part[:1].upper() + part[1:] for part in parts) + suffix


def discover_card_constants() -> set[str]:
    src = CARD_IDS_H.read_text()
    return set(re.findall(r"^#define\s+([A-Z0-9_]+)\s+", src, flags=re.M))


def validate_manifest(manifest: object) -> dict:
    if not isinstance(manifest, dict):
        raise SystemExit("Manifest must be a JSON object with a top-level 'cards' array.")
    cards = manifest.get("cards")
    if not isinstance(cards, list):
        raise SystemExit("Manifest must contain a top-level 'cards' array.")

    seen_consts = set()
    validated = []
    for index, item in enumerate(cards):
        if not isinstance(item, dict):
            raise SystemExit(f"cards[{index}] must be an object.")

        card_const = item.get("card_const")
        card_name = item.get("card_name")
        if not isinstance(card_const, str) or not re.fullmatch(r"[A-Z0-9_]+", card_const):
            raise SystemExit(f"cards[{index}].card_const must be an uppercase constant name.")
        if not isinstance(card_name, str) or not card_name:
            raise SystemExit(f"cards[{index}].card_name must be a non-empty string.")
        if card_const in seen_consts:
            raise SystemExit(f"Duplicate card_const in manifest: {card_const}")
        seen_consts.add(card_const)

        extra = sorted(set(item.keys()) - ALLOWED_ENTRY_KEYS)
        if extra:
            raise SystemExit(f"cards[{index}] has unknown keys: {', '.join(extra)}")

        missing = sorted(REQUIRED_STATS_KEYS - item.keys())
        if missing:
            raise SystemExit(f"cards[{index}] is missing required keys: {', '.join(missing)}")

        stats = {key: item[key] for key in REQUIRED_STATS_KEYS | OPTIONAL_STATS_KEYS if key in item}
        for key in ("atk", "def", "cost", "attribute", "level", "type", "monsterEffect", "spellEffect", "trapEffect"):
            if not isinstance(stats[key], int):
                raise SystemExit(f"cards[{index}].{key} must be an integer.")
        if not isinstance(stats["color"], (str, int)):
            raise SystemExit(f"cards[{index}].color must be a C enum-style identifier or integer.")
        if "description" in stats and (not isinstance(stats["description"], str) or not stats["description"]):
            raise SystemExit(f"cards[{index}].description must be a non-empty string when present.")

        validated.append({"card_const": card_const, "card_name": card_name, **stats})

    return {"cards": validated}


def discover_entries() -> list[CardArtEntry]:
    card_constants = discover_card_constants()
    manifest = validate_manifest(json.loads(CUSTOM_CARD_MANIFEST.read_text()))
    manifest_by_const = {item["card_const"]: item for item in manifest["cards"]}
    entries = []
    missing_manifest = []
    for big_huff in sorted(BIG_DIR.glob("*_80x80.huff")):
        stem = big_huff.name.removesuffix("_80x80.huff")
        card_const = stem.upper()
        big_pal = BIG_DIR / f"{stem}_80x80.gbapal"
        mini_lz = MINI_DIR / f"{stem}_24x24.lz"
        if card_const not in card_constants:
            continue
        if card_const not in manifest_by_const:
            missing_manifest.append(card_const)
            continue
        if not big_pal.exists() or not mini_lz.exists():
            continue
        item = manifest_by_const[card_const]
        entries.append(CardArtEntry(stem, card_const, item["card_name"], big_huff, big_pal, mini_lz, item))

    if missing_manifest:
        raise SystemExit("Missing manifest entries for: " + ", ".join(sorted(missing_manifest)))
    return entries


def render_asset_inc(entries: list[CardArtEntry]) -> str:
    lines = ["#include \"global.h\"", ""]
    for entry in entries:
        big_symbol = to_symbol(entry.stem, "BigArt")
        pal_symbol = to_symbol(entry.stem, "BigPalette")
        mini_symbol = to_symbol(entry.stem, "MiniArt")
        lines.extend(
            [
                f'static const unsigned char {big_symbol}[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/80x80/{entry.big_huff.name}");',
                f'static const unsigned short {pal_symbol}[] __attribute__((section(".append_assets"))) = INCBIN_U16("src/hooks/assets/cards/80x80/{entry.big_pal.name}");',
                f'static const unsigned char {mini_symbol}[] __attribute__((section(".append_assets"))) = INCBIN_U8("src/hooks/assets/cards/24x24/{entry.mini_lz.name}");',
                "",
            ]
        )
    return "\n".join(lines).rstrip() + "\n"


def render_name_inc(entries: list[CardArtEntry]) -> str:
    lines = []
    for entry in entries:
        name_symbol = to_symbol(entry.stem, "Name")
        lines.append(f'static const u8 {name_symbol}[] __attribute__((section(".append_assets"))) = "{entry.card_name}";')
    lines.append("")
    lines.append("static u8 *GetCardName_Hook(unsigned short cardId) {")
    for entry in entries:
        name_symbol = to_symbol(entry.stem, "Name")
        lines.append(f"  if (cardId == {entry.card_const})")
        lines.append(f"    return (u8 *){name_symbol};")
    lines.append("")
    lines.append("  return gCardNames[cardId];")
    lines.append("}")
    lines.append("")
    return "\n".join(lines)


def render_data_inc(entries: list[CardArtEntry]) -> str:
    lines = []
    for entry in entries:
        if entry.card_const == "CARD_NONE":
            continue
        s = entry.stats
        lines.append(f"  [{entry.card_const}] = {{")
        for key in ("atk", "def", "cost", "attribute", "level", "type"):
            lines.append(f"    .{key} = {s[key]},")
        lines.append(f"    .color = {s['color']},")
        lines.append(f"    .monsterEffect = {s['monsterEffect']},")
        lines.append(f"    .spellEffect = {s['spellEffect']},")
        lines.append(f"    .trapEffect = {s['trapEffect']},")
        if s.get("description"):
            lines.append(f"    .description = {s['description']},")
        lines.append("  },")
    lines.append("")
    return "\n".join(lines)


def render_data_src(manifest: dict) -> str:
    lines = [
        '#include "global.h"',
        '#include "configs/runtime.h"',
        '#include "constants/card_ids.h"',
        '#include "constants/card_descriptions.h"',
        "",
        "#define NORMAL_CARD 0",
        "#define EFFECT_CARD 1",
        "#define FUSION_CARD 2",
        "#define SPELL_CARD 3",
        "#define TRAP_CARD 4",
        "#define RITUAL_CARD 5",
        "",
        "const CardData gCardData_NEW[CUSTOM_CARD_START + 1] APPEND_RODATA = {",
        "  [CARD_NONE] = {",
        "    .atk = 0xFFFF,",
        "    .def = 0xFFFF,",
        "    .cost = 0,",
        "    .attribute = 0,",
        "    .level = 0,",
        "    .type = 0,",
        "    .color = NORMAL_CARD,",
        "    .monsterEffect = 0,",
        "    .spellEffect = 0,",
        "    .trapEffect = 0,",
        "  },",
    ]
    for item in manifest["cards"]:
        if item["card_const"] == "CARD_NONE":
            continue
        lines.append(f"  [{item['card_const']}] = {{")
        for key in ("atk", "def", "cost", "attribute", "level", "type"):
            lines.append(f"    .{key} = {item[key]},")
        lines.append(f"    .color = {item['color']},")
        lines.append(f"    .monsterEffect = {item['monsterEffect']},")
        lines.append(f"    .spellEffect = {item['spellEffect']},")
        lines.append(f"    .trapEffect = {item['trapEffect']},")
        if "description" in item:
            lines.append(f"    .description = {item['description']},")
        lines.append("  },")
    lines.append("};")
    lines.append("")
    return "\n".join(lines)


def update_file(path: pathlib.Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Generate card art and name hook includes from matching files in src/hooks/assets/cards."
    )
    parser.add_argument("--print", action="store_true", help="Print the generated content instead of writing files")
    args = parser.parse_args()

    entries = discover_entries()
    manifest = validate_manifest(json.loads(CUSTOM_CARD_MANIFEST.read_text()))
    if not entries:
        raise SystemExit("No matching card art pairs found.")

    asset_inc = render_asset_inc(entries)
    name_inc = render_name_inc(entries)
    data_inc = render_data_inc(entries)
    data_src = render_data_src(manifest)

    if args.print:
        print(f"--- {GENERATED_ASSET_INC} ---")
        print(asset_inc, end="")
        print(f"--- {GENERATED_NAME_INC} ---")
        print(name_inc, end="")
        print(f"--- {GENERATED_DATA_INC} ---")
        print(data_inc, end="")
        print(f"--- {GENERATED_DATA_SRC} ---")
        print(data_src, end="")
        return 0

    update_file(GENERATED_ASSET_INC, asset_inc)
    update_file(GENERATED_NAME_INC, name_inc)
    update_file(GENERATED_DATA_INC, data_inc)
    update_file(GENERATED_DATA_SRC, data_src)
    print(f"Generated {len(entries)} card art bindings.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
