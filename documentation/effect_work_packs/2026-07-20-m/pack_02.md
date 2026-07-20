# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## INSTANT_FUSION (spell)
- file: `src_custom/spell_effects/instant_fusion.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Pay 1000 LP; Special Summon 1 Level 5 or lower Fusion Monster from your Extra Deck, but it cannot attack,  Pay 1000 LP; Special Summon 1 Level 5 or lower Fusion Monster from your Extra Deck, but it cannot attack, also it is destroyed during the End Phase. (This is treated as a Fusion Summon.) You can only activate 1 Instant Fusion per turn.

## THE_LAW_OF_THE_NORMAL (spell)
- file: `src_custom/spell_effects/the_law_of_the_normal.c`
- clone: `src_custom/spell_effects/the_forceful_sentry.c` (THE_FORCEFUL_SENTRY)
- text: You can only activate this card while there are 5 face-up Level 2 or lower Normal Monsters on your side of the field. Bo You can only activate this card while there are 5 face-up Level 2 or lower Normal Monsters on your side of the field. Both players discard all cards in their hands, and destroy all cards on the field except Level 2 or lower Normal Monsters.

## AMAZONESS_VILLAGE (spell)
- file: `src_custom/spell_effects/amazoness_village.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: All "Amazoness" monsters gain 200 ATK. Once per turn, when an "Amazoness" monster is destroyed by battle or card effect  All Amazoness monsters gain 200 ATK. Once per turn, when an Amazoness monster is destroyed by battle or card effect and sent to the GY: You can Special Summon 1 Amazoness monster from your Deck with a Level less than or equal to that Amazoness monster in the GY.

## ANCIENT_GEAR_FUSION (spell)
- file: `src_custom/spell_effects/ancient_gear_fusion.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Fusion Summon 1 Ancient Gear Fusion Monster from your Extra Deck, using monsters from your hand or field as Fusion Mat Fusion Summon 1 Ancient Gear Fusion Monster from your Extra Deck, using monsters from your hand or field as Fusion Material. If you use Ancient Gear Golem or Ancient Gear Golem - Ultimate Pound you control as Fusion Material, you can also use monsters from your Deck as material.
