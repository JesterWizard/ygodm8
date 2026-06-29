# Expanded Graveyard

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Runtime toggle](#runtime-toggle)
- [Player access](#player-access)
- [API](#api)
- [EWRAM allocations](#ewram-allocations)
- [AI simulation](#ai-simulation)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Vanilla duel state stores each duelist's graveyard as a single `u16` in `gDuel.duelistbattleState[duelist].graveyard`. Only the most recently sent card is retained; older graveyard cards are lost. That is enough for vanilla effects that only care about the top card, but not for custom cards that need to read, pick from, or banish specific cards deeper in the stack (for example Dark Magician of Chaos).

When `expand_graveyard` is enabled, each fixed duelist (`DUEL_PLAYER`, `DUEL_OPPONENT`) gets a 40-card LIFO (Last In, First Out) stack in EWRAM. The legacy `graveyard` field is kept in sync with the stack top so existing vanilla and custom code that only reads the top card continues to work.

Design goals:

- Store the full graveyard history up to deck size (40 cards).
- Let the player inspect either graveyard from the duel B-menu.
- Keep vanilla top-card semantics for legacy paths.
- Prevent AI speculative simulations from leaking phantom cards into the visible stack.

## Plan

### Dual-storage model

| Storage | Type | Role when enabled |
|---------|------|-------------------|
| `gExpandedGraveyard[duelist][index]` | `u16` stack | Authoritative graveyard history |
| `gExpandedGraveyardCount[duelist]` | `u8` | Number of cards in the stack |
| `gDuel.duelistbattleState[duelist].graveyard` | `u16` | Mirror of stack top (`CARD_NONE` when empty) |

All pushes, pops, and indexed removes go through `GraveyardExpand_*` in `src_custom/expanded_graveyard.c`. After every mutation, `SyncLegacyTop` writes the top card (or `CARD_NONE`) into the legacy field.

When `expand_graveyard` is **off**, the API falls back to the legacy single-slot field and behavior matches vanilla.

### Stack rules

| Rule | Behavior |
|------|----------|
| Capacity | `EXPANDED_GRAVEYARD_CAPACITY` (40) per duelist |
| Overflow | Oldest card is dropped (shift left, then push) |
| Index 0 | Bottom of stack (first card sent) |
| Index `count - 1` | Top of stack (most recent send) |
| Duelist mapping | `PushTurn` / `PopTurn` map turn duelist → fixed duelist via `gTurnDuelistBattleState` |

### Send-to-graveyard write paths

Most cards reach the expanded stack through `ClearZoneAndSendMonToGraveyard` in `src_custom/card_passive_hooks.c`, which pushes any non-empty zone card (monsters, spells, traps). Additional direct pushes exist for edge cases (Robbin Zombie mill, Ojama Trio token path, Embodiment of Apophis, Magical Merchant, Guardian Treasure).

## Runtime toggle

| Field | Location | Default |
|-------|----------|---------|
| `expand_graveyard` | `configs/runtime.c` → `gRuntimeConfig.expand_graveyard` | **on** (`TRUE`) |

When off: zero behavioral change from vanilla for graveyard storage; B-menu graveyard viewer options are hidden and navigation skips them.

## Player access

| Input | Action |
|-------|--------|
| **B** (duel menu) → opponent graveyard row | Open opponent graveyard viewer (`B_MENU_GY_OPPONENT`) |
| **B** (duel menu) → player graveyard row | Open player graveyard viewer (`B_MENU_GY_PLAYER`) |
| **Up** / **Down** | Scroll card list |
| **A** | Full card detail view; **B** returns to list |
| **B** | Close viewer and return to duel |

The B-menu shows the top graveyard card name for each duelist when expanded mode is on (`GraveyardTopCardForDisplay` in `duel_b_menu_hooks.c`).

`Duel_GraveyardViewer_Open` in `src_custom/duel_gy_viewer.c` loads the expanded stack into `gDeckMenu`, runs a custom input loop (not `DeckMenuMainReadOnly`, which corrupts duel state on exit), saves/restores `gDeckMenu` around the session, and calls `UpdateAllDuelGfx()` after close. An empty graveyard plays `SFX_FORBIDDEN`.

## API

Public header: `include/expanded_graveyard.h`.

| Function | Purpose |
|----------|---------|
| `GraveyardExpand_IsEnabled()` | Returns whether `expand_graveyard` is on |
| `GraveyardExpand_Init()` | Clears both stacks (called on duel start) |
| `GraveyardExpand_PushFixed` / `PushTurn` | Send a card to graveyard |
| `GraveyardExpand_PopFixed` / `PopTurn` | Pop top card (LIFO) |
| `GraveyardExpand_GetCount` | Stack depth (0 or 1 when disabled) |
| `GraveyardExpand_GetCardAt` | Read card at index without removing |
| `GraveyardExpand_RemoveAtFixed` / `RemoveAtTurn` | Remove and return card at index |
| `GraveyardExpand_SyncLegacyTop` | Force legacy `graveyard` field to match stack top |

Vanilla pop entry points are replaced via LynJump:

- `GetGraveCardAndClearGrave` → `GraveyardExpand_PopTurn`
- `GetGraveCardAndClearGrave2` → `GraveyardExpand_PopFixed`

## EWRAM allocations

All symbols are declared in `asm/ram_map.s` via `_kernel_malloc_ewram_array`. Total cost when `expand_graveyard` is compiled in: **486 bytes** EWRAM (three 162-byte layers).

| Symbol | Size | Layer | Purpose |
|--------|------|-------|---------|
| `gExpandedGraveyard` | `0xA0` (2 × 40 `u16`) | Live | Authoritative graveyard stacks |
| `gExpandedGraveyardCount` | `0x2` (2 × `u8`) | Live | Per-duelist counts |
| `gAiSimSavedExpandedGraveyard` | `0xA0` | AI sim | Per-candidate snapshot before speculative play |
| `gAiSimSavedExpandedGraveyardCount` | `0x2` | AI sim | Counts for per-candidate snapshot |
| `gAiBatchCheckpointGraveyard` | `0xA0` | AI sim | Pre-batch snapshot for full candidate loop |
| `gAiBatchCheckpointGraveyardCount` | `0x2` | AI sim | Counts for pre-batch snapshot |

The live pair is always required when the feature is enabled. The two AI sim pairs exist because expanded graveyard state lives **outside** `gDuel`; vanilla duel save/restore (`sub_800EE24` / `sub_800EE94`) does not include it. See [AI simulation](#ai-simulation).

Allocations remain in EWRAM even when `expand_graveyard` is off at runtime; guards in code skip use.

## AI simulation

Opponent AI evaluates hundreds of speculative actions per decision. Each candidate temporarily mutates duel state, scores the result, then restores. Without extra bookkeeping, expanded graveyard cards could leak into the real duel (phantom cards in the GY viewer on turn 1).

Three mechanisms work together:

### 1. Mutation suppression

`AiSimSuppressesGraveyardMutations()` (`include/ai_sim.h`) returns true when `gAiSimInBatch || gHideEffectText`.

- **Push** checks this guard and returns without modifying the stack.
- **Pop** / **RemoveAt** check `gAiSimInBatch` only (not `gHideEffectText`).

`gAiSimInBatch` and `gHideEffectText` are set for the entire `AiSimulateAllCandidateActions` call in `src_custom/ai_hooks.c`.

### 2. Per-candidate save/restore

`sub_800EE24__Replacement` / `sub_800EE94__Replacement` in `src_custom/ai_simulation_hooks.c` extend vanilla duel snapshot save/restore:

| Step | Save (`sub_800EE24`) | Restore (`sub_800EE94`) |
|------|----------------------|-------------------------|
| Expanded stack | Copy live → `gAiSimSavedExpandedGraveyard` | Copy saved → live **before** assigning `gDuel` |
| Legacy field in snapshot | Sanitize from expanded top (not stale `gDuel` value) | `GraveyardExpand_SyncLegacyTop` after `gDuel` assign |

Used by the custom AI loop (`ai_hooks.c`), fast AI path (`ai_sim_fast.c`), and vanilla `ai.c` candidate loop.

### 3. Batch checkpoint

`AiSimBeginBatchGraveyardCheckpoint` / `AiSimEndBatchGraveyardCheckpoint` wrap `AiSimulateAllCandidateActions`:

```
Begin batch  → copy live GY → gAiBatchCheckpointGraveyard
  for each candidate:
    save → simulate → restore   (uses gAiSimSaved*)
End batch    → copy checkpoint → live GY, sync legacy top
```

This restores pre-batch graveyard state even if per-candidate restore order or legacy snapshot sanitization drifts during the loop.

### Duel lifecycle

On duel init (`code_803F02C_hooks.c`): `GraveyardExpand_Init()` then `AiSimClearSavedGraveyard()` (zeros both sim buffer pairs).

After each real AI action (`ai_main_hooks.c`): `GraveyardExpand_SyncLegacyTop` for both duelists keeps legacy field aligned post-execution.

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Core stack API | `src_custom/expanded_graveyard.c` | Push, pop, remove, legacy sync, LynJump pop replacements |
| Public API | `include/expanded_graveyard.h` | Capacity constant and function declarations |
| EWRAM symbols | `asm/ram_map.s` | All six graveyard-related allocations |
| Runtime toggle | `configs/runtime.c`, `configs/runtime.h` | `expand_graveyard` field |
| Duel init | `GraveyardExpand_Init` in `src_custom/code_803F02C_hooks.c` | Clear stacks; `AiSimClearSavedGraveyard` |
| Primary send hook | `ClearZoneAndSendMonToGraveyard` in `src_custom/card_passive_hooks.c` | Push on zone clear/send |
| GY viewer | `src_custom/duel_gy_viewer.c` | `Duel_GraveyardViewer_Open`, custom deck-menu loop |
| B-menu integration | `src_custom/duel_b_menu_hooks.c` | Top-card name tiles, navigation, viewer dispatch |
| B-menu input | `src_custom/duel_opponent_hand_scroll_hooks.c` | Opens viewer on `B_MENU_GY_*` |
| AI batch wrapper | `AiSimulateAllCandidateActions` in `src_custom/ai_hooks.c` | Sets sim flags; batch checkpoint begin/end |
| AI sim save/restore | `sub_800EE24__Replacement`, `sub_800EE94__Replacement` in `src_custom/ai_simulation_hooks.c` | Per-candidate expanded GY + duel snapshot |
| AI sim helpers | `include/ai_sim.h` | `AiSimSuppressesGraveyardMutations`, checkpoint API |
| Post-action sync | `AI_Main` replacement in `src_custom/ai_main_hooks.c` | `SyncLegacyTop` after real AI plays |
| Indexed GY effects | `src_custom/permanent_effects/dark_magician_of_chaos.c` | `GetCount`, `GetCardAt`, `RemoveAtTurn` |
| Direct push sites | `robbin_zombie.c`, `ojama_trio.c`, `embodiment_of_apophis_hooks.c`, `magical_merchant.c`, `guardian_treasure.c` | Card-specific send paths |

## TODO

- Monster Reborn (and similar) combined graveyard picker when multiple monsters are in the stack.
- Evaluate merging `gAiSimSaved*` and `gAiBatchCheckpoint*` into one buffer (~162 bytes EWRAM savings) if per-candidate restore can always read the batch checkpoint.
- Host tests for push/pop/remove, overflow drop-oldest, and legacy top sync.

## Limitations & Bugs

- Graveyard state is **not persisted** in save data; it resets each duel.
- Overflow drops the oldest card silently at 40 cards — matches deck size but differs from official rules for mill-heavy decks.
- Pop/remove during AI sim only guard on `gAiSimInBatch`, not `gHideEffectText`; push guards on both. Asymmetric by design but worth noting when adding new GY mutation paths.
- Code that writes `gDuel.duelistbattleState[].graveyard` directly bypasses the expanded stack; prefer `GraveyardExpand_Push*` or the `ClearZoneAndSend*` hooks.
- EWRAM is reserved for all six symbols at link time regardless of runtime toggle.
- Phantom GY cards from AI sim were addressed in session logs 2026-06-28/29; report regressions with `fast_ai` + `expand_graveyard` and a save state if they reappear.
