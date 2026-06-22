# Session Log

Working history for AI and human contributors. **Read this at the start of every session** before making changes. **Append an entry when you finish meaningful work.**

## 2026-06-22 — Fix overworld dialogue text colour (font palette overwritten by start menu)

**Diagnosis:** Overworld dialogue text appeared grey because the start menu overwrites palette bank 0 with `gStartMenuBgPalette` (entry 1 = `0x7AFC` = grey-purple) when it loads. When dialogue starts, the font palette `g82ADC8C` (entry 1 = `0x7FFF` = white) was never reloaded. The text tilemap uses palette bank 0, so the text displayed using the start menu's grey-purple color instead of white.

**Root cause:** A red herring — the BLDCNT layer swap analysis (textbox BG0→BG3) was incorrect. The textbox was a blend target both before and after the swap (`0xDE` has both bit 1 and bit 3 set), so blending was never the issue.

**Fix:** Added `CpuCopy16(g82ADC8C, gPaletteBuffer, 0x20)` to `sub_80532A8()` in `script.c`, which reloads the font palette into bank 0 every time dialogue starts, undoing any start menu palette corruption.

**Files:**
- `src/overworld/script.c` — `sub_80532A8()` now reloads font palette before setting VBlank callback

**Outcome:** `make` passes clean.

## 2026-06-22 — Section titles, scroll bounds, quarter-cursor fix, cursor palette durability

**Worked on:** Four bug fixes in the debug menu:

1. **Root menu scrolls past items** — `DEBUG_ROOT_ITEMS` was 15 but only 13 entries exist in `sRootLabels`. Changed to 13 so cursor can't scroll past "Save" into blank rows.

2. **Quarter cursor at top-left** — `DebugMenuLoadGraphics` called `LoadOam()` with stale overworld OAM data, which (after wiping OBJ VRAM and loading cursor at tile 0) showed a partial cursor tile at (0,0). Added `DebugMenuClearAuxOam()` and `DebugMenuUpdateCursor(0)` before the initial `LoadOam()`.

3. **Section titles** — Each sub-viewer now draws a centered 16-char title at pixel y=16 (text row 2, one row above the list at row 3). Added `DebugMenuDrawSectionTitle(view)` called in `DebugMenuRedraw` for non-root views. `DebugMenuSetupTextRows` clears an extra row. `DebugMenuUploadText` uploads one extra row (title glyphs). Title strings use `APPEND_RODATA` to avoid linker section conflicts.

4. **Cursor palette still breaking on portrait loads** — The VBlank-only fix was insufficient because `LoadPalettes()` (called after every `DebugMenuRedraw`) copies the full `gPaletteBuffer` after VBlank, overwriting the palette RAM fix. Added `CpuCopy16(gStartMenuCursorPalette, ...)` in `DebugMenuRedraw` just before `LoadPalettes()` so the cursor palette is correct in the buffer before it hits palette RAM.

**Files touched:**
- `src_custom/debug/debug_menu_internal.h` — `DEBUG_ROOT_ITEMS` 15→13
- `src_custom/debug/debug_menu.c` — all four fixes

**Outcome:** `make test-cards-build` passes cleanly. All 17 tests OK, full ROM links.

**Open / next:** None.**

## 2026-06-22 — Fix BG2/BG3 + sidebar corruption in OBJ debug menu

**Worked on:** Fixed three bugs in the OBJ-sprite sidebar rewrite that caused art corruption, wrong palette, and persistent BG3 corruption:

1. **BG3 corruption**: `DISPCNT_BG3_ON` was set unconditionally in VBlank, enabling BG3 on maps where it was off (showing stale VRAM data). Made BG3 conditional like BG2.
2. **Tile corruption**: The destride function wrote to `gBgVram.cbb4` at byte offsets up to 19744, but `cbb4[0x4000]` = 16384 bytes. Rows 8+ wrote past the buffer, corrupting adjacent memory (sbb19 tilemap, palette buffer, etc.). Fixed by splitting writes between `cbb4` (offsets < 0x4000) and `cbb5` (offsets ≥ 0x4000).
3. **Cursor tile conflict**: Cursor was at tile 0 which overlapped with sidebar tile at grid (0,0). Relocated cursor to grid row 20 (tile 640) and updated `DebugMenuUpdateCursorSlot` to use the new tile index instead of the hardcoded `0x800` value.

