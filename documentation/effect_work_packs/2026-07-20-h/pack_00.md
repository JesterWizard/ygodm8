# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## FORBIDDEN_CHALICE (spell)
- file: `src_custom/spell_effects/forbidden_chalice.c`
- clone: `src_custom/spell_effects/h_heated_heart.c` (H_HEATED_HEART)
- text: Target 1 face-up monster on the field; until the end of this turn, that target gains 400 ATK, but its effects are negate Target 1 face-up monster on the field; until the end of this turn, that target gains 400 ATK, but its effects are negated.

## THE_SHALLOW_GRAVE (spell)
- file: `src_custom/spell_effects/the_shallow_grave.c`
- clone: `src_custom/spell_effects/the_a_forces.c` (THE_A_FORCES)
- text: Each player targets 1 monster in their own GY; each player Special Summons the target from their GY in face-down Defense Each player targets 1 monster in their own GY; each player Special Summons the target from their GY in face-down Defense Position.

## OIL (spell)
- file: `src_custom/spell_effects/oil.c`
- clone: `src_custom/spell_effects/twin_swords_of_flashing_light_tryce.c` (TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE)
- text: Target up to 2 Level 4 or lower FIRE monsters with different names in your GY; add them to your hand. You can only activ Target up to 2 Level 4 or lower FIRE monsters with different names in your GY; add them to your hand. You can only activate 1 Oil per turn.

## INFERNO_TEMPEST (spell)
- file: `src_custom/spell_effects/inferno_tempest.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: When you take 3000 or more Battle Damage from 1 attack, you can activate this card. Remove all monsters in each player's When you take 3000 or more Battle Damage from 1 attack, you can activate this card. Remove all monsters in each player's Deck and Graveyard from play.
