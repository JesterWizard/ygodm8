# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GRAND_CONVERGENCE (spell)
- file: `src_custom/spell_effects/grand_convergence.c`
- clone: `src_custom/spell_effects/burning_land.c` (BURNING_LAND)
- text: If you control Macro Cosmos: Inflict 300 damage to your opponent and destroy all monsters on the field. If you control Macro Cosmos: Inflict 300 damage to your opponent and destroy all monsters on the field.

## ILLUSION_MAGIC (spell)
- file: `src_custom/spell_effects/illusion_magic.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: Tribute Spellcaster; add up to 2 Dark Magician from Deck/GY. Tribute 1 Spellcaster monster; add up to 2 copies of Dark Magician from your Deck and/or GY to your hand. You can only activate 1 Illusion Magic per turn.

## REPTILIANNE_POISON (spell)
- file: `src_custom/spell_effects/reptilianne_poison.c`
- clone: `src_custom/spell_effects/burden_of_the_mighty.c` (BURDEN_OF_THE_MIGHTY)
- text: If control Reptilianne: flip Defense to Attack; ATK to 0. Activate only if you control a face-up Reptilianne monster. Change 1 Defense Position monster your opponent controls to face-up Attack Position and reduce its ATK to 0.

## CALL_OF_THE_MUMMY (spell)
- file: `src_custom/spell_effects/call_of_the_mummy.c`
- clone: `src_custom/spell_effects/polymerization.c` (POLYMERIZATION)
- text: 1/turn: Special Summon 1 Zombie from hand. Must control no monsters to activate and resolve. Once per turn: You can Special Summon 1 Zombie monster from your hand. You must control no monsters to activate and to resolve this effect.
