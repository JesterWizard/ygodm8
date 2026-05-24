#!/usr/bin/env python3

import argparse
import json
import pathlib
import re
import struct
import subprocess
import tempfile
from PIL import Image
from dataclasses import dataclass


ROOT = pathlib.Path(__file__).resolve().parents[1]
ASSET_ROOT = ROOT / "src/hooks/assets/cards"
BIG_DIR = ASSET_ROOT / "80x80"
MINI_DIR = ASSET_ROOT / "24x24"
EXPORT_DIR = ASSET_ROOT / "export"
BASE_ROM = ROOT / "baserom.gba"
GENERATED_DIR = ROOT / "src/hooks/generated"
GENERATED_ASSET_INC = GENERATED_DIR / "card_art_generated.inc"
GENERATED_NAME_INC = GENERATED_DIR / "card_name_generated.inc"
GENERATED_DATA_INC = GENERATED_DIR / "card_data_generated.inc"
GENERATED_DATA_SRC = GENERATED_DIR / "card_data_hooks.c"
GENERATED_TRUNK_INC = GENERATED_DIR / "card_trunk_generated.inc"
GENERATED_ACTIVATION_TEXT_INC = GENERATED_DIR / "card_activation_text_generated.inc"
GENERATED_ACTIVATION_TEXT_LOOKUP_INC = GENERATED_DIR / "card_activation_text_lookup_generated.inc"
CARD_IDS_H = ROOT / "include/constants/card_ids.h"
CUSTOM_CARD_MANIFEST = ROOT / "tools/card_data_manifest.json"
RUNTIME_CONFIG_C = ROOT / "configs/runtime.c"
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
OPTIONAL_STATS_KEYS = {"description", "activation_description", "lock_after_activation"}
ALLOWED_ENTRY_KEYS = {"card_const", "card_name", "trunk_card"} | REQUIRED_STATS_KEYS | OPTIONAL_STATS_KEYS
ASSET_ENTRY_KEYS = {"big_art", "big_palette", "mini_art"}
ALLOWED_ENTRY_KEYS |= ASSET_ENTRY_KEYS

GBAFX = ROOT / "tools/gbagfx/gbagfx"


@dataclass
class CardArtEntry:
    index: int
    stem: str
    card_const: str
    card_name: str
    big_art: pathlib.Path | None
    big_pal: pathlib.Path | None
    mini_art: pathlib.Path | None
    stats: dict


def to_symbol(stem: str, suffix: str) -> str:
    parts = [part for part in re.split(r"[^A-Za-z0-9]+", stem) if part]
    return "s" + "".join(part[:1].upper() + part[1:] for part in parts) + suffix


def manifest_asset_path(value: str, default: str) -> pathlib.Path:
    path = pathlib.Path(value if value else default)
    return path if path.is_absolute() else ROOT / path


def load_runtime_flag(name: str) -> bool:
    text = RUNTIME_CONFIG_C.read_text()
    match = re.search(rf"\.{re.escape(name)}\s*=\s*(TRUE|FALSE)", text)
    if not match:
        raise SystemExit(f"Unable to find runtime flag .{name} in {RUNTIME_CONFIG_C}.")
    return match.group(1) == "TRUE"


def include_asset_path(path: pathlib.Path) -> str:
    return path.relative_to(ROOT).as_posix() if path.is_absolute() else path.as_posix()


def run_gbagfx(input_path: pathlib.Path, output_path: pathlib.Path) -> None:
    subprocess.run([str(GBAFX), str(input_path), str(output_path)], check=True)


def load_gba_palette(path: pathlib.Path) -> list[tuple[int, int, int]]:
    data = path.read_bytes()
    if len(data) % 2 != 0:
        raise SystemExit(f"Palette file must contain an even number of bytes: {path}")
    colors = []
    for i in range(0, len(data), 2):
        value = data[i] | (data[i + 1] << 8)
        colors.append(
            (
                (value & 0x1F) * 255 // 31,
                ((value >> 5) & 0x1F) * 255 // 31,
                ((value >> 10) & 0x1F) * 255 // 31,
            )
        )
    return colors


