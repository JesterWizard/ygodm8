# Effect work pack 02 (3 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ARMED_DRAGON_LV3 (turn)
- file: `src_custom/turn_effects/armed_dragon_lv3.c`
- clone: `src_custom/turn_effects/sinister_serpent.c` (SINISTER_SERPENT)
- text: During your Standby Phase: You can send this card to the GY; Special Summon 1 Armed Dragon LV5 from your hand or Deck. During your Standby Phase: You can send this card to the GY; Special Summon 1 Armed Dragon LV5 from your hand or Deck.

## REPTILIANNE_SCYLLA (battle)
- file: `src_custom/battle_effects/reptilianne_scylla.c`
- clone: `src_custom/battle_effects/cyber_barrier_dragon.c` (CYBER_BARRIER_DRAGON)
- text: If destroys 0 ATK by battle: SS that monster in Defense. If this card destroys a monster with 0 ATK by battle, you can Special Summon that monster from the Graveyard to your side of the field in face-up Defense Position. The effect(s) of that monster is negated.

## THE_WHITE_STONE_OF_ANCIENTS (turn)
- file: `src_custom/turn_effects/the_white_stone_of_ancients.c`
- clone: `src_custom/turn_effects/sinister_serpent.c` (SINISTER_SERPENT)
- text: End Phase: SS Blue-Eyes. Banish: add Blue-Eyes. Once per turn, during the End Phase, if this card is in the GY because it was sent there this turn: You can Special Summon 1 Blue-Eyes monster from your Deck. You can banish this card from your GY, then target 1 Blue-Eyes monster in your GY; add it to your hand. You can only use this effect of The White Stone of Ancients once per turn.
