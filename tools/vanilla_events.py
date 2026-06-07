#!/usr/bin/env python3
"""Extract, validate, catalog, and compile vanilla overworld events."""

from __future__ import annotations

import argparse
import ast
import re
import struct
import sys
import textwrap
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    import yaml
except ImportError:  # pragma: no cover - exercised only on stripped systems
    yaml = None

if yaml is not None:
    YAML_LOADER = getattr(yaml, "CSafeLoader", yaml.SafeLoader)
    YAML_DUMPER = getattr(yaml, "CSafeDumper", yaml.SafeDumper)


ROOT = Path(__file__).resolve().parents[1]
ROM_BASE = 0x08000000
MAP_DATA_ADDR = 0x08E19274
MAP_DATA_SIZE = 0x1F8
OBJECT_DATA_SIZE = 0x14
MAP_SCRIPT_SIZE = 8
OBJECT_COUNT = 16
SCRIPT_MAX_BYTES = 0x4000

CUTSCENE_NAMES = {
    0: "RESHEF_VISION",
    1: "BURNING_RESHEF_2_AND_SOL_CHEVALSKY",
    2: "CREDITS",
    3: "CUTSCENE_3",
    4: "CUTSCENE_4",
    5: "CUTSCENE_5",
    6: "CUTSCENE_6",
    7: "PEGASUS_BEFORE_CREDITS",
    8: "INTRO_CUTSCENE",
}


def load_charmap(path: Path) -> dict[tuple[int, ...], str]:
    result: dict[tuple[int, ...], str] = {}
    for raw_line in path.read_text().splitlines():
        line = raw_line.split("@", 1)[0].strip()
        if " = " not in line:
            continue
        key, value = line.split(" = ", 1)
        key = key.strip()
        bytes_value = tuple(int(part, 16) for part in value.split())
        if key.startswith("'"):
            try:
                text = ast.literal_eval(key)
            except (SyntaxError, ValueError):
                continue
        elif key == "PLAYER":
            text = "{PLAYER}"
        elif key.startswith("CARD_"):
            text = "{" + key + "}"
        elif key == "TEXT_END":
            text = ""
        else:
            continue
        if text == "\\p":
            text = "\n\n"
        result[bytes_value] = text
    return result


CHARMAP = load_charmap(ROOT / "charmap.txt")


def parse_c_integer_constant(value: str, names: dict[str, int]) -> int:
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
                    value = parse_c_integer_constant(explicit, constants)
                constants[name] = value
                value += 1
    return constants


SPECIAL_COMMANDS = {
    0: "effect_0",
    1: "effect_1",
    2: "random_card_name",
    3: "random_text_group_3",
    4: "random_text_group_4",
    5: "random_text_group_5",
    6: "random_text_group_6",
    7: "random_text_group_7",
    8: "random_text_group_8",
    9: "random_text_group_9",
    10: "random_text_group_10",
    11: "random_text_group_11",
    12: "effect_12",
    13: "random_text_group_13",
    14: "random_text_group_14",
    15: "cutscene_0",
    16: "cutscene_1",
    17: "card_shop_buy",
    18: "card_shop_sell",
    19: "card_password",
    20: "credits",
    21: "effect_21",
    22: "effect_22",
    23: "effect_23",
    24: "effect_24",
    25: "palette_fade",
    32: "palette_fade_alt",
    33: "cutscene_8",
    34: "cutscene_7",
    35: "remove_1000_domino",
}
SPECIAL_COMMANDS_INV = {name: value for value, name in SPECIAL_COMMANDS.items()}


@dataclass(frozen=True)
class ObjectData:
    object_id: int
    sprite_id: int
    direction: int
    x: int
    y: int
    script_a: int
    script_r: int
    has_shadow: bool
    face_player: bool
    wander: bool
    elevation: int


@dataclass
class ScriptNode:
    address: int
    start_address: int
    false_address: int
    true_address: int
    raw_bytes: list[int]
    steps: list[dict[str, Any]]


class Rom:
    def __init__(self, path: Path):
        self.path = path
        self.data = path.read_bytes()

    def valid_addr(self, addr: int) -> bool:
        return ROM_BASE <= addr < ROM_BASE + len(self.data)

    def off(self, addr: int) -> int:
        if not self.valid_addr(addr):
            raise ValueError(f"ROM address out of range: 0x{addr:08X}")
        return addr - ROM_BASE

    def u8(self, addr: int) -> int:
        return self.data[self.off(addr)]

    def s16(self, addr: int) -> int:
        return struct.unpack_from("<h", self.data, self.off(addr))[0]

    def u16(self, addr: int) -> int:
        return struct.unpack_from("<H", self.data, self.off(addr))[0]

    def u32(self, addr: int) -> int:
        return struct.unpack_from("<I", self.data, self.off(addr))[0]

    def bytes_at(self, addr: int, size: int) -> list[int]:
        off = self.off(addr)
        return list(self.data[off : off + size])


def hexaddr(addr: int | None) -> str | None:
    if not addr:
        return None
    return f"0x{addr:08X}"


def byte_list(values: list[int]) -> list[str]:
    return [f"0x{value:02X}" for value in values]


def parse_hex(value: Any) -> int:
    if value is None:
        return 0
    if isinstance(value, int):
        return value
    return int(str(value), 0)


def load_yaml(path: Path) -> dict[str, Any]:
    if yaml is None:
        raise SystemExit("PyYAML is required to read event YAML. Install python3-yaml.")
    with path.open() as f:
        loaded = yaml.load(f, Loader=YAML_LOADER)
    if not isinstance(loaded, dict):
        raise SystemExit(f"{path} did not contain a YAML mapping.")
    return loaded


def write_yaml(path: Path, data: dict[str, Any]) -> None:
    if yaml is None:
        raise SystemExit("PyYAML is required to write event YAML. Install python3-yaml.")
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w") as f:
        yaml.dump(data, f, Dumper=YAML_DUMPER, sort_keys=False, width=120)


