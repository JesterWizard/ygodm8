# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## PHOTON_GENERATOR_UNIT (spell)
- file: `src_custom/spell_effects/photon_generator_unit.c`
- clone: `src_custom/spell_effects/guardian_treasure.c` (GUARDIAN_TREASURE)
- optional template: `--fill tribute_summon PHOTON_GENERATOR_UNIT`
- text: Tribute 2 Cyber Dragons. Special Summon 1 Cyber Laser Dragon from your hand Deck or Graveyard. Tribute 2 Cyber Dragons. Special Summon 1 Cyber Laser Dragon from your hand, Deck, or Graveyard.

## METAMORPHOSIS (spell)
- file: `src_custom/spell_effects/metamorphosis.c`
- clone: `src_custom/spell_effects/tribute_doll.c` (TRIBUTE_DOLL)
- optional template: `--fill tribute_summon METAMORPHOSIS`
- text: Tribute 1 monster. Special Summon 1 Fusion Monster from your Extra Deck with the same Level as the Tributed monster. Tribute 1 monster. Special Summon 1 Fusion Monster from your Extra Deck with the same Level as the Tributed monster.

## MASK_OF_THE_ACCURSED (spell)
- file: `src_custom/spell_effects/mask_of_the_accursed.c`
- clone: `src_custom/spell_effects/big_bang_shot.c` (BIG_BANG_SHOT)
- optional template: `--fill burn MASK_OF_THE_ACCURSED`
- text: The equipped monster cannot attack. Once per turn, during your Standby Phase: Inflict 500 damage to the controller of th The equipped monster cannot attack. Once per turn, during your Standby Phase: Inflict 500 damage to the controller of the equipped monster.

## MAGICAL_DIMENSION (spell)
- file: `src_custom/spell_effects/magical_dimension.c`
- clone: `src_custom/spell_effects/tribute_doll.c` (TRIBUTE_DOLL)
- optional template: `--fill tribute_summon MAGICAL_DIMENSION`
- text: If you control a Spellcaster: Tribute 1 monster; SS 1 from hand, then destroy 1 monster. If you control a Spellcaster monster: Target 1 monster you control; Tribute that target, then Special Summon 1 Spellcaster monster from your hand, then you can destroy 1 monster on the field.
