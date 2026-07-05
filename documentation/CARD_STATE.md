# CARD_STATE — latest session

**Last worked on:** 2026-07-05 — Fixed turn counter frozen at 0 (IWRAM misalignment)

**Files touched:**
- `asm/ram_map_iwram.s`

**Outcome:** `gDuelBoardTurnCount` pad increased to 2 bytes so u16 lands at even address; `make all` passes

**Open / next:** Playtest turn counter increments each turn start
