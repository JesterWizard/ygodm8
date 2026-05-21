#!/usr/bin/env python3
"""Extract, validate, catalog, and compile vanilla overworld events."""

from __future__ import annotations

import argparse
import ast
import re
import struct
import sys
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


def strip_c_comments(text: str) -> str:
    out: list[str] = []
    index = 0
    quote: str | None = None
    escape = False
    while index < len(text):
        ch = text[index]
        next_ch = text[index + 1] if index + 1 < len(text) else ""
        if quote:
            out.append(ch)
            if escape:
                escape = False
            elif ch == "\\":
                escape = True
            elif ch == quote:
                quote = None
            index += 1
            continue
        if ch in {"'", '"'}:
            quote = ch
            out.append(ch)
            index += 1
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
])


def split_macro_args(arg_text: str) -> list[str]:
    args: list[str] = []
    start = 0
    depth = 0
    quote: str | None = None
    escape = False
    for index, ch in enumerate(arg_text):
        if quote:
            if escape:
                escape = False
            elif ch == "\\":
                escape = True
            elif ch == quote:
                quote = None
            continue
        if ch in {"'", '"'}:
            quote = ch
        elif ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        elif ch == "," and depth == 0:
            args.append(arg_text[start:index].strip())
            start = index + 1
    tail = arg_text[start:].strip()
    if tail:
        args.append(tail)
    return args


def parse_macro_calls(text: str) -> list[tuple[str, list[str]]]:
    calls: list[tuple[str, list[str]]] = []
    clean = strip_c_comments(text)
    index = 0
    while index < len(clean):
        match = re.search(r"\b([A-Z][A-Z0-9_]*)\s*\(", clean[index:])
        if not match:
            break
        name = match.group(1)
        open_index = index + match.end() - 1
        p = open_index + 1
        depth = 1
        quote: str | None = None
        escape = False
        while p < len(clean):
            ch = clean[p]
            if quote:
                if escape:
                    escape = False
                elif ch == "\\":
                    escape = True
                elif ch == quote:
                    quote = None
            elif ch in {"'", '"'}:
                quote = ch
            elif ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
                if depth == 0:
                    calls.append((name, split_macro_args(clean[open_index + 1 : p])))
                    p += 1
                    break
            p += 1
        index = p
    return calls


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


def object_mask_expr(mask: int) -> str:
    if mask == 0:
        return "0"
    parts = [f"OBJECT_{bit + 1}" for bit in range(15) if mask & (1 << bit)]
    return " | ".join(parts) if parts else str(mask)


@dataclass
class CScriptEntry:
    name: str
    script_address: int | None
    on_false: str
    on_true: str
    raw_bytes: list[int]


