#!/usr/bin/env python3
"""Build custom duel field spell graphics and generated registration headers."""

from __future__ import annotations

import argparse
import re
import struct
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
ASSET_ROOT = ROOT / "src_custom/assets/field_spells"
TABLE_INC = ROOT / "src_custom/field_spell_table.inc"
GBAFX = ROOT / "tools/gbagfx/gbagfx"
GENERATED_DIR = ROOT / "src_custom/generated"
GFX_GENERATED_INC = GENERATED_DIR / "field_spell_gfx_generated.inc"
TILEMAPS_GENERATED_INC = GENERATED_DIR / "field_spell_tilemaps_generated.inc"
CUSTOM_FIELD_SPELLS_GENERATED_H = ROOT / "include/constants/custom_field_spells_generated.h"
CUSTOM_FIELDS_GENERATED_H = ROOT / "include/constants/custom_fields_generated.h"
CARD_LOOKUP_GENERATED_INC = GENERATED_DIR / "field_spell_card_lookup_generated.inc"
GFX_TABLES_GENERATED_INC = GENERATED_DIR / "field_spell_gfx_tables_generated.inc"
EFFECT_TABLE_GENERATED_INC = GENERATED_DIR / "field_spell_effect_table_generated.inc"
STAT_MODS_GENERATED_INC = GENERATED_DIR / "field_spell_stat_mods_generated.inc"
MAPPING_GENERATED_INC = GENERATED_DIR / "field_spell_mapping_generated.inc"

FIELD_PNG_WIDTH = 248
FIELD_PNG_HEIGHT = 304
FIELD_TILEMAP_ROWS = 38
FIELD_TILEMAP_COLS = 31
FIELD_TILE_COUNT = FIELD_TILEMAP_ROWS * FIELD_TILEMAP_COLS
FIELD_MAX_COLORS = 48
FIELD_PALETTE_BYTES = 96
FIELD_MAX_UNIQUE_TILES = 1024
FIELD_MAX_TILESET_BYTES = 0x8000
FIELD_BPP_TILE_BYTES = 32
FIELD_PALETTE_BANK_SIZE = 16
FIELD_PALETTE_BANK_COUNT = FIELD_MAX_COLORS // FIELD_PALETTE_BANK_SIZE
FIELD_BPP_PATH_SUFFIX = ".4bpp"

TABLE_ENTRY_RE = re.compile(
    r"^\s*_\(\s*"
    r"(?P<spell_id>[A-Z0-9_]+)\s*,\s*"
    r"(?P<field_id>[A-Z0-9_]+)\s*,\s*"
    r"(?P<card_const>[A-Z0-9_]+)\s*,\s*"
    r"(?P<effect_fn>[A-Za-z0-9_]+)\s*"
    r"\)\s*\\?\s*$"
)


@dataclass
class FieldSpellEntry:
    spell_id: str
    field_id: str
    card_const: str
    effect_fn: str
    stem: str
    asset_dir: Path


def card_const_to_stem(card_const: str) -> str:
    return card_const.lower()


def tile_symbol(field_id: str, suffix: str) -> str:
    body = field_id.removeprefix("FIELD_").removeprefix("CUSTOM_")
    parts = [part for part in re.split(r"[^A-Za-z0-9]+", body) if part]
    return "gField" + "".join(part[:1].upper() + part[1:] for part in parts) + suffix


def parse_field_spell_table(path: Path) -> list[FieldSpellEntry]:
    entries: list[FieldSpellEntry] = []
    for line in path.read_text().splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("//") or stripped.startswith("/*") or stripped.startswith("*"):
            continue
        match = TABLE_ENTRY_RE.match(line)
        if not match:
            continue
        card_const = match.group("card_const")
        entries.append(
            FieldSpellEntry(
                spell_id=match.group("spell_id"),
                field_id=match.group("field_id"),
                card_const=card_const,
                effect_fn=match.group("effect_fn"),
                stem=card_const_to_stem(card_const),
                asset_dir=ASSET_ROOT / card_const_to_stem(card_const),
            )
        )
    return entries


