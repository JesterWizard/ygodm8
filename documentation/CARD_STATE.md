# CARD_STATE — latest session

**Last worked on:** 2026-07-04 — Grand Jupiter equip ATK via stat pipeline post-hook (Power Bond pattern)

**Files touched:**
- `src_custom/activated_effects/the_grand_jupiter.c`
- `include/the_grand_jupiter.h`
- `asm/ram_map_ewram.s`
- `src_custom/card_hooks.c`
- `src_custom/duel_helpers.c`
- `tests/host/test_the_grand_jupiter.py`

**Outcome:** Absorb still places monster in backrow; ATK bonus now applied in `ApplyFieldZoneStatsToCardInfo` via `ApplyTheGrandJupiterEquipAtkBonus` (sums equipped monsters' original ATK from `gCardData_NEW`). Equip links store Jupiter fixed row/col instead of board-cell index. `make test-cards-build` passes.

**Open / next:**
- Playtest absorb → 2750 with Zone Eater; multi-equip stacking; End Phase SS
