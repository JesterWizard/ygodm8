# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## FOG_KING (activated)
- file: `src_custom/activated_effects/fog_king.c`
- clone: `src_custom/activated_effects/granmarg_the_rock_monarch.c` (GRANMARG_THE_ROCK_MONARCH)
- text: You can Tribute 1 monster, or no monsters, to Normal Summon (but not Set) this card. The ATK of this card becomes the co You can Tribute 1 monster, or no monsters, to Normal Summon (but not Set) this card. The ATK of this card becomes the combined original ATK of the Tributed monsters. Neither player can Tribute cards.

## DECOY_DRAGON (activated)
- file: `src_custom/activated_effects/decoy_dragon.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: If this card is targeted for an attack: Target 1 Level 7 or higher Dragon-Type monster in your Graveyard; Special Summon If this card is targeted for an attack: Target 1 Level 7 or higher Dragon-Type monster in your Graveyard; Special Summon it, and if you do, change the attack target to it and perform damage calculation.

## TATSUNOKO (activated)
- file: `src_custom/activated_effects/tatsunoko.c`
- clone: `src_custom/activated_effects/the_suppression_pluto.c` (THE_SUPPRESSION_PLUTO)
- text: 1 Tuner + 1+ non-Tuner monsters
If this Synchro Summoned monster would be used as a Synchro Material, 1 monster in your 1 Tuner + 1+ non-Tuner monsters If this Synchro Summoned monster would be used as a Synchro Material, 1 monster in your hand can be used as 1 of the other materials. Unaffected by other monsters' effects.

## MAXX_C (activated)
- file: `src_custom/activated_effects/maxx_c.c`
- clone: `src_custom/activated_effects/tuningware.c` (TUNINGWARE)
- text: During either player's turn: You can send this card from your hand to the Graveyard; this turn, each time your opponent During either player's turn: You can send this card from your hand to the Graveyard; this turn, each time your opponent Special Summons a monster(s), immediately draw 1 card. You can only use 1 Maxx C per turn.
