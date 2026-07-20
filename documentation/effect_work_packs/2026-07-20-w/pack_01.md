# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## AMBUSH_FANGS (trap)
- file: `src_custom/trap_effects/ambush_fangs.c`
- clone: `src_custom/trap_effects/morphtronic_bind.c` (MORPHTRONIC_BIND)
- text: Venom monster attacked: Negate attack, end Battle Phase, place 1 Venom Counter on attacker. Activate only when a face-up Venom monster you control is declared as an attack target. Negate the attack and end the Battle Phase. Then place 1 Venom Counter on the monster that attacked.

## TORNADO_WALL (trap)
- file: `src_custom/trap_effects/tornado_wall.c`
- clone: `src_custom/trap_effects/royal_decree.c` (ROYAL_DECREE)
- text: Activate only while Umi is on the field. While Umi is face-up on the field, you take no Battle Damage from attacking Activate only while Umi is on the field. While Umi is face-up on the field, you take no Battle Damage from attacking monsters. Destroy this card when Umi leaves the field.

## DRAMATIC_RESCUE (trap)
- file: `src_custom/trap_effects/dramatic_rescue.c`
- clone: `src_custom/trap_effects/embodiment_of_apophis.c` (EMBODIMENT_OF_APOPHIS)
- text: Activate only when a card is activated that targets an "Amazoness" monster. Return the targeted monster to its owner's h Activate only when a card is activated that targets an Amazoness monster. Return the targeted monster to its owner's hand and Special Summon 1 other monster from your hand.

## APPROPRIATE (trap)
- file: `src_custom/trap_effects/appropriate.c`
- clone: `src_custom/trap_effects/jar_of_greed.c` (JAR_OF_GREED)
- text: Activate only when your opponent draws a card(s) outside of either Draw Phase. After that, each time your opponent draws Activate only when your opponent draws a card(s) outside of either Draw Phase. After that, each time your opponent draws a card(s) outside of either Draw Phase, immediately draw 2 cards.
