# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## WETLANDS (spell)
- file: `src_custom/spell_effects/wetlands.c`
- text: All Aqua-Type/WATER/Level 2 or lower monsters gain 1200 ATK. All Aqua-Type/WATER/Level 2 or lower monsters gain 1200 ATK.

## MAGICAL_STONE_EXCAVATION (spell)
- file: `src_custom/spell_effects/magical_stone_excavation.c`
- clone: `src_custom/spell_effects/twin_swords_of_flashing_light_tryce.c` (TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE)
- text: Discard 2 cards, then target 1 Spell in your GY; add it to your hand. Discard 2 cards, then target 1 Spell in your GY; add it to your hand.

## BURDEN_OF_THE_MIGHTY (spell)
- file: `src_custom/spell_effects/burden_of_the_mighty.c`
- clone: `src_custom/spell_effects/united_we_stand.c` (UNITED_WE_STAND)
- text: Each face-up monster your opponent controls loses 100 ATK x its own Level. Each face-up monster your opponent controls loses 100 ATK x its own Level.

## COCOON_PARTY (spell)
- file: `src_custom/spell_effects/cocoon_party.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: SS Chrysalis per Neo-Spacian in GY. Special Summon 1 Chrysalis monster from your Deck for each Neo-Spacian monster with a different name in your Graveyard.
