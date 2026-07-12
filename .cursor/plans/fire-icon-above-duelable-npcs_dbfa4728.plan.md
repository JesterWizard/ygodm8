---
name: fire-icon-above-duelable-npcs
overview: Render an 8x8 fire icon above every duelable NPC on the overworld, gated by a runtime config option. Uses OAM entries (like the reaction bubble), tracks NPC world positions, and checks duelability via the existing ObjectHasDuelDialogue function.
todos:
  - id: add-config-field
    content: Add enable_fire_icon to RuntimeConfig struct, init, and debug menu
    status: completed
  - id: add-build-rules
    content: Add fire.4bpp and fire.gbapal build rules to graphics.mk and Makefile dependency
    status: completed
  - id: add-render-logic
    content: Add INCBIN, LoadFireIconGfx, SetFireIconOam, and hook into OverworldRunEndFrame
    status: completed
  - id: validate
    content: Run make test-cards-build to validate compilation and linking
    status: completed
isProject: false
---

# Fire Icon Above Duelable NPCs

## Summary

Add an 8x8 fire icon above every duelable overworld NPC. Always-on when `gRuntimeConfig.enable_fire_icon == TRUE` (no button toggle). Icons move with NPCs and disappear when NPCs are not duelable or not on screen.

## Files to Change

### 1. `configs/runtime.h` — add config field

Add `u8 enable_fire_icon;` inside the `RuntimeConfig` struct (before `enable_card_detail_navigation`).

### 2. `configs/runtime.c` — add default value

Add `.enable_fire_icon = TRUE,` to `gRuntimeConfigRom`.

### 3. `src_custom/debug/debug_menu_runtime_config.c` — add debug menu entry

Add `CONF("Fire Icon", enable_fire_icon),` to `sRuntimeConfigEntries[]`.

### 4. `graphics.mk` — build fire.png into 4bpp tile + palette

Add rules to convert `src_custom/assets/icons/fire.png` to `fire.4bpp` and `fire.gbapal` via `gbagfx` (no repack needed for 8x8).

### 5. `Makefile` — add dependency

Add a dependency line so the `.o` file compiling `overworld_hooks.c` depends on the generated fire.4bpp and fire.gbapal.

### 6. `src_custom/overworld_hooks.c` — INCBIN assets + render logic

- INCBIN the fire tile (32 bytes) and palette (32 bytes) as static const arrays
- Add `LoadFireIconGfx()` — DMA copies tile to OBJ VRAM at tile #0x3F8, palette to OBJ palette slot #14
- Add `SetFireIconOam()` — iterates NPC slots 1-14, checks `ObjectHasDuelDialogue(i)`, positions an OAM entry 28px above each duelable NPC, or hides off-screen for non-duelable/non-existent NPCs
- Hook into `OverworldRunEndFrame` after thought bubble, gated by `gRuntimeConfig.enable_fire_icon == TRUE`

## OAM Allocation

Use indices **50-63** (14 entries, one per NPC slot 1-14). These are currently unused.

Per-NPC OAM entry:
- `y` = `object.y * 2 - object.unk8 + gOverworld.unk24C - 28` (tight above head, matching reaction bubble offset)
- `x` = `object.x * 2 + gOverworld.unk24E - 4` (centers 8px icon on 16px-wide NPC)
- `tileNum` = 0x3F8, `paletteNum` = 14, 4bpp, 8x8 square, no flip
- When hidden: `y = 0xA0, x = 0xF0` (off-screen)

## Duelability Check

Reuse existing `ObjectHasDuelDialogue(objId)` — checks `scriptR != NULL`, `scriptR != scriptA`, and script resolves to valid data.

## Rendering Order

Call in `OverworldRunEndFrame` after thought bubble code, before `SetVBlankCallback`. The fire icons render on top of the thought bubble (higher OAM priority via lower index), which is fine since the thought bubble tracks the player, not NPCs.