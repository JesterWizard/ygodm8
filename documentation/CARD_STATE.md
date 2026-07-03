# CARD_STATE — latest session

**Last worked on:** 2026-07-03 — Fix Sunrise field glitch on opponent turn

**Files touched:**
- `src_custom/permanent_effects/elemental_hero_sunrise.c`
- `src_custom/fusion_duel.c`
- `asm/ram_map_ewram.s`

**Outcome:** No longer stamps stat overlays on updateGfx=FALSE placements (AI summon); ATK boost still applies on real draws; opponent-turn destroy is silent

**Open / next:**
- playtest Sunrise on field through opponent turn and AI summons
