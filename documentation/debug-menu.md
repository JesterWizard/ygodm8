# Debug Menu

---

## Index

- [Introduction](#introduction)
- [Access](#access)
- [Root Menu](#root-menu)
- [Music Viewer](#music-viewer)
- [Adding Tracks](#adding-tracks)
- [Portrait Viewer](#portrait-viewer)
- [Adding Portraits](#adding-portraits)
- [Sprite Viewer](#sprite-viewer)
- [Adding Sprites](#adding-sprites)
- [Text Layout](#text-layout)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

The debug menu is a developer-facing overlay for testing game systems outside normal story flow. It reuses the start-menu background and cursor art, but lives in custom code under `src_custom/debug_menu.c`.

Three viewers are implemented today:

- **Music Viewer** — scrollable OST list; preview a track with **A**.
- **Portrait Viewer** — scrollable dialogue-portrait list; the highlighted entry is drawn live on the right with neutral expression.
- **Sprite Viewer** — scrollable overworld sprites that have no dialogue portrait; the highlighted entry is drawn live on the right (down-facing idle frame).

## Access

| Requirement | Detail |
|-------------|--------|
| Runtime toggle | `gRuntimeConfig.enable_debug_menu` in `configs/runtime.c` (default **on**) |
| Input | On the overworld field, press **B** alone (no D-Pad held) |
| Hook | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` |

After the menu closes, overworld state is restored via `OverworldRestoreAfterDebugMenu()` and field music resumes with `PlayOverworldMusic()`.

## Root Menu

The root screen shows three menu rows and uses the same OAM cursor as the vanilla start menu.

| Row | Label | **A** behavior |
|-----|-------|----------------|
| 0 | Music Viewer | Opens the music list |
| 1 | Portrait Viewer | Opens the portrait list |
| 2 | Sprite Viewer | Opens the overworld sprite list |

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor between rows |
| **A** | Activate highlighted row |
| **B** | Exit debug menu |

Background music while the root menu is open is `MUSIC_DECK_ADJUSTMENT_MENU`.

## Music Viewer

The music viewer lists every entry in `src_custom/debug_menu_music_table.inc`. Three rows are visible at a time; longer lists scroll.

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor; list scrolls when cursor passes top or bottom visible row |
| **A** | Play the highlighted track (`PlayMusic` with that entry’s `musicId`) |
| **B** | Return to root menu |

### On-screen formatting

Each visible row is built by `DebugMenuFormatTrack()`:

- Prefix: `$0` (English language tag for the text engine)
- Column 0: `>` when that row’s track is currently playing, otherwise space
- Columns 1–15: track title, space-padded to `DEBUG_CHARS` (16)

Example while **World Map** is playing:

```text
>World Map
```

Titles longer than 15 characters are truncated to fit the row buffer.

### Track table

Tracks are defined with the `DEBUG_MENU_MUSIC_ENTRY` macro in `debug_menu_music_table.inc`:

```c
DEBUG_MENU_MUSIC_ENTRY(MUSIC_WORLD_MAP, "World Map")
```

`musicId` must be a valid `MUSIC_*` constant from `include/constants/music_ids.h`. Display names are free-form ASCII (up to 23 characters plus terminator in `title[24]`).

## Adding Tracks

1. Confirm the song ID exists in `include/constants/music_ids.h`.
2. Add one line to `src_custom/debug_menu_music_table.inc`:

   ```c
   DEBUG_MENU_MUSIC_ENTRY(MUSIC_YOUR_TRACK, "Your Label")
   ```

3. Rebuild the ROM (`make`).

No C changes are required unless you change row width, visible row count, or menu behavior.

## Portrait Viewer

The portrait viewer lists every entry in `src_custom/debug_menu_portrait_table.inc`. Three rows are visible at a time; longer lists scroll. The highlighted portrait is shown on the right as soon as the cursor moves to that row (no **A** press).

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor; list scrolls when cursor passes top or bottom visible row |
| **B** | Return to root menu |

### On-screen formatting

Each visible row uses the same `DebugMenuFormatListRow()` layout as the music viewer, but the `>` prefix marks the **cursor row**, not “currently playing”:

- Prefix: `$0`
- Column 0: `>` on the selected row, otherwise space
- Columns 1–15: portrait label, space-padded to `DEBUG_CHARS` (16)

Example with **Player** selected:

```text
>Player
```

Titles longer than 15 characters are truncated to fit the row buffer.

### Portrait preview

When the cursor changes, `DebugMenuLoadPortraitIfChanged()` loads tiles and palette through `LoadPortraitGfx(portraitId, EXPRESSION_NEUTRAL)` (same path as dialogue `PORTRAIT()`). OAM is reapplied every frame via `DebugMenuApplyPortraitOam()` because the start-menu VBlank path clears `gOamBuffer` each frame.

| Constant | Value | Role |
|----------|-------|------|
| `DEBUG_PORTRAIT_X_TILE` | 19 | OAM X in pixels (`× 8`) |
| `DEBUG_PORTRAIT_Y_TILE` | 6 | OAM Y in pixels (`× 8`) |
| `DEBUG_PORTRAIT_TILE_BYTES` | `0x1000` | OBJ tile stash at `gBgVram.cbb4 + 0x2000` |
| `DEBUG_PORTRAIT_PAL_BYTES` | `0x80` | OBJ palette stash at `gPaletteBuffer + 256 + 0xC0` |

The preview uses `PORTRAIT_POSITION_RIGHT`, OBJ palette slot 12, and a second OAM slot (index 1) so the list cursor (slot 0) and portrait do not fight.

On exit, `DebugMenuHidePortrait()` and `DebugMenuClearPortraitObjStash()` remove the preview and zero the portrait VRAM/palette scratch area.

### Portrait table

Portraits are defined with the `DEBUG_MENU_PORTRAIT_ENTRY` macro in `debug_menu_portrait_table.inc`:

```c
DEBUG_MENU_PORTRAIT_ENTRY(PORTRAIT_PLAYER, "Player")
```

`portraitId` must be a valid `PORTRAIT_*` constant from `enum Portrait` in `include/overworld.h`. Display names are free-form ASCII (up to 23 characters plus terminator in `title[24]`).

Custom portraits must be wired in `src_custom/portrait_hooks.c` before they will render here; see [custom-portraits.md](custom-portraits.md).

## Adding Portraits

1. Confirm the portrait id exists in `enum Portrait` in `include/overworld.h` and is loadable via `LoadPortraitGfx` / `portrait_hooks.c`.
2. Add one line to `src_custom/debug_menu_portrait_table.inc`:

   ```c
   DEBUG_MENU_PORTRAIT_ENTRY(PORTRAIT_YOUR_FACE, "Your Label")
   ```

3. Rebuild the ROM (`make`).

No C changes are required unless you change preview position, expression, row layout, or menu behavior.

## Sprite Viewer

The sprite viewer lists overworld sprites that do **not** have a dialogue portrait (no overlap with the portrait viewer). Entries live in `src_custom/debug_menu_sprite_table.inc`. Three rows are visible at a time; longer lists scroll. The highlighted sprite is shown on the right as soon as the cursor moves to that row (no **A** press).

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor; list scrolls when cursor passes top or bottom visible row |
| **B** | Return to root menu |

### On-screen formatting

Each visible row uses the same `DebugMenuFormatListRow()` layout as the other list viewers: `>` marks the cursor row, not playback state.

### Sprite preview

When the cursor changes, `DebugMenuLoadSpriteIfChanged()` loads tiles through `sub_804F054()` (same path as overworld object graphics) and copies the entity palette from `gOverworldEntityPalettes` via `g82AD20C`. OAM is reapplied every frame via `DebugMenuApplySpriteOam()` because the start-menu VBlank path clears `gOamBuffer` each frame.

| Constant | Value | Role |
|----------|-------|------|
| `DEBUG_SPRITE_X_TILE` | 16 | OAM X in pixels (`× 8`) |
| `DEBUG_SPRITE_Y_TILE` | 5 | OAM Y in pixels (`× 8`) |
| `DEBUG_SPRITE_TILE_OFFSET` | `0x3400` | OBJ tile stash in `gBgVram.cbb4` |
| `DEBUG_SPRITE_TILE_BYTES` | `0xE00` | Bytes reserved for one frame |
| `DEBUG_SPRITE_PAL_SLOT` | 13 | OBJ palette slot for preview |
| `DEBUG_SPRITE_PAL_OFFSET` | `DEBUG_SPRITE_PAL_SLOT * 16` | OBJ palette buffer offset in `u16` colors |
| `DEBUG_SPRITE_FRAME_DOWN_IDLE` | 0 | Down-facing idle frame index |
| `DEBUG_SPRITE_OAM_SLOT_CURSOR` | 0 | List cursor OAM slot |
| `DEBUG_SPRITE_OAM_SLOT` | 1 | 32×32 sprite preview OAM slot |

The preview uses one 32×32 OBJ. `sub_804F054()` lays out the frame in OBJ VRAM's 2D tile pattern, so a single square OBJ points at the preview stash. List redraws invalidate the cached sprite id so tiles reload after `DebugMenuLoadTilemaps()` refreshes charblock 4.

On exit, `DebugMenuHideSprite()` and `DebugMenuClearSpriteObjStash()` remove the preview and zero the sprite VRAM/palette scratch area.

### Sprite table

Sprites are defined with the `DEBUG_MENU_SPRITE_ENTRY` macro in `debug_menu_sprite_table.inc`:

```c
DEBUG_MENU_SPRITE_ENTRY(SPRITE_YUGI, "Yugi")
```

`spriteId` must be a valid `SPRITE_*` constant from `enum OverworldEntitySprite` in `include/overworld.h`. Only add sprites that have **no** dialogue portrait (characters already in `debug_menu_portrait_table.inc` belong in the portrait viewer instead). Display names are free-form ASCII (up to 23 characters plus terminator in `title[24]`).

## Adding Sprites

1. Confirm the sprite id exists in `enum OverworldEntitySprite` in `include/overworld.h` and has graphics in `gOverworldEntitySprites`.
2. Add one line to `src_custom/debug_menu_sprite_table.inc`:

   ```c
   DEBUG_MENU_SPRITE_ENTRY(SPRITE_YOUR_NPC, "Your Label")
   ```

3. Rebuild the ROM (`make`).

No C changes are required unless you change preview position, frame index, row layout, or menu behavior.

## Text Layout

Menu text is **not** drawn with `CopyStringTilesToVRAMBuffer` for the full string. That API lays out `0x901` glyphs in the vanilla start-menu pattern (about 10 characters before wrapping in VRAM). The debug menu instead calls `sub_8020968()` once per character into fixed tile slots.

| Constant | Value | Role |
|----------|-------|------|
| `DEBUG_CHARS` | 16 | Characters per menu row |
| `DEBUG_ROWS` | 3 | Visible list rows (music and portrait viewers) |
| `DEBUG_TEXT_TILE` | `0x81` | First char tile in BG charblock 3 (`sbb18`) |
| `DEBUG_TEXT_STRIDE` | `DEBUG_TEXT_BLOCKS * 4 * 32` | Bytes between row buffers in char VRAM |
| `DEBUG_LINE0_TILE` | Same as `DEBUG_TEXT_TILE` | First tile index referenced by the tilemap |

Tilemap entries are written to **BG2** screenbase `sbb1F` (visible layer), at map rows `0/1`, `2/3`, `4/5` (two map rows per menu line), starting at column 0. Each character uses one 2×2 tile block; two half-width glyphs share that block (standard `0x901` packing).

If you increase `DEBUG_CHARS`, `DEBUG_TEXT_STRIDE` must stay derived from `DEBUG_TEXT_BLOCKS` so row buffers do not overlap (otherwise trailing characters from one line bleed into the next).

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Entry point | `DebugMenuMain` in `src_custom/debug_menu.c` | Loads graphics, runs root loop, tears down on exit |
| Overworld hook | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` | Opens menu on **B** when `enable_debug_menu` is set |
| Runtime toggle | `enable_debug_menu` in `configs/runtime.h`, `configs/runtime.c` | Gates overworld access |
| Root menu | `DebugMenuRoot` in `src_custom/debug_menu.c` | Three-item list; opens music, portrait, or sprite viewer |
| Music viewer | `DebugMusicViewer` in `src_custom/debug_menu.c` | Scrollable list, preview on **A** |
| Portrait viewer | `DebugPortraitViewer` in `src_custom/debug_menu.c` | Scrollable list, live preview on cursor |
| Sprite viewer | `DebugSpriteViewer` in `src_custom/debug_menu.c` | Scrollable list, live preview on cursor |
| Track table | `src_custom/debug_menu_music_table.inc` | `DEBUG_MENU_MUSIC_ENTRY` rows included into `sTracks[]` |
| Portrait table | `src_custom/debug_menu_portrait_table.inc` | `DEBUG_MENU_PORTRAIT_ENTRY` rows included into `sPortraits[]` |
| Sprite table | `src_custom/debug_menu_sprite_table.inc` | `DEBUG_MENU_SPRITE_ENTRY` rows included into `sSprites[]` |
| Track struct | `struct DebugMenuMusicEntry` in `src_custom/debug_menu.c` | `musicId` + `title[24]` |
| Portrait struct | `struct DebugMenuPortraitEntry` in `src_custom/debug_menu.c` | `portraitId` + `title[24]` |
| Sprite struct | `struct DebugMenuSpriteEntry` in `src_custom/debug_menu.c` | `spriteId` + `title[24]` |
| Sprite load | `DebugMenuLoadSpriteIfChanged`, `DebugMenuApplySpriteOam` in `src_custom/debug_menu.c` | `sub_804F054` + OAM each frame |
| Sprite cleanup | `DebugMenuClearSpriteObjStash`, `DebugMenuHideSprite` in `src_custom/debug_menu.c` | Clears OBJ tile/palette stash on exit |
| Sprite IDs | `enum OverworldEntitySprite` in `include/overworld.h` | Source of truth for `SPRITE_*` constants |
| Portrait load | `DebugMenuLoadPortraitIfChanged`, `DebugMenuApplyPortraitOam` in `src_custom/debug_menu.c` | `LoadPortraitGfx` + OAM each frame |
| Portrait cleanup | `DebugMenuClearPortraitObjStash`, `DebugMenuHidePortrait` in `src_custom/debug_menu.c` | Clears OBJ tile/palette stash on exit |
| Portrait IDs | `enum Portrait` in `include/overworld.h` | Source of truth for `PORTRAIT_*` constants |
| Portrait loader | `LoadPortraitGfx` in `src_custom/portrait_hooks.c` | Shared with dialogue `PORTRAIT()` |
| Text draw | `DebugMenuCopyLine`, `DebugMenuReadGlyphArg` in `src_custom/debug_menu.c` | Per-glyph layout into charblock 3 |
| Tilemap setup | `DebugMenuSetupTextRows` in `src_custom/debug_menu.c` | Maps 2×2 blocks on `sbb1F` for each row |
| Graphics load | `DebugMenuLoadGraphics`, `DebugMenuLoadTilemaps` in `src_custom/debug_menu.c` | Start-menu tiles + custom text rows |
| Public API | `include/debug_menu.h` | Declares `DebugMenuMain` |
| Music IDs | `include/constants/music_ids.h` | Source of truth for `MUSIC_*` constants |

## TODO

- Add more root-menu entries (flags, maps, duel shortcuts) without hard-coding `DEBUG_ROOT_ITEMS` in multiple places.
- Optional search or category grouping when the track or portrait lists grow further.
- Document or automate sync between `music_ids.h` comments and `debug_menu_music_table.inc`.
- Portrait viewer: expression toggle or cycle (today locked to `EXPRESSION_NEUTRAL`).
- Sprite viewer: direction or walk-frame toggle (today locked to down-facing idle frame 0).

## Limitations & Bugs

- Track and portrait titles truncate to 15 visible characters after the row prefix marker.
- The music viewer does not stop the previous track explicitly before starting a new one; behavior depends on vanilla `PlayMusic` handling.
- Exiting the music viewer restores root menu BGM (`MUSIC_DECK_ADJUSTMENT_MENU`), not the track that was previewed.
- The portrait viewer always uses `EXPRESSION_NEUTRAL`; other expressions are not selectable.
- Custom portraits only appear if `portrait_hooks.c` can load them; table entries alone are not enough.
- Portrait preview shares OBJ tile/palette scratch with dialogue portraits (`cbb4 + 0x2000`, palette `0xC0..0xFF`); leaving the menu clears this stash.
- Sprite preview uses a separate OBJ stash (`cbb4 + 0x3400`, palette slot 13); leaving the menu clears this stash.
- Menu text shares BG2 charblock 3 with start-menu-derived assets; large future changes to tile indices need VRAM/layout checks in No$gba or similar.
- Debug menu is only reachable from the overworld field input hook today, not from main menu or duel.
