# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## NEO_SPACIAN_GRAND_MOLE (battle)
- file: `src_custom/battle_effects/neo_spacian_grand_mole.c`
- clone: `src_custom/battle_effects/harpie_lady_3.c` (HARPIE_LADY_3)
- text: Battle: bounce both to hand. At the start of the Damage Step, if this card battles an opponent's monster: You can return both the opponent's monster and this card to the hand.

## LIGHTNING_WARRIOR (battle)
- file: `src_custom/battle_effects/lightning_warrior.c`
- clone: `src_custom/battle_effects/harpie_lady_3.c` (HARPIE_LADY_3)
- text: If destroys by battle: 300 damage per card in opp hand. 1 Tuner + 1 or more non-Tuner monsters If this card destroys an opponent's monster by battle and sends it to the Graveyard: Inflict 300 damage to your opponent for each card in your opponent's hand.

## NEO_SPACIAN_GLOW_MOSS (battle)
- file: `src_custom/battle_effects/neo_spacian_glow_moss.c`
- clone: `src_custom/battle_effects/harpie_lady_3.c` (HARPIE_LADY_3)
- text: Opp draw; apply by card type. If this card attacks or is attacked: Your opponent draws 1 card and shows it, then, based on its type apply this effect. Monster: End the Battle Phase of this turn. Spell: If this card is attacking, you can change it to a direct attack instead. Trap: Change this card to Defense Position.

## NEO_SPACIAN_TWINKLE_MOSS (battle)
- file: `src_custom/battle_effects/neo_spacian_twinkle_moss.c`
- clone: `src_custom/battle_effects/cyber_barrier_dragon.c` (CYBER_BARRIER_DRAGON)
- text: NEX only; draw; apply by type. This card's name is also treated as Neo-Spacian Glow Moss. This card cannot be Special Summoned except with NEX. When this card attacks or is attacked, draw 1 card. Reveal that card, and based on its type apply the proper effect: Monster: End the Battle Phase. Spell: You can change this card's attack to a direct attack. Trap: This monster is changed to Defense Position.
