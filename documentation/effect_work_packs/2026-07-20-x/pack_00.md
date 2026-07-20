# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## LIGHTSWORN_AEGIS (trap)
- file: `src_custom/trap_effects/lightsworn_aegis.c`
- clone: `src_custom/trap_effects/lightsworn_barrier.c` (LIGHTSWORN_BARRIER)
- text: Negate opp cards; Set if milled. Target face-up cards your opponent controls, up to the number of Lightsworn monsters you control; negate their effects until the end of this turn. If this card is sent from the Deck to the GY: You can Set this card. You can only use each effect of Lightsworn Aegis once per turn.

## ALL_OUT_ATTACKS (trap)
- file: `src_custom/trap_effects/all_out_attacks.c`
- clone: `src_custom/trap_effects/embodiment_of_apophis.c` (EMBODIMENT_OF_APOPHIS)
- text: If a monster(s) is Special Summoned while this card is face-up on the field: Change that monster to face-up Attack Posit If a monster(s) is Special Summoned while this card is face-up on the field: Change that monster to face-up Attack Position, and must attack, if able, during the turn they are Special Summoned.

## HALF_COUNTER (trap)
- file: `src_custom/trap_effects/half_counter.c`
- clone: `src_custom/trap_effects/gift_of_the_mystical_elf.c` (GIFT_OF_THE_MYSTICAL_ELF)
- text: During damage calculation, if a monster you control is being attacked: Target that monster you control; that target gain During damage calculation, if a monster you control is being attacked: Target that monster you control; that target gains ATK equal to half the original ATK of the attacking monster, until the End Phase.

## NUMINOUS_HEALER (trap)
- file: `src_custom/trap_effects/numinous_healer.c`
- clone: `src_custom/trap_effects/light_of_destruction.c` (LIGHT_OF_DESTRUCTION)
- text: You can only activate this card when you take damage to your Life Points. Increase your Life Points by 1000 points. Also You can only activate this card when you take damage to your Life Points. Increase your Life Points by 1000 points. Also, increase your Life Points by 500 points for each Numinous Healer card in your Graveyard.
