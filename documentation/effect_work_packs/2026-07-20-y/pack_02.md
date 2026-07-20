# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## IMPERIAL_TOMBS_OF_NECROVALLEY (trap)
- file: `src_custom/trap_effects/imperial_tombs_of_necrovalley.c`
- clone: `src_custom/trap_effects/imperial_order.c` (IMPERIAL_ORDER)
- text: When a Spell Card, Trap Card, or monster effect is activated, while both a "Gravekeeper's" monster and "Necrovalley" are When a Spell Card, Trap Card, or monster effect is activated, while both a Gravekeeper's monster and Necrovalley are on the field: Negate the activation, and if you do, destroy it. You can only activate 1 Imperial Tombs of Necrovalley per turn.

## NEEDLE_WALL (trap)
- file: `src_custom/trap_effects/needle_wall.c`
- clone: `src_custom/trap_effects/ambush_fangs.c` (AMBUSH_FANGS)
- text: Once per turn, during your Standby Phase: Roll a six-sided die. Treat your opponent's Main Monster Zones as numbers 1-5, Once per turn, during your Standby Phase: Roll a six-sided die. Treat your opponent's Main Monster Zones as numbers 1-5, counting from your right, and destroy the monster that is in the same Main Monster Zone as the result. If the result is 6, roll again.

## AMAZONESS_WILLPOWER (trap)
- file: `src_custom/trap_effects/amazoness_willpower.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: Select 1 "Amazoness" monster in your Graveyard and Special Summon it in Attack Position. It cannot change its battle pos Select 1 Amazoness monster in your Graveyard and Special Summon it in Attack Position. It cannot change its battle position and must attack if able. When this card is removed from the field, destroy that monster. When that monster is destroyed, destroy this card.

## FOSSIL_EXCAVATION (trap)
- file: `src_custom/trap_effects/fossil_excavation.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: Activate this card by discarding 1 card, then target 1 Dinosaur-Type monster in your Graveyard; Special Summon that targ Activate this card by discarding 1 card, then target 1 Dinosaur-Type monster in your Graveyard; Special Summon that target. Negate the effects of that monster on the field. When this card leaves the field, destroy that monster. When that monster is destroyed, destroy this card.
