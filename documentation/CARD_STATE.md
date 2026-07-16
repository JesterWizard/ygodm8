# CARD_STATE — latest session

**Last worked on:** 2026-07-16 — Fix ghost portrait glitch under duel portrait

**Files touched:**
- `src_custom/duel_voice_hooks.c` — always clear OAM 0–3 (leftover overworld portrait at y=48); mini-cards only when `hideBoardSprites`
- `include/duel_voice.h`

**Outcome:** `make` exits 0.

**Open / next:** In-game confirm no second square under Yugi; mini-cards still visible.
