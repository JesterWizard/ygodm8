#!/usr/bin/env python3
"""Regenerate custom_map_manifest.json.

Reads baserom.gba to extract map connections, music IDs, collision,
and PNG dimensions. Writes the new manifest format.
"""

from __future__ import annotations

import json
import re
import struct
from pathlib import Path

try:
    from PIL import Image
except ImportError:
    Image = None

ROOT = Path(__file__).resolve().parents[1]
ROM_PATH = ROOT / "baserom.gba"
MANIFEST_PATH = ROOT / "tools" / "custom_map_manifest.json"
ASSETS_DIR = ROOT / "src_custom" / "assets" / "maps"
ROM_BASE = 0x08000000

CW, CH = 120, 80  # collision grid
BLOCKED_THRESHOLD = 4096

# Direction constant names (matching overworld.h enum)
DIRECTION_NAMES = {0: "DIRECTION_DOWN", 1: "DIRECTION_LEFT", 2: "DIRECTION_UP", 3: "DIRECTION_RIGHT"}

# Edge direction constants (matching overworld.h)
EDGES = ["bottom", "left", "top", "right"]

LOCATIONS = [
    (0, "LOCATION_CLOCK_TOWER_SQUARE_NORTHWEST", "Clock Tower Square NW"),
    (1, "LOCATION_CLOCK_TOWER_SQUARE_NORTH", "Clock Tower Square N"),
    (2, "LOCATION_CLOCK_TOWER_SQUARE_NORTHEAST", "Clock Tower Square NE"),
    (3, "LOCATION_CLOCK_TOWER_SQUARE_SOUTHEAST", "Clock Tower Square SE"),
    (4, "LOCATION_CLOCK_TOWER_SQUARE_SOUTHWEST", "Clock Tower Square SW"),
    (5, "LOCATION_LUMBERYARD", "Lumberyard"),
    (6, "LOCATION_SOUTH_AVENUE_WEST", "South Avenue W"),
    (7, "LOCATION_SOUTH_AVENUE_EAST", "South Avenue E"),
    (8, "LOCATION_CLOCK_TOWER_ENTRANCE", "Clock Tower Entrance"),
    (9, "LOCATION_CLOCK_TOWER_FOYER", "Clock Tower Foyer"),
    (10, "LOCATION_CLOCK_TOWER_INTERIOR", "Clock Tower Interior"),
    (11, "LOCATION_MAIDEN_GARDEN", "Maiden's Garden"),
    (12, "LOCATION_CLOCK_TOWER_ROOF", "Clock Tower Roof"),
    (13, "LOCATION_COLOSSEUM_YARD", "Colosseum Yard"),
    (14, "LOCATION_COLOSSEUM_ENTRANCE", "Colosseum Entrance"),
    (15, "LOCATION_COLOSSEUM_INTERIOR", "Colosseum Interior"),
    (16, "LOCATION_COLOSSEUM_ROOFTOP", "Colosseum Rooftop"),
    (17, "LOCATION_COLOSSEUM_STOREHOUSE", "Colosseum Storehouse"),
    (18, "LOCATION_COLOSSEUM_FOYER", "Colosseum Foyer"),
    (19, "LOCATION_FOUNTAIN_COURTYARD", "Fountain Courtyard"),
    (20, "LOCATION_PALACE_GATE", "Palace Gate"),
    (21, "LOCATION_PALACE_FOYER_LOWER", "Palace Foyer Lower"),
    (22, "LOCATION_PALACE_FOYER_UPPER", "Palace Foyer Upper"),
    (23, "LOCATION_PALACE_THRONE_ROOM", "Palace Throne Room"),
    (24, "LOCATION_PALACE_DINING_ROOM", "Palace Dining Room"),
    (25, "LOCATION_PALACE_KITCHEN", "Palace Kitchen"),
    (26, "LOCATION_PALACE_STUDY", "Palace Study"),
    (27, "LOCATION_PALACE_BEDROOM", "Palace Bedroom"),
    (28, "LOCATION_RUINS_EXTERIOR", "Ruins Exterior"),
    (29, "LOCATION_RUINS_HALL", "Ruins Hall"),
    (30, "LOCATION_RUINS_SANCTUARY", "Ruins Sanctuary"),
    (31, "LOCATION_RUINS_PASSAGE", "Ruins Passage"),
    (32, "LOCATION_UNDERWATER_RUINS", "Underwater Ruins"),
    (33, "LOCATION_LAKESIDE_LABORATORY", "Lakeside Laboratory"),
    (34, "LOCATION_LAKESIDE_LAB_ENTRY", "Lakeside Lab Entry"),
    (35, "LOCATION_LAKESIDE_LAB_MAIN", "Lakeside Lab Main"),
    (36, "LOCATION_LAKESIDE_LAB_STORAGE", "Lakeside Lab Storage"),
    (37, "LOCATION_LAKESIDE_LAB_ROOM1", "Lakeside Lab Room 1"),
    (38, "LOCATION_LAKESIDE_LAB_ROOM2", "Lakeside Lab Room 2"),
    (39, "LOCATION_LAKESIDE_LAB_OFFICE", "Lakeside Lab Office"),
    (40, "LOCATION_LAKESIDE_LAB_HALL", "Lakeside Lab Hall"),
    (41, "LOCATION_FOREST_CLEARING", "Forest Clearing"),
    (42, "LOCATION_FOREST_TRAIL", "Forest Trail"),
    (43, "LOCATION_FOREST_GROVE", "Forest Grove"),
    (44, "LOCATION_FOREST_BLUE_HOUSE", "Forest Blue House"),
    (45, "LOCATION_FOREST_CAFE", "Forest Cafe"),
    (46, "LOCATION_FOREST_ITEM_SHOP", "Forest Item Shop"),
    (47, "LOCATION_FOREST_DECK_SHOP", "Forest Deck Shop"),
    (48, "LOCATION_CEMETERY_EXTERIOR", "Cemetery Exterior"),
    (49, "LOCATION_CEMETERY_CHAPEL", "Cemetery Chapel"),
    (50, "LOCATION_CEMETERY_STORAGE", "Cemetery Storage"),
    (51, "LOCATION_CEMETERY_LIBRARY", "Cemetery Library"),
    (52, "LOCATION_CEMETERY_BASEMENT", "Cemetery Basement"),
    (53, "LOCATION_HIGHWAY", "Highway"),
    (54, "LOCATION_FOREST_REST_ROOM", "Forest Rest Room"),
    (55, "LOCATION_CABLE_CAR_STATION", "Cable Car Station"),
    (56, "LOCATION_CABLE_CAR", "Cable Car"),
    (57, "LOCATION_HIGHWAY_STATION_WAITING", "Highway Station Waiting"),
    (58, "LOCATION_HIGHWAY_STATION_PLATFORM", "Highway Station Platform"),
    (59, "LOCATION_FOREST_AVENUE", "Forest Avenue"),
    (60, "LOCATION_CLOCK_TOWER_SQUARE_SOUTH", "Clock Tower Square S"),
]

