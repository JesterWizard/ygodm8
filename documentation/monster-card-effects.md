# Monster Card Effects

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

Monster card effects in this repo are split into two layers:

1. central hook entrypoints that stay small and handle dispatch
2. one card-specific source file per custom effect under `src/hooks/permanent_effects` or `src/hooks/activated_effects`

The goal is to keep new card work readable. Adding a new custom card effect should mostly mean creating one new file and one new dispatch entry, not editing a large mixed logic file.

## Plan

Use this layout when adding monster card effects:

| Effect kind | Folder | When to use |
|--------|----------|-------------|
| Permanent board effect | `src/hooks/permanent_effects/` | The card changes stages or board state during the permanent-effect scan |
| Activated monster effect | `src/hooks/activated_effects/` | The card effect is triggered from the monster action menu or normal monster-effect flow |

Quick edit path:

- Activated monster effects: `include/constants/monster_effects.h`, `tools/card_data_manifest.json`, `src/hooks/monster_effect_hooks.c`, `src/hooks/activated_effects/<card_name>.c`
- Permanent effects: `src/hooks/permanent_effect_hooks.c`, `src/hooks/permanent_effects/<card_name>.c`
- End-of-turn cleanup or delayed destruction: `src/hooks/turn_effect_hooks.c`

Authoring flow:

1. Decide whether the card belongs in the permanent scan or the normal monster activation path.
2. Create one new `.c` file named after the card in the matching folder.
3. Put the card-specific logic in that file.
4. For activated monster effects, add or reuse a `MONSTER_EFFECT_*` entry in `include/constants/monster_effects.h`.
5. Point the card's `monsterEffect` field in `tools/card_data_manifest.json` at that enum constant.
6. Add only the minimal declarations and dispatch wiring in the central hook file.
7. Build with `make` and verify the effect path still works in duel flow.

Recommended file naming:

- `src/hooks/permanent_effects/<card_name>.c`
- `src/hooks/activated_effects/<card_name>.c`

Recommended function naming:

- Permanent effects:
  - `unsigned char ShouldActivate<CardName>(void);`
  - `void Activate<CardName>(void);`
- Normal effects:
  - `unsigned char CanActivate<CardName>(void);`
  - `void Activate<CardName>Effect(void);`

## Code Locations

| Feature | Location | Description |
|--------|----------|-------------|
| Permanent-effect dispatch | `TryActivatingPermanentEffect__Hook` in `src/hooks/permanent_effect_hooks.c` | Chooses between custom permanent overrides and vanilla permanent effect handlers |
| Permanent-effect override table | `sPermanentEffectOverrides` in `src/hooks/permanent_effect_hooks.c` | Maps a card ID to card-specific permanent-effect functions |
| Permanent card example | `ShouldActivateMilusRadiant` and `ActivateMilusRadiant` in `src/hooks/permanent_effects/milus_radiant.c` | Example custom permanent effect file with one card per file |
| Normal-effect dispatch | `ActivateMonsterEffect__Replacement` in `src/hooks/monster_effect_hooks.c` | Runs custom activated monster effects before falling back to the vanilla monster-effect table |
| Normal-effect action gate | `MonsterActionMenu__Replacement` in `src/hooks/monster_effect_hooks.c` | Blocks or allows activation from the duel UI before calling the custom effect |
| Normal card example | `CanActivateInjectionFairyLily` and `ActivateInjectionFairyLilyEffect` in `src/hooks/activated_effects/injection_fairy_lily.c` | Example custom activated monster effect file with one card per file |
| Activated-effect enum source | `MONSTER_EFFECT_*` entries in `include/constants/monster_effects.h` | Symbolic values used by the manifest and the activated-effect dispatcher |
| Activated-effect manifest wiring | `monsterEffect` fields in `tools/card_data_manifest.json` | Names the enum constant for cards that need custom activated monster behavior |
| Custom description overrides | `sCardDescriptionOverrides` in `src/hooks/card_hooks.c` | Optional custom card text overrides when the vanilla description no longer matches behavior |
| Hook jump wiring | `src/hooks/LynJump.event` | Maps vanilla engine entrypoints to hook-side replacement functions |

## TODO

- Add a shared helper file if many normal effects start reusing the same stat, LP, or popup routines.
- Add a second normal-effect example that does not use a manual activation gate.
- Add a second permanent-effect example that affects types instead of attributes.
- Add a short manifest example for an activated monster effect that uses a symbolic `monsterEffect` entry.

## Limitations & Bugs

- Hook-side static data may need to live in a kept section if the linker discards normal `.rodata` for hook objects.
- Some cards may still need central hook edits if the vanilla flow does not expose a clean dispatch point yet.
- The current normal-effect path is not fully table-driven. New custom normal effects still require a small amount of central wiring in `src/hooks/monster_effect_hooks.c`.
- Activated monster effects rely on the manifest, enum header, and dispatcher staying in sync. If the enum changes, regenerate the manifest-driven card data.
