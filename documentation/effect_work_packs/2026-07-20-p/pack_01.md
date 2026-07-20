# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## THE_GAZE_OF_TIMAEUS (spell)
- file: `src_custom/spell_effects/the_gaze_of_timaeus.c`
- clone: `src_custom/spell_effects/dragons_mirror.c` (DRAGONS_MIRROR)
- text: Shuffle DM/DMG; Fusion Summon mentioning it. Target 1 Dark Magician or Dark Magician Girl in your field or GY; Fusion Summon 1 Fusion Monster from your Extra Deck that mentions that monster as material, by shuffling it into the Deck as material (this is treated as a Fusion Summon with The Eye of Timaeus), but banish it during the End Phase of the next turn. You can only activate 1 The Gaze of Timaeus per turn.

## VISION_FUSION (spell)
- file: `src_custom/spell_effects/vision_fusion.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Fusion Summon 1 HERO Fusion Monster from your Extra Deck, using monsters from your hand or field as Fusion Material. Y Fusion Summon 1 HERO Fusion Monster from your Extra Deck, using monsters from your hand or field as Fusion Material. You can also use up to 2 monsters in your Spell & Trap Zone that are being treated as Continuous Traps as Fusion Material, by banishing them. You can only activate 1 Vision Fusion per turn.

## SUPREME_KINGS_CASTLE (spell)
- file: `src_custom/spell_effects/supreme_kings_castle.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Enable Dark Fusion. Fiend battle: send Evil HERO. You can Fusion Summon Fusion Monsters that must be Special Summoned with Dark Fusion, with effects other than Dark Fusion. Once per turn, during damage calculation, if your Fiend monster battles an opponent's monster: You can send 1 Evil HERO monster from your Deck or Extra Deck to the GY; your monster gains ATK equal to the Level of the monster sent to the GY x 200, until the end of this turn (even if this card leaves the field).

## ULTRA_POLYMERIZATION (spell)
- file: `src_custom/spell_effects/ultra_polymerization.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Pay 2000; Fusion 2. GY: SS used materials. Pay 2000 LP; Fusion Summon 1 Fusion Monster from your Extra Deck, using 2 monsters you control as Fusion Materials. Neither player can activate cards or effects in response to this card's activation. You can banish this card from your GY, then target 1 Fusion Monster that was Fusion Summoned with this card's effect; Special Summon all the Fusion Materials used for its Fusion Summon from your GY, but change their ATK/DEF to 0, also they have their effect