def run_gbagfx(src: Path, dst: Path, *extra: str) -> None:
    cmd = [str(GBAFX), str(src), str(dst), *extra]
    subprocess.run(cmd, check=True, cwd=ROOT)


def resolve_field_spell_png(entry: FieldSpellEntry) -> Path:
    stem_png = ASSET_ROOT / f"{entry.stem}.png"
    legacy_png = entry.asset_dir / "field.png"
    if stem_png.is_file():
        return stem_png
    if legacy_png.is_file():
        return legacy_png
    raise SystemExit(
        f"Missing field spell PNG for {entry.card_const}: "
        f"expected {stem_png} or {legacy_png}"
    )


def validate_png(path: Path) -> None:
    with Image.open(path) as image:
        if image.size != (FIELD_PNG_WIDTH, FIELD_PNG_HEIGHT):
            raise SystemExit(
                f"{path}: expected {FIELD_PNG_WIDTH}x{FIELD_PNG_HEIGHT}px, got {image.size[0]}x{image.size[1]}px"
            )
        if image.mode != "P":
            raise SystemExit(f"{path}: expected indexed PNG (mode P), got mode {image.mode}")
        colors = image.getcolors(maxcolors=256)
        if colors is None:
            raise SystemExit(f"{path}: unable to count palette colors")
        if len(colors) > FIELD_MAX_COLORS:
            raise SystemExit(f"{path}: uses {len(colors)} colors; maximum is {FIELD_MAX_COLORS}")


def rgb_distance(left: tuple[int, int, int], right: tuple[int, int, int]) -> int:
    return sum((left[channel] - right[channel]) ** 2 for channel in range(3))


def load_png_palette_rgb(image: Image.Image) -> list[tuple[int, int, int]]:
    palette = image.getpalette()
    if palette is None:
        raise SystemExit("Indexed PNG is missing a palette")
    colors: list[tuple[int, int, int]] = []
    for index in range(FIELD_MAX_COLORS):
        offset = index * 3
        colors.append((palette[offset], palette[offset + 1], palette[offset + 2]))
    return colors


def closest_local_index(pixel_index: int, bank: int, palette_rgb: list[tuple[int, int, int]]) -> int:
    target = palette_rgb[pixel_index]
    best_index = 0
    best_distance = rgb_distance(target, palette_rgb[bank * FIELD_PALETTE_BANK_SIZE])
    for local_index in range(1, FIELD_PALETTE_BANK_SIZE):
        candidate = bank * FIELD_PALETTE_BANK_SIZE + local_index
        distance = rgb_distance(target, palette_rgb[candidate])
        if distance < best_distance:
            best_distance = distance
            best_index = local_index
    return best_index


def encode_tile_pixels(
    pixel_indices: list[int],
    palette_rgb: list[tuple[int, int, int]],
) -> tuple[bytes, int]:
    best_bank = 0
    best_local: list[int] | None = None
    best_error = None

    for bank in range(FIELD_PALETTE_BANK_COUNT):
        local = [closest_local_index(pixel, bank, palette_rgb) for pixel in pixel_indices]
        error = sum(
            rgb_distance(
                palette_rgb[pixel],
                palette_rgb[bank * FIELD_PALETTE_BANK_SIZE + local_value],
            )
            for pixel, local_value in zip(pixel_indices, local)
        )
        if best_error is None or error < best_error:
            best_error = error
            best_bank = bank
            best_local = local

    assert best_local is not None
    return pack_4bpp_tile(best_local), best_bank


def pack_4bpp_tile(local_indices: list[int]) -> bytes:
    if len(local_indices) != 64:
        raise ValueError("expected 64 pixel indices per tile")

    out = bytearray(FIELD_BPP_TILE_BYTES)
    for row in range(8):
        for pair in range(4):
            left = local_indices[row * 8 + pair * 2] & 0xF
            right = local_indices[row * 8 + pair * 2 + 1] & 0xF
            out[row * 4 + pair] = (right << 4) | left
    return bytes(out)


