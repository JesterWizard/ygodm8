# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Timed Duel 3 missing from menu (stale .o)

**Files touched:**
- `Makefile` — `timed_duel.o` depends on table `.inc` + layouts header
- `documentation/timed-duels.md` — rebuild note

**Outcome:** `make` exits 0. Root cause was stale `timed_duel.o` (table `.inc` not a make dep). Layout 03 now linked.

**Open / next:** Reload ROM; confirm Timed Duel 3 in debug menu.
