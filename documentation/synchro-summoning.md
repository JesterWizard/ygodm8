# Synchro Summoning

---

## Index

- [Introduction](#introduction)
- [Plan](#plan)
- [Player flow](#player-flow)
- [Tuner flag](#tuner-flag)
- [API](#api)
- [Code Locations](#code-locations)
- [TODO](#todo)
- [Limitations & Bugs](#limitations--bugs)

## Introduction

The Extra Deck already stores Synchro monsters (`COLOR_SYNCHRO` / `SYNCHRO_CARD`) and shows white frames, but there was no in-duel Synchro Summon procedure. Fusion uses Polymerization + fixed recipes; Synchro needs a different model: face-up field materials whose levels sum to the Extra Deck target’s level, with exactly one Tuner.

This feature adds a minimal playable Synchro path, first exercised with Stardust Dragon (Level 8). Stardust’s negate/destroy protection effect remains stubbed.

## Plan

### Rules (v1, TCG-lite)

| Rule | Behavior |
|------|----------|
| Materials | Face-up monsters on the **active** monster row only (ATK counts as face-up before EOT `FlipAtkPosCardsFaceUp`; face-down sets do not) |
| Composition | Exactly **1 Tuner** + **1 or more non-Tuners** |
| Levels | Sum of material levels equals the Synchro’s `level` |
| Result | Must be `COLOR_SYNCHRO` and present in the active Extra Deck |
| Extra Deck | Whitelist only (same as Fusion); copy is **not** consumed |
| Restrictions | No attribute/type Tuning limits; no AI Synchro yet |

### Recipe model

**Level-sum engine**, not Fusion-style fixed card-ID recipes. Feasibility is computed from the current field + Extra Deck contents each time the player opens Synchro.

### Entry point

Fifth monster-menu action (**Synchro**), left column under Defend. Drawn when `SynchroDuel_PlayerCanSummon()` — any legal level-sum Synchro exists (openable from tuner or non-tuner). LynJump of `HandlePlayerMonsterAction`.

## Player flow

| Step | What happens |
|------|----------------|
| A on own face-up monster | Monster menu (Attack / Defend / Tribute / Effect / Synchro) |
| Synchro | If `SynchroDuel_PlayerCanSummon()`, open Extra Deck Synchro pick list |
| Pick + confirm | Deck-menu list of feasible Synchros; confirm **Synchro Summon** |
| Pay | Auto-selected materials sent to GY |
| Summon | Result Special Summoned face-up ATK via `Duel_SpecialSummonMonsterId` |

Toggle: when `enable_extra_deck` is off, Synchro acts as forbidden.

## Tuner flag

Tuners are tagged in the card manifest (`"is_tuner": true`), not by expanding `CardData`. The card-data generator emits parallel `gCardIsTuner_Hook[]` (same pattern as `gCardSelectableOnce_Hook`). Runtime check: `Card_IsTuner(cardId)`.

`add_custom_card.py` sets `is_tuner` when the YGOProDeck / API type string contains `"Tuner"`.

## API

Public header: `include/synchro_duel.h`.

| Function | Purpose |
|----------|---------|
| `Card_IsTuner` | Manifest-driven Tuner check |
| `SynchroDuel_CollectFaceUpFieldSources` | Active row, face-up monsters |
| `SynchroDuel_BuildFeasibleExtraDeckTargets` | Extra Deck Synchros with a valid level-sum subset |
| `SynchroDuel_PlayerPickTarget` | Deck-menu pick + Synchro Summon confirm |
| `SynchroDuel_SelectMaterialsForLevel` | Auto-pick 1 Tuner + non-Tuners totaling `level` |
| `SynchroDuel_Execute` | Pay materials, Special Summon result |
| `SynchroDuel_PlayerCanSummon` | Menu enable gate |
| `SynchroDuel_RunPlayerFlow` | Full player Synchro path from the menu |

## Code Locations

| Feature | Location | Description |
|---------|----------|-------------|
| Core Synchro API | `SynchroDuel_*` in `src_custom/synchro_duel.c` | Collect, match, pick, execute |
| Public API | `include/synchro_duel.h` | Declarations and source struct |
| Tuner hook table | `gCardIsTuner_Hook` in `src_custom/generated/card_data_hooks.c` | Generated from manifest |
| Generator | `tools/add_card_art.py` | Emits `gCardIsTuner_Hook` |
| New-card Tuner detect | `tools/add_custom_card.py` | Sets `is_tuner` from API type |
| Monster menu | `HandlePlayerMonsterAction__Replacement` in `src_custom/monster_action_menu_hooks.c` | 5th Synchro action |
| Menu dispatch | `MonsterActionMenu__Replacement` in `src_custom/monster_effect_hooks.c` | `case 6` → `SynchroDuel_RunPlayerFlow` |
| LynJump | `src_custom/LynJump.event` | Patches `HandlePlayerMonsterAction` |
| Extra Deck whitelist | `trunk_hooks.c` / Extra Deck arrays | Same gate as Fusion |
| Stardust effect stub | `src_custom/activated_effects/stardust_dragon.c` | Negate not implemented |

## TODO

- Stardust Dragon negate / tribute-to-negate destroy protection.
- AI Synchro Summon candidates and scoring.
- Non-standard material wording (2+ Tuners, named materials, “except Tokens”, etc.).
- Consume Extra Deck copies on summon / return on leave field.
- Mechanics tutorial entry once the flow is stable.
- Manual material zone picking when multiple subsets are legal.

## Limitations & Bugs

- Materials must be face-up for Synchro purposes: `isFaceUp || !isDefending` (same as Court of Justice / Riryoku). Face-down Defense sets cannot be used.
- Only the active duelist’s monster row is scanned (no opponent materials).
- Auto material selection may pick a different valid subset than the player intended when several exist.
- Extra Deck is a whitelist, not a depleting pile — summoning Stardust does not remove it from the Extra Deck.
- Synchro menu layout is a custom 5-option overlay; localization strings beyond English may need width tweaks.
- No AI path in v1.
