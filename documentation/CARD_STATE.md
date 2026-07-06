# CARD_STATE — latest session

**Last worked on:** 2026-07-06 — Spell workflow: generated dispatch + activation gates

**Files touched:**
- `tools/generate_spell_effect_dispatch.py`, `tools/add_custom_card.py`, `tools/wire_card_effect.py`
- `src_custom/spell_effect_hooks.c`, `src_custom/code_8043EF4_hooks.c`
- `src_custom/generated/spell_effect_dispatch_*.inc`, `src_custom/generated/spell_activation_gates.c`
- `include/spell_activation_gates.h`

**Outcome:** `make test-cards-build` passes; new spells need manifest + effect `.c` only (no dispatcher/header/gate edits)

**Open / next:**
- playtest Trade-In activation gate still works via generated table
