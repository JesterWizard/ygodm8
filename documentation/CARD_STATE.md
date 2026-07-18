# CARD_STATE — latest session

**Last worked on:** 2026-07-18 — Duel voice portrait keeps mini-cards

**Files touched:**
- `src_custom/duel_voice_hooks.c`
- `include/duel_voice.h`
- `src_custom/mechanics_tutorial.c`
- `documentation/custom-voices.md`

**Outcome:** Portrait only hides OAM 102 (VRAM clash); other mini-cards stay. `make` OK.

**Open / next:**
- Playtest turn-start portrait with a full board
- Optional: evacuate zone (0,0) tiles so that slot stays visible too