**Files:**
- `src_custom/debug/debug_menu.c` — VBlank BG3 conditional, destride cbb4/cbb5 split, cursor relocation, palette confirmation
- `src_custom/debug/debug_menu_internal.h` — `DEBUG_SIDEBAR_OBJ_TILE_BASE` 256 → 0

**Outcome:** `make test-cards-build` passes. All BG palette banks untouched by debug menu. Sidebar tiles within cbb4+cbb5 bounds. BG2/BG3 display their proper overworld content while menu is open.

**Worked on:** Rewrote the debug menu sidebar from a BG1 tile layer to 50 16×16 OBJ sprites using **OBJ palette bank 12** (above entity palettes 0-11). This eliminates all BG palette bank conflicts — the overworld uses all 16 BG palette banks, so any BG palette bank chosen for the sidebar inevitably corrupts some overworld tiles. The OBJ palette is fully separate.

- Sidebar art destrided from packed 10-wide BG layout (cbb1) to 32-stride 2D OBJ grid (cbb4+cbb5) starting at tile index 256
- 50 OAM entries at slots 16-65 covering 80×160px sidebar as 5×10 grid of 16×16 sprites
- Text kept on BG0 using **BG palette bank 0 slot 9** (font bank) — only 1 palette entry changed, not a full bank
- Removed all BG1 setup from VBlank, DISPCNT, and LoadGraphics — sidebar no longer uses cbb1 or any BG tile layer
- Sub-viewers (portrait, sprite, etc.) retain cbb4 tile area above index 256 for their OBJ data without interfering with sidebar tiles

**Files:**
- `src_custom/debug/debug_menu_internal.h` — OBJ constants, removed BG1 defines
- `src_custom/debug/debug_menu.c` — destride, OAM setup, VBlank, redraw, exit cleanup

**Outcome:** No BG palette bank is clobbered by the debug menu sidebar. The overworld's BG2/BG3 tiles display with their correct palettes while the menu is open. `make test-cards-build` passes.

**Open / next:** None.

## 2026-06-22 — Fix BG2/BG3 palette corruption in debug menu (bank 0 → bank 15)

**Worked on:** The debug menu sidebar palette was loaded into BG palette **bank 0** (the font palette bank). Any visible BG2/BG3 tile whose tilemap entry referenced palette bank 0 showed sidebar colors instead of correct font/map colors. The earlier save/restore of bank 0 only fixed the *exit* — during-menu corruption remained.

**Actual fix:** Changed `DEBUG_BG1_TEXT_PAL_BANK` from 0 to **15** (a high bank unlikely to be referenced by ground/roof tiles). The debug menu now shares sidebar art + text colors in bank 15 instead of clobbering bank 0. Font palette at bank 0 is untouched. Removed the now-unnecessary save/restore of bank 0 and its EWRAM allocation.

**Files:**
- `src_custom/debug/debug_menu_internal.h` — `DEBUG_BG1_TEXT_PAL_BANK` 0 → 15
- `src_custom/debug/debug_menu.c` — removed `gDebugMenuSavedBgPalBank0` save/restore code
- `asm/ram_map.s` — removed `gDebugMenuSavedBgPalBank0` allocation

**Outcome:** `make test-cards-build` passes. Font palette (bank 0) is preserved. Sidebar/text use bank 15 exclusively. BG2 and BG3 tiles should no longer show palette corruption during the debug menu.

**Open / next:** None.

**Worked on:** Two root causes identified and fixed:

1. **BG2 garbage on non-roof maps:** The debug menu VBlank unconditionally wrote `DISPCNT_BG2_ON`, enabling the roof layer (BG2) even on maps without roofs, revealing stale/garbage data in sbb1e. Fixed: read `REG_DISPCNT` at runtime and only include BG2_ON if the overworld had it on.

