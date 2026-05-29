# Reaction Viewer

---

## Index

- [Introduction](#introduction)
- [Access](#access)
- [Controls](#controls)
- [Reaction List](#reaction-list)
- [On-Screen Layout](#on-screen-layout)
- [Animation Model](#animation-model)
- [Palette Layout](#palette-layout)
- [Adding Reactions](#adding-reactions)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

The **Reaction Viewer** is a debug-menu tool for previewing overworld reaction bubbles (`REACTION()` script command) on a live sprite. Each list row maps to one `enum OverworldReactions` value. The highlighted reaction plays its full vanilla animation sequence on **SPRITE_PLAYER** (down-facing idle frame) while the list scrolls on the left.

Design goals:

- Match field behavior: same bubble tiles, palette slots, and frame tables as `sub_8053B40` / overworld reaction objects.
- Animate automatically when the cursor moves (no **A** press required).
- Avoid palette clashes between reaction OBJ banks, the player preview, and the start-menu eye cursor.

The viewer is opened from the debug menu root (**B** on the overworld). See [debug-menu.md](debug-menu.md) for shared text layout, graphics load, and root-menu access.

## Access

| Requirement | Detail |
|-------------|--------|
| Runtime toggle | `gRuntimeConfig.enable_debug_menu` in `configs/runtime.c` (default **on**) |
| Input | Overworld **B** → root menu → **Reaction Viewer** (row 3) |
| Hook | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` → `DebugMenuMain` |

Root menu shows three visible rows; the fourth item (**Reaction Viewer**) scrolls into view with **Down** from **Sprite Viewer**.

## Controls

| Input | Action |
|-------|--------|
| **Up** / **Down** | Move cursor; list scrolls when cursor passes the top or bottom visible row |
| **B** | Return to root menu |

There is no **A** action. Changing the cursor restarts that reaction’s animation from frame 0.

Seven reactions are listed (`DEBUG_ROWS` = 3 visible at a time).

## Reaction List

Entries are defined in `src_custom/debug/debug_menu_reaction_table.inc`:

| Menu label | `reactionId` | Vanilla enum |
|------------|--------------|--------------|
| Exclamation | 0 | `REACTION_EXCLAMATION_MARK` |
| Question | 1 | `REACTION_QUESTION_MARK` |
| Love Heart | 2 | `REACTION_LOVE_HEART` |
| Ellipsis | 3 | `REACTION_ELLIPSIS` |
| Sweatdrop | 4 | `REACTION_SWEATDROP` |
| Angry | 5 | `REACTION_ANGRY` |
| Chant | 6 | `REACTION_CHANT` |

`reactionId` values must match `enum OverworldReactions` in `include/overworld.h` (lines 837–843). List order in the `.inc` file must stay aligned with those IDs because `DebugMenuReactionAnimStep` indexes `g8105114[reactionId]`.

## On-Screen Layout

| Region | Implementation |
|--------|----------------|
| List (left) | Three rows × 16 characters via `DebugMenuFormatTitleRow` / `DebugMenuCopyLine` |
| Text color | BG palette 15 (`DEBUG_MENU_TEXT_PAL`); restored with `DebugMenuRestoreTextPalettes` |
| Eye cursor | OAM slot 0; OBJ palette **slot 15** (`DEBUG_MENU_CURSOR_PAL_SLOT`) |
| Player preview | `SPRITE_PLAYER`, frame 0, OAM slot 1 (`debug_menu_sprite.c`) |
| Reaction bubble | OAM slot 2; 16×16 OBJ above the player’s head |

### Key constants

| Constant | Value | Role |
|----------|-------|------|
| `DEBUG_REACTION_TILE_OFFSET` | `0x4200` | OBJ tile stash in `gBgVram.cbb4` |
| `DEBUG_REACTION_TILE_NUM` | `0x4200 / 32` | OAM tile index for the bubble |
| `DEBUG_REACTION_X_TILE` / `Y_TILE` | 25 / 7 | Bubble position (pixels = × 8) |
| `DEBUG_REACTION_OAM_SLOT` | 2 | OAM slot (cursor = 0, player = 1) |
| `DEBUG_SPRITE_PAL_SLOT` | 13 | Player entity palette row via `g82AD20C` |
| `DEBUG_MENU_CURSOR_PAL_SLOT` | 15 | Eye cursor palette (not overwritten by entity load) |
| `DEBUG_MENU_TEXT_PAL` | 15 | BG palette bank for list glyphs |

On exit, `DebugMenuHideReactionOam`, `DebugMenuHideSprite`, `DebugMenuClearReactionStash`, and `DebugMenuClearSpriteObjStash` clear preview VRAM and palette scratch.

## Animation Model

Animations use the same tables as script `REACTION()`:

| Table | Role |
|-------|------|
| `g8105114[reactionId][]` | Sequence of `{ bubbleId, holdFrames }`; `bubbleId == -1` marks loop end |
| `g81032A2[bubbleId]` | Tile index into `ReactionBubbleTiles` |
| `g82AD2B6[bubbleId]` | OBJ palette slot for that bubble |

`DebugMenuReactionAnimStep` in `debug_menu_reaction.c`:

1. Decrements a per-frame hold timer (`holdFrames` from the table, minimum 1).
2. Advances the sequence index when the timer expires.
3. On bubble change, reloads tiles via `DebugMenuLoadReactionGfx` (same copy pattern as `sub_804EFE8`).
4. Loops to sequence index 0 after the `-1` terminator.

`bubbleId == 0` hides the reaction OAM (pause / end of sequence).

Vanilla reference: `sub_8053B40` in `src/overworld/script_commands1.c`.

## Palette Layout

Reaction preview loads overworld entity OBJ palettes the same way as `LoadSpriteGraphics()`:

```c
CpuCopy16(gOverworldEntityPalettes, gPaletteBuffer + 256, 0x180);  // OBJ slots 0–11
```

That copy **overwrites OBJ palette slot 0**, where `DebugMenuLoadTilemaps` normally places `gStartMenuCursorPalette`. The reaction viewer therefore:

1. Calls `DebugMenuLoadReactionObjPalettes()` each frame (and after list redraw).
2. Restores `gStartMenuCursorPalette` into **OBJ slot 15**.
3. Sets the cursor OAM `paletteNum` to **15** via `DebugMenuUpdateCursorSlot(..., DEBUG_MENU_CURSOR_PAL_SLOT)`.

Reaction bubbles use `g82AD2B6[bubbleId]` (slots 0, 2, 4, etc.) — identical to overworld `sub_804E918`. No separate “line art” palette override is applied in the debug menu.

| OBJ slot | Owner in reaction viewer |
|----------|---------------------------|
| 0–11 | `gOverworldEntityPalettes` (reaction bubbles) |
| 13 | Player preview (`g82AD20C[SPRITE_PLAYER]`) |
| 15 | Start-menu eye cursor |

The ante card viewer uses the same cursor-on-slot-15 pattern; see [ante-card-viewer.md](ante-card-viewer.md).

### Assets

| Asset | Path |
|-------|------|
| Bubble tiles | `src/overworld/entities/reaction_bubbles.4bpp` (`ReactionBubbleTiles` in `entities.c`) |
| Entity palettes | `src/overworld/entities/palette.gbapal` (`gOverworldEntityPalettes`) |
| Bubble → tile / palette | `g81032A2`, `g82AD2B6` in ROM (`entities.c` / overworld) |

## Adding Reactions

1. Confirm the reaction exists in `enum OverworldReactions` in `include/overworld.h` and has a sequence in `g8105114`.
2. Add one line to `src_custom/debug/debug_menu_reaction_table.inc`:

   ```c
   DEBUG_MENU_REACTION_ENTRY(REACTION_YOUR_REACTION, "Your Label")
   ```

3. Rebuild (`make`).

If the new reaction’s `reactionId` does not equal its row index in the table, either keep table order matching enum values or change `DebugMenuReactionAnimStep` to pass `sReactions[cursor].reactionId` instead of using `cursor` as the `g8105114` index.

No C changes are required for a new row when IDs and table order stay aligned.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Main loop | `DebugReactionViewer` in `src_custom/debug/debug_menu_reaction.c` | Input, animation step, OAM each frame |
| List draw | `DebugMenuDrawReactions` in `debug_menu_reaction.c` | Scrollable titles + text palette restore |
| Animation step | `DebugMenuReactionAnimStep` in `debug_menu_reaction.c` | `g8105114` timing and bubble swaps |
| Gfx load | `DebugMenuLoadReactionGfx` in `debug_menu_reaction.c` | `ReactionBubbleTiles` → `cbb4 + 0x4200` |
| OAM | `DebugMenuApplyReactionOam` in `debug_menu_reaction.c` | 16×16 bubble; `g82AD2B6` palette |
| Reaction table | `src_custom/debug/debug_menu_reaction_table.inc` | `DEBUG_MENU_REACTION_ENTRY` rows |
| Struct | `struct DebugMenuReactionEntry` in `debug_menu_internal.h` | `reactionId` + `title[24]` |
| OBJ palette load | `DebugMenuLoadReactionObjPalettes` in `src_custom/debug/debug_menu.c` | Entity palettes + cursor on slot 15 |
| Cursor OAM | `DebugMenuUpdateCursorSlot` in `debug_menu.c` | Optional `paletteNum` (15 in reaction viewer) |
| Player preview | `DebugMenuLoadSpriteFrameIfChanged`, `DebugMenuApplySpriteOam` in `debug_menu_sprite.c` | Shared with sprite viewer |
| Root wiring | `DebugMenuRoot`, `DebugMenuRedraw` in `debug_menu.c` | `DEBUG_VIEW_REACTION`, fourth root row |
| Reaction IDs | `enum OverworldReactions` in `include/overworld.h` | Source of truth for `REACTION_*` |
| Vanilla script | `sub_8053B40` in `src/overworld/script_commands1.c` | Field `REACTION()` implementation |
| Vanilla gfx | `sub_804EFE8` in `src/overworld/overworld.c` | Field bubble tile upload |
| Vanilla OAM | `sub_804E918` in `src/overworld/overworld.c` | Field bubble palette slot |
| Sequence / tile tables | `g8105114`, `g81032A2`, `g82AD2B6` | ROM data (see `ldscript.ld`) |

## TODO

- Optional **A** to freeze animation or step one bubble frame manually.
- Preview sprite picker (today locked to `SPRITE_PLAYER`).
- Direction / walk-frame toggle for the preview sprite.
- Dedicated `reaction_bubbles.gbpal` in the build if shared `palette.gbapal` row 0 cannot represent line-art indices correctly on hardware.

## Limitations & Bugs

- Preview sprite is always **SPRITE_PLAYER**, down idle frame 0.
- Menu labels truncate to 16 characters (`DEBUG_CHARS`).
- `g8105114` is indexed by list cursor index; table order must match `enum OverworldReactions` numeric values (0–6 today).
- Reaction and player previews share OBJ charblock 4 with the start-menu cursor tiles and other debug viewers; stash offsets must not overlap (`0x3400` player, `0x4200` reaction).
- Line-art bubbles (Angry, Chant) use the same entity palette rows as the field; if colors differ from the PNG source art, fix belongs in assets or overworld palette tables, not a debug-only palette hack.
- Viewer is only reachable from the debug menu on the overworld field.
- List redraw (`DebugMenuLoadTilemaps`) briefly loads the cursor palette to slot 0; reaction viewer restores slot 15 on the same frame via `DebugMenuLoadReactionObjPalettes`.
