#!/usr/bin/env python3

import argparse
import json
import pathlib
import re
import struct
import subprocess
import sys
import tempfile
from PIL import Image
from dataclasses import dataclass

ROOT = pathlib.Path(__file__).resolve().parents[1]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from card_manifest import (  # noqa: E402
    ALLOWED_ENTRY_KEYS,
    ASSET_ENTRY_KEYS,
    ManifestValidationError,
    OPTIONAL_STATS_KEYS,
    REQUIRED_STATS_KEYS,
    effect_text_symbol,
    load_manifest_json,
    validate_manifest as _validate_manifest,
)
ASSET_ROOT = ROOT / "src_custom/assets/cards"
BIG_DIR = ASSET_ROOT / "80x80"
MINI_DIR = ASSET_ROOT / "24x24"
BIG_BUILD_DIR = ROOT / "build" / "cards" / "80x80"
MINI_BUILD_DIR = ROOT / "build" / "cards" / "24x24"
LEGACY_BIG_ASSET_DIR = "src_custom/assets/cards/80x80"
LEGACY_MINI_ASSET_DIR = "src_custom/assets/cards/24x24"
MINI_PAL = ASSET_ROOT / "mini.pal"
BASE_ROM = ROOT / "baserom.gba"
GENERATED_DIR = ROOT / "src_custom/generated"
GENERATED_ASSET_INC = GENERATED_DIR / "card_art_generated.inc"
GENERATED_NAME_INC = GENERATED_DIR / "card_name_generated.inc"
GENERATED_NAME_SORT_INC = GENERATED_DIR / "card_name_sort_generated.inc"
GENERATED_DATA_INC = GENERATED_DIR / "card_data_generated.inc"
GENERATED_DATA_SRC = GENERATED_DIR / "card_data_hooks.c"
GENERATED_TRUNK_INC = GENERATED_DIR / "card_trunk_generated.inc"
GENERATED_ACTIVATION_TEXT_INC = GENERATED_DIR / "card_activation_text_generated.inc"
GENERATED_ACTIVATION_TEXT_LOOKUP_INC = GENERATED_DIR / "card_activation_text_lookup_generated.inc"
GENERATED_EFFECT_TEXT_IDS_H = ROOT / "include/constants/card_effect_texts.h"
CARD_IDS_H = ROOT / "include/constants/card_ids.h"
CARD_COUNTS_H = ROOT / "include/constants/card_counts.h"
CARD_COUNTS_LD = ROOT / "generated/card_counts.ld"
CARD_MEMORY_SIZES_ASM = ROOT / "generated/card_memory_sizes.inc"
CUSTOM_CARD_MANIFEST = ROOT / "tools/card_data_manifest.json"
RUNTIME_CONFIG_C = ROOT / "configs/runtime.c"
EFFECT_ENUM_HEADERS = {
    "monsterEffect": ROOT / "include/constants/monster_effects.h",
    "spellEffect": ROOT / "include/constants/spell_effects.h",
    "customFieldSpell": ROOT / "include/constants/custom_field_spells.h",
}

GBAFX = ROOT / "tools/gbagfx/gbagfx"


def validate_manifest(manifest: object) -> dict:
    try:
        return _validate_manifest(manifest)
    except ManifestValidationError as exc:
        raise SystemExit(str(exc)) from exc

# Big card art palettes are traditionally 64 colors (4 banks). This repo can optionally
# extend big card art palettes to 112 colors (7 banks) for the card detail view.
BIG_PALETTE_COLORS_DEFAULT = 64
BIG_PALETTE_COLORS_EXTENDED = 112

# ponytail: vanilla ROM names for these stay "Amazon"; manifest uses "Amazoness" instead
VANILLA_AMAZON_NAME_OVERRIDE_SKIP = frozenset({
    "AMAZON_ARCHERS",
    "AMAZON_OF_THE_SEAS",
})


