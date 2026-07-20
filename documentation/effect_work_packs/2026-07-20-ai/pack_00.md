# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## THUNDER_END_DRAGON (activated)
- file: `src_custom/activated_effects/thunder_end_dragon.c`
- clone: `src_custom/activated_effects/elemental_hero_tempest.c` (ELEMENTAL_HERO_TEMPEST)
- text: 2 Level 8 Normal Monsters
Once per turn: You can detach 1 Xyz Material from this card; destroy all other monsters on the 2 Level 8 Normal Monsters Once per turn: You can detach 1 Xyz Material from this card; destroy all other monsters on the field.

## NEO_SPACIAN_DARK_PANTHER (activated)
- file: `src_custom/activated_effects/neo_spacian_dark_panther.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: Copy opp monster name and effects. Once per turn: You can target 1 face-up monster your opponent controls; until the End Phase, this card's name becomes that monster's original name, also replace this effect with that monster's original effects (if any).

## DARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT (activated)
- file: `src_custom/activated_effects/dark_magician_girl_the_dragon_knight.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: Dark Magician Girl + 1 Dragon monster Must be Fusion Summoned with the above Fusion Materials or with The Eye of Timaeus. Once per turn (Quick Effect): You can send 1 card from your hand to the GY, then target 1 face-up card on the field; destroy that target.

## BABYCERASAURUS (activated)
- file: `src_custom/activated_effects/babycerasaurus.c`
- clone: `src_custom/activated_effects/ehren_lightsworn_monk.c` (EHREN_LIGHTSWORN_MONK)
- text: If this card is destroyed by a card effect and sent to the Graveyard: Special Summon 1 Level 4 or lower Dinosaur-Type mo If this card is destroyed by a card effect and sent to the Graveyard: Special Summon 1 Level 4 or lower Dinosaur-Type monster from your Deck.
