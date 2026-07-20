# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ANCIENT_GEAR_CASTLE (spell)
- file: `src_custom/spell_effects/ancient_gear_castle.c`
- clone: `src_custom/spell_effects/attack_pheromones.c` (ATTACK_PHEROMONES)
- text: All Ancient Gear monsters gain 300 ATK. Each time a monster is Normal Summoned/Set, place 1 counter on this card. If y All Ancient Gear monsters gain 300 ATK. Each time a monster is Normal Summoned/Set, place 1 counter on this card. If you Tribute Summon an Ancient Gear monster face-up, you can Tribute this card instead, if the number of its counters is equal to or greater than the number of required Tribute(s).

## HARPIES_FEATHER_REST (spell)
- file: `src_custom/spell_effects/harpies_feather_rest.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Shuffle 3 Harpies from GY; draw 1 (or 2). Then WIND SS lock. Target 3 Harpie Lady and/or Harpie Lady Sisters in your GY; shuffle them into the Deck, then draw 1 card. If you controlled a Level 5 or higher Harpie monster when you activated this effect, draw 2 cards instead. For the rest of this turn after this card resolves, you cannot Special Summon monsters, except WIND monsters. You can only activate 1 Harpie's Feather Rest per turn.

## ARCANA_SPREAD (spell)
- file: `src_custom/spell_effects/arcana_spread.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Coin: SS Arcana Force or coin monster. Toss a coin and apply this effect. If Light Barrier is in your Field Zone, you can choose the effect instead. Heads: Special Summon 1 Level 4 or lower Arcana Force monster from your Deck. Tails: Special Summon 1 monster that has a coin tossing effect from your GY. You can banish this card from your GY; add 1 card from your GY to your hand that has a coin tossing effect. You can only use 1 Arcana Spread effect per turn, and only once that turn.

## AMAZONESS_CALL (spell)
- file: `src_custom/spell_effects/amazoness_call.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Take 1 "Amazoness" card from your Deck, except "Amazoness Call", and either add it to your hand or send it to the GY. Du Take 1 Amazoness card from your Deck, except Amazoness Call, and either add it to your hand or send it to the GY. During your Main Phase: You can banish this card from your GY, then target 1 Amazoness monster you control; this turn, that monster can attack all monsters your opponent controls, once each, also other monsters you control cannot attack. You can only activate 1 Ama
