# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## EVIL_HERO_INFERNAL_GAINER (activated)
- file: `src_custom/activated_effects/evil_hero_infernal_gainer.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: Banish: Fiend you control can attack twice. Returns on 2nd Standby. During your Main Phase 1: You can banish this card from the field, then target 1 Fiend monster you control; that target can make a second attack during each Battle Phase while you control it face-up. Once per turn, during your second Standby Phase after this card was banished to activate this effect: Special Summon this card in Attack Position.

## DESTINY_HERO_DASHER (activated)
- file: `src_custom/activated_effects/destiny_hero_dasher.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: Destiny HERO - Dasher Once per turn: You can Tribute 1 other monster; this card gains 1000 ATK until the End Phase. If this card attacks, change it to Defense Position at the end of the Battle Phase. One time only, when you draw a Monster Card during your Draw Phase while this card is in your Graveyard: You can reveal it; Special Summon it. This card must be in the Graveyard to activate and to resolve this effect.

## THE_AGENT_OF_JUDGMENT_SATURN (activated)
- file: `src_custom/activated_effects/the_agent_of_judgment_saturn.c`
- clone: `src_custom/activated_effects/dark_strike_fighter.c` (DARK_STRIKE_FIGHTER)
- text: While your Life Points are higher than your opponent's, you can Tribute this card to inflict damage to your opponent equ While your Life Points are higher than your opponent's, you can Tribute this card to inflict damage to your opponent equal to the difference. If you do not control a face-up The Sanctuary in the Sky, this effect is not applied. You cannot conduct your Battle Phase the turn you activate this effect.

## REESHADDOLL_WENDI (activated)
- file: `src_custom/activated_effects/reeshaddoll_wendi.c`
- clone: `src_custom/activated_effects/chimeratech_megafleet_dragon.c` (CHIMERATECH_MEGAFLEET_DRAGON)
- text: FLIP: SS Shaddoll from Deck. Sent by effect: SS face-down. FLIP: You can Special Summon 1 Shaddoll monster from your Deck in face-up or face-down Defense Position, except Reeshaddoll Wendi. If this card is sent to the GY by a card effect: You can Special Summon 1 Shaddoll monster from your Deck in face-down Defense Position, except Reeshaddoll Wendi. You can only use 1 Reeshaddoll Wendi effect per turn, and only once that turn.
