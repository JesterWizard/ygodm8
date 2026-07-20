# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## CUP_OF_ACE (spell)
- file: `src_custom/spell_effects/cup_of_ace.c`
- clone: `src_custom/spell_effects/card_destruction.c` (CARD_DESTRUCTION)
- optional template: `--fill draw_n CUP_OF_ACE`
- text: Coin toss: Heads you draw 2; Tails opponent draws 2. Toss a coin: Heads: Draw 2 cards. Tails: Your opponent draws 2 cards.

## GLADIATOR_PROVING_GROUND (spell)
- file: `src_custom/spell_effects/gladiator_proving_ground.c`
- clone: `src_custom/spell_effects/polymerization.c` (POLYMERIZATION)
- optional template: `--fill search GLADIATOR_PROVING_GROUND`
- text: Add 1 Level 4 or lower Gladiator Beast monster from your Deck to your hand. Add 1 Level 4 or lower Gladiator Beast monster from your Deck to your hand.

## THE_MELODY_OF_AWAKENING_DRAGON (spell)
- file: `src_custom/spell_effects/the_melody_of_awakening_dragon.c`
- clone: `src_custom/spell_effects/e_emergency_call.c` (E_EMERGENCY_CALL)
- optional template: `--fill search THE_MELODY_OF_AWAKENING_DRAGON`
- text: Discard 1; add up to 2 high-ATK Dragons. Discard 1 card; add up to 2 Dragon monsters with 3000 or more ATK and 2500 or less DEF from your Deck to your hand.

## ANCIENT_LEAF (spell)
- file: `src_custom/spell_effects/ancient_leaf.c`
- clone: `src_custom/spell_effects/card_destruction.c` (CARD_DESTRUCTION)
- optional template: `--fill draw_n ANCIENT_LEAF`
- text: If you have 9000 or more Life Points, you can pay 2000 Life Points to draw 2 cards. If you have 9000 or more Life Points, you can pay 2000 Life Points to draw 2 cards.