def decode_tile_key(key: tuple[int, bytes], palette_rgb: list[tuple[int, int, int]]) -> list[tuple[int, int, int]]:
    bank, tile_bytes = key
    colors: list[tuple[int, int, int]] = []
    for row in range(8):
        for pair in range(4):
            byte = tile_bytes[row * 4 + pair]
            for local in (byte & 0xF, byte >> 4):
                colors.append(palette_rgb[bank * FIELD_PALETTE_BANK_SIZE + local])
    return colors


def tile_key_distance(
    left: tuple[int, bytes],
    right: tuple[int, bytes],
    palette_rgb: list[tuple[int, int, int]],
) -> int:
    left_colors = decode_tile_key(left, palette_rgb)
    right_colors = decode_tile_key(right, palette_rgb)
    return sum(rgb_distance(a, b) for a, b in zip(left_colors, right_colors))


def tile_signature(key: tuple[int, bytes], palette_rgb: list[tuple[int, int, int]]) -> tuple[int, int, int]:
    colors = decode_tile_key(key, palette_rgb)
    return (
        sum(color[0] for color in colors) // 64,
        sum(color[1] for color in colors) // 64,
        sum(color[2] for color in colors) // 64,
    )


def merge_tile_keys_to_budget(
    cell_keys: list[tuple[int, bytes] | None],
    palette_rgb: list[tuple[int, int, int]],
) -> list[tuple[int, bytes] | None]:
    unique_keys = {key for key in cell_keys if key is not None}
    if len(unique_keys) <= FIELD_MAX_UNIQUE_TILES:
        return cell_keys

    merged_cells = list(cell_keys)
    active_keys = list(unique_keys)
    merges = 0

    while len(active_keys) > FIELD_MAX_UNIQUE_TILES:
        active_keys.sort(key=lambda key: tile_signature(key, palette_rgb))

        best_index = 0
        best_distance: int | None = None
        for index in range(len(active_keys) - 1):
            distance = tile_key_distance(active_keys[index], active_keys[index + 1], palette_rgb)
            if best_distance is None or distance < best_distance:
                best_distance = distance
                best_index = index

        keep_key = active_keys[best_index]
        drop_key = active_keys[best_index + 1]
        active_keys.pop(best_index + 1)

        for index, key in enumerate(merged_cells):
            if key == drop_key:
                merged_cells[index] = keep_key
        merges += 1

    if merges:
        print(
            f"Merged {merges} similar 8x8 tile(s) to fit the {FIELD_MAX_UNIQUE_TILES}-tile duel field budget.",
            file=sys.stderr,
        )

    return merged_cells


def build_field_tileset_and_tilemap(image: Image.Image) -> tuple[bytes, bytes]:
    pixels = image.load()
    palette_rgb = load_png_palette_rgb(image)
    tiles_wide = FIELD_PNG_WIDTH // 8
    tiles_high = FIELD_PNG_HEIGHT // 8
    cell_keys: list[tuple[int, bytes] | None] = []

    for row in range(FIELD_TILEMAP_ROWS):
        for col in range(FIELD_TILEMAP_COLS):
            if row >= tiles_high or col >= tiles_wide:
                cell_keys.append(None)
                continue

            tile_pixels = [
                pixels[col * 8 + x, row * 8 + y]
                for y in range(8)
                for x in range(8)
            ]
            tile_bytes, bank = encode_tile_pixels(tile_pixels, palette_rgb)
            cell_keys.append((bank, tile_bytes))

    cell_keys = merge_tile_keys_to_budget(cell_keys, palette_rgb)

    tile_lookup: dict[tuple[int, bytes], int] = {}
    tileset = bytearray()
    entries: list[int] = []

    for key in cell_keys:
        if key is None:
            entries.append(0)
            continue

        bank, tile_bytes = key
        if key not in tile_lookup:
            tile_lookup[key] = len(tile_lookup)
            tileset.extend(tile_bytes)

        entries.append(tile_lookup[key] | (bank << 12))

    if len(tileset) > FIELD_MAX_TILESET_BYTES:
        raise SystemExit(
            f"Field tileset is {len(tileset)} bytes; maximum is {FIELD_MAX_TILESET_BYTES}."
        )

    return bytes(tileset), struct.pack(f"<{len(entries)}H", *entries)


