# CARD_STATE — latest session

**Last worked on:** 2026-07-04 — Added Elemental HERO Stratos

**Files touched:**
- `tools/card_data_manifest.json`
- `configs/runtime.c`
- `src_custom/activated_effects/elemental_hero_stratos.c`
- `include/elemental_hero_stratos.h`
- `src_custom/duel_helpers.c`
- `src_custom/code_8043EF4_hooks.c`
- `Makefile`
- `src_custom/card_effect_tally.md`
- `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** make test-cards-build passes; on-summon search HERO or destroy S/T up to other HEROes (cancel deck pick falls through to destroy)

**Open / next:**
- playtest: NS Stratos with Sparkman in deck; cancel search to destroy S/T when another HERO is on field
