# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Millennium tracker: event-cmd docs + 8px content spacing

**Files touched:**
- `documentation/status-menu-layout.md` — expanded `SET_MILLENNIUM_ITEM` / `CLEAR_MILLENNIUM_ITEM` docs
- `tools/generate_millennium_item_assets.py` — pack by opaque bbox with 8px gaps; emit `sMillenniumItemMapCols`
- `src_custom/status_menu_hooks.c` — place via map-col table
- `src_custom/generated/millennium_item_assets_generated.inc`

**Outcome:** `make` exits 0; layout gaps verified at 8px between content.

**Open / next:** In-game confirm tighter spacing.
