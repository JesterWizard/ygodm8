# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## POWER_FILTER (spell)
- file: `src_custom/spell_effects/power_filter.c`
- clone: `src_custom/spell_effects/court_of_justice.c` (COURT_OF_JUSTICE)
- text: Neither player can Special Summon monsters with 1000 or less ATK. Neither player can Special Summon monsters with 1000 or less ATK.

## OVERFLOWING_TREASURE (spell)
- file: `src_custom/spell_effects/overflowing_treasure.c`
- clone: `src_custom/spell_effects/polymerization.c` (POLYMERIZATION)
- text: ATK +500 per card in both hands. For one turn, boost the ATK of one monster on your field by 500 points for every card in each player's hand.

## DARK_MAGIC_VEIL (spell)
- file: `src_custom/spell_effects/dark_magic_veil.c`
- clone: `src_custom/spell_effects/twin_swords_of_flashing_light_tryce.c` (TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE)
- text: Pay 1000 LP; Special Summon 1 DARK Spellcaster from hand or GY. Pay 1000 LP; Special Summon 1 DARK Spellcaster-Type monster from your hand or Graveyard.

## POT_OF_AVARICE (spell)
- file: `src_custom/spell_effects/pot_of_avarice.c`
- clone: `src_custom/spell_effects/pot_of_extravagance.c` (POT_OF_EXTRAVAGANCE)
- text: Target 5 monsters in your GY; shuffle all 5 into the Deck, then draw 2 cards. Target 5 monsters in your GY; shuffle all 5 into the Deck, then draw 2 cards.
