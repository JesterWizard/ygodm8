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
CUSTOM_CARD_MANIFEST = ROOT / "tools/card_data_manifest.json"
EFFECT_ENUM_HEADERS = {
    "monsterEffect": ROOT / "include/constants/monster_effects.h",
    "spellEffect": ROOT / "include/constants/spell_effects.h",
}

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
    "password",
}
OPTIONAL_STATS_KEYS = {"description"}
ALLOWED_ENTRY_KEYS = {"card_const", "card_name"} | REQUIRED_STATS_KEYS | OPTIONAL_STATS_KEYS
ASSET_ENTRY_KEYS = {"big_art", "big_palette", "mini_art"}
ALLOWED_ENTRY_KEYS |= ASSET_ENTRY_KEYS


@dataclass(frozen=True)
class CardArtEntry:
    stem: str
    card_const: str
    card_name: str
    big_art: pathlib.Path
    big_pal: pathlib.Path
    mini_art: pathlib.Path
    stats: dict


def to_symbol(stem: str, suffix: str) -> str:
    parts = [part for part in re.split(r"[^A-Za-z0-9]+", stem) if part]
    return "s" + "".join(part[:1].upper() + part[1:] for part in parts) + suffix


def manifest_asset_path(value: str, default: str) -> pathlib.Path:
    path = pathlib.Path(value if value else default)
    return path if path.is_absolute() else ROOT / path


def include_asset_path(path: pathlib.Path) -> str:
    return path.relative_to(ROOT).as_posix() if path.is_absolute() else path.as_posix()


def parse_enum_value(text: str, start: int) -> tuple[int, int]:
    i = start
    while i < len(text) and text[i] in " \t\r":
        i += 1
    if i < len(text) and text[i] == "=":
        i += 1
        while i < len(text) and text[i] in " \t\r":
            i += 1
        j = i
        if j < len(text) and text[j] in "0123456789":
            while j < len(text) and text[j] in "0123456789":
                j += 1
            return int(text[i:j]), j
        if j < len(text) and text[j] in "Xx":
            j += 1
            while j < len(text) and text[j] in "0123456789abcdefABCDEF":
                j += 1
            return int(text[i:j], 16), j
    return None, start


def parse_enum_header(path: pathlib.Path) -> dict[str, int]:
    text = path.read_text()
    mapping = {}
    idx = text.find("enum {")
    if idx < 0:
        idx = text.find("enum\n{")
    if idx < 0:
        idx = text.find("enum\r\n{")
    if idx < 0:
        return mapping
    idx = text.find("{", idx) + 1
    value = 0
    brace_depth = 1
    i = idx
    while i < len(text) and brace_depth > 0:
        c = text[i]
        if c == "/" and i + 1 < len(text):
            if text[i + 1] == "/":
                end = text.find("\n", i)
                i = end if end >= 0 else len(text)
                continue
            if text[i + 1] == "*":
                end = text.find("*/", i + 2)
                i = end + 2 if end >= 0 else len(text)
                continue
        if c == "{":
            brace_depth += 1
            i += 1
            continue
        if c == "}":
            brace_depth -= 1
            i += 1
            continue
        if c == ",":
            value += 1
            i += 1
            continue
        if c in " \t\r\n":
            i += 1
            continue
        m = re.match(r"[A-Za-z_][A-Za-z0-9_]*", text[i:])
        if m:
            name = m.group()
            end = i + len(name)
            eq_val, end2 = parse_enum_value(text, end)
            if eq_val is not None:
                mapping[name] = eq_val
                value = eq_val + 1
                i = end2
            else:
                mapping[name] = value
                value += 1
                i = end
            if i < len(text) and text[i] == ",":
                i += 1
            continue
        i += 1
    return mapping


def load_effect_enums() -> dict[str, dict[str, int]]:
    result = {}
    for key, header_path in EFFECT_ENUM_HEADERS.items():
        if header_path.exists():
            result[key] = parse_enum_header(header_path)
    return result


