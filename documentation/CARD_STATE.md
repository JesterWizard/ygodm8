# CARD_STATE — latest session

**Last worked on:** 2026-07-04 — Neptune copied vanilla passives apply tempStage

**Files touched:**
- `include/duel_helpers.h`
- `src_custom/duel_helpers.c`
- `src_custom/permanent_effects/the_tyrant_neptune.c`
- `tests/host/test_the_tyrant_neptune.py`

**Outcome:** Blade Knight (and other vanilla tempStage passives) now boost Neptune's displayed ATK/DEF via `Duel_StageModifiedStat(ComputeFinalStage(zone))` in `TheTyrantNeptune_ApplyDynamicZoneStats`. `make test-cards-build` passes; Neptune host tests pass.

**Open / next:**
- Register more custom passives in `sCopiedPassiveAtkBonuses` as needed
