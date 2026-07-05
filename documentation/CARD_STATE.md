# CARD_STATE — latest session

**Last worked on:** 2026-07-05 — Instant win cheat moved from L to START in duel

**Files touched:**
- `configs/runtime.h`
- `configs/runtime.c`
- `src_custom/code_803F02C_hooks.c`

**Outcome:** `make test-cards-build` passes. `instant_win_with_start_button` triggers player win on START; L restores vanilla stat-screen behavior.

**Open / next:**
- Playtest START instant win in duel; L should open stat screen again
