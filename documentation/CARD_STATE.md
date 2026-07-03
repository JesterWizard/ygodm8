# CARD_STATE — latest session

**Last worked on:** 2026-07-03 — Added Elemental HERO Ice Edge

**Files touched:**
- `tools/card_data_manifest.json`
- `configs/runtime.c`
- `src_custom/activated_effects/elemental_hero_ice_edge.c`
- `src_custom/battle_effects/elemental_hero_ice_edge.c`
- `include/elemental_hero_ice_edge.h`
- `include/constants/monster_effects.h`
- `src_custom/monster_effect_hooks.c`
- `src_custom/battle_damage_hooks.c`
- `src_custom/code_8043EF4_hooks.c`
- `src_custom/code_803F02C_hooks.c`
- `src_custom/ai_attack_hooks.c`
- `src_custom/ai_main_hooks.c`
- `src_custom/code_8041C94_hooks.c`
- `src_custom/draining_shield_hooks.c`
- `src_custom/call_of_the_haunted_hooks.c`
- `asm/ram_map_ewram.s`
- `Makefile`

**Outcome:** make test-cards-build passes; discard grants direct attack this turn; direct battle damage targets Set S/T

**Open / next:**
- playtest discard direct-attack grant and Set S/T destroy on direct damage
