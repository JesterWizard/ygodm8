# CARD_STATE — latest session

**Last worked on:** 2026-06-28 — Restored duel board life point counters

**Files touched:**
- `src_custom/field_spell_gfx_hooks.c`, `src_custom/duel_board_lp_hooks.c`

**Outcome:** `FlushDuelFieldLayerToHardware` no longer calls `LoadPalettes()`; pushes field palette to PPU banks 0-2, UI banks 3-15, and OBJ palettes (`gPaletteBuffer + 256`) separately. LP/turn counters draw before the field tilemap flush. Follow-up fix restored card/cursor OBJ palette upload. `make test-cards-build` passes.

**Open / next:** Playtest LP/turn counters during scroll and with custom field spells active.
