# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SOLAR_RECHARGE (spell)
- file: `src_custom/spell_effects/solar_recharge.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: Discard LS; draw 2; mill 2. Discard 1 Lightsworn monster; draw 2 cards, then send the top 2 cards of your Deck to the GY.

## SNAKE_RAIN (spell)
- file: `src_custom/spell_effects/snake_rain.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: Discard 1; send 4 Reptiles from Deck to GY. Discard 1 card. Select 4 Reptile-Type monsters from your Deck and send them to the Graveyard.

## SHARE_THE_PAIN (spell)
- file: `src_custom/spell_effects/share_the_pain.c`
- clone: `src_custom/spell_effects/dark_room_of_nightmare.c` (DARK_ROOM_OF_NIGHTMARE)
- text: Tribute 1 monster; make your opponent Tribute 1 monster (for no effect). Tribute 1 monster; make your opponent Tribute 1 monster (for no effect).

## CONVERT_CONTACT (spell)
- file: `src_custom/spell_effects/convert_contact.c`
- clone: `src_custom/spell_effects/guardian_treasure.c` (GUARDIAN_TREASURE)
- text: Send 2 Neo-Spacians; draw 2. If you control no monsters: Send 2 Neo-Spacian monsters (1 from your hand and 1 from your Deck) to the GY, then draw 2 cards.
