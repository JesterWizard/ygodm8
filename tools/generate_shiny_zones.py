#!/usr/bin/env python3
"""Generate shiny-zone pickup data from tools/shiny_zone_manifest.json."""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[1]
MAX_FLAGS = 128
MAP_WIDTH = 120
MAP_HEIGHT = 80
BG_TILE_WIDTH = 32
BG_TILE_HEIGHT = 32
TILE_SIZE = 8


def strip_c_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.DOTALL)
    return re.sub(r"//.*", "", text)


def parse_c_integer(value: str, names: dict[str, int]) -> int:
    value = value.strip()
    if value in names:
        return names[value]
    if re.fullmatch(r"[-+]?(?:0[xX][0-9A-Fa-f]+|\d+)", value):
        return int(value, 0)
    raise ValueError(f"unsupported C integer constant {value!r}")


def load_c_constants(paths: list[Path]) -> dict[str, int]:
    constants: dict[str, int] = {}
    for path in paths:
        text = strip_c_comments(path.read_text())
        for match in re.finditer(r"^\s*#define\s+([A-Za-z_][A-Za-z0-9_]*)\s+([-+]?(?:0[xX][0-9A-Fa-f]+|\d+))\b", text, re.MULTILINE):
            constants[match.group(1)] = int(match.group(2), 0)
        for enum_body in re.findall(r"\benum(?:\s+[A-Za-z_][A-Za-z0-9_]*)?\s*\{(.*?)\}", text, re.DOTALL):
            value = 0
            for raw_item in enum_body.split(","):
                item = raw_item.strip()
                if not item:
                    continue
                name, _, explicit = item.partition("=")
                name = name.strip()
                if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", name):
                    continue
                if explicit:
                    value = parse_c_integer(explicit, constants)
                constants[name] = value
                value += 1
    return constants


def load_card_names(path: Path) -> dict[str, str]:
    data = json.loads(path.read_text())
    names: dict[str, str] = {}
    for card in data.get("cards", []):
        const = card.get("card_const")
        name = card.get("card_name")
        if isinstance(const, str) and isinstance(name, str):
            names[const] = name
    return names


def resolve_int(value: Any, constants: dict[str, int], field: str) -> int:
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        if value in constants:
            return constants[value]
        if re.fullmatch(r"[-+]?(?:0[xX][0-9A-Fa-f]+|\d+)", value):
            return int(value, 0)
    raise SystemExit(f"{field} must be an integer or known constant, got {value!r}")


def c_string(value: str) -> str:
    return '"' + value.replace("\\", "\\\\").replace('"', '\\"') + '"'


def get_card_name(card_const: str, card_id: int, card_names: dict[str, str]) -> str:
    if card_const in card_names:
        return card_names[card_const]
    return f"Card {card_id}"


def load_manifest(path: Path) -> list[dict[str, Any]]:
    data = json.loads(path.read_text())
    zones = data.get("zones")
    if not isinstance(zones, list):
        raise SystemExit("shiny zone manifest must contain a zones list")
    for index, zone in enumerate(zones):
        if not isinstance(zone, dict):
            raise SystemExit(f"zone {index} must be an object")
    return zones


def resolve_coordinate(zone: dict[str, Any], index: int, constants: dict[str, int], object_id: int) -> tuple[int, int, int]:
    if object_id != constants["SHINY_ZONE_NO_OBJECT"]:
        return constants["SHINY_ZONE_COORD_OVERWORLD"], 0, 0

    if "tile_x" in zone or "tile_y" in zone:
        tile_x = resolve_int(zone.get("tile_x"), constants, f"zones[{index}].tile_x")
        tile_y = resolve_int(zone.get("tile_y"), constants, f"zones[{index}].tile_y")
        if not (0 <= tile_x < BG_TILE_WIDTH and 0 <= tile_y < BG_TILE_HEIGHT):
            raise SystemExit(f"zones[{index}].tile_x/tile_y must be BG tile coordinates 0-{BG_TILE_WIDTH - 1}, 0-{BG_TILE_HEIGHT - 1}")
        return constants["SHINY_ZONE_COORD_SCREEN_TILE"], tile_x, tile_y

    if "screen_x" in zone or "screen_y" in zone:
        screen_x = resolve_int(zone.get("screen_x"), constants, f"zones[{index}].screen_x")
        screen_y = resolve_int(zone.get("screen_y"), constants, f"zones[{index}].screen_y")
        if screen_x % TILE_SIZE or screen_y % TILE_SIZE:
            raise SystemExit(f"zones[{index}].screen_x/screen_y must be tile-aligned pixel origins")
        tile_x = screen_x // TILE_SIZE
        tile_y = screen_y // TILE_SIZE
        if not (0 <= tile_x < BG_TILE_WIDTH and 0 <= tile_y < BG_TILE_HEIGHT):
            raise SystemExit(f"zones[{index}].screen_x/screen_y resolve outside the BG tilemap")
        return constants["SHINY_ZONE_COORD_SCREEN_TILE"], tile_x, tile_y

    x = resolve_int(zone.get("x", 0), constants, f"zones[{index}].x")
    y = resolve_int(zone.get("y", 0), constants, f"zones[{index}].y")
    if not (0 <= x < MAP_WIDTH and 0 <= y < MAP_HEIGHT):
        raise SystemExit(
            f"zones[{index}].x/y must be overworld coordinates "
            f"(0-{MAP_WIDTH - 1}, 0-{MAP_HEIGHT - 1}); use tile_x/tile_y for No$GBA BG tile coordinates"
        )
    return constants["SHINY_ZONE_COORD_OVERWORLD"], x, y