# Build music ID → constant name from the enum header
_MUSIC_NAMES: dict[int, str] = {}
_music_header = (ROOT / "include" / "constants" / "music_ids.h").read_text()
for m in re.finditer(r'(\w+)\s*=\s*(0x[0-9A-Fa-f]+)', _music_header):
    _MUSIC_NAMES[int(m.group(2), 16)] = m.group(1)


def read_ptr_table(rom: bytes, addr: int, count: int) -> list[int]:
    off = addr - ROM_BASE
    return [struct.unpack_from("<I", rom, off + i * 4)[0] for i in range(count)]


def _collision_to_blocked(rom: bytes, ptr: int) -> list[list[int]]:
    """Compress collision grid into [x, y, w, h] rects (values >= 4096 = blocked)."""
    off = ptr - ROM_BASE
    raw = struct.unpack_from("<9600H", rom, off)
    grid = [[1 if raw[y * CW + x] >= BLOCKED_THRESHOLD else 0 for x in range(CW)] for y in range(CH)]
    visited = [[False] * CW for _ in range(CH)]
    rects = []
    for y in range(CH):
        for x in range(CW):
            if not grid[y][x] or visited[y][x]:
                continue
            w = 0
            while x + w < CW and grid[y][x + w] and not visited[y][x + w]:
                w += 1
            h = 1
            while y + h < CH:
                ok = True
                for dx in range(w):
                    if not grid[y + h][x + dx] or visited[y + h][x + dx]:
                        ok = False
                        break
                if not ok:
                    break
                h += 1
            for dy in range(h):
                for dx in range(w):
                    visited[y + dy][x + dx] = True
            rects.append([x, y, w, h])
    return rects


