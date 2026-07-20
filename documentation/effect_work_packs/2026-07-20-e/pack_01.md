# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ANCIENT_GEAR_WORKSHOP (spell)
- file: `src_custom/spell_effects/ancient_gear_workshop.c`
- clone: `src_custom/spell_effects/twin_swords_of_flashing_light_tryce.c` (TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE)
- text: Target 1 Ancient Gear monster in your Graveyard; add that target to your hand. Target 1 Ancient Gear monster in your Graveyard; add that target to your hand.

## DARK_MAGIC_ATTACK (spell)
- file: `src_custom/spell_effects/dark_magic_attack.c`
- clone: `src_custom/spell_effects/block_attack.c` (BLOCK_ATTACK)
- text: If you control Dark Magician: destroy all Spells/Traps your opponent controls. If you control Dark Magician: Destroy all Spells and Traps your opponent controls.

## SILVERS_CRY (spell)
- file: `src_custom/spell_effects/silvers_cry.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: Target 1 Dragon Normal in GY; Special Summon it. 1/turn. Target 1 Dragon Normal Monster in your GY; Special Summon that target. You can only activate 1 Silver's Cry per turn.

## SALVAGE (spell)
- file: `src_custom/spell_effects/salvage.c`
- clone: `src_custom/spell_effects/twin_swords_of_flashing_light_tryce.c` (TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE)
- text: Target 2 WATER monsters with 1500 or less ATK in your Graveyard; add those targets to your hand. Target 2 WATER monsters with 1500 or less ATK in your Graveyard; add those targets to your hand.
