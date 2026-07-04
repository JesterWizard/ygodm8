# CARD_STATE — latest session

**Last worked on:** 2026-07-04 — Fix Future Fusion Chimeratech material count

**Files touched:**
- `src_custom/spell_effects/future_fusion.c`
- `asm/ram_map_ewram.s`

**Outcome:** make test-cards-build passes; material count stored in EWRAM not tempStage (was zeroed by permanent effects, defaulting to 2 mats / 1600 ATK)

**Open / next:**
- playtest: Future Fusion 5 Cyber Dragons -> Overdragon 4000 ATK
