# CARD_STATE — latest session

**Last worked on:** 2026-07-18 — Info bar clears on empty cursor zone

**Files touched:**
- `src_custom/duel_opponent_hand_scroll_hooks.c`

**Outcome:** Empty field/hand cursor blanks bottom alpha-blend bar (`SetCardInfo(CARD_NONE)`). `make` OK.

**Open / next:**
- Playtest cursor on empty monster/backrow/hand — bar should have no name/ATK/DEF
