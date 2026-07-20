# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## EVOLZAR_DOLKKA (activated)
- file: `src_custom/activated_effects/evolzar_dolkka.c`
- clone: `src_custom/activated_effects/amazoness_sage.c` (AMAZONESS_SAGE)
- text: 2 Level 4 Dinosaur-Type monsters
During either player's turn, when a monster effect activates: You can detach 1 Xyz Mate 2 Level 4 Dinosaur-Type monsters During either player's turn, when a monster effect activates: You can detach 1 Xyz Material from this card; negate the activation, and if you do, destroy that monster.

## GRAVEKEEPERS_CHIEF (activated)
- file: `src_custom/activated_effects/gravekeepers_chief.c`
- clone: `src_custom/activated_effects/gravekeepers_descendant.c` (GRAVEKEEPERS_DESCENDANT)
- text: You can only control 1 face-up "Gravekeeper's Chief". Your GY is unaffected by "Necrovalley". When this card is Tribute  You can only control 1 face-up Gravekeeper's Chief. Your GY is unaffected by Necrovalley. When this card is Tribute Summoned: You can target 1 Gravekeeper's monster in your GY; Special Summon that target.

## DESTINY_HERO_DIAMOND_DUDE (activated)
- file: `src_custom/activated_effects/destiny_hero_diamond_dude.c`
- clone: `src_custom/activated_effects/amazoness_trainee.c` (AMAZONESS_TRAINEE)
- text: Destiny HERO - Diamond Dude Once per turn: You can excavate the top card of your Deck, and if it is a Normal Spell, send it to the GY, otherwise place it on the bottom of your Deck. During the Main Phase of your next turn, you can activate the effect of that Spell in your GY (even if you no longer control this face-up card).

## SHADDOLL_SQUAMATA (activated)
- file: `src_custom/activated_effects/shaddoll_squamata.c`
- clone: `src_custom/activated_effects/shaddoll_dragon.c` (SHADDOLL_DRAGON)
- text: FLIP: destroy 1. Sent by effect: send 1 Shaddoll from Deck to GY. FLIP: You can target 1 monster on the field; destroy it. If this card is sent to the GY by a card effect: You can send 1 Shaddoll card from your Deck to the GY, except Shaddoll Squamata. You can only use 1 Shaddoll Squamata effect per turn, and only once that turn.
