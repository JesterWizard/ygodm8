# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## AROMAGE_ROSEMARY (activated)
- file: `src_custom/activated_effects/aromage_rosemary.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: If LP higher: Plant attacks lock monster effects. Once/turn if gain LP: change position. While your LP are higher than your opponent's, if a Plant monster you control attacks, your opponent cannot activate monster effects until the end of the Damage Step. Once per turn, if you gain LP: Target 1 face-up monster on the field; change its battle position.

## AROMAGE_BERGAMOT (activated)
- file: `src_custom/activated_effects/aromage_bergamot.c`
- clone: `src_custom/activated_effects/aromage_cananga.c` (AROMAGE_CANANGA)
- text: If LP higher: Plants pierce. Once/turn if gain LP: +1000 ATK/DEF until opp. turn end. While your LP is higher than your opponent's, if a Plant-Type monster you control attacks a Defense Position monster, inflict piercing battle damage to your opponent. Once per turn, if you gain LP: This card gains 1000 ATK and DEF until the end of your opponent's turn.

## LEVEL_EATER (activated)
- file: `src_custom/activated_effects/level_eater.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: If this card is in your Graveyard: You can target 1 Level 5 or higher monster you control; reduce its Level by 1, and if If this card is in your Graveyard: You can target 1 Level 5 or higher monster you control; reduce its Level by 1, and if you do, Special Summon this card. This face-up card on the field cannot be Tributed, except for a Tribute Summon.

## ROAD_SYNCHRON (activated)
- file: `src_custom/activated_effects/road_synchron.c`
- clone: `src_custom/activated_effects/aromage_cananga.c` (AROMAGE_CANANGA)
- text: When using this card as Synchro Material for the Synchro Summon of a monster other than Road Warrior, reduce this card When using this card as Synchro Material for the Synchro Summon of a monster other than Road Warrior, reduce this card's Level by 2. If this card attacks, at the end of the Damage Step: Increase its Level by 1 until the end of this turn.
