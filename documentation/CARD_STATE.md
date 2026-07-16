# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Small-font description reflow

**Files touched:**
- `src_custom/code_801EF30_hooks.c` — recover + word-wrap into 10-row pages when small font on
- `asm/ram_map_ewram.s` — `gDescProseBuf` / `gDescReflowBuf`
- `tests/host/test_card_description_reflow.py`

**Outcome:** Manifest 70-char pages are concatenated and reflowed into denser 136-char small-font pages at runtime. `make` exits 0; reflow host test OK.

**Open / next:** Confirm in-game (2-page cards should often become 1 page).
