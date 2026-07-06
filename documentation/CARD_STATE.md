# CARD_STATE — latest session

**Last worked on:** 2026-07-06 — Added Trade-In spell with effect

**Files touched:**
- `tools/card_data_manifest.json`
- `configs/runtime.c`
- `src_custom/spell_effects/trade_in.c`
- `include/trade_in.h`
- `src_custom/spell_effect_hooks.c`
- `src_custom/code_8043EF4_hooks.c`

**Outcome:** make test-cards-build passes; discard Level 8 monster from hand, draw 2

**Open / next:**
- playtest activation gate without Level 8 in hand
