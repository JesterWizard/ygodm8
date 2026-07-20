# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## PAINFUL_CHOICE (spell)
- file: `src_custom/spell_effects/painful_choice.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Select 5 cards from your Deck and show them to your opponent. Your opponent selects 1 card among them. Add t Select 5 cards from your Deck and show them to your opponent. Your opponent selects 1 card among them. Add that card to your hand and discard the remaining cards to the Graveyard.

## INFECTED_MAIL (spell)
- file: `src_custom/spell_effects/infected_mail.c`
- clone: `src_custom/spell_effects/dragons_mirror.c` (DRAGONS_MIRROR)
- text: Once per turn: You can target 1 Level 4 or lower monster you control; it can attack your opponent directly this turn. Se Once per turn: You can target 1 Level 4 or lower monster you control; it can attack your opponent directly this turn. Send it to the Graveyard at the end of the Battle Phase.

## AMAZONESS_HEIRLOOM (spell)
- file: `src_custom/spell_effects/amazoness_heirloom.c`
- clone: `src_custom/spell_effects/amazoness_fighting_spirit.c` (AMAZONESS_FIGHTING_SPIRIT)
- text: Equip only to an "Amazoness" monster. Once per turn, that monster cannot be destroyed by battle. After damage calculatio Equip only to an Amazoness monster. Once per turn, that monster cannot be destroyed by battle. After damage calculation, if the equipped monster attacks a monster: Destroy the attacked monster.

## DE_SYNCHRO (spell)
- file: `src_custom/spell_effects/de_synchro.c`
- clone: `src_custom/spell_effects/dragons_mirror.c` (DRAGONS_MIRROR)
- text: Target 1 Synchro Monster on the field; return that target to the Extra Deck, then, if all of the monsters that were used Target 1 Synchro Monster on the field; return that target to the Extra Deck, then, if all of the monsters that were used for the Synchro Summon of that monster are in your GY, you can Special Summon all of them.
