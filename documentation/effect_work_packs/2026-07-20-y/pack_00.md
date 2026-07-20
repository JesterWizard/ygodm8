# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## AMAZONESS_SHAMANISM (trap)
- file: `src_custom/trap_effects/amazoness_shamanism.c`
- clone: `src_custom/trap_effects/a_hero_emerges.c` (A_HERO_EMERGES)
- text: Destroy all face-up "Amazoness" monsters you control. Then, you can Special Summon any number of Level 4 or lower "Amazo Destroy all face-up Amazoness monsters you control. Then, you can Special Summon any number of Level 4 or lower Amazoness monsters from your Graveyard in face-up Defense Position, up to the number of monsters destroyed by this effect.

## SIXTH_SENSE (trap)
- file: `src_custom/trap_effects/sixth_sense.c`
- clone: `src_custom/trap_effects/light_of_destruction.c` (LIGHT_OF_DESTRUCTION)
- text: Declare 2 numbers from 1 to 6, then your opponent rolls a six-sided die, and if the result is one of the numbers you dec Declare 2 numbers from 1 to 6, then your opponent rolls a six-sided die, and if the result is one of the numbers you declared, you draw that many cards. Otherwise, send a number of cards from the top of your Deck to the Graveyard equal to the result.

## BATTLE_MANIA (trap)
- file: `src_custom/trap_effects/battle_mania.c`
- clone: `src_custom/trap_effects/level_limit_area_a.c` (LEVEL_LIMIT_AREA_A)
- text: Activate only during your opponent's Standby Phase. All face-up monsters your opponent controls are changed to Attack Po Activate only during your opponent's Standby Phase. All face-up monsters your opponent controls are changed to Attack Position, and cannot change their battle positions this turn. All monsters your opponent currently controls must attack this turn, if able.

## RED_REBOOT (trap)
- file: `src_custom/trap_effects/red_reboot.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: Negate Trap; Set it. Opp cannot activate Traps. Hand: pay half LP. When your opponent activates a Trap Card: Negate the activation, and if you do, Set that card face-down, then they can Set 1 other Trap directly from their Deck. For the rest of this turn after this card resolves, your opponent cannot activate Trap Cards. You can activate this card from your hand by paying half your LP.
