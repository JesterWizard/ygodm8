# Debug Menu

---

## Index

- [Introduction](#introduction)
- [Access](#access)
- [Root Menu](#root-menu)
- [Music Viewer](#music-viewer)
- [Adding Tracks](#adding-tracks)
- [Text Layout](#text-layout)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

The debug menu is a developer-facing overlay for testing game systems outside normal story flow. It reuses the start-menu background and cursor art, but lives in custom code under `src_custom/debug_menu.c`.

The first implemented feature is a **Music Viewer**: a scrollable list of OST tracks that can be previewed in-game with **B**.

## Access

| Requirement | Detail |
|-------------|--------|
| Runtime toggle | `gRuntimeConfig.enable_debug_menu` in `configs/runtime.c` (default **on**) |
| Input | On the overworld field, press **B** alone (no D-Pad held) |
| Hook | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` |

After the menu closes, overworld state is restored via `OverworldRestoreAfterDebugMenu()` and field music resumes with `PlayOverworldMusic()`.

## Root Menu

The root screen shows two menu rows and uses the same OAM cursor as the vanilla start menu.

| Row | Label | **A** behavior |
|-----|-------|----------------|
| 0 | Music Viewer | Opens the music list |
| 1 | Coming Soon | Plays forbidden SFX (placeholder) |

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

## Text Layout

Menu text is **not** drawn with `CopyStringTilesToVRAMBuffer` for the full string. That API lays out `0x901` glyphs in the vanilla start-menu pattern (about 10 characters before wrapping in VRAM). The debug menu instead calls `sub_8020968()` once per character into fixed tile slots.

| Constant | Value | Role |
|----------|-------|------|
| `DEBUG_CHARS` | 16 | Characters per menu row |
| `DEBUG_ROWS` | 3 | Visible list rows (music viewer) |
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
| Root menu | `DebugMenuRoot` in `src_custom/debug_menu.c` | Two-item list; opens music viewer or forbidden placeholder |
| Music viewer | `DebugMusicViewer` in `src_custom/debug_menu.c` | Scrollable list, preview on **A** |
| Track table | `src_custom/debug_menu_music_table.inc` | `DEBUG_MENU_MUSIC_ENTRY` rows included into `sTracks[]` |
| Track struct | `struct DebugMenuMusicEntry` in `src_custom/debug_menu.c` | `musicId` + `title[24]` |
| Text draw | `DebugMenuCopyLine`, `DebugMenuReadGlyphArg` in `src_custom/debug_menu.c` | Per-glyph layout into charblock 3 |
| Tilemap setup | `DebugMenuSetupTextRows` in `src_custom/debug_menu.c` | Maps 2×2 blocks on `sbb1F` for each row |
| Graphics load | `DebugMenuLoadGraphics`, `DebugMenuLoadTilemaps` in `src_custom/debug_menu.c` | Start-menu tiles + custom text rows |
| Public API | `include/debug_menu.h` | Declares `DebugMenuMain` |
| Music IDs | `include/constants/music_ids.h` | Source of truth for `MUSIC_*` constants |

## TODO

- Implement **Coming Soon** or replace it with the next debug tool.
- Add more root-menu entries (flags, maps, duel shortcuts) without hard-coding `DEBUG_ROOT_ITEMS` in multiple places.
- Optional search or category grouping when the track list grows further.
- Document or automate sync between `music_ids.h` comments and `debug_menu_music_table.inc`.

## Limitations & Bugs

- **Coming Soon** is a non-functional placeholder (forbidden sound only).
- Track titles truncate to 15 visible characters after the playing marker.
- The music viewer does not stop the previous track explicitly before starting a new one; behavior depends on vanilla `PlayMusic` handling.
- Exiting the music viewer restores root menu BGM (`MUSIC_DECK_ADJUSTMENT_MENU`), not the track that was previewed.
- Menu text shares BG2 charblock 3 with start-menu-derived assets; large future changes to tile indices need VRAM/layout checks in No$gba or similar.
- Debug menu is only reachable from the overworld field input hook today, not from main menu or duel.
