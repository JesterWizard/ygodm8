# CARD_STATE — latest session

**Last worked on:** 2026-07-04 — Fix Big Saturn popup_2 on opponent effect destroy (explicit resolve + owner scan)

**Files touched:**
- `src_custom/permanent_effects/the_big_saturn.c`
- `src_custom/permanent_effect_hooks.c`
- `include/the_big_saturn.h`
- `asm/ram_map_ewram.s`

**Outcome:** Effect owner from origin card on field; TheBigSaturn_TryResolveGyDamage after board scan; force gHideEffectText off for popup; make test-cards-build passes

**Open / next:**
- Playtest Raigeki/MST/monarch destroy on opponent turn
