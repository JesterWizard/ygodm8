# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MACRO_COSMOS (trap)
- file: `src_custom/trap_effects/macro_cosmos.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: When this card resolves: You can Special Summon 1 Helios - The Primordial Sun from your hand or Deck. While this card  When this card resolves: You can Special Summon 1 Helios - The Primordial Sun from your hand or Deck. While this card is face-up on the field, any card sent to the Graveyard is banished instead.

## D_TIME (trap)
- file: `src_custom/trap_effects/d_time.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: When a face-up Elemental HERO monster you control leaves the field: Add 1 Destiny HERO monster from your Deck to you When a face-up Elemental HERO monster you control leaves the field: Add 1 Destiny HERO monster from your Deck to your hand whose Level is less than or equal to that Elemental HERO monster's original Level.

## DAMAGE_EQUALS_REPTILE (trap)
- file: `src_custom/trap_effects/damage_equals_reptile.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: Once per turn, when you take Battle Damage from a battle involving a Reptile-Type monster, you can Special Summon 1 Rept Once per turn, when you take Battle Damage from a battle involving a Reptile-Type monster, you can Special Summon 1 Reptile-Type monster from your Deck with ATK less than or equal to the Battle Damage you took.

## EXCHANGE_OF_THE_SPIRIT (trap)
- file: `src_custom/trap_effects/exchange_of_the_spirit.c`
- clone: `src_custom/trap_effects/light_of_destruction.c` (LIGHT_OF_DESTRUCTION)
- text: If both players have 15 or more cards in their Graveyards: Pay 1000 LP; each player swaps the cards in their Graveyard w If both players have 15 or more cards in their Graveyards: Pay 1000 LP; each player swaps the cards in their Graveyard with the cards in their Deck, then shuffles their Deck. You can only activate 1 Exchange of the Spirit per Duel.
