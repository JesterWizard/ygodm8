# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Small font card descriptions

**Files touched:**
- `configs/runtime.h` / `configs/runtime.c` — `use_small_card_description_font`
- `src_custom/code_801EF30_hooks.c` — 8×8 font + sequential 10×14 tilemap
- `src_custom/debug/debug_menu_runtime_config.c` — "Small Desc" toggle

**Outcome:** Card detail descriptions can use the half-height font (10 rows / 140 chars vs 5 / 70). Default ON. `make` exits 0.

**Open / next:** Confirm in-game; optionally extend generator to emit denser pages when small font is intended.
