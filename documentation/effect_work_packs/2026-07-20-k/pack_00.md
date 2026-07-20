# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## FACTORY_OF_ONE_HUNDRED_MACHINES (spell)
- file: `src_custom/spell_effects/factory_of_one_hundred_machines.c`
- clone: `src_custom/spell_effects/burden_of_the_mighty.c` (BURDEN_OF_THE_MIGHTY)
- text: Remove from play all Morphtronic monsters from your Graveyard. Target face-up Machine-Type monster you control gains 2 Remove from play all Morphtronic monsters from your Graveyard. Target face-up Machine-Type monster you control gains 200 ATK for each card removed, until the End Phase.

## GLADIATOR_BEASTS_BATTLE_MANICA (spell)
- file: `src_custom/spell_effects/gladiator_beasts_battle_manica.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Battle immune equip; recycle. Equip only to a Gladiator Beast monster. It cannot be destroyed by battle (Damage calculation is applied normally). When the equipped monster is returned from your side of the field to the Deck and this card is sent to the Graveyard, return this card to your hand.

## DOUBLE_SPELL (spell)
- file: `src_custom/spell_effects/double_spell.c`
- clone: `src_custom/spell_effects/double_cyclone.c` (DOUBLE_CYCLONE)
- text: Discard 1 Spell, then target 1 Spell in opponent GY and use its effect. Discard 1 Spell Card, then target 1 Spell Card in your opponent's Graveyard; place that target in the appropriate Zone on your side of the field, and as this card's effect resolution, follow its card text as if you had used it yourself.

## MASK_OF_DISPEL (spell)
- file: `src_custom/spell_effects/mask_of_dispel.c`
- clone: `src_custom/spell_effects/venom_swamp.c` (VENOM_SWAMP)
- text: Select 1 face-up Spell Card on the field. The controller of the Spell Card takes 500 points of damage during each of you Select 1 face-up Spell Card on the field. The controller of the Spell Card takes 500 points of damage during each of your Standby Phases. When the selected card is removed from the field, destroy this card.