def map_pointer_table(rom: Rom) -> list[tuple[int, int, list[int]]]:
    arrays: list[int] = []
    index = 0
    while True:
        ptr = rom.u32(MAP_DATA_ADDR + index * 4)
        if not rom.valid_addr(ptr):
            break
        arrays.append(ptr)
        index += 1

    result: list[tuple[int, int, list[int]]] = []
    for map_id, array_addr in enumerate(arrays):
        next_array = arrays[map_id + 1] if map_id + 1 < len(arrays) else MAP_DATA_ADDR
        state_count = max(0, (next_array - array_addr) // 4)
        state_ptrs = [rom.u32(array_addr + state * 4) for state in range(state_count)]
        result.append((map_id, array_addr, state_ptrs))
    return result


def read_object(rom: Rom, addr: int, object_id: int) -> ObjectData:
    flags = rom.u8(addr + 0x10)
    return ObjectData(
        object_id=object_id,
        sprite_id=rom.s16(addr),
        direction=rom.u8(addr + 2),
        x=rom.u16(addr + 4),
        y=rom.u16(addr + 6),
        script_a=rom.u32(addr + 8),
        script_r=rom.u32(addr + 12),
        has_shadow=bool(flags & 1),
        face_player=bool(flags & 2),
        wander=bool(flags & 4),
        elevation=rom.u8(addr + 0x11),
    )


def object_to_yaml(obj: ObjectData) -> dict[str, Any]:
    return {
        "object_id": obj.object_id,
        "sprite_id": obj.sprite_id,
        "direction": obj.direction,
        "x": obj.x,
        "y": obj.y,
        "script_a": hexaddr(obj.script_a),
        "script_r": hexaddr(obj.script_r),
        "has_shadow": obj.has_shadow,
        "face_player": obj.face_player,
        "wander": obj.wander,
        "elevation": obj.elevation,
    }


def read_map_script(rom: Rom, addr: int, slot: int) -> dict[str, Any]:
    return {
        "slot": slot,
        "script": hexaddr(rom.u32(addr)),
        "target_map_or_connection": rom.u8(addr + 4),
        "connection": rom.u8(addr + 5),
    }


def read_map_state(rom: Rom, map_id: int, state: int, addr: int) -> dict[str, Any]:
    objects: list[dict[str, Any]] = []
    for object_id in range(OBJECT_COUNT):
        obj = read_object(rom, addr + object_id * OBJECT_DATA_SIZE, object_id + 1)
        if obj.sprite_id == -1:
            break
        objects.append(object_to_yaml(obj))

    on_enter = [
        read_map_script(rom, addr + 0x140 + slot * MAP_SCRIPT_SIZE, slot)
        for slot in range(5)
    ]
    on_exit = [
        read_map_script(rom, addr + 0x168 + slot * MAP_SCRIPT_SIZE, slot)
        for slot in range(5)
    ]
    player_start = [
        object_to_yaml(read_object(rom, addr + 0x190 + slot * OBJECT_DATA_SIZE, slot))
        for slot in range(5)
    ]
    return {
        "scene_id": f"map_{map_id:02d}_state_{state:02d}",
        "label": None,
        "map_id": map_id,
        "state": state,
        "map_data_address": hexaddr(addr),
        "music": rom.u16(addr + 0x1F4),
        "flags": rom.u8(addr + 0x1F6),
        "initial_sprites": objects,
        "player_start": player_start,
        "on_enter": on_enter,
        "on_exit": on_exit,
    }


def collect_script_refs(scenes: list[dict[str, Any]]) -> set[int]:
    refs: set[int] = set()
    for scene in scenes:
        for obj in scene["initial_sprites"]:
            refs.add(parse_hex(obj.get("script_a")))
            refs.add(parse_hex(obj.get("script_r")))
        for slot in scene["on_enter"] + scene["on_exit"]:
            refs.add(parse_hex(slot.get("script")))
    refs.discard(0)
    return refs


def decode_char(data: list[int], index: int) -> tuple[str, int]:
    if index + 1 < len(data):
        pair = (data[index], data[index + 1])
        if pair in CHARMAP:
            text = CHARMAP[pair]
            if len(text) == 1 and 0x20 <= ord(text) <= 0x7E:
                return f"{{BYTE_{data[index]:02X}{data[index + 1]:02X}}}", 2
            return text, 2
    value = data[index]
    if (value,) in CHARMAP:
        return CHARMAP[(value,)], 1
    if value <= 0x7F:
        if value == 0:
            return "", 1
        if 0x20 <= value <= 0x7E:
            return chr(value), 1
        return f"{{BYTE_{value:02X}}}", 1
    if index + 1 < len(data):
        return f"{{BYTE_{value:02X}{data[index + 1]:02X}}}", 2
    return f"{{BYTE_{value:02X}}}", 1


def decode_text_bytes(raw: list[int]) -> str:
    parts: list[str] = []
    index = 0
    while index < len(raw):
        text, size = decode_char(raw, index)
        parts.append(text)
        index += size
    return "".join(parts)


def read_language_block(data: list[int], index: int) -> tuple[int, list[int], str]:
    raw_start = index
    english: list[int] = []
    selected: list[int] | None = None

    while index + 1 < len(data) and data[index] == 0x24:
        lang = data[index + 1]
        index += 2
        if lang == ord("6"):
            return index, data[raw_start:index], decode_text_bytes(english)
        body_start = index
        while index < len(data) and data[index] != 0x24:
            index += 2 if data[index] & 0x80 else 1
        if lang == ord("0"):
            selected = data[body_start:index]
            english = selected

    if selected is None:
        return raw_start + 1, [data[raw_start]], ""
    return index, data[raw_start:index], decode_text_bytes(english)


def parse_language_block(raw: list[int]) -> list[tuple[int, str]]:
    languages: list[tuple[int, str]] = []
    index = 0
    while index + 1 < len(raw) and raw[index] == 0x24:
        lang = raw[index + 1]
        index += 2
        if lang == ord("6"):
            if index != len(raw):
                raise ValueError("trailing bytes after language block terminator")
            return languages
        body_start = index
        while index < len(raw) and raw[index] != 0x24:
            index += 2 if raw[index] & 0x80 else 1
        languages.append((lang - ord("0"), decode_text_bytes(raw[body_start:index])))
    raise ValueError("invalid language block")


def parse_language_blocks(raw: list[int]) -> list[list[tuple[int, str]]]:
    blocks: list[list[tuple[int, str]]] = []
    index = 0
    while index < len(raw):
        block_start = index
        while index + 1 < len(raw) and raw[index] == 0x24:
            index += 2
            if raw[index - 1] == ord("6"):
                blocks.append(parse_language_block(raw[block_start:index]))
                break
            while index < len(raw) and raw[index] != 0x24:
                index += 2 if raw[index] & 0x80 else 1
        else:
            raise ValueError("invalid language block sequence")
    return blocks


def append_text_step(steps: list[dict[str, Any]], raw: list[int], text: str) -> None:
    if not text:
        return
    if steps and steps[-1].get("type") == "dialogue":
        steps[-1]["text"] += text
        steps[-1]["raw"].extend(byte_list(raw))
        return
    steps.append({"type": "dialogue", "text": text, "raw": byte_list(raw)})


def read_bytecode(rom: Rom, start_addr: int) -> list[int]:
    max_size = min(SCRIPT_MAX_BYTES, ROM_BASE + len(rom.data) - start_addr)
    return rom.bytes_at(start_addr, max_size)


def decode_steps_with_size(data: list[int]) -> tuple[list[dict[str, Any]], int]:
    steps: list[dict[str, Any]] = []
    p = 0
    while p < len(data):
        op = data[p]
        if op == 0:
            steps.append({"type": "fallthrough", "raw": byte_list([op])})
            p += 1
            break
        if op == 0x5D:
            steps.append({"type": "end", "raw": byte_list([op])})
            p += 1
            break
        if op == 0x24:
            new_p, raw, text = read_language_block(data, p)
            append_text_step(steps, raw, text)
            p = new_p
            continue
        if op == 0x23 and p + 1 < len(data):
            cmd = data[p + 1]
            if cmd == ord("0"):
                raw = data[p : p + 2]
                steps.append({"type": "newline", "raw": byte_list(raw)})
                p += 2
                continue
            if cmd == ord("1"):
                raw = data[p : p + 2]
                steps.append({"type": "page_break", "raw": byte_list(raw)})
                p += 2
                continue
            if cmd == ord("3"):
                raw = data[p : p + 2]
                steps.append({"type": "choice", "branches": {"false": "unk4", "true": "unk8"}, "raw": byte_list(raw)})
                p += 2
                continue
            if cmd == ord("4") and p + 4 < len(data):
                raw = data[p : p + 5]
                steps.append({
                    "type": "portrait",
                    "portrait_id": raw[2],
                    "expression": raw[3],
                    "position": raw[4],
                    "raw": byte_list(raw),
                })
                p += 5
                continue
            if cmd == ord("5"):
                raw = data[p : p + 2]
                append_text_step(steps, raw, "{PLAYER}")
                p += 2
                continue
            if cmd in (ord("6"), ord("7"), ord("8")) and p + 2 < len(data):
                names = {ord("6"): "set_flag", ord("7"): "check_flag", ord("8"): "clear_flag"}
                raw = data[p : p + 3]
                steps.append({"type": names[cmd], "flag": raw[2], "raw": byte_list(raw)})
                p += 3
                continue
            if cmd == ord("9"):
                raw = data[p : p + 2]
                steps.append({"type": "restore_life_points", "raw": byte_list(raw)})
                p += 2
                continue
        if op == 0x40 and p + 1 < len(data):
            cmd = data[p + 1]
            if cmd == ord("0") and p + 2 < len(data):
                raw = data[p : p + 3]
                steps.append({"type": "duel", "opponent": raw[2], "branches": {"win": "unk4", "loss": "unk8"}, "raw": byte_list(raw)})
                p += 3
                continue
            if cmd in (ord("3"), ord("4"), ord("5"), ord("6")) and p + 3 < len(data):
                names = {ord("3"): "play_music", ord("4"): "set_map_music", ord("5"): "stop_music", ord("6"): "fade_music"}
                raw = data[p : p + 4]
                steps.append({"type": names[cmd], "music": raw[2] | (raw[3] << 8), "raw": byte_list(raw)})
                p += 4
                continue
            if cmd == ord("7") and p + 5 < len(data):
                raw = data[p : p + 6]
                steps.append({
                    "type": "move_object",
                    "object_id": raw[2],
                    "direction": raw[3],
                    "distance": raw[4],
                    "wander": raw[5],
                    "raw": byte_list(raw),
                })
                p += 6
                continue
            if cmd == ord("9") and p + 5 < len(data):
                raw = data[p : p + 6]
                steps.append({"type": "set_object_position", "object_id": raw[2], "x": raw[3], "y": raw[4], "frame": raw[5], "raw": byte_list(raw)})
                p += 6
                continue
            raw = data[p : p + 2]
            names = {ord("1"): "start_menu", ord("2"): "save", ord("8"): "stop_footsteps"}
            steps.append({"type": names.get(cmd, f"command_40_{chr(cmd)}"), "raw": byte_list(raw)})
            p += 2
            continue
        if op == 0x5E and p + 1 < len(data):
            cmd = data[p + 1]
            if cmd == ord("0") and p + 7 < len(data):
                raw = data[p : p + 8]
                steps.append({
                    "type": "show_object",
                    "object_id": raw[2],
                    "x": raw[3],
                    "y": raw[4],
                    "frame": raw[5],
                    "mode": raw[6],
                    "raw": byte_list(raw),
                })
                p += 8
                continue
            if cmd in (ord("1"), ord("2")) and p + 3 < len(data):
                raw = data[p : p + 4]
                steps.append({"type": "walk_object_x" if cmd == ord("1") else "walk_object_y", "object_id": raw[2], "target": raw[3], "raw": byte_list(raw)})
                p += 4
                continue
            if cmd == ord("3") and p + 4 < len(data):
                raw = data[p : p + 5]
                steps.append({"type": "slide_object", "object_id": raw[2], "direction": raw[3], "distance": raw[4], "raw": byte_list(raw)})
                p += 5
                continue
            if cmd == ord("4") and p + 4 < len(data):
                raw = data[p : p + 5]
                steps.append({"type": "object_effect", "object_mask": (raw[2] << 8) | raw[3], "mode": raw[4], "raw": byte_list(raw)})
                p += 5
                continue
            if cmd == ord("5") and p + 2 < len(data):
                raw = data[p : p + 3]
                special = raw[2]
                step: dict[str, Any] = {"type": "special", "command": SPECIAL_COMMANDS.get(special, f"special_{special}"), "raw": byte_list(raw)}
                if special in (15, 16, 33, 34):
                    cutscene_id = {15: 0, 16: 1, 33: 8, 34: 7}[special]
                    step = {"type": "cutscene", "cutscene": {"id": cutscene_id, "name": CUTSCENE_NAMES.get(cutscene_id), "opaque": True}, "raw": byte_list(raw)}
                steps.append(step)
                p += 3
                continue
            if cmd == ord("6") and p + 2 < len(data):
                raw = data[p : p + 3]
                steps.append({"type": "delay", "frames": raw[2], "raw": byte_list(raw)})
                p += 3
                continue
            if cmd in (ord("7"), ord("8")) and p + 3 < len(data):
                raw = data[p : p + 4]
                steps.append({"type": "add_card" if cmd == ord("7") else "remove_card", "card": raw[2] | (raw[3] << 8), "raw": byte_list(raw)})
                p += 4
                continue
            if cmd == ord("9") and p + 2 < len(data):
                raw = data[p : p + 3]
                steps.append({"type": "condition_check", "condition": raw[2], "raw": byte_list(raw)})
                p += 3
                continue
        if op == 0x7C and p + 1 < len(data):
            cmd = data[p + 1]
            if cmd == ord("1") and p + 2 < len(data):
                raw = data[p : p + 3]
                steps.append({"type": "fade_screen", "speed": raw[2], "raw": byte_list(raw)})
                p += 3
                continue
            if cmd == ord("B") and p + 2 < len(data):
                raw = data[p : p + 3]
                steps.append({"type": "fade_in", "speed": raw[2], "raw": byte_list(raw)})
                p += 3
                continue
            if cmd == ord("D") and p + 2 < len(data):
                raw = data[p : p + 3]
                steps.append({"type": "fade_out", "speed": raw[2], "raw": byte_list(raw)})
                p += 3
                continue
            if cmd == ord("C") and p + 6 < len(data):
                raw = data[p : p + 7]
                steps.append({
                    "type": "set_object_position",
                    "object_id": raw[2],
                    "x": raw[3],
                    "y": raw[4],
                    "frame": raw[5],
                    "direction": raw[6],
                    "raw": byte_list(raw),
                })
                p += 7
                continue
            if cmd == ord("3"):
                raw = data[p : p + 2]
                steps.append({"type": "hide_portrait", "raw": byte_list(raw)})
                p += 2
                continue
            if cmd == ord("4") and p + 3 < len(data):
                raw = data[p : p + 4]
                steps.append({"type": "swap_object_sprite", "object_id": raw[2], "sprite_id": raw[3], "raw": byte_list(raw)})
                p += 4
                continue
            if cmd == ord("5") and p + 5 < len(data):
                raw = data[p : p + 6]
                steps.append({"type": "warp", "map_id": raw[2], "state": raw[3], "connection": raw[4], "raw": byte_list(raw)})
                p += 6
                continue
            if cmd == ord("6") and p + 4 < len(data):
                raw = data[p : p + 5]
                steps.append({"type": "reaction", "reaction": raw[2], "object_mask": (raw[3] << 8) | raw[4], "raw": byte_list(raw)})
                p += 5
                continue
            if cmd == ord("9") and p + 3 < len(data):
                raw = data[p : p + 4]
                steps.append(
                    {
                        "type": "display_cg",
                        "cg_id": raw[2],
                        "fade_speed": raw[3],
                        "raw": byte_list(raw),
                    }
                )
                p += 4
                continue
            if cmd == ord("A") and p + 2 < len(data):
                raw = data[p : p + 3]
                steps.append({"type": "hide_cg", "fade_speed": raw[2], "raw": byte_list(raw)})
                p += 3
                continue
            raw_len = 3 if cmd in (ord("0"), ord("2"), ord("7"), ord("8")) else 2
            raw = data[p : min(len(data), p + raw_len)]
            steps.append({"type": f"command_7c_{chr(cmd)}", "raw": byte_list(raw)})
            p += len(raw)
            continue

        if op & 0x80:
            raw = data[p : min(len(data), p + 2)]
            text = decode_text_bytes(raw)
            append_text_step(steps, raw, text)
            p += len(raw)
        else:
            raw = [op]
            append_text_step(steps, raw, decode_text_bytes(raw))
            p += 1
    return steps, p


def decode_steps(data: list[int]) -> list[dict[str, Any]]:
    return decode_steps_with_size(data)[0]


class Extractor:
    def __init__(self, rom: Rom):
        self.rom = rom
        self.nodes: dict[int, ScriptNode] = {}
        self.visiting: set[int] = set()

    def decode_script(self, script_addr: int) -> None:
        if script_addr in self.nodes or script_addr in self.visiting or script_addr == 0:
            return
        if not self.rom.valid_addr(script_addr):
            return
        self.visiting.add(script_addr)
        start_addr = self.rom.u32(script_addr)
        false_addr = self.rom.u32(script_addr + 4)
        true_addr = self.rom.u32(script_addr + 8)
        raw = []
        steps: list[dict[str, Any]] = []
        if self.rom.valid_addr(start_addr):
            chunk = read_bytecode(self.rom, start_addr)
            steps, used = decode_steps_with_size(chunk)
            raw = chunk[:used]
        self.nodes[script_addr] = ScriptNode(script_addr, start_addr, false_addr, true_addr, raw, steps)
        self.decode_script(false_addr)
        self.decode_script(true_addr)
        self.visiting.discard(script_addr)


def node_to_yaml(node: ScriptNode) -> dict[str, Any]:
    return {
        "script_address": hexaddr(node.address),
        "start_address": hexaddr(node.start_address),
        "on_false": hexaddr(node.false_address),
        "on_true": hexaddr(node.true_address),
        "replace": False,
        "raw_bytes": byte_list(node.raw_bytes),
        "steps": node.steps,
    }


def extract_events(rom: Rom) -> dict[str, Any]:
    scenes: list[dict[str, Any]] = []
    for map_id, _array_addr, state_ptrs in map_pointer_table(rom):
        for state, map_state_addr in enumerate(state_ptrs):
            if rom.valid_addr(map_state_addr):
                scenes.append(read_map_state(rom, map_id, state, map_state_addr))

    extractor = Extractor(rom)
    for script_addr in sorted(collect_script_refs(scenes)):
        extractor.decode_script(script_addr)

    scripts = [node_to_yaml(node) for node in sorted(extractor.nodes.values(), key=lambda n: n.address)]
    return {
        "version": 1,
        "source": {
            "rom": str(rom.path),
            "language": "english",
            "map_data": hexaddr(MAP_DATA_ADDR),
        },
        "scenes": scenes,
        "scripts": scripts,
    }


def step_summary(step: dict[str, Any]) -> str:
    kind = step.get("type")
    if kind == "dialogue":
        text = re.sub(r"\s+", " ", str(step.get("text", ""))).strip()
        return f'dialogue: "{text[:100]}"'
    if kind == "portrait":
        return f"portrait p{step.get('portrait_id')} expr{step.get('expression')} pos{step.get('position')}"
    if kind == "cutscene":
        c = step.get("cutscene", {})
        return f"cutscene {c.get('id')} {c.get('name')}"
    if kind in {"move_object", "show_object", "swap_object_sprite", "reaction", "warp"}:
        details = {k: v for k, v in step.items() if k not in {"raw", "type"}}
        return f"{kind}: {details}"
    return str(kind)


def render_catalog(data: dict[str, Any]) -> str:
    scripts = {entry["script_address"]: entry for entry in data.get("scripts", [])}
    lines = [
        "# Vanilla Event Catalog",
        "",
        f"Source ROM: `{data.get('source', {}).get('rom')}`",
        "",
    ]
    for scene in data.get("scenes", []):
        label = scene.get("label") or scene["scene_id"]
        lines.extend([
            f"## {label}",
            "",
            f"- map/state: `{scene['map_id']}/{scene['state']}`",
            f"- music: `{scene.get('music')}`",
            "",
            "### Initial Sprites",
        ])
        for obj in scene.get("initial_sprites", []):
            lines.append(
                f"- obj {obj['object_id']}: sprite `{obj['sprite_id']}` at `{obj['x']},{obj['y']}` "
                f"A `{obj['script_a']}` R `{obj['script_r']}`"
            )
        lines.extend(["", "### Scripts"])
        refs = []
        for slot in scene.get("on_enter", []):
            refs.append(("enter", slot["slot"], slot.get("script")))
        for slot in scene.get("on_exit", []):
            refs.append(("exit", slot["slot"], slot.get("script")))
        for obj in scene.get("initial_sprites", []):
            refs.append((f"obj {obj['object_id']}", "A", obj.get("script_a")))
            refs.append((f"obj {obj['object_id']}", "R", obj.get("script_r")))
        seen: set[str] = set()
        for owner, slot, script_addr in refs:
            if not script_addr or script_addr in seen:
                continue
            seen.add(script_addr)
            script = scripts.get(script_addr)
            lines.append(f"- {owner} {slot}: `{script_addr}`")
            if script:
                for step in script.get("steps", [])[:50]:
                    lines.append(f"  - {step_summary(step)}")
        lines.append("")
    return "\n".join(lines)


def c_ident(addr: int) -> str:
    return f"EventScript_{addr:08X}"


def bytes_from_yaml(raw_values: list[Any]) -> list[int]:
    return [parse_hex(value) & 0xFF for value in raw_values]


def encode_text(text: str) -> list[int]:
    inverse: dict[str, tuple[int, ...]] = {}
    for raw, value in CHARMAP.items():
        if value and value not in inverse:
            inverse[value] = raw

    out: list[int] = []
    index = 0
    control_tokens = sorted(
        (token for token in inverse if token.startswith("{") and token.endswith("}")),
        key=len,
        reverse=True,
    )
    while index < len(text):
        if text.startswith("\n\n\n", index) and "\n" in inverse and "\n\n" in inverse:
            out.extend(inverse["\n"])
            out.extend(inverse["\n\n"])
            index += 3
            continue
        if text.startswith("\n\n", index) and "\n\n" in inverse:
            out.extend(inverse["\n\n"])
            index += 2
            continue
        byte_token = re.match(r"\{BYTE_([0-9A-Fa-f]{2}|[0-9A-Fa-f]{4})\}", text[index:])
        if byte_token:
            value = byte_token.group(1)
            out.extend(int(value[pos : pos + 2], 16) for pos in range(0, len(value), 2))
            index += byte_token.end()
            continue
        if text.startswith("{PLAYER}", index):
            out.extend([0x23, ord("5")])
            index += len("{PLAYER}")
            continue
        matched = False
        for token in control_tokens:
            if text.startswith(token, index):
                out.extend(inverse[token])
                index += len(token)
                matched = True
                break
        if matched:
            continue
        ch = text[index]
        if ch in inverse and len(inverse[ch]) == 1:
            out.extend(inverse[ch])
            index += 1
            continue
        if 0x20 <= ord(ch) <= 0x7E:
            out.append(ord(ch))
            index += 1
            continue
        if ch in inverse:
            out.extend(inverse[ch])
            index += 1
            continue
        raise ValueError(f"cannot encode event text character {ch!r}")
    return out


def scan_quoted_literal(text: str, start: int) -> int:
    quote = text[start]
    triple = text.startswith(quote * 3, start)
    index = start + (3 if triple else 1)
    escape = False
    while index < len(text):
        ch = text[index]
        if escape:
            escape = False
        elif ch == "\\":
            escape = True
        elif triple:
            if ch == quote and text.startswith(quote * 3, index):
                return index + 3
        elif ch == quote:
            return index + 1
        index += 1
    raise ValueError("unterminated string literal")


def strip_c_comments(text: str) -> str:
    out: list[str] = []
    index = 0
    while index < len(text):
        ch = text[index]
        next_ch = text[index + 1] if index + 1 < len(text) else ""
        if ch in {"'", '"'}:
            end = scan_quoted_literal(text, index)
            out.append(text[index:end])
            index = end
            continue
        if ch == "/" and next_ch == "/":
            while index < len(text) and text[index] != "\n":
                index += 1
            continue
        if ch == "/" and next_ch == "*":
            index += 2
            while index + 1 < len(text) and not (text[index] == "*" and text[index + 1] == "/"):
                index += 1
            index += 2
            continue
        out.append(ch)
        index += 1
    return "".join(out)


C_CONSTANTS = load_c_constants([
    ROOT / "include/overworld.h",
    ROOT / "include/constants/music_ids.h",
    ROOT / "include/constants/event_cg_generated.h",
    ROOT / "events/scripts/event_object_slots.h",
])


def load_script_constants(script_path: Path) -> dict[str, int]:
    constants = dict(C_CONSTANTS)
    constants.update(load_c_constants([script_path]))
    return constants


SPRITE_CONSTANT_NAMES = frozenset(
    name for name in C_CONSTANTS if name.startswith("SPRITE_")
)
OBJECT_SLOT_COUNT = 16
OBJECT_ID_MACROS = frozenset({
    "MOVE_OBJECT",
    "SET_OBJECT_POSITION",
    "SHOW_OBJECT",
    "WALK_OBJECT_X",
    "WALK_OBJECT_Y",
    "SLIDE_OBJECT",
})
SPRITE_IDENTIFIER_PATTERN = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


class ObjectSlotState:
    def __init__(self) -> None:
        self.slot_to_sprite: dict[int, int] = {}

    def assign(self, slot: int, sprite_id: int) -> None:
        if not 0 <= slot < OBJECT_SLOT_COUNT:
            raise ValueError(f"object slot must be 0..{OBJECT_SLOT_COUNT - 1}, got {slot}")
        self.slot_to_sprite[slot] = sprite_id

    def resolve_object_slot(
        self,
        arg: str,
        constants: dict[str, int] | None,
        path: Path,
        macro_name: str,
    ) -> int:
        name = arg.strip()
        if (
            SPRITE_IDENTIFIER_PATTERN.fullmatch(name)
            and name in SPRITE_CONSTANT_NAMES
            and (constants is None or name in constants or name in C_CONSTANTS)
        ):
            sprite_id = parse_c_value(name, constants)
            slots = sorted(
                slot for slot, bound_sprite in self.slot_to_sprite.items()
                if bound_sprite == sprite_id
            )
            if not slots:
                raise ValueError(
                    f"{path}: {macro_name} references {name} but no prior LOAD_SPRITE assigned it"
                )
            if len(slots) > 1:
                raise ValueError(
                    f"{path}: {macro_name} references {name} on multiple slots {slots}; "
                    "use an explicit slot id"
                )
            return slots[0]
        return parse_c_value(arg, constants)

    def resolve_object_mask(
        self,
        arg: str,
        constants: dict[str, int] | None,
        path: Path,
        macro_name: str,
    ) -> int:
        value = arg.strip()
        tree = ast.parse(value, mode="eval")

        def eval_node(node: ast.AST) -> int:
            if isinstance(node, ast.Expression):
                return eval_node(node.body)
            if isinstance(node, ast.Constant) and isinstance(node.value, int):
                return node.value
            if isinstance(node, ast.Name):
                if node.id in SPRITE_CONSTANT_NAMES:
                    slot = self.resolve_object_slot(node.id, constants, path, macro_name)
                    return 1 << slot
                if constants and node.id in constants:
                    return constants[node.id]
                if node.id in C_CONSTANTS:
                    return C_CONSTANTS[node.id]
                raise ValueError(f"unsupported C identifier {node.id!r}")
            if isinstance(node, ast.BinOp):
                left = eval_node(node.left)
                right = eval_node(node.right)
                if isinstance(node.op, ast.BitOr):
                    return left | right
                if isinstance(node.op, ast.BitAnd):
                    return left & right
                if isinstance(node.op, ast.BitXor):
                    return left ^ right
                if isinstance(node.op, ast.LShift):
                    return left << right
                if isinstance(node.op, ast.RShift):
                    return left >> right
                if isinstance(node.op, ast.Add):
                    return left + right
                if isinstance(node.op, ast.Sub):
                    return left - right
                raise ValueError(f"unsupported C operator {type(node.op).__name__}")
            if isinstance(node, ast.UnaryOp):
                operand = eval_node(node.operand)
                if isinstance(node.op, ast.UAdd):
                    return operand
                if isinstance(node.op, ast.USub):
                    return -operand
                if isinstance(node.op, ast.Invert):
                    return ~operand
                raise ValueError(f"unsupported C operator {type(node.op).__name__}")
            if isinstance(node, ast.Call):
                if (
                    isinstance(node.func, ast.Name)
                    and node.func.id == "OBJECT_LOCALID"
                    and len(node.args) == 1
                ):
                    return 1 << eval_node(node.args[0])
                raise ValueError(f"unsupported C expression {ast.dump(node, include_attributes=False)}")
            raise ValueError(f"unsupported C expression {ast.dump(node, include_attributes=False)}")

        try:
            return eval_node(tree)
        except SyntaxError:
            return parse_c_value(value, constants)


OVERWORLD_LOCATION_NAMES = {
    value: name for name, value in C_CONSTANTS.items() if name.startswith("LOCATION_")
}


def split_macro_args(arg_text: str) -> list[str]:
    args: list[str] = []
    start = 0
    depth = 0
    index = 0
    while index < len(arg_text):
        ch = arg_text[index]
        if ch in {"'", '"'}:
            index = scan_quoted_literal(arg_text, index)
            continue
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        elif ch == "," and depth == 0:
            args.append(arg_text[start:index].strip())
            start = index + 1
        index += 1
    tail = arg_text[start:].strip()
    if tail:
        args.append(tail)
    return args


def parse_macro_calls(text: str) -> list[tuple[str, list[str]]]:
    return [(name, args) for name, args, _start, _end in find_macro_spans(text)]


def find_macro_spans(text: str) -> list[tuple[str, list[str], int, int]]:
    spans: list[tuple[str, list[str], int, int]] = []
    index = 0
    while index < len(text):
        if index + 1 < len(text) and text[index] == "/" and text[index + 1] == "/":
            while index < len(text) and text[index] != "\n":
                index += 1
            continue
        if index + 1 < len(text) and text[index] == "/" and text[index + 1] == "*":
            index += 2
            while index + 1 < len(text) and not (text[index] == "*" and text[index + 1] == "/"):
                index += 1
            index = min(index + 2, len(text))
            continue
        if text[index] in {"'", '"'}:
            index = scan_quoted_literal(text, index)
            continue
        match = re.match(r"\b([A-Z][A-Z0-9_]*)\s*\(", text[index:])
        if not match:
            index += 1
            continue
        name = match.group(1)
        span_start = index + match.start()
        open_paren = index + match.end() - 1
        p = open_paren + 1
        depth = 1
        while p < len(text):
            ch = text[p]
            if ch in {"'", '"'}:
                p = scan_quoted_literal(text, p)
                continue
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
                if depth == 0:
                    args = split_macro_args(text[open_paren + 1 : p])
                    spans.append((name, args, span_start, p + 1))
                    break
            p += 1
        index = p + 1 if depth == 0 else index + 1
    return spans


def talk_text_indent(base_indent: str) -> str:
    return base_indent + "    "


def align_talk_text_arg(text_arg: str, text_indent: str) -> str:
    return "\n".join(
        text_indent + line.strip() for line in text_arg.splitlines() if line.strip()
    )


def align_talk_macros_in_text(text: str) -> tuple[str, int]:
    spans = find_macro_spans(text)
    replacements: list[tuple[int, int, str]] = []
    count = 0
    for name, _args, start, end in spans:
        if name != "TALK":
            continue
        macro_text = text[start:end]
        if "\n" not in macro_text:
            continue
        lines = macro_text.split("\n")
        talk_indent = re.match(r"^(\s*)", lines[0]).group(1)
        text_indent = talk_text_indent(talk_indent)
        new_lines = [lines[0]]
        for line in lines[1:-1]:
            stripped = line.strip()
            if stripped:
                new_lines.append(text_indent + stripped)
        new_lines.append(talk_indent + lines[-1].strip())
        replacement = "\n".join(new_lines)
        if replacement != macro_text:
            replacements.append((start, end, replacement))
            count += 1

    if not replacements:
        return text, 0

    out: list[str] = []
    pos = 0
    for start, end, repl in replacements:
        out.append(text[pos:start])
        out.append(repl)
        pos = end
    out.append(text[pos:])
    return "".join(out), count


def migrate_portrait_text_to_talk(text: str) -> tuple[str, int]:
    spans = find_macro_spans(text)
    replacements: list[tuple[int, int, str]] = []
    count = 0
    for i in range(len(spans) - 1):
        name1, args1, start1, end1 = spans[i]
        name2, _args2, start2, end2 = spans[i + 1]
        if name1 != "PORTRAIT" or name2 != "TEXT" or len(args1) != 3:
            continue
        if text[end1:start2].strip():
            continue
        indent_match = re.match(r"(\s*)", text[start1:])
        indent = indent_match.group(1) if indent_match else ""
        portrait_part = f"{args1[0]}, {args1[1]}, {args1[2]}"
        text_args = spans[i + 1][1]
        if len(text_args) != 1:
            continue
        text_arg = text_args[0].strip()
        if "\n" in text[start2:end2]:
            text_indent = talk_text_indent(indent)
            aligned_text = align_talk_text_arg(text_arg, text_indent)
            replacement = f"{indent}TALK({portrait_part},\n{aligned_text}\n{indent})"
        else:
            replacement = f"{indent}TALK({portrait_part}, {text_arg})"
        replacements.append((start1, end2, replacement))
        count += 1

    if not replacements:
        return text, 0

    out: list[str] = []
    pos = 0
    for start, end, repl in replacements:
        out.append(text[pos:start])
        out.append(repl)
        pos = end
    out.append(text[pos:])
    return "".join(out), count


def parse_c_value(value: str, names: dict[str, int] | None = None) -> int:
    value = value.strip()
    if len(value) >= 3 and value[0] == "'" and value[-1] == "'":
        return ord(ast.literal_eval(value))

    tree = ast.parse(value, mode="eval")

    def eval_node(node: ast.AST) -> int:
        if isinstance(node, ast.Expression):
            return eval_node(node.body)
        if isinstance(node, ast.Constant) and isinstance(node.value, int):
            return node.value
        if isinstance(node, ast.Name):
            if names and node.id in names:
                return names[node.id]
            if node.id in C_CONSTANTS:
                return C_CONSTANTS[node.id]
            raise ValueError(f"unsupported C identifier {node.id!r}")
        if isinstance(node, ast.BinOp):
            left = eval_node(node.left)
            right = eval_node(node.right)
            if isinstance(node.op, ast.BitOr):
                return left | right
            if isinstance(node.op, ast.BitAnd):
                return left & right
            if isinstance(node.op, ast.BitXor):
                return left ^ right
            if isinstance(node.op, ast.LShift):
                return left << right
            if isinstance(node.op, ast.RShift):
                return left >> right
            if isinstance(node.op, ast.Add):
                return left + right
            if isinstance(node.op, ast.Sub):
                return left - right
            raise ValueError(f"unsupported C operator {type(node.op).__name__}")
        if isinstance(node, ast.UnaryOp):
            operand = eval_node(node.operand)
            if isinstance(node.op, ast.UAdd):
                return operand
            if isinstance(node.op, ast.USub):
                return -operand
            if isinstance(node.op, ast.Invert):
                return ~operand
            raise ValueError(f"unsupported C operator {type(node.op).__name__}")
        raise ValueError(f"unsupported C expression {ast.dump(node, include_attributes=False)}")

    try:
        return eval_node(tree)
    except SyntaxError:
        if value in C_CONSTANTS:
            return C_CONSTANTS[value]
        return parse_hex(value)


def parse_text_literal(value: str) -> str:
    return ast.literal_eval("(" + textwrap.dedent(value) + ")")


def object_mask_expr(mask: int) -> str:
    if mask == 0:
        return "0"
    parts = [f"OBJECT_{bit + 1}" for bit in range(15) if mask & (1 << bit)]
    return " | ".join(parts) if parts else str(mask)


def overworld_location_expr(location: int) -> str:
    return OVERWORLD_LOCATION_NAMES.get(location, str(location))


@dataclass
class CScriptEntry:
    name: str
    script_address: int | None
    on_false: str
    on_true: str
    raw_bytes: list[int]
    map_id: int | None = None
    map_state: int | None = None


VANILLA_NOP_BRANCH = "0x08F04040"


def has_card_choice(text: str) -> bool:
    return "{CARD_1}" in text and "{CARD_2}" in text


def macro_has_card_choice(name: str, args: list[str]) -> bool:
    if name == "TEXT":
        return has_card_choice(parse_text_literal(args[0]))
    if name == "LANGUAGE_TEXT":
        return has_card_choice(parse_text_literal(args[1]))
    if name == "DIALOGUE":
        return has_card_choice(parse_text_literal(args[0]))
    if name == "TALK":
        return has_card_choice(parse_text_literal(args[3]))
    return False


def append_event_macro(
    name: str,
    args: list[str],
    raw_bytes: list[int],
    path: Path,
    constants: dict[str, int] | None = None,
    slot_state: ObjectSlotState | None = None,
) -> None:
    def need_args(count: int) -> None:
        if len(args) != count:
            raise ValueError(f"{path}: {name} expected {count} args, got {len(args)}")

    def c_value(arg: str) -> int:
        return parse_c_value(arg, constants)

    def object_slot(arg: str) -> int:
        if slot_state is None:
            return c_value(arg)
        return slot_state.resolve_object_slot(arg, constants, path, name)

    def object_slot_args(macro_args: list[str]) -> list[int]:
        if not macro_args:
            return []
        resolved = [object_slot(macro_args[0])] + [c_value(arg) for arg in macro_args[1:]]
        return [value & 0xFF for value in resolved]

    def object_mask(arg: str) -> int:
        if slot_state is None:
            return c_value(arg)
        return slot_state.resolve_object_mask(arg, constants, path, name)

    if name == "RAW":
        raw_bytes.extend(c_value(arg) & 0xFF for arg in args)
    elif name == "DIALOGUE":
        need_args(1)
        text = parse_text_literal(args[0])
        raw_bytes.extend([0x24, ord("0")])
        raw_bytes.extend(encode_text(text))
        raw_bytes.extend([0x24, ord("6")])
    elif name == "LANGUAGE_TEXT":
        need_args(2)
        raw_bytes.extend([0x24, ord("0") + c_value(args[0])])
        raw_bytes.extend(encode_text(parse_text_literal(args[1])))
    elif name == "END_LANGUAGE_TEXT":
        need_args(0)
        raw_bytes.extend([0x24, ord("6")])
    elif name == "TEXT":
        need_args(1)
        raw_bytes.extend([0x24, ord("0")])
        raw_bytes.extend(encode_text(parse_text_literal(args[0])))
        raw_bytes.extend([0x24, ord("6")])
    elif name == "TEXT_FRAGMENT":
        need_args(1)
        raw_bytes.extend(encode_text(parse_text_literal(args[0])))
    elif name == "PLAYER_NAME":
        need_args(0)
        raw_bytes.extend([0x23, ord("5")])
    elif name == "NEWLINE":
        need_args(0)
        raw_bytes.extend([0x23, ord("0")])
    elif name == "PAGE_BREAK":
        need_args(0)
        raw_bytes.extend([0x23, ord("1")])
    elif name == "CHOICE":
        need_args(0)
        raw_bytes.extend([0x23, ord("3")])
    elif name == "PORTRAIT":
        need_args(3)
        raw_bytes.extend([0x23, ord("4"), *(c_value(arg) & 0xFF for arg in args)])
    elif name == "TALK":
        need_args(4)
        raw_bytes.extend([0x23, ord("4"), *(c_value(arg) & 0xFF for arg in args[:3])])
        raw_bytes.extend([0x24, ord("0")])
        raw_bytes.extend(encode_text(parse_text_literal(args[3])))
        raw_bytes.extend([0x24, ord("6")])
    elif name in {"SET_FLAG", "CHECK_FLAG", "CLEAR_FLAG"}:
        need_args(1)
        cmd = {"SET_FLAG": "6", "CHECK_FLAG": "7", "CLEAR_FLAG": "8"}[name]
        raw_bytes.extend([0x23, ord(cmd), c_value(args[0]) & 0xFF])
    elif name == "RESTORE_LIFE_POINTS":
        need_args(0)
        raw_bytes.extend([0x23, ord("9")])
    elif name == "DUEL":
        need_args(1)
        raw_bytes.extend([0x40, ord("0"), c_value(args[0]) & 0xFF])
    elif name in {"PLAY_MUSIC", "SET_MAP_MUSIC", "STOP_MUSIC", "FADE_MUSIC"}:
        need_args(1)
        cmd = {"PLAY_MUSIC": "3", "SET_MAP_MUSIC": "4", "STOP_MUSIC": "5", "FADE_MUSIC": "6"}[name]
        music = c_value(args[0])
        raw_bytes.extend([0x40, ord(cmd), music & 0xFF, (music >> 8) & 0xFF])
    elif name == "START_MENU":
        need_args(0)
        raw_bytes.extend([0x40, ord("1")])
    elif name == "SAVE":
        need_args(0)
        raw_bytes.extend([0x40, ord("2")])
    elif name == "MOVE_OBJECT":
        need_args(4)
        raw_bytes.extend([0x40, ord("7"), *object_slot_args(args)])
    elif name == "STOP_FOOTSTEPS":
        need_args(0)
        raw_bytes.extend([0x40, ord("8")])
    elif name == "SET_OBJECT_POSITION":
        if len(args) == 4:
            raw_bytes.extend([0x40, ord("9"), *object_slot_args(args)])
        elif len(args) == 5:
            raw_bytes.extend([0x7C, ord("C"), *object_slot_args(args)])
        else:
            raise ValueError(f"{path}: {name} expected 4 or 5 args, got {len(args)}")
    elif name == "SHOW_OBJECT":
        if len(args) not in {5, 6}:
            raise ValueError(f"{path}: {name} expected 5 or 6 args, got {len(args)}")
        raw_bytes.extend([0x5E, ord("0"), *object_slot_args(args)])
    elif name in {"WALK_OBJECT_X", "WALK_OBJECT_Y"}:
        need_args(2)
        cmd = "1" if name == "WALK_OBJECT_X" else "2"
        raw_bytes.extend([0x5E, ord(cmd), *object_slot_args(args)])
    elif name == "SLIDE_OBJECT":
        need_args(3)
        raw_bytes.extend([0x5E, ord("3"), *object_slot_args(args)])
    elif name == "OBJECT_EFFECT":
        need_args(2)
        mask = object_mask(args[0])
        raw_bytes.extend([0x5E, ord("4"), (mask >> 8) & 0xFF, mask & 0xFF, c_value(args[1]) & 0xFF])
    elif name == "SPECIAL":
        need_args(1)
        raw_bytes.extend([0x5E, ord("5"), c_value(args[0]) & 0xFF])
    elif name == "CUTSCENE":
        need_args(1)
        special = {0: 15, 1: 16, 8: 33, 7: 34}[c_value(args[0])]
        raw_bytes.extend([0x5E, ord("5"), special])
    elif name == "DELAY":
        need_args(1)
        raw_bytes.extend([0x5E, ord("6"), c_value(args[0]) & 0xFF])
    elif name in {"ADD_CARD", "REMOVE_CARD"}:
        need_args(1)
        card = c_value(args[0])
        raw_bytes.extend([0x5E, ord("7" if name == "ADD_CARD" else "8"), card & 0xFF, (card >> 8) & 0xFF])
    elif name == "CONDITION_CHECK":
        need_args(1)
        raw_bytes.extend([0x5E, ord("9"), c_value(args[0]) & 0xFF])
    elif name == "FADE_SCREEN":
        need_args(1)
        raw_bytes.extend([0x7C, ord("1"), c_value(args[0]) & 0xFF])
    elif name == "FADE_IN":
        need_args(1)
        raw_bytes.extend([0x7C, ord("B"), c_value(args[0]) & 0xFF])
    elif name == "FADE_OUT":
        need_args(1)
        raw_bytes.extend([0x7C, ord("D"), c_value(args[0]) & 0xFF])
    elif name == "SCREEN_SHAKE":
        need_args(1)
        raw_bytes.extend([0x7C, ord("7"), c_value(args[0]) & 0xFF])
    elif name == "HIDE_PORTRAIT":
        need_args(0)
        raw_bytes.extend([0x7C, ord("3")])
    elif name in {"SWAP_OBJECT_SPRITE", "LOAD_SPRITE"}:
        need_args(2)
        slot = c_value(args[0])
        sprite_id = c_value(args[1])
        if slot_state is not None:
            slot_state.assign(slot, sprite_id)
        raw_bytes.extend([0x7C, ord("4"), slot & 0xFF, sprite_id & 0xFF])
    elif name == "WARP":
        if len(args) not in {3, 4}:
            raise ValueError(f"{path}: {name} expected 3 or 4 args, got {len(args)}")
        raw_bytes.extend([0x7C, ord("5"), *(c_value(arg) & 0xFF for arg in args)])
    elif name == "REACTION":
        need_args(2)
        mask = object_mask(args[1])
        raw_bytes.extend([0x7C, ord("6"), c_value(args[0]) & 0xFF, (mask >> 8) & 0xFF, mask & 0xFF])
    elif name == "COMMAND_7C_ARG":
        need_args(2)
        raw_bytes.extend([0x7C, ord("0") + c_value(args[0]), c_value(args[1]) & 0xFF])
    elif name in {"SHOW_OVERWORLD_GRAPHIC", "SHOW_LARGE_GRAPHIC"}:
        need_args(1)
        raw_bytes.extend([0x7C, ord("8"), c_value(args[0]) & 0xFF])
    elif name == "DISPLAY_CG":
        need_args(2)
        raw_bytes.extend([0x7C, ord("9"), c_value(args[0]) & 0xFF, c_value(args[1]) & 0xFF])
    elif name == "HIDE_CG":
        need_args(1)
        raw_bytes.extend([0x7C, ord("A"), c_value(args[0]) & 0xFF])
    elif name == "FALLTHROUGH":
        need_args(0)
        raw_bytes.append(0)
    elif name == "END":
        need_args(0)
        raw_bytes.append(0x5D)
    else:
        raise ValueError(f"{path}: unknown event macro {name}")


def finalize_segment_bytes(raw_bytes: list[int]) -> list[int]:
    if not raw_bytes or raw_bytes[-1] != 0:
        return raw_bytes + [0]
    return raw_bytes


MAP_SCENE_FILE_PATTERN = re.compile(r"map_(\d+)_state_(\d+)")
SCRIPT_BLOCK_MACROS = frozenset({
    "EVENT_SCRIPT_REPLACEMENT",
    "REPLACE_EVENT_SCRIPT",
    "EVENT_SCRIPT",
})


def parse_map_scene_id(map_name: str) -> tuple[int, int]:
    match = MAP_SCENE_FILE_PATTERN.fullmatch(map_name)
    if not match:
        raise ValueError(f"scene name must be map_NN_state_MM, got {map_name!r}")
    return int(match.group(1)), int(match.group(2))


def is_map_scene_file(path: Path) -> bool:
    return MAP_SCENE_FILE_PATTERN.fullmatch(path.stem) is not None


def compile_linear_map_event(
    map_name: str,
    calls: list[tuple[str, list[str]]],
    path: Path,
    constants: dict[str, int] | None = None,
) -> CScriptEntry:
    raw_bytes: list[int] = []
    slot_state = ObjectSlotState()
    for name, args in calls:
        if name in {
            "MAP_EVENT",
            "END_MAP_EVENT",
            "HOOK",
            "END_HOOK",
            "BRANCH",
            "END_BRANCH",
            "JOIN",
            "MERGE",
            "END_MERGE",
        }:
            raise ValueError(f"{path}: map enter script {map_name} uses legacy wrapper/branch macros")
        append_event_macro(name, args, raw_bytes, path, constants, slot_state)
    map_id, map_state = parse_map_scene_id(map_name)
    return CScriptEntry(
        map_name,
        None,
        VANILLA_NOP_BRANCH,
        VANILLA_NOP_BRANCH,
        finalize_segment_bytes(raw_bytes),
        map_id,
        map_state,
    )


def parse_map_scene_enter_calls(
    calls: list[tuple[str, list[str]]],
    path: Path,
) -> tuple[list[tuple[str, list[str]]], int]:
    index = 0
    enter_calls: list[tuple[str, list[str]]] = []

    if index < len(calls) and calls[index][0] == "MAP_EVENT":
        map_name, args = calls[index]
        if len(args) != 1:
            raise ValueError(f"{path}: MAP_EVENT expected 1 arg, got {len(args)}")
        if map_name != path.stem:
            raise ValueError(f"{path}: MAP_EVENT({map_name}) must match filename {path.stem}")
        index += 1
        depth = 1
        while index < len(calls) and depth > 0:
            inner_name, inner_args = calls[index]
            if inner_name == "MAP_EVENT":
                depth += 1
            elif inner_name == "END_MAP_EVENT":
                depth -= 1
                if depth == 0:
                    index += 1
                    break
            if depth > 0:
                enter_calls.append((inner_name, inner_args))
            index += 1
        else:
            raise ValueError(f"{path}: unclosed MAP_EVENT {map_name}")
        return enter_calls, index

    while index < len(calls) and calls[index][0] not in SCRIPT_BLOCK_MACROS:
        enter_calls.append(calls[index])
        index += 1
    return enter_calls, index


def parse_event_c_sources(paths: list[Path]) -> list[CScriptEntry]:
    entries: list[CScriptEntry] = []
    current: CScriptEntry | None = None

    def need_args(name: str, args: list[str], count: int, path: Path) -> None:
        if len(args) != count:
            raise ValueError(f"{path}: {name} expected {count} args, got {len(args)}")

    for path in paths:
        script_constants = load_script_constants(path)
        calls = parse_macro_calls(path.read_text())
        call_index = 0
        slot_state: ObjectSlotState | None = None

        if is_map_scene_file(path):
            enter_calls, call_index = parse_map_scene_enter_calls(calls, path)
            if enter_calls:
                entries.append(compile_linear_map_event(path.stem, enter_calls, path, script_constants))

        while call_index < len(calls):
            name, args = calls[call_index]
            if name in {"MAP_EVENT", "END_MAP_EVENT"}:
                raise ValueError(f"{path}: stray {name} after map enter script")

            if name in {"EVENT_SCRIPT_REPLACEMENT", "REPLACE_EVENT_SCRIPT"}:
                need_args(name, args, 4, path)
                if current is not None:
                    raise ValueError(f"{path}: nested {name}")
                current = CScriptEntry(args[1], parse_hex(args[0]), args[2], args[3], [])
                slot_state = ObjectSlotState()
                call_index += 1
                continue
            if name == "EVENT_SCRIPT":
                need_args(name, args, 3, path)
                if current is not None:
                    raise ValueError(f"{path}: nested {name}")
                current = CScriptEntry(args[0], None, args[1], args[2], [])
                slot_state = ObjectSlotState()
                call_index += 1
                continue
            if name == "END_EVENT_SCRIPT":
                need_args(name, args, 0, path)
                if current is None:
                    raise ValueError(f"{path}: END_EVENT_SCRIPT without script")
                entries.append(current)
                current = None
                slot_state = None
                call_index += 1
                continue
            if current is None:
                call_index += 1
                continue

            append_event_macro(name, args, current.raw_bytes, path, script_constants, slot_state)
            call_index += 1
        if current is not None:
            raise ValueError(f"{path}: unclosed event script {current.name}")
    return entries


DEFAULT_STORY_SEQUENCE_PATH = Path("events/story_sequence.txt")
VANILLA_NOP_ENTER_ADDRS = {0x08F04034, 0x08F04040}


STORY_START_LINE_PATTERN = re.compile(
    r"^@start\s+(map_\d+_state_\d+)(?:\s+(\d+))?\s*$",
    re.IGNORECASE,
)

CATALOG_REFERENCE_LINE_PATTERN = re.compile(
    r"^#\s*map_\d+_state_\d+\s+#\s*map \d+/\d+ enter=",
)

TECHNICAL_SCENE_COMMENT_PATTERN = re.compile(
    r"map \d+/\d+ enter=0x[0-9A-Fa-f]{8} \((?:noop|vanilla-event)\)",
)

STORY_SEQUENCE_HEADER_LINES = [
    "# Game event play order — uncomment a scene to enable its custom map enter script.",
    "# Commented scenes run no map enter event; vanilla cutscenes are never loaded.",
    "# New-game warp: @start <scene_name> <connection> (must match the first active scene).",
    "# Generated from events/vanilla/vanilla_event_catalog.md — refresh with:",
    "#   python3 tools/vanilla_events.py generate-story-skeleton",
]


@dataclass(frozen=True)
class StoryStartWarp:
    scene_name: str
    connection: int


@dataclass(frozen=True)
class StorySequenceFile:
    preamble: list[str]
    story_section: list[str] | None
    catalog_section: list[str] | None


def parse_story_start_warp(sequence_path: Path) -> StoryStartWarp | None:
    if not sequence_path.is_file():
        return None
    for line in sequence_path.read_text().splitlines():
        stripped = line.split("#", 1)[0].strip()
        if not stripped:
            continue
        match = STORY_START_LINE_PATTERN.match(stripped)
        if match:
            connection = int(match.group(2)) if match.group(2) is not None else 0
            return StoryStartWarp(match.group(1), connection)
    return None


def parse_story_sequence_names(sequence_path: Path) -> list[str]:
    if not sequence_path.is_file():
        return []
    names: list[str] = []
    for line in sequence_path.read_text().splitlines():
        line = line.split("#", 1)[0].strip()
        if not line or line.startswith("@start"):
            continue
        parse_map_scene_id(line)
        names.append(line)
    return names


def parse_story_sequence_catalog_names(sequence_path: Path) -> list[str]:
    if not sequence_path.is_file():
        return []
    names: list[str] = []
    for line in sequence_path.read_text().splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("# Generated") or stripped.startswith("# Game event") or stripped.startswith("# New-game"):
            continue
        if stripped.startswith("#"):
            match = MAP_SCENE_FILE_PATTERN.search(stripped)
            if match:
                names.append(match.group(0))
            continue
        name = stripped.split("#", 1)[0].strip()
        if not name or name.startswith("@start"):
            continue
        parse_map_scene_id(name)
        names.append(name)
    return names


def story_sequence_uses_catalog_mode(sequence_path: Path) -> bool:
    return bool(parse_story_sequence_catalog_names(sequence_path))


def compile_story_start_section(
    sequence_path: Path,
    map_event_entries: list[CScriptEntry],
) -> list[str]:
    start = parse_story_start_warp(sequence_path)
    if start is None:
        return [
            "const u8 gStoryStartConfigured APPEND_RODATA = 0;",
            "const u8 gStoryStartMapId APPEND_RODATA = 0;",
            "const u8 gStoryStartMapState APPEND_RODATA = 0;",
            "const u8 gStoryStartMapConnection APPEND_RODATA = 0;",
            "",
        ]

    map_event_by_name = {
        entry.name: entry for entry in map_event_entries if entry.map_id is not None
    }
    entry = map_event_by_name.get(start.scene_name)
    if entry is None:
        raise ValueError(
            f"{sequence_path}: @start scene {start.scene_name!r} has no map enter script"
        )
    return [
        "const u8 gStoryStartConfigured APPEND_RODATA = 1;",
        f"const u8 gStoryStartMapId APPEND_RODATA = {entry.map_id};",
        f"const u8 gStoryStartMapState APPEND_RODATA = {entry.map_state};",
        f"const u8 gStoryStartMapConnection APPEND_RODATA = {start.connection};",
        "",
    ]


def compile_story_sequence_section(
    sequence_path: Path,
    map_event_entries: list[CScriptEntry],
    script_ident,
) -> list[str]:
    sequence_names = parse_story_sequence_names(sequence_path)
    map_event_by_name = {entry.name: entry for entry in map_event_entries}
    lines: list[str] = [
        "const StorySequenceEntry gStorySequence[] APPEND_RODATA = {",
    ]
    if not sequence_names:
        lines.extend([
            "  {0, 0, 0},",
            "};",
            "const unsigned gStorySequenceCount APPEND_RODATA = 0;",
            "",
        ])
        return lines

    for name in sequence_names:
        entry = map_event_by_name.get(name)
        if entry is None:
            raise ValueError(
                f"{sequence_path}: story scene {name!r} has no map enter script "
                f"(add event macros at the top of events/scripts/{name}.c)"
            )
        lines.append(
            f"  {{{entry.map_id}, {entry.map_state}, "
            f"&sEventScript_{script_ident(entry)}Node}},"
        )
    lines.extend([
        "};",
        f"const unsigned gStorySequenceCount APPEND_RODATA = {len(sequence_names)};",
        "",
    ])
    return lines


def compile_c_replacements(paths: list[Path]) -> str:
    entries = parse_event_c_sources(paths)
    replacement_entries = [entry for entry in entries if entry.script_address is not None]
    names = [entry.name for entry in entries]
    if len(names) != len(set(names)):
        duplicate = next(name for name in names if names.count(name) > 1)
        raise ValueError(f"duplicate event script name {duplicate}")
    name_to_entry = {entry.name: entry for entry in entries}
    vanilla_to_entry = {entry.script_address: entry for entry in replacement_entries}

    def script_ident(entry: CScriptEntry) -> str:
        return re.sub(r"[^A-Za-z0-9_]", "_", entry.name)

    def branch_expr(value: str) -> str:
        value = value.strip()
        if value in {"0", "NULL", "nullptr"}:
            return "(struct Script *)0"
        if value in name_to_entry:
            return f"&sEventScript_{script_ident(name_to_entry[value])}Node"
        addr = parse_hex(value)
        if addr in vanilla_to_entry:
            return f"&sEventScript_{script_ident(vanilla_to_entry[addr])}Node"
        return f"(struct Script *)0x{addr:08X}"

    lines = ["/* Auto-generated by tools/vanilla_events.py. */", ""]
    if not replacement_entries:
        lines.extend([
            "const EventScriptReplacement gEventScriptReplacements[] APPEND_RODATA = {",
            "  {0, 0},",
            "};",
            "const unsigned gEventScriptReplacementCount APPEND_RODATA = 0;",
            "",
        ])
        return "\n".join(lines)

    for entry in entries:
        values = ", ".join(f"0x{value:02X}" for value in entry.raw_bytes)
        lines.append(f"static const u8 sEventScript_{script_ident(entry)}Bytes[] APPEND_TEXT = {{{values}}};")
    lines.append("")
    for entry in entries:
        lines.append(f"static struct Script sEventScript_{script_ident(entry)}Node;")
    lines.append("")
    for entry in entries:
        lines.append(
            f"static struct Script sEventScript_{script_ident(entry)}Node APPEND_RODATA = "
            f"{{(u8 *)sEventScript_{script_ident(entry)}Bytes, {branch_expr(entry.on_false)}, {branch_expr(entry.on_true)}}};"
        )
    lines.extend(["", "const EventScriptReplacement gEventScriptReplacements[] APPEND_RODATA = {"])
    for entry in replacement_entries:
        lines.append(f"  {{(const struct Script *)0x{entry.script_address:08X}, &sEventScript_{script_ident(entry)}Node}},")
    lines.extend([
        "};",
        f"const unsigned gEventScriptReplacementCount APPEND_RODATA = {len(replacement_entries)};",
        "",
    ])
    return "\n".join(lines)


def parse_catalog_enter_scripts(catalog_path: Path) -> dict[str, int]:
    return {scene.scene_id: scene.enter_addr for scene in parse_catalog_scenes(catalog_path)}


@dataclass
class CatalogScene:
    scene_id: str
    map_id: int
    map_state: int
    enter_addr: int


def parse_catalog_scenes(catalog_path: Path) -> list[CatalogScene]:
    scenes: list[CatalogScene] = []
    scene_id: str | None = None
    map_id: int | None = None
    map_state: int | None = None
    enter_addr: int | None = None

    def flush() -> None:
        nonlocal scene_id, map_id, map_state, enter_addr
        if scene_id is None or map_id is None or map_state is None or enter_addr is None:
            return
        scenes.append(CatalogScene(scene_id, map_id, map_state, enter_addr))
        scene_id = map_id = map_state = enter_addr = None

    for line in catalog_path.read_text().splitlines():
        if line.startswith("## map_"):
            flush()
            scene_id = line[3:].strip()
            continue
        if scene_id is None:
            continue
        if line.startswith("- map/state:"):
            match = re.search(r"`(\d+)/(\d+)`", line)
            if match:
                map_id = int(match.group(1))
                map_state = int(match.group(2))
        elif line.startswith("- enter 0:"):
            match = re.search(r"`(0x[0-9A-Fa-f]+)`", line)
            if match:
                enter_addr = parse_hex(match.group(1))
    flush()
    return scenes


SCENE_SKELETON_TEMPLATE = """#include "event_macros.h"
#include "overworld.h"

/* {scene_id}: map {map_id} state {map_state} — skeleton (vanilla enter 0x{enter_addr:08X}) */

END()
"""


def scene_line_comment_suffix(comment: str | None, scene: CatalogScene) -> str:
    if comment and not TECHNICAL_SCENE_COMMENT_PATTERN.search(comment):
        return f"  # {comment}"
    tag = "noop" if scene.enter_addr in VANILLA_NOP_ENTER_ADDRS else "vanilla-event"
    return (
        f"  # map {scene.map_id}/{scene.map_state} "
        f"enter=0x{scene.enter_addr:08X} ({tag})"
    )


def parse_story_sequence_scene_comments(sequence_path: Path) -> dict[str, str]:
    if not sequence_path.is_file():
        return {}
    comments: dict[str, str] = {}
    for line in sequence_path.read_text().splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("@start"):
            continue
        active = not stripped.startswith("#")
        body = stripped[1:].strip() if not active else stripped
        match = MAP_SCENE_FILE_PATTERN.match(body.split("#", 1)[0].split("-", 1)[0].strip())
        if not match:
            continue
        scene_id = match.group(0)
        comment_part = ""
        if "#" in body:
            comment_part = body.split("#", 1)[1].strip()
        elif " - " in body:
            comment_part = body.split(" - ", 1)[1].strip()
        if comment_part and not TECHNICAL_SCENE_COMMENT_PATTERN.search(comment_part):
            comments[scene_id] = comment_part
    return comments


def parse_story_sequence_file(sequence_path: Path) -> StorySequenceFile | None:
    if not sequence_path.is_file():
        return None
    lines = sequence_path.read_text().splitlines()
    catalog_start = next(
        (index for index, line in enumerate(lines) if CATALOG_REFERENCE_LINE_PATTERN.match(line.strip())),
        None,
    )
    if catalog_start is None:
        return None

    pre_catalog = lines[:catalog_start]
    while pre_catalog and not pre_catalog[-1].strip():
        pre_catalog.pop()

    preamble: list[str] = []
    story_section: list[str] = []
    in_header = True
    for line in pre_catalog:
        stripped = line.strip()
        if in_header:
            if (
                stripped.startswith("# Game event")
                or stripped.startswith("# Commented scenes")
                or stripped.startswith("# New-game warp")
                or stripped.startswith("# Generated from")
                or stripped.startswith("#   python3 tools/vanilla_events.py generate-story-skeleton")
            ):
                preamble.append(line)
                continue
            if stripped.startswith("@start"):
                preamble.append(line)
                continue
            if not stripped:
                preamble.append(line)
                continue
            in_header = False
        story_section.append(line)

    if not story_section:
        return None
    return StorySequenceFile(
        preamble=preamble or list(STORY_SEQUENCE_HEADER_LINES) + [""],
        story_section=story_section,
        catalog_section=lines[catalog_start:],
    )


def render_catalog_reference_lines(scenes: list[CatalogScene]) -> list[str]:
    lines: list[str] = []
    for scene in scenes:
        tag = "noop" if scene.enter_addr in VANILLA_NOP_ENTER_ADDRS else "vanilla-event"
        lines.append(
            f"# {scene.scene_id}  # map {scene.map_id}/{scene.map_state} "
            f"enter=0x{scene.enter_addr:08X} ({tag})"
        )
    return lines


def render_story_sequence_text(
    scenes: list[CatalogScene],
    active_names: set[str],
    existing_start: StoryStartWarp | None = None,
    scene_comments: dict[str, str] | None = None,
) -> str:
    comments = scene_comments or {}
    lines = list(STORY_SEQUENCE_HEADER_LINES)
    lines.append("")
    if existing_start is not None:
        lines.append(f"@start {existing_start.scene_name} {existing_start.connection}")
        lines.append("")
    elif active_names:
        first_active = next(
            (scene.scene_id for scene in scenes if scene.scene_id in active_names),
            None,
        )
        if first_active is not None:
            lines.append(f"@start {first_active} 0")
            lines.append("")
    for scene in scenes:
        suffix = scene_line_comment_suffix(comments.get(scene.scene_id), scene)
        if scene.scene_id in active_names:
            lines.append(f"{scene.scene_id}{suffix}")
        else:
            lines.append(f"# {scene.scene_id}{suffix}")
    return "\n".join(lines) + "\n"


def render_story_sequence_dual(
    scenes: list[CatalogScene],
    existing: StorySequenceFile,
) -> str:
    lines = list(existing.preamble)
    if lines and lines[-1].strip():
        lines.append("")
    lines.extend(existing.story_section or [])
    lines.append("")
    lines.append("")
    lines.extend(render_catalog_reference_lines(scenes))
    return "\n".join(lines) + "\n"


def generate_story_skeleton_files(
    scenes: list[CatalogScene],
    scripts_dir: Path,
) -> list[str]:
    created: list[str] = []
    for scene in scenes:
        path = scripts_dir / f"{scene.scene_id}.c"
        if path.is_file():
            continue
        path.write_text(
            SCENE_SKELETON_TEMPLATE.format(
                scene_id=scene.scene_id,
                map_id=scene.map_id,
                map_state=scene.map_state,
                enter_addr=scene.enter_addr,
            )
        )
        created.append(str(path))
    return created


def generate_story_skeleton(
    catalog_path: Path,
    scripts_dir: Path,
    sequence_path: Path,
    preserve_active: bool = True,
) -> tuple[list[str], str]:
    scenes = parse_catalog_scenes(catalog_path)
    if not scenes:
        raise ValueError(f"no scenes found in {catalog_path}")
    existing_file = parse_story_sequence_file(sequence_path)
    active_names = set(parse_story_sequence_names(sequence_path)) if preserve_active else set()
    existing_start = parse_story_start_warp(sequence_path) if preserve_active else None
    scene_comments = (
        parse_story_sequence_scene_comments(sequence_path) if preserve_active else {}
    )
    created = generate_story_skeleton_files(scenes, scripts_dir)
    if existing_file is not None and preserve_active:
        sequence_text = render_story_sequence_dual(scenes, existing_file)
    else:
        sequence_text = render_story_sequence_text(
            scenes,
            active_names,
            existing_start,
            scene_comments,
        )
    sequence_path.write_text(sequence_text)
    return created, sequence_text


def cmd_generate_story_skeleton(args: argparse.Namespace) -> None:
    catalog_path = Path(args.catalog)
    scripts_dir = Path(args.scripts_dir)
    sequence_path = Path(args.sequence)
    created, _ = generate_story_skeleton(
        catalog_path,
        scripts_dir,
        sequence_path,
        preserve_active=not args.reset_active,
    )
    for path in created:
        print(f"created {path}")
    print(f"created {len(created)} skeleton file(s)")
    print(f"wrote {sequence_path} ({len(parse_catalog_scenes(catalog_path))} scenes)")


@dataclass
class EventScriptBlockSource:
    script_address: int
    name: str
    on_false: str
    on_true: str
    body: str
    macros: list[tuple[str, list[str]]]


def extract_event_replacement_blocks(text: str) -> list[EventScriptBlockSource]:
    blocks: list[EventScriptBlockSource] = []
    index = 0
    while index < len(text):
        match = re.search(r"\bEVENT_SCRIPT_REPLACEMENT\s*\(", text[index:])
        if not match:
            break
        header_start = index + match.start()
        open_paren = index + match.end() - 1
        depth = 1
        cursor = open_paren + 1
        while cursor < len(text) and depth:
            ch = text[cursor]
            if ch in {"'", '"'}:
                cursor = scan_quoted_literal(text, cursor)
                continue
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
            cursor += 1
        header_end = cursor
        args = split_macro_args(text[open_paren + 1 : header_end - 1])
        if len(args) != 4:
            raise ValueError(f"EVENT_SCRIPT_REPLACEMENT expected 4 args near offset {header_start}")
        end_match = re.search(r"\bEND_EVENT_SCRIPT\s*\(\s*\)", text[header_end:])
        if not end_match:
            raise ValueError(f"unclosed EVENT_SCRIPT_REPLACEMENT near offset {header_start}")
        body = text[header_end : header_end + end_match.start()].strip()
        blocks.append(
            EventScriptBlockSource(
                parse_hex(args[0]),
                args[1],
                args[2],
                args[3],
                body,
                parse_macro_calls(body),
            )
        )
        index = header_end + end_match.end()
    return blocks


def resolve_event_block(
    ref: str,
    by_addr: dict[int, EventScriptBlockSource],
    by_name: dict[str, EventScriptBlockSource],
) -> EventScriptBlockSource | None:
    ref = ref.strip()
    if ref in {"0", "NULL", "nullptr"}:
        return None
    if ref in by_name:
        return by_name[ref]
    try:
        addr = parse_hex(ref)
    except ValueError:
        return None
    if addr == parse_hex(VANILLA_NOP_BRANCH):
        return None
    return by_addr.get(addr)


def strip_trailing_fallthrough(body: str) -> str:
    return re.sub(r"\s*FALLTHROUGH\s*\(\s*\)\s*$", "", body).strip()


def body_without_choice_macros(body: str) -> tuple[str, bool]:
    macros = parse_macro_calls(body)
    if not macros:
        return body.strip(), False
    had_choice = False
    parts: list[str] = []
    cursor = 0
    clean = strip_c_comments(body)
    macro_index = 0
    while macro_index < len(macros):
        name, args = macros[macro_index]
        match = re.search(rf"\b{re.escape(name)}\s*\(", clean[cursor:])
        if not match:
            macro_index += 1
            continue
        macro_start = cursor + match.start()
        open_paren = cursor + match.end() - 1
        depth = 1
        pos = open_paren + 1
        while pos < len(clean) and depth:
            ch = clean[pos]
            if ch in {"'", '"'}:
                pos = scan_quoted_literal(clean, pos)
                continue
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
            pos += 1
        macro_end = pos
        if macro_has_card_choice(name, args):
            had_choice = True
        else:
            parts.append(body[macro_start:macro_end].strip())
        cursor = macro_end
        macro_index += 1
    return "\n  ".join(part for part in parts if part), had_choice


def linearize_enter_script(
    enter: EventScriptBlockSource,
    by_addr: dict[int, EventScriptBlockSource],
    by_name: dict[str, EventScriptBlockSource],
) -> tuple[set[int], str]:
    absorbed: set[int] = set()
    body_parts: list[str] = []
    current: EventScriptBlockSource | None = enter
    while current is not None and current.script_address not in absorbed:
        absorbed.add(current.script_address)
        segment, had_choice = body_without_choice_macros(current.body)
        segment = strip_trailing_fallthrough(segment)
        if segment:
            body_parts.append(segment)
        if had_choice:
            current = resolve_event_block(current.on_false, by_addr, by_name)
            continue
        current = resolve_event_block(current.on_false, by_addr, by_name)
    return absorbed, "\n  ".join(body_parts)


def file_header(text: str) -> str:
    match = re.search(r"\b(?:EVENT_SCRIPT_REPLACEMENT|REPLACE_EVENT_SCRIPT|EVENT_SCRIPT)\s*\(", text)
    if match:
        return text[: match.start()].rstrip()
    return text.rstrip()


def strip_map_event_wrapper(text: str, scene_id: str) -> str:
    pattern = re.compile(
        rf"MAP_EVENT\s*\(\s*{re.escape(scene_id)}\s*\)\s*\n(.*?)\nEND_MAP_EVENT\s*\(\s*\)",
        re.DOTALL,
    )
    match = pattern.search(text)
    if not match:
        return text
    body = match.group(1)
    body_lines = body.splitlines()
    if body_lines and all(not line.strip() or line.startswith("  ") for line in body_lines):
        body = "\n".join(line[2:] if line.startswith("  ") else line for line in body_lines)
    return text[: match.start()] + body + text[match.end() :]


def normalize_map_scene_file(text: str) -> str:
    text = re.sub(
        r"(/\* map_\d+_state_\d+:[^\n]*\*/\s*\n\s*){2,}",
        lambda match: match.group(0).split("\n\n")[0] + "\n\n",
        text,
        count=1,
    )
    lines = text.splitlines()
    split_at = len(lines)
    for index, line in enumerate(lines):
        if re.match(r"\s*(?:EVENT_SCRIPT_REPLACEMENT|REPLACE_EVENT_SCRIPT|EVENT_SCRIPT)\s*\(", line):
            split_at = index
            break
    enter = lines[:split_at]
    rest = lines[split_at:]
    enter = [line[2:] if line.startswith("  ") else line for line in enter]
    return "\n".join(enter + rest).rstrip() + "\n"


def convert_map_event_source(path: Path, enter_scripts: dict[str, int]) -> str | None:
    text = path.read_text()
    scene_id = path.stem
    if not is_map_scene_file(path):
        return None
    if "MAP_EVENT(" in text:
        return None
    blocks = extract_event_replacement_blocks(text)
    if not blocks:
        return None
    enter_addr = enter_scripts.get(scene_id)
    if enter_addr is None or enter_addr not in {block.script_address for block in blocks}:
        return None

    by_addr = {block.script_address: block for block in blocks}
    by_name = {block.name: block for block in blocks}
    absorbed, linear_body = linearize_enter_script(by_addr[enter_addr], by_addr, by_name)
    remaining = [block for block in blocks if block.script_address not in absorbed]

    comment_match = re.search(r"/\* map_\d+_state_\d+:[^*]*\*/", text)
    comment = comment_match.group(0) if comment_match else f"/* {scene_id} */"

    out_lines = [
        file_header(text),
        "",
        comment,
        "",
        linear_body,
        "",
    ]
    for block in remaining:
        out_lines.extend(
            [
                f"EVENT_SCRIPT_REPLACEMENT(0x{block.script_address:08X}, {block.name}, {block.on_false}, {block.on_true})",
                block.body,
                "END_EVENT_SCRIPT()",
                "",
            ]
        )
    return normalize_map_scene_file("\n".join(out_lines).rstrip() + "\n")


OBJECT_MASK_OBJECT_PATTERN = re.compile(r"^OBJECT_(\d+)$")
OBJECT_MASK_LSHIFT_PATTERN = re.compile(r"^\(\s*1\s*<<\s*(.+?)\s*\)$")


def _sprite_name_for_slot(
    slot: int,
    slot_to_sprite_name: dict[int, str],
) -> str | None:
    sprite_name = slot_to_sprite_name.get(slot)
    if sprite_name is None:
        return None
    if sum(1 for name in slot_to_sprite_name.values() if name == sprite_name) != 1:
        return None
    return sprite_name


def _slot_from_object_id_arg(arg: str, constants: dict[str, int]) -> int | None:
    value = arg.strip()
    if value.startswith("SPRITE_"):
        return None
    try:
        slot = parse_c_value(value, constants)
    except ValueError:
        return None
    if 0 <= slot < OBJECT_SLOT_COUNT:
        return slot
    return None


def _rewrite_object_id_arg(
    arg: str,
    slot_to_sprite_name: dict[int, str],
    constants: dict[str, int],
) -> str:
    slot = _slot_from_object_id_arg(arg, constants)
    if slot is None:
        return arg
    sprite_name = _sprite_name_for_slot(slot, slot_to_sprite_name)
    return sprite_name if sprite_name is not None else arg


def _split_mask_terms(mask: str) -> list[str]:
    terms: list[str] = []
    start = 0
    depth = 0
    index = 0
    while index < len(mask):
        ch = mask[index]
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        elif ch == "|" and depth == 0:
            terms.append(mask[start:index].strip())
            start = index + 1
        index += 1
    tail = mask[start:].strip()
    if tail:
        terms.append(tail)
    return terms


def _rewrite_mask_term(
    term: str,
    slot_to_sprite_name: dict[int, str],
    constants: dict[str, int],
) -> str:
    value = term.strip()
    if value.startswith("SPRITE_"):
        return value

    object_match = OBJECT_MASK_OBJECT_PATTERN.fullmatch(value)
    if object_match is not None:
        slot = int(object_match.group(1))
        sprite_name = _sprite_name_for_slot(slot, slot_to_sprite_name)
        return sprite_name if sprite_name is not None else value

    lshift_match = OBJECT_MASK_LSHIFT_PATTERN.fullmatch(value)
    if lshift_match is not None:
        slot = parse_c_value(lshift_match.group(1).strip(), constants)
        if 0 <= slot < OBJECT_SLOT_COUNT:
            sprite_name = _sprite_name_for_slot(slot, slot_to_sprite_name)
            return sprite_name if sprite_name is not None else value

    slot = _slot_from_object_id_arg(value, constants)
    if slot is not None:
        sprite_name = _sprite_name_for_slot(slot, slot_to_sprite_name)
        return sprite_name if sprite_name is not None else value

    return value


def _rewrite_mask_arg(
    arg: str,
    slot_to_sprite_name: dict[int, str],
    constants: dict[str, int],
) -> str:
    terms = _split_mask_terms(arg)
    if not terms:
        return arg
    rewritten = [
        _rewrite_mask_term(term, slot_to_sprite_name, constants)
        for term in terms
    ]
    if rewritten == terms:
        return arg
    return " | ".join(rewritten)


def _format_macro_call(name: str, args: list[str]) -> str:
    if not args:
        return f"{name}()"
    return f"{name}({', '.join(args)})"


def _reset_sprite_slot_tracking() -> tuple[ObjectSlotState, dict[int, str]]:
    return ObjectSlotState(), {}


def migrate_sprite_refs_in_text(text: str, constants: dict[str, int]) -> tuple[str, int]:
    spans = find_macro_spans(text)
    replacements: list[tuple[int, int, str]] = []
    slot_state, slot_to_sprite_name = _reset_sprite_slot_tracking()
    changes = 0

    for name, args, start, end in spans:
        if name in {"EVENT_SCRIPT_REPLACEMENT", "REPLACE_EVENT_SCRIPT", "EVENT_SCRIPT"}:
            slot_state, slot_to_sprite_name = _reset_sprite_slot_tracking()
            continue
        if name == "END_EVENT_SCRIPT":
            slot_state, slot_to_sprite_name = _reset_sprite_slot_tracking()
            continue

        new_args = list(args)
        changed = False

        if name in {"LOAD_SPRITE", "SWAP_OBJECT_SPRITE"} and len(new_args) == 2:
            slot_arg = new_args[0].strip()
            sprite_arg = new_args[1].strip()
            if slot_arg == "0":
                new_args[0] = "SLOT_PLAYER"
                changed = True
            slot = parse_c_value(new_args[0], constants)
            sprite_id = parse_c_value(sprite_arg, constants)
            slot_state.assign(slot, sprite_id)
            slot_to_sprite_name[slot] = sprite_arg

        elif name in OBJECT_ID_MACROS and new_args:
            rewritten = _rewrite_object_id_arg(new_args[0], slot_to_sprite_name, constants)
            if rewritten != new_args[0]:
                new_args[0] = rewritten
                changed = True

        elif name == "REACTION" and len(new_args) >= 2:
            rewritten = _rewrite_mask_arg(new_args[1], slot_to_sprite_name, constants)
            if rewritten != new_args[1]:
                new_args[1] = rewritten
                changed = True

        elif name == "OBJECT_EFFECT" and new_args:
            rewritten = _rewrite_mask_arg(new_args[0], slot_to_sprite_name, constants)
            if rewritten != new_args[0]:
                new_args[0] = rewritten
                changed = True

        if changed:
            replacements.append((start, end, _format_macro_call(name, new_args)))
            changes += 1

    if not replacements:
        return text, 0

    out: list[str] = []
    pos = 0
    for start, end, repl in replacements:
        out.append(text[pos:start])
        out.append(repl)
        pos = end
    out.append(text[pos:])
    return "".join(out), changes


def ensure_object_slots_include(text: str) -> str:
    if "event_object_slots.h" in text:
        return text
    if "SLOT_PLAYER" not in text:
        return text
    marker = '#include "event_macros.h"\n'
    if marker not in text:
        return text
    return text.replace(
        marker,
        marker + '#include "event_object_slots.h"\n',
        1,
    )


def migrate_sprite_refs_in_file(path: Path) -> int:
    constants = load_script_constants(path)
    original = path.read_text()
    migrated, changes = migrate_sprite_refs_in_text(original, constants)
    migrated = ensure_object_slots_include(migrated)
    if migrated != original:
        path.write_text(migrated)
    return changes


def migrate_sprite_refs_in_dir(scripts_dir: Path) -> list[tuple[str, int]]:
    results: list[tuple[str, int]] = []
    for path in sorted(scripts_dir.glob("map_*_state_*.c")):
        changes = migrate_sprite_refs_in_file(path)
        if changes:
            results.append((str(path), changes))
    return results


def cmd_migrate_sprite_refs(args: argparse.Namespace) -> None:
    scripts_dir = Path(args.scripts_dir)
    results = migrate_sprite_refs_in_dir(scripts_dir)
    total = sum(changes for _, changes in results)
    for path, changes in results:
        print(f"migrated {changes} macro(s) in {path}")
    print(f"migrated {total} macro(s) across {len(results)} file(s)")


def migrate_map_event_files(scripts_dir: Path, catalog_path: Path) -> list[str]:
    enter_scripts = parse_catalog_enter_scripts(catalog_path)
    changed: list[str] = []
    for path in sorted(scripts_dir.glob("map_*_state_*.c")):
        converted = convert_map_event_source(path, enter_scripts)
        if converted is not None:
            if converted != path.read_text():
                path.write_text(converted)
                changed.append(str(path))
            continue
        if "MAP_EVENT(" in path.read_text():
            normalized = strip_map_event_wrapper(path.read_text(), path.stem)
            normalized = normalize_map_scene_file(normalized)
            if normalized != path.read_text():
                path.write_text(normalized)
                changed.append(str(path))
    return changed


def strip_all_map_event_wrappers(scripts_dir: Path) -> list[str]:
    changed: list[str] = []
    for path in sorted(scripts_dir.glob("map_*_state_*.c")):
        text = path.read_text()
        stripped = strip_map_event_wrapper(text, path.stem)
        normalized = normalize_map_scene_file(stripped)
        if normalized != text:
            path.write_text(normalized)
            changed.append(str(path))
    return changed


def cmd_strip_map_event_wrappers(args: argparse.Namespace) -> None:
    scripts_dir = Path(args.scripts_dir)
    changed = strip_all_map_event_wrappers(scripts_dir)
    for path in changed:
        print(f"stripped {path}")
    print(f"stripped MAP_EVENT wrapper from {len(changed)} file(s)")


def cmd_migrate_map_events(args: argparse.Namespace) -> None:
    scripts_dir = Path(args.scripts_dir)
    catalog_path = Path(args.catalog)
    changed = migrate_map_event_files(scripts_dir, catalog_path)
    for path in changed:
        print(f"migrated {path}")
    print(f"migrated {len(changed)} map event file(s)")


def validate_c_sources(paths: list[Path]) -> list[str]:
    errors: list[str] = []
    try:
        entries = parse_event_c_sources(paths)
    except ValueError as exc:
        return [str(exc)]

    names = [entry.name for entry in entries]
    if len(names) != len(set(names)):
        duplicate = next(name for name in names if names.count(name) > 1)
        errors.append(f"duplicate event script name {duplicate}")

    for path in paths:
        for name, _args in parse_macro_calls(path.read_text()):
            if name == "RAW":
                errors.append(f"{path}: RAW macro remains")
                break

    by_addr = {
        entry.script_address: entry
        for entry in entries
        if entry.script_address is not None
    }
    if 0x08E62160 not in by_addr:
        errors.append("missing map_09_state_01 intro dialogue script 0x08E62160")
    if 0x08E62154 not in by_addr:
        errors.append("missing map_09_state_01 intro cutscene handoff script 0x08E62154")

    intro_path = next((path for path in paths if path.name == "map_09_state_01.c"), None)
    if intro_path is None:
        errors.append("missing map_09_state_01.c")
    else:
        intro_text = intro_path.read_text()
        has_dialogue = (
            "LANGUAGE_TEXT(" in intro_text
            or "TEXT(" in intro_text
            or "TALK(" in intro_text
            or re.search(r"\bTEXT\b", intro_text) is not None
        )
        if not has_dialogue:
            errors.append("map_09_state_01.c has no editable language text")
        if "CUTSCENE(8)" not in intro_text:
            errors.append("map_09_state_01.c does not hand off to intro cutscene 8")

    return errors


def compile_replacements(data: dict[str, Any]) -> str:
    enabled = [entry for entry in data.get("scripts", []) if entry.get("replace") is True]
    enabled_by_addr = {parse_hex(entry["script_address"]): entry for entry in enabled}
    lines = [
        "/* Auto-generated by tools/vanilla_events.py. */",
        "",
    ]
    if not enabled:
        lines.extend([
            "const EventScriptReplacement gEventScriptReplacements[] APPEND_RODATA = {",
            "  {0, 0},",
            "};",
            "const unsigned gEventScriptReplacementCount APPEND_RODATA = 0;",
            "",
        ])
        return "\n".join(lines)

    for entry in enabled:
        script_addr = parse_hex(entry["script_address"])
        raw = bytes_from_yaml(entry.get("raw_bytes", []))
        values = ", ".join(f"0x{value:02X}" for value in raw)
        lines.append(f"static const u8 s{c_ident(script_addr)}Bytes[] APPEND_TEXT = {{{values}}};")
    lines.append("")

    for entry in enabled:
        script_addr = parse_hex(entry["script_address"])
        lines.append(f"static struct Script s{c_ident(script_addr)}Node;")
    lines.append("")

    for entry in enabled:
        script_addr = parse_hex(entry["script_address"])
        false_addr = parse_hex(entry.get("on_false"))
        true_addr = parse_hex(entry.get("on_true"))
        false_expr = f"&s{c_ident(false_addr)}Node" if false_addr in enabled_by_addr else f"(struct Script *)0x{false_addr:08X}"
        true_expr = f"&s{c_ident(true_addr)}Node" if true_addr in enabled_by_addr else f"(struct Script *)0x{true_addr:08X}"
        lines.append(
            f"static struct Script s{c_ident(script_addr)}Node APPEND_RODATA = "
            f"{{(u8 *)s{c_ident(script_addr)}Bytes, {false_expr}, {true_expr}}};"
        )
    lines.extend(["", "const EventScriptReplacement gEventScriptReplacements[] APPEND_RODATA = {"])
    for entry in enabled:
        script_addr = parse_hex(entry["script_address"])
        lines.append(f"  {{(const struct Script *)0x{script_addr:08X}, &s{c_ident(script_addr)}Node}},")
    lines.extend([
        "};",
        f"const unsigned gEventScriptReplacementCount APPEND_RODATA = {len(enabled)};",
        "",
    ])
    return "\n".join(lines)


def scene_script_refs(scene: dict[str, Any]) -> list[str]:
    refs: list[str] = []
    for slot in scene.get("on_enter", []):
        if slot.get("script"):
            refs.append(slot["script"])
    for slot in scene.get("on_exit", []):
        if slot.get("script"):
            refs.append(slot["script"])
    for obj in scene.get("initial_sprites", []):
        if obj.get("script_a"):
            refs.append(obj["script_a"])
        if obj.get("script_r"):
            refs.append(obj["script_r"])
    return refs


def collect_reachable_scripts(start_refs: list[str], scripts: dict[str, dict[str, Any]]) -> list[dict[str, Any]]:
    result: list[dict[str, Any]] = []
    seen: set[str] = set()
    stack = list(reversed(start_refs))
    while stack:
        ref = stack.pop()
        if not ref or ref in seen or ref not in scripts:
            continue
        seen.add(ref)
        entry = scripts[ref]
        result.append(entry)
        stack.append(entry.get("on_true"))
        stack.append(entry.get("on_false"))
    return result


def macro_safe_name(value: str) -> str:
    value = re.sub(r"[^A-Za-z0-9_]", "_", value)
    if value and value[0].isdigit():
        value = "_" + value
    return value or "SCRIPT"


def c_string(value: str) -> str:
    if "\n" in value or "\r" in value:
        value = value.replace("\r\n", "\n").replace("\r", "\n")
        parts: list[str] = []
        for line in value.splitlines(keepends=True):
            if line == "\n":
                if parts:
                    parts[-1] = parts[-1][:-1] + "\\n\\n\""
                else:
                    parts.append('"\\n\\n"')
                continue
            escaped = line.replace("\\", "\\\\").replace('"', '\\"')
            parts.append('"' + escaped + '"')
        return "\n".join(parts)
    return '"' + value.encode("unicode_escape").decode("ascii").replace('"', '\\"') + '"'


def raw_macro(raw_values: list[Any]) -> str:
    return "RAW(" + ", ".join(str(value) for value in raw_values) + ")"


def step_macro(step: dict[str, Any]) -> str:
    raw = bytes_from_yaml(step.get("raw", []))
    kind = step.get("type")
    macro: str | None = None

    def exact(name: str, args: list[Any], expected: list[int]) -> str | None:
        if raw == expected:
            return name + "(" + ", ".join(str(arg) for arg in args) + ")"
        return None

    if kind == "dialogue":
        text = str(step.get("text", ""))
        expected = [0x24, ord("0")] + encode_text(text) + [0x24, ord("6")]
        macro = exact("TEXT", [c_string(text)], expected)
        if macro is None:
            macro = exact("DIALOGUE", [c_string(text)], expected)
        if macro is None:
            macro = exact("TEXT_FRAGMENT", [c_string(text)], encode_text(text))
        if macro is None and raw and raw[0] == 0x24:
            expected = []
            lines = []
            for languages in parse_language_blocks(raw):
                if len(languages) == 1 and languages[0][0] == 0:
                    expected.extend([0x24, ord("0")])
                    expected.extend(encode_text(languages[0][1]))
                    lines.append(f"TEXT({c_string(languages[0][1])})")
                else:
                    for lang, lang_text in languages:
                        expected.extend([0x24, ord("0") + lang])
                        expected.extend(encode_text(lang_text))
                        lines.append(f"LANGUAGE_TEXT({lang}, {c_string(lang_text)})")
                    lines.append("END_LANGUAGE_TEXT()")
                expected.extend([0x24, ord("6")])
            if raw == expected:
                macro = "\n  ".join(lines)
    elif kind == "newline":
        macro = exact("NEWLINE", [], [0x23, ord("0")])
    elif kind == "page_break":
        macro = exact("PAGE_BREAK", [], [0x23, ord("1")])
    elif kind == "choice":
        macro = exact("CHOICE", [], [0x23, ord("3")])
    elif kind == "portrait":
        args = [step.get("portrait_id"), step.get("expression"), step.get("position")]
        macro = exact("PORTRAIT", args, [0x23, ord("4")] + [int(arg) & 0xFF for arg in args])
    elif kind in {"set_flag", "check_flag", "clear_flag"}:
        names = {"set_flag": "SET_FLAG", "check_flag": "CHECK_FLAG", "clear_flag": "CLEAR_FLAG"}
        cmds = {"set_flag": "6", "check_flag": "7", "clear_flag": "8"}
        flag = int(step.get("flag")) & 0xFF
        macro = exact(names[kind], [flag], [0x23, ord(cmds[kind]), flag])
    elif kind == "restore_life_points":
        macro = exact("RESTORE_LIFE_POINTS", [], [0x23, ord("9")])
    elif kind == "duel":
        opponent = int(step.get("opponent")) & 0xFF
        macro = exact("DUEL", [opponent], [0x40, ord("0"), opponent])
    elif kind in {"play_music", "set_map_music", "stop_music", "fade_music"}:
        names = {"play_music": "PLAY_MUSIC", "set_map_music": "SET_MAP_MUSIC", "stop_music": "STOP_MUSIC", "fade_music": "FADE_MUSIC"}
        cmds = {"play_music": "3", "set_map_music": "4", "stop_music": "5", "fade_music": "6"}
        music = int(step.get("music")) & 0xFFFF
        macro = exact(names[kind], [music], [0x40, ord(cmds[kind]), music & 0xFF, (music >> 8) & 0xFF])
    elif kind == "start_menu":
        macro = exact("START_MENU", [], [0x40, ord("1")])
    elif kind == "save":
        macro = exact("SAVE", [], [0x40, ord("2")])
    elif kind == "move_object":
        args = [step.get("object_id"), step.get("direction"), step.get("distance"), step.get("wander")]
        direction = int(step.get("direction"))
        direction_name = {
            0: "DIRECTION_DOWN",
            1: "DIRECTION_LEFT",
            2: "DIRECTION_UP",
            3: "DIRECTION_RIGHT",
        }.get(direction, direction)
        macro = exact("MOVE_OBJECT", [step.get("object_id"), direction_name, step.get("distance"), step.get("wander")], [0x40, ord("7")] + [int(arg) & 0xFF for arg in args])
    elif kind == "stop_footsteps":
        macro = exact("STOP_FOOTSTEPS", [], [0x40, ord("8")])
    elif kind == "set_object_position":
        args = [step.get("object_id"), step.get("x"), step.get("y"), step.get("frame")]
        if step.get("direction") is not None:
            direction = int(step.get("direction"))
            direction_name = {
                0: "DIRECTION_DOWN",
                1: "DIRECTION_LEFT",
                2: "DIRECTION_UP",
                3: "DIRECTION_RIGHT",
            }.get(direction, direction)
            args.append(direction_name)
        macro = exact("SET_OBJECT_POSITION", args, raw)
    elif kind == "show_object":
        args = [step.get("object_id"), step.get("x"), step.get("y"), step.get("frame"), step.get("mode")]
        if len(raw) == 8:
            args.append(raw[7])
        macro = exact("SHOW_OBJECT", args, [0x5E, ord("0")] + [int(arg) & 0xFF for arg in args])
    elif kind in {"walk_object_x", "walk_object_y"}:
        name = "WALK_OBJECT_X" if kind == "walk_object_x" else "WALK_OBJECT_Y"
        cmd = "1" if kind == "walk_object_x" else "2"
        args = [step.get("object_id"), step.get("target")]
        macro = exact(name, args, [0x5E, ord(cmd)] + [int(arg) & 0xFF for arg in args])
    elif kind == "slide_object":
        args = [step.get("object_id"), step.get("direction"), step.get("distance")]
        macro = exact("SLIDE_OBJECT", args, [0x5E, ord("3")] + [int(arg) & 0xFF for arg in args])
    elif kind == "object_effect":
        mask = int(step.get("object_mask")) & 0xFFFF
        mode = int(step.get("mode")) & 0xFF
        macro = exact("OBJECT_EFFECT", [object_mask_expr(mask), mode], [0x5E, ord("4"), (mask >> 8) & 0xFF, mask & 0xFF, mode])
    elif kind == "special":
        special = SPECIAL_COMMANDS_INV.get(step.get("command"))
        if special is not None:
            macro = exact("SPECIAL", [special], [0x5E, ord("5"), special])
    elif kind == "cutscene":
        cutscene_id = int(step.get("cutscene", {}).get("id"))
        special = {0: 15, 1: 16, 8: 33, 7: 34}.get(cutscene_id)
        if special is not None:
            macro = exact("CUTSCENE", [cutscene_id], [0x5E, ord("5"), special])
    elif kind == "delay":
        frames = int(step.get("frames")) & 0xFF
        macro = exact("DELAY", [frames], [0x5E, ord("6"), frames])
    elif kind in {"add_card", "remove_card"}:
        name = "ADD_CARD" if kind == "add_card" else "REMOVE_CARD"
        cmd = "7" if kind == "add_card" else "8"
        card = int(step.get("card")) & 0xFFFF
        macro = exact(name, [card], [0x5E, ord(cmd), card & 0xFF, (card >> 8) & 0xFF])
    elif kind == "condition_check":
        condition = int(step.get("condition")) & 0xFF
        macro = exact("CONDITION_CHECK", [condition], [0x5E, ord("9"), condition])
    elif kind == "fade_screen":
        speed = int(step.get("speed")) & 0xFF
        macro = exact("FADE_SCREEN", [speed], [0x7C, ord("1"), speed])
    elif kind == "fade_in":
        speed = int(step.get("speed")) & 0xFF
        macro = exact("FADE_IN", [speed], [0x7C, ord("B"), speed])
    elif kind == "fade_out":
        speed = int(step.get("speed")) & 0xFF
        macro = exact("FADE_OUT", [speed], [0x7C, ord("D"), speed])
    elif kind == "screen_shake":
        speed = int(step.get("speed")) & 0xFF
        macro = exact("SCREEN_SHAKE", [speed], [0x7C, ord("7"), speed])
    elif kind == "hide_portrait":
        macro = exact("HIDE_PORTRAIT", [], [0x7C, ord("3")])
    elif kind == "swap_object_sprite":
        args = [step.get("object_id"), step.get("sprite_id")]
        macro = exact("LOAD_SPRITE", args, [0x7C, ord("4")] + [int(arg) & 0xFF for arg in args])
    elif kind == "warp":
        map_id = int(step.get("map_id"))
        args = [overworld_location_expr(map_id), step.get("state"), step.get("connection")]
        if len(raw) == 6:
            args.append(raw[5])
        expected = [0x7C, ord("5"), map_id & 0xFF, int(step.get("state")) & 0xFF, int(step.get("connection")) & 0xFF]
        if len(raw) == 6:
            expected.append(raw[5])
        macro = exact("WARP", args, expected)
    elif kind == "reaction":
        reaction = int(step.get("reaction")) & 0xFF
        mask = int(step.get("object_mask")) & 0xFFFF
        macro = exact("REACTION", [reaction, mask], [0x7C, ord("6"), reaction, (mask >> 8) & 0xFF, mask & 0xFF])
    elif kind == "display_cg":
        cg_id = int(step.get("cg_id")) & 0xFF
        fade_speed = int(step.get("fade_speed", 8)) & 0xFF
        macro = exact("DISPLAY_CG", [cg_id, fade_speed], [0x7C, ord("9"), cg_id, fade_speed])
    elif kind == "hide_cg":
        fade_speed = int(step.get("fade_speed", 8)) & 0xFF
        macro = exact("HIDE_CG", [fade_speed], [0x7C, ord("A"), fade_speed])
    elif kind == "fallthrough":
        macro = exact("FALLTHROUGH", [], [0])
    elif kind == "end":
        macro = exact("END", [], [0x5D])
    elif isinstance(kind, str) and kind.startswith("command_7c_") and len(raw) == 3:
        command = raw[1] - ord("0")
        if command == 8:
            macro = exact("SHOW_OVERWORLD_GRAPHIC", [raw[2]], raw)
        else:
            macro = exact("COMMAND_7C_ARG", [command, raw[2]], raw)
    return macro or raw_macro(step.get("raw", []))


def render_c_script(entry: dict[str, Any], scene_id: str) -> str:
    addr = parse_hex(entry["script_address"])
    name = f"{macro_safe_name(scene_id)}_{addr:08X}"
    lines = [
        f"EVENT_SCRIPT_REPLACEMENT(0x{addr:08X}, {name}, {entry.get('on_false') or '0'}, {entry.get('on_true') or '0'})",
    ]
    raw_from_steps: list[int] = []
    for step in entry.get("steps", []):
        raw_from_steps.extend(bytes_from_yaml(step.get("raw", [])))
    if raw_from_steps == bytes_from_yaml(entry.get("raw_bytes", [])):
        steps = entry.get("steps", [])
        index = 0
        while index < len(steps):
            step = steps[index]
            if (
                step.get("type") == "portrait"
                and index + 1 < len(steps)
                and steps[index + 1].get("type") == "dialogue"
            ):
                next_step = steps[index + 1]
                portrait_args = [
                    step.get("portrait_id"),
                    step.get("expression"),
                    step.get("position"),
                ]
                text = str(next_step.get("text", ""))
                combined_raw = [0x23, ord("4")] + [int(arg) & 0xFF for arg in portrait_args]
                combined_raw.extend([0x24, ord("0")])
                combined_raw.extend(encode_text(text))
                combined_raw.extend([0x24, ord("6")])
                actual_raw = bytes_from_yaml(step.get("raw", [])) + bytes_from_yaml(next_step.get("raw", []))
                if actual_raw == combined_raw:
                    text_arg = c_string(text)
                    if "\n" in text_arg:
                        text_indent = talk_text_indent("  ")
                        aligned_text = align_talk_text_arg(text_arg, text_indent)
                        lines.append(
                            "  TALK("
                            + ", ".join(str(arg) for arg in portrait_args)
                            + ",\n"
                            + aligned_text
                            + "\n  )"
                        )
                    else:
                        lines.append(
                            "  TALK("
                            + ", ".join(str(arg) for arg in portrait_args)
                            + ", "
                            + text_arg
                            + ")"
                        )
                    index += 2
                    continue
            lines.append(f"  {step_macro(step)}")
            index += 1
    else:
        lines.append("  " + raw_macro(entry.get("raw_bytes", [])))
    lines.extend(["END_EVENT_SCRIPT()", ""])
    return "\n".join(lines)


def export_c_sources(data: dict[str, Any], out_dir: Path, all_scripts: bool) -> None:
    scripts = {entry["script_address"]: entry for entry in data.get("scripts", [])}
    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / "event_macros.h").write_text(EVENT_MACROS_HEADER)

    assigned: set[str] = set()
    for scene in data.get("scenes", []):
        scene_id = scene.get("scene_id", "scene")
        entries = collect_reachable_scripts(scene_script_refs(scene), scripts)
        if not all_scripts:
            entries = [entry for entry in entries if entry.get("replace") is True]
        entries = [entry for entry in entries if entry["script_address"] not in assigned]
        if not entries:
            continue
        assigned.update(entry["script_address"] for entry in entries)
        body = [
            '#include "event_macros.h"',
            '#include "overworld.h"'
            "",
            f"/* {scene_id}: map {scene.get('map_id')} state {scene.get('state')} */",
            "",
        ]
        for entry in entries:
            body.append(render_c_script(entry, scene_id))
        (out_dir / f"{scene_id}.c").write_text("\n".join(body))


