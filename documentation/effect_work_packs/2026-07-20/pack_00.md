# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DESTINY_DRAW (spell)
- file: `src_custom/spell_effects/destiny_draw.c`
- clone: `src_custom/spell_effects/card_destruction.c` (CARD_DESTRUCTION)
- optional template: `--fill draw_n DESTINY_DRAW`
- text: Discard 1 Destiny HERO card; draw 2 cards. Discard 1 Destiny HERO card; draw 2 cards.

## MORAY_OF_GREED (spell)
- file: `src_custom/spell_effects/moray_of_greed.c`
- clone: `src_custom/spell_effects/guardian_treasure.c` (GUARDIAN_TREASURE)
- optional template: `--fill draw_n MORAY_OF_GREED`
- text: Shuffle 2 WATER monsters from your hand into the Deck, then draw 3 cards. Shuffle 2 WATER monsters from your hand into the Deck, then draw 3 cards.

## CHARGE_OF_THE_LIGHT_BRIGADE (spell)
- file: `src_custom/spell_effects/charge_of_the_light_brigade.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- optional template: `--fill search CHARGE_OF_THE_LIGHT_BRIGADE`
- text: Mill 3; add Level 4- Lightsworn. Send the top 3 cards of your Deck to the Graveyard; add 1 Level 4 or lower Lightsworn monster from your Deck to your hand.

## POISON_OF_THE_OLD_MAN (spell)
- file: `src_custom/spell_effects/poison_of_the_old_man.c`
- clone: `src_custom/spell_effects/chain_energy.c` (CHAIN_ENERGY)
- optional template: `--fill burn POISON_OF_THE_OLD_MAN`
- text: Activate 1 of these effects: Gain 1200 LP or inflict 800 damage to your opponent. Activate 1 of these effects; Gain 1200 LP. Inflict 800 damage to your opponent.
