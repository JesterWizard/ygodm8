# CARD_STATE — latest session

**Last worked on:** 2026-07-06 — Added The Wicked Eraser with dynamic ATK/DEF and field wipe

**Files touched:**
- `tools/card_data_manifest.json`
- `configs/runtime.c`
- `src_custom/permanent_effects/the_wicked_eraser.c`
- `src_custom/activated_effects/the_wicked_eraser.c`
- `include/the_wicked_eraser.h`
- `asm/ram_map_ewram.s`

**Outcome:** make test-cards-build passes; ATK/DEF = opponent cards x1000; GY wipe destroys all field cards; Main Phase self-destruct ignition

**Open / next:**
- playtest cannot-be-set restriction; verify opponent card count includes field spell
