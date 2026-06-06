# Save Anywhere

---

## Index

- [Introduction](#introduction)
- [Access](#access)
- [Player Flow](#player-flow)
- [Plan](#plan)
- [Save Data](#save-data)
- [Overworld Transition](#overworld-transition)
- [Continue / Load Behavior](#continue--load-behavior)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

**Save Anywhere** is a debug-menu tool that opens the same save prompt as the player’s house bed (LP restored, “Would you like to save?”, Yes/No), but from any overworld map and position.

Vanilla **Continue** always loads map 9 (player house) and does not persist the player’s exact tile coordinates in the main save blob. This feature stores map id, map state, connection, player X/Y, and facing direction in a separate flash-backed struct so **Continue** can restore the field exactly where the save happened.

The tool is developer-facing and gated by the same runtime toggle as the debug menu (`enable_debug_menu`).

## Access

| Requirement | Detail |
|-------------|--------|
| Runtime toggle | `gRuntimeConfig.enable_debug_menu` in `configs/runtime.c` (default **on**) |
| Overworld input | Press **R** alone on the field to open the debug menu |
| Root row | Scroll to **Save Anywhere** (row 12, last item) and press **A** |

See [debug-menu.md](debug-menu.md) for shared menu graphics, teardown, and overworld restore behavior.

## Player Flow

1. Open the debug menu on the overworld (**R**).
2. Highlight **Save Anywhere** and press **A** — the menu closes immediately and the field is restored (same path as exiting any debug submenu).
3. After one stable overworld frame, the house save dialogue opens (no purple screen fade).
4. LP is restored and the Yes/No save prompt appears.
5. **Yes** — vanilla `SaveGame()` runs; progress and custom position data are written to flash.
6. **No** — dialogue closes; the player remains on the field.

After a **Save Anywhere** save, **Continue** from the title screen loads the saved map and applies the saved coordinates once the map entry script finishes.

Saving through any other path (house bed, normal story save, etc.) clears the custom position blob so **Continue** uses vanilla map routing again.

## Plan

High-level stages:

| Stage | Trigger | Result |
|--------|---------|--------|
| Menu selection | **A** on **Save Anywhere** in `DebugMenuRoot` | Sets `gDebugMenuPendingSaveAnywhere` and exits the menu |
| Field restore | `OverworldRestoreAfterDebugMenu()` in `ProcessInput__Replacement` | Reloads map OBJ/BG state after debug GFX teardown |
| Deferred open | `sub_804EF10__Replacement` (two-frame deferral) | One skipped end frame, one full end frame, then opens dialogue |
| Dialogue | `DebugSaveAnywhere_OpenDialogNow()` | Vanilla `OverworldLoadGraphics`, entity palettes, `InitiateScript` with house prompt |
| Position capture | `SaveGame__Replacement` when `gDebugSaveAnywherePendingCapture` | Writes `DebugSaveAnywhereData` to EWRAM + flash mirrors |
| Continue load | `sub_80523EC__Replacement` + `DebugSaveAnywhere_ApplySavedCoords` | Overrides hardcoded map 9 warp, then applies X/Y/direction after entry script |

Flag lifecycle during one Save Anywhere session:

| Flag | Set when | Cleared when |
|------|----------|--------------|
| `gDebugMenuPendingSaveAnywhere` | **A** on root row | `DebugMenu_ApplyPendingSaveAnywhere` after menu exit |
| `gDebugSaveAnywhereOpenDialogPending` | `DebugMenu_ApplyPendingSaveAnywhere` | First full end frame after restore |
| `gDebugSaveAnywhereOpenDialogReady` | End of deferral frame | `DebugSaveAnywhere_OpenDialogNow` |
| `gDebugSaveAnywherePendingCapture` | Start of `OpenDialogNow` (after gfx sync) | `SaveGame__Replacement` on **Yes**, or end of `InitiateScript__Replacement` if dialogue ends without save |
| `gDebugSaveAnywhereRestorePending` | Load from flash when magic valid | `sub_80523EC__Replacement` when map override applied |
| `gDebugSaveAnywhereApplyCoordsPending` | Load from flash when magic valid | `DebugSaveAnywhere_ApplySavedCoords` after entry script |

## Save Data

`struct DebugSaveAnywhereData` (`include/debug_save_anywhere.h`), 12 bytes (`0xC`):

| Field | Type | Purpose |
|--------|------|---------|
| `magic` | `u8` | `0x5A` (`DEBUG_SAVE_ANYWHERE_MAGIC`) when position is valid |
| `direction` | `u8` | Player facing (`DIRECTION_*`) |
| `mapId` | `u16` | `gOverworld.map.id` at save time |
| `mapState` | `u16` | `gOverworld.map.state` |
| `mapConnection` | `u16` | `gOverworld.map.unkC` (entrance / connection) |
| `x` | `u16` | Player tile X (`gOverworld.objects[0].x`) |
| `y` | `u16` | Player tile Y (`gOverworld.objects[0].y`) |

On capture, `DebugSaveAnywhere_CaptureCurrentPosition` also mirrors map id/state into `gOverworld.map.unk8` / `unkA` so the vanilla save table stays consistent with the custom blob.

Storage:

| Buffer | Location | Role |
|--------|----------|------|
| `gDebugSaveAnywhereData` | EWRAM + flash primary/backup (`asm/ram_map.s`) | Live copy and SRAM mirrors |
| Flash write | `DebugSaveAnywhere_SaveToFlashPrimary/Backup` | Called from `sub_800AD84` / `sub_800ADA4` hooks |
| Flash read | `DebugSaveAnywhere_LoadFromFlashPrimary/Backup` | Called from save-slot load hooks |

## Overworld Transition

Save Anywhere reuses the same debug-menu exit path as other submenus so OBJ tiles and palettes are not left in menu layout.

```
Debug menu closes (DisableDisplay)
  → OverworldRestoreAfterDebugMenu()
  → gSkipOverworldEndFrameAfterSubmenu = 1   // skip one end frame
  → [next frame] full OverworldRunEndFrame
  → gDebugSaveAnywhereOpenDialogReady
  → [next frame] DebugSaveAnywhere_OpenDialogNow()
       → vanilla OverworldLoadGraphics (direct call, not overlay hook)
       → sub_804F580 / sub_804F598 (entity + font OBJ palettes)
       → MatchSetter_RefreshField()
       → LoadObjVRAM / LoadPalettes
       → OverworldRunEndFrame()
       → gDebugSaveAnywherePendingCapture = TRUE
       → InitiateScript(house save prompt)
```

Dialog-specific behavior while `gDebugSaveAnywherePendingCapture` is set:

| Concern | Handling |
|---------|----------|
| Purple BLDY fade | `sub_8054AB0__Replacement` case 0 calls `sub_8054EC8_NoFade` instead of `sub_8054EC8` |
| House `LOAD_SPRITE(1, SPRITE_INVISIBLE)` | Skipped in `sub_8053D50__Replacement` — would overwrite OBJ slot 1 tiles at VRAM `0x06010080` (`gUnk08103264[1] == 4`) |
| Debug coordinate overlay | `OverworldOverlay_*` hooks in `overworld_debug_overlay_hooks.c` no-op during capture |
| Script source | `EventSystem_GetHouseSavePromptScript()` → `map_09_state_00` save prompt (`events/scripts/map_09_state_00.c`) |

## Continue / Load Behavior

1. **Load save slot** — `DebugSaveAnywhere_LoadFromFlash*` copies the blob into EWRAM. Valid magic sets restore + apply-coords flags.
2. **Continue map warp** — Vanilla calls `sub_80523EC(9, 1, 0)`. The hook replaces id/state/connection when `gDebugSaveAnywhereRestorePending` is set.
3. **Map init** — `InitOverworld` and the map entry script run as usual.
4. **Coordinate apply** — `DebugSaveAnywhere_ApplySavedCoords` runs at the end of `InitiateScript__Replacement` for normal scripts, and is deferred until after the entry script so map setup does not overwrite saved X/Y.
5. **Followers** — Slots 13–14 are synced to the player when apply-coords runs.

Normal saves call `DebugSaveAnywhere_ClearSavedPosition()` so a subsequent **Continue** without Save Anywhere data follows vanilla routing.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Public API | `include/debug_save_anywhere.h` | Struct, magic, flags, function declarations |
| Core logic | `DebugSaveAnywhere_*` in `src_custom/debug_save_anywhere.c` | Capture, apply, flash sync, dialogue open |
| Root menu row | `DebugMenuRoot` in `src_custom/debug/debug_menu.c` | Row 12 label **Save Anywhere**; **A** sets pending flag and breaks out |
| Menu handoff | `DebugMenu_ApplyPendingSaveAnywhere` in `src_custom/debug_save_anywhere.c` | Converts menu pending → open-dialog pending |
| Overworld input | `ProcessInput__Replacement` in `src_custom/overworld_hooks.c` | Restore after menu, defer dialogue open |
| End-frame deferral | `sub_804EF10__Replacement` in `src_custom/overworld_hooks.c` | Skip frame + two-phase dialog ready |
| End-frame helper | `OverworldRunEndFrame` in `src_custom/overworld_hooks.c` | Shared sprite/overlay sync; skips overlay during capture |
| Field restore | `OverworldRestoreAfterDebugMenu` in `src_custom/overworld_hooks.c` | BG/OBJ/palette restore after debug menu |
| Save hook | `SaveGame__Replacement` in `src_custom/code_800AC64_hooks.c` | Captures or clears position on save |
| Flash I/O | `sub_800AD84` / `sub_800ADA4` / load hooks in `src_custom/code_800AC64_hooks.c` | Mirrors custom blob with save slot |
| Continue map | `sub_80523EC__Replacement` in `src_custom/map_transition_hooks.c` | Overrides hardcoded house warp |
| Coord apply timing | `InitiateScript__Replacement` in `src_custom/event_system_hooks.c` | Applies coords after entry script; post-dialog gfx restore |
| House script resolver | `EventSystem_GetHouseSavePromptScript` in `src_custom/event_system_hooks.c` | Points at `map_09_state_00` save prompt node |
| No-fade SPECIAL(0) | `sub_8054AB0__Replacement` in `src_custom/script_commands2_hooks.c` | Save-anywhere dialogue text box without purple fade |
| LOAD_SPRITE guard | `sub_8053D50__Replacement` in `src_custom/script_commands1_hooks.c` | Prevents house script from stomping OBJ slot 1 VRAM |
| Overlay guard | `src_custom/debug/overworld_debug_overlay_hooks.c` | Blocks coordinate overlay during save dialogue |
| RAM / SRAM | `asm/ram_map.s` | EWRAM flags + `gDebugSaveAnywhereData` flash allocation |
| LynJump | `src_custom/LynJump.event` | `sub_80523EC`, `SaveGame`, `sub_8054AB0`, `sub_8053D50`, etc. |
| Vanilla script | `events/scripts/map_09_state_00.c` | Source event script for LP restore + save prompt text |

## TODO

- Document expected test maps / coordinates for manual QA (Continue restore on multi-state maps).
- Consider a dedicated save-anywhere event script without house-only `LOAD_SPRITE` instead of hooking `sub_8053D50`.
- Optional runtime toggle separate from `enable_debug_menu` if the feature is needed without full debug access.

## Limitations & Bugs

- Requires `enable_debug_menu`; there is no standalone player-facing toggle.
- Uses the house save **music** and **wording** from `map_09_state_00` (LP restored message, Yes/No layout).
- Map state resolution in `sub_80523EC__Replacement` still runs vanilla `gMapStates` flag checks after the custom id/state override.
- Saving outside Save Anywhere clears custom position data; only the most recent Save Anywhere **Yes** keeps Continue routing.
- If flash magic is corrupt or missing, **Continue** falls back to vanilla map 9 behavior.
- Follower slots 13–14 are synced on coord apply; other follower edge cases are unchanged from vanilla.
