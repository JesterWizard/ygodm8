# CARD_STATE — latest session

**Last worked on:** 2026-07-04 — Added The Suppression Pluto

**Files touched:**
- `tools/card_data_manifest.json`
- `configs/runtime.c`
- `src_custom/activated_effects/the_suppression_pluto.c`
- `include/the_suppression_pluto.h`
- `src_custom/duel_helpers.c`
- `src_custom/code_8043EF4_hooks.c`
- `tests/host/test_the_suppression_pluto.py`

**Outcome:** make test-cards-build passes; on-summon opponent Spell/Trap steal implemented (simplified from full hand-reveal choice effect)

**Open / next:**
- Full once-per-turn declare/hand-reveal/choice effect when choice UI exists
