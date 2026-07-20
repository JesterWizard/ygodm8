# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## REPTILIANNE_VASKII (activated)
- file: `src_custom/activated_effects/reptilianne_vaskii.c`
- clone: `src_custom/activated_effects/elemental_hero_great_tornado.c` (ELEMENTAL_HERO_GREAT_TORNADO)
- text: SS by Tributing 2 with 0 ATK. OPT: destroy 1 face-up opp. This card cannot be Normal Summoned or Set. This card cannot be Special Summoned except by Tributing 2 face-up monsters with 0 ATK from anywhere on the field. Once per turn, you can select and destroy 1 face-up monster your opponent controls. There can only be 1 face-up Reptilianne Vaskii on the field.

## ELDER_ENTITY_NORDEN (activated)
- file: `src_custom/activated_effects/elder_entity_norden.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: 1 Synchro or Xyz Monster + 1 Synchro or Xyz Monster
When this card is Special Summoned: You can target 1 Level 4 or lowe 1 Synchro or Xyz Monster + 1 Synchro or Xyz Monster When this card is Special Summoned: You can target 1 Level 4 or lower monster in your Graveyard; Special Summon it, but its effects are negated, also banish it when this card leaves the field.

## AROMASERAPHY_ROSEMARY (activated)
- file: `src_custom/activated_effects/aromaseraphy_rosemary.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: If LP higher: Plants +500. Once/turn if gain LP: negate 1 opp. face-up card. 1 Tuner + 1 or more non-Tuner monsters While your LP is higher than your opponent's, all Plant-Type monsters you control gain 500 ATK and DEF. Once per turn, if you gain LP: Target 1 face-up card your opponent controls; that face-up card has its effects negated until the end of this turn.

## JAIN_TWILIGHTSWORN_GENERAL (activated)
- file: `src_custom/activated_effects/jain_twilightsworn_general.c`
- clone: `src_custom/activated_effects/jain_lightsworn_paladin.c` (JAIN_LIGHTSWORN_PALADIN)
- text: Banish Lightsworn; weaken; mill trigger. Once per turn: You can banish 1 Lightsworn monster from your hand or GY, then target 1 face-up monster on the field; it loses ATK and DEF equal to the banished monster's Level x 300, until the end of this turn. Once per turn, if your other Lightsworn monster's effect is activated: Send the top 2 cards of your Deck to the GY.
