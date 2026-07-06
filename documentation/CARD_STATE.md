# CARD_STATE — latest session

**Last worked on:** 2026-07-06 — Wicked Avatar lock arms on any normal summon (no tribute gate)

**Files touched:** `src_custom/permanent_effects/the_wicked_avatar.c`, `src_custom/tribute_hooks.c`, `tests/host/test_ai_spell_targets.py`

**Outcome:** Lock + popup_1 fire whenever Avatar is normal summoned to the field; tribute count / level no longer gate the effect. make test-cards-build passes.

**Open / next:** playtest summon Avatar → popup_1 → opponent Raigeki forbidden
