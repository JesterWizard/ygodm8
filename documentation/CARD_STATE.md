# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Trunk freeze: gSortableEntries 800-cap overflow

**Files touched:**
- `asm/ram_map_ewram.s` — `gExpandedSortableEntries` (NUM_TOTAL_CARDS × 12)
- `src_custom/card_sort_hooks.c` — `gSortableEntries` → expanded buffer (APPEND_DATA)
- `ldscript.ld` — removed ROM absolute `gSortableEntries = 0x8E0CC20`
- `tools/add_card_art.py` / `ram_map_layout.py` — `SORTABLE_ENTRIES_BYTES`; qty align to 4

**Outcome:** make exits 0. Sort scratch holds 1434 entries (was 800).

**Open / next:**
- Confirm trunk opens in-game (reload ROM; new game if save qty looks wrong)
