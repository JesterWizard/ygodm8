# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## CHRYSALIS_CHICKY (activated)
- file: `src_custom/activated_effects/chrysalis_chicky.c`
- clone: `src_custom/activated_effects/chrysalis_dolphin.c` (CHRYSALIS_DOLPHIN)
- text: Tribute; SS Air Hummingbird. You can Tribute this card while Neo Space is on the field to Special Summon 1 Neo-Spacian Air Hummingbird from your hand or Deck.

## D_D_WARRIOR (activated)
- file: `src_custom/activated_effects/d_d_warrior.c`
- clone: `src_custom/activated_effects/boot_up_soldier_dread_dynamo.c` (BOOT_UP_SOLDIER_DREAD_DYNAMO)
- text: After damage calculation, banish the battled monster and this card. After damage calculation, when this card battles a monster: Banish that monster, also banish this card.

## HELIOS_THE_PRIMORDIAL_SUN (activated)
- file: `src_custom/activated_effects/helios_the_primordial_sun.c`
- clone: `src_custom/activated_effects/venom_serpent.c` (VENOM_SERPENT)
- text: This card's ATK and DEF are each equal to the number of removed from play monsters x 100. This card's ATK and DEF are each equal to the number of removed from play monsters x 100.

## TYRANNO_INFINITY (activated)
- file: `src_custom/activated_effects/tyranno_infinity.c`
- clone: `src_custom/activated_effects/venom_serpent.c` (VENOM_SERPENT)
- text: The original ATK of this card is the number of your banished Dinosaur-Type monsters x 1000. The original ATK of this card is the number of your banished Dinosaur-Type monsters x 1000.
