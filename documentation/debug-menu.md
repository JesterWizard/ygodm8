# Debug Menu

---

## Index

- [Introduction](#introduction)
- [Related: Ante Card Viewer](#related-ante-card-viewer)
- [Related: Duelist Deck Viewer](#related-duelist-deck-viewer)
- [Source Layout](#source-layout)
- [Access](#access)
- [Root Menu](#root-menu)
- [Music Viewer](#music-viewer)
- [Adding Tracks](#adding-tracks)
- [Portrait Viewer](#portrait-viewer)
- [Adding Portraits](#adding-portraits)
- [Sprite Viewer](#sprite-viewer)
- [Adding Sprites](#adding-sprites)
- [Reaction Viewer](#reaction-viewer)
- [AI Mode](#ai-mode)
- [Text Layout](#text-layout)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

The debug menu is a developer-facing overlay for testing game systems outside normal story flow. It reuses the start-menu background and cursor art, but lives in custom code under `src_custom/debug/`.

Viewers and tools implemented today:

- **Music Viewer** — scrollable OST list; preview a track with **A**.
- **Portrait Viewer** — scrollable dialogue-portrait list; the highlighted entry is drawn live on the right with neutral expression.
- **Sprite Viewer** — scrollable overworld sprites that have no dialogue portrait; the highlighted entry is drawn live on the right (down-facing idle frame).
- **Reaction Viewer** — scrollable overworld reactions; the highlighted entry animates on **SPRITE_PLAYER** with vanilla bubble sequences. See [reaction-viewer.md](reaction-viewer.md).
- **Graphic Viewer** — scrollable overworld animation graphics (Blue-Eyes, Slifer, etc.); play the full effect with **A**.
- **Voice Viewer** — preview duel voice clips (vanilla and custom).
- **Match Setter** — spawn test duelists on the overworld field.
- **AI Mode** — toggle **AI Both Sides** for fully automated duels. See [ai-both-sides-duel-mode.md](ai-both-sides-duel-mode.md).

## Related: Ante Card Viewer

The **ante card viewer** (`src_custom/debug/ante_card_viewer.c`) shares this folder’s text and graphics helpers but is **not** part of the debug menu root. On the overworld, **SELECT** while facing a duelist opens a scrollable ante reward list with a mini card preview. It uses `DebugMenuCopyLine`, `DebugMenuSetLinePalette`, and `DebugMenuLoadGraphics`, but is gated by `enable_ante_card_viewer` instead of `enable_debug_menu`.

Full behavior, controls, data sources, and colored row text are documented in [ante-card-viewer.md](ante-card-viewer.md).

## Related: Duelist Deck Viewer

The **duelist deck viewer** (`src_custom/duelist_deck_viewer.c`) is a separate player-facing feature gated by `enable_duelist_deck_viewer`. On the overworld, **START** while facing a duelist opens a read-only copy of the status-menu deck list (sort and card details only; no trunk edits). It reuses deck menu code in `src_custom/deck_menu_hooks.c`, not the debug menu root.

Full behavior, controls, and deck resolution are documented in [duelist-deck-viewer.md](duelist-deck-viewer.md).

## Source Layout

All debug-menu sources and data tables live in `src_custom/debug/`:

| File | Role |
|------|------|
| `debug_menu.c` | Entry point (`DebugMenuMain`), root menu, shared graphics/text/input |
| `debug_menu_internal.h` | Shared constants, structs, and cross-file declarations |
| `debug_menu_music.c` | Music viewer loop and `debug_menu_music_table.inc` |
| `debug_menu_portrait.c` | Portrait viewer, preview load/OAM, `debug_menu_portrait_table.inc` |
| `debug_menu_sprite.c` | Sprite viewer, preview load/OAM, `debug_menu_sprite_table.inc` |
| `debug_menu_reaction.c` | Reaction viewer, bubble animation/OAM, `debug_menu_reaction_table.inc` |
| `debug_menu_graphic.c` | Graphic viewer, plays `sub_80512E0` effects, `debug_menu_graphic_table.inc` |
| `debug_menu_*_table.inc` | Data-only entry lists (no C logic) |
| `overworld_debug_overlay_hooks.c` | Field coordinate overlay (separate from the menu UI) |
| `ante_card_viewer.c` | Overworld ante reward list (opened with **SELECT**, not from root menu) |
| `debug_menu_ai_mode.c` | AI Mode submenu (Off / AI Both Sides) |

Public API remains in `include/debug_menu.h` (`DebugMenuMain`, `DebugMenuClearPortraitObjStash`).

To add a new root-menu feature:

1. Add a `DEBUG_VIEW_*` id and root row label in `debug_menu.c`.
2. Implement `DebugYourFeatureViewer()` in a new `debug_menu_yourfeature.c` (or extend an existing feature file).
3. Declare draw/viewer helpers in `debug_menu_internal.h` and wire `DebugMenuRedraw()` / `DebugMenuRoot()`.

## Access

| Requirement | Detail |
|-------------|--------|
| Runtime toggle | `gRuntimeConfig.enable_debug_menu` in `configs/runtime.c` (default **on**) |
| Input | On the overworld field, press **B** alone (no D-Pad held) |
| Hook | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` |

After the menu closes, overworld state is restored via `OverworldRestoreAfterDebugMenu()` and field music resumes with `PlayOverworldMusic()`.

## Root Menu

The root screen shows five visible rows at a time (`DEBUG_ROWS`) and uses the same OAM cursor as the vanilla start menu. Eight items scroll when the cursor moves past the bottom row (`DEBUG_ROOT_ITEMS`).

| Row | Label | **A** behavior |
|-----|-------|----------------|
| 0 | Music Viewer | Opens the music list |
| 1 | Portrait Viewer | Opens the portrait list |
| 2 | Sprite Viewer | Opens the overworld sprite list |
| 3 | Reaction Viewer | Opens the reaction bubble list (see [reaction-viewer.md](reaction-viewer.md)) |
| 4 | Graphic Viewer | Opens the overworld animation graphic list |
| 5 | Voice Viewer | Opens the voice clip list |
| 6 | Match Setter | Opens overworld duelist spawn presets |
| 7 | AI Mode | Opens Off / AI Both Sides toggle (see [ai-both-sides-duel-mode.md](ai-both-sides-duel-mode.md)) |

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor between rows |
| **A** | Activate highlighted row |
| **B** | Exit debug menu |

Background music while the root menu is open is `MUSIC_DECK_ADJUSTMENT_MENU`.

## AI Mode

Opens a two-row submenu: **Off** and **AI Both Sides**. Choosing **A** on a row applies that mode and writes it to save flash (primary and backup) immediately.

Full duel behavior, persistence, auto-advance text, and bug-fix history are documented in [ai-both-sides-duel-mode.md](ai-both-sides-duel-mode.md).

## Music Viewer

The music viewer lists every entry in `src_custom/debug/debug_menu_music_table.inc`. Three rows are visible at a time; longer lists scroll.

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor; list scrolls when cursor passes top or bottom visible row |
| **A** | Play the highlighted track (`PlayMusic` with that entry’s `musicId`) |
| **B** | Return to root menu |

### On-screen formatting

Each visible row is built by `DebugMenuFormatTrack()` in `debug_menu_music.c`:

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
2. Add one line to `src_custom/debug/debug_menu_music_table.inc`:

   ```c
   DEBUG_MENU_MUSIC_ENTRY(MUSIC_YOUR_TRACK, "Your Label")
   ```

3. Rebuild the ROM (`make`).

No C changes are required unless you change row width, visible row count, or menu behavior.

## Portrait Viewer

The portrait viewer lists every entry in `src_custom/debug/debug_menu_portrait_table.inc`. Three rows are visible at a time; longer lists scroll. The highlighted portrait is shown on the right as soon as the cursor moves to that row (no **A** press).

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor; list scrolls when cursor passes top or bottom visible row |
| **B** | Return to root menu |

### On-screen formatting

Each visible row is built by `DebugMenuFormatTitleRow()` in `debug_menu_portrait.c` (no `>` cursor prefix; the OAM cursor shows selection):

- Prefix: `$0`
- Columns 0–15: portrait label, space-padded to `DEBUG_CHARS` (16)

Example:

```text
Player
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
2. Add one line to `src_custom/debug/debug_menu_portrait_table.inc`:

   ```c
   DEBUG_MENU_PORTRAIT_ENTRY(PORTRAIT_YOUR_FACE, "Your Label")
   ```

3. Rebuild the ROM (`make`).

No C changes are required unless you change preview position, expression, row layout, or menu behavior.

## Sprite Viewer

The sprite viewer lists overworld sprites that do **not** have a dialogue portrait (no overlap with the portrait viewer). Entries live in `src_custom/debug/debug_menu_sprite_table.inc`. Three rows are visible at a time; longer lists scroll. The highlighted sprite is shown on the right as soon as the cursor moves to that row (no **A** press).

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor; list scrolls when cursor passes top or bottom visible row |
| **B** | Return to root menu |

### On-screen formatting

Each visible row uses `DebugMenuFormatTitleRow()` in `debug_menu_sprite.c` (no `>` prefix; the OAM cursor shows selection). Labels start one character column left of the music viewer’s title text.

### Sprite preview

When the cursor changes, `DebugMenuLoadSpriteIfChanged()` loads tiles through `sub_804F054()` (same path as overworld object graphics) and copies the entity palette from `gOverworldEntityPalettes` via `g82AD20C`. OAM is reapplied every frame via `DebugMenuApplySpriteOam()` because the start-menu VBlank path clears `gOamBuffer` each frame.

| Constant | Value | Role |
|----------|-------|------|
| `DEBUG_SPRITE_X_TILE` | 22 | OAM X in pixels (`× 8`) |
| `DEBUG_SPRITE_Y_TILE` | 8 | OAM Y in pixels (`× 8`) |
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
2. Add one line to `src_custom/debug/debug_menu_sprite_table.inc`:

   ```c
   DEBUG_MENU_SPRITE_ENTRY(SPRITE_YOUR_NPC, "Your Label")
   ```

3. Rebuild the ROM (`make`).

No C changes are required unless you change preview position, frame index, row layout, or menu behavior.

## Reaction Viewer

The reaction viewer lists every `REACTION_*` entry in `debug_menu_reaction_table.inc`. Three rows are visible at a time; seven reactions scroll. The highlighted reaction plays automatically on **SPRITE_PLAYER** (down idle) with vanilla `g8105114` timing — no **A** press.

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor; list scrolls; animation restarts for the new reaction |
| **B** | Return to root menu |

Palette handling, animation tables, OBJ slot layout, and how to add rows are documented in [reaction-viewer.md](reaction-viewer.md).

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
| Entry point | `DebugMenuMain` in `src_custom/debug/debug_menu.c` | Loads graphics, runs root loop, tears down on exit |
| Shared internals | `src_custom/debug/debug_menu_internal.h` | Constants, structs, cross-file API |
| Overworld hook | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` | Opens menu on **B** when `enable_debug_menu` is set |
| Runtime toggle | `enable_debug_menu` in `configs/runtime.h`, `configs/runtime.c` | Gates overworld access |
| Root menu | `DebugMenuRoot` in `src_custom/debug/debug_menu.c` | Eight-item scrollable list; opens viewers, match setter, or AI mode |
| AI mode | `DebugAiModeViewer` in `src_custom/debug/debug_menu_ai_mode.c` | Off / AI Both Sides; see [ai-both-sides-duel-mode.md](ai-both-sides-duel-mode.md) |
| Music viewer | `DebugMusicViewer` in `src_custom/debug/debug_menu_music.c` | Scrollable list, preview on **A** |
| Portrait viewer | `DebugPortraitViewer` in `src_custom/debug/debug_menu_portrait.c` | Scrollable list, live preview on cursor |
| Sprite viewer | `DebugSpriteViewer` in `src_custom/debug/debug_menu_sprite.c` | Scrollable list, live preview on cursor |
| Reaction viewer | `DebugReactionViewer` in `src_custom/debug/debug_menu_reaction.c` | Scrollable list, animated bubble on player |
| Graphic viewer | `DebugGraphicViewer` in `src_custom/debug/debug_menu_graphic.c` | Scrollable list, full effect on **A** via `sub_80512E0` |
| Graphic table | `src_custom/debug/debug_menu_graphic_table.inc` | `DEBUG_MENU_GRAPHIC_ENTRY` rows (`enum OverworldGraphics`) |
| Reaction table | `src_custom/debug/debug_menu_reaction_table.inc` | `DEBUG_MENU_REACTION_ENTRY` rows |
| Reaction OBJ palettes | `DebugMenuLoadReactionObjPalettes` in `debug_menu.c` | Entity OBJ 0–11 + cursor palette slot 15 |
| Reaction struct | `struct DebugMenuReactionEntry` in `debug_menu_internal.h` | `reactionId` + `title[24]` |
| Reaction IDs | `enum OverworldReactions` in `include/overworld.h` | Source of truth for `REACTION_*` |
| Track table | `src_custom/debug/debug_menu_music_table.inc` | `DEBUG_MENU_MUSIC_ENTRY` rows included into `sTracks[]` |
| Portrait table | `src_custom/debug/debug_menu_portrait_table.inc` | `DEBUG_MENU_PORTRAIT_ENTRY` rows included into `sPortraits[]` |
| Sprite table | `src_custom/debug/debug_menu_sprite_table.inc` | `DEBUG_MENU_SPRITE_ENTRY` rows included into `sSprites[]` |
| Track struct | `struct DebugMenuMusicEntry` in `debug_menu_internal.h` | `musicId` + `title[24]` |
| Portrait struct | `struct DebugMenuPortraitEntry` in `debug_menu_internal.h` | `portraitId` + `title[24]` |
| Sprite struct | `struct DebugMenuSpriteEntry` in `debug_menu_internal.h` | `spriteId` + `title[24]` |
| Sprite load | `DebugMenuLoadSpriteIfChanged`, `DebugMenuApplySpriteOam` in `debug_menu_sprite.c` | `sub_804F054` + OAM each frame |
| Sprite cleanup | `DebugMenuClearSpriteObjStash` in `debug_menu_sprite.c` | Clears OBJ tile/palette stash on exit |
| Sprite IDs | `enum OverworldEntitySprite` in `include/overworld.h` | Source of truth for `SPRITE_*` constants |
| Portrait load | `DebugMenuLoadPortraitIfChanged`, `DebugMenuApplyPortraitOam` in `debug_menu_portrait.c` | `LoadPortraitGfx` + OAM each frame |
| Portrait cleanup | `DebugMenuClearPortraitObjStash` in `debug_menu_portrait.c` | Clears OBJ tile/palette stash on exit |
| Portrait IDs | `enum Portrait` in `include/overworld.h` | Source of truth for `PORTRAIT_*` constants |
| Portrait loader | `LoadPortraitGfx` in `src_custom/portrait_hooks.c` | Shared with dialogue `PORTRAIT()` |
| Text draw | `DebugMenuCopyLine` in `debug_menu.c` | Per-glyph layout into charblock 3 |
| Row palette | `DebugMenuSetLinePalette` in `debug_menu.c` | Per-row BG palette bank on `sbb1F` (used by ante card viewer) |
| Tilemap setup | `DebugMenuSetupTextRows` in `debug_menu.c` | Maps 2×2 blocks on `sbb1F` for each row |
| Graphics load | `DebugMenuLoadGraphics`, `DebugMenuLoadTilemaps` in `debug_menu.c` | Start-menu tiles + custom text rows |
| Field overlay | `overworld_debug_overlay_hooks.c` in `src_custom/debug/` | Player tile/pixel coordinate HUD |
| Public API | `include/debug_menu.h` | Declares `DebugMenuMain`, `DebugMenuClearPortraitObjStash` |
| Music IDs | `include/constants/music_ids.h` | Source of truth for `MUSIC_*` constants |

## TODO

- Add more root-menu entries (flags, maps, duel shortcuts) without hard-coding `DEBUG_ROOT_ITEMS` in multiple places.
- Optional search or category grouping when the track or portrait lists grow further.
- Document or automate sync between `music_ids.h` comments and `debug_menu_music_table.inc`.
- Portrait viewer: expression toggle or cycle (today locked to `EXPRESSION_NEUTRAL`).
- Sprite viewer: direction or walk-frame toggle (today locked to down-facing idle frame 0).
- Reaction viewer: preview sprite picker and animation freeze/step (see [reaction-viewer.md](reaction-viewer.md) TODO).

## Limitations & Bugs

- Track and portrait titles truncate to 15 visible characters after the row prefix marker.
- The music viewer does not stop the previous track explicitly before starting a new one; behavior depends on vanilla `PlayMusic` handling.
- Exiting the music viewer restores root menu BGM (`MUSIC_DECK_ADJUSTMENT_MENU`), not the track that was previewed.
- The portrait viewer always uses `EXPRESSION_NEUTRAL`; other expressions are not selectable.
- Custom portraits only appear if `portrait_hooks.c` can load them; table entries alone are not enough.
- Portrait preview shares OBJ tile/palette scratch with dialogue portraits (`cbb4 + 0x2000`, palette `0xC0..0xFF`); leaving the menu clears this stash.
- Sprite preview uses a separate OBJ stash (`cbb4 + 0x3400`, palette slot 13); leaving the menu clears this stash.
- Reaction preview uses OBJ stash `cbb4 + 0x4200` and shares entity OBJ palettes 0–11; the eye cursor must use OBJ palette slot 15 in the reaction viewer (see [reaction-viewer.md](reaction-viewer.md)).
- Menu text shares BG2 charblock 3 with start-menu-derived assets; large future changes to tile indices need VRAM/layout checks in No$gba or similar.
- Debug menu is only reachable from the overworld field input hook today, not from main menu or duel.
