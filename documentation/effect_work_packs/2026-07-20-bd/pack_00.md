# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DESTINY_HERO_DOOM_LORD (activated)
- file: `src_custom/activated_effects/destiny_hero_doom_lord.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: Once per turn: You can target 1 monster your opponent controls; banish that target. You cannot declare an attack the tur Once per turn: You can target 1 monster your opponent controls; banish that target. You cannot declare an attack the turn you activate this effect. You must control this face-up Attack Position card to activate and to resolve this effect. The banished monster returns to the opponent's side of the field, in the same battle position, during your 2nd Standby Phase after activatio

## MAZERA_DEVILLE (activated)
- file: `src_custom/activated_effects/mazera_deville.c`
- clone: `src_custom/activated_effects/test_tiger.c` (TEST_TIGER)
- text: Cannot NS. SS from hand by Tributing Warrior of Zera with Pandemonium. Opponent discards 3 random cards. This card cannot be Normal Summoned or Set. This card cannot be Special Summoned except by Tributing 1 face-up Warrior of Zera on your side of the field while Pandemonium is on the field. If Pandemonium is on your side of the field when you Special Summon this card, your opponent discards 3 random cards from their hand. If Pandemonium is not on your side of the field, this effect is not appli

## HELSHADDOLL_HOLLOW (activated)
- file: `src_custom/activated_effects/helshaddoll_hollow.c`
- clone: `src_custom/activated_effects/gravekeepers_ambusher.c` (GRAVEKEEPERS_AMBUSHER)
- text: FLIP: banish via Shaddoll mill. GY: mill Extra = field count. FLIP: You can target 1 face-up monster your opponent controls; send 1 Shaddoll monster with its same Attribute from your Extra Deck to the GY, and if you do, banish that monster. If this card is sent to the GY by card effect: You can send cards from the top of your Deck to the GY, equal to the number of different original Attributes among the monsters on the field. You can only use 1 Helshaddoll Hollow effect per turn, and only once t

## AROMASERAPHY_SWEET_MARJORAM (activated)
- file: `src_custom/activated_effects/aromaseraphy_sweet_marjoram.c`
- clone: `src_custom/activated_effects/aromaseraphy_rosemary.c` (AROMASERAPHY_ROSEMARY)
- text: If LP higher: Plants untargetable. If Synchro: add Winds. If gain LP: destroy 1. 1 Tuner + 1+ non-Tuner monsters While your LP are higher than your opponent's, your opponent cannot target Plant monsters you control with card effects. You can only use each of the following effects of Aromaseraphy Sweet Marjoram once per turn. If this card is Synchro Summoned: You can add 1 Humid Winds, Dried Winds, or Blessed Winds from your Deck to your hand. If you gain LP: Target 1 card your opponent controls;
