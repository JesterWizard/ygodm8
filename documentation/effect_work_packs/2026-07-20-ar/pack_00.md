# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MORPHTRONIC_MAGNEN (activated)
- file: `src_custom/activated_effects/morphtronic_magnen.c`
- clone: `src_custom/activated_effects/morphtronic_boomboxen.c` (MORPHTRONIC_BOOMBOXEN)
- text: - While in Attack Position: If your opponent controls a face-up monster, this card can only select their highest ATK mon - While in Attack Position: If your opponent controls a face-up monster, this card can only select their highest ATK monster as an attack target. - While in Defense Position: Your opponent cannot select another monster as an attack target.

## ARCANITE_MAGICIAN (activated)
- file: `src_custom/activated_effects/arcanite_magician.c`
- clone: `src_custom/activated_effects/amazoness_sage.c` (AMAZONESS_SAGE)
- text: Synchro: 2 Spell Counters. +1000 ATK each. Remove 1 Spell Counter; destroy 1 opp. card. 1 Tuner + 1+ non-Tuner Spellcaster monsters If this card is Synchro Summoned: Place 2 Spell Counters on it. This card gains 1000 ATK for each Spell Counter on it. You can remove 1 Spell Counter from your field, then target 1 card your opponent controls; destroy that target.

## DARKLORD_DESIRE (activated)
- file: `src_custom/activated_effects/darklord_desire.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: Cannot be Special Summoned. You can Tribute Summon this card by Tributing 1 Fairy-Type monster. Once per turn: You can t Cannot be Special Summoned. You can Tribute Summon this card by Tributing 1 Fairy-Type monster. Once per turn: You can target 1 monster your opponent controls; this card loses exactly 1000 ATK, and if it does, send that target to the Graveyard.

## FORMULA_SYNCHRON (activated)
- file: `src_custom/activated_effects/formula_synchron.c`
- clone: `src_custom/activated_effects/t_g_hyper_librarian.c` (T_G_HYPER_LIBRARIAN)
- text: 1 Tuner + 1 non-Tuner monster
When this card is Synchro Summoned: You can draw 1 card. Once per Chain, during your oppon 1 Tuner + 1 non-Tuner monster When this card is Synchro Summoned: You can draw 1 card. Once per Chain, during your opponent's Main Phase, you can (Quick Effect): Immediately after this effect resolves, Synchro Summon using this card you control.