def write_tilemap_source(path: Path, field_id: str, tilemap: bytes) -> None:
    symbol = tile_symbol(field_id, "Tilemap")
    lines = [f"const u16 {symbol}[{FIELD_TILEMAP_ROWS}][{FIELD_TILEMAP_COLS}] APPEND_RODATA = {{"]
    offset = 0
    for row in range(FIELD_TILEMAP_ROWS):
        row_values = []
        for col in range(FIELD_TILEMAP_COLS):
            value = struct.unpack_from("<H", tilemap, offset)[0]
            row_values.append(str(value))
            offset += 2
        lines.append("  {" + ", ".join(row_values) + "},")
    lines.append("};")
    path.write_text("\n".join(lines) + "\n")


def build_entry_assets(entry: FieldSpellEntry) -> None:
    entry.asset_dir.mkdir(parents=True, exist_ok=True)
    png_path = resolve_field_spell_png(entry)

    validate_png(png_path)

    with Image.open(png_path) as image:
        bpp_bytes, tilemap = build_field_tileset_and_tilemap(image)

    bpp_path = entry.asset_dir / f"field{FIELD_BPP_PATH_SUFFIX}"
    pal_path = entry.asset_dir / "field.gbapal"
    huff_path = entry.asset_dir / "field.huff"
    tilemap_path = entry.asset_dir / "field.tilemap.bin"

    bpp_path.write_bytes(bpp_bytes)
    if len(bpp_bytes) > FIELD_MAX_UNIQUE_TILES * FIELD_BPP_TILE_BYTES:
        raise SystemExit(
            f"{bpp_path}: {len(bpp_bytes)} bytes exceeds the {FIELD_MAX_UNIQUE_TILES}-tile VRAM budget."
        )

    run_gbagfx(png_path, pal_path)

    pal_data = pal_path.read_bytes()
    if len(pal_data) > FIELD_PALETTE_BYTES:
        pal_data = pal_data[:FIELD_PALETTE_BYTES]
        pal_path.write_bytes(pal_data)
    if len(pal_data) != FIELD_PALETTE_BYTES:
        raise SystemExit(f"{pal_path}: expected {FIELD_PALETTE_BYTES} bytes, got {len(pal_data)}")

    tilemap_path.write_bytes(tilemap)
    write_tilemap_source(entry.asset_dir / "field.tilemap.c", entry.field_id, tilemap)

    run_gbagfx(bpp_path, huff_path, "-depth", "4")

    legacy_8bpp = entry.asset_dir / "field.8bpp"
    if legacy_8bpp.is_file():
        legacy_8bpp.unlink()


def render_gfx_generated_inc(entries: list[FieldSpellEntry]) -> str:
    lines = [
        "// Auto-generated by tools/build_field_spell_gfx.py. Do not edit.",
        "",
    ]
    for entry in entries:
        rel = (entry.asset_dir / "field.huff").relative_to(ROOT).as_posix()
        pal_rel = (entry.asset_dir / "field.gbapal").relative_to(ROOT).as_posix()
        lines.append(
            f"const u8 {tile_symbol(entry.field_id, 'Tiles')}[] APPEND_ASSET = "
            f'INCBIN_U8("{rel}");'
        )
        lines.append(
            f"const u16 {tile_symbol(entry.field_id, 'Palette')}[] APPEND_ASSET = "
            f'INCBIN_U16("{pal_rel}");'
        )
        lines.append("")
    return "\n".join(lines).rstrip() + "\n"


def render_tilemaps_generated_inc(entries: list[FieldSpellEntry]) -> str:
    lines = [
        "// Auto-generated by tools/build_field_spell_gfx.py. Do not edit.",
        "",
    ]
    for entry in entries:
        rel = (entry.asset_dir / "field.tilemap.c").relative_to(ROOT).as_posix()
        lines.append(f'#include "{rel}"')
    if entries:
        lines.append("")
    return "\n".join(lines).rstrip() + "\n"


def render_custom_field_spells_generated_h(entries: list[FieldSpellEntry]) -> str:
    lines = ["  // Auto-generated by tools/build_field_spell_gfx.py. Do not edit."]
    for index, entry in enumerate(entries, start=1):
        lines.append(f"  {entry.spell_id} = {index},")
    if not entries:
        lines.append("  // No custom field spells registered in src_custom/field_spell_table.inc.")
    return "\n".join(lines) + "\n"


