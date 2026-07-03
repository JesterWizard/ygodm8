# CARD_STATE — latest session

**Last worked on:** 2026-07-04 — Fix Blazeman popup_2 blocked by on-summon once-per-turn

**Files touched:**
- `src_custom/activated_effects/elemental_hero_blazeman.c`
- `tools/card_data_manifest.json`

**Outcome:** make test-cards-link passes; on-summon no longer sets effectUsedThisTurn; menu effect uses gFixedZones

**Open / next:**
- playtest: NS popup_1 then same-turn effect menu popup_2 + discard
