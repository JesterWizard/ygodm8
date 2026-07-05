# CARD_STATE — latest session

**Last worked on:** 2026-07-05 — Removed-from-play zone (80 bytes EWRAM per duelist, L/R viewers)

**Files touched:**
- `asm/ram_map_ewram.s`
- `include/removed_from_play.h`
- `include/duel_helpers.h`
- `configs/runtime.h`, `configs/runtime.c`
- `src_custom/removed_from_play.c`
- `src_custom/duel_gy_viewer.c`
- `src_custom/duel_helpers.c`
- `src_custom/code_803F02C_hooks.c`
- `src_custom/trap_effects/angels_tear.c`
- `src_custom/activated_effects/chaos_emperor_dragon_envoy_of_the_end.c`
- `src_custom/activated_effects/black_luster_soldier_envoy_of_the_beginning.c`
- `src_custom/spell_effects/book_of_life.c`
- `src_custom/fusion_duel.c`
- `documentation/removed-from-play.md`
- `documentation/ram-map.md`
- `tests/host/test_removed_from_play.py`

**Outcome:** `make test-cards-build` passes. Banished cards stored in `gRemovedFromPlay`; L/R opens player/opponent list viewer.

**Open / next:**
- Wire E-HERO banish-counting effects to `RemovedFromPlay_*` API
- Playtest L/R during duel; confirm banish from field and GY shows in lists
