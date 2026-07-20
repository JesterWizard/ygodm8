# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ONE_DAY_OF_PEACE (spell)
- file: `src_custom/spell_effects/one_day_of_peace.c`
- text: Each player draws 1 card, and neither player takes damage until the end of the opponent's next turn. Each player draws 1 card, and neither player takes damage until the end of the opponent's next turn.

## VIPERS_REBIRTH (spell)
- file: `src_custom/spell_effects/vipers_rebirth.c`
- clone: `src_custom/spell_effects/ancient_rules.c` (ANCIENT_RULES)
- text: SS non-Tuner Reptile from GY; destroy later. Activate only if all monsters in your Graveyard are Reptile-Type. Select 1 non-Tuner monster in your Graveyard. Special Summon it. Destroy it during the End Phase.

## THE_A_FORCES (spell)
- file: `src_custom/spell_effects/the_a_forces.c`
- clone: `src_custom/spell_effects/kaiser_colosseum.c` (KAISER_COLOSSEUM)
- text: All Warrior-Type monsters you control gain 200 ATK for each Warrior or Spellcaster-Type monster you control. All Warrior-Type monsters you control gain 200 ATK for each Warrior or Spellcaster-Type monster you control.

## THAT_GRASS_LOOKS_GREENER (spell)
- file: `src_custom/spell_effects/that_grass_looks_greener.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: If Deck larger: mill until Deck sizes match. If you have more cards in your Deck than your opponent does: Send cards from the top of your Deck to the Graveyard so you have the same number of cards in the Deck as your opponent.
