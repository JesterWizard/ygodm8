# CARD_STATE — latest session

**Last worked on:** 2026-07-03 — Added Elemental HERO The Shining

**Files touched:**
- `tools/card_data_manifest.json`
- `configs/runtime.c`
- `src_custom/assets/cards/80x80/elemental_hero_the_shining.png`
- `src_custom/permanent_effects/elemental_hero_the_shining.c`
- `include/elemental_hero_the_shining.h`
- `include/fusion_recipes.h`
- `src_custom/fusion_recipes.c`
- `src_custom/duel_helpers.c`
- `src_custom/code_803F02C_hooks.c`

**Outcome:** make test-cards-build passes; banish-based ATK boost and leave-field hand recovery stubbed (text only on leave) until banish zone exists

**Open / next:**
- Implement banish zone, then wire +300 ATK per banished E-HERO and return-up-to-2 on leave
