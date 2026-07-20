# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## EL_SHADDOLL_FUSION (spell)
- file: `src_custom/spell_effects/el_shaddoll_fusion.c`
- clone: `src_custom/spell_effects/polymerization.c` (POLYMERIZATION)
- text: Fusion Summon 1 Shaddoll Fusion using hand/field materials. Once/turn. Fusion Summon 1 Shaddoll Fusion Monster from your Extra Deck, using monsters from your hand or field as Fusion Material. You can only activate 1 El Shaddoll Fusion per turn.

## VENOM_SWAMP (spell)
- file: `src_custom/spell_effects/venom_swamp.c`
- clone: `src_custom/spell_effects/burden_of_the_mighty.c` (BURDEN_OF_THE_MIGHTY)
- text: End Phase: Venom Counters; -500 ATK each. During each player's End Phase: Place 1 Venom Counter on each face-up monster, except Venom monsters. Monsters lose 500 ATK for each Venom Counter on them. Destroy a monster if its ATK becomes 0 by this effect.

## FIELD_BARRIER (spell)
- file: `src_custom/spell_effects/field_barrier.c`
- text: Field Spell Cards on the field cannot be destroyed. Neither player can activate a new Field Spell Card. You can only con Field Spell Cards on the field cannot be destroyed. Neither player can activate a new Field Spell Card. You can only control 1 Field Barrier.

## FORBIDDEN_DRESS (spell)
- file: `src_custom/spell_effects/forbidden_dress.c`
- clone: `src_custom/spell_effects/h_heated_heart.c` (H_HEATED_HEART)
- text: Target 1 face-up monster on the field; until the end of this turn, that target loses 600 ATK, but cannot be targeted or  Target 1 face-up monster on the field; until the end of this turn, that target loses 600 ATK, but cannot be targeted or destroyed by other card effects.
