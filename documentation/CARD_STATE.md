# CARD_STATE — latest session

**Last worked on:** 2026-07-06 — Cyber Barrier Dragon fast_ai sim mask + popup fix

**Files touched:**
- `asm/ram_map_ewram.s`
- `src_custom/ai_simulation_hooks.c`
- `src_custom/battle_effects/cyber_barrier_dragon.c`
- `src_custom/ai_attack_hooks.c`

**Outcome:** `make test-cards-build` passes; AI sim no longer consumes CBD once-per-turn mask before real attack; popup forced on negate

**Open / next:**
- playtest opponent first attack with CBD in ATK vs Tristan
