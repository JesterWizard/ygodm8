# CARD_STATE — latest session

**Last worked on:** 2026-06-28 — De-Fusion (manifest, shared fusion recipes, spell effect hook, runtime test hand)

**Files touched:**
- `tools/card_data_manifest.json`
- `configs/runtime.c`
- `include/fusion_recipes.h`
- `include/de_fusion.h`
- `src_custom/fusion_recipes.c`
- `src_custom/spell_effects/de_fusion.c`
- `src_custom/spell_effects/polymerization.c`
- `src_custom/spell_effect_hooks.c`
- `src_custom/code_8043EF4_hooks.c`
- `src_custom/card_effect_tally.md`

**Outcome:** `make test-cards-build` passes. De-Fusion targets a fusion monster with a Polymerization recipe entry, sends it to the GY, and Special Summons the recipe materials in Attack Position.

**Open / next:**
- In-duel test: Polymerize a monster, activate De-Fusion, confirm materials return
- `src_custom/assets/cards/80x80/de_fusion.png` art still missing
