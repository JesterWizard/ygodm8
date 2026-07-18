# CARD_STATE — latest session

**Last worked on:** 2026-07-18 — Graveyard black vertical lines (LZ77)

**Files touched:**
- `tools/build_custom_maps.py` (BIOS LZ77 store `disp-1`; always insert transparent tile 0)
- `tests/host/test_custom_maps_collision.py` (BIOS roundtrip test)
- regenerated graveyard tileset (746 tiles, tile 0 = transparent)

**Outcome:** Broken LZ displacement wrote OOB zeros → barcode stripes. Fixed + transparent tile 0. `make` OK.

**Open / next:**
- Playtest graveyard — vertical lines should be gone
