# Custom Maps — Overworld Background System

---

## Index

- [Introduction](#introduction)
- [Quick start](#quick-start)
- [Manifest structure](#manifest-structure)
- [Swapping graphics between maps](#swapping-graphics-between-maps)
- [Adding custom collision](#adding-custom-collision)
- [Creating a brand-new map](#creating-a-brand-new-map)
- [Runtime config toggle](#runtime-config-toggle)
- [Tools reference](#tools-reference)
- [Code locations](#code-locations)
- [Limitations](#limitations)

---

## Introduction

The overworld is a big tilemap with 61 vanilla map locations (clock tower square, card shop, player house, etc.). Each map has tiles, a ground layer, optionally a roof layer, collision data, and a music track — all burned into the ROM.

This system lets you:

- **Swap** which map's graphics appear at a location (e.g. make the player house look like the clock tower square)
- **Override** collision per map with simple rectangles
- **Create** entirely new maps from scratch using indexed PNG tilesheets and CSV tilemaps

All editing happens through a single JSON file: `tools/custom_map_manifest.json`. No C code, no assembly.

---

## Quick start

**Change map 9 to show map 0's graphics:**

1. Open `tools/custom_map_manifest.json`
2. Find entry `"id": 9` (`LOCATION_PLAYER_HOUSE_INSIDE`)
3. Change `images.ground` to `"src_custom/assets/maps/map_00_ground.png"`
4. Change `images.roof` to `"src_custom/assets/maps/map_00_roof.png"`
5. Enable the feature: set `enable_manifest_map_overrides = TRUE` in `configs/runtime.c`
6. Rebuild: `make -j$(nproc)`

Result: entering the player house now shows the clock tower square's graphics. NPCs, scripts, collision, and music stay as map 9.

---

## Manifest structure

Each entry in the JSON array describes one map location:

```json
{
  "id": 9,
  "constant": "LOCATION_PLAYER_HOUSE_INSIDE",
  "label": "Player House Inside",
  "images": {
    "ground": "src_custom/assets/maps/map_09_ground.png",
    "roof": "src_custom/assets/maps/map_09_roof.png"
  },
  "tiles": {
    "tile_w": 32,
    "tile_h": 32
  },
  "music": "MUSIC_HOME",
  "collision": {
    "blocked": []
  },
  "connections": [
    {"edge": 2, "range": [0, 119], "target": "LOCATION_LUMBERYARD"}
  ]
}
```

| Field | Always needed? | What it does |
|-------|---------------|--------------|
| `id` | Yes | Map numeric ID (0–60 vanilla, ≥61 custom). Must match the `LOCATION_*` enum. |
| `constant` | Yes | The C enum name from `include/overworld.h`. Reference this in event scripts. |
| `label` | No | Human-readable name for debug menus. |
| `images` | Yes | PNG paths for the ground and optional roof layers. |
| `tiles` | Yes | Tile grid dimensions derived from the PNG (`width/8`, `height/8`). |
| `music` | Yes | Music track constant name from `include/constants/music_ids.h` (e.g. `MUSIC_CLOCK_TOWER_SQUARE`). |
| `collision` | No | Custom collision overrides — `blocked` rects `[x, y, w, h]`. |
| `connections` | Yes | Map edge exits — which edges lead to which maps. Auto-detected from ROM. |

### The `images` field

All image paths are relative to the repo root:

```json
"images": {
  "ground": "src_custom/assets/maps/map_00_ground.png",
  "roof": "src_custom/assets/maps/map_00_roof.png"
}
```

- **`ground`** (required) — the ground layer image
- **`roof`** (optional) — roof/overhang layer that renders on top. Omit the key entirely if the map has no roof (the manifest auto-detects this from the extracted PNG).
- **`cable_car_overlay`** — special case for map 41 (cable car interior BG3 window overlay)

### The `connections` field

Each entry lists the map's edge exits, auto-detected from the ROM's collision data:

```json
"connections": [
  {"edge": 2, "range": [48, 72], "target": "LOCATION_CEMETERY_CHAPEL"},
  {"edge": 3, "range": [61, 78], "target": "LOCATION_FOREST_DECK_SHOP"}
]
```

| Field | Description |
|-------|-------------|
| `edge` | Direction: 0=bottom, 1=left, 2=top, 3=right (matching the game's internal enum). |
| `range` | Tile coordinate range on that edge that triggers the exit. Single range like `[48, 72]`, or multiple ranges like `[[16, 24], [51, 119]]` for disjoint triggers. |
| `target` | Target map's constant name (e.g. `LOCATION_CEMETERY_CHAPEL`) or `WORLD_MAP` for world map triggers. |

The `range` is in tile coordinates:
- **top/bottom edges**: x tiles (0–119)
- **left/right edges**: y tiles (0–79)

### The `tiles` field

Derived automatically from the ground PNG dimensions:

```json
"tiles": {
  "tile_w": 32,
  "tile_h": 32
}
```

`tile_w` = PNG width ÷ 8, `tile_h` = PNG height ÷ 8. All vanilla maps are 32×32 tiles (256×256 px).

---

## Swapping graphics between maps

To make map A show map B's art, change the `images.ground` (and `images.roof`) paths in entry A to point to B's PNGs:

```json
// Before: map 9 shows its own art
{ "id": 9, "images": { "ground": "src_custom/assets/maps/map_09_ground.png" } }

// After: map 9 shows map 0's art instead
{ "id": 9, "images": { "ground": "src_custom/assets/maps/map_00_ground.png" } }
```

At build time, the script detects the source map from the filename (`map_00_ground.png` → source map 0) and generates a redirect table. At runtime, `CopyOverworldBgGraphics` is called with the source map's ID instead of the current map's ID. Everything else (NPCs, scripts, collision, music) stays with the original map.

**Important:** This only changes **graphics** (tiles, tilemaps, palette). To also change collision, add a `collision` block (see below).

---

## Adding custom collision

The collision grid is 120 tiles wide × 80 tiles tall. Each tile is either passable (0) or blocked (1). Two tiles per screen pixel.

Add a `collision` block to any entry:

```json
"collision": {
  "blocked": [
    [0, 0, 120, 1],     // top border: x=0, y=0, width=120, height=1
    [0, 79, 120, 1],    // bottom border
    [0, 0, 1, 80],     // left border
    [119, 0, 1, 80],   // right border
    [20, 20, 10, 10],  // a 10×10 blocked area in the middle
    [50, 15, 8, 6]     // another blocked area
  ]
}
```

Each map entry contains the **real collision data extracted from the ROM**, stored as 80 hex-encoded rows. Each hex string is 480 characters: 120 `u16` values, each as 4 hex digits. For example, map 9's collision starts like:

```
"collision": {
  "data": [
    "000100010001000100010001...",   // row 0: 120 values
    "000100010001000100010001...",   // row 1
    ...
  ]
}
```

- `0001` = wall blocked
- `1000` = passable (direction flag)
- `0000` = fully passable
- Other values encode different collision behaviors (direction restrictions, etc.)

To edit collision, you can replace any hex group. For a large change, it's easier to delete the `data` array and use blocked rectangles instead:

```json
"collision": {
  "blocked": [
    [0, 0, 120, 1],     // top border: x=0, y=0, width=120, height=1
    [0, 79, 120, 1],    // bottom border
    ...
  ]
}
```

The `blocked` format rasterizes blocked tiles to `0001`. Everything else becomes `0000` (fully passable). This loses the bitflag information but is much easier to edit by hand. For full flag fidelity, edit the hex `data` rows directly.

At runtime, `gOverworld.unk23C` is redirected to the custom collision data (gated by `enable_manifest_map_overrides`).

**Tips:**
- The overworld collision viewer in the debug menu (`R` on the overworld) shows blocked tiles as red overlays
- Rectangles outside the 120×80 grid are clamped and a build warning is printed
- Multiple rectangles overlap cleanly
- Omit `collision` entirely or use `"collision": null` to keep the ROM's original collision

### Overriding map connections

Each manifest connection includes a `slot` (0-4) identifying which of the 5 hardware connection slots it maps to. By default the manifest stores the ROM's own values, producing zero overrides at build time.

To redirect where a map transition goes, change the `target` constant:

```json
// Map 9 (Clock Tower Foyer): instead of going to Clock Tower Entrance,
// make it go to a different map
{
  "id": 9,
  "connections": [
    {"slot": 0, "target": "LOCATION_SOUTH_AVENUE_EAST"}
  ]
}
```

The build script reads the ROM's per-slot targets, compares them to the manifest, and emits only the differences into `manifest_connection_overrides.inc`. At runtime, `sub_80523EC__Replacement` checks the override table before using the ROM-sourced value. Gated by `enable_manifest_map_overrides`.

This works for both edge-triggered transitions (walking off the map) and script-triggered transitions (doors, elevators, etc).

---

## Creating a brand-new map

For maps with ID ≥ 61 (`CUSTOM_MAP_BASE`), you provide your own assets in a folder. This is for entirely new locations not in the original game.

### Step 1: Create a manifest entry

Add to `tools/custom_map_manifest.json`:

```json
{
  "name": "my_new_zone",
  "manifest_folder": "src_custom/assets/maps/my_new_zone",
  "music": 12,
  "connections": {
    "from_vanilla": [
      {
        "vanilla_location": 0,
        "edge": 0,
        "trigger_x": 15,
        "trigger_y_range": [0, 31],
        "custom_map_id": 61
      }
    ]
  }
}
```

### Step 2: Prepare assets

Create a folder at `src_custom/assets/maps/my_new_zone/` with:

| File | Required | Format |
|------|----------|--------|
| `tiles.png` | Yes | **Indexed** (palette) PNG, 256×256 pixels max, ≤512 unique 8×8 tiles |
| `ground.csv` | Yes | 32×32 comma-separated tile indices (hex or decimal) |
| `roof.csv` | No | Same format, for the roof layer |
| `collision.json` | No | 120×80 grid, `[[x,y,w,h], ...]` rect format |

**`tiles.png` rules:**
- Must be an indexed PNG with a palette (P mode in Pillow)
- Each 8×8 block in the PNG is one tile
- Max 512 unique tiles
- First palette entry (index 0) should be the transparent/background color

**`ground.csv` / `roof.csv` example:**
```csv
00,01,02,03,04,05,06,07,08,09,0A,0B,0C,0D,0E,0F,10,11,12,13,14,15,16,17,18,19,1A,1B,1C,1D,1E,1F
... (32 rows × 32 columns)
```

### Step 3: Wire up connections

The `connections.from_vanilla` array defines where the player can enter your custom map from the overworld. Each entry specifies:

| Field | Description |
|-------|-------------|
| `vanilla_location` | Source map ID (the map the player is standing on) |
| `edge` | Which edge triggers the transition: 0=down, 1=left, 2=up, 3=right |
| `trigger_x` | Player X tile on the source map that triggers this |
| `trigger_y_range` | `[min, max]` Y tile range on the source map |
| `custom_map_id` | Destination ID (61, 62, etc.) |

### Step 4: Build

```bash
make -j$(nproc)
```

The build tool compresses the tileset via LZ77, generates per-map `.inc` files and dispatch tables into `src_custom/generated/maps/`.

---

## Runtime config toggle

The graphics override feature is gated behind a config flag so it can be enabled/disabled per build:

| File | Field | Default |
|------|-------|---------|
| `configs/runtime.h` | `enable_manifest_map_overrides` | — |
| `configs/runtime.c` | `.enable_manifest_map_overrides` | `FALSE` |

Set to `TRUE` to activate manifest-driven graphics redirects and custom collision.

---

## Tools reference

| Command | When to run | What it does |
|---------|-------------|--------------|
| `python3 tools/extract_maps.py` | After adding new vanilla maps | Extracts all 61 maps from `baserom.gba` as separate ground + roof PNGs into `src_custom/assets/maps/`. |
| `python3 tools/regenerate_manifest.py` | After re-extracting maps | Rebuilds `tools/custom_map_manifest.json` from scratch using ROM data — connections, music, collision, tiles. **Overwrites everything**; save custom entries (with `name` fields) separately and re-add after regeneration. |
| `python3 tools/build_custom_maps.py` | Automatically during `make` | Reads manifest, generates dispatch tables and override tables into `src_custom/generated/maps/`. |
| `make -j$(nproc)` | After any manifest changes | Full rebuild including custom map assets. |

**Workflow for vanilla map overrides (no new assets):**

1. Edit `tools/custom_map_manifest.json` — change `images.ground`/`roof` paths
2. Optionally add `collision` blocks
3. Build: `make -j$(nproc)`

**Workflow for a brand-new map:**

1. Create asset folder with `tiles.png`, `ground.csv`
2. Add a manifest entry with a `name` and `manifest_folder`
3. Build: `make -j$(nproc)`

---

## Code locations

| Component | File | Description |
|-----------|------|-------------|
| Manifest | `tools/custom_map_manifest.json` | All map definitions: IDs, image paths, music constants, collision rects, connections, tile dims |
| Extract script | `tools/extract_maps.py` | Renders 61 vanilla maps as PNGs from ROM binary |
| Regenerate script | `tools/regenerate_manifest.py` | Rebuilds manifest JSON from ROM: connections, music constants, collision rects, PNG tile dims |
| Build script | `tools/build_custom_maps.py` | Generates `.inc` dispatch tables, graphics source table, collision override table |
| Generated dispatch | `src_custom/generated/maps/custom_map_dispatch.inc` | Custom map (≥61) asset pointer tables |
| Graphics sources | `src_custom/generated/maps/manifest_map_sources.inc` | `u16[61]` — which map ID's graphics each vanilla map pulls from |
| Collision overrides | `src_custom/generated/maps/manifest_collision_overrides.inc` | `u16*[61]` — custom collision data per map (NULL = use ROM) |
| Runtime hook | `src_custom/debug/overworld_debug_overlay_hooks.c` | Reads override tables, redirects graphics/collision in `OverworldLoadGraphics__Replacement` |
| Custom map API | `src_custom/maps_custom.c` | Getter functions for custom (≥61) map tilesets, tilemaps, palettes |
| Custom map header | `include/maps_custom.h` | Public API declarations and runtime state vars |
| Map enum + base | `include/overworld.h` | `enum OverworldLocation` (0–60), `#define CUSTOM_MAP_BASE 61` |
| Runtime config | `configs/runtime.c` | `enable_manifest_map_overrides` toggle |
| Runtime config header | `configs/runtime.h` | `RuntimeConfig` struct with the toggle field |
| Transition hooks | `src_custom/map_transition_hooks.c` | Routes map transitions for IDs ≥61 to safe dummy load + deferred override |
| Makefile | `Makefile` | Build rules for custom map generation |

---

## Limitations

- **Graphics overrides only change tiles, tilemaps, and palettes.** NPCs, NPC scripts, connection edges, map states, and music stay with the original map ID. To change those, you need event script edits.
- **The graphics source is detected from the PNG filename.** The script parses `map_(\d+)_ground\.png` to find the source map ID. If you copy a PNG outside the `map_XX_ground.png` naming convention, the override won't activate.
- **Custom map entries (id ≥ 61) require a `name` field** to trigger the full asset pipeline. Vanilla entries (0–60) don't need a `name`.
- **Collision override only applies when `enable_manifest_map_overrides` is TRUE.** The map still uses the ROM's original collision data when the flag is off.
- **Collision is a `u16` array**, not `u8`. Each cell uses 16 bits for 1 bit of data. This matches how the vanilla code stores collision internally.
- **Map 58** (`CLOCK_TOWER_SQUARE_NORTH_WEST2_TODO`) shares pointers with map 0 — its tileset, tilemaps, and palette are identical at the ROM level. This is a vanilla bug/quirk.
- The regenerate script (`regenerate_manifest.py`) overwrites the entire manifest. If you have custom entries (with `name` fields) that you want to keep, save them separately and re-add them after regeneration.
