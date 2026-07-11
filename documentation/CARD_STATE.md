# CARD_STATE — latest session

**Last worked on:** 2026-07-11 — Added 10 cards (THE_SHALLOW_GRAVE through TORNADO_WALL) with stubbed effects

**Files touched:**
- `tools/card_data_manifest.json`
- `src_custom/monster_effect_hooks.c`
- `src_custom/permanent_effect_hooks.c`
- `src_custom/spell_effects/the_shallow_grave.c`
- `src_custom/spell_effects/toon_world.c`
- `src_custom/activated_effects/theinen_the_great_sphinx.c`
- `src_custom/activated_effects/thestalos_the_firestorm_monarch.c`
- `src_custom/activated_effects/thunder_dragon_titan.c`
- `src_custom/activated_effects/timaeus_the_knight_of_destiny.c`
- `src_custom/activated_effects/time_magic_hammer.c`
- `src_custom/activated_effects/tornado_bird.c`
- `src_custom/permanent_effects/thunder_dragon_colossus.c`
- `src_custom/trap_effects/tornado_wall.c`

**Outcome:** make clean && make passes; 10 cards added to manifest (costs ranged 15-500), art already present in 80x80/ and 512x512/, effect stubs created and wired, monster_effect_hooks.c and permanent_effect_hooks.c fixed for wiring script issues; CARD_PROGRESS.md updated (in-game: 551->571)

**Open / next:**
- implement effect logic for the 10 stubbed effects
- or tackle next batch from TRAP_DUSTSHOOT onward
