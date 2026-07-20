# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## NEO_SPACE (spell)
- file: `src_custom/spell_effects/neo_space.c`
- clone: `src_custom/spell_effects/realm_of_light.c` (REALM_OF_LIGHT)
- text: Neos Fusions +500; stay on field. Elemental HERO Neos and all Fusion Monsters that specifically list Elemental HERO Neos as a Fusion Material gain 500 ATK. Fusion Monsters that specifically list Elemental HERO Neos as a Fusion Material do not have to activate their effects during the End Phase that shuffle them into the Extra Deck.

## MIRAGE_OF_NIGHTMARE (spell)
- file: `src_custom/spell_effects/mirage_of_nightmare.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Opponent Standby: Draw until 4. Your Standby: Randomly discard equal number (or whole hand). Once per turn, during your opponent's Standby Phase: Draw cards until you have 4 cards in your hand. If you do, during your next Standby Phase after that: Randomly discard the same number of cards you drew (or your entire hand, if you do not have enough cards).

## HERO_FLASH (spell)
- file: `src_custom/spell_effects/hero_flash.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Banish H - Heated Heart, E - Emergency Call, R - Righteous Justice and O - Oversoul from your Graveyard;  Banish H - Heated Heart, E - Emergency Call, R - Righteous Justice and O - Oversoul from your Graveyard; Special Summon 1 Elemental HERO Normal Monster from your Deck. All Elemental HERO Normal Monsters you currently control can attack your opponent directly this turn.

## FUSION_DEPLOYMENT (spell)
- file: `src_custom/spell_effects/fusion_deployment.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Reveal Fusion; SS 1 listed material. ED lock except Fusions. Reveal 1 Fusion Monster in your Extra Deck and Special Summon, from your hand or Deck, 1 of the Fusion Materials whose name is specifically listed on that card, also you cannot Special Summon monsters from the Extra Deck, except Fusion Monsters, the turn you activate this card. You can only activate 1 Fusion Deployment per turn.
