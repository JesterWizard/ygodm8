# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## CELESTIAL_SWORD_EATOS (spell)
- file: `src_custom/spell_effects/celestial_sword_eatos.c`
- clone: `src_custom/spell_effects/dragons_mirror.c` (DRAGONS_MIRROR)
- text: Equipped gains 500 ATK. When sent to GY: target Guardian Eatos; gains 500 ATK per banished monster. (This card is always treated as a Noble Arms card.) The equipped monster gains 500 ATK. When this card is sent from the field to the Graveyard: You can target 1 Guardian Eatos you control; it gains 500 ATK for each banished monster.

## PARALLEL_WORLD_FUSION (spell)
- file: `src_custom/spell_effects/parallel_world_fusion.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Fusion Summon 1 Elemental HERO Fusion Monster from your Extra Deck by shuffling your banished Fusion Materia Fusion Summon 1 Elemental HERO Fusion Monster from your Extra Deck, by shuffling your banished Fusion Materials listed on it into your Deck. You cannot Special Summon monsters except by this card's effect, during the turn you activate this card.

## ARCANE_BARRIER (spell)
- file: `src_custom/spell_effects/arcane_barrier.c`
- clone: `src_custom/spell_effects/attack_pheromones.c` (ATTACK_PHEROMONES)
- text: Each time a face-up Spellcaster monster(s) on the field is destroyed, place 1 Spell Counter on this card (max. 4). You c Each time a face-up Spellcaster monster(s) on the field is destroyed, place 1 Spell Counter on this card (max. 4). You can send this card and 1 face-up Spellcaster monster you control to the GY; draw 1 card for each Spell Counter that was on this card.

## CHICKEN_GAME (spell)
- file: `src_custom/spell_effects/chicken_game.c`
- clone: `src_custom/spell_effects/card_destruction.c` (CARD_DESTRUCTION)
- text: Lowest LP player takes no damage. Turn MP: pay 1000 LP; draw 1 or gain 1000 LP. No response. The player with the lowest LP takes no damage. Once per turn, during the Main Phase: The turn player can pay 1000 LP, then activate 1 of these effects; Draw 1 card. Destroy this card. Your opponent gains 1000 LP. Neither player can activate cards or effects in response to this effect's activation.
