# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## LIGHTNING_STORM (spell)
- file: `src_custom/spell_effects/lightning_storm.c`
- clone: `src_custom/spell_effects/venom_swamp.c` (VENOM_SWAMP)
- text: If you control no face-up cards: Activate 1 of these effects; - Destroy all Attack Position monsters your opponent cont If you control no face-up cards: Activate 1 of these effects; - Destroy all Attack Position monsters your opponent controls. - Destroy all Spells and Traps your opponent controls. You can only activate 1 Lightning Storm per turn.

## NECROVALLEY (spell)
- file: `src_custom/spell_effects/necrovalley.c`
- clone: `src_custom/spell_effects/realm_of_light.c` (REALM_OF_LIGHT)
- text: All Gravekeeper's monsters gain 500 ATK and DEF. Cards in the Graveyard cannot be banished. Negate any card effect tha All Gravekeeper's monsters gain 500 ATK and DEF. Cards in the Graveyard cannot be banished. Negate any card effect that would move a card in the Graveyard to a different place. Negate any card effect that changes Types or Attributes in the Graveyard.

## BOND_BETWEEN_TEACHER_AND_STUDENT (spell)
- file: `src_custom/spell_effects/bond_between_teacher_and_student.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: If you control Dark Magician Girl: Special Summon 1 Dark Magician from your hand, Deck, or GY, If you control Dark Magician: Special Summon 1 Dark Magician Girl from your hand, Deck, or GY, then, you can Set 1 Dark Magic Attack, Dark Burning Attack, Dark Burning Magic, or Dark Magic Twin Burst directly from your Deck. You can only activate 1 Bond Between Teacher and Student per turn.

## BIG_EVOLUTION_PILL (spell)
- file: `src_custom/spell_effects/big_evolution_pill.c`
- clone: `src_custom/spell_effects/venom_swamp.c` (VENOM_SWAMP)
- text: After this card's activation, it remains on the field, but destroy it during your opponent's 3rd End Phase. Tribute 1 Di After this card's activation, it remains on the field, but destroy it during your opponent's 3rd End Phase. Tribute 1 Dinosaur-Type monster to activate this card; while this card is face-up on the field, you can Normal Summon Level 5 or higher Dinosaur-Type monsters without Tributing.
