---
name: extra-deck-implementation
overview: Add a per-deck Extra Deck (15 fusion-only cards) with SRAM persistence, trunk menu UI, and fusion summon gate.
todos:
  - id: ram-alloc
    content: Allocate EWRAM (93 bytes) and SRAM (99 bytes per mirror) for 3 extra decks
    status: completed
  - id: extra-deck-header
    content: Create include/extra_deck.h with constants and function declarations
    status: completed
  - id: extra-deck-impl
    content: Create src_custom/extra_deck.c with add/remove/owns/is-full/save/load logic
    status: completed
  - id: trunk-submenu
    content: Add Trunk_A_Submenu__Replacement in trunk_hooks.c with dynamic 'Move to Extra Deck' option and LynJump wiring
    status: completed
  - id: block-main-deck
    content: Block fusion monsters from being added to main deck in deck_menu_hooks.c
    status: completed
  - id: fusion-gate
    content: Add Extra Deck ownership check in FusionDuel_BuildFeasibleRecipeIndices
    status: completed
  - id: save-load
    content: Extend player_decks.c save/load to persist extra decks to flash
    status: completed
  - id: enum-global
    content: Add TRUNK_CURSOR_MOVE_TO_EXTRA_DECK to include/global.h
    status: completed
  - id: validate
    content: Build and validate with make test-cards-build
    status: completed
isProject: false
---

## Plan: Extra Deck Implementation

### Data model

- 3 player decks, each gets a 15-card Extra Deck (15 x u16 = 30 bytes)
- EWRAM: `gExtraDeck1/2/3Cards[15]` + `gExtraDeck1/2/3Count` (u8)
- SRAM: mirrored primary/backup blocks, same layout, saved alongside player deck cards
- Cards stored as `u16` IDs with `CARD_NONE` sentinel in unused slots
- `gExtraDeck*Count` tracks current size for fast "full" check

### Files to create

**`include/extra_deck.h`** — constants (`EXTRA_DECK_SIZE` = 15, `EXTRA_DECK_CARD_BYTES` = 0x1E) and function declarations for add/remove/is-full/owns-card/is-fusion-monster

**`src_custom/extra_deck.c`** — implementation:
- `ExtraDeck_IsFusionMonster(cardId)` — SetCardInfo + check `gCardInfo.color == FUSION_CARD`
- `ExtraDeck_GetCards(deckIndex)` — return pointer to correct EWRAM array
- `ExtraDeck_GetCountPtr(deckIndex)` — return pointer to correct count byte
- `ExtraDeck_IsFull(deckIndex)` — count >= 15
- `ExtraDeck_OwnsCard(deckIndex, cardId)` — linear scan
- `ExtraDeck_AddCard(deckIndex, cardId)` — append, increment count
- `ExtraDeck_SaveToFlash(slotPrimary)` — write all 3 extra decks to primary or backup flash
- `ExtraDeck_LoadFromFlash(slotPrimary)` — read all 3 extra decks from flash
- `ExtraDeck_Clear(deckIndex)` — zero out cards + count

### Files to modify

**`include/global.h`** — add `TRUNK_CURSOR_MOVE_TO_EXTRA_DECK = 3` to trunk cursor enum

**`asm/ram_map_ewram.s`** — after existing player deck allocations, add:
```asm
.set EXTRA_DECK_CARD_BYTES, 0x1E
_kernel_malloc_ewram_array gExtraDeck1Cards, EXTRA_DECK_CARD_BYTES
_kernel_malloc_ewram gExtraDeck1Count, 1
_kernel_malloc_ewram_array gExtraDeck2Cards, EXTRA_DECK_CARD_BYTES
_kernel_malloc_ewram gExtraDeck2Count, 1
_kernel_malloc_ewram_array gExtraDeck3Cards, EXTRA_DECK_CARD_BYTES
_kernel_malloc_ewram gExtraDeck3Count, 1
```
Total: 93 bytes EWRAM.

**`asm/ram_map_sram.s`** — after existing `gTimedDuelCompletionFlags` flash allocation, add:
```asm
_kernel_malloc_flash gExtraDeck1Cards, EXTRA_DECK_CARD_BYTES
_kernel_malloc_flash gExtraDeck2Cards, EXTRA_DECK_CARD_BYTES
_kernel_malloc_flash gExtraDeck3Cards, EXTRA_DECK_CARD_BYTES
```
(Counts stored as the first byte of each array — use slot 0 as count or separate flash alloc per count; simpler: allocate an extra array per deck for counts)
Total SRAM per mirror: 99 bytes (3 x 30 + 3 x 1, plus 6 bytes pad for alignment).

**`src_custom/trunk_hooks.c`** — add `Trunk_A_Submenu__Replacement`:
- Dynamically builds submenu options based on selected card type
- For fusion monsters: shows "Details" / "Move to Extra Deck"
- For non-fusion: shows "Details" / "Move to Deck" / "Return to Trunk" (same as vanilla, Return to Trunk only if card is in active deck)
- Cursor navigation arrays (gNextUpOption, gNextDownOption, cursor coords) become dynamic based on option count
- New function `SelectAddToExtraDeck()`: validates fusion type, trunk qty >= 1, extra deck not full, then decrements trunk qty, appends to extra deck
- Error text "Extra deck at 15 card limit" displayed when full (use `Duel_ShowEffectText`-style text or SFX_FORBIDDEN)
- `MoveSelectedCardToExtraDeck()` parallel to existing `MoveSelectedCardToTrunk()` pattern

**`src_custom/deck_menu_hooks.c`** — in `AddCardToDeck__Replacement`:
- Before adding, call `ExtraDeck_IsFusionMonster(cardId)` 
- If TRUE, reject with SFX_FORBIDDEN (fusion monsters only go to Extra Deck)

**`src_custom/fusion_duel.c`** — in `FusionDuel_BuildFeasibleRecipeIndices`:
- After checking `FusionRecipe_IsFeasibleWithSources`, add a new check:
- Get active deck index via `PlayerDecks_GetActiveIndex()`
- Call `ExtraDeck_OwnsCard(activeDeckIndex, recipe->result)` 
- If FALSE, skip this recipe (not in extra deck = can't fusion summon it)

**`src_custom/player_decks/player_decks.c`** — extend save/load:
- In `SaveDecksToFlashPrimary()` and `SaveDecksToFlashBackup()`: also write extra deck data to flash
- In `LoadDecksFromFlashPrimary()` and `LoadDecksFromFlashBackup()`: also read extra deck data from flash
- In `InitUnsavedExtraDecks()`: also clear extra decks
- In `InitNewGame()`: clear all extra decks

**`src_custom/LynJump.event`** — add:
```
POIN Trunk_A_Submenu__Replacement
```

### Error text

```
"Extra deck at 15 card limit"
```
Placed as `APPEND_TEXT` string in `trunk_hooks.c`.

### Validation

After implementation, run:
```
make test-cards-build
```
This validates card layout + full ROM link and catches RAM/symbol issues.
