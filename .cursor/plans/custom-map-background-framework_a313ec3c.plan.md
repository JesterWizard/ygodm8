---
name: custom-map-background-framework
overview: One-time script to extract all 61 vanilla map PNGs, plus a manifest-driven build pipeline and LynJump runtime hooks to add new custom overworld locations beyond the ROM-baked array limits.
todos:
  - id: extract-script
    content: Create tools/extract_maps.py — one-time script that reads baserom.gba and renders all 61 vanilla maps as PNGs into src_custom/assets/maps/
    status: completed
  - id: manifest-spec
    content: Define custom_map_manifest.json schema and create the manifest file
    status: completed
  - id: build-tool
    content: Create tools/build_custom_maps.py — reads manifest, validates assets, converts PNG→4bpp+LZ77, CSV→u16 tilemaps, JSON→binary collision, generates .inc files
    status: completed
  - id: build-integration
    content: Wire build_custom_maps.py into graphics.mk and validate tile budget at build time
    status: completed
  - id: runtime-hooks
    content: Add LynJump hooks in src_custom/overworld_hooks.c and map_transition_hooks.c for CopyOverworldBgGraphics, collision pointer, MapData dummy, and vanilla→custom transition redirects
    status: completed
  - id: enum-and-includes
    content: Add CUSTOM_MAP_BASE to include/overworld.h, create src_custom/maps_custom.c that includes generated dispatch tables
    status: completed
isProject: false
---

# Custom Map Background Framework

## Part 1 — Map extraction script

One-time Python script `tools/extract_maps.py` reads `baserom.gba`, decompresses tilesets, renders each of the 61 locations as a combined ground+roof PNG into `src_custom/assets/maps/`.

- Reads `ldscript.ld` for ROM addresses of `gMapTilesets`, `gLowLayerTilemaps`, `gHighLayerTilemaps`, `g8E11CD0`
- Iterates enum `OverworldLocation` (0-60) from `include/overworld.h`
- For each map: decompress LZ77 tileset, render ground tilemap with palette, overlay roof tilemap, output PNG
- Handles special cases: cable car BG3 overlay (map 0x29)

## Part 2 — Custom map manifest + build pipeline

### Manifest: `tools/custom_map_manifest.json`

One JSON array. Each entry names a custom map with these fields:

```json
{
  "name": "my_area",
  "manifest_folder": "src_custom/assets/maps/my_area/",
  "music": 42,
  "connections": {
    "from_vanilla": [
      {"vanilla_location": 5, "edge": "right", "trigger_x": 29, "trigger_y_range": [8, 12]}
    ],
    "to_vanilla": [
      {"edge": "left", "dest_location": 5, "player_x": 58, "player_y": 10, "player_dir": "left"}
    ]
  }
}
```

Folder convention (`src_custom/assets/maps/<name>/`) contains:
- `tiles.png` — indexed PNG tilesheet (palette embedded)
- `ground.csv` — 32x32 tile references
- `roof.csv` — optional 32x32 tile references (omitted = no roof layer)
- `collision.json` — 120x80 grid of u16 collision values
- `music` field in manifest
- `connections` define bidirectional transitions with vanilla maps

### Build tool: `tools/build_custom_maps.py`

Runs during `make` (wired into `graphics.mk`). Outputs go to `src_custom/generated/maps/`:

1. Per-map generated `#include` files:
   - `tileset_<name>.inc` — LZ77-compressed 4bpp tileset `const u8[]`
   - `ground_tilemap_<name>.inc` — `const u16[1024]`
   - `roof_tilemap_<name>.inc` — `const u16[1024]` or `NULL`
   - `palette_<name>.inc` — `const u16[240]` extracted from PNG
   - `collision_<name>.inc` — `const u16[9600]` from JSON
2. Dispatch table: `custom_map_dispatch.inc` — parallel arrays indexed by `mapId - CUSTOM_MAP_BASE`
3. Connection patch table: `custom_map_connections.inc` — vanilla→custom transition redirects

