# CARD_STATE — latest session

**Last worked on:** 2026-07-20 — Effect data system follow-ups (OPT / Phase 4b / events / scripts)

**Outcome:** Migrated all `*UsedThisTurn APPEND_DATA` flags to `EffectOpt_*`. Phase 4b JSON→codegen live (`effect_scripts_manifest.json` → `effect_scripts_table.inc`); Ancient Leaf added as script pilot. `ON_DAMAGE_CALC` emitted from pending battle stat refresh; `ON_FIELD_CHANGE` drives Rivalry/Level Limit/Amazoness/Ring. Legacy AI meta map expanded. Host test `test_effect_followups.py`.

**Open / next:** Thin redundant `Duel_Check*` call sites; more JSON scripts; subscribe damage-calc ATK boosts to `ON_DAMAGE_CALC`.
