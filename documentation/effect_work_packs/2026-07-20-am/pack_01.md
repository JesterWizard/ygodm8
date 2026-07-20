# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## CYBER_PHOENIX (activated)
- file: `src_custom/activated_effects/cyber_phoenix.c`
- clone: `src_custom/activated_effects/cyber_laser_dragon.c` (CYBER_LASER_DRAGON)
- text: While in Attack Position: negate S/T targeting your Machine. When destroyed: destroy 1 face-up S/T. While this card is in Attack Position, negate any Spell/Trap effects that target 1 Machine monster you control (and no other cards). When this card is destroyed by battle and sent to the GY: You can draw 1 card.

## ULTIMATE_OBEDIENT_FIEND (activated)
- file: `src_custom/activated_effects/ultimate_obedient_fiend.c`
- clone: `src_custom/activated_effects/aromage_cananga.c` (AROMAGE_CANANGA)
- text: This card can only attack if this card is the only card on your side of the field and if you also have no cards in your  This card can only attack if this card is the only card on your side of the field and if you also have no cards in your hand. The effects of Effect Monsters that this card destroys are negated.

## ULTIMATE_TYRANNO (activated)
- file: `src_custom/activated_effects/ultimate_tyranno.c`
- clone: `src_custom/activated_effects/aromage_cananga.c` (AROMAGE_CANANGA)
- text: This card can attack all monsters your opponent controls, once each. During your Battle Phase, if you control an Ultima This card can attack all monsters your opponent controls, once each. During your Battle Phase, if you control an Ultimate Tyranno that can attack, monsters other than Ultimate Tyranno cannot attack.

## NUMBER_39_UTOPIA (activated)
- file: `src_custom/activated_effects/number_39_utopia.c`
- clone: `src_custom/activated_effects/amazoness_sage.c` (AMAZONESS_SAGE)
- text: 2 Level 4 monsters When a monster declares an attack: You can detach 1 material from this card; negate the attack. If t 2 Level 4 monsters When a monster declares an attack: You can detach 1 material from this card; negate the attack. If this card is targeted for an attack, while it has no material: Destroy this card.
