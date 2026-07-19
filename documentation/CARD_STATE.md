# CARD_STATE — latest session

**Last worked on:** 2026-07-19 — Wire new duelist voice clips

**Files touched:**
- `tools/voice_manifest.json` — Bonz, Espa Roba, Lumis, Umbra, Marik, Noah, Rebecca, Strings, Serenity
- `include/overworld.h` — `DUELIST_STRINGS_070` alias for mislabeled Mako 070
- `src_custom/duel_voice_portrait_table.inc` — Strings → `PORTRAIT_STRINGS`
- `events/scripts/map_39_state_03.c` — duel uses `DUELIST_STRINGS_070`

**Outcome:** `make` OK. 27 new clips registered.

**Open / next:** Serenity has no story duel ID (raw voice id 200 / debug only); playtest new VO.
