# CARD_STATE — latest session

**Last worked on:** 2026-07-05 — Court of Justice hand-lock fix (Ultimate Offering-style ignition)

**Files touched:**
- `src_custom/spell_effects/court_of_justice.c`
- `include/court_of_justice.h`
- `src_custom/code_8043EF4_hooks.c`
- `src_custom/code_803F02C_hooks.c`
- `src_custom/turn_effect_hooks.c`
- `asm/ram_map_iwram.s`

**Outcome:** `make test-cards-build` passes. After face-up Court on backrow + face-up Level 1 Fairy, Fairy monsters in hand unlock and can be placed as Special Summons (bypassing lock/tribute). Backrow activation still uses hand picker.

**Open / next:**
- Playtest: set Court → normal summon Tiny Angel face-up → click Splendid Venus; also backrow Court ignition path
