# CARD_STATE — latest session

**Last worked on:** 2026-07-03 — Fixed Plasma Vice crash on hand discard selection

**Files touched:**
- `src_custom/activated_effects/elemental_hero_plasma_vice.c` — dedicated cursor + `sub_8041E70(PLAYER_HAND, targetRow)` after discard (Wild Wingman pattern)
- `include/elemental_hero_plasma_vice.h`
- `src_custom/code_8043EF4_hooks.c`, `monster_effect_hooks.c`, `chaos_command_magician.c`

**Outcome:** `make test-cards-build` passes. Hand pick no longer corrupts field scroll before destroy targeting.

**Open / next:**
- Playtest Plasma Vice: discard hand card → target opponent ATK monster
