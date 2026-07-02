# CARD_STATE — latest session

**Last worked on:** 2026-07-02 — Gaia ATK boost persists while on field (not End Phase)

**Files touched:**
- `src_custom/activated_effects/elemental_hero_gaia.c`
- `include/elemental_hero_gaia.h`
- `asm/ram_map_ewram.s`
- `src_custom/card_hooks.c`
- `src_custom/code_803F02C_hooks.c`

**Outcome:** make test-cards-build passes; Gaia boost + target halving stored in EWRAM, applied via stat pipeline; cleared when respective monster leaves field

**Open / next:**
- User rebuild ROM; confirm Gaia keeps boost across turns until it leaves the field