def resolve_effect_value(effect_key: str, raw_value: object, enum_tables: dict[str, dict[str, int]]) -> int:
    if isinstance(raw_value, int):
        return raw_value
    if isinstance(raw_value, str):
        table = enum_tables.get(effect_key)
        if table is None:
            raise SystemExit(
                f"Cannot resolve string '{raw_value}' for {effect_key}: "
                f"no enum header loaded for this field."
            )
        resolved = table.get(raw_value)
        if resolved is None:
            raise SystemExit(
                f"Unknown enum value '{raw_value}' for {effect_key}. "
                f"Valid values: {', '.join(sorted(table))}"
            )
        return resolved
    raise SystemExit(f"{effect_key} must be an integer or a C enum-style identifier string.")


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

        stats = {key: item[key] for key in REQUIRED_STATS_KEYS | OPTIONAL_STATS_KEYS | ASSET_ENTRY_KEYS if key in item}
        
        for key in ("atk", "def", "cost", "level"):
            if not isinstance(stats[key], int):
                raise SystemExit(f"cards[{index}].{key} must be an integer.")

        for key in ("monsterEffect", "spellEffect", "trapEffect"):
            if not isinstance(stats[key], (int, str)):
                raise SystemExit(f"cards[{index}].{key} must be an integer or a C enum-style identifier string.")
        
        # Validating flexible fields (Allowing defines/strings or integers)
        for key in ("color", "type", "attribute"):
            if not isinstance(stats[key], (str, int)):
                raise SystemExit(f"cards[{index}].{key} must be a C enum-style identifier (string) or integer.")

        password = stats.get("password")
        if not isinstance(password, list) or len(password) != 8 or not all(isinstance(d, int) and 0 <= d <= 15 for d in password):
            raise SystemExit(f"cards[{index}].password must be an array of 8 integers (0-15).")

        if "description" in stats:
            description = stats["description"]
            if not isinstance(description, dict):
                raise SystemExit(f"cards[{index}].description must be an object when present.")
            symbol = description.get("symbol")
            pages = description.get("pages")
            if not isinstance(symbol, str) or not symbol:
                raise SystemExit(f"cards[{index}].description.symbol must be a non-empty string.")
            if not isinstance(pages, list) or len(pages) != 2 or not all(isinstance(page, str) and page for page in pages):
                raise SystemExit(f"cards[{index}].description.pages must be a 2-item array of non-empty strings.")

        for key in ASSET_ENTRY_KEYS:
            if key in stats and not isinstance(stats[key], str):
                raise SystemExit(f"cards[{index}].{key} must be a string when present.")

        validated.append({"card_const": card_const, "card_name": card_name, **stats})

    return {"cards": validated}


def render_card_ids_header(manifest: dict) -> str:
    card_count = len(manifest["cards"]) - 1
    lines = [
        "#ifndef GUARD_CONSTANTS_CARD_IDS_H",
        "#define GUARD_CONSTANTS_CARD_IDS_H",
        "",
    ]
    for index, item in enumerate(manifest["cards"]):
        lines.append(f"#define {item['card_const']:<40} 0x{index:04X}")
    lines.extend([
        "",
        f"#define NUM_CARDS                               0x{card_count:04X}",
        f"#define NUM_TRUE_CARDS                          0x{card_count:04X}",
    ])
    lines.extend([
        "",
        "#endif // GUARD_CONSTANTS_CARD_IDS_H",
        "",
    ])
    return "\n".join(lines)


