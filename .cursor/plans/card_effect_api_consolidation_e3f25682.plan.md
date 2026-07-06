---
name: Card effect API consolidation
overview: Extract shared APIs from 8 categories of duplicated card-effect code across ~200 files, and migrate legacy patterns to the new APIs. Create a migration tool for the PickZone targeting transition.
todos:
  - id: p7-adopt-existing-apis
    content: P7 — Adopt Duel_DrawCardsUntilHandSize and Duel_DiscardRandomFromHand in callers
    status: completed
  - id: p8-burn-spell-adoption
    content: P8 — Convert sparks.c and hinotama.c to Duel_ResolveBurnSpell
    status: completed
  - id: p6-equip-boost-helper
    content: P6 — Extract Duel_ResolveEquipStatBoost for United We Stand / Mage Power
    status: completed
  - id: p5-destroy-mask-lifecycle
    content: P5 — Extract Duel_InitDestroyMaskState / Mark / Resolve for Triangle Power / Thousand Energy / Limiter Removal
    status: completed
  - id: p4-flip-effect-unification
    content: P4 — Extract Duel_ActivateFlipEffect for Giant Germ / Skull Mark Lady Bug / Nimble Momonga
    status: cancelled
  - id: p3-turn-effect-boilerplate
    content: P3 — Extract Duel_ShouldActivateSimpleTurnEffect for 7 turn effect files
    status: completed
  - id: p2-trap-boilerplate
    content: P2 — Extract Duel_ActivateContinuousTrapZone and Duel_TryActivateBackrowTrapOnTurnStart for ~8 trap files
    status: completed
  - id: p1-deckmenu-macro
    content: P1 — Add DECKMENU_SAVE/RESTORE macros and migrate 18 call sites
    status: completed
  - id: p0-pickzone-migration
    content: P0 — Create migration tool + batch-migrate ~33 legacy cards to PickZone
    status: completed
isProject: false
---

# Card Effect API Consolidation Plan

## Categories (from most to least impactful)

### P0 — Migration tool for PickZone targeting (~33 cards)
- **Files**: `tools/` (new Python script), ~33 card effect files + `code_8043EF4_hooks.c` (both dispatch cases)
- **What**: Legacy cards use per-card `DUEL_CURSOR_*` constants (defined in per-card headers), `BeginXxxTargeting()`, `TrySelectXxxTarget()`, `CancelXxxTargeting()`, plus 2 switch-case entries in `code_8043EF4_hooks.c` (A-button and B-button dispatch). PickZone system (`Duel_SetupPickZone` + `Duel_EnterPickZoneTargeting`) already exists and 7 cards are migrated.
- **Approach**: Write a Python script (`tools/migrate_to_pickzone.py`) that reads the AI picker + validator from the legacy card, generates the 4-callback PickZone template (`IsValidTarget`, `ResolveTarget`, `CancelTargeting`, `AiPickTarget`), and removes the per-card header + cursor constant + HookA/HookB cases. Run the tool per-card, verify each individually.
- **Savings**: ~15-20 LOC per card file + 2 cases per card from hooks file

### P1 — `gDeckMenu` save/restore macro (~18 files)
- **Files**: `include/duel_helpers.h` (macro) + all files with `sizeof(gDeckMenu)` byte-copy loops
- **What**: The 4-8 line `for(i=0;i<sizeof(gDeckMenu);i++)` save/restore byte-copy pattern appears 18 times. No two callers differ.
- **Approach**: Add macros:
  ```c
  #define DECKMENU_SAVE(buf) CpuCopy32(&gDeckMenu, buf, sizeof(gDeckMenu))
  #define DECKMENU_RESTORE(buf) CpuCopy32(buf, &gDeckMenu, sizeof(gDeckMenu))
  ```
- **Savings**: ~6 LOC per call site, 18 sites = ~108 lines removed

### P2 — Continuous trap activation boilerplate (~8 files)
- **Files**: `src_custom/duel_helpers.c` (new functions), `include/duel_helpers.h` (declarations), trap effect files
- **What**: 7-8 trap files share `ActivateXxxZone()` (Duel_ActivateContinuousZone + destroy + showtext) and `TryActivateXxxOnOpponentTurnStart()` (iterate backrow finding face-down copies) patterns.
- **Approach**: Extract two shared functions:
  - `Duel_ActivateContinuousTrapZone(struct DuelCard *zone, u16 trapId)` — activate + destroy + show text
  - `Duel_TryActivateBackrowTrapOnTurnStart(u16 trapId, void (*activateBody)(struct DuelCard *))` — iterate INACTIVE_DUELIST_BACKROW, find face-down trapId, call body
- **Savings**: ~15-20 LOC per file, 8 files = ~120-160 lines removed

### P3 — Turn effect `ShouldActivate` boilerplate (~7 files)
- **Files**: `src_custom/turn_effects/*.c` (cure_mermaid, mysterious_puppeteer, dancing_fairy, spirit_of_the_breeze, bowganian, white_magician_pikeru, ebon_magician_curran)
- **What**: Identical guard pattern checking `gActiveEffect.cardId`, `gActiveEffect.turnRow`, and zone face-up status.
- **Approach**: Add shared function `Duel_ShouldActivateSimpleTurnEffect(u16 cardId, u8 requireDefending, u8 requireAttacking)` — returns TRUE if card matches, row matches, zone exists, and face-up + optional position check. Zero changes to the turn effect hook table.
- **Savings**: ~5-8 LOC per file, 7 files = ~40 lines

