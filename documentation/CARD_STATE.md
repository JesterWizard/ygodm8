# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Added AROMAGE_JASMINE through AROMASERAPHY_SWEET_MARJORAM (trunk + stub effects)

**Files touched:**
- `tools/card_data_manifest.json` — 10 new cards
- `tools/add_custom_card.py` — Tuner/Link/XYZ frame + Link level support
- `tools/wire_card_effect.py` — activated decls/entries insert inside ActivateMonsterEffectBody
- `src_custom/activated_effects/{aromage_jasmine,aromage_laurel,aromage_marjoram,aromage_rosemary,aromalilith_magnolia,aromalilith_rosalina,aromalilith_rosemary,aromaseraphy_jasmine,aromaseraphy_rosemary,aromaseraphy_sweet_marjoram}.c`
- `src_custom/monster_effect_hooks.c`
- `src_custom/assets/cards/CARD_PROGRESS.md` — moved to done

**Outcome:** `make` exits 0. Art from existing `80x80/`; effects stubbed with TODO bodies.

**Open / next:** Implement actual effect logic for these 10 cards.