def generate(zones: list[dict[str, Any]], constants: dict[str, int], card_names: dict[str, str]) -> str:
    lines: list[str] = [
        "/* Generated by tools/generate_shiny_zones.py. Do not edit by hand. */",
        "",
    ]
    entries: list[str] = []
    used_flags: set[int] = set()

    for index, zone in enumerate(zones):
        flag = resolve_int(zone.get("flag", index), constants, f"zones[{index}].flag")
        if flag < 0 or flag >= MAX_FLAGS:
            raise SystemExit(f"zones[{index}].flag must be between 0 and {MAX_FLAGS - 1}")
        if flag in used_flags:
            raise SystemExit(f"duplicate shiny zone flag {flag}")
        used_flags.add(flag)

        map_id = resolve_int(zone.get("map"), constants, f"zones[{index}].map")
        state_value = zone.get("state", "SHINY_ZONE_ANY_STATE")
        state = resolve_int(state_value, constants, f"zones[{index}].state")
        object_value = zone.get("object_id", "SHINY_ZONE_NO_OBJECT")
        object_id = resolve_int(object_value, constants, f"zones[{index}].object_id")
        coordinate_type, x, y = resolve_coordinate(zone, index, constants, object_id)

        card_const = zone.get("card")
        if not isinstance(card_const, str):
            raise SystemExit(f"zones[{index}].card must be a card constant string")
        card_id = resolve_int(card_const, constants, f"zones[{index}].card")
        card_name = get_card_name(card_const, card_id, card_names)

        if index == 0:
            lines.append("static const u8 sShinyZoneEndBytes[] APPEND_TEXT = {0x5D};")
            lines.append(
                "static const struct Script sShinyZoneEndScript APPEND_RODATA = { "
                "(u8 *)sShinyZoneEndBytes, "
                "(struct Script *)&sShinyZoneEndScript, "
                "(struct Script *)&sShinyZoneEndScript };"
            )
            lines.append("")

        lines.append(f"static const u8 sShinyZoneText{index}[] APPEND_TEXT = {c_string('Obtained#0' + card_name + '#1')};")
        lines.append(
            f"static const struct Script sShinyZoneScript{index} APPEND_RODATA = {{ "
            f"(u8 *)sShinyZoneText{index}, "
            "(struct Script *)&sShinyZoneEndScript, "
            "(struct Script *)&sShinyZoneEndScript };"
        )
        entries.append(
            "  { "
            f".flag = {flag}, .mapId = {map_id}, .state = {state}, "
            f".objectId = {object_id}, .coordinateType = {coordinate_type}, .x = {x}, .y = {y}, "
            f".cardId = {card_id}, .script = &sShinyZoneScript{index} "
            "},"
        )

    if not entries:
        entries.append(
            "  { .flag = 0, .mapId = 0, .state = 0, .objectId = SHINY_ZONE_NO_OBJECT, .coordinateType = SHINY_ZONE_COORD_OVERWORLD, .x = 0, .y = 0, .cardId = CARD_NONE, .script = 0 },"
        )

    lines.extend([
        "",
        "const ShinyZoneEntry gShinyZoneEntries[] APPEND_RODATA = {",
        *entries,
        "};",
        f"const unsigned gShinyZoneEntryCount APPEND_RODATA = {len(zones)};",
        "",
    ])
    return "\n".join(lines)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest", type=Path)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()

    constants = load_c_constants([
        ROOT / "include/constants/card_ids.h",
        ROOT / "include/overworld.h",
        ROOT / "include/shiny_zones.h",
    ])
    card_names = load_card_names(ROOT / "tools/card_data_manifest.json")
    output = generate(load_manifest(args.manifest), constants, card_names)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(output)


if __name__ == "__main__":
    main()
