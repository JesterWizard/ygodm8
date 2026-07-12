# Repeatable Duel Icon

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

When browsing the overworld, not every NPC can be dueled repeatedly. Only those whose R-button script (`scriptR`) starts directly with a `DUEL()` command are repeatable duelists. Story-only duelists (like Ishizu) have a flag check before the duel — once beaten, their script branches to dialogue instead.

This feature places an 8x8 duel icon above every **repeatable** duelist's head so the player can identify who they can duel at a glance. The icon follows the NPC as it walks, appears for all eligible NPCs on screen simultaneously, and hides for non-duelable NPCs. No button press is needed — it is always on when the config toggle is TRUE.

## Plan

The feature has three layers:

1. asset build: the duel PNG is converted to a single 4bpp OBJ tile + palette
2. per-frame gfx load: tile and palette are DMA-copied to OBJ VRAM each frame
3. per-frame OAM placement: each NPC slot is checked for repeatable duels, and an OAM entry is positioned above the head

### Repeatable Duel Check

The icon uses `ObjectHasRepeatableDuel(objId)` rather than the looser `ObjectHasDuelDialogue`. This adds an extra check against the script bytecode:

- `scriptR` must be non-NULL, different from `scriptA`, and resolve to a valid script
- The resolved script's `start` data must begin with the **DUEL** command bytes (`0x40 0x30`)

Story duelists like Ishizu have `scriptR.start` that begins with **CHECK_FLAG** (`0x40 0x37`) — the DUEL command is in a branch, not the entry. The icon correctly skips them without any hard-coded deny list.

### Position Constants

The icon's position above the NPC is controlled by two `#define` constants at the top of `overworld_hooks.c`:

| Constant | Value | Effect |
|----------|-------|--------|
| `DUEL_ICON_X_OFFSET` | 4 | Pixels to left-shift from the NPC center (higher = more left) |
| `DUEL_ICON_Y_OFFSET` | 28 | Pixels above the NPC sprite base (higher = higher on screen) |

Both are positive integers. To move the icon lower, decrease `DUEL_ICON_Y_OFFSET`. To move it right, decrease `DUEL_ICON_X_OFFSET` (or set it to 0 for dead center on the 16px-wide NPC).

### OAM Layout

| OAM indices | Purpose | Tiles |
|-------------|---------|-------|
| 50-63 | Duel icons (one per NPC slot 1-14) | 8x8 OBJ tile at VRAM tile #0x3F8, palette slot 14 |

### Rendering Pipeline

`OverworldRunEndFrame` gates the call behind the runtime config:

```c
if (gRuntimeConfig.enable_repeatable_duel_icon == TRUE) {
    LoadDuelIconGfx();
    SetDuelIconOam();
}
```

`LoadDuelIconGfx` copies the single-tile 4bpp data (32 bytes) to `0x06010000 + 0x3F8 * 32` and the 16-color palette (32 bytes) to OBJ palette slot 14.

`SetDuelIconOam` loops slots 1-14, checks `ObjectHasRepeatableDuel(i)`, and writes the OAM entry:

```
y = object.y * 2 - object.unk8 + gOverworld.unk24C - DUEL_ICON_Y_OFFSET
x = object.x * 2 + gOverworld.unk24E - DUEL_ICON_X_OFFSET
```

Hidden entries are pushed off-screen (`y=0xA0, x=0xF0`).

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Config field | `configs/runtime.h` | `u8 enable_repeatable_duel_icon` in `RuntimeConfig` struct |
| Config default | `configs/runtime.c` | `.enable_repeatable_duel_icon = TRUE` in `gRuntimeConfigRom` |
| Debug menu entry | `debug_menu_runtime_config.c` | `CONF("Repeat Duel", enable_repeatable_duel_icon)` in `sRuntimeConfigEntries` |
| Graphics build | `graphics.mk` | Converts `duel.png` to `duel.4bpp` + `duel.gbapal` via `gbagfx` |
| INCBIN | `overworld_hooks.c:157-158` | `sDuelIconTiles` (4bpp), `sDuelIconPalette` (gbapal) |
| GFX loader | `LoadDuelIconGfx` in `overworld_hooks.c:211` | DMA-copies tile + palette to OBJ VRAM |
| OAM writer | `SetDuelIconOam` in `overworld_hooks.c:217` | Positions/hides duel icon per NPC slot |
| Repeatable duel check | `ObjectHasRepeatableDuel` in `overworld_hooks.c:211` | Verifies scriptR starts with DUEL command, not CHECK_FLAG |
| Frame hook | `OverworldRunEndFrame` in `overworld_hooks.c:410` | Calls loader + OAM writer when config is TRUE |
| Position constants | `overworld_hooks.c:124-128` | `DUEL_ICON_OAM_START`, `DUEL_ICON_TILE_NUM`, `DUEL_ICON_PALETTE_NUM`, `DUEL_ICON_X_OFFSET`, `DUEL_ICON_Y_OFFSET` |
| Source art | `src_custom/assets/icons/duel.png` | 8x8 indexed PNG |

## TODO

- None currently.

## Limitations & Bugs

- The 8x8 icon uses OAM priority 0 (lowest index), rendering above thought bubbles and reaction bubbles. This cannot be configured.
- Only 14 NPC slots exist per map; if more than 14 NPCs are on a map, the last one has no icon slot.
- The icon uses a hard-coded OBJ VRAM tile index (#0x3F8) and palette slot (#14). Collisions with other custom OBJ assets would require updating these constants.
- Tile/palette data is re-copied to VRAM every frame (32 bytes and 32 bytes respectively) — negligible overhead, but could be optimized with a dirty flag if VRAM bandwidth becomes a concern.
