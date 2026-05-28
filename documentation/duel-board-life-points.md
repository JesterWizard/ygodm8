# Duel Board Life Points

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

During a duel, life points are normally only visible on the field stat screen (hold **B**). This feature adds an optional always-on overlay on the duel field so both players can read LP without opening that menu.

The feature is controlled by `gRuntimeConfig.show_duel_life_points_on_board` in `configs/runtime.c` (default **on**).

## Plan

When the toggle is enabled, the hook runs at the end of each duel graphics refresh and draws five-digit LP counters on **BG2** (the scrolling field layer).

| Display | Tile position | Source |
|--------|---------------|--------|
| Player LP | Bottom-left (`x=1`, `y=19`) | `gDuelLifePoints[DUEL_PLAYER]` |
| Opponent LP | Bottom-right (`x=25`, `y=19`) | `gDuelLifePoints[DUEL_OPPONENT]` |

Formatting matches other five-digit LP UI: leading zeros (for example `08000` for 8000 LP).

Rendering details:

| Piece | Choice | Notes |
|-------|--------|-------|
| Font | `CopyStringTilesToVRAMBuffer` flag `0x001` | Same small font path as the overworld coordinate overlay |
| Palette | BG palette 3 (`0x3000`) | Same slot used by the duel info bar (`sub_8040B4C`) |
| Char tiles | Player `0x380`–`0x384`, opponent `0x385`–`0x389` | Tile index must equal `charBufOffset / 32` |
| Tilemap | Field map at `0xD800` | Flushed to VRAM each frame after draw |

To change on-screen placement, edit `BOARD_LP_PLAYER_X/Y` and `BOARD_LP_OPPONENT_X/Y` in `src_custom/duel_board_lp_hooks.c`.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Runtime toggle | `show_duel_life_points_on_board` in `configs/runtime.h` and `configs/runtime.c` | Enables or disables the board LP overlay |
| Draw hook | `sub_80411D4__Replacement` in `src_custom/duel_board_lp_hooks.c` | Runs after `LoadVRAM` / `LoadPalettes`, then draws LP when enabled |
| LP formatting | `FormatLifePointsString` in `src_custom/duel_board_lp_hooks.c` | Builds a digit string from `gDuelLifePoints` via `ConvertU16ToDigitBuffer` |
| Field draw | `DrawLifePointsAt`, `DrawBoardLifePoints` in `src_custom/duel_board_lp_hooks.c` | Writes glyphs and tilemap entries, uploads char tiles, flushes map rows |
| Hook wiring | `src_custom/LynJump.event` (`ORG $411D4`) | Redirects `sub_80411D4` to the replacement |
| Vanilla refresh | `sub_80411D4` in `src/duel/duel_textbox.c` | Called from `UpdateDuelGfxExceptField` each duel frame |

## TODO

- Consider scrolling with the field if LP should stay pinned to a zone instead of a fixed map row.
- Document recommended tile/palette ranges if more on-field HUD text is added later.

## Limitations & Bugs

- Counters use a fixed map row (`y=19`). They scroll with the field background like other BG2 tiles; they are not screen-fixed like the bottom info bar.
- LP is redrawn every frame while enabled. This is simple but repeats char tile uploads.
- Values above `99999` are not supported; the buffer is five digits wide (`MAX_U16_DIGITS`).
- Char tile slots `0x380`–`0x389` must stay free of conflicting field or UI art. Change the defines in the hook file if a future field pack collides.
