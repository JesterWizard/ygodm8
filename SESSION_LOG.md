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
