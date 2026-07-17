# CARD_STATE — latest session

**Last worked on:** 2026-07-17 — Added VENOM_BURN–YOWIE (trunk + stub effects)

**Files touched:**
- `tools/card_data_manifest.json`
- `tools/fix_descriptions.py`
- `src_custom/monster_effect_hooks.c`
- `src_custom/permanent_effect_hooks.c`
- `src_custom/trap_effect_hooks.c`
- `stub .c under activated_effects/ permanent_effects/ spell_effects/ trap_effects/`
- `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** make exits 0. 9 cards in trunk with art; effects stubbed (VENOM_COBRA normal, no wire). total_cards=1601. Forced VIPERS_REBIRTH (vs API VIPER_S_REBIRTH) to match art stem. CARD_PROGRESS todo list empty — all art-ready cards now In game.

**Open / next:**
- Implement real effect logic for these 9 cards (and prior stub batches)
