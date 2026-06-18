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
2. one card-specific source file per custom effect under `src_custom/permanent_effects` or `src_custom/activated_effects`

The goal is to keep new card work readable. Adding a new custom card effect should mostly mean creating one new file and one new dispatch entry, not editing a large mixed logic file.

## Plan

Use this layout when adding monster card effects:

| Effect kind | Folder | When to use |
|--------|----------|-------------|
| Permanent board effect | `src_custom/permanent_effects/` | The card changes stages or board state during the permanent-effect scan |
| Activated monster effect | `src_custom/activated_effects/` | The card effect is triggered from the monster action menu or normal monster-effect flow |

Quick edit path:

- Activated monster effects: `include/constants/monster_effects.h`, `tools/card_data_manifest.json`, `src_custom/monster_effect_hooks.c`, `src_custom/activated_effects/<card_name>.c`
- Permanent effects: `src_custom/permanent_effect_hooks.c`, `src_custom/permanent_effects/<card_name>.c`
- End-of-turn cleanup or delayed destruction: `src_custom/turn_effect_hooks.c`

Authoring flow:

1. Decide whether the card belongs in the permanent scan or the normal monster activation path.
2. Create one new `.c` file named after the card in the matching folder.
3. Put the card-specific logic in that file.
4. For activated monster effects, add or reuse a `MONSTER_EFFECT_*` entry in `include/constants/monster_effects.h`.
5. Point the card's `monsterEffect` field in `tools/card_data_manifest.json` at that enum constant.
6. Add only the minimal declarations and dispatch wiring in the central hook file.
7. Build with `make` and verify the effect path still works in duel flow.

Recommended file naming:

- `src_custom/permanent_effects/<card_name>.c`
- `src_custom/activated_effects/<card_name>.c`

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
| Shared duel actions | `include/duel_helpers.h`, `src_custom/duel_helpers.c` | Draw, destroy, discard, LP, summon, deck search, effect text, spell-through-traps |
| Permanent-effect dispatch | `TryActivatingPermanentEffect__Hook` in `src_custom/permanent_effect_hooks.c` | Chooses between custom permanent overrides and vanilla permanent effect handlers |
| Permanent-effect override table | `sPermanentEffectOverrides` in `src_custom/permanent_effect_hooks.c` | Maps a card ID to card-specific permanent-effect functions |
| Permanent card example | `ShouldActivateMilusRadiant` and `ActivateMilusRadiant` in `src_custom/permanent_effects/milus_radiant.c` | Example custom permanent effect file with one card per file |
| Normal-effect dispatch | `ActivateMonsterEffect__Replacement` in `src_custom/monster_effect_hooks.c` | Runs custom activated monster effects before falling back to the vanilla monster-effect table |
| Normal-effect action menu | `MonsterActionMenu__Replacement` in `src_custom/monster_effect_hooks.c` | Blocks or allows activation from the duel UI before calling the custom effect |
| Normal card example | `CanActivateInjectionFairyLily` and `ActivateInjectionFairyLilyEffect` in `src_custom/activated_effects/injection_fairy_lily.c` | Example custom activated monster effect file with one card per file |
| Activated-effect enum source | `MONSTER_EFFECT_*` entries in `include/constants/monster_effects.h` | Symbolic values used by the manifest and the activated-effect dispatcher |
| Activated-effect manifest wiring | `monsterEffect` fields in `tools/card_data_manifest.json` | Names the enum constant for cards that need custom activated monster behavior |
| Custom description overrides | `sCardDescriptionOverrides` in `src_custom/card_hooks.c` | Optional custom card text overrides when the vanilla description no longer matches behavior |
| Hook jump wiring | `src_custom/LynJump.event` | Maps vanilla engine entrypoints to hook-side replacement functions |

### Duel helpers cheat sheet (new cards)

Use `duel_helpers.h` for common actions instead of copying static helpers into each card file. Duelist args use `ACTIVE_DUELIST` / `INACTIVE_DUELIST`. Pass `updateGfx=TRUE` when the caller wants `UpdateDuelGfxExceptField()` after the action.

| Verb | Function |
|------|----------|
| Count hand | `Duel_CountCardsInHand(handRow)` |
| Draw | `Duel_DrawCards(duelist, count, updateGfx)` |
| Mill deck | `Duel_MillTopDeckCards(duelist, count, updateGfx)` |
| Destroy zone | `Duel_DestroyZone(zone, graveyardDuelist, updateGfx)` |
| Banish zone | `Duel_BanishZone(zone, updateGfx)` — `ClearZone` without graveyard |
| Destroy row | `Duel_DestroyAllMonstersMatching(turnRow, pred, updateGfx)` |
| Discard | `Duel_DiscardFromHand(duelist, count, pred, updateGfx)` |
| Discard random | `Duel_DiscardRandomFromHand(duelist, count, updateGfx)` |
| Discard all hand | `Duel_DestroyAllHandCards(duelist, updateGfx)` |
| LP change | `Duel_ChangeLp(targetDuelist, delta, updateGfx)` — positive gain, negative burn |
| Effect text | `Duel_ShowEffectText(cardId)` |
| Typed effect text | `Duel_ShowEffectTextTyped(cardId, textType)` |
| Spell vs traps | `Duel_TryResolveSpellThroughTraps(spellId, resolveBody)` |
| Spell vs traps (LP hint) | `Duel_TryResolveSpellThroughTrapsEx(spellId, trapLp, resolveBody)` |
| Find in deck | `Duel_FindDeckCardIndex(duelist, cardId)` |
| Remove from deck | `Duel_RemoveDeckCardAt(duelist, index, updateGfx)` |
| Shuffle deck | `Duel_ShuffleDeckFromDrawn(duelist)` |
| Special summon | `Duel_SpecialSummonFromHand/Grave/Deck/HandZone/MonsterId(...)` with `Duel_DefaultSpecialSummonOpts(updateGfx)` |
| Locked special summon | set `opts.lockMonster = TRUE` on `DuelSummonOpts` |
| Normal summon | `Duel_NormalSummonFromHand(duelist, cardId, pred, Duel_DefaultNormalSummonOpts(updateGfx))` |
| Return to hand | `Duel_ReturnMonsterZoneToOwnerHand(zone, updateGfx)` |

All custom card effect files under `src_custom/*_effects/` use these helpers for shared duel actions. Keep vanilla calls only for card-specific logic (equip wiring, battle-context LP, custom deck/hand UI, flip position).

Example spell body:

```c
Duel_ShowEffectText(MY_SPELL);
if (Duel_TryResolveSpellThroughTrapsEx(MY_SPELL, 200, MySpell_ResolveBody) == DUEL_ACTION_BLOCKED)
  return;
if (Duel_DrawCards(ACTIVE_DUELIST, 2, TRUE) == DUEL_ACTION_DUEL_OVER)
  return;
Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, TRUE);
```

## TODO

- Add a second normal-effect example that does not use a manual activation gate.
- Add a second permanent-effect example that affects types instead of attributes.
- Add a short manifest example for an activated monster effect that uses a symbolic `monsterEffect` entry.
## Limitations & Bugs

- Hook-side static data may need to live in a kept section if the linker discards normal `.rodata` for hook objects.
- Some cards may still need central hook edits if the vanilla flow does not expose a clean dispatch point yet.
- The current normal-effect path is not fully table-driven. New custom normal effects still require a small amount of central wiring in `src_custom/monster_effect_hooks.c`.
- Activated monster effects rely on the manifest, enum header, and dispatcher staying in sync. If the enum changes, regenerate the manifest-driven card data.