def _extract_connections(rom: bytes, mapdata_ptr: int, collision_ptr: int,
                         mid: int) -> list[dict]:
    """Read the 5 connection slots from a map's MapData.

    Each slot is at MapData+0x168+i*8 with format:
      [script_ptr:4][target_map_id:1][target_conn:1][pad:2]

    Then scan collision edges to find which edge+range each slot triggers on.
    """
    state0_ptr = struct.unpack_from("<I", rom, mapdata_ptr - ROM_BASE)[0]
    base = state0_ptr - ROM_BASE

    # Slot data
    slot_targets = []
    for i in range(5):
        off = base + 0x168 + i * 8
        tgt_id, tgt_conn = struct.unpack_from("<BB", rom, off + 4)
        slot_targets.append((tgt_id, tgt_conn))

    # Scan collision edges for connection bits
    col_off = collision_ptr - ROM_BASE
    col = struct.unpack_from("<9600H", rom, col_off)

    edge_defs = [
        ("top",    [(x, 0) for x in range(CW)]),      # edge 2: top (up direction)
        ("bottom", [(x, CH - 1) for x in range(CW)]),  # edge 0: bottom (down direction)
        ("left",   [(0, y) for y in range(CH)]),       # edge 1: left
        ("right",  [(CW - 1, y) for y in range(CH)]),  # edge 3: right
    ]

    connections: list[dict] = []
    slots_with_edge: set[int] = set()

    for edge_name, edge_coords in edge_defs:
        slot_type_ranges: dict[tuple[int, str], list[int]] = {}
        for cx, cy in edge_coords:
            v = col[cy * CW + cx]
            slot_bits = v & 0x700
            if not slot_bits:
                continue
            slot = slot_bits >> 8
            conn_type = "world" if (v & 0x4000) else "map"
            key = (slot, conn_type)
            if key not in slot_type_ranges:
                slot_type_ranges[key] = []
            coord = cx if edge_name in ("top", "bottom") else cy
            slot_type_ranges[key].append(coord)

        for (slot, conn_type), coords in sorted(slot_type_ranges.items()):
            tgt_id, tgt_conn = slot_targets[slot]
            if conn_type == "world":
                tgt_const = "WORLD_MAP"
            elif tgt_id == mid or tgt_id >= 61:
                continue
            else:
                tgt_const = (LOCATIONS[tgt_id][1]
                             if tgt_id < len(LOCATIONS)
                             else f"LOCATION_{tgt_id}")

            slots_with_edge.add(slot)

            coords = sorted(set(coords))
            ranges = []
            start = coords[0]
            end = start
            for c in coords[1:]:
                if c == end + 1:
                    end = c
                else:
                    ranges.append([start, end])
                    start = end = c
            ranges.append([start, end])

            # Emit one rect per contiguous range
            for r in ranges:
                s, e = r
                if edge_name in ("top", "bottom"):
                    y = 0 if edge_name == "top" else CH - 1
                    rect = [s, y, e - s + 1, 1]
                else:  # left, right
                    x = 0 if edge_name == "left" else CW - 1
                    rect = [x, s, 1, e - s + 1]
                connections.append({
                    "rect": rect,
                    "target": tgt_const,
                    "slot": slot,
                })

    # Second pass: slots with valid targets but no edge collision bits
    # (door/script triggers that teleport the player, not walk-off-edge)
    for slot, (tgt_id, tgt_conn) in enumerate(slot_targets):
        if slot in slots_with_edge:
            continue
        if tgt_id == 0 or tgt_id == mid or tgt_id >= 61:
            continue
        tgt_const = (LOCATIONS[tgt_id][1]
                     if tgt_id < len(LOCATIONS)
                     else f"LOCATION_{tgt_id}")
        connections.append({
            "target": tgt_const,
            "slot": slot,
        })

    return sorted(connections, key=lambda c: (
        c["rect"][1] if "rect" in c else 999,
        c["rect"][0] if "rect" in c else 0,
    ))


def _read_player_start(rom: bytes, mapdata_ptr: int) -> dict:
    """Read playerInitialState[5] from ROM for a map.

    Returns dict keyed by slot index (int): {0: {"x": 60, "y": 16, "dir": "DIRECTION_DOWN"}, ...}
    Only includes slots where spriteId != 0xFFFF (unused slot).
    Each entry is 20 bytes: i16 spriteId, u8 dir, u8 pad, u16 x, u16 y,
    u32 scriptA, u32 scriptR, u32 bitfield.
    """
    state0_ptr = struct.unpack_from("<I", rom, mapdata_ptr - ROM_BASE)[0]
    base = state0_ptr - ROM_BASE
    start: dict[int, dict] = {}
    for slot in range(5):
        off = base + 0x190 + slot * 20
        sprite_id, dir_, _, x, y, _, _, _ = struct.unpack_from(
            "<h B B H H I I I", rom, off)
        if sprite_id == -1:
            continue  # unused slot
        dir_name = DIRECTION_NAMES.get(dir_, str(dir_))
        start[slot] = {"x": x, "y": y, "dir": dir_name}
    return start


