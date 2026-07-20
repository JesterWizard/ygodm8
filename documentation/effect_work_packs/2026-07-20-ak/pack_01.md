# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ZERADIAS_HERALD_OF_HEAVEN (activated)
- file: `src_custom/activated_effects/zeradias_herald_of_heaven.c`
- clone: `src_custom/activated_effects/amazoness_sage.c` (AMAZONESS_SAGE)
- text: You can discard this card to the GY; add 1 "The Sanctuary in the Sky" from your Deck to your hand. If "The Sanctuary in  You can discard this card to the GY; add 1 The Sanctuary in the Sky from your Deck to your hand. If The Sanctuary in the Sky is not on the field, destroy this card.

## TURBO_CANNON (activated)
- file: `src_custom/activated_effects/turbo_cannon.c`
- clone: `src_custom/activated_effects/elemental_hero_lady_heat.c` (ELEMENTAL_HERO_LADY_HEAT)
- text: Turbo Rocket + 1 or more non-Tuner monsters
Once per turn, you can destroy 1 face-up monster on the field and inflict  Turbo Rocket + 1 or more non-Tuner monsters Once per turn, you can destroy 1 face-up monster on the field and inflict damage to its controller equal to half of its ATK.

## RYKO_TWILIGHTSWORN_FIGHTER (activated)
- file: `src_custom/activated_effects/ryko_twilightsworn_fighter.c`
- clone: `src_custom/activated_effects/ehren_lightsworn_monk.c` (EHREN_LIGHTSWORN_MONK)
- text: Banish LS to banish field; mill 3. If this card is Normal Summoned or flipped face-up: You can banish 1 Lightsworn monster from your hand or GY; banish 1 card on the field. Once per turn, if your other Lightsworn monster's effect is activated: Send the top 3 cards of your Deck to the GY.

## ELEMENTAL_HERO_MARINE_NEOS (activated)
- file: `src_custom/activated_effects/elemental_hero_marine_neos.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: Destroy 1 random card in opp hand. Elemental HERO Neos + Neo-Spacian Marine Dolphin Must first be Special Summoned (from your Extra Deck) by shuffling the above cards you control into the Deck. (You do not use Polymerization.) Once per turn: You can destroy 1 random card in your opponent's hand.
