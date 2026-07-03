# CARD_STATE — latest session

**Last worked on:** 2026-07-03 — Duel trunk-view graphics API

**Outcome:** Card-opened trunk/deck-menu views now bracket menu use with `DeckMenu_BeginDuelTrunkView()` / `DeckMenu_EndDuelTrunkView()` so duel graphics reload on every exit path. Non-graveyard card pickers use `DeckMenuMainPickConfirmWithLabels`; top-level B waits a frame and does nothing, avoiding both field return and input-loop freeze. `make test-cards-build` passes.

**Open / next:** playtest Emergency Call and fusion picker trunk menus in emulator