### Build-time validation

- Tile count check: sum unique tiles across ground+roof tilemaps must be ≤ 512. Fail `make` if exceeded.
- Manifest JSON schema validation
- CSV dimensions (must be 32x32), collision dimensions (must be 120x80)

## Part 3 — Runtime hooks (LynJump)

### Enum extension

Append to `include/overworld.h`:

```c
#define CUSTOM_MAP_BASE 61  // first custom map ID after vanilla 0-60
```

### Hook: `CopyOverworldBgGraphics` (LynJump in `src_custom/overworld_hooks.c`)

When `gOverworld.map.id >= CUSTOM_MAP_BASE`:
- Index into generated custom arrays (tileset, tilemap, palette)
- Decompress custom tileset into cbb0
- Copy custom tilemaps into sbb1F (ground) and sbb1E (roof, if present)
- Copy custom palette into gPaletteBuffer + 0x10
- Still call `sub_804F5D8()` for entity+font palettes
- Fall through to vanilla `CopyOverworldBgGraphics()` for IDs < 61

### Hook: collision pointer assignment (`gOverworld.unk23C`)

In `InitOverworld` (or wherever the collision pointer is set): when `map.id >= CUSTOM_MAP_BASE`, set `gOverworld.unk23C` to the custom collision array instead of `gMapCollisions[map.id]`.

### Hook: MapData lookup

Vanilla code does `gMapData[map.id][state]->...` for NPC placements. Since custom maps use event scripts for NPCs (not MapData), intercept the lookup and return a zeroed dummy `MapData` struct to prevent null-pointer crashes. Custom MapData has:
- `objects[0].spriteId = -1` (no NPCs)
- `playerInitialState` set from connection direction data in the manifest
- `music` from manifest

### Hook: map transition redirection

When the player triggers a transition on a vanilla map that should go to a custom map (defined by `from_vanilla` connections in the manifest), intercept `sub_804EF84` (or wherever `LoadMap` happens) and redirect the destination location to the custom map ID. This requires patching the collision-match in `code_8051958.c` or the transition function itself.

For custom→vanilla transitions: the custom collision JSON already encodes the connection edges, and the custom MapData dummy has `playerInitialState` for each connection direction. No additional hook needed at runtime — the existing transition code handles it.

## Part 4 — Memory

All custom map assets live in ROM (compiled into the `.gba` via `#include`). At runtime:
- Only ONE map's tileset+tilemap+palette+metatile lives in EWRAM at a time (cbb0 + sbb1E/sbb1F + palette buffer), same as vanilla.
- The collision grid (9600 u16 = 19.2 KB) is also loaded on demand. Vanilla keeps it in ROM and points to it; custom stays in ROM too.
- No additional persistent EWRAM/IWRAM allocation needed beyond small dispatch tables (< 1 KB).

## Part 5 — File map

| File | Role |
|------|------|
| `tools/extract_maps.py` | One-time baserom reader, renders vanilla map PNGs |
| `tools/custom_map_manifest.json` | Declares all custom maps |
| `tools/build_custom_maps.py` | Build-time generator: PNG→4bpp, CSV→u16[], JSON collision→binary |
| `src_custom/assets/maps/<name>/tiles.png` | Indexed PNG tilesheet |
| `src_custom/assets/maps/<name>/ground.csv` | 32x32 tile references |
| `src_custom/assets/maps/<name>/roof.csv` | Optional 32x32 roof layer |
| `src_custom/assets/maps/<name>/collision.json` | 120x80 u16 grid |
| `src_custom/generated/maps/*.inc` | Build outputs (included by C) |
| `src_custom/overworld_hooks.c` | `CopyOverworldBgGraphics__Replacement`, collision hook, MapData dummy |
| `src_custom/map_transition_hooks.c` | Map transition redirection for vanilla→custom |
| `include/overworld.h` | `CUSTOM_MAP_BASE` define |
| `graphics.mk` | Wire `build_custom_maps.py` into `make`