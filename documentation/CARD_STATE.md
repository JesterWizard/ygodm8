# CARD_STATE — latest session

**Last worked on:** 2026-07-06 — Replaced Light End Dragon's tempStage reduction with EWRAM delta array (persists until End Phase)

**Files touched:**
- `src_custom/activated_effects/light_end_dragon.c`
- `include/light_end_dragon.h`
- `asm/ram_map_ewram.s`
- `src_custom/card_hooks.c`
- `src_custom/turn_effect_hooks.c`

**Outcome:** make test-cards-build passes; target ATK/DEF -1500 now stored in `gLightEndDragonDefDelta[]` EWRAM array (not tempStage which was reset prematurely). Delta applied in `card_hooks.c` stat pipeline alongside Riryoku/PowerBond deltas. Cleared at End Phase alongside `ClearAllRiryokuAtkDeltas()`. Self still uses permanent -500 via `DecrementPermStage`.

**Open / next:**
- playtest both End Dragons
