# Session Log

Working history for AI and human contributors. **Read this at the start of every session** before making changes. **Append an entry when you finish meaningful work.**

Format for new entries (newest first):

```markdown
## YYYY-MM-DD — Short title

**Worked on:** …
**Files:** …
**Outcome:** …
**Open / next:** …
```

---

## 2026-06-21 — Expanded graveyard (40-card LIFO stack)

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

## 2026-06-21 — GY viewer & selector: remove InitTrunkData (fixes trunk corruption)

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
