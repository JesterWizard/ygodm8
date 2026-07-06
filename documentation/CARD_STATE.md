# CARD_STATE — latest session

**Last worked on:** 2026-07-06 — Fixed Dark End Dragon targeting — rewrote with Soul Taker cursor pattern

**Files touched:**
- `include/dark_end_dragon.h`
- `src_custom/activated_effects/dark_end_dragon.c`
- `src_custom/code_8043EF4_hooks.c`

**Outcome:** make test-cards-build passes; replaced buggy PickZone targeting (null ptr in FindFirstTarget) with manual DUEL_CURSOR_DARK_END_DRAGON_TARGET dispatch via code_8043EF4_hooks.c A/B handlers; effect: DecrementPermStage on self + Duel_DestroyZone on opponent monster + stat refresh

**Open / next:**
- playtest targeting + ATK reduction