def _png_tile_dims(png_path: Path) -> dict:
    """Derive tile grid dimensions from a PNG. Returns {tile_w, tile_h} or None."""
    try:
        im = Image.open(png_path)
        return {"tile_w": im.width // 8, "tile_h": im.height // 8}
    except (FileNotFoundError, AttributeError, OSError):
        return None


def _compact_arrays(text: str) -> str:
    """Collapse multi-line integer arrays (blocked rects) to one line."""
    def _flatten(m):
        nums = re.findall(r'\d+', m.group(1))
        tail = m.group(2) or ''
        return '[' + ', '.join(nums) + ']' + tail
    return re.sub(r'\[\s*\n\s+(\d[\d,\s]*\d)\s*\n\s+\](,?)', _flatten, text)


def main() -> int:
    if not ROM_PATH.exists():
        print(f"error: {ROM_PATH} not found")
        return 1

    rom = ROM_PATH.read_bytes()

    tileset_ptrs = read_ptr_table(rom, 0x08E119F4, 61)
    collision_ptrs = read_ptr_table(rom, 0x08E11DC4, 61)
    mapdata_ptrs = read_ptr_table(rom, 0x08E19274, 61)

    # Read music from gMapData[id][0]->music at offset 0x1F4
    music_by_map: dict[int, int] = {}
    for mid in range(61):
        state0_ptr = struct.unpack_from("<I", rom, mapdata_ptrs[mid] - ROM_BASE)[0]
        music_by_map[mid] = struct.unpack_from("<H", rom, state0_ptr - ROM_BASE + 0x1F4)[0]

    if Image is None:
        check_roof = False
        print("warning: Pillow not available, cannot check roof layers")
    else:
        check_roof = True

    manifest = []
    for mid, const, label in LOCATIONS:
        ground_png = f"src_custom/assets/maps/map_{mid:02d}_ground.png"
        roof_png = f"src_custom/assets/maps/map_{mid:02d}_roof.png"

        # Collision
        blocked = _collision_to_blocked(rom, collision_ptrs[mid])

        # Connections
        connections = _extract_connections(
            rom, mapdata_ptrs[mid], collision_ptrs[mid], mid)

        # Player start positions per connection slot
        start = _read_player_start(rom, mapdata_ptrs[mid])

        # Music constant name
        music_val = music_by_map[mid]
        music_name = _MUSIC_NAMES.get(music_val, f"0x{music_val:X}")

        has_roof = False
        if check_roof:
            roof_path = ASSETS_DIR / f"map_{mid:02d}_roof.png"
            if roof_path.exists():
                im = Image.open(roof_path)
                for y in range(im.height):
                    for x in range(im.width):
                        if im.getpixel((x, y)) != (0, 0, 0):
                            has_roof = True
                            break
                    if has_roof:
                        break

        # Tile dimensions from ground PNG
        dims = _png_tile_dims(ROOT / ground_png)

        # Merge spawn data into each connection entry
        for conn in connections:
            slot = conn.get("slot")
            if slot in start:
                conn["spawn"] = start[slot]

        entry = {
            "id": mid,
            "constant": const,
            "label": label,
            "images": {
                "ground": ground_png,
            },
            "tiles": dims or {"tile_w": 32, "tile_h": 32},
            "music": music_name,
            "collision": {
                "blocked": blocked,
            },
            "connections": connections,
        }
        if has_roof:
            entry["images"]["roof"] = roof_png

        manifest.append(entry)

    MANIFEST_PATH.write_text(_compact_arrays(json.dumps(manifest, indent=2)) + "\n")

    print(f"Wrote {len(manifest)} entries to {MANIFEST_PATH}")
    for m in manifest:
        roof = " +roof" if "roof" in m.get("images", {}) else ""
        n_conn = len(m.get("connections", []))
        print(f"  [{m['id']:2d}] {m['constant']:60s} music={m['music']:30s}{roof} conn={n_conn}")
    return 0


if __name__ == "__main__":
    import sys
    sys.exit(main())
