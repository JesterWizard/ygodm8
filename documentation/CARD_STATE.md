# CARD_STATE — latest session

**Last worked on:** 2026-07-12 — Fixed map extraction: sRGB gamma + 256-color palette

**Files touched:**
- `tools/extract_maps.py` — rewritten: reads 256 colors, applies sRGB gamma (1/2.2), separate ground/roof layers
- `src_custom/assets/maps/` — all 122 files re-extracted (61 ground + 61 roof)
- `documentation/session_logs/2026-07-12.md` — updated

**Outcome:** Map extraction is now correct:
- Palette: 256 colors from pointer (not 240+font palette)
- Gamma: sRGB correction applied (avg brightness 108→273)
- Layers: separate ground + roof PNGs for all 61 maps
- Cable car overlay (map 0x29) saved as separate file
- Game code confirmed: 4bpp mode, CBB0, SBB31/30

**Open / next:**
- Run `make test-host` to verify no regressions
- Implement effects for Vision HERO and other cards
