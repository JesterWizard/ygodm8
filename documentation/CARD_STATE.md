# CARD_STATE — latest session

**Last worked on:** 2026-06-29 — First-turn opponent GY purge after AI sim (35 deck remaining)

**Files touched:**
- `src_custom/expanded_graveyard.c` — `GraveyardExpand_ClearOpponentAfterSimIfFirstTurn`
- `src_custom/ai_main_hooks.c` — call after `AiSimulateAllCandidateActions`
- `include/expanded_graveyard.h`, `documentation/expanded-graveyard.md`
- `tests/host/test_expanded_graveyard.py`

**Outcome:** After opponent AI sim, clears opponent GY when `NumCardsInDeck - cardsDrawn == 35` (`DECK_SIZE - 5`). Documented threshold for future deck-size changes. `make test-cards-build` passes.

**Open / next:**
- Playtest Tristan — opponent GY empty until real send; no purge on turn 2+