def parse_event_c_sources(paths: list[Path]) -> list[CScriptEntry]:
    entries: list[CScriptEntry] = []
    current: CScriptEntry | None = None

    def need_args(name: str, args: list[str], count: int) -> None:
        if len(args) != count:
            raise ValueError(f"{name} expected {count} args, got {len(args)}")

    for path in paths:
        for name, args in parse_macro_calls(path.read_text()):
            if name in {"EVENT_SCRIPT_REPLACEMENT", "REPLACE_EVENT_SCRIPT"}:
                need_args(name, args, 4)
                if current is not None:
                    raise ValueError(f"{path}: nested {name}")
                current = CScriptEntry(args[1], parse_hex(args[0]), args[2], args[3], [])
                continue
            if name == "EVENT_SCRIPT":
                need_args(name, args, 3)
                if current is not None:
                    raise ValueError(f"{path}: nested {name}")
                current = CScriptEntry(args[0], None, args[1], args[2], [])
                continue
            if name == "END_EVENT_SCRIPT":
                need_args(name, args, 0)
                if current is None:
                    raise ValueError(f"{path}: END_EVENT_SCRIPT without script")
                entries.append(current)
                current = None
                continue
            if current is None:
                continue

            if name == "RAW":
                current.raw_bytes.extend(parse_c_value(arg) & 0xFF for arg in args)
            elif name == "DIALOGUE":
                need_args(name, args, 1)
                text = ast.literal_eval(args[0])
                current.raw_bytes.extend([0x24, ord("0")])
                current.raw_bytes.extend(encode_text(text))
                current.raw_bytes.extend([0x24, ord("6")])
            elif name == "LANGUAGE_TEXT":
                need_args(name, args, 2)
                current.raw_bytes.extend([0x24, ord("0") + parse_c_value(args[0])])
                current.raw_bytes.extend(encode_text(ast.literal_eval(args[1])))
            elif name == "END_LANGUAGE_TEXT":
                need_args(name, args, 0)
                current.raw_bytes.extend([0x24, ord("6")])
            elif name == "TEXT":
                need_args(name, args, 1)
                current.raw_bytes.extend([0x24, ord("0")])
                current.raw_bytes.extend(encode_text(ast.literal_eval(args[0])))
                current.raw_bytes.extend([0x24, ord("6")])
            elif name == "TEXT_FRAGMENT":
                need_args(name, args, 1)
                current.raw_bytes.extend(encode_text(ast.literal_eval(args[0])))
            elif name == "PLAYER_NAME":
                need_args(name, args, 0)
                current.raw_bytes.extend([0x23, ord("5")])
            elif name == "NEWLINE":
                need_args(name, args, 0)
                current.raw_bytes.extend([0x23, ord("0")])
            elif name == "PAGE_BREAK":
                need_args(name, args, 0)
                current.raw_bytes.extend([0x23, ord("1")])
            elif name == "CHOICE":
                need_args(name, args, 0)
                current.raw_bytes.extend([0x23, ord("3")])
            elif name == "PORTRAIT":
                need_args(name, args, 3)
                current.raw_bytes.extend([0x23, ord("4"), *(parse_c_value(arg) & 0xFF for arg in args)])
            elif name in {"SET_FLAG", "CHECK_FLAG", "CLEAR_FLAG"}:
                need_args(name, args, 1)
                cmd = {"SET_FLAG": "6", "CHECK_FLAG": "7", "CLEAR_FLAG": "8"}[name]
                current.raw_bytes.extend([0x23, ord(cmd), parse_c_value(args[0]) & 0xFF])
            elif name == "RESTORE_LIFE_POINTS":
                need_args(name, args, 0)
                current.raw_bytes.extend([0x23, ord("9")])
            elif name == "DUEL":
                need_args(name, args, 1)
                current.raw_bytes.extend([0x40, ord("0"), parse_c_value(args[0]) & 0xFF])
            elif name in {"PLAY_MUSIC", "SET_MAP_MUSIC", "STOP_MUSIC", "FADE_MUSIC"}:
                need_args(name, args, 1)
                cmd = {"PLAY_MUSIC": "3", "SET_MAP_MUSIC": "4", "STOP_MUSIC": "5", "FADE_MUSIC": "6"}[name]
                music = parse_c_value(args[0])
                current.raw_bytes.extend([0x40, ord(cmd), music & 0xFF, (music >> 8) & 0xFF])
            elif name == "START_MENU":
                need_args(name, args, 0)
                current.raw_bytes.extend([0x40, ord("1")])
            elif name == "SAVE":
                need_args(name, args, 0)
                current.raw_bytes.extend([0x40, ord("2")])
            elif name == "MOVE_OBJECT":
                need_args(name, args, 4)
                current.raw_bytes.extend([0x40, ord("7"), *(parse_c_value(arg) & 0xFF for arg in args)])
            elif name == "STOP_FOOTSTEPS":
                need_args(name, args, 0)
                current.raw_bytes.extend([0x40, ord("8")])
            elif name == "SET_OBJECT_POSITION":
                need_args(name, args, 4)
                current.raw_bytes.extend([0x40, ord("9"), *(parse_c_value(arg) & 0xFF for arg in args)])
            elif name == "SHOW_OBJECT":
                if len(args) not in {5, 6}:
                    raise ValueError(f"{name} expected 5 or 6 args, got {len(args)}")
                current.raw_bytes.extend([0x5E, ord("0"), *(parse_c_value(arg) & 0xFF for arg in args)])
            elif name in {"WALK_OBJECT_X", "WALK_OBJECT_Y"}:
                need_args(name, args, 2)
                cmd = "1" if name == "WALK_OBJECT_X" else "2"
                current.raw_bytes.extend([0x5E, ord(cmd), *(parse_c_value(arg) & 0xFF for arg in args)])
            elif name == "SLIDE_OBJECT":
                need_args(name, args, 3)
                current.raw_bytes.extend([0x5E, ord("3"), *(parse_c_value(arg) & 0xFF for arg in args)])
            elif name == "OBJECT_EFFECT":
                need_args(name, args, 2)
                mask = parse_c_value(args[0])
                current.raw_bytes.extend([0x5E, ord("4"), (mask >> 8) & 0xFF, mask & 0xFF, parse_c_value(args[1]) & 0xFF])
            elif name == "SPECIAL":
                need_args(name, args, 1)
                current.raw_bytes.extend([0x5E, ord("5"), parse_c_value(args[0]) & 0xFF])
            elif name == "CUTSCENE":
                need_args(name, args, 1)
                special = {0: 15, 1: 16, 8: 33, 7: 34}[parse_c_value(args[0])]
                current.raw_bytes.extend([0x5E, ord("5"), special])
            elif name == "DELAY":
                need_args(name, args, 1)
                current.raw_bytes.extend([0x5E, ord("6"), parse_c_value(args[0]) & 0xFF])
            elif name in {"ADD_CARD", "REMOVE_CARD"}:
                need_args(name, args, 1)
                card = parse_c_value(args[0])
                current.raw_bytes.extend([0x5E, ord("7" if name == "ADD_CARD" else "8"), card & 0xFF, (card >> 8) & 0xFF])
            elif name == "CONDITION_CHECK":
                need_args(name, args, 1)
                current.raw_bytes.extend([0x5E, ord("9"), parse_c_value(args[0]) & 0xFF])
            elif name == "FADE_SCREEN":
                need_args(name, args, 1)
                current.raw_bytes.extend([0x7C, ord("1"), parse_c_value(args[0]) & 0xFF])
            elif name == "HIDE_PORTRAIT":
                need_args(name, args, 0)
                current.raw_bytes.extend([0x7C, ord("3")])
            elif name in {"SWAP_OBJECT_SPRITE", "LOAD_SPRITE"}:
                need_args(name, args, 2)
                current.raw_bytes.extend([0x7C, ord("4"), *(parse_c_value(arg) & 0xFF for arg in args)])
            elif name == "WARP":
                if len(args) not in {3, 4}:
                    raise ValueError(f"{name} expected 3 or 4 args, got {len(args)}")
                current.raw_bytes.extend([0x7C, ord("5"), *(parse_c_value(arg) & 0xFF for arg in args)])
            elif name == "REACTION":
                need_args(name, args, 2)
                mask = parse_c_value(args[1])
                current.raw_bytes.extend([0x7C, ord("6"), parse_c_value(args[0]) & 0xFF, (mask >> 8) & 0xFF, mask & 0xFF])
            elif name == "COMMAND_7C_ARG":
                need_args(name, args, 2)
                current.raw_bytes.extend([0x7C, ord("0") + parse_c_value(args[0]), parse_c_value(args[1]) & 0xFF])
            elif name == "FALLTHROUGH":
                need_args(name, args, 0)
                current.raw_bytes.append(0)
            elif name == "END":
                need_args(name, args, 0)
                current.raw_bytes.append(0x5D)
            else:
                raise ValueError(f"{path}: unknown event macro {name}")
        if current is not None:
            raise ValueError(f"{path}: unclosed event script {current.name}")
    return entries


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
        if "LANGUAGE_TEXT(" not in intro_text:
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
        macro = exact("SET_OBJECT_POSITION", args, [0x40, ord("9")] + [int(arg) & 0xFF for arg in args])
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
    elif kind == "hide_portrait":
        macro = exact("HIDE_PORTRAIT", [], [0x7C, ord("3")])
    elif kind == "swap_object_sprite":
        args = [step.get("object_id"), step.get("sprite_id")]
        macro = exact("LOAD_SPRITE", args, [0x7C, ord("4")] + [int(arg) & 0xFF for arg in args])
    elif kind == "warp":
        args = [step.get("map_id"), step.get("state"), step.get("connection")]
        if len(raw) == 6:
            args.append(raw[5])
        macro = exact("WARP", args, [0x7C, ord("5")] + [int(arg) & 0xFF for arg in args])
    elif kind == "reaction":
        reaction = int(step.get("reaction")) & 0xFF
        mask = int(step.get("object_mask")) & 0xFFFF
        macro = exact("REACTION", [reaction, mask], [0x7C, ord("6"), reaction, (mask >> 8) & 0xFF, mask & 0xFF])
    elif kind == "fallthrough":
        macro = exact("FALLTHROUGH", [], [0])
    elif kind == "end":
        macro = exact("END", [], [0x5D])
    elif isinstance(kind, str) and kind.startswith("command_7c_") and len(raw) == 3:
        macro = exact("COMMAND_7C_ARG", [raw[1] - ord("0"), raw[2]], raw)
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
        lines.extend(f"  {step_macro(step)}" for step in entry.get("steps", []))
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

/* These files are parsed by tools/vanilla_events.py, not compiled directly. */

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
#define SET_OBJECT_POSITION(object_id, x, y, frame)
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
    compile_cmd.add_argument("--out", default="src/hooks/generated/event_script_replacements.inc")
    compile_cmd.set_defaults(func=cmd_compile)

    compile_c = subparsers.add_parser("compile-c", help="compile event C macro replacement files")
    compile_c.add_argument("inputs", nargs="*")
    compile_c.add_argument("--out", default="src/hooks/generated/event_script_replacements.inc")
    compile_c.set_defaults(func=cmd_compile_c)

    test_c = subparsers.add_parser("test-c", help="validate event C macro files")
    test_c.add_argument("inputs", nargs="*")
    test_c.set_defaults(func=cmd_test_c)

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
