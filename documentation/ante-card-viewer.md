# Ante Card Viewer

---

## Index

- [Introduction](#introduction)
- [Access](#access)
- [Controls](#controls)
- [Card List Sources](#card-list-sources)
- [On-Screen Layout](#on-screen-layout)
- [Text Colors](#text-colors)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

On the overworld, the player can inspect which cards a duelist might take as ante rewards before starting a duel. Press **SELECT** while facing an NPC that has ante data; a scrollable list appears on the left and a mini card preview on the right.

The UI reuses the debug menu’s start-menu background, text layout, and cursor (`DebugMenuLoadGraphics`, `DebugMenuCopyLine`, and related helpers in `src_custom/debug/`). It is **not** opened from the debug menu root (**B**); it is a separate player-facing feature gated by its own runtime toggle.

Design goals:

- Show normal and low ante pools in one list without opening a duel.
- Distinguish pool tier at a glance (gold vs white row text).
- Allow full card details on **A**, same as other card inspection screens.

## Access

| Requirement | Detail |
|-------------|--------|
| Runtime toggle | `gRuntimeConfig.enable_ante_card_viewer` in `configs/runtime.c` (default **on**) |
| Input | On the overworld field, press **SELECT** while no D-Pad direction is held for movement |
| Hook | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` |
| Target | An overworld object in talk range in front of the player (same directional boxes as talk/duel) |
| Data | At least one ante card must resolve for that NPC; otherwise **SELECT** falls through to the status menu |

When the viewer opens successfully, overworld state is restored the same way as after the debug menu (`OverworldRestoreAfterDebugMenu()`, field music via `PlayOverworldMusic()`).

## Controls

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor; list scrolls when cursor passes the top or bottom visible row |
| **A** | Open full card detail view for the highlighted card; **B** returns to the list |
| **B** | Close the ante card viewer and return to the field |

Three card names are visible at a time (`DEBUG_ROWS`). Longer lists scroll.

## Card List Sources

The viewer builds a deduplicated list (max 128 cards) in this order:

1. **Normal ante** drops first (gold text).
2. **Low ante** drops second (white text).

If the same card appears in both pools, only the first entry is kept (normal ante wins).

### Resolution order per NPC

| Priority | Source | How it is found |
|----------|--------|-----------------|
| 1 | Custom card-shop duel rewards | `CustomDecks_FindCardShopDuelRewardEntry(spriteId, mapId)` in `src_custom/custom_decks/custom_decks.c` |
| 2 | Vanilla duelist ante tables | Script scan for duel command `@0` (`0x40`, `'0'`, duelist id byte) via `FindDuelistIdInScript`, then `GetDuelistAnteDrops(duelistId, normalAnte)` in `src_custom/code_801EF30_hooks.c` |

Custom entries use `CustomDuelRewardEntry` (`normalDrops` / `lowDrops` arrays). Vanilla entries use the duelist reward manifest path documented in [duelist-reward-manifest.md](duelist-reward-manifest.md).

### Script scan behavior

`FindDuelistIdInScript` walks up to `ANTE_SCRIPT_SCAN_LIMIT` (256) bytes from the script start. It does **not** treat `0x00` as end-of-script, because duel scripts often contain zero-valued argument bytes before the `@0` duel opcode.

## On-Screen Layout

| Region | Implementation |
|--------|----------------|
| List (left) | Three rows × 16 characters via `DebugMenuCopyLine` / `FormatAnteCardRow` |
| Cursor | OAM slot 0; palette restored each frame (`ApplyAnteCursorPalette`, slot 15) |
| Mini card (right) | `sub_80573D0` into OBJ VRAM tile `0x180`, OAM slot 1 at (180, 64) |
| Row labels | Card name from `gCardInfo.name` after `SetCardInfo(cardId)`; `$0` English prefix |

Card names are not prefixed with `>`; selection is shown only by the OAM cursor.

### Key constants

| Constant | Value | Role |
|----------|-------|------|
| `ANTE_CARD_MAX_CARDS` | 128 | Max entries in the built list |
| `ANTE_MINI_CARD_TILE_NUM` | `0x180` | OBJ tile index for mini card art |
| `ANTE_MINI_CARD_X` / `Y` | 180 / 64 | Mini card OAM position |
| `ANTE_MINI_CARD_OAM_SLOT` | 1 | OAM slot (cursor uses slot 0) |
| `ANTE_CURSOR_PAL_SLOT` | 15 | OBJ palette slot for list cursor after mini-card palette load |

After **A** opens card details, `DebugMenuLoadGraphics()` and `ApplyAnteTextPalettes()` run again so list graphics and gold/white palettes are restored.

## Text Colors

Row color encodes ante pool tier using BG palette banks, not different font packing modes (`0x900` vs `0x901`).

| Pool | Tilemap palette bank | Text color |
|------|----------------------|------------|
| Normal ante | 14 (`0xE000` in tilemap) | Gold — palette index 1 set to `0x031F` (`ANTE_GOLD_TEXT_COLOR`) |
| Low ante | 15 (`0xF000`) | White — vanilla text palette `gUnk_8079424` at `gPaletteBuffer[0xF0]` |

`ApplyAnteTextPalettes()` copies `gUnk_8079424` to bank 14 (`gPaletteBuffer[0xE0]`) and overrides color index 1 for gold. `DebugMenuSetLinePalette()` in `src_custom/debug/debug_menu.c` updates the high nibble of each tilemap entry on `sbb1F` per row after glyphs are drawn.

To change gold tone, edit `ANTE_GOLD_TEXT_COLOR` in `src_custom/debug/ante_card_viewer.c` (for example `0x039F` for a lighter yellow-gold).

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Public API | `AnteCardViewer_TryOpen` in `include/ante_card_viewer.h`, `src_custom/debug/ante_card_viewer.c` | Entry point; returns TRUE if the viewer opened |
| Main loop | `AnteCardViewerMain` in `ante_card_viewer.c` | Graphics setup, input, mini-card OAM each frame |
| List build (vanilla) | `BuildDuelistAnteCardList`, `FindDuelistIdInScript` in `ante_card_viewer.c` | Script scan + `GetDuelistAnteDrops` |
| List build (custom) | `BuildCustomAnteCardList` in `ante_card_viewer.c` | `CustomDuelRewardEntry` normal/low arrays |
| Ante drop lookup | `GetDuelistAnteDrops` in `src_custom/code_801EF30_hooks.c` | Manifest-backed normal/low `CardDrop` tables |
| Custom reward lookup | `CustomDecks_FindCardShopDuelRewardEntry` in `src_custom/custom_decks/custom_decks.c` | Per-sprite, per-map reward override |
| Overworld hook | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` | **SELECT** tries viewer before status menu |
| Runtime toggle | `enable_ante_card_viewer` in `configs/runtime.h`, `configs/runtime.c` | Gates overworld **SELECT** behavior |
| Shared UI | `DebugMenuLoadGraphics`, `DebugMenuCopyLine`, `DebugMenuSetLinePalette` in `src_custom/debug/debug_menu.c` | Background, glyphs, per-row palette |
| Shared constants | `debug_menu_internal.h` | `DEBUG_ROWS`, `DEBUG_CHARS`, text VRAM layout |
| Mini card draw | `sub_80573D0__Replacement` in `src_custom/mini_card_hooks.c` | Mini card tiles into OBJ VRAM |
| Portrait cleanup | `DisplayPortrait(PORTRAIT_NONE)` in `src_custom/portrait_hooks.c` | Avoids ghost portraits after submenus (shared with debug menu) |
| Reward authoring | [duelist-reward-manifest.md](duelist-reward-manifest.md) | Vanilla duelist normal/low ante data |

## TODO

- Show pool labels or icons (for example “Normal” / “Low”) in addition to row color.
- Handle NPCs with duel scripts that store the duelist id outside the `@0` opcode pattern.
- Optional sort mode (name, id, pool) without changing manifest order.
- Surface “no ante data” feedback instead of silently opening the status menu when **SELECT** finds zero cards.

## Limitations & Bugs

- **SELECT** with zero ante cards does not open the viewer; vanilla status menu opens instead.
- Card names truncate to 16 characters (`DEBUG_CHARS`) after the `$0` prefix.
- Duplicate cards across normal and low pools appear once, colored as normal ante.
- NPCs without a resolvable duelist id or custom reward entry cannot be inspected.
- Script scan is capped at 256 bytes; unusual script layouts may miss `@0` if it lies beyond that window.
- Mini card palette load can overwrite OBJ palette slots; cursor palette is forced back to slot 15 each frame.
- Viewer is overworld-only; not available from duel, trunk, or shop screens.
- Requires facing a valid talk-range object; empty tiles or wrong facing do nothing (status menu on **SELECT** only when toggle is on but open fails).
