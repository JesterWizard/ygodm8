# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Fix mGBA title-screen black screen (LZ asset alignment)

**Files touched:**
- `configs/runtime.h` — `APPEND_ASSET` now `aligned(4)`
- `src_custom/title_screen_hooks.c` — cast LZ source to `const u32 *`
- `tools/build_custom_maps.py`, `documentation/title-screen.md`

**Outcome:** `sTitleScreenTiles` at `0x097505a0` (word-aligned). `make` exits 0.

**Open / next:** Confirm title screen boots on mGBA.
