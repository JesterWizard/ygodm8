# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Fix Status BG3 clobber from silhouette tiles

**Files touched:**
- `src_custom/status_menu_hooks.c` — silhouette tile base `0x120` → `0x110`
- `documentation/status-menu-layout.md`

**Outcome:** Silhouettes no longer overwrite `sbb1E`. Should clear BG3 garbage and stray top glyphs. `make` exits 0.

**Open / next:** In-game Status confirm.
