# CARD_STATE — latest session

**Last worked on:** 2026-07-11 — Added 12 Vision HERO and other cards to trunk

**Files touched:**
- `tools/card_data_manifest.json`
- `include/constants/card_ids.h`
- `src_custom/assets/cards/CARD_PROGRESS.md`

**Outcome:** make clean && make passes (exit 0). 12 cards added: VISION_HERO_MINIMUM_RAY, VISION_HERO_MULTIPLY_GUY, VISION_HERO_POISONER, VISION_HERO_TRINITY, VISION_HERO_VYON, VISION_HERO_WITCH_RAIDER, VISION_RELEASE, WATAPON, WHITE_DRAGON_RITUAL, WILD_NATURES_RELEASE, WOUGHTWEILER, YELLOW_GADGET. All have 80x80 + 512x512 art. Manifest entries with condensed descriptions and popup texts. Effects stubbed (no hook files).

**Open / next:**
- Implement effects for these cards