2. **BG palette bank 0 not restored on exit:** The debug menu loads its sidebar palette into bank 0, clobbering the overworld's font palette. `DebugMenuMain` didn't restore it, and the overworld VBlank (`sub_804F1E4`) only calls `LoadBgOffsets` + `LoadOam` — never `LoadPalettes()`. Fixed: save bank 0 to EWRAM (`gDebugMenuSavedBgPalBank0`) on entry, restore + `LoadPalettes()` on exit. (The overworld restore path `OverworldRestoreAfterDebugMenu` → `sub_804F598` also reloads the font palette, but the fix in `DebugMenuMain` runs before that for correctness.)

**Files:**
- `asm/ram_map.s` — `gDebugMenuSavedBgPalBank0[16]` EWRAM allocation (0x20 bytes)
- `src_custom/debug/debug_menu.c` — `DebugMenuVBlank` reads REG_DISPCNT for BG2 state; `DebugMenuLoadGraphics` same fix; save/restore bank 0 in entry/exit

**Outcome:** `make test-cards-build` passes. Debug menu no longer enables BG2 on non-roof maps. Font palette restored correctly on exit.

**Open / next:** None.

**Worked on:** The debug menu overwrites BG palette bank 0 (the overworld's font/tile palette bank) with sidebar colors. The overworld VBlank (`sub_804F1E4`) only calls `LoadBgOffsets()` + `LoadOam()` — never `LoadPalettes()` — so corrupted palette entries persisted after menu exit, making BG3 ground tiles using bank 0 display wrong colors. Fix: save bank 0 on debug menu entry and restore it + call `LoadPalettes()` on exit.

**Files:**
- `asm/ram_map.s` — added `gDebugMenuSavedBgPalBank0[16]` EWRAM allocation (0x20 bytes)
- `src_custom/debug/debug_menu.c` — save bank 0 in `DebugMenuLoadGraphics`, restore + `LoadPalettes()` in `DebugMenuMain`

**Outcome:** `make test-cards-build` passes. BG palette bank 0 is restored immediately on debug menu exit, fixing BG3 ground tile colors and textbox font.

**Open / next:** BG3 tiles using bank 0 still show sidebar colors *while* the debug menu is open — acceptable for a debug overlay since the sidebar covers the affected area. A full fix would require per-frame palette splitting or using a guaranteed-unused palette bank.

Format for new entries (newest first):

```markdown
## YYYY-MM-DD — Short title

**Worked on:** …
**Files:** …
**Outcome:** …
**Open / next:** …
```

## 2026-06-22 — Debug menu exit: save/restore all display registers

**Worked on:** Overworld dialogue text appeared grey (not white) after exiting the debug menu and talking to an NPC. The text was white in VRAM but grey on screen, indicating stale compositing state from the debug menu.

**Diagnosis:** The debug menu's VBlank callback set `REG_BLDCNT = 0` and `REG_BLDALPHA = 0`, and the standard `OverworldRestoreGraphicsAfterSubmenu()` only restored `REG_BLDCNT = 0` and `REG_BLDY = 7` — it did NOT restore `REG_BLDALPHA`, `REG_WININ`, or `REG_BG0CNT` to the exact overworld entry values. Additionally, stale debug-menu OBJ data in OAM slots beyond the explicitly-cleared ones (portrait/sprite viewer slots 4-15) could persist and render with priority over the dialogue text.

**Fix:** `DebugMenuMain()` now saves all overworld display registers before entry and restores them on exit, clears ALL 128 OAM slots instead of only sidebar+cursor slots, and restores `REG_BLDALPHA` and `REG_WININ` from the saved values (which the standard restore function does not touch).

**Files:**
- `src_custom/debug/debug_menu.c` — added save/restore for REG_DISPCNT, REG_BLDCNT, REG_BLDALPHA, REG_BLDY, REG_WININ, REG_WINOUT, REG_BG0CNT; clear all 128 OAM slots

**Outcome:**
- `make all` passes clean link

**Open / next:**
- Confirm dialogue text is white after debug menu exit
|---

## 2026-06-21 — Debug menu VBlank restructure: restore original overworld-first call order

**Worked on:** Fixed debug menu not displaying at all by restoring the original VBlank call order (overworld VBlank first, then debug menu register setup). My earlier restructure put debug menu setup before the overworld VBlank call, which broke display. Kept the HOFS=0 fix after the overworld VBlank to prevent the sidebar being shifted by the overworld's textbox scroll offset.

**Files:**
- `src_custom/debug/debug_menu.c` — `DebugMenuVBlank` restructured back to: call overworld VBlank → set HOFS=0 → set debug BG/WIN registers → upload VRAM. Removed redundant re-assertion block after overworld VBlank.

**Outcome:** `make test-cards-build` passes. Debug menu sidebar overlay should render correctly on R press.

**Open / next:** None.

---

## 2026-06-21 — Overworld BG layer swap: free BG0/BG1 for debug menu

**Worked on:** Moved overworld ground layer from BG2 to BG3; roof/high layer from BG1 to BG2; textbox from BG0 to BG1. BG0 is now completely unused by the overworld and free for the debug menu. BG1 used only for the textbox overlay (still at same VRAM addresses, just moved to BG1 hardware layer).

**Files:**
- `src/overworld/overworld.c` — `SetBg3Regs` → BG3 (ground, sbb1F, 0x1F82); `SetBg2Regs` → BG2 (roofs, sbb1E, 0x1E81); `SetBg1Regs` → BG1 (textbox, sbb1D, 0x1D0C); `SetBg0Data` → no longer writes REG_BG0CNT; `OverworldSetRegDispcnt` / `OverworldSetRegDispcnt2` → BG0_ON removed, BG1_ON always, BG2_ON conditional (roofs), BG3_ON always (ground)

**Outcome:** `make test-cards-build` passes. Overworld no longer touches BG0. Textbox on BG1, roofs on BG2, ground on BG3. Debug menu gets BG0 (text) and BG1 (sidebar art) free from overworld interference.

**Open / next:** After fixing white-screen regression (SetBg0Data register writes restored for ROM address stability), needed to fix three display bugs caused by the debug menu's VBlank callback not being restored after exit: grey text, BG2/BG3 corruption, and missing debug menu art. Fix: `SetVBlankCallback(overworld_vblank)` at end of `DebugMenuMain()`.

---

## 2026-06-21 — Debug menu VBlank leak fix

**Worked on:** Added configurable `expand_graveyard` runtime option that expands the per-player graveyard from a single `u16` slot to a 40-card LIFO stack. Dual-storage approach keeps the legacy `u16 graveyard` field synced to the top of the expanded array for vanilla compatibility.

**Files:**
- `configs/runtime.h` — added `u8 expand_graveyard` field
- `configs/runtime.c` — defaulted to `FALSE`
- `asm/ram_map.s` — `gExpandedGraveyard[2][40]` + `gExpandedGraveyardCount[2]` EWRAM allocations
- `src_custom/graveyard_expand_hooks.c` — 4 LynJump replacements (GetGraveCardAndClearGrave, GetGraveCardAndClearGrave2, ClearZoneAndSendMonToGraveyard, ClearZoneAndSendMonToGraveyard2) + helper functions
- `src_custom/card_passive_hooks.c` — updated ClearZoneAndSendMonToGraveyard replacement to call GraveyardExpand_PushMonster
- `src_custom/embodiment_of_apophis_hooks.c` — updated both GY writes to use GraveyardExpand_PushMonster
- `src_custom/code_803F02C_hooks.c` — added GraveyardExpand_Init() to InitBoard
- `src_custom/graveyard_scan_hooks.c` + `include/graveyard_scan_hooks.h` — helpers: HasCardInGrave, GetCount, GetNthCard, PopSpecificCard
- `src_custom/graveyard_selector.c` + `include/graveyard_selector.h` — GySelector_ShowSingle / GySelector_ShowCombined (uses deck menu in read-only mode)
- `src_custom/spell_effects/monster_reborn.c` — custom effect with combined GY picker
- `src_custom/spell_effect_hooks.c` — wired MONSTER_REBORN case to custom EffectMonsterReborn
- `include/graveyard_expand_hooks.h` — public helpers header
- `src_custom/LynJump.event` — added GetGraveCardAndClearGrave + GetGraveCardAndClearGrave2 entries

**Outcome:**
- `make test-cards-build` passes clean link
- When `expand_graveyard = FALSE` (default): zero behavioral change
- When `expand_graveyard = TRUE`: all GY operations use the expanded array; Monster Reborn shows combined GY picker

**Open / next:**
- GY viewer: now accessible from B menu (cursor down from Surrender/Turn End to GY zones, press A) — implemented
- Specific-card GY scan replacements: helper exists but individual function replacements for DM/Gernia/DFK checks in monster_effects.c and permanent_effect.c are still needed (ponytail: known ceiling)
- Premature Burial / Call of the Haunted: currently pop top card from expanded GY (works); per-player selector UI is future work
- Delete stale `src_custom/graveyard_*.h` files after migration to `include/`

## 2026-06-21 — B menu GY cursor navigation

**Worked on:** Extended the duel field B menu cursor to allow moving DOWN from the 4 options (Details, Turn End, Discard, Surrender) to each player's graveyard zone. Pressing A on a GY zone opens a read-only trunk-style list of all cards in that GY.

**Files:**
- `include/duel_b_menu.h` — added B_MENU_GY_OPPONENT=4, B_MENU_GY_PLAYER=5 to enum, declared Duel_GraveyardViewer_Open
- `src_custom/duel_b_menu_hooks.c` — added highlight tile offsets + navigation table entries for GY zones; extended HighlightBMenuOption from 4 to 6 entries; added GY highlight positions to stale cells list
- `src_custom/duel_opponent_hand_scroll_hooks.c` — added B_MENU_GY_OPPONENT / B_MENU_GY_PLAYER A-button cases to BMenuMainWithSurrender
- `src_custom/duel_gy_viewer.c` — new file: GY viewer function that loads expanded GY cards into gDeckMenu and calls DeckMenuMainReadOnly

**Outcome:**
- `make test-cards-build` passes clean link
- Cursor navigation: DOWN from Turn End -> opponent GY -> player GY -> (stays). UP goes back up. Left/Right stay on GY. Press A to open GY viewer, then browse + B to exit back to B menu

**Open / next:**
- GY viewer still returns to B menu after exit; no field cursor reset needed
- Premature Burial / Call of the Haunted per-player GY selector still to wire up

## 2026-06-21 — GY viewer: fix black screen, turn-counter corruption, card filtering

**Worked on:** Fixed three issues with the GY viewer:
- Rewrote `duel_gy_viewer.c` to use a custom input loop instead of `DeckMenuMainReadOnly()`, skipping the exit tasks (`RunPlayerDeckTask(8)`, `RunTrunkTask(9)`) that corrupted duel state (turn counter)
- After viewer exit, caller now calls `DuelBMenu_Init(cursorState)` instead of `DuelBMenu_RefreshOverlay`, which runs `InitBMenuWithSurrender` to properly re-set `REG_DISPCNT` and window registers (fixes black screen)
- Expanded GY already only stores monster cards sent from field via `ClearZoneAndSendMonToGraveyard` hooks (no filtering needed — already correct)

**Files:**
- `src_custom/duel_gy_viewer.c` — full rewrite: custom input loop, no exit tasks, no final DisableDisplay
- `src_custom/duel_opponent_hand_scroll_hooks.c` — changed `DuelBMenu_RefreshOverlay` → `DuelBMenu_Init` in both GY viewer cases

**Outcome:**
- `make test-cards-build` passes clean link
- B menu overlay fully restored after GY viewer exit (no black screen)
- Turn counter unaffected by GY viewer navigation
- GY already filtered to field-origin monsters

**Open / next:**
- Specific-card GY scan replacements for DM/Gernia/DFK checks still needed
- Premature Burial / Call of the Haunted per-player GY selector UI still to wire up

## 2026-06-21 — Debug menu BG1 sidebar overlay

**Worked on:** Rewrote the debug menu from a full-screen start-menu-takeover to a BG1 sidebar overlay on the overworld, using `src_custom/assets/menus/debug_menu.png` (80x160 indexed PNG) as sidebar art. The overworld remains visible behind the sidebar via WIN0 window clipping (columns 20-29). Text/tilemap now writes to BG1 charblock cbb1 and screenbase sbb18 instead of the old start-menu layout.

**Files:**
- `graphics.mk` — added `DEBUG_MENU_*` asset variables, build rule for `.lz`, clean rule for `menus/`, added to `graphics-rules` target
- `Makefile` — added `custom_object_dep` for `debug/debug_menu.o` on `$(DEBUG_MENU_LZ) $(DEBUG_MENU_PAL)`
- `src_custom/debug/debug_menu.c` — sidebar on BG1 at columns 0-9; text on BG0 with small overworld font via `CopyStringTilesToVRAMBuffer`; overworld VBlank; no screen transition
- `src_custom/debug/debug_menu_internal.h` — BG1 sidebar at columns 0-9, BG0 text constants, WIN0 aligned to left 80px
- `documentation/debug-menu.md` — updated introduction, text layout section, code locations, and limitations

**Outcome:**
- `make test-cards-build` passes clean
- Debug menu now renders as an 80px sidebar on the right side of the screen with the overworld visible behind it
- No screen transition/flash on open: removed `ClearGraphicsBuffers`, `LoadVRAM`, `LoadBgVRAM`, `FadeOutMusic`, and `PlayMusic(MUSIC_DECK_ADJUSTMENT_MENU)` calls so the sidebar appears seamlessly over the running overworld

**Open / next:**
- Overworld OBJ sprites (player, NPCs) may show wrong colors while menu is open (cursor palette overwrites OBJ slot 0) — acceptable for a debug overlay

**Worked on:** Removed `InitTrunkData()` calls from the GY viewer and graveyard selector.
`InitTrunkData()` calls `RefreshTrunkOwnershipTotals()`, which reads `gDeckMenu.cards`
to add deck card quantities to `gTotalCardQty`. But during GY viewing,
`gDeckMenu.cards` holds GY cards (not the player's deck), so GY card IDs
leaked into the trunk's ownership totals, corrupting trunk display.

**Files:**
- `src_custom/duel_gy_viewer.c` — removed `InitTrunkData()` call, unused externs
- `src_custom/graveyard_selector.c` — removed both `InitTrunkData()` calls, unused extern

**Outcome:** `make test-cards-build` passes. Trunk ownership totals are no longer
corrupted after viewing a GY during a duel.

**Note on 6 opponent GY cards:** The expanded GY correctly tracks all monsters
sent to GY from the field (battle destruction, tribute summons, card effects).
During the AI's turns, the opponent naturally accumulates GY cards from its own
plays. This is correct behavior — the GY viewer shows exactly what's in the GY.

**Open / next:**
- Specific-card GY scan replacements still needed
- Premature Burial / Call of the Haunted per-player GY selector UI still to wire up

## 2026-06-21 — Remove black overlay from debug menu

**Worked on:** Eliminating a persistent black overlay that obscured the debug menu sidebar art. BG0 (screen block 19) was rendering on top of BG1 (screen block 18) even when all its tiles referenced palette bank 15 with tile 0 (which should be transparent). Tried filling the tilemap with palette-bank-15 mask — overlay remained.

**Fix:** Removed BG0 from the debug menu entirely — no more `DISPCNT_BG0_ON` in `DebugMenuVBlank`, no `REG_BG0CNT` writes (save or restore), no sbb19 upload in `DebugMenuUploadBg1`, no sbb19 fill in `DebugMenuLoadGraphics`. Only BG1 renders now.

**Files:**
- `src_custom/debug/debug_menu.c` — stripped BG0 from VBlank, load, upload, and teardown; removed `gSavedDebugMenuBg0Cnt` extern

**Outcome:** `make` builds clean. BG0 layer is gone — sidebar art on BG1 should display without black overlay. Text overlay (written to sbb19) is currently invisible since BG0 is off — will restore as a separate fix.

**Open / next:**
- Restore text overlay without reintroducing the black background — e.g. merge text tilemap into sbb18 alongside art, or disable BG0 outside the text area via a second window (WIN1).