def make_paletted_mini(big_png: pathlib.Path, big_palette: pathlib.Path, mini_png: pathlib.Path) -> None:
    image = Image.open(big_png).convert("RGBA")
    image = image.resize((24, 24), Image.Resampling.LANCZOS).convert("RGBA")

    palette = load_gba_palette(big_palette)
    pal_img = Image.new("P", (1, 1))
    palette_data = []
    for r, g, b in palette[:16]:
        palette_data.extend([r, g, b])
    palette_data.extend([0, 0, 0] * (256 - len(palette_data) // 3))
    pal_img.putpalette(palette_data)

    quantized = image.convert("RGB").quantize(palette=pal_img, dither=Image.Dither.NONE)
    mini_png.parent.mkdir(parents=True, exist_ok=True)
    quantized.save(mini_png)


def build_mini_assets(big_png: pathlib.Path, big_palette: pathlib.Path, mini_base: pathlib.Path) -> pathlib.Path:
    mini_png = mini_base.with_suffix(".png")
    mini_4bpp = mini_base.with_suffix(".4bpp")
    mini_lz = mini_base.with_suffix(".lz")

    make_paletted_mini(big_png, big_palette, mini_png)
    run_gbagfx(mini_png, mini_4bpp)
    run_gbagfx(mini_4bpp, mini_lz)
    return mini_lz


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
    description_pages_max = 3

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

        for desc_key in ("description", "activation_description"):
            if desc_key not in stats:
                continue
            description = stats[desc_key]
            if not isinstance(description, dict):
                raise SystemExit(f"cards[{index}].{desc_key} must be an object when present.")
            symbol = description.get("symbol")
            pages = description.get("pages")
            if not isinstance(symbol, str) or not symbol:
                raise SystemExit(f"cards[{index}].{desc_key}.symbol must be a non-empty string.")
            if not isinstance(pages, list) or not all(isinstance(page, str) and page for page in pages):
                raise SystemExit(f"cards[{index}].{desc_key}.pages must be an array of non-empty strings.")
            min_pages = 1 if desc_key == "activation_description" else 2
            if len(pages) < min_pages or len(pages) > description_pages_max:
                raise SystemExit(
                    f"cards[{index}].{desc_key}.pages must contain between {min_pages} and {description_pages_max} strings."
                )

        for key in ASSET_ENTRY_KEYS:
            if key in stats and not isinstance(stats[key], str):
                raise SystemExit(f"cards[{index}].{key} must be a string when present.")
        if "trunk_card" in item and not isinstance(item["trunk_card"], bool):
            raise SystemExit(f"cards[{index}].trunk_card must be a boolean when present.")
        if "lock_after_activation" in item and not isinstance(item["lock_after_activation"], bool):
            raise SystemExit(f"cards[{index}].lock_after_activation must be a boolean when present.")

        validated.append({"card_const": card_const, "card_name": card_name, **stats, **({"trunk_card": item["trunk_card"]} if "trunk_card" in item else {})})

    return {"cards": validated}


def render_card_ids_header(manifest: dict) -> str:
    cards = manifest["cards"]
    custom_start = next((i for i, item in enumerate(cards) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"), len(cards))
    lines = [
        "#ifndef GUARD_CONSTANTS_CARD_IDS_H",
        "#define GUARD_CONSTANTS_CARD_IDS_H",
        "",
    ]
    for index, item in enumerate(cards[:custom_start]):
        lines.append(f"#define {item['card_const']:<40} 0x{index:04X}")
    for index, item in enumerate(cards[custom_start:], start=custom_start):
        lines.append(f"#define {item['card_const']:<40} 0x{index:04X}")
    lines.extend([
        "",
        f"#define NUM_CARDS                               0x{custom_start:04X}",
        f"#define NUM_TRUE_CARDS                          (NUM_CARDS - 1)",
        f"#define CUSTOM_CARD_START                       SORCERER_OF_DARK_MAGIC",
    ])
    lines.extend([
        "",
        "#endif // GUARD_CONSTANTS_CARD_IDS_H",
        "",
    ])
    return "\n".join(lines)


def discover_entries(manifest: dict) -> list[CardArtEntry]:
    enum_tables = load_effect_enums()
    entries = []
    custom_start = next((i for i, item in enumerate(manifest["cards"]) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"), len(manifest["cards"]))
    for index, item in enumerate(manifest["cards"][custom_start:], start=custom_start):
        for key in ("monsterEffect", "spellEffect", "trapEffect"):
            item[key] = resolve_effect_value(key, item[key], enum_tables)
        stem = item["card_const"].lower()
        big_art = manifest_asset_path(item.get("big_art", ""), f"src/hooks/assets/cards/80x80/{stem}.huff")
        big_pal = manifest_asset_path(item.get("big_palette", ""), f"src/hooks/assets/cards/80x80/{stem}.gbapal")
        mini_art = manifest_asset_path(item.get("mini_art", ""), f"src/hooks/assets/cards/24x24/{stem}.lz")
        entries.append(
            CardArtEntry(
                index=index,
                stem=stem,
                card_const=item["card_const"],
                card_name=item["card_name"],
                big_art=big_art if big_art.exists() else None,
                big_pal=big_pal if big_pal.exists() else None,
                mini_art=mini_art if mini_art.exists() else None,
                stats=item,
            )
        )

    return entries


def render_asset_inc(entries: list[CardArtEntry]) -> str:
    lines = ["#include \"global.h\"", ""]
    for entry in entries:
        big_symbol = to_symbol(entry.stem, "BigArt")
        pal_symbol = to_symbol(entry.stem, "BigPalette")
        mini_symbol = to_symbol(entry.stem, "MiniArt")
        if entry.big_art:
            lines.append(
                f'static const unsigned char {big_symbol}[] __attribute__((section(".append_assets"))) = INCBIN_U8("{include_asset_path(entry.big_art)}");'
            )
        if entry.big_pal:
            lines.append(
                f'static const unsigned short {pal_symbol}[] __attribute__((section(".append_assets"))) = INCBIN_U16("{include_asset_path(entry.big_pal)}");'
            )
        if entry.mini_art:
            lines.append(
            f'static const unsigned char {mini_symbol}[] __attribute__((section(".append_assets"))) = INCBIN_U8("{include_asset_path(entry.mini_art)}");'
            )
        lines.append("")
    lines.append("const unsigned char *gCardArts_Hook[] APPEND_RODATA = {")
    for entry in entries:
        if entry.big_art and entry.big_pal:
            lines.append(f"  [0x{entry.index:04X}] = {to_symbol(entry.stem, 'BigArt')},")
        else:
            lines.append(f"  [0x{entry.index:04X}] = 0,")
    lines.append("};")
    lines.append("")
    lines.append("const unsigned short *gCardArtPalettes_Hook[] APPEND_RODATA = {")
    for entry in entries:
        if entry.big_art and entry.big_pal:
            lines.append(f"  [0x{entry.index:04X}] = {to_symbol(entry.stem, 'BigPalette')},")
        else:
            lines.append(f"  [0x{entry.index:04X}] = 0,")
    lines.append("};")
    lines.append("")
    lines.append("const unsigned char *gMiniCardArts_Hook[] APPEND_RODATA = {")
    for entry in entries:
        if entry.mini_art:
            lines.append(f"  [0x{entry.index:04X}] = {to_symbol(entry.stem, 'MiniArt')},")
        else:
            lines.append(f"  [0x{entry.index:04X}] = 0,")
    lines.append("};")
    lines.append("")
    return "\n".join(lines).rstrip() + "\n"


def render_name_inc(manifest: dict) -> str:
    custom_start = next((i for i, item in enumerate(manifest["cards"]) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"), len(manifest["cards"]))
    lines = []
    for index, item in enumerate(manifest["cards"][custom_start:], start=custom_start):
        name_symbol = to_symbol(item["card_const"].lower(), "Name")
        lines.append(f'static const u8 {name_symbol}[] __attribute__((section(".append_assets"))) = "{item["card_name"]}";')
    lines.append("")
    lines.append("static u8 *GetCardName_Hook(unsigned short cardId) {")
    for index, item in enumerate(manifest["cards"][custom_start:], start=custom_start):
        name_symbol = to_symbol(item["card_const"].lower(), "Name")
        lines.append(f"  if (cardId == 0x{index:04X})")
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
        lines.append(f"  [0x{entry.index:04X}] = {{")
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


def split_paragraphs(text: str) -> list[str]:
    normalized = text.replace("\\n", "\n")
    return normalized.split("\n")


def wrap_paragraph(text: str, width: int) -> list[str]:
    words = text.split()
    if not words:
        return [""]

    lines = []
    word_index = 0
    while word_index < len(words):
        line_words = []
        line_len = 0

        while word_index < len(words):
            word = words[word_index]
            word_len = len(word)
            if word_len > width:
                if width <= 1:
                    raise SystemExit(f"Description word does not fit in width {width}: {word}")
                chunk = word[: width - 1] + "-"
                words[word_index] = word[width - 1 :]
                word = chunk
                word_len = len(word)
            next_len = word_len if not line_words else line_len + 1 + word_len
            if next_len > width:
                break
            line_words.append(word)
            line_len = next_len
            word_index += 1

        if not line_words:
            raise SystemExit(f"Could not fit description text into width {width}.")
        lines.append(" ".join(line_words))

    return lines


def wrap_page(text: str) -> list[str]:
    row_widths = (27, 27, 27, 27, 27)
    words = re.findall(r"#\d+|[^\s#]+", text)
    lines = []

    word_index = 0
    for width in row_widths:
        if word_index >= len(words):
            lines.append("")
            continue

        line_parts = []
        visible_len = 0
        last_was_control = False

        while word_index < len(words):
            word = words[word_index]
            is_control = re.fullmatch(r"#\d+", word) is not None
            word_len = 0 if is_control else len(word)
            gap = 0 if not line_parts or last_was_control or is_control else 1
            next_len = visible_len + gap + word_len

            if not is_control and next_len > width:
                break

            if not is_control and line_parts and not last_was_control:
                line_parts.append(" ")
                visible_len += 1

            line_parts.append(word)
            visible_len += word_len
            last_was_control = is_control
            word_index += 1

        if not line_parts:
            raise SystemExit(f"Could not fit description text into width {width}.")
        lines.append("".join(line_parts))

    if word_index < len(words):
        raise SystemExit(f"Description text does not fit in one page: {' '.join(words[word_index:])}")

    return lines


def wrap_activation_lines(text: str) -> list[str]:
    width = 27
    words = re.findall(r"#\d+|[^\s#]+", text)
    lines = []

    word_index = 0
    while word_index < len(words):
        line_parts = []
        visible_len = 0
        last_was_control = False

        while word_index < len(words):
            word = words[word_index]
            is_control = re.fullmatch(r"#\d+", word) is not None
            word_len = 0 if is_control else len(word)
            gap = 0 if not line_parts or last_was_control or is_control else 1
            next_len = visible_len + gap + word_len

            if not is_control and next_len > width:
                break

            if not is_control and line_parts and not last_was_control:
                line_parts.append(" ")
                visible_len += 1

            line_parts.append(word)
            visible_len += word_len
            last_was_control = is_control
            word_index += 1

        if not line_parts:
            raise SystemExit(f"Could not fit activation text into width {width}.")
        lines.append("".join(line_parts))

    return lines


def normalize_activation_page(text: str) -> str:
    normalized = text.replace("\\n", "\n").replace("\r\n", "\n").replace("\r", "\n")
    lines = [line.strip() for line in normalized.split("\n")]
    while lines and lines[-1] == "":
        lines.pop()
    while lines and lines[0] == "":
        lines.pop(0)
    return "#0".join(lines)


def wrap_activation_page(text: str) -> str:
    normalized = normalize_activation_page(text)
    lines = []
    for line in normalized.split("#0"):
        if line:
            lines.extend(wrap_activation_lines(line))
        else:
            lines.append("")
    return "#0".join(lines)


def wrap_description_page(text: str) -> list[str]:
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
                if width <= 1:
                    raise SystemExit(f"Description word does not fit in width {width}: {word}")
                chunk = word[: width - 1] + "-"
                words[word_index] = word[width - 1 :]
                word = chunk
                word_len = len(word)
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
        pages = description["pages"]
        payload = ["  ", f"^{len(pages)}"]
        for page in pages:
            payload.extend(wrap_description_page(page))
            payload.append("^")
        data = "".join(payload).encode("ascii") + b"\0"
        lines.append(f"const u8 {symbol}[] APPEND_TEXT = {{")
        for i in range(0, len(data), 12):
            chunk = data[i:i + 12]
            lines.append("    " + ", ".join(f"0x{byte:02X}" for byte in chunk) + ",")
        lines.append("};")
        lines.append("")
    return "\n".join(lines).rstrip() + ("\n" if lines else "")


def render_activation_description_inc(manifest: dict) -> str:
    lines = []
    intro_page = "#2\nwas activated."
    for item in manifest["cards"]:
        activation_description = item.get("activation_description")
        if not activation_description:
            continue
        symbol = activation_description["symbol"]
        pages = activation_description["pages"]
        payload = [wrap_activation_page(intro_page), "#1"]
        for page in pages:
            payload.append(wrap_activation_page(page))
            payload.append("#1")
        data = "".join(payload).encode("ascii") + b"\0"
        lines.append(f"const u8 {symbol}[] APPEND_TEXT = {{")
        for i in range(0, len(data), 12):
            chunk = data[i:i + 12]
            lines.append("    " + ", ".join(f"0x{byte:02X}" for byte in chunk) + ",")
        lines.append("};")
        lines.append("")
    return "\n".join(lines).rstrip() + ("\n" if lines else "")


def render_activation_description_lookup_inc(manifest: dict) -> str:
    lines = [
        "typedef struct {",
        "  u16 cardId;",
        "  const u8 *text;",
        "} CardActivationTextEntry;",
        "",
        "static const CardActivationTextEntry sCardActivationTextEntries[] APPEND_RODATA = {",
    ]
    for index, item in enumerate(manifest["cards"]):
        activation_description = item.get("activation_description")
        if not activation_description:
            continue
        lines.append(f"  {{ {item['card_const']}, {activation_description['symbol']} }},")
    lines.extend([
        "};",
        "",
        "static const u8 *GetCardActivationText(u16 cardId) {",
        "  u8 i;",
        "",
        "  for (i = 0; i < ARRAY_COUNT(sCardActivationTextEntries); i++)",
        "    if (sCardActivationTextEntries[i].cardId == cardId)",
        "      return sCardActivationTextEntries[i].text;",
        "",
        "  return NULL;",
        "}",
        "",
    ])
    return "\n".join(lines)


def render_trunk_inc(manifest: dict, enable_custom_cards_past_800: bool) -> str:
    custom_start = next((i for i, item in enumerate(manifest["cards"]) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"), len(manifest["cards"]))
    cards = [item["card_const"] for item in manifest["cards"][custom_start:]] if enable_custom_cards_past_800 else []
    lines = [
        "#include \"global.h\"",
        "",
        f"#define NUM_CUSTOM_TRUNK_CARDS {len(cards)}",
        "",
    ]
    if cards:
        lines.append("static const u16 gCustomTrunkCards[NUM_CUSTOM_TRUNK_CARDS] APPEND_RODATA = {")
        for card_const in cards:
            lines.append(f"  {card_const},")
        lines.append("};")
    else:
        lines.append("static const u16 gCustomTrunkCards[1] APPEND_RODATA = { CARD_NONE };")
    lines.append("")
    return "\n".join(lines)


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
        f"const u8 gCardLockAfterActivation_Hook[{len(manifest['cards'])}] APPEND_RODATA = {{",
    ]
    for index, item in enumerate(manifest["cards"]):
        lock_after_activation = item.get("lock_after_activation", True)
        lines.append(f"  [0x{index:04X}] = {1 if lock_after_activation else 0},")
    lines.append("};")
    lines.append("")
    lines.append(f"const CardData gCardData_NEW[{len(manifest['cards'])}] APPEND_RODATA = {{")
    lines.append("  [CARD_NONE] = {")
    lines.append("    .atk = 0xFFFF,")
    lines.append("    .def = 0xFFFF,")
    lines.append("    .cost = 0,")
    lines.append("    .attribute = 0,")
    lines.append("    .level = 0,")
    lines.append("    .type = 0,")
    lines.append("    .color = NORMAL_CARD,")
    lines.append("    .monsterEffect = 0,")
    lines.append("    .spellEffect = 0,")
    lines.append("    .trapEffect = 0,")
    lines.append("    .password = {15, 15, 15, 15, 15, 15, 15, 14},")
    lines.append("  },")
    for index, item in enumerate(manifest["cards"]):
        if item["card_const"] == "CARD_NONE":
            continue
        lines.append(f"  [0x{index:04X}] = {{")
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
    if path.exists() and path.read_text() == content:
        return
    path.write_text(content)


def sync_mini_exports() -> list[pathlib.Path]:
    EXPORT_DIR.mkdir(parents=True, exist_ok=True)
    exported = []
    for src in sorted(MINI_DIR.glob("*.png")):
        dst = EXPORT_DIR / src.name
        dst.write_bytes(src.read_bytes())
        exported.append(dst)
    return exported


def sync_missing_mini_assets(entries: list[CardArtEntry]) -> list[pathlib.Path]:
    exported = []
    for entry in entries:
        if entry.mini_art and entry.mini_art.exists():
            continue
        if not entry.big_art or not entry.big_pal:
            continue
        big_png = entry.big_art.with_suffix(".png")
        if not big_png.exists():
            continue
        base = MINI_DIR / f"{entry.stem}"
        mini_lz = build_mini_assets(big_png, entry.big_pal, base)
        entry.mini_art = mini_lz
        exported.append(mini_lz)
    return exported


def parse_card_colors() -> dict[int, int]:
    text = (ROOT / "src/data/cards_data.c").read_text()
    colors = {}
    for match in re.finditer(r"\[([A-Z0-9_]+)\]\s*=\s*([0-9]+)", text):
        name = match.group(1)
        value = int(match.group(2))
        colors[name] = value

    card_ids = (ROOT / "include/constants/card_ids.h").read_text()
    ids = {}
    for match in re.finditer(r"^#define\s+([A-Z0-9_]+)\s+0x([0-9A-F]+)$", card_ids, re.M):
        ids[match.group(1)] = int(match.group(2), 16)

    return {ids[name]: color for name, color in colors.items() if name in ids and ids[name] < 0x321}


def compose_mini_card(src: bytes, border: bytes) -> bytes:
    dest = bytearray()
    src_idx = 0

    for _ in range(16):
        dest.append(src[src_idx])
        src_idx += 1
    for i in range(6):
        for _ in range(4, 8):
            dest.append(src[src_idx])
            src_idx += 1
        border_idx = i * 8
        for j in range(4):
            dest.append(border[border_idx + j])
            src_idx += 1

    ip = 0
    r8 = 64
    for _ in range(16):
        dest.append(src[src_idx])
        src_idx += 1
    for i in range(6):
        border_idx = i * 8 + ip + 4
        for j in range(4, 8):
            dest.append(border[border_idx + (j - 4)])
            src_idx += 1
        border_idx = i * 8 + r8
        for j in range(4):
            dest.append(border[border_idx + j])
            src_idx += 1

    ip = 64
    r8 = 128
    for _ in range(16):
        dest.append(src[src_idx])
        src_idx += 1
    for i in range(6):
        border_idx = i * 8 + ip + 4
        for j in range(4, 8):
            dest.append(border[border_idx + (j - 4)])
            src_idx += 1
        border_idx = i * 8 + r8
        for j in range(4):
            dest.append(border[border_idx + j])
            src_idx += 1

    return bytes(dest)


def export_base_rom_minis() -> list[pathlib.Path]:
    colors_by_card = parse_card_colors()
    rom = BASE_ROM.read_bytes()
    ptr_base = 0x08E17F70 - 0x08000000
    border_base = 0x08E17F48 - 0x08000000
    pal_base = 0x089A781C - 0x08000000

    ptrs = [struct.unpack_from("<I", rom, ptr_base + i * 4)[0] for i in range(801)]
    borders = [rom[struct.unpack_from("<I", rom, border_base + i * 4)[0] - 0x08000000:struct.unpack_from("<I", rom, border_base + i * 4)[0] - 0x08000000 + 0x400] for i in range(6)]

    palette = rom[pal_base:pal_base + 32]
    palette_img = Image.new("P", (1, 1))
    palette_data = []
    for i in range(16):
        value = palette[i * 2] | (palette[i * 2 + 1] << 8)
        r = (value & 0x1F) * 255 // 31
        g = ((value >> 5) & 0x1F) * 255 // 31
        b = ((value >> 10) & 0x1F) * 255 // 31
        palette_data.extend([r, g, b])
    palette_img.putpalette(palette_data + [0, 0, 0] * (256 - 16))

    exported = []
    with tempfile.TemporaryDirectory(prefix="mini_export_") as tmp:
        tmpdir = pathlib.Path(tmp)
        for card_id, name in sorted((v, k) for k, v in ((k, v) for k, v in parse_card_colors().items())):
            pass

    return exported


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Generate card art and name hook includes from matching files in src/hooks/assets/cards."
    )
    parser.add_argument("--print", action="store_true", help="Print the generated content instead of writing files")
    parser.add_argument("--card-ids", action="store_true", help="Generate include/constants/card_ids.h from the manifest")
    parser.add_argument(
        "--generate-minis",
        action="store_true",
        help="Generate only missing 24x24 mini assets from existing 80x80 PNGs and palettes",
    )
    args = parser.parse_args()

    manifest = validate_manifest(json.loads(CUSTOM_CARD_MANIFEST.read_text()))

    if args.card_ids:
        enum_tables = load_effect_enums()
        for item in manifest["cards"]:
            for key in ("monsterEffect", "spellEffect", "trapEffect"):
                item[key] = resolve_effect_value(key, item[key], enum_tables)
        card_ids = render_card_ids_header(manifest)
        if args.print:
            print(card_ids, end="")
        else:
            update_file(CARD_IDS_H, card_ids)
        return 0

    if args.generate_minis:
        entries = discover_entries(manifest)
        generated_minis = sync_missing_mini_assets(entries)
        exported = sync_mini_exports()
        exported.extend(generated_minis)
        print(f"Generated {len(exported)} mini assets.")
        return 0

    enum_tables = load_effect_enums()
    for item in manifest["cards"]:
        for key in ("monsterEffect", "spellEffect", "trapEffect"):
            item[key] = resolve_effect_value(key, item[key], enum_tables)

    entries = discover_entries(manifest)
    generated_minis = sync_missing_mini_assets(entries)

    asset_inc = render_asset_inc(entries)
    name_inc = render_name_inc(manifest)
    data_inc = render_data_inc(entries)
    data_src = render_data_src(manifest)
    description_inc = render_description_inc(manifest)
    activation_description_inc = render_activation_description_inc(manifest)
    activation_description_lookup_inc = render_activation_description_lookup_inc(manifest)
    trunk_inc = render_trunk_inc(manifest, load_runtime_flag("enable_custom_cards_past_800"))

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
        print(f"--- {GENERATED_ACTIVATION_TEXT_INC} ---")
        print(activation_description_inc, end="")
        print(f"--- {GENERATED_ACTIVATION_TEXT_LOOKUP_INC} ---")
        print(activation_description_lookup_inc, end="")
        print(f"--- {GENERATED_TRUNK_INC} ---")
        print(trunk_inc, end="")
        return 0

    update_file(CARD_IDS_H, render_card_ids_header(manifest))
    update_file(GENERATED_ASSET_INC, asset_inc)
    update_file(GENERATED_NAME_INC, name_inc)
    update_file(GENERATED_DATA_INC, data_inc)
    update_file(GENERATED_DATA_SRC, data_src)
    update_file(ROOT / "src/hooks/card_description_data_generated.inc", description_inc)
    update_file(GENERATED_ACTIVATION_TEXT_INC, activation_description_inc)
    update_file(GENERATED_ACTIVATION_TEXT_LOOKUP_INC, activation_description_lookup_inc)
    update_file(GENERATED_TRUNK_INC, trunk_inc)
    exported = sync_mini_exports()
    exported.extend(generated_minis)
    print(f"Generated {len(entries)} card art bindings and exported {len(exported)} mini PNGs.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
