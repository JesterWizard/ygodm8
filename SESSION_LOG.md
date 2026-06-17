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

## 2026-06-17 — Repo-wide duel_helpers standardization

**Worked on:** Extended `duel_helpers` with reusable zone/stat/LP/trap APIs and migrated ~60 effect files off duplicated boilerplate.

**New APIs:** `Duel_ActivateContinuousZone`, `Duel_GetZoneFinalAtk`, `Duel_FixedMonsterRowForDuelist` / `Duel_FixedDuelistForMonsterRow`, `Duel_CountMonstersOnTurnRow`, `Duel_IsFixedMonsterRow`, `Duel_IsMonsterZoneTarget`, `Duel_FindBackrowCard`, `Duel_FixedMonsterSlotBit`, `Duel_ZoneIsHandSlot`, `Duel_ChangeLpWithPrefaceText`, `Duel_ResolveBurnSpell`, `Duel_ShowTrapResponseText`, `Duel_DestroyMaskedMonstersInFixedRow`, `Duel_TurnDuelistMatchingWhoseTurn`.

**Migrated:** 41 continuous trap/spell activations; limiter/graceful dice/thousand/triangle EOT masks; turn LP effects; equip spells; burn spells; trap response text; skull invitation/coffin seller; slifer atk check; riryoku/book_of_moon/kaiser_glider row checks.

**Files:** `include/duel_helpers.h`, `src_custom/duel_helpers.c`, bulk `spell_effects/`, `trap_effects/`, `turn_effects/`, `permanent_effects/`, `battle_effects/`.

**Outcome:** `make test-cards-build` and `tests.host.test_duel_helpers` pass.

**Open / next:** Backrow scan helpers for skill drain/imperial order; `Duel_FindFixedZone` (all rows) for dynamic_equip; raregold attack redirect table; more burn spells (tremendous_fire + dark room).

## 2026-06-17 — Card-ID dispatch for dynamic zone stats

**Worked on:**
- Replaced per-card stat/attack APIs (`ApplyGoblinKing*`, `GoblinKing_CanBeAttacked`, etc.) with ID-keyed dispatch in `duel_helpers`
- Central tables in `duel_helpers.c` map `cardId` → zone stat applier / attack gate predicate
- Migrated Goblin King, Gyaku Gire Panda, Great Maju Garzett; deleted `goblin_king.h`

**Files:**
- `include/duel_helpers.h`, `src_custom/duel_helpers.c` — `Duel_TryApplyDynamicZoneStats`, `Duel_TryApplyDynamicStatMod`, `Duel_CanAttackMonsterZone`, helpers
- `src_custom/card_hooks.c`, `code_8043EF4_hooks.c`, `ai_attack_hooks.c` — generic dispatch calls
- `src_custom/permanent_effects/goblin_king.c`, `gyaku_gire_panda.c`, `great_maju_garzett.c`
- `include/great_maju_garzett.h`, `include/gyaku_gire_panda.h`

**Outcome:** `make test-cards-build` passes. New dynamic-stat cards: implement `Card_ApplyDynamicZoneStats`, add one table row + optional attack gate row.

**Open / next:** None for this thread.

## 2026-06-17 — Goblin King stat helpers in duel_helpers

**Worked on:**
- Extracted reusable field-stat / zone-scan APIs from Goblin King into `duel_helpers`
- Refactored `goblin_king.c` to card-specific rules only (Fiend count × 500, attack gate)

**Files:**
- `include/duel_helpers.h` — `Duel_ClampStat`, zone find/count, `Duel_WriteCardInfoStats`, `Duel_ApplyStatModViaZoneApplier`
- `src_custom/duel_helpers.c` — implementations + `Duel_ClampStat` self-check
- `src_custom/permanent_effects/goblin_king.c` — slim card file
- `tests/host/test_duel_helpers.py` — header symbol coverage

**Outcome:**
- `make test-cards-build` and `make test-host` pass
- Gyaku Gire Panda / Great Maju Garzett can adopt `Duel_ApplyStatModViaZoneApplier` next

**Open / next:**
- Migrate other dynamic-stat cards (Gyaku Gire Panda, Great Maju Garzett) to shared helpers

## 2026-06-17 — Repo context docs + Hourglass stat pipeline

**Worked on:**
- Field vs battle ATK/DEF discrepancy (Hourglass of Life and similar stage boosts)
- Split stat pipelines: field uses `ApplyFieldZoneStatsToCardInfo`; battle uses `SetFinalStat` via `SetAttackAction`
- `gSetFinalStatZone` poisoning from field refresh / mismatched zone reads
- Hourglass refactor to `duel_helpers` API
- Created `ARCHITECTURE.md`, this log, and session-context Cursor rule

**Files:**
- `src_custom/card_hooks.c` — `ComputeFinalStage`, `RefreshPendingBattleActionStatsFromZones`, `SetFinalStat` id-match guard, field path clears
- `src_custom/code_803F02C_hooks.c` — `ComputeFinalStage`
- `src_custom/mini_card_hooks.c` — stage stamps via `ComputeFinalStage`
- `src_custom/trap_effects/fairy_box.c` — battle stat resync hook point
- `src_custom/duel_helpers.c` — `Duel_IncrementPermStageOnDuelistMonsters`, `Duel_RefreshMonsterStatOverlays`
- `src_custom/activated_effects/hourglass_of_life.c` — slim API-based effect
- `tests/host/test_mini_card_stats.py`
- `ARCHITECTURE.md`, `SESSION_LOG.md`, `.cursor/rules/session-context.mdc`

**Outcome:**
- Field overlays and battle stats should agree after stage changes when attack goes through `TryApplyFairyBoxToPendingAction`
- Hourglass: boost active duelist row → `Duel_ChangeLp` → refresh overlays → effect text
- `make test-cards-build` and host stat tests pass

**Open / next:**
- In-game confirm Hourglass field + battle ATK match after activate + attack
- Consider migrating other stage-boost effects (Thousand Energy, Triangle Power) to `Duel_RefreshMonsterStatOverlays`
- Broader cleanup: more effects on `duel_helpers` instead of manual LP loops