def render_custom_fields_generated_h(entries: list[FieldSpellEntry]) -> str:
    lines = [
        "#ifndef GUARD_CONSTANTS_CUSTOM_FIELDS_GENERATED_H",
        "#define GUARD_CONSTANTS_CUSTOM_FIELDS_GENERATED_H",
        "",
        "// Auto-generated by tools/build_field_spell_gfx.py. Do not edit.",
        "",
        f"#define NUM_CUSTOM_FIELDS {len(entries)}",
        "",
    ]
    for index, entry in enumerate(entries):
        value = f"NUM_VANILLA_FIELDS + {index}" if index else "NUM_VANILLA_FIELDS"
        lines.append(f"#define {entry.field_id} {value}")
    lines.append("")
    lines.append("#define NUM_FIELDS (NUM_VANILLA_FIELDS + NUM_CUSTOM_FIELDS)")
    lines.append("#define FIRST_CUSTOM_FIELD NUM_VANILLA_FIELDS")
    lines.append("")
    lines.append("#endif // GUARD_CONSTANTS_CUSTOM_FIELDS_GENERATED_H")
    lines.append("")
    return "\n".join(lines)


def load_manifest_custom_field_cards() -> dict[str, str]:
    manifest_path = ROOT / "tools/card_data_manifest.json"
    if not manifest_path.is_file():
        return {}
    import json

    data = json.loads(manifest_path.read_text())
    mapping: dict[str, str] = {}
    for card in data.get("cards", []):
        spell_id = card.get("customFieldSpell")
        card_const = card.get("card_const")
        if isinstance(spell_id, str) and isinstance(card_const, str):
            mapping[card_const] = spell_id
    return mapping


def render_gfx_tables_generated_inc(entries: list[FieldSpellEntry]) -> str:
    lines = [
        "// Auto-generated by tools/build_field_spell_gfx.py. Do not edit.",
        "",
    ]
    if not entries:
        lines.append("static const struct CustomFieldGfxAsset *const sCustomFieldGfxAssets = NULL;")
        lines.append("")
        return "\n".join(lines)

    lines.append("static const struct CustomFieldGfxAsset sCustomFieldGfxAssets[NUM_CUSTOM_FIELDS] APPEND_RODATA = {")
    for entry in entries:
        lines.append(
            "  {"
            f"{tile_symbol(entry.field_id, 'Tiles')}, "
            f"{tile_symbol(entry.field_id, 'Tilemap')}, "
            f"{tile_symbol(entry.field_id, 'Palette')}"
            "},"
        )
    lines.extend(["};", ""])
    return "\n".join(lines)


def render_effect_table_generated_inc(entries: list[FieldSpellEntry]) -> str:
    lines = [
        "// Auto-generated by tools/build_field_spell_gfx.py. Do not edit.",
        "",
    ]
    if not entries:
        lines.append("static const CustomFieldSpellEffectFn *const sCustomFieldSpellEffects = NULL;")
        lines.append("")
        return "\n".join(lines)

    for entry in entries:
        lines.append(f"extern void {entry.effect_fn}(void);")
    lines.append("")
    lines.append("static const CustomFieldSpellEffectFn sCustomFieldSpellEffects[NUM_CUSTOM_FIELD_SPELLS - 1] APPEND_RODATA = {")
    for entry in entries:
        lines.append(f"  [{entry.spell_id} - 1] = {entry.effect_fn},")
    lines.extend(["};", ""])
    return "\n".join(lines)


def render_stat_mods_generated_inc(entries: list[FieldSpellEntry]) -> str:
    lines = [
        "// Auto-generated by tools/build_field_spell_gfx.py. Do not edit.",
        "",
    ]
    if not entries:
        lines.append("// No custom field stat modifiers registered.")
        lines.append("")
        return "\n".join(lines)

    lines.append("const u8 gCustomFieldStatMods[NUM_CUSTOM_FIELDS][NUM_CARD_TYPES] APPEND_RODATA = {")
    for _ in entries:
        lines.append("  {" + ", ".join(["0"] * 24) + "},")
    lines.extend(["};", ""])
    return "\n".join(lines)


