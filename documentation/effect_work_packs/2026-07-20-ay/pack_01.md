# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GRAVEKEEPERS_AMBUSHER (activated)
- file: `src_custom/activated_effects/gravekeepers_ambusher.c`
- clone: `src_custom/activated_effects/gravekeepers_spiritualist.c` (GRAVEKEEPERS_SPIRITUALIST)
- text: When this card is flipped face-up: You can target 1 card in your opponent's GY; place that target on the bottom of their When this card is flipped face-up: You can target 1 card in your opponent's GY; place that target on the bottom of their Deck. If this card is sent from the field to the GY after being flipped face-up: You can target 1 Necrovalley card in your GY; add that target to your hand. These effects are unaffected by Necrovalley.

## MICHAEL_THE_ARCH_LIGHTSWORN (activated)
- file: `src_custom/activated_effects/michael_the_arch_lightsworn.c`
- clone: `src_custom/activated_effects/amazoness_trainee.c` (AMAZONESS_TRAINEE)
- text: Banish for LP; recycle LS; mill 3. 1 Tuner + 1 or more non-Tuner LIGHT monsters Once per turn: You can pay 1000 LP, then target 1 card on the field; banish that target. When this card is destroyed: You can target any number of other Lightsworn monsters in your Graveyard; shuffle them into the Deck, and if you do, you gain 300 LP for each returned card. Once per turn, during your End Phase: Send the top 3 cards of your Deck to the Graveyard.

## ANCIENT_GEAR_KNIGHT (activated)
- file: `src_custom/activated_effects/ancient_gear_knight.c`
- clone: `src_custom/activated_effects/ancient_gear_beast.c` (ANCIENT_GEAR_BEAST)
- text: This card is treated as a Normal Monster while face-up on the field or in the Graveyard. While this card is a Normal Mon This card is treated as a Normal Monster while face-up on the field or in the Graveyard. While this card is a Normal Monster on the field, you can Normal Summon it to have it become an Effect Monster with this effect. - If this card attacks, your opponent cannot activate any Spell/Trap Cards until the end of the Damage Step.

## PUNISHMENT_DRAGON (activated)
- file: `src_custom/activated_effects/punishment_dragon.c`
- clone: `src_custom/activated_effects/chimeratech_megafleet_dragon.c` (CHIMERATECH_MEGAFLEET_DRAGON)
- text: SS via banished LS; shuffle; mill 4. Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by possessing 4 or more banished Lightsworn monsters with different names. Once per turn (Quick Effect): You can pay 1000 LP; shuffle into the Decks, all cards in the GYs and all face-up banished cards, except Lightsworn monsters. Once per turn, if your Lightsworn monster's effect is activated: Send the top 4 cards of your Deck to the GY.
