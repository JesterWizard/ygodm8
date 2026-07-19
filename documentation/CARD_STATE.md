# CARD_STATE — latest session

**Last worked on:** 2026-07-19 — Spellbinding gate + always light-score attacks

**Files touched:**
- `src_custom/ai_spell_targets.c` — Spellbinding Circle / Shadow Spell / Dark-Piercing Light need real targets
- `src_custom/ai_sim_fast.c` — light-score attacks even with set backrow; `AiSimFoundLethal`
- `src_custom/ai_hooks.c` — skip full-sim budget once lethal already scored
- `include/ai_sim.h`, tests, `documentation/fast-ai-architecture.md`

**Outcome:** `make` OK; host AI spell-target tests pass.

**Open / next:** Playtest empty-field Circle no longer forced; turns with set backrow should feel faster.