def render_mapping_generated_inc(entries: list[FieldSpellEntry]) -> str:
    lines = [
        "// Auto-generated by tools/build_field_spell_gfx.py. Do not edit.",
        "",
    ]
    if not entries:
        lines.append("static const u8 *const sCustomFieldIdBySpellId = NULL;")
        lines.append("")
        return "\n".join(lines)

    lines.append("static const u8 sCustomFieldIdBySpellId[NUM_CUSTOM_FIELD_SPELLS - 1] APPEND_RODATA = {")
    for entry in entries:
        lines.append(f"  [{entry.spell_id} - 1] = {entry.field_id},")
    lines.extend(["};", ""])
    return "\n".join(lines)


def render_card_lookup_generated_inc(entries: list[FieldSpellEntry]) -> str:
    manifest_map = load_manifest_custom_field_cards()
    by_spell = {entry.spell_id: entry for entry in entries}
    for card_const, spell_id in manifest_map.items():
        if spell_id not in by_spell:
            raise SystemExit(
                f"Manifest card {card_const} references unknown customFieldSpell {spell_id}"
            )
    if len(manifest_map) == 1:
        only_const, only_spell = next(iter(sorted(manifest_map.items())))
        return "\n".join([
            "// Auto-generated by tools/build_field_spell_gfx.py. Do not edit.",
            "",
            "static u8 LookupCustomFieldSpellIdForCard(u16 cardId)",
            "{",
            f"  if (cardId == {only_const})",
            f"    return {only_spell};",
            "  return CUSTOM_FIELD_SPELL_NONE;",
            "}",
            "",
        ])
    lines = [
        "// Auto-generated by tools/build_field_spell_gfx.py. Do not edit.",
        "",
        "static u8 LookupCustomFieldSpellIdForCard(u16 cardId)",
        "{",
        "  switch (cardId) {",
    ]
    for card_const, spell_id in sorted(manifest_map.items()):
        lines.append(f"    case {card_const}:")
        lines.append(f"      return {spell_id};")
    lines.extend(
        [
            "    default:",
            "      return CUSTOM_FIELD_SPELL_NONE;",
            "  }",
            "}",
            "",
        ]
    )
    return "\n".join(lines)


def update_file(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.is_file() and path.read_text() == content:
        return
    path.write_text(content)


def main() -> int:
    parser = argparse.ArgumentParser(description="Build custom field spell graphics and generated headers.")
    parser.add_argument("--print", action="store_true", help="Print generated files instead of writing them")
    args = parser.parse_args()

    if not TABLE_INC.is_file():
        raise SystemExit(f"Missing registration table: {TABLE_INC}")
    if not GBAFX.is_file():
        raise SystemExit(f"Missing gbagfx tool: {GBAFX}")

    entries = parse_field_spell_table(TABLE_INC)
    for entry in entries:
        build_entry_assets(entry)

    outputs = {
        GFX_GENERATED_INC: render_gfx_generated_inc(entries),
        TILEMAPS_GENERATED_INC: render_tilemaps_generated_inc(entries),
        CUSTOM_FIELD_SPELLS_GENERATED_H: render_custom_field_spells_generated_h(entries),
        CUSTOM_FIELDS_GENERATED_H: render_custom_fields_generated_h(entries),
        CARD_LOOKUP_GENERATED_INC: render_card_lookup_generated_inc(entries),
        GFX_TABLES_GENERATED_INC: render_gfx_tables_generated_inc(entries),
        EFFECT_TABLE_GENERATED_INC: render_effect_table_generated_inc(entries),
        STAT_MODS_GENERATED_INC: render_stat_mods_generated_inc(entries),
        MAPPING_GENERATED_INC: render_mapping_generated_inc(entries),
    }

    if args.print:
        for path, content in outputs.items():
            print(f"--- {path} ---")
            print(content, end="")
        return 0

    for path, content in outputs.items():
        update_file(path, content)

    print(f"Built {len(entries)} custom field spell asset(s).")
    return 0


if __name__ == "__main__":
    sys.exit(main())
