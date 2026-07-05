# CARD_STATE — latest session

**Last worked on:** 2026-07-05 — Premature Burial (equip-linked GY revival spell)

**Files touched:**
- `tools/card_data_manifest.json`
- `configs/runtime.c`
- `include/premature_burial.h`
- `src_custom/spell_effects/premature_burial.c`
- `src_custom/spell_effects/dynamic_equip.c`
- `src_custom/spell_effect_hooks.c`
- `src_custom/code_8043EF4_hooks.c`

**Outcome:** `make test-cards-build` passes. Pay 800 LP, revive own GY top monster, spell stays on field equipped; dynamic equip destroys the other when either leaves.

**Open / next:**
- Per-player GY selector UI for Premature Burial (and Call of the Haunted)
- Wire E-HERO banish-counting effects to `RemovedFromPlay_*` API