def discover_entries() -> list[CardArtEntry]:
    card_constants = discover_card_constants()
    manifest = validate_manifest(json.loads(CUSTOM_CARD_MANIFEST.read_text()))
    enum_tables = load_effect_enums()
    for item in manifest["cards"]:
        for key in ("monsterEffect", "spellEffect", "trapEffect"):
            item[key] = resolve_effect_value(key, item[key], enum_tables)
    manifest_by_const = {item["card_const"]: item for item in manifest["cards"]}
    entries = []
    missing_manifest = []
    for big_huff in sorted(BIG_DIR.glob("*_80x80.huff")):
        stem = big_huff.name.removesuffix("_80x80.huff")
        card_const = stem.upper()
        if card_const not in card_constants:
            continue
        if card_const not in manifest_by_const:
            missing_manifest.append(card_const)
            continue
        item = manifest_by_const[card_const]
        big_art = manifest_asset_path(item.get("big_art", ""), f"src/hooks/assets/cards/80x80/{stem}_80x80.huff")
        big_pal = manifest_asset_path(item.get("big_palette", ""), f"src/hooks/assets/cards/80x80/{stem}_80x80.gbapal")
        mini_art = manifest_asset_path(item.get("mini_art", ""), f"src/hooks/assets/cards/24x24/{stem}_24x24.lz")
        if not big_art.exists() or not big_pal.exists() or not mini_art.exists():
            continue
        entries.append(CardArtEntry(stem, card_const, item["card_name"], big_art, big_pal, mini_art, item))

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
                f'static const unsigned char {big_symbol}[] __attribute__((section(".append_assets"))) = INCBIN_U8("{include_asset_path(entry.big_art)}");',
                f'static const unsigned short {pal_symbol}[] __attribute__((section(".append_assets"))) = INCBIN_U16("{include_asset_path(entry.big_pal)}");',
                f'static const unsigned char {mini_symbol}[] __attribute__((section(".append_assets"))) = INCBIN_U8("{include_asset_path(entry.mini_art)}");',
                "",
            ]
        )
    lines.append("const unsigned char *gCardArts_Hook[] APPEND_RODATA = {")
    for entry in entries:
        lines.append(f"  [{entry.card_const}] = {to_symbol(entry.stem, 'BigArt')},")
    lines.append("};")
    lines.append("")
    lines.append("const unsigned short *gCardArtPalettes_Hook[] APPEND_RODATA = {")
    for entry in entries:
        lines.append(f"  [{entry.card_const}] = {to_symbol(entry.stem, 'BigPalette')},")
    lines.append("};")
    lines.append("")
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
        for key in ("atk", "def", "cost", "attribute", "level", "type", "color"):
            lines.append(f"    .{key} = {s[key]},")
        lines.append(f"    .monsterEffect = {s['monsterEffect']},")
        lines.append(f"    .spellEffect = {s['spellEffect']},")
        lines.append(f"    .trapEffect = {s['trapEffect']},")
        password_digits = ", ".join(str(d) for d in s['password'])
        lines.append(f"    .password = {{{password_digits}}},")
        if s.get("description"):
            lines.append(f"    .description = {s['description']['symbol']},")
        lines.append("  },")
    lines.append("")
    return "\n".join(lines)


def wrap_page(text: str) -> list[str]:
    row_widths = (12, 14, 14, 14, 12)
    words = text.split()
    lines = []
    word_index = 0

    for width in row_widths:
        if word_index >= len(words):
            lines.append("")
            continue

        line_words = []
        line_len = 0

        while word_index < len(words):
            word = words[word_index]
            word_len = len(word)
            if word_len > width:
                raise SystemExit(f"Description word does not fit in width {width}: {word}")
            next_len = word_len if not line_words else line_len + 1 + word_len
            if next_len > width:
                break
            line_words.append(word)
            line_len = next_len
            word_index += 1

        if not line_words:
            raise SystemExit(f"Could not fit description text into width {width}.")
        lines.append(" ".join(line_words).ljust(width))

    if word_index < len(words):
        raise SystemExit(f"Description text does not fit in one page: {' '.join(words[word_index:])}")

    return lines


