# CARD_STATE — latest session

**Last worked on:** 2026-07-11 — Added 10 cards (MAGICAL_SCIENTIST through MAUSOLEUM_OF_THE_EMPEROR) from lines 512-521.

**Files touched:**
- `tools/card_data_manifest.json`
- `configs/runtime.c`
- `src_custom/activated_effects/magical_scientist.c`, `majestic_mech_goryu.c`, `manju_of_the_ten_thousand_hands.c`, `marshmallon.c`, `master_peace_the_true_dracoslaying_king.c`, `man_thro_tro.c`
- `src_custom/spell_effects/magical_stone_excavation.c`, `mask_of_dispel.c`, `mask_of_the_accursed.c`, `mausoleum_of_the_emperor.c`
- `src_custom/monster_effect_hooks.c`
- `tools/add_custom_card.py`

**Outcome:** `make clean && make` passes. All 10 cards in trunk with 512x512 art; effects stubbed with TODO bodies.

**Open / next:**
- Implement actual effect logic for these 10 cards
