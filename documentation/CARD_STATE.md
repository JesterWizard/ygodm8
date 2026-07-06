# CARD_STATE — latest session

**Last worked on:** 2026-07-06 — Shrunk Light End Dragon EWRAM: 6 × s8 (6 bytes, was 40)

**Files touched:**
- `asm/ram_map_ewram.s`
- `include/light_end_dragon.h`
- `src_custom/activated_effects/light_end_dragon.c`
- `src_custom/card_hooks.c`
- `src_custom/turn_effect_hooks.c`

**Outcome:** make test-cards-build passes. Replaced 20 × s16 (40 bytes) delta array with 6 × s8 (6 bytes) stage-count array. Stores stage count (-3) per column; applies `stages * 500` to both ATK and DEF. Cleared at End Phase.

**Open / next:**
- playtest both End Dragons
