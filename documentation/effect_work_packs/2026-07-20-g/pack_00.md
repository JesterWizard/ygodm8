# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GROUND_COLLAPSE (spell)
- file: `src_custom/spell_effects/ground_collapse.c`
- clone: `src_custom/spell_effects/burden_of_the_mighty.c` (BURDEN_OF_THE_MIGHTY)
- text: Select 2 unused Monster Zones. Neither player can use those zones while this remains face-up. Select 2 Main Monster Zones on the field. Neither player can use the selected zones. You cannot select a zone that is occupied by a Monster Card.

## REPTILANNE_RAGE (spell)
- file: `src_custom/spell_effects/reptilanne_rage.c`
- clone: `src_custom/spell_effects/h_heated_heart.c` (H_HEATED_HEART)
- text: Equip: Reptile +800 ATK. If destroyed: opp monster loses 800 ATK. The equipped monster becomes Reptile-Type. It gains 800 ATK. If this card is destroyed and sent to the Graveyard: Target 1 face-up monster your opponent controls; it loses 800 ATK.

## TRIANGLE_ECSTASY_SPARK (spell)
- file: `src_custom/spell_effects/triangle_ecstasy_spark.c`
- clone: `src_custom/spell_effects/triangle_power.c` (TRIANGLE_POWER)
- text: Sisters 2700 ATK; negate opponent Trap effects. Until the end of this turn, the ATK of all Harpie Lady Sisters currently on the field becomes 2700, your opponent cannot activate any Trap Cards, also negate all your opponent's Trap effects on the field.

## ANCIENT_GEAR_TANK (spell)
- file: `src_custom/spell_effects/ancient_gear_tank.c`
- clone: `src_custom/spell_effects/big_bang_shot.c` (BIG_BANG_SHOT)
- text: Equip only to an Ancient Gear monster. It gains 600 ATK. When this card is destroyed and sent to the Graveyard: Inflic Equip only to an Ancient Gear monster. It gains 600 ATK. When this card is destroyed and sent to the Graveyard: Inflict 600 damage to your opponent.