def manifest_custom_start(manifest: dict) -> int:
    return next(
        (i for i, item in enumerate(manifest["cards"]) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"),
        len(manifest["cards"]),
    )


def manifest_name_hook_entries(manifest: dict) -> list[tuple[int, dict]]:
    custom_start = manifest_custom_start(manifest)
    entries: list[tuple[int, dict]] = []
    for index, item in enumerate(manifest["cards"][:custom_start]):
        if item["card_const"].startswith("AMAZON") and item["card_const"] not in VANILLA_AMAZON_NAME_OVERRIDE_SKIP:
            entries.append((index, item))
    for index, item in enumerate(manifest["cards"][custom_start:], start=custom_start):
        entries.append((index, item))
    return entries


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
    big_art_colors_used: int = 0


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


def remap_legacy_asset_path(path: pathlib.Path) -> pathlib.Path:
    resolved = path if path.is_absolute() else ROOT / path
    rel = resolved.relative_to(ROOT).as_posix()
    name = resolved.name
    if rel.startswith(f"{LEGACY_BIG_ASSET_DIR}/") and name.endswith((".huff", ".gbapal")):
        return BIG_BUILD_DIR / name
    if rel.startswith(f"{LEGACY_MINI_ASSET_DIR}/") and name.endswith(".lz"):
        return MINI_BUILD_DIR / name
    return resolved


def run_gbagfx(input_path: pathlib.Path, output_path: pathlib.Path, *extra: str) -> None:
    subprocess.run([str(GBAFX), str(input_path), str(output_path), *extra], check=True, cwd=ROOT)


def pad_gba_palette(path: pathlib.Path, target_colors: int) -> None:
    """Pad a GBA palette file (RGB555 little-endian) to exactly target_colors entries.
    Extra entries are filled with black (0x0000).
    """
    data = path.read_bytes()
    expected_bytes = target_colors * 2
    if len(data) >= expected_bytes:
        return
    # Pad with zeros (GBA color 0x0000 = black)
    padding = bytes(expected_bytes - len(data))
    path.write_bytes(data + padding)


def build_big_art_from_png(png_path: pathlib.Path) -> tuple[pathlib.Path, pathlib.Path]:
    BIG_BUILD_DIR.mkdir(parents=True, exist_ok=True)
    stem = png_path.stem
    huff_path = BIG_BUILD_DIR / f"{stem}.huff"
    palette_path = BIG_BUILD_DIR / f"{stem}.gbapal"

    run_gbagfx(png_path, palette_path)

    # Determine the target palette size based on how many colors the art actually uses.
    # The PNG may have fewer PLTE entries than the GBA expects (e.g. Photoshop strips
    # unused entries). Pad to avoid the game reading garbage past the end of the file.
    colors_used = count_colors_used_in_big_art(png_path)
    target = BIG_PALETTE_COLORS_EXTENDED if colors_used > BIG_PALETTE_COLORS_DEFAULT else BIG_PALETTE_COLORS_DEFAULT
    pad_gba_palette(palette_path, target)

    with tempfile.NamedTemporaryFile(suffix=".8bpp", delete=False) as tmp:
        tmp_8bpp = pathlib.Path(tmp.name)
    try:
        run_gbagfx(png_path, tmp_8bpp)
        run_gbagfx(tmp_8bpp, huff_path, "-depth", "8", "-ygodm")
    finally:
        tmp_8bpp.unlink(missing_ok=True)

    return huff_path, palette_path


def build_mini_lz_from_png(mini_png: pathlib.Path) -> pathlib.Path:
    MINI_BUILD_DIR.mkdir(parents=True, exist_ok=True)
    mini_lz = MINI_BUILD_DIR / f"{mini_png.stem}.lz"
    with tempfile.NamedTemporaryFile(suffix=".8bpp", delete=False) as tmp:
        tmp_8bpp = pathlib.Path(tmp.name)
    try:
        run_gbagfx(mini_png, tmp_8bpp)
        run_gbagfx(tmp_8bpp, mini_lz)
    finally:
        tmp_8bpp.unlink(missing_ok=True)
    return mini_lz


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


def count_colors_used_in_big_art(png_path: pathlib.Path) -> int:
    """Count distinct palette indices used in 80x80 big art (index 0 excluded as transparent)."""
    if not png_path.exists():
        return 0

    image = Image.open(png_path).convert("P")
    used = set(image.get_flattened_data())
    used.discard(0)
    return len(used)


def validate_big_palette(path: pathlib.Path) -> int:
    """
    Validate that a big card palette is in a supported format.

    We allow both the vanilla-sized 64-color palette (128 bytes) and the extended
    112-color palette (224 bytes).
    """
    data = path.read_bytes()
    if len(data) % 2 != 0:
        raise SystemExit(f"Palette file must contain an even number of bytes: {path}")

    colors = len(data) // 2
    if colors not in (BIG_PALETTE_COLORS_DEFAULT, BIG_PALETTE_COLORS_EXTENDED):
        raise SystemExit(
            f"Unsupported big palette size in {path}: {colors} colors "
            f"(expected {BIG_PALETTE_COLORS_DEFAULT} or {BIG_PALETTE_COLORS_EXTENDED})."
        )
    return colors


def load_jasc_palette(path: pathlib.Path) -> list[tuple[int, int, int]]:
    lines = path.read_text().splitlines()
    if len(lines) < 3 or lines[0].strip() != "JASC-PAL" or lines[1].strip() != "0100":
        raise SystemExit(f"Invalid JASC palette file: {path}")
    try:
        count = int(lines[2].strip())
    except ValueError as exc:
        raise SystemExit(f"Invalid palette color count in {path}") from exc
    if count < 1 or len(lines) < 3 + count:
        raise SystemExit(f"Palette file does not contain {count} colors: {path}")

    colors: list[tuple[int, int, int]] = []
    for line in lines[3 : 3 + count]:
        parts = line.split()
        if len(parts) != 3:
            raise SystemExit(f"Invalid palette line in {path}: {line}")
        try:
            r, g, b = (int(part) for part in parts)
        except ValueError as exc:
            raise SystemExit(f"Invalid palette color in {path}: {line}") from exc
        colors.append((r, g, b))
    return colors


def color_distance_sq(left: tuple[int, int, int], right: tuple[int, int, int]) -> int:
    return sum((l - r) * (l - r) for l, r in zip(left, right))


def select_mini_palette(
    big_palette: list[tuple[int, int, int]],
    master_palette: list[tuple[int, int, int]],
    count: int = 16,
) -> list[tuple[int, int, int]]:
    if not master_palette:
        raise SystemExit(f"{MINI_PAL} does not contain any colors.")

    source_palette = big_palette[:64] if len(big_palette) > 64 else big_palette
    if not source_palette:
        raise SystemExit("Mini palette selection needs at least one source color.")

    target_count = min(count, len(master_palette))
    selected_indices: list[int] = []
    selected_set: set[int] = set()
    best_distances = [None] * len(source_palette)

    def score_candidate(index: int) -> int:
        candidate = master_palette[index]
        return sum(color_distance_sq(candidate, source) for source in source_palette)

    def update_best_distances(index: int) -> None:
        candidate = master_palette[index]
        for source_index, source in enumerate(source_palette):
            distance = color_distance_sq(candidate, source)
            current = best_distances[source_index]
            if current is None or distance < current:
                best_distances[source_index] = distance

    first_index = min(range(len(master_palette)), key=score_candidate)
    selected_indices.append(first_index)
    selected_set.add(first_index)
    update_best_distances(first_index)

    while len(selected_indices) < target_count:
        best_index = None
        best_score = None
        for index in range(len(master_palette)):
            if index in selected_set:
                continue
            candidate = master_palette[index]
            score = 0
            for source_index, source in enumerate(source_palette):
                current = best_distances[source_index]
                candidate_distance = color_distance_sq(candidate, source)
                score += candidate_distance if current is None or candidate_distance < current else current
            if best_score is None or score < best_score:
                best_score = score
                best_index = index

        if best_index is None:
            break

        selected_indices.append(best_index)
        selected_set.add(best_index)
        update_best_distances(best_index)

    return [master_palette[index] for index in selected_indices]


def make_paletted_mini(big_png: pathlib.Path, big_palette: pathlib.Path, mini_png: pathlib.Path) -> None:
    image = Image.open(big_png).convert("RGBA")
    image = image.resize((24, 24), Image.Resampling.LANCZOS).convert("RGBA")

    palette = load_jasc_palette(MINI_PAL)
    pal_img = Image.new("P", (1, 1))
    palette_data = []
    for r, g, b in palette:
        palette_data.extend([r, g, b])
    palette_data.extend([0, 0, 0] * (256 - len(palette_data) // 3))
    pal_img.putpalette(palette_data)

    quantized = image.convert("RGB").quantize(palette=pal_img, dither=Image.Dither.NONE)

    # Remap any pixel with index >= 160 (padded black entries) to index 159
    # (the darkest real color in mini.pal). CopyMiniCardPalette only loads
    # indices 0-159, so entries 160+ would read garbage at runtime.
    lut = list(range(160)) + [159] * (256 - 160)
    quantized = quantized.point(lut)

    # Trunk/shop force palette slot 0 to 0x0000 (transparent). Remap opaque art
    # pixels off index 0 using the pre-quantize RGB (ponytail: index 1 fallback).
    rgb_px = image.convert("RGB").load()
    mini_px = quantized.load()
    for y in range(24):
        for x in range(24):
            if mini_px[x, y] != 0:
                continue
            r, g, b = rgb_px[x, y]
            best_index = 1
            best_distance = float("inf")
            for index in range(1, 160):
                pr, pg, pb = palette[index]
                distance = (r - pr) ** 2 + (g - pg) ** 2 + (b - pb) ** 2
                if distance < best_distance:
                    best_distance = distance
                    best_index = index
            mini_px[x, y] = best_index

    mini_png.parent.mkdir(parents=True, exist_ok=True)
    quantized.save(mini_png)


def build_mini_assets(big_png: pathlib.Path, big_palette: pathlib.Path, stem: str) -> pathlib.Path:
    MINI_BUILD_DIR.mkdir(parents=True, exist_ok=True)
    mini_lz = MINI_BUILD_DIR / f"{stem}.lz"

    with tempfile.TemporaryDirectory(prefix="mini_build_") as tmp:
        tmpdir = pathlib.Path(tmp)
        mini_png = tmpdir / f"{stem}.png"
        mini_8bpp = tmpdir / f"{stem}.8bpp"
        make_paletted_mini(big_png, big_palette, mini_png)
        run_gbagfx(mini_png, mini_8bpp)
        run_gbagfx(mini_8bpp, mini_lz)

    return mini_lz


def ensure_custom_card_assets(manifest: dict, force_minis: bool = False) -> list[pathlib.Path]:
    custom_start = next(
        (i for i, item in enumerate(manifest["cards"]) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"),
        len(manifest["cards"]),
    )
    built_minis: list[pathlib.Path] = []
    for index, item in enumerate(manifest["cards"]):
        if index < custom_start:
            big_png = BIG_DIR / f"{item['card_const'].lower()}.png"
            if not big_png.exists():
                continue
        stem = item["card_const"].lower()
        big_png = BIG_DIR / f"{stem}.png"
        mini_png = MINI_DIR / f"{stem}.png"
        mini_lz = MINI_BUILD_DIR / f"{stem}.lz"

        if big_png.exists():
            build_big_art_from_png(big_png)

        if mini_png.exists():
            built_minis.append(build_mini_lz_from_png(mini_png))
            continue

        if not big_png.exists():
            continue

        palette_path = BIG_BUILD_DIR / f"{stem}.gbapal"
        if not palette_path.exists():
            continue
        if not force_minis and mini_lz.exists():
            continue
        built_minis.append(build_mini_assets(big_png, palette_path, stem))

    return built_minis


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
    return parse_enum_header_text(path.read_text())


def parse_enum_header_text(text: str) -> dict[str, int]:
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
        if c == "#":
            end = text.find("\n", i)
            i = end if end >= 0 else len(text)
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
        if not header_path.exists():
            continue
        if key == "customFieldSpell":
            text = header_path.read_text()
            generated_path = ROOT / "include/constants/custom_field_spells_generated.h"
            if generated_path.is_file():
                generated = generated_path.read_text()
                text = text.replace('#include "constants/custom_field_spells_generated.h"', generated)
            result[key] = parse_enum_header_text(text)
            continue
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


def render_card_ids_header(manifest: dict) -> str:
    cards = manifest["cards"]
    custom_start = next((i for i, item in enumerate(cards) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"), len(cards))
    total_cards = len(cards)
    custom_cards = max(0, total_cards - custom_start)
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
        f"#define NUM_TOTAL_CARDS                         0x{total_cards:04X}",
        f"#define NUM_CUSTOM_CARDS                        0x{custom_cards:04X}",
    ])
    lines.extend([
        "",
        "#endif // GUARD_CONSTANTS_CARD_IDS_H",
        "",
    ])
    return "\n".join(lines)


def render_card_counts_ld(manifest: dict) -> str:
    cards = manifest["cards"]
    custom_start = next((i for i, item in enumerate(cards) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"), len(cards))
    total_cards = len(cards)
    custom_cards = max(0, total_cards - custom_start)
    return "\n".join(
        [
            f"NUM_TOTAL_CARDS = 0x{total_cards:04X};",
            f"NUM_CUSTOM_CARDS = 0x{custom_cards:04X};",
            "",
        ]
    )


def render_card_counts_header(manifest: dict) -> str:
    cards = manifest["cards"]
    custom_start = next((i for i, item in enumerate(cards) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"), len(cards))
    total_cards = len(cards)
    custom_cards = max(0, total_cards - custom_start)
    custom_card_qty_bytes = max(custom_cards, 0x200)  # Keep in sync with render_card_memory_sizes_asm.
    return "\n".join(
        [
            "#ifndef GUARD_CONSTANTS_CARD_COUNTS_H",
            "#define GUARD_CONSTANTS_CARD_COUNTS_H",
            "",
            f"#define NUM_TOTAL_CARDS                         0x{total_cards:04X}",
            f"#define NUM_CUSTOM_CARDS                        0x{custom_cards:04X}",
            f"#define CUSTOM_CARD_QTY_BYTES                   0x{custom_card_qty_bytes:04X}",
            "",
            "#endif // GUARD_CONSTANTS_CARD_COUNTS_H",
            "",
        ]
    )


def render_card_memory_sizes_asm(manifest: dict) -> str:
    cards = manifest["cards"]
    custom_start = next((i for i, item in enumerate(cards) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"), len(cards))
    total_cards = len(cards)
    custom_cards = max(0, total_cards - custom_start)
    custom_card_qty_bytes = max(custom_cards, 0x200)  # Keep in sync with render_card_counts_header.
    trunk_custom_card_bytes = custom_cards * 2
    trunk_sort_list_bytes = (custom_start + custom_cards) * 2
    shop_rows = (total_cards + 6) // 7
    shop_list_entries = shop_rows * 7 + 1
    shop_list_bytes = shop_list_entries * 2
    card_cost_table_bytes = total_cards * 2
    return "\n".join(
        [
            "@ Generated by tools/add_card_art.py. Do not edit by hand.",
            f".equ CARD_COST_TABLE_BYTES, 0x{card_cost_table_bytes:04X}",
            f".equ CUSTOM_CARD_QTY_BYTES, 0x{custom_card_qty_bytes:04X}",
            f".equ TRUNK_MENU_CUSTOM_CARD_BYTES, 0x{trunk_custom_card_bytes:04X}",
            f".equ TRUNK_MENU_SORT_LIST_BYTES, 0x{trunk_sort_list_bytes:04X}",
            f".equ CUSTOM_SHOP_CARD_ROWS, 0x{shop_rows:04X}",
            f".equ CUSTOM_SHOP_CARD_LIST_ENTRIES, 0x{shop_list_entries:04X}",
            f".equ CUSTOM_SHOP_CARD_LIST_BYTES, 0x{shop_list_bytes:04X}",
            "",
        ]
    )


def discover_entries(manifest: dict) -> list[CardArtEntry]:
    enum_tables = load_effect_enums()
    entries = []
    custom_start = next((i for i, item in enumerate(manifest["cards"]) if item["card_const"] == "SORCERER_OF_DARK_MAGIC"), len(manifest["cards"]))
    for index, item in enumerate(manifest["cards"]):
        if index < custom_start:
            stem = item["card_const"].lower()
            if not (BIG_DIR / f"{stem}.png").exists():
                continue
        for key in ("monsterEffect", "spellEffect", "trapEffect"):
            item[key] = resolve_effect_value(key, item[key], enum_tables)
        stem = item["card_const"].lower()
        big_png = BIG_DIR / f"{stem}.png"
        big_art = remap_legacy_asset_path(
            manifest_asset_path(item.get("big_art", ""), f"build/cards/80x80/{stem}.huff")
        )
        big_pal = remap_legacy_asset_path(
            manifest_asset_path(item.get("big_palette", ""), f"build/cards/80x80/{stem}.gbapal")
        )
        mini_art = remap_legacy_asset_path(
            manifest_asset_path(item.get("mini_art", ""), f"build/cards/24x24/{stem}.lz")
        )

        big_art_colors_used = 0
        if big_png.exists():
            big_art_colors_used = count_colors_used_in_big_art(big_png)

        if big_pal.exists():
            palette_colors = validate_big_palette(big_pal)
            if big_art_colors_used > BIG_PALETTE_COLORS_DEFAULT and palette_colors < BIG_PALETTE_COLORS_EXTENDED:
                raise SystemExit(
                    f"{big_pal}: art uses {big_art_colors_used} colors but palette only has "
                    f"{palette_colors} entries; export a {BIG_PALETTE_COLORS_EXTENDED}-color .gbapal."
                )

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
                big_art_colors_used=big_art_colors_used,
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
    lines.append("const u8 gCardArtUsesExtendedPalette_Hook[] APPEND_RODATA = {")
    for entry in entries:
        if entry.big_art and entry.big_pal:
            uses_extended = 1 if entry.big_art_colors_used > BIG_PALETTE_COLORS_DEFAULT else 0
            lines.append(f"  [0x{entry.index:04X}] = {uses_extended},")
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
    lines = []
    for index, item in manifest_name_hook_entries(manifest):
        name_symbol = to_symbol(item["card_const"].lower(), "Name")
        lines.append(f'static const u8 {name_symbol}[] __attribute__((section(".append_assets"))) = "{item["card_name"]}";')
    lines.append("")
    lines.append("static u8 *GetCardName_Hook(unsigned short cardId) {")
    for index, item in manifest_name_hook_entries(manifest):
        name_symbol = to_symbol(item["card_const"].lower(), "Name")
        lines.append(f"  if (cardId == 0x{index:04X})")
        lines.append(f"    return (u8 *){name_symbol};")
    lines.append("")
    lines.append("  return gCardNames[cardId];")
    lines.append("}")
    lines.append("")
    return "\n".join(lines)


def render_name_sort_inc(manifest: dict) -> str:
    custom_start = manifest_custom_start(manifest)
    custom_cards = [
        (index, item["card_name"], item["card_const"])
        for index, item in enumerate(manifest["cards"][custom_start:], start=custom_start)
    ]
    custom_cards.sort(key=lambda entry: (entry[1].upper(), entry[0]))

    lines = [
        "#include \"global.h\"",
        "",
        f"#define NUM_CUSTOM_NAME_SORT_CARDS {len(custom_cards)}",
        "",
    ]

    for index, item in manifest_name_hook_entries(manifest):
        name_symbol = to_symbol(item["card_const"].lower(), "SortName")
        lines.append(f'static const u8 {name_symbol}[] APPEND_RODATA = "{item["card_name"]}";')
    lines.append("")

    if custom_cards:
        lines.append("static const u16 sCustomCardsByName[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {")
        for card_id, card_name, _card_const in custom_cards:
            lines.append(f"  0x{card_id:04X}, // {card_name}")
        lines.append("};")
        lines.append("")
        lines.append("static const u16 sCustomCardNameSortOrder[NUM_CUSTOM_NAME_SORT_CARDS] APPEND_RODATA = {")
        for sort_index, (card_id, card_name, _card_const) in enumerate(custom_cards, start=1):
            lines.append(f"  {sort_index}, // {card_name}")
        lines.append("};")
        lines.append("")

    lines.extend([
        "static u8 *GetSortCardName(u16 cardId) {",
    ])
    for index, item in manifest_name_hook_entries(manifest):
        name_symbol = to_symbol(item["card_const"].lower(), "SortName")
        lines.append(f"  if (cardId == 0x{index:04X})")
        lines.append(f"    return (u8 *){name_symbol};")
    lines.extend([
        "",
        "  return gCardNames[cardId];",
        "}",
        "",
        "static u16 GetCustomCardNameSortOrder(u16 cardId) {",
        "  u16 i;",
        "",
        "  for (i = 0; i < NUM_CUSTOM_NAME_SORT_CARDS; i++)",
        "    if (sCustomCardsByName[i] == cardId)",
        "      return sCustomCardNameSortOrder[i];",
        "",
        "  return 0;",
        "}",
        "",
    ])
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


def _append_activation_text_symbol(lines: list[str], symbol: str, pages: list[str]) -> None:
    # Always lead with "CARD was activated." then card-specific pages.
    payload = [wrap_activation_page("#2\nwas activated."), "#1"]
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


def render_activation_description_inc(manifest: dict) -> str:
    lines = []
    for item in manifest["cards"]:
        activation_description = item.get("activation_description")
        if activation_description:
            _append_activation_text_symbol(
                lines, activation_description["symbol"], activation_description["pages"]
            )
        effect_texts = item.get("effect_texts") or {}
        for effect_id, effect in effect_texts.items():
            symbol = effect.get("symbol") or effect_text_symbol(item["card_const"], effect_id)
            _append_activation_text_symbol(lines, symbol, effect["pages"])
    return "\n".join(lines).rstrip() + ("\n" if lines else "")


def iter_effect_text_entries(manifest: dict):
    for item in manifest["cards"]:
        effect_texts = item.get("effect_texts") or {}
        for effect_id, effect in effect_texts.items():
            symbol = effect.get("symbol") or effect_text_symbol(item["card_const"], effect_id)
            enum_name = f"CARD_EFFECT_TEXT_{item['card_const']}_{effect_id.upper()}"
            yield item["card_const"], effect_id, symbol, enum_name


def render_effect_text_ids_header(manifest: dict) -> str:
    lines = [
        "#ifndef GUARD_CARD_EFFECT_TEXTS_H",
        "#define GUARD_CARD_EFFECT_TEXTS_H",
        "",
        "/* Generated from manifest effect_texts — do not edit. */",
        "",
        "enum CardEffectTextId {",
        "  CARD_EFFECT_TEXT_NONE = 0,",
    ]
    for _card, _effect_id, _symbol, enum_name in iter_effect_text_entries(manifest):
        lines.append(f"  {enum_name},")
    lines.extend(
        [
            "  NUM_CARD_EFFECT_TEXTS",
            "};",
            "",
            "const u8 *GetCardEffectText(u16 effectTextId);",
            "",
            "#endif /* GUARD_CARD_EFFECT_TEXTS_H */",
            "",
        ]
    )
    return "\n".join(lines)


def render_effect_text_lookup_inc(manifest: dict) -> str:
    """Appended into activation-text lookup include (compiled in effect_text_hooks.c)."""
    lines = [
        "static const u8 *const sCardEffectTextById[NUM_CARD_EFFECT_TEXTS] APPEND_RODATA = {",
        "  [CARD_EFFECT_TEXT_NONE] = NULL,",
    ]
    for _card, _effect_id, symbol, enum_name in iter_effect_text_entries(manifest):
        lines.append(f"  [{enum_name}] = {symbol},")
    lines.extend(
        [
            "};",
            "",
            "const u8 *GetCardEffectText(u16 effectTextId)",
            "{",
            "  if (effectTextId >= NUM_CARD_EFFECT_TEXTS)",
            "    return NULL;",
            "",
            "  return sCardEffectTextById[effectTextId];",
            "}",
            "",
        ]
    )
    return "\n".join(lines)


def render_activation_description_lookup_inc(manifest: dict) -> str:
    lines = [
        "#include \"constants/card_effect_texts.h\"",
        "",
        "static const u8 *const sCardActivationTextById[NUM_TOTAL_CARDS] APPEND_RODATA = {",
    ]
    for item in manifest["cards"]:
        activation_description = item.get("activation_description")
        if not activation_description:
            continue
        lines.append(
            f"  [{item['card_const']}] = {activation_description['symbol']},"
        )
    lines.extend([
        "};",
        "",
        "static const u8 *GetCardActivationText(u16 cardId) {",
        "  if (cardId >= NUM_TOTAL_CARDS)",
        "    return NULL;",
        "",
        "  return sCardActivationTextById[cardId];",
        "}",
        "",
    ])
    lines.append(render_effect_text_lookup_inc(manifest).rstrip())
    lines.append("")
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


def effect_usage_for_item(item: dict) -> str:
    manifest_to_c = {
        "once": "EFFECT_USAGE_ONCE",
        "once_per_turn": "EFFECT_USAGE_ONCE_PER_TURN",
        "multiple_per_turn": "EFFECT_USAGE_MULTIPLE_PER_TURN",
        "continuous": "EFFECT_USAGE_CONTINUOUS",
    }
    raw = item.get("effect_usage")
    if raw is not None:
        return manifest_to_c[raw]

    monster_effect = item.get("monsterEffect", 0)
    if monster_effect in (0, "MONSTER_EFFECT_NONE", "0"):
        return "EFFECT_USAGE_NONE"
    return "EFFECT_USAGE_ONCE_PER_TURN"


def render_data_src(manifest: dict) -> str:
    lines = [
        '#include "global.h"',
        '#include "common-chax.h"',
        '#include "constants/card_descriptions.h"',
        '#include "constants/effect_usage.h"',
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
    lines.append(f"const u8 gCardEffectUsage_Hook[{len(manifest['cards'])}] APPEND_RODATA = {{")
    for index, item in enumerate(manifest["cards"]):
        lines.append(f"  [0x{index:04X}] = {effect_usage_for_item(item)},")
    lines.append("};")
    lines.append("")

    lines.append(f"const u8 gCardSelectableOnce_Hook[{len(manifest['cards'])}] APPEND_RODATA = {{")
    for index, item in enumerate(manifest["cards"]):
        selectable_once = item.get("selectableOnce", False)
        lines.append(f"  [0x{index:04X}] = {1 if selectable_once else 0},")
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
        description="Generate card art and name hook includes from matching files in src_custom/assets/cards."
    )
    parser.add_argument("--print", action="store_true", help="Print the generated content instead of writing files")
    parser.add_argument("--card-ids", action="store_true", help="Generate include/constants/card_ids.h from the manifest")
    parser.add_argument(
        "--generate-minis",
        action="store_true",
        help="Generate only missing 24x24 mini assets from existing 80x80 PNGs and palettes",
    )
    parser.add_argument(
        "--skip-art",
        action="store_true",
        help="Regenerate manifest-driven includes without converting card PNGs",
    )
    parser.add_argument(
        "--art-only",
        action="store_true",
        help="Convert card PNGs in 80x80/24x24 and refresh card_art_generated.inc only",
    )
    args = parser.parse_args()

    if args.skip_art and args.art_only:
        raise SystemExit("Cannot use --skip-art with --art-only.")

    manifest = validate_manifest(load_manifest_json(CUSTOM_CARD_MANIFEST))

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
            update_file(CARD_COUNTS_H, render_card_counts_header(manifest))
            update_file(CARD_COUNTS_LD, render_card_counts_ld(manifest))
            update_file(CARD_MEMORY_SIZES_ASM, render_card_memory_sizes_asm(manifest))
        return 0

    if args.generate_minis:
        built_minis = ensure_custom_card_assets(manifest, force_minis=True)
        print(f"Generated {len(built_minis)} mini assets.")
        return 0

    if args.art_only:
        built_minis = ensure_custom_card_assets(manifest)
        entries = discover_entries(manifest)
        asset_inc = render_asset_inc(entries)
        if args.print:
            print(f"--- {GENERATED_ASSET_INC} ---")
            print(asset_inc, end="")
        else:
            update_file(GENERATED_ASSET_INC, asset_inc)
            print(
                f"Built {len(built_minis)} mini assets and refreshed art bindings for {len(entries)} cards."
            )
        return 0

    enum_tables = load_effect_enums()
    custom_field_spell_names = set(enum_tables.get("customFieldSpell", {}).keys())
    for item in manifest["cards"]:
        for key in ("monsterEffect", "spellEffect", "trapEffect"):
            item[key] = resolve_effect_value(key, item[key], enum_tables)
        custom_field_spell = item.get("customFieldSpell")
        if custom_field_spell is not None:
            if custom_field_spell not in custom_field_spell_names:
                raise SystemExit(
                    f"cards[{item['card_const']}].customFieldSpell references unknown enum {custom_field_spell!r}."
                )
            if custom_field_spell == "CUSTOM_FIELD_SPELL_NONE":
                raise SystemExit(
                    f"cards[{item['card_const']}].customFieldSpell must not be CUSTOM_FIELD_SPELL_NONE."
                )

    if args.skip_art:
        built_minis = []
    else:
        built_minis = ensure_custom_card_assets(manifest)
    entries = discover_entries(manifest)

    asset_inc = render_asset_inc(entries)
    name_inc = render_name_inc(manifest)
    name_sort_inc = render_name_sort_inc(manifest)
    data_inc = render_data_inc(entries)
    data_src = render_data_src(manifest)
    description_inc = render_description_inc(manifest)
    activation_description_inc = render_activation_description_inc(manifest)
    activation_description_lookup_inc = render_activation_description_lookup_inc(manifest)
    effect_text_ids_h = render_effect_text_ids_header(manifest)
    trunk_inc = render_trunk_inc(manifest, load_runtime_flag("enable_custom_cards_past_800"))

    if args.print:
        print(f"--- {CARD_IDS_H} ---")
        print(render_card_ids_header(manifest), end="")
        print(f"--- {GENERATED_ASSET_INC} ---")
        print(asset_inc, end="")
        print(f"--- {GENERATED_NAME_INC} ---")
        print(name_inc, end="")
        print(f"--- {GENERATED_NAME_SORT_INC} ---")
        print(name_sort_inc, end="")
        print(f"--- {GENERATED_DATA_INC} ---")
        print(data_inc, end="")
        print(f"--- {GENERATED_DATA_SRC} ---")
        print(data_src, end="")
        print(f"--- src_custom/card_description_data_generated.inc ---")
        print(description_inc, end="")
        print(f"--- {GENERATED_ACTIVATION_TEXT_INC} ---")
        print(activation_description_inc, end="")
        print(f"--- {GENERATED_ACTIVATION_TEXT_LOOKUP_INC} ---")
        print(activation_description_lookup_inc, end="")
        print(f"--- {GENERATED_EFFECT_TEXT_IDS_H} ---")
        print(effect_text_ids_h, end="")
        print(f"--- {GENERATED_TRUNK_INC} ---")
        print(trunk_inc, end="")
        return 0

    update_file(CARD_IDS_H, render_card_ids_header(manifest))
    update_file(CARD_COUNTS_H, render_card_counts_header(manifest))
    update_file(CARD_COUNTS_LD, render_card_counts_ld(manifest))
    update_file(CARD_MEMORY_SIZES_ASM, render_card_memory_sizes_asm(manifest))
    update_file(GENERATED_ASSET_INC, asset_inc)
    update_file(GENERATED_NAME_INC, name_inc)
    update_file(GENERATED_NAME_SORT_INC, name_sort_inc)
    update_file(GENERATED_DATA_INC, data_inc)
    update_file(GENERATED_DATA_SRC, data_src)
    update_file(ROOT / "src_custom/card_description_data_generated.inc", description_inc)
    update_file(GENERATED_ACTIVATION_TEXT_INC, activation_description_inc)
    update_file(GENERATED_ACTIVATION_TEXT_LOOKUP_INC, activation_description_lookup_inc)
    update_file(GENERATED_EFFECT_TEXT_IDS_H, effect_text_ids_h)
    update_file(GENERATED_TRUNK_INC, trunk_inc)
    print(f"Generated {len(entries)} card art bindings and built {len(built_minis)} mini assets.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
