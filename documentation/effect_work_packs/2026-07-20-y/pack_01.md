# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GLORIOUS_ILLUSION (trap)
- file: `src_custom/trap_effects/glorious_illusion.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: Revive Lightsworn; mill 2; leave kill. Activate this card by targeting 1 Lightsworn monster in your Graveyard; Special Summon that target in face-up Attack Position. During each of your End Phases: Send the top 2 cards of your Deck to the Graveyard. When this card leaves the field, destroy that monster. When that monster leaves the field, destroy this card.

## ATTACK_AND_RECEIVE (trap)
- file: `src_custom/trap_effects/attack_and_receive.c`
- clone: `src_custom/trap_effects/coffin_seller.c` (COFFIN_SELLER)
- text: You can only activate this card when you take damage to your Life Points. Inflict 700 points of damage to your opponent' You can only activate this card when you take damage to your Life Points. Inflict 700 points of damage to your opponent's Life Points. Also, inflict 300 points of damage to your opponent's Life Points for each Attack and Receive card in your Graveyard.

## FORGOTTEN_TEMPLE_OF_THE_DEEP (trap)
- file: `src_custom/trap_effects/forgotten_temple_of_the_deep.c`
- clone: `src_custom/trap_effects/embodiment_of_apophis.c` (EMBODIMENT_OF_APOPHIS)
- text: While this card is on the field, this card's name becomes "Umi". Once per turn: You can target 1 Level 4 or lower Fish,  While this card is on the field, this card's name becomes Umi. Once per turn: You can target 1 Level 4 or lower Fish, Sea Serpent or Aqua-Type monster you control; banish that target. During your End Phase: Special Summon the monster(s) banished by this effect.

## ATTACK_GUIDANCE_ARMOR (trap)
- file: `src_custom/trap_effects/attack_guidance_armor.c`
- clone: `src_custom/trap_effects/attack_reflector_unit.c` (ATTACK_REFLECTOR_UNIT)
- text: When a monster declares an attack: Activate 1 of these effects;
* Destroy the attacking monster.
* Target 1 monster on When a monster declares an attack: Activate 1 of these effects; Destroy the attacking monster. Target 1 monster on either field, except the attacking monster; change the attack target to it and perform damage calculation. You can only activate 1 Attack Guidance Armor per turn.
