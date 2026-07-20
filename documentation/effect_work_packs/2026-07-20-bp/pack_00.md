# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## NEO_SPACIAN_FLARE_SCARAB (permanent)
- file: `src_custom/permanent_effects/neo_spacian_flare_scarab.c`
- clone: `src_custom/permanent_effects/elemental_hero_sunrise.c` (ELEMENTAL_HERO_SUNRISE)
- text: +400 ATK per opp Spell/Trap. Gains 400 ATK for each Spell/Trap your opponent controls.

## CANNONBALL_SPEAR_SHELLFISH (permanent)
- file: `src_custom/permanent_effects/cannonball_spear_shellfish.c`
- clone: `src_custom/permanent_effects/elemental_hero_sunrise.c` (ELEMENTAL_HERO_SUNRISE)
- text: While Umi is face-up, this card is unaffected by any Spell Cards. While Umi is face-up on the field, this card is unaffected by any Spell Cards.

## ARMAGEDDON_KNIGHT (permanent)
- file: `src_custom/permanent_effects/armageddon_knight.c`
- clone: `src_custom/permanent_effects/des_feral_imp.c` (DES_FERAL_IMP)
- text: When this card is Summoned: You can send 1 DARK monster from your Deck to the GY. When this card is Summoned: You can send 1 DARK monster from your Deck to the GY.

## REPTILIANNE_GARDNA (permanent)
- file: `src_custom/permanent_effects/reptilianne_gardna.c`
- clone: `src_custom/permanent_effects/des_feral_imp.c` (DES_FERAL_IMP)
- text: If destroyed: add 1 Reptilianne from Deck to hand. When this card you control is destroyed and sent to the Graveyard, add 1 Reptilianne monster from your Deck to your hand.
