# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## INSECT_IMITATION (spell)
- file: `src_custom/spell_effects/insect_imitation.c`
- clone: `src_custom/spell_effects/tribute_doll.c` (TRIBUTE_DOLL)
- optional template: `--fill tribute_summon INSECT_IMITATION`
- text: Tribute 1 monster. Special Summon 1 Insect-Type monster from your Deck whose Level is 1 higher than the  Tribute 1 monster. Special Summon 1 Insect-Type monster from your Deck whose Level is 1 higher than the Tributed monster's.

## MORPHTRONIC_CORD (spell)
- file: `src_custom/spell_effects/morphtronic_cord.c`
- clone: `src_custom/spell_effects/block_attack.c` (BLOCK_ATTACK)
- optional template: `--fill destroy_zone MORPHTRONIC_CORD`
- text: Equip only to a Morphtronic monster. Each time the equipped monster's battle position is changed, destroy 1 Spell or T Equip only to a Morphtronic monster. Each time the equipped monster's battle position is changed, destroy 1 Spell or Trap Card on the field.

## DRAGON_RAVINE (spell)
- file: `src_custom/spell_effects/dragon_ravine.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- optional template: `--fill search DRAGON_RAVINE`
- text: OPT: discard 1; add Lv4- Dragunity from Deck, or send 1 Dragon from Deck to GY. Once per turn: You can discard 1 card, then activate 1 of these effects; Add 1 Level 4 or lower Dragunity monster from your Deck to your hand. Send 1 Dragon monster from your Deck to the GY.

## DARK_MAGIC_INHERITANCE (spell)
- file: `src_custom/spell_effects/dark_magic_inheritance.c`
- clone: `src_custom/spell_effects/e_emergency_call.c` (E_EMERGENCY_CALL)
- optional template: `--fill search DARK_MAGIC_INHERITANCE`
- text: Banish 2 Spells from GY; add 1 DM/DMG Spell/Trap from Deck. Once per turn. Banish 2 Spells from your GY; add 1 Spell/Trap from your Deck to your hand, that specifically lists the card Dark Magician or Dark Magician Girl in its text, except Dark Magic Inheritance. You can only activate 1 Dark Magic Inheritance per turn.
