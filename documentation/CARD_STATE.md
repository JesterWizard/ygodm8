# CARD_STATE — latest session

**Last worked on:** 2026-06-29 — AI sim phantom GY (Zone Eater) — second pass

**Files touched:**
- `src_custom/expanded_graveyard.c`
- `src_custom/ai_simulation_hooks.c`
- `src_custom/ai_hooks.c`
- `src_custom/ai_sim_fast.c`
- `src_custom/ai_main_hooks.c`
- `include/ai_sim.h`
- `asm/ram_map.s`

**Outcome:** `make test-cards-build` passes. Sim guard uses `gAiSimInBatch || gHideEffectText`; batch checkpoint wraps full sim; save/restore keeps expanded stack authoritative and syncs legacy top; legacy graveyard stripped from duel snapshot on save.

**Open / next:**
- Playtest Tristan turn 1 — opponent GY empty until a real send; Zone Eater on field only
