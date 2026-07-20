# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SKILLED_DARK_MAGICIAN (activated)
- file: `src_custom/activated_effects/skilled_dark_magician.c`
- clone: `src_custom/activated_effects/chimeratech_fortress_dragon.c` (CHIMERATECH_FORTRESS_DRAGON)
- text: Each time a Spell Card is activated, place 1 Spell Counter on this card when that Spell resolves (max. 3). You can Tribu Each time a Spell Card is activated, place 1 Spell Counter on this card when that Spell resolves (max. 3). You can Tribute this card with 3 Spell Counters on it; Special Summon 1 Dark Magician from your hand, Deck, or GY.

## SHADDOLL_HEDGEHOG (activated)
- file: `src_custom/activated_effects/shaddoll_hedgehog.c`
- clone: `src_custom/activated_effects/shaddoll_squamata.c` (SHADDOLL_SQUAMATA)
- text: FLIP: add Shaddoll S/T. Sent by effect: add Shaddoll monster. FLIP: You can add 1 Shaddoll Spell/Trap from your Deck to your hand. If this card is sent to the GY by a card effect: You can add 1 Shaddoll monster from your Deck to your hand, except Shaddoll Hedgehog. You can only use 1 Shaddoll Hedgehog effect per turn, and only once that turn.

## MORPHTRONIC_BOOMBOXEN (activated)
- file: `src_custom/activated_effects/morphtronic_boomboxen.c`
- clone: `src_custom/activated_effects/atlantean_attack_squad.c` (ATLANTEAN_ATTACK_SQUAD)
- text: - While in Attack Position, this card can attack twice during each Battle Phase.
- Once per turn, while in Defense Posit - While in Attack Position, this card can attack twice during each Battle Phase. - Once per turn, while in Defense Position, when a face-up Morphtronic monster you control is targeted for an attack: You can negate the attack.

## GREAT_POSEIDON_BEETLE (activated)
- file: `src_custom/activated_effects/great_poseidon_beetle.c`
- clone: `src_custom/activated_effects/atlantean_attack_squad.c` (ATLANTEAN_ATTACK_SQUAD)
- text: If this card targets an opponent's face-up Attack Position monster for an attack, and that monster is not destroyed by t If this card targets an opponent's face-up Attack Position monster for an attack, and that monster is not destroyed by the battle, this card can attack the same monster again in a row. This effect can only be used twice per turn.
