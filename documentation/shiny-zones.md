# Shiny Zones

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Shiny zones are one-shot overworld card pickups.

The player-facing goal is to let maps hide cards in specific places, similar to RPG item spots. When the player presses A on a configured zone, the game shows `Obtained [CARD_NAME]`, opens the same card detail popup used by ante rewards, adds the card to the trunk, then marks the pickup as collected.

The feature is controlled by `gRuntimeConfig.enable_shiny_zones`.

## Plan

The feature flow is:

| Stage | Location | Result |
|--------|----------|--------|
| Manifest data | `tools/shiny_zone_manifest.json` | Stores map, coordinate/object, card, and collection flag data |
| Generation | `tools/generate_shiny_zones.py` | Resolves constants and emits `src_custom/generated/shiny_zones_generated.inc` |
| Runtime lookup | `ShinyZones_TryInteract` | Checks the tile/object in front of the player before vanilla talk scripts run |
| Reward display | `ShinyZones_TryInteract` | Shows obtained text, clears the textbox, opens card detail, adds card to trunk |
| Persistence | `ShinyZones_SaveFlagsToFlash*` and `ShinyZones_LoadFlagsFromFlash*` | Mirrors the 16-byte flag bitfield between EWRAM and SRAM |

Behavior summary:

| Field | Purpose | Notes |
|--------|---------|-------|
| `flag` | Collection bit index | Must be unique per shiny zone, valid range `0-127` |
| `map` | Overworld location | Uses `LOCATION_*` names from `include/overworld.h` |
| `state` | Optional map state filter | Defaults to `SHINY_ZONE_ANY_STATE`; use only when the pickup belongs to one story/layout state |
| `tile_x`, `tile_y` | No$GBA BG tilemap coordinate | Runtime accepts the center tile and surrounding 3x3 tile area |
| `object_id` | Object-based interaction | Use instead of coordinates when the pickup should bind to a specific map object |
| `card` | Reward card | Uses constants from `include/constants/card_ids.h` |

Example:

```json
{
  "flag": 0,
  "map": "LOCATION_PLAYER_HOUSE_INSIDE",
  "tile_x": 22,
  "tile_y": 13,
  "card": "BLUE_EYES_WHITE_DRAGON"
}
```

This matches No$GBA tile `0x16,0x0D`, whose screen-pixel origin is `176,104`.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Runtime toggle | `enable_shiny_zones` in `configs/runtime.h` and `configs/runtime.c` | Enables or disables shiny-zone interactions |
| Manifest | `tools/shiny_zone_manifest.json` | Authoritative editable pickup list |
| Generator | `tools/generate_shiny_zones.py` | Validates constants, tile coordinates, flags, and emits generated C data |
| Generated table | `src_custom/generated/shiny_zones_generated.inc` | Build output consumed by the runtime hook |
| Runtime implementation | `src_custom/shiny_zones.c` | Finds matching zones, shows reward UI, adds cards, and flips flags |
| Talk hook | `TryTalking__Replacement` in `src_custom/code_8051958_hooks.c` | Gives shiny zones first chance to handle A-button interactions |
| EWRAM flags | `gShinyZoneFlags` in `asm/ram_map.s` | 16-byte live collection bitfield |
| SRAM mirrors | `gShinyZoneFlagsFlashPrimary` and `gShinyZoneFlagsFlashBackup` in `asm/ram_map.s` | Persistent copies saved with primary and backup save slots |
| Save/load hooks | `src_custom/code_800AC64_hooks.c` | Copies flags between EWRAM and SRAM when saving/loading |
| Reset hook | `InitFlags__Replacement` in `src_custom/flag_hooks.c` | Clears shiny-zone flags for new flag state |

## TODO

- Add a visual sparkle or object marker for configured zones.
- Add a manifest validation report that warns when two active zones overlap on the same map/state.
- Consider exposing a simple debug print for the current player-facing tile coordinate.

## Limitations & Bugs

- Coordinate entries use No$GBA BG tilemap coordinates, not raw object coordinates.
- Tile entries match a 3x3 area centered on `tile_x/tile_y`; overlapping zones resolve in manifest order.
- The current collection bitfield supports 128 shiny zones.
- The feature persists only when the player saves after collecting a card.
