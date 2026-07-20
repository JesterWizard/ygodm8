# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MAUSOLEUM_OF_THE_EMPEROR (spell)
- file: `src_custom/spell_effects/mausoleum_of_the_emperor.c`
- clone: `src_custom/spell_effects/amazoness_fighting_spirit.c` (AMAZONESS_FIGHTING_SPIRIT)
- text: During any Main Phase: The turn player can pay 1000 LP x the number of monsters normally needed for the Tribute Summon o During any Main Phase: The turn player can pay 1000 LP x the number of monsters normally needed for the Tribute Summon of a monster (max. 2000); that player Normal Summons/Sets that monster without Tributing. (This is their one Normal Summon/Set for that turn. This is not a Tribute Summon.)

## MONSTER_RECOVERY (spell)
- file: `src_custom/spell_effects/monster_recovery.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Target 1 monster you own. Shuffle it and your hand into Deck. Draw equal to Target 1 monster you control that is owned by you; if that monster is still on the field, shuffle it and your entire hand into the Deck, also, after that, draw cards equal to the number of cards you shuffled from your hand into the Deck by this effect. (You cannot activate this card if you have a card in your hand that is owned by your opponent.)

## REASONING (spell)
- file: `src_custom/spell_effects/reasoning.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Your opponent declares a monster Level from 1 to 12. Excavate cards from the top of your Deck until you excavate a monst Your opponent declares a monster Level from 1 to 12. Excavate cards from the top of your Deck until you excavate a monster that can be Normal Summoned/Set, then, if that monster is the same Level as the one declared by your opponent, send all excavated cards to the GY. If not, Special Summon the excavated monster, also send the remaining cards to the GY.

## LIGHT_FORCE (spell)
- file: `src_custom/spell_effects/light_force.c`
- clone: `src_custom/spell_effects/ancient_gear_fusion.c` (ANCIENT_GEAR_FUSION)
- text: Coin; Fairies boost; search Arcana. Once per turn, during your Standby Phase, if Light Barrier is not in your Field Zone: Toss a coin. If tails, the following effects are negated until your next Standby Phase. Fairy monsters you control gain 300 ATK/DEF. You can discard 1 card; add 2 Arcana Force monsters with different names from your Deck to your hand, also you cannot Special Summon for the rest of this turn, except Arcana Force monsters. You can only use this effect of Light Force once per tu