EVENT_MACROS_HEADER = """#ifndef EVENT_MACROS_H
#define EVENT_MACROS_H

/* These files are parsed by tools/vanilla_events.py, not compiled directly.
 * TEXT/DIALOGUE/LANGUAGE_TEXT accept normal Python string literals, including
 * triple-quoted multiline strings for easier authoring.
 */

#define EVENT_SCRIPT_REPLACEMENT(vanilla_addr, name, on_false, on_true)
#define EVENT_SCRIPT(name, on_false, on_true)
#define END_EVENT_SCRIPT()

#define RAW(...)
#define DIALOGUE(text)
#define LANGUAGE_TEXT(language, text)
#define END_LANGUAGE_TEXT()
#define TEXT(text) LANGUAGE_TEXT(LANGUAGE_ENGLISH, text) END_LANGUAGE_TEXT()
#define TEXT_FRAGMENT(text)
#define PLAYER_NAME()
#define NEWLINE()
#define PAGE_BREAK()
#define CHOICE()
#define PORTRAIT(portrait_id, expression, position)
#define TALK(portrait_id, expression, position, text)
#define HIDE_PORTRAIT()
#define SET_FLAG(flag)
#define CHECK_FLAG(flag)
#define CLEAR_FLAG(flag)
#define RESTORE_LIFE_POINTS()
#define DUEL(opponent)
#define PLAY_MUSIC(music)
#define SET_MAP_MUSIC(music)
#define STOP_MUSIC(music)
#define FADE_MUSIC(music)
#define START_MENU()
#define SAVE()
#define MOVE_OBJECT(object_id, direction, distance, wander)
#define STOP_FOOTSTEPS()
#define SET_OBJECT_POSITION(object_id, x, y, frame, direction)
#define SHOW_OBJECT(object_id, x, y, frame, mode, unused)
#define WALK_OBJECT_X(object_id, target)
#define WALK_OBJECT_Y(object_id, target)
#define SLIDE_OBJECT(object_id, direction, distance)
#define OBJECT_EFFECT(object_mask, mode)
#define SPECIAL(command)
#define CUTSCENE(cutscene_id)
#define DELAY(frames)
#define ADD_CARD(card)
#define REMOVE_CARD(card)
#define CONDITION_CHECK(condition)
#define FADE_SCREEN(speed)
#define FADE_OUT(speed)
#define FADE_IN(speed)
#define SWAP_OBJECT_SPRITE(object_id, sprite_id)
#define LOAD_SPRITE(object_id, sprite_id)
#define WARP(map_id, state, connection, unused)
#define REACTION(reaction, object_mask)
#define COMMAND_7C_ARG(command, argument)
#define FALLTHROUGH()
#define END()

#endif
"""