def render_description_inc(manifest: dict) -> str:
    lines = []
    for item in manifest["cards"]:
        description = item.get("description")
        if not description:
            continue
        symbol = description["symbol"]
        page1, page2 = description["pages"]
        payload = ["  ", "^2", *wrap_page(page1), "^", *wrap_page(page2), "^"]
        data = "".join(payload).encode("ascii") + b"\0"
        lines.append(f"const u8 {symbol}[] APPEND_TEXT = {{")
        for i in range(0, len(data), 12):
            chunk = data[i:i + 12]
            lines.append("    " + ", ".join(f"0x{byte:02X}" for byte in chunk) + ",")
        lines.append("};")
        lines.append("")
    return "\n".join(lines).rstrip() + ("\n" if lines else "")


def render_data_src(manifest: dict) -> str:
    lines = [
        '#include "global.h"',
        '#include "common-chax.h"',
        '#include "constants/card_descriptions.h"',
        '#include "../card_description_data_generated.inc"',
        "",
        "#define NORMAL_CARD 0",
        "#define EFFECT_CARD 1",
        "#define FUSION_CARD 2",
        "#define SPELL_CARD 3",
        "#define TRAP_CARD 4",
        "#define RITUAL_CARD 5",
        "",
        f"const CardData gCardData_NEW[{len(manifest['cards'])}] APPEND_RODATA = {{",
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
        "    .password = {15, 15, 15, 15, 15, 15, 15, 14},",
        "  },",
    ]
    for item in manifest["cards"]:
        if item["card_const"] == "CARD_NONE":
            continue
        lines.append(f"  [{item['card_const']}] = {{")
        for key in ("atk", "def", "cost", "attribute", "level", "type", "color"):
            lines.append(f"    .{key} = {item[key]},")
        lines.append(f"    .monsterEffect = {item['monsterEffect']},")
        lines.append(f"    .spellEffect = {item['spellEffect']},")
        lines.append(f"    .trapEffect = {item['trapEffect']},")
        password_digits = ", ".join(str(d) for d in item['password'])
        lines.append(f"    .password = {{{password_digits}}},")
        if "description" in item:
            lines.append(f"    .description = {item['description']['symbol']},")
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
    parser.add_argument("--card-ids", action="store_true", help="Generate include/constants/card_ids.h from the manifest")
    args = parser.parse_args()

    manifest = validate_manifest(json.loads(CUSTOM_CARD_MANIFEST.read_text()))
    enum_tables = load_effect_enums()
    for item in manifest["cards"]:
        for key in ("monsterEffect", "spellEffect", "trapEffect"):
            item[key] = resolve_effect_value(key, item[key], enum_tables)

    if args.card_ids:
        card_ids = render_card_ids_header(manifest)
        if args.print:
            print(card_ids, end="")
        else:
            update_file(CARD_IDS_H, card_ids)
        return 0

    entries = discover_entries()
    if not entries:
        raise SystemExit("No matching card art pairs found.")

    asset_inc = render_asset_inc(entries)
    name_inc = render_name_inc(entries)
    data_inc = render_data_inc(entries)
    data_src = render_data_src(manifest)
    description_inc = render_description_inc(manifest)

    if args.print:
        print(f"--- {CARD_IDS_H} ---")
        print(render_card_ids_header(manifest), end="")
        print(f"--- {GENERATED_ASSET_INC} ---")
        print(asset_inc, end="")
        print(f"--- {GENERATED_NAME_INC} ---")
        print(name_inc, end="")
        print(f"--- {GENERATED_DATA_INC} ---")
        print(data_inc, end="")
        print(f"--- {GENERATED_DATA_SRC} ---")
        print(data_src, end="")
        print(f"--- src/hooks/card_description_data_generated.inc ---")
        print(description_inc, end="")
        return 0

    update_file(CARD_IDS_H, render_card_ids_header(manifest))
    update_file(GENERATED_ASSET_INC, asset_inc)
    update_file(GENERATED_NAME_INC, name_inc)
    update_file(GENERATED_DATA_INC, data_inc)
    update_file(GENERATED_DATA_SRC, data_src)
    update_file(ROOT / "src/hooks/card_description_data_generated.inc", description_inc)
    print(f"Generated {len(entries)} card art bindings.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
