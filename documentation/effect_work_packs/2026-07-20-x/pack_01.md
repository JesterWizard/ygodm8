# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SPARK_BLASTER (trap)
- file: `src_custom/trap_effects/spark_blaster.c`
- clone: `src_custom/trap_effects/morphtronic_bind.c` (MORPHTRONIC_BIND)
- text: Equip only to Elemental HERO Sparkman. During your Main Phase: You can target 1 face-up monster; change the battle pos Equip only to Elemental HERO Sparkman. During your Main Phase: You can target 1 face-up monster; change the battle position of that target. After you use this effect 3 times, destroy this card.

## DARK_RENEWAL (trap)
- file: `src_custom/trap_effects/dark_renewal.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: On opp Summon: send that monster and your Spellcaster to GY; SS 1 DARK Spellcaster. When your opponent Normal or Special Summons a monster(s): Target 1 of those monsters and 1 Spellcaster monster you control; send both monsters to the GY, then you can Special Summon 1 DARK Spellcaster monster from your Deck or GY.

## TRAP_TRICK (trap)
- file: `src_custom/trap_effects/trap_trick.c`
- clone: `src_custom/trap_effects/light_of_destruction.c` (LIGHT_OF_DESTRUCTION)
- text: Banish Normal Trap; Set same name, usable now. Banish 1 Normal Trap from your Deck, except Trap Trick, and Set 1 card with the same name directly from your Deck, also it can be activated this turn. You can only activate 1 Trap Card for the rest of this turn after this card resolves. You can only activate 1 Trap Trick per turn.

## TWILIGHT_ERASER (trap)
- file: `src_custom/trap_effects/twilight_eraser.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: Banish 2 LS from GY; banish 2 field. If you control 2 or more Lightsworn monsters with the same Type but different names: Banish 2 Lightsworn monsters from your GY, then target 2 cards on the field; banish them. If this card is sent from the Deck to the GY by a Lightsworn monster's effect: You can Special Summon 1 Lightsworn monster from your hand.
