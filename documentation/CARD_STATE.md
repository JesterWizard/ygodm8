# CARD_STATE — latest session

**Last worked on:** 2026-07-20 — Burn popup fix + heal scripts

**Outcome:** Burn popups skipped because `BURN_THROUGH_TRAPS` stashed args in `APPEND_DATA` (ROM; writes no-ops → spellId/damage 0). Fixed via `Duel_TryResolveBurnSpellThroughTraps`. Added `HEAL_THROUGH_TRAPS` + Mooyan→Dian Keto JSON scripts.

**Open / next:** More damage-calc subscribers beyond Skyscraper/Inferno; more JSON scripts (draw/search/simple destroy).
