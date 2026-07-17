# CARD_STATE — latest session

**Last worked on:** 2026-07-17 — Fix empty starting deck (sort buffer bridge)

**Files touched:**
- `src_custom/card_sort_hooks.c`
- `tools/validate_trunk_sort.py`
- `documentation/session_logs/2026-07-17.md`

**Outcome:** `make` exits 0. Opening the deck menu no longer wipes `gDeckMenu.cards` while leaving `cardCount` at 40.

**Open / next:** Playtest new game → Deck: cards list matches the 40-count; optional upgrade is patching ROM `0x8E0CC20` → `gExpandedSortableEntries` to drop the bridge.
