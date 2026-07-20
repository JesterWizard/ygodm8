# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DRAGONS_MIRROR (spell)
- file: `src_custom/spell_effects/dragons_mirror.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: Fusion Summon 1 Dragon Fusion Monster from your Extra Deck, by banishing Fusion Materials listed on it from your field o Fusion Summon 1 Dragon Fusion Monster from your Extra Deck, by banishing Fusion Materials listed on it from your field or GY.

## ANCIENT_GEAR_EXPLOSIVE (spell)
- file: `src_custom/spell_effects/ancient_gear_explosive.c`
- clone: `src_custom/spell_effects/ancient_gear_workshop.c` (ANCIENT_GEAR_WORKSHOP)
- text: Target 1 Ancient Gear monster you control; destroy it, and if you do, inflict damage to your opponent equal to half it Target 1 Ancient Gear monster you control; destroy it, and if you do, inflict damage to your opponent equal to half its original ATK.

## ANCIENT_GEAR_DRILL (spell)
- file: `src_custom/spell_effects/ancient_gear_drill.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: If you control an Ancient Gear monster: Discard 1 card; Set 1 Spell Card directly from your Deck. This turn, that Spel If you control an Ancient Gear monster: Discard 1 card; Set 1 Spell Card directly from your Deck. This turn, that Spell Card cannot be activated.

## AMAZONESS_SPELLCASTER (spell)
- file: `src_custom/spell_effects/amazoness_spellcaster.c`
- clone: `src_custom/spell_effects/h_heated_heart.c` (H_HEATED_HEART)
- text: Target 1 "Amazoness" monster you control and 1 face-up monster your opponent controls; switch the original ATK of those  Target 1 Amazoness monster you control and 1 face-up monster your opponent controls; switch the original ATK of those targets until the end of this turn.
