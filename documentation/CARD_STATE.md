# CARD_STATE — latest session

**Last worked on:** 2026-06-28 — Diffusion Wave-Motion attack lock for rest of turn

**Files touched:**
- `asm/ram_map.s`
- `include/diffusion_wave_motion.h`
- `src_custom/spell_effects/diffusion_wave_motion.c`
- `src_custom/duel_attack_restrictions.c`
- `src_custom/code_803F02C_hooks.c`

**Outcome:** make test-cards-link passes; gDiffusionWaveMotionAttackLockTurn blocks all active-duelist monster attacks until turn ends

**Open / next:**
- In-duel test: activate DWM
- confirm other monsters cannot attack same turn
- can attack next turn
