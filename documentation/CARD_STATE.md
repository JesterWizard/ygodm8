# CARD_STATE — latest session

**Last worked on:** 2026-07-23 — MyBoy Continue bisect (extras no-op)

**Outcome:** Extras load no-op’d; VBlank cleared before Game Menu; `gLoadCustomSaveExtrasPending` in EWRAM ram_map (custom `.data` was discarded). `make` OK.

**Open / next:** MyBoy playtest: title Continue → Game Menu → Continue → overworld. If OK, re-enable extras loaders one at a time.
