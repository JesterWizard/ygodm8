# CARD_STATE — latest session

**Last worked on:** 2026-07-04 — AI spell/trap wipe gating + Despair Uranus ATK fix

**Files touched:**
- `src_custom/ai_spell_targets.c`, `include/ai_spell_targets.h`
- `src_custom/ai_hooks.c`, `src_custom/ai_sim_fast.c`
- `src_custom/permanent_effects/the_despair_uranus.c`
- `tests/host/test_ai_spell_targets.py`, `tests/host/test_the_despair_uranus.py`

**Outcome:** AI skips Harpie's Feather Duster / Heavy Storm / Raigeki / Dark Hole when they have no valid targets (shared `AiNormalSpellHasActivationTargets`; fast-AI quick reject too). Uranus ATK boost now treats attack-position summons as active and counts owner face-up backrow Spell/Traps ×300. Protection still applies while Uranus is in monster zone (face-down OK). `make test-cards-link` passes.

**Open / next:**
- Playtest opponent AI with empty player backrow + set Feather Duster; Uranus ATK with multiple face-up backrow cards