### P4 — Flip-effect identical structure (3 files)
- **Files**: `src_custom/activated_effects/giant_germ.c`, `skull_mark_lady_bug.c`, `nimble_momonga.c`
- **What**: Near-identical 15-line `ActivateXxxEffect()` with only amount and card ID differing.
- **Approach**: Add `Duel_ActivateFlipEffect(u16 cardId, s32 lpDelta)` — handles the turnRow→duelist mapping, LP change, GY clear, and showtext.
- **Savings**: ~12 LOC per file, 3 files = ~36 lines

### P5 — Destroy-mask lifecycle (3 files)
- **Files**: `src_custom/spell_effects/triangle_power.c`, `thousand_energy.c`, `limiter_removal.c`
- **What**: Each has: `static` destroy mask (per-side or single), `static` fixed-monster-row variable, reset function, destroy-at-end-of-turn function.
- **Approach**: Extract into `duel_helpers.c`:
  - `Duel_InitDestroyMaskState(struct DuelDestroyMaskState *state, u8 singleMask)` — init
  - `Duel_MarkMonstersForEndOfTurnDestroy(struct DuelDestroyMaskState *state, u8 fixedRow, u8 colMask)` — mark
  - `Duel_ResolveEndOfTurnDestroy(struct DuelDestroyMaskState *state)` — destroy marked zones
- **Savings**: ~20 LOC per file, 3 files = ~60 lines

### P6 — Equip stage boost resolve (2 files)
- **Files**: `src_custom/spell_effects/united_we_stand.c`, `mage_power.c`
- **What**: 15-line `ResolveBody` pattern with target, spellZone, count, clamp, apply, register, activate, notify, show.
- **Approach**: Add `Duel_ResolveEquipStatBoost(struct DuelCard *target, struct DuelCard *spellZone, u16 spellId, u8 stages)` — wraps `ApplyDynamicEquipStages` + `RegisterDynamicEquip` + `Duel_ActivateContinuousZone` + `NotifyDynamicEquipFieldChanged` + showtext.
- **Savings**: ~10 LOC per file, 2 files = ~20 lines

### P7 — Adopt existing but unused APIs (2 cases)
- **File**: `src_custom/spell_effects/card_of_sanctity.c`, `card_of_demise.c`
- **What**: Both have `while (handSize < 5) { Duel_DrawCards(..., 1, FALSE); }` — `Duel_DrawCardsUntilHandSize()` exists in the header but is not used by either.
- **Approach**: Replace manual while-loops with `Duel_DrawCardsUntilHandSize()`.

- **File**: `src_custom/spell_effects/delinquent_duo.c`, `confiscation.c`, `the_forceful_sentry.c` (or wherever `PickRandomOpponentHandZone` is duplicated)
- **What**: `Duel_DiscardRandomFromHand()` exists but multiple cards implement manual random-hand-pick logic.
- **Approach**: Replace manual random-hand-pick with `Duel_DiscardRandomFromHand()`.

### P8 — `Duel_ResolveBurnSpell` adoption (2 files)
- **File**: `src_custom/spell_effects/sparks.c`, `hinotama.c`
- **What**: `Duel_ResolveBurnSpell` exists but these two write the burn body manually.
- **Approach**: Delegate to `Duel_ResolveBurnSpell`.

### P9 — Piercing damage helper (3 files, optional)
- **Files**: `src_custom/battle_effects/airknight_parshath.c`, `cyber_end_dragon.c`, `piranha_army.c`
- **What**: Duplicated `ApplyPiercingDamageToPlayer/ToOpponent` functions and an identical struct definition.
- **Approach**: Extract `Duel_ApplyPiercingBattleDamage(u8 damagedDuelist, s32 diff)` to `duel_helpers.c`.

## Implementation order

```
Phase 1 (infrastructure): P7 + P8 (adopt existing APIs) — safe, zero new function surface
Phase 2 (P6): Equip boost helper — 2 files, straightforward extraction
Phase 3 (P5): Destroy-mask lifecycle — 3 files, new struct in duel_helpers
Phase 4 (P4): Flip-effect shared function — 3 files
Phase 5 (P3 + P2): Turn/trap boilerplate shared functions — ~15 files
Phase 6 (P1): gDeckMenu save/restore macro — 18 sites, one header change
Phase 7 (P0): PickZone migration tool + batch migration — ~33 cards
Phase 8 (P9, optional): Piercing damage helper — low priority
```

## Files that will be created or modified

- `include/duel_helpers.h` — new function declarations + DECKMENU_SAVE/RESTORE macros
- `src_custom/duel_helpers.c` — all new shared function implementations
- `tools/migrate_to_pickzone.py` — PickZone migration script
- `src_custom/code_8043EF4_hooks.c` — remove PICK_ZONE-coded switch cases as cards migrate
- ~60 effect files — use new APIs, remove duplicated code

## Validation strategy

After each phase: `make test-cards-build` (compilation + link test). For destructively modified effects (PickZone migration, trap boilerplate), run individual hand-test configs from `configs/runtime.c`. No regression tests needed — these are mechanical extractions, not behavioral changes.

## Risks

- PickZone migration: some legacy cards have unusual cursor logic (e.g., Creature Swap needs 2 picks, Yubel has complex tributing). The migration tool must allow manual override for non-standard cases.
- Trap boilerplate: the `activateBody` callback approach means each trap still owns its one unique line. If a trap's body needs pre-destroy side effects, the shared function must support a pre-destroy hook or the card stays un-migrated.
- `CpuCopy32` availability: verify it exists as a GBA intrinsic before committing to the macro approach for gDeckMenu.
