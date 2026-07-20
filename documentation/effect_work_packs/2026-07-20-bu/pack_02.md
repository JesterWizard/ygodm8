# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GLADIATOR_BEAST_SPARTACUS (permanent)
- file: `src_custom/permanent_effects/gladiator_beast_spartacus.c`
- clone: `src_custom/permanent_effects/gladiator_beast_alexander.c` (GLADIATOR_BEAST_ALEXANDER)
- text: Search GB Equip; tag out after. This card cannot be Special Summoned except by the effect of Gladiator Beast Hoplomus. When this card is Special Summoned, add 1 Gladiator Beast Equip Spell Card from your Deck to your hand. At the end of the Battle Phase, if this card attacked or was attacked, you can return it to the Deck to Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Spartacus.

## DRAGON_SPIRIT_OF_WHITE (permanent)
- file: `src_custom/permanent_effects/dragon_spirit_of_white.c`
- clone: `src_custom/permanent_effects/el_shaddoll_anoyatyllis.c` (EL_SHADDOLL_ANOYATYLLIS)
- text: Blue-Eyes name. On Summon: banish 1 opp S/T. Tribute: SS Blue-Eyes from hand. (This card is always treated as a Blue-Eyes card.) This card is treated as a Normal Monster while in the hand or GY. When this card is Normal or Special Summoned: You can target 1 Spell/Trap your opponent controls; banish it. If your opponent controls a monster (Quick Effect): You can Tribute this card; Special Summon 1 Blue-Eyes White Dragon from your hand.

## DESTINY_HERO_DOUBLE_DUDE (permanent)
- file: `src_custom/permanent_effects/destiny_hero_double_dude.c`
- clone: `src_custom/permanent_effects/destiny_hero_dogma.c` (DESTINY_HERO_DOGMA)
- text: Cannot be Special Summoned. This card can attack twice during each Battle Phase. During your Standby Phase, if this card Cannot be Special Summoned. This card can attack twice during each Battle Phase. During your Standby Phase, if this card was destroyed since your last Standby Phase: You can Special Summon 2 Double Dude Tokens (Warrior-Type/DARK/Level 4/ATK 1000/DEF 1000). This card must be in your Graveyard to activate and to resolve this effect.

## THE_DARK_MAGICIANS (permanent)
- file: `src_custom/permanent_effects/the_dark_magicians.c`
- clone: `src_custom/permanent_effects/el_shaddoll_anoyatyllis.c` (EL_SHADDOLL_ANOYATYLLIS)
- text: OPT draw on S/T. If destroyed: SS DM and DMG. Dark Magician or Dark Magician Girl + 1 Spellcaster monster Once per turn, if a Spell/Trap Card or effect is activated (except during the Damage Step): You can draw 1 card, then if it was a Spell/Trap, you can Set it, and if it was a Trap or Quick-Play Spell, you can activate it this turn. If this card is destroyed: You can Special Summon both 1 Dark Magician and 1 Dark Magician Girl from your hand, Deck, and/or GY.
