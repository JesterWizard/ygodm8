# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## TYRANT_BURST_DRAGON (activated)
- file: `src_custom/activated_effects/tyrant_burst_dragon.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: Must be Special Summoned with The Fang of Critias, using Tyrant Wing. This card can attack all your opponent's monsters, once each. You can target 1 face-up monster you control; equip this monster to that target. It gains 400 ATK/DEF, also it can make 3 attacks during each Battle Phase.

## SILENT_MAGICIAN_LV8 (activated)
- file: `src_custom/activated_effects/silent_magician_lv8.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: Cannot be Normal Summoned/Set. Must be Special Summoned by Silent Magician LV4 and cannot be Special Summoned by other Cannot be Normal Summoned/Set. Must be Special Summoned by Silent Magician LV4 and cannot be Special Summoned by other ways. Unaffected by your opponent's Spell effects.

## AROMAGE_CANANGA (activated)
- file: `src_custom/activated_effects/aromage_cananga.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: If LP higher: opp. monsters -500. Once/turn if gain LP: bounce 1 opp. Spell/Trap. While your LP is higher than your opponent's, face-up monsters your opponent controls lose 500 ATK and DEF. Once per turn, if you gain LP: Target 1 Spell/Trap Card your opponent controls; return it to the hand.

## MORPHTRONIC_VIDEON (activated)
- file: `src_custom/activated_effects/morphtronic_videon.c`
- clone: `src_custom/activated_effects/venom_boa.c` (VENOM_BOA)
- text: - While in Attack Position: This card gains 800 ATK for each Equip Card equipped to it. 
- While in Defense Position: Th - While in Attack Position: This card gains 800 ATK for each Equip Card equipped to it. - While in Defense Position: This card gains 800 DEF for each Equip Card equipped to it.
