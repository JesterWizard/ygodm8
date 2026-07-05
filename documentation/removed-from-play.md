# Removed From Play Zone

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Runtime toggle](#runtime-toggle)
- [Player access](#player-access)
- [API](#api)
- [EWRAM allocations](#ewram-allocations)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Vanilla duel code has no persistent banished / removed-from-play storage. `Duel_BanishZone` clears the zone and the card is gone — enough for effects that only need to exile a card, but not for custom cards that count banished cards, return them to hand or deck, or let the player inspect what left the game (for example Elemental HERO The Shining, Voltic, Electrum).

When `enable_removed_from_play_zone` is enabled, each fixed duelist (`DUEL_PLAYER`, `DUEL_OPPONENT`) gets a 40-card FIFO-style list in EWRAM (oldest dropped at capacity). Cards reach the list through `Duel_BanishZone` (field/hand exile) or the graveyard banish helpers in `duel_helpers.c`.

## Plan

### Storage model

| Storage | Type | Role |
|---------|------|------|
| `gRemovedFromPlay[duelist][index]` | `u16` list | Banished card IDs, `CARD_NONE`-terminated |
| Index 0 | Bottom | First card banished this duel |
| Index `count - 1` | Top | Most recently banished card |

Capacity is `REMOVED_FROM_PLAY_CAPACITY` (40), matching deck size. On overflow the oldest entry is shifted out before push.

### Write paths

| Path | Function |
|------|----------|
| Field / hand / backrow banish | `Duel_BanishZone` → `RemovedFromPlay_PushZone` |
| Graveyard banish by index | `Duel_BanishGraveyardAtFixed` / `Duel_BanishGraveyardAtTurn` |
| Graveyard banish top card | `Duel_BanishGraveyardTopTurn` (Book of Life) |

Zone ownership for field banish is derived from fixed row (`OPPONENT_*` → opponent, `PLAYER_*` → player) or turn hand row when the zone is a hand slot.

## Runtime toggle

| Field | Location | Default |
|-------|----------|---------|
| `enable_removed_from_play_zone` | `configs/runtime.c` → `gRuntimeConfig.enable_removed_from_play_zone` | **on** (`TRUE`) |

When off: banish calls still clear zones / graveyard as before, but nothing is recorded and L/R open nothing (L falls back to the ATK/DEF stat screen; R falls back to vanilla opponent-hand peek / scroll behavior).

## Player access

| Input | Action |
|-------|--------|
| **L** (during player turn main loop) | Open player removed-from-play viewer |
| **R** (during player turn main loop) | Open opponent removed-from-play viewer |
| **Up** / **Down** | Scroll card list |
| **A** | Full card detail view; **B** returns to list |
| **B** | Close viewer and return to duel |

Empty zones play `SFX_FORBIDDEN`, same as the graveyard viewer.

When the toggle is on, L/R replace the vanilla L stat overlay and R opponent-hand peek for the duration of the duel turn loop.

## API

Public header: `include/removed_from_play.h`.

| Function | Purpose |
|----------|---------|
| `RemovedFromPlay_IsEnabled()` | Returns whether `enable_removed_from_play_zone` is on |
| `RemovedFromPlay_Init()` | Clears both lists (duel start) |
| `RemovedFromPlay_PushFixed` | Record a banished card for a fixed duelist |
| `RemovedFromPlay_PushZone` | Resolve zone owner and push |
| `RemovedFromPlay_GetCount` | Number of banished cards |
| `RemovedFromPlay_GetCardAt` | Read card at index without removing |
| `Duel_RemovedFromPlayViewer_Open` | Scrollable read-only list UI |

Graveyard banish helpers live in `include/duel_helpers.h`:

| Function | Purpose |
|----------|---------|
| `Duel_BanishGraveyardAtFixed` | Remove GY card at index → RFP |
| `Duel_BanishGraveyardAtTurn` | Same, turn duelist index |
| `Duel_BanishGraveyardTopTurn` | Banish top graveyard card → RFP |

## EWRAM allocations

Declared in `asm/ram_map_ewram.s` via `_kernel_malloc_ewram_array`. Total: **160 bytes** (`0xA0`).

| Symbol | Size | Purpose |
|--------|------|---------|
| `gRemovedFromPlay` | `0xA0` (2 × 40 `u16`) | Both duelists' banished lists |

Allocation is always linked; runtime toggle gates reads and writes.

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Core list API | `src_custom/removed_from_play.c` | Push, count, indexed read, init |
| Public API | `include/removed_from_play.h` | Capacity constant and declarations |
| EWRAM symbol | `asm/ram_map_ewram.s` | `gRemovedFromPlay` |
| Runtime toggle | `configs/runtime.c`, `configs/runtime.h` | `enable_removed_from_play_zone` |
| Duel init | `InitBoard__Replacement` in `src_custom/code_803F02C_hooks.c` | `RemovedFromPlay_Init` |
| Field banish hook | `Duel_BanishZone` in `src_custom/duel_helpers.c` | Push before `ClearZone` |
| GY banish helpers | `src_custom/duel_helpers.c` | `Duel_BanishGraveyardAt*` |
| L/R viewer dispatch | `PlayerTurnMain__Replacement` in `src_custom/code_803F02C_hooks.c` | L = player, R = opponent |
| List viewer UI | `src_custom/duel_gy_viewer.c` | Shared deck-menu loop for GY and RFP |
| Card effect call sites | `angels_tear.c`, `chaos_emperor_dragon_envoy_of_the_end.c`, `black_luster_soldier_envoy_of_the_beginning.c`, `book_of_life.c`, `fusion_duel.c` | Graveyard / material banish |
| Host wiring test | `tests/host/test_removed_from_play.py` | RAM size, init, L/R hooks |

## TODO

- Wire deferred custom effects that reference banished zones (E-HERO Shining, Flash, Voltic, Electrum).
- Optional B-menu rows for removed-from-play (mirror expanded graveyard).
- Host tests for push overflow, zone-owner mapping, and viewer empty-state.

## Limitations & Bugs

- Removed-from-play state is **not persisted** in save data; it resets each duel.
- Overflow drops the oldest banished card silently at 40 entries.
- No AI simulation save/restore — banish during AI sim is rare; sim paths that banish do not snapshot RFP (acceptable until banish-counting AI effects exist).
- When enabled, L no longer opens the vanilla ATK/DEF stat overlay and R no longer opens the vanilla opponent-hand peek unless the toggle is turned off.
- Cards banished before this feature was added are not retroactively tracked.
