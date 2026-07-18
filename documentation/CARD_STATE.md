# CARD_STATE — latest session

**Last worked on:** 2026-07-18 — Full TCG descriptions for remaining long cards

**Files touched:**
- `tools/card_data_manifest.json`
- `tools/add_card_art.py`
- `tools/refresh_card_descriptions.py`
- `asm/ram_map_ewram.s`
- `src_custom/code_801EF30_hooks.c`
- `documentation/card-descriptions.md`

**Outcome:** make exits 0. Bumped `gDescProseBuf`/`gDescReflowBuf` to 0x400. Fit check allows 9 display pages. Former 33 “overflow” cards now have full TCG text.

**Open / next:**
- Anime/custom cards with no API match still have hand-written text
