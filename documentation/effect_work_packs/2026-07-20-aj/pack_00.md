# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## AMAZONESS_SAGE (activated)
- file: `src_custom/activated_effects/amazoness_sage.c`
- clone: `src_custom/activated_effects/amazoness_archer.c` (AMAZONESS_ARCHER)
- text: At the end of the Damage Step, if this card attacked and is still on the field: Target 1 Spell/Trap your opponent contro At the end of the Damage Step, if this card attacked and is still on the field: Target 1 Spell/Trap your opponent controls; destroy that target.

## ROAD_WARRIOR (activated)
- file: `src_custom/activated_effects/road_warrior.c`
- clone: `src_custom/activated_effects/elemental_hero_wildedge.c` (ELEMENTAL_HERO_WILDEDGE)
- text: Road Synchron + 2 or more non-Tuner monsters
Once per turn: You can Special Summon 1 Level 2 or lower Warrior or Machi Road Synchron + 2 or more non-Tuner monsters Once per turn: You can Special Summon 1 Level 2 or lower Warrior or Machine-Type monster from your Deck.

## TUNINGWARE (activated)
- file: `src_custom/activated_effects/tuningware.c`
- clone: `src_custom/activated_effects/dark_magician_the_dragon_knight.c` (DARK_MAGICIAN_THE_DRAGON_KNIGHT)
- text: This card can be treated as a Level 2 monster when used for a Synchro Summon. If this card is sent to the Graveyard for  This card can be treated as a Level 2 monster when used for a Synchro Summon. If this card is sent to the Graveyard for a Synchro Summon: Draw 1 card.

## ANCIENT_GEAR_CANNON (activated)
- file: `src_custom/activated_effects/ancient_gear_cannon.c`
- clone: `src_custom/activated_effects/gravekeepers_cannonholder.c` (GRAVEKEEPERS_CANNONHOLDER)
- text: You can Tribute this card; inflict 500 damage to your opponent, and if you do, neither player can activate Trap Cards du You can Tribute this card; inflict 500 damage to your opponent, and if you do, neither player can activate Trap Cards during the Battle Phase of this turn.
