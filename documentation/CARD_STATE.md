# CARD_STATE — latest session

**Last worked on:** 2026-07-18 — Fix deck wipe on GY viewer

**Files touched:**
- `src_custom/duel_gy_viewer.c`

**Outcome:** make exits 0. Empty GY/RFP no longer mutates `gDeckMenu` before save; load is wrapped in DECKMENU_SAVE/RESTORE.

**Open / next:**
- Playtest: open empty + non-empty GY during a duel; confirm deck still has cards after the duel