def validate_yaml(rom: Rom, data: dict[str, Any]) -> list[str]:
    errors: list[str] = []
    for entry in data.get("scripts", []):
        start_addr = parse_hex(entry.get("start_address"))
        raw = bytes_from_yaml(entry.get("raw_bytes", []))
        if not rom.valid_addr(start_addr):
            errors.append(f"{entry.get('script_address')}: invalid start_address {entry.get('start_address')}")
            continue
        actual = rom.bytes_at(start_addr, len(raw))
        if actual != raw:
            errors.append(f"{entry.get('script_address')}: raw_bytes differ from ROM at {entry.get('start_address')}")
    return errors


def cmd_extract(args: argparse.Namespace) -> None:
    data = extract_events(Rom(Path(args.rom)))
    write_yaml(Path(args.out), data)
    if args.catalog:
        catalog_path = Path(args.catalog)
        catalog_path.parent.mkdir(parents=True, exist_ok=True)
        catalog_path.write_text(render_catalog(data))


def cmd_catalog(args: argparse.Namespace) -> None:
    data = load_yaml(Path(args.input))
    Path(args.out).write_text(render_catalog(data))


def cmd_compile(args: argparse.Namespace) -> None:
    data = load_yaml(Path(args.input))
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(compile_replacements(data))


