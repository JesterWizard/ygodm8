# Duelist Reward Manifest

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

This system moves duel reward tuning out of the vanilla duelist data table and into `tools/duelist_reward_manifest.json`.

The player-facing goal is to make per-opponent rewards easy to change without hunting raw `DUEL(n)` values through event scripts. Each duel opponent now has a named `DUELIST_*` constant, and both event scripts and reward data refer to the same enum name.

The current manifest controls:

1. deck capacity gained after victory
2. domino reward min/max and scale
3. normal ante card drops
4. low ante card drops

## Plan

The feature flow is:

| Stage | Location | Result |
|--------|----------|--------|
| Duelist identity | `enum DuelistId` | Gives every vanilla opponent ID a named `DUELIST_*` constant |
| Event script use | `DUEL(DUELIST_...)` | Starts duels with named constants instead of raw numbers |
| Manifest data | `tools/duelist_reward_manifest.json` | Stores per-duelist reward values keyed by `DUELIST_*` |
| Generation | `tools/generate_duelist_rewards.py` | Resolves enum names and emits `src_custom/generated/duelist_rewards_generated.inc` |
| Runtime lookup | `HandleWin__Replacement`, `sub_801FFE0__Replacement`, `AddMoneyFromDuelVictory__Replacement` | Applies manifest rewards when a duel ends |

Behavior summary:

| Runtime config | Capacity source | Card/drop source |
|--------|-----------------|------------------|
| `repeatable_opponent_capacity_reward == 0` and `story_opponent_capacity_reward == 0` | Manifest `capacity_reward` | Manifest drop lists |
| Either global capacity config is nonzero | Global repeatable/story fallback for vanilla reward classes | Vanilla/custom-deck fallback as applicable |
| Custom deck shop duel pending | Custom deck reward entry | Custom deck reward entry |

Implementation notes:

1. `duelist_id` values in the JSON should be enum names from `enum DuelistId`, not raw numbers.
2. Every enum name is prefixed with `DUELIST_` so it is easy to find from scripts and generated reward output.
3. `tools/vanilla_events.py` already loads constants from `include/overworld.h`, so `DUEL(DUELIST_...)` compiles to the same bytecode as the old numeric call.
4. `tools/generate_duelist_rewards.py` also reads `include/overworld.h` and validates each manifest enum name before generating C data.
5. Some characters have multiple duel IDs. Tristan, for example, appears as several separate duel IDs for normal and story/robot encounters.

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Duelist ID enum | `enum DuelistId` in `include/overworld.h` | Defines the shared names used by event scripts and reward data |
| Duel event calls | `DUEL(DUELIST_...)` in `events/scripts/map_*_state_*.c` | Starts overworld duels using named opponent IDs |
| Reward manifest | `tools/duelist_reward_manifest.json` | Authoritative editable reward table for capacity, domino, and ante rewards |
| Reward generator | `load_duelist_ids`, `resolve_duelist_id`, and `main` in `tools/generate_duelist_rewards.py` | Resolves enum names and emits generated C reward tables |
| Generated reward table | `src_custom/generated/duelist_rewards_generated.inc` | Build output consumed by the reward hook |
| Win reward hook | `HandleWin__Replacement` in `src_custom/code_801EF30_hooks.c` | Selects the configured capacity reward and displays the victory text |
| Card reward hook | `sub_801FFE0__Replacement` in `src_custom/code_801EF30_hooks.c` | Selects normal or low ante rewards from the manifest |
| Domino reward hook | `AddMoneyFromDuelVictory__Replacement` in `src_custom/code_801EF30_hooks.c` | Selects manifest domino min/max and scale values |
| Build integration | `DUELIST_REWARD_MANIFEST`, `DUELIST_REWARD_GENERATOR`, and `DUELIST_REWARDS_GENERATED` in `Makefile` | Regenerates reward data when the manifest or generator changes |

## TODO

- Replace remaining generic names like `DUELIST_ID_003` with clearer names as each opponent is identified.
- Add a small validation report that lists event-script duel IDs not referenced by the manifest.
- Consider adding comments or aliases for characters with multiple duel IDs.

## Limitations & Bugs

- The enum currently preserves all known IDs from `0` through `163`; names are only as descriptive as the current event-script context allows.
- A character can legitimately have more than one duelist ID, so changing one reward may not affect every encounter for that character.
- The manifest is used only when the runtime global repeatable/story capacity rewards are both `0`.
- `src_custom/generated/duelist_rewards_generated.inc` is generated output. Edit the manifest or enum instead of hand-editing the generated file.
