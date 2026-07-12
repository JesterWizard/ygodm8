#!/usr/bin/env python3
"""Regenerate custom_map_manifest.json with images grouping + collision support.

Reads baserom.gba to extract ROM pointers and music IDs,
writes tools/custom_map_manifest.json with the new structure.
"""

from __future__ import annotations

import json
import struct
from pathlib import Path

try:
    from PIL import Image
except ImportError:
    Image = None  # type: ignore[assignment]

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
  (4, "LOCATION_CLOCK_TOWER_SQUARE_SOUTH", "Clock Tower Square S"),
  (5, "LOCATION_CLOCK_TOWER_SQUARE_SOUTHWEST", "Clock Tower Square SW"),
  (6, "LOCATION_CARD_SHOP_OUTSIDE", "Card Shop Outside"),
  (7, "LOCATION_CARD_SHOP_INSIDE", "Card Shop Inside"),
  (8, "LOCATION_PLAYER_HOUSE_OUTSIDE", "Player House Outside"),
  (9, "LOCATION_PLAYER_HOUSE_INSIDE", "Player House Inside"),
  (10, "LOCATION_CLOCK_TOWER_SQUARE_BACK_ALLEY_NORTH", "Back Alley North"),
  (11, "LOCATION_CLOCK_TOWER_SQUARE_BACK_ALLEY_NORTH_EAST", "Back Alley NE"),
  (12, "LOCATION_KAIBACORP", "KaibaCorp"),
  (13, "LOCATION_DUEL_MACHINE", "Duel Machine"),
  (14, "LOCATION_DOMINO_STATION_TURNSTILES", "Domino Station Turnstiles"),
  (15, "LOCATION_DOMINO_STATION_TRAIN_STATION", "Domino Station Train"),
  (16, "LOCATION_DUEL_EXPRESS_CARRIAGE_RIGHT", "Duel Express Right"),
  (17, "LOCATION_DUEL_EXPRESS_CARRIAGE_MIDDLE", "Duel Express Middle"),
  (18, "LOCATION_DUEL_EXPRESS_CARRIAGE_LEFT", "Duel Express Left"),
  (19, "LOCATION_ITALY_CATACOMBS_MIDDLE", "Italy Catacombs Middle"),
  (20, "LOCATION_EGYPT_EXHIBITION_TRAIN_STATION", "Egypt Exhibition Station"),
  (21, "LOCATION_EGYPT_EXHIBITION_TURNSTILES", "Egypt Exhibition Turnstiles"),
  (22, "LOCATION_EGYPT_EXHIBITION_ARTWORK", "Egypt Exhibition Artwork"),
  (23, "LOCATION_EGYPT_EXHIBITION_MILLENNIUM_GUARDIAN", "Egypt Exhibition Guardian"),
  (24, "LOCATION_DOMINO_PIER_DOCKS", "Domino Pier Docks"),
  (25, "LOCATION_DOMINO_PIER_CASINO_LEFT_ROOM", "Pier Casino Left"),
  (26, "LOCATION_DOMINO_PIER_CASINO_MAIN_ROOM", "Pier Casino Main"),
  (27, "LOCATION_DOMINO_PIER_MILLENNIUM_GUARDIAN", "Pier Millennium Guardian"),
  (28, "LOCATION_ITALY_CATACOMBS_LEFT", "Italy Catacombs Left"),
  (29, "LOCATION_ITALY_CATACOMBS_RIGHT", "Italy Catacombs Right"),
  (30, "LOCATION_ITALY_MILLENNIUM_GUARDIAN", "Italy Millennium Guardian"),
  (31, "LOCATION_CHINA_GREAT_WALL_ENTRANCE", "Great Wall Entrance"),
  (32, "LOCATION_CHINA_GREAT_WALL", "Great Wall"),
  (33, "LOCATION_CHINA_GREAT_WALL_MILLENNIUM_GUARDIAN", "Great Wall Guardian"),
  (34, "LOCATION_CANADA_RUINS_OUTSIDE", "Canada Ruins Outside"),
  (35, "LOCATION_CANADA_RUINS_INSIDE", "Canada Ruins Inside"),
  (36, "LOCATION_CANADA_RUINS_MILLENNIUM_GUARDIAN", "Canada Ruins Guardian"),
  (37, "LOCATION_GALAPAGOS_BEACH", "Galapagos Beach"),
  (38, "LOCATION_GALAPAGOS_FOREST", "Galapagos Forest"),
  (39, "LOCATION_GALAPAGOS_TEMPLE", "Galapagos Temple"),
  (40, "LOCATION_PEGASUS_ISLAND_CABLE_CAR_BOTTOM_OUTSIDE", "Cable Car Bottom"),
  (41, "LOCATION_PEGASUS_ISLAND_CABLE_CAR_INSIDE", "Cable Car Inside"),
  (42, "LOCATION_PEGASUS_ISLAND_CABLE_CAR_TOP_OUTSIDE", "Cable Car Top"),
  (43, "LOCATION_PEGASUS_ISLAND_DUNGEON_ENTRANCE", "Dungeon Entrance"),
  (44, "LOCATION_PEGASUS_ISLAND_DUNGEON_LAVA_ROOM_SOUTH", "Dungeon Lava South"),
  (45, "LOCATION_PEGASUS_ISLAND_DUNGEON_CLIFF", "Dungeon Cliff"),
  (46, "LOCATION_PEGASUS_ISLAND_DUNGEON_LAVA_ROOM_NORTH", "Dungeon Lava North"),
  (47, "LOCATION_PEGASUS_ISLAND_DUNGEON_BRIDGE", "Dungeon Bridge"),
  (48, "LOCATION_PEGASUS_ISLAND_DUNGEON_STAIRCASE", "Dungeon Staircase"),
  (49, "LOCATION_PEGASUS_ISLAND_DUNGEON_RUINS", "Dungeon Ruins"),
  (50, "LOCATION_PEGASUS_CASTLE_OUTSIDE", "Pegasus Castle Outside"),
  (51, "LOCATION_PEGASUS_CASTLE_HALLWAY", "Pegasus Castle Hallway"),
  (52, "LOCATION_PEGASUS_CASTLE_LEFT_ROOM", "Pegasus Castle Left"),
  (53, "LOCATION_PEGASUS_CASTLE_RIGHT_ROOM", "Pegasus Castle Right"),
  (54, "LOCATION_PEGASUS_CASTLE_DUEL_ROOM", "Pegasus Castle Duel Room"),
  (55, "LOCATION_PEGASUS_CASTLE_RESHEF_TABLET_ROOM", "Reshef Tablet Room"),
  (56, "LOCATION_HALL_OF_ETERNITY", "Hall of Eternity"),
  (57, "LOCATION_KAIBA_LAND", "Kaiba Land"),
  (58, "LOCATION_CLOCK_TOWER_SQUARE_NORTH_WEST2_TODO", "Clock Tower NW2 (TODO)"),
  (59, "LOCATION_EGYPT", "Egypt"),
  (60, "LOCATION_EGYPT_MARIK_ROOM", "Egypt Marik Room"),
]


def read_ptr_table(rom: bytes, addr: int, count: int) -> list[int]:
    off = addr - ROM_BASE
    return [struct.unpack_from("<I", rom, off + i * 4)[0] for i in range(count)]


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
        if mid == 41:
            entry["images"]["cable_car_overlay"] = f"src_custom/assets/maps/map_41_cable.png"

        manifest.append(entry)

    MANIFEST_PATH.write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"Wrote {len(manifest)} entries to {MANIFEST_PATH}")
    for m in manifest:
        roof = " +roof" if "roof" in m.get("images", {}) else ""
        cable = " +cable" if "cable_car_overlay" in m.get("images", {}) else ""
        print(f"  [{m['id']:2d}] {m['constant']:60s} music={m['music']:3d}{roof}{cable}")
    return 0


if __name__ == "__main__":
    import sys
    sys.exit(main())
