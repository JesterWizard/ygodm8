# Persistent Card Cost Randomizer

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

This feature randomizes card costs at startup when `gRuntimeConfig.randomize_card_costs_at_start` is enabled.

The original problem was simple: a purely RAM-based random seed is lost when the game is powered off, so the same save would rebuild with different costs or fall back to zeroed values on the next session.

The current design fixes that by splitting the system into three parts:

1. a live entropy accumulator that changes while the title screen is active
2. a persistent seed record stored through the game's existing save/write path
3. a rebuilt cost table in IWRAM at `0x03001678`, one `u16` per card ID

The goal is repeatable randomness per save file, not a one-time boot randomizer.

## Plan

The feature flow is:

| Stage | Location | Result |
|--------|----------|--------|
| Menu entropy | `LfsrNextByte__Replacement` | Mixes timing state, input state, and RNG output into a live EWRAM entropy value while the title/menu is running |
| New game setup | `sub_800AF68__Replacement` | Calls the normal new-game flow and then rebuilds the randomized cost table from the persistent seed |
| Save/load persistence | `GetPersistentCostSeed`, `WriteStoredCostSeedToFlash`, `ReadStoredCostSeedFromFlash` | Stores the seed in a persisted record and rehydrates it on later sessions |
| Save restore | `sub_803519C__Replacement` | Restores save data and then regenerates the cost table from the persistent seed |
| Runtime lookup | `SetCardInfo__Replacement` | Reads the randomized cost table when the config flag is enabled |

Behavior summary:

| Config | Seed source | Cost generation | Result |
|--------|-------------|-----------------|--------|
| `FALSE` | None | Original ROM cost table | Vanilla behavior |
| `TRUE` and existing seed found | EWRAM cache, then persisted record | Deterministic rebuild from saved seed | Same costs across sessions for that save |
| `TRUE` and no existing seed | Live entropy accumulator | New persistent seed is created and stored | New randomized cost set for the save |

Implementation notes:

1. The live entropy cache lives in an EWRAM gap at `0x02020E06`.
2. The persistent seed is written through the game’s existing save/write machinery using the available save buffer path.
3. The cost table itself is stored in IWRAM starting at `0x03001678`.
4. Costs are generated independently with a `0..500` inclusive range and are not derived from the vanilla card-cost table.
5. `CARD_NONE` stays `0`.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Card cost lookup override | `SetCardInfo__Replacement` in `src_custom/card_hooks.c` | Replaces the vanilla cost read with the randomized table when the config toggle is on |
| Cost table build | `InitializeRandomizedCardCosts` in `src_custom/card_hooks.c` | Fills the IWRAM cost table from the persistent seed |
| Persistent seed read/write | `ReadStoredCostSeed`, `WriteStoredCostSeed`, `ReadStoredCostSeedFromFlash`, `WriteStoredCostSeedToFlash` in `src_custom/card_hooks.c` | Handles the seed record and the persisted mirror |
| Live entropy mixing | `LfsrNextByte__Replacement` in `src_custom/card_hooks.c` | Keeps the runtime entropy value changing while menus are active |
| Save restore hook | `sub_803519C__Replacement` in `src_custom/card_hooks.c` | Restores save state, then rebuilds the randomized cost table |
| New-game hook | `sub_800AF68__Replacement` in `src_custom/new_game_randomizer_hooks.c` | Ensures a fresh new-game start also rebuilds the table |
| Hook jump wiring | `src_custom/LynJump.event` | Redirects the vanilla entry points into the replacement functions |
| Runtime config toggle | `gRuntimeConfig.randomize_card_costs_at_start` in `configs/runtime.h` and `configs/runtime.c` | Enables or disables the feature |

## TODO

- Add a short debug helper that prints the active persistent seed during development builds.
- Consider moving the persisted record constants into a small shared header if more save-backed randomizers are added.
- Add a test note for verifying that two sessions with the same save produce identical card costs.

## Limitations & Bugs

- The feature depends on the game’s existing save/write flow; if that flow is bypassed, the persistent seed will not be updated.
- The EWRAM entropy cache is only runtime state. It helps generate the first persistent seed, but it does not survive power-off by itself.
- The randomized table covers the known card IDs in the current build. Any future expansion of the card list needs the table bounds revisited.
- If the save data is erased, the next boot will generate a new seed and therefore a new cost set.
