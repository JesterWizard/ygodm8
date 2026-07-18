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
2. one-shot gfx load: tile and palette are DMA-copied to OBJ VRAM when the feature is first enabled (and again after overlay paths that reload OBJ VRAM)
3. per-frame OAM placement: each NPC slot uses a cached duel-availability result, and an OAM entry is positioned above the head

### Repeatable Duel Check

The icon uses a cached `ObjectHasAvailableDuel(objId)` rather than re-scanning scripts every frame:

- `scriptR` must be non-NULL, different from `scriptA`, and resolve to a valid script
- Story duelists whose script starts with **CHECK_FLAG** (`0x23 '7' flagByte`) show the icon while the flag is clear
- Otherwise the resolved script bytecode is scanned once for **DUEL** (`0x40 '0'`); the result is cached keyed by the `scriptR` pointer

`EventSystem_ResolveScript` walks ~1500 replacement entries. Doing that (twice) for every NPC every frame was the train-station hitch; the cache only resolves+scans when an NPC's `scriptR` pointer changes (map load / state change).

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

`LoadDuelIconGfx` copies the single-tile 4bpp data (32 bytes) to `0x06010000 + 0x3FF * 32` and the 16-color palette (32 bytes) to OBJ palette slot 11 each frame (cheap; survives overlay VRAM/palette reloads). Overlay VBlank paths that call `LoadObjVRAM` also call `LoadDuelIconGfx`.

`SetDuelIconOam` loops slots 1-14, uses the cached availability result, and writes the OAM entry:

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
| GFX loader | `LoadDuelIconGfx` in `overworld_hooks.c` | DMA-copies tile + palette to OBJ VRAM each frame |
| OAM writer | `SetDuelIconOam` in `overworld_hooks.c` | Positions/hides duel icon per NPC slot |
| Availability cache | `gDuelIconCache` (EWRAM) / `RebuildDuelIconCacheEntry` | Resolve+scan once per `scriptR` change; flag-gated slots re-check `CheckFlag` only |
| Frame hook | `OverworldRunEndFrame` in `overworld_hooks.c` | Calls loader + OAM writer when config is TRUE |
| Position constants | `overworld_hooks.c:124-128` | `DUEL_ICON_OAM_START`, `DUEL_ICON_TILE_NUM`, `DUEL_ICON_PALETTE_NUM`, `DUEL_ICON_X_OFFSET`, `DUEL_ICON_Y_OFFSET` |
| Source art | `src_custom/assets/icons/duel.png` | 8x8 indexed PNG |

## TODO

- None currently.

## Limitations & Bugs

- The 8x8 icon uses OAM priority 0 (lowest index), rendering above thought bubbles and reaction bubbles. This cannot be configured.
- Only 14 NPC slots exist per map; if more than 14 NPCs are on a map, the last one has no icon slot.
- The icon uses a hard-coded OBJ VRAM tile index (#0x3FF) and palette slot (#11). Collisions with other custom OBJ assets would require updating these constants.
- Availability is cached by `scriptR` pointer. If script bytecode were ever rewritten in place without changing the pointer, the cache would stay stale until the next pointer change.
