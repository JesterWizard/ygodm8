# CARD_STATE — latest session

**Last worked on:** 2026-07-10 — Added 10 cards (BERSERKER_SOUL through CHAOS_FORM) with art and stub effects

**Files touched:**
- `tools/card_data_manifest.json`
- `src_custom/spell_effects/{berserker_soul`
- `bubble_blaster`
- `burden_of_the_mighty`
- `call_of_the_mummy`
- `celestial_sword_eatos`
- `chaos_form}.c`
- `src_custom/trap_effects/break_the_destiny.c`
- `src_custom/activated_effects/{birdface`
- `blue_eyes_alternative_ultimate_dragon}.c`
- `src_custom/permanent_effects/cannonball_spear_shellfish.c`
- `src_custom/monster_effect_hooks.c`
- `src_custom/permanent_effect_hooks.c`
- `include/constants/monster_effects.h`

**Outcome:** make test-cards-link passes; all 10 cards in manifest with 512x512 art; effects stubbed with TODO bodies; descriptions condensed to fit page width limits

**Open / next:**
- implement actual effect logic for these 10 cards
