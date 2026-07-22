# CARD_STATE — latest session

**Last worked on:** 2026-07-22 — Hourglass stage ATK wiped by overlay SetCardInfo

**Outcome:** Stage applied, then `GetTypeGroup`/`SetCardInfo` in Castle/Gillman/etc. overlays reset ATK/DEF to print. Fixed via `Duel_CardIsMonster` / `gCardData_NEW` gates + atk/def restore in `Duel_CardNameContains`. `make` OK.

**Open / next:** Playtest Flip Hourglass alone → 1200/1100. Audit other Apply* helpers for GetTypeGroup.
