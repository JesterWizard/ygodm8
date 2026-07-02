# CARD_STATE — latest session

**Last worked on:** 2026-07-02 — Terra Firma duel-loss fix (dedicated cursor)

**Files touched:**
- `src_custom/activated_effects/elemental_hero_terra_firma.c`
- `include/elemental_hero_terra_firma.h`
- `src_custom/code_8043EF4_hooks.c`
- `src_custom/monster_effect_hooks.c`
- `src_custom/card_passives/chaos_command_magician.c`

**Outcome:** Tribute targeting uses dedicated `DUEL_CURSOR_TERRA_FIRMA_TARGET` (Cannon Soldier / BLS pattern) instead of shared PickZone; validation uses `gMonEffect` origin; ATK boost refreshes overlays; effect wrapped in Begin/End monster resolve; make test-cards-build passes

**Open / next:** User rebuild ROM — fuse TF, summon ally, activate tribute; confirm no defeat screen and ATK rises until end phase