def cmd_compile_c(args: argparse.Namespace) -> None:
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(compile_c_replacements([Path(path) for path in args.inputs]))


def cmd_test_c(args: argparse.Namespace) -> None:
    errors = validate_c_sources([Path(path) for path in args.inputs])
    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        raise SystemExit(1)
    print("event C sources validated")


def cmd_export_c(args: argparse.Namespace) -> None:
    export_c_sources(load_yaml(Path(args.input)), Path(args.out_dir), args.all)


def cmd_validate(args: argparse.Namespace) -> None:
    errors = validate_yaml(Rom(Path(args.rom)), load_yaml(Path(args.input)))
    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        raise SystemExit(1)
    print("validated")


def build_arg_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)

    extract = subparsers.add_parser("extract", help="extract vanilla event YAML")
    extract.add_argument("--rom", default="baserom.gba")
    extract.add_argument("--out", default="events/vanilla/vanilla_events.yaml")
    extract.add_argument("--catalog", default="events/vanilla/vanilla_event_catalog.md")
    extract.set_defaults(func=cmd_extract)

    catalog = subparsers.add_parser("catalog", help="render Markdown from event YAML")
    catalog.add_argument("input")
    catalog.add_argument("--out", default="events/vanilla/vanilla_event_catalog.md")
    catalog.set_defaults(func=cmd_catalog)

    compile_cmd = subparsers.add_parser("compile", help="compile enabled YAML replacements")
    compile_cmd.add_argument("input")
    compile_cmd.add_argument("--out", default="src_custom/generated/event_script_replacements.inc")
    compile_cmd.set_defaults(func=cmd_compile)

    compile_c = subparsers.add_parser("compile-c", help="compile event C macro replacement files")
    compile_c.add_argument("inputs", nargs="*")
    compile_c.add_argument("--out", default="src_custom/generated/event_script_replacements.inc")
    compile_c.add_argument(
        "--story-sequence",
        default=str(DEFAULT_STORY_SEQUENCE_PATH),
        help="ordered main-story scene list (default: events/story_sequence.txt)",
    )
    compile_c.set_defaults(func=cmd_compile_c)

    test_c = subparsers.add_parser("test-c", help="validate event C macro files")
    test_c.add_argument("inputs", nargs="*")
    test_c.set_defaults(func=cmd_test_c)

    migrate_sprite_refs = subparsers.add_parser(
        "migrate-sprite-refs",
        help="rewrite object slot ids to SPRITE_* names where unambiguous",
    )
    migrate_sprite_refs.add_argument("--scripts-dir", default="events/scripts")
    migrate_sprite_refs.set_defaults(func=cmd_migrate_sprite_refs)

    migrate_map_events = subparsers.add_parser(
        "migrate-map-events",
        help="convert map enter EVENT_SCRIPT_REPLACEMENT chains into linear map enter scripts",
    )
    migrate_map_events.add_argument("--scripts-dir", default="events/scripts")
    migrate_map_events.add_argument(
        "--catalog",
        default="events/vanilla/vanilla_event_catalog.md",
    )
    migrate_map_events.set_defaults(func=cmd_migrate_map_events)

    strip_map_events = subparsers.add_parser(
        "strip-map-event-wrappers",
        help="remove legacy MAP_EVENT/END_MAP_EVENT wrappers (filename is the scene id)",
    )
    strip_map_events.add_argument("--scripts-dir", default="events/scripts")
    strip_map_events.set_defaults(func=cmd_strip_map_event_wrappers)

    generate_skeleton = subparsers.add_parser(
        "generate-story-skeleton",
        help="create skeleton scene files and refresh events/story_sequence.txt from the catalog",
    )
    generate_skeleton.add_argument(
        "--catalog",
        default="events/vanilla/vanilla_event_catalog.md",
    )
    generate_skeleton.add_argument("--scripts-dir", default="events/scripts")
    generate_skeleton.add_argument(
        "--sequence",
        default=str(DEFAULT_STORY_SEQUENCE_PATH),
    )
    generate_skeleton.add_argument(
        "--reset-active",
        action="store_true",
        help="comment out every scene instead of preserving currently active entries",
    )
    generate_skeleton.set_defaults(func=cmd_generate_story_skeleton)

    export_c = subparsers.add_parser("export-c", help="split event YAML into C macro files")
    export_c.add_argument("input")
    export_c.add_argument("--out-dir", default="events/scripts")
    export_c.add_argument("--all", action="store_true", help="export all reachable scripts instead of replacements only")
    export_c.set_defaults(func=cmd_export_c)

    validate = subparsers.add_parser("validate", help="validate YAML raw byte round trips")
    validate.add_argument("input")
    validate.add_argument("--rom", default="baserom.gba")
    validate.set_defaults(func=cmd_validate)
    return parser


def main(argv: list[str] | None = None) -> int:
    parser = build_arg_parser()
    args = parser.parse_args(argv)
    args.func(args)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
