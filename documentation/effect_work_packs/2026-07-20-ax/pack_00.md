# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## BLACK_ROSE_DRAGON (activated)
- file: `src_custom/activated_effects/black_rose_dragon.c`
- clone: `src_custom/activated_effects/cyber_phoenix.c` (CYBER_PHOENIX)
- text: 1 Tuner + 1+ non-Tuner monsters. If Synchro Summoned: destroy all cards on the field. You can 1 Tuner + 1+ non-Tuner monsters When this card is Synchro Summoned: You can destroy all cards on the field. Once per turn: You can banish 1 Plant monster from your GY, then target 1 Defense Position monster your opponent controls; change that target to face-up Attack Position, and if you do, its ATK becomes 0 until the end of this turn.

## RAINBOW_DARK_DRAGON (activated)
- file: `src_custom/activated_effects/rainbow_dark_dragon.c`
- clone: `src_custom/activated_effects/herald_of_ulimateness.c` (HERALD_OF_ULIMATENESS)
- text: (This card is always treated as an Ultimate Crystal card.)
Cannot be Normal Summoned/Set. Must be Special Summoned (f (This card is always treated as an Ultimate Crystal card.) Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by banishing 7 DARK monsters with different names from your GY. You can banish all other DARK monsters from your field and GY; this card gains 500 ATK for each card banished this way.

## ANCIENT_GEAR_ENGINEER (activated)
- file: `src_custom/activated_effects/ancient_gear_engineer.c`
- clone: `src_custom/activated_effects/ancient_gear_soldier.c` (ANCIENT_GEAR_SOLDIER)
- text: Negate any Trap effects that target this card, and if you do, destroy that Trap Card. If this card attacks, your opponen Negate any Trap effects that target this card, and if you do, destroy that Trap Card. If this card attacks, your opponent cannot activate any Spell/Trap Cards until the end of the Damage Step. At the end of the Damage Step, if this card attacked: Target 1 Spell/Trap Card your opponent controls; destroy that target.

## EL_SHADDOLL_WENDIGO (activated)
- file: `src_custom/activated_effects/el_shaddoll_wendigo.c`
- clone: `src_custom/activated_effects/ancient_gear_beast.c` (ANCIENT_GEAR_BEAST)
- text: Protect monster from battle vs opp SS. GY: add Shaddoll S/T. 1 Shaddoll monster + 1 WIND monster Must first be Fusion Summoned. (Quick Effect): You can target 1 monster you control; this turn, it cannot be destroyed by battle with an opponent's Special Summoned monster. You can only use this effect of El Shaddoll Wendigo once per turn. If this card is sent to the GY: You can target 1 Shaddoll Spell/Trap in your GY; add it to your hand.
