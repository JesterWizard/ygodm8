# CARD_STATE — latest session

**Last worked on:** 2026-07-03 — Added Elemental HERO Captain Gold

**Files touched:**
- `tools/card_data_manifest.json`
- `configs/runtime.c`
- `src_custom/permanent_effects/elemental_hero_captain_gold.c`
- `src_custom/permanent_effect_hooks.c`
- `src_custom/code_8043EF4_hooks.c`
- `Makefile`

**Outcome:** make test-cards-build passes; hand discard searches Skyscraper; face-up on field without Skyscraper self-destructs

**Open / next:**
- playtest hand search and field self-destruct with/without Skyscraper
