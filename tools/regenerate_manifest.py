"""Regenerate custom_map_manifest.json with images grouping + collision support.

Reads baserom.gba to extract ROM pointers and music IDs,
writes tools/custom_map_manifest.json with the new structure.
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


def read_ptr_table(rom: bytes, addr: int, count: int) -> list[int]:
    off = addr - ROM_BASE
    return [struct.unpack_from("<I", rom, off + i * 4)[0] for i in range(count)]


CW, CH = 120, 80  # collision grid


def _collision_to_blocked(rom: bytes, ptr: int) -> list[list[int]]:
    """Read u16 collision grid from ROM and compress same-valued cells into
    [x, y, w, h, value] rectangles using a greedy scan."""
    off = ptr - ROM_BASE
    raw = struct.unpack_from("<9600H", rom, off)
    val = [[raw[y * CW + x] for x in range(CW)] for y in range(CH)]
    visited = [[False] * CW for _ in range(CH)]

    rects = []
    for y in range(CH):
        for x in range(CW):
            v = val[y][x]
            if v == 0 or visited[y][x]:
                continue
            # max width from (x, y) in current row for this value
            w = 0
            while x + w < CW and val[y][x + w] == v and not visited[y][x + w]:
                w += 1
            # try to extend height
            h = 1
            while y + h < CH:
                ok = True
                for dx in range(w):
                    if val[y + h][x + dx] != v or visited[y + h][x + dx]:
                        ok = False
                        break
                if not ok:
                    break
                h += 1
            # mark visited
            for dy in range(h):
                for dx in range(w):
                    visited[y + dy][x + dx] = True
            rects.append([x, y, w, h, v])
    return rects


def _compact_arrays(text: str) -> str:
    """Collapse multi-line integer arrays (e.g. blocked rects) to one line."""
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
    low_tm_ptrs = read_ptr_table(rom, 0x08E11AE8, 61)
    high_tm_ptrs = read_ptr_table(rom, 0x08E11BDC, 61)
    palette_ptrs = read_ptr_table(rom, 0x08E11CD0, 61)
    collision_ptrs = read_ptr_table(rom, 0x08E11DC4, 61)
    mapdata_ptrs = read_ptr_table(rom, 0x08E19274, 61)

    # Read music from gMapData[id][0]->music at offset 0x1F4
    music_by_map = {}
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

        # Extract and compress collision data
        blocked = _collision_to_blocked(rom, collision_ptrs[mid])

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

        entry = {
            "id": mid,
            "constant": const,
            "label": label,
            "images": {
                "ground": ground_png,
            },
            "music": music_by_map[mid],
            "collision": {
                "blocked": blocked,
            },
            "rom": {
                "tileset_ptr": f"0x{tileset_ptrs[mid]:08X}",
                "ground_tilemap_ptr": f"0x{low_tm_ptrs[mid]:08X}",
                "roof_tilemap_ptr": f"0x{high_tm_ptrs[mid]:08X}",
                "palette_ptr": f"0x{palette_ptrs[mid]:08X}",
                "collision_ptr": f"0x{collision_ptrs[mid]:08X}",
                "mapdata_ptr": f"0x{mapdata_ptrs[mid]:08X}",
            },
        }
        if has_roof:
            entry["images"]["roof"] = roof_png

        manifest.append(entry)

    MANIFEST_PATH.write_text(_compact_arrays(json.dumps(manifest, indent=2)) + "\n")

    print(f"Wrote {len(manifest)} entries to {MANIFEST_PATH}")
    for m in manifest:
        roof = " +roof" if "roof" in m.get("images", {}) else ""
        cable = " +cable" if "cable_car_overlay" in m.get("images", {}) else ""
        print(f"  [{m['id']:2d}] {m['constant']:60s} music={m['music']:3d}{roof}{cable}")
    return 0


if __name__ == "__main__":
    import sys
    sys.exit(main())
