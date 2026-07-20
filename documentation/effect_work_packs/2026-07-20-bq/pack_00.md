# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DESTINY_HERO_DEFENDER (permanent)
- file: `src_custom/permanent_effects/destiny_hero_defender.c`
- clone: `src_custom/permanent_effects/reptilianne_viper.c` (REPTILIANNE_VIPER)
- text: Destiny HERO - Defender During each of your opponent's Standby Phases: Your opponent draws 1 card. This card must be in face-up Defense Position to activate and to resolve this effect.

## DARKLORD_NURSE_REFICULE (permanent)
- file: `src_custom/permanent_effects/darklord_nurse_reficule.c`
- clone: `src_custom/permanent_effects/reptilianne_viper.c` (REPTILIANNE_VIPER)
- text: Any effect that would make your opponent gain LP inflicts the same amount of damage to them, instead. Any effect that would make your opponent gain LP inflicts the same amount of damage to them, instead.

## LIGHT_SERPENT (permanent)
- file: `src_custom/permanent_effects/light_serpent.c`
- clone: `src_custom/permanent_effects/elemental_hero_the_shining.c` (ELEMENTAL_HERO_THE_SHINING)
- text: If sent from hand to GY: SS it from GY. Not Synchro Material. If this card is sent from the hand to your Graveyard: You can Special Summon it from the Graveyard. This card cannot be used as a Synchro Material Monster.

## GLADIATOR_BEAST_TORAX (permanent)
- file: `src_custom/permanent_effects/gladiator_beast_torax.c`
- clone: `src_custom/permanent_effects/fenrir.c` (FENRIR)
- text: Draw 2 discard 1; tag out after. If this card was Special Summoned by the effect of a Gladiator Beast monster, at the end of any Battle Phase that this card attacked or was attacked, you can return it to the Deck to draw 1 card.
