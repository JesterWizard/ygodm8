# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MAGICAL_ARM_SHIELD (trap)
- file: `src_custom/trap_effects/magical_arm_shield.c`
- clone: `src_custom/trap_effects/morphtronic_bind.c` (MORPHTRONIC_BIND)
- text: When your opponent declares an attack while you control a monster: Target 1 face-up monster your opponent controls, exce When your opponent declares an attack while you control a monster: Target 1 face-up monster your opponent controls, except the attacking monster; take control of that target until the end of the Battle Phase, and if you do, it is attacked instead, and you proceed to damage calculation.

## BLESSED_WINDS (trap)
- file: `src_custom/trap_effects/blessed_winds.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: You can activate 1 of these effects (but you can only use each of this card once per turn): Target 1 Plant You can activate 1 of the following effects. Send 1 Plant monster from your hand or face-up field to the GY; gain 500 LP. Target 1 Plant monster in your GY; shuffle it into the Deck, then gain 500 LP. Pay 1000 LP; Special Summon 1 Aroma monster from your GY. You can only use this effect of Blessed Winds once per turn.

## TWILIGHT_CLOTH (trap)
- file: `src_custom/trap_effects/twilight_cloth.c`
- clone: `src_custom/trap_effects/light_spiral.c` (LIGHT_SPIRAL)
- text: Banish LS; target gains 200 each. Target 1 face-up monster you control; banish any number of Lightsworn monsters from your GY, and if you do, that monster gains 200 ATK and DEF for each monster banished by this effect, until the end of this turn. If this card is sent from the Deck to the GY by a Lightsworn monster's effect: You can activate this effect; this turn, Lightsworn monsters you control cannot be destroyed by battle or card effects.

## MAGICIANS_COMBINATION (trap)
- file: `src_custom/trap_effects/magicians_combination.c`
- clone: `src_custom/trap_effects/magicians_circle.c` (MAGICIANS_CIRCLE)
- text: Tribute DM/DMG; SS the other and negate. Leaves S/T: destroy 1. Once per turn, when a card or effect is activated (except during the Damage Step): You can Tribute 1 Dark Magician or 1 Dark Magician Girl; Special Summon 1 Dark Magician or 1 Dark Magician Girl from your hand or GY, with a different name from the Tributed monster, and if you do, negate that activated effect. If this face-up card is sent from the Spell & Trap Zone to the GY: You can destroy 1 card on the field.
