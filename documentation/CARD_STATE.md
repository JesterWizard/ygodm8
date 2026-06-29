# CARD_STATE — latest session

**Last worked on:** 2026-06-29 — Expanded graveyard documentation

**Files touched:**
- `documentation/expanded-graveyard.md`
- `CUSTOM_CONTENT.md`
- `documentation/ram-map.md`

**Outcome:** Feature doc covers dual-storage model, all six EWRAM symbols, API, B-menu viewer, and AI sim save/restore/checkpoint layers.

**Open / next:**
- Playtest Tristan turn 1 — opponent GY empty until a real send; Zone Eater on field only

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
