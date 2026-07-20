# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Traps: only edit listed trap .c. Do not leave TODO bodies. One make at the end of the whole batch.

## THUMBS_DOWN (trap)
- file: `src_custom/trap_effects/thumbs_down.c`
- clone: `-` (-)
- text: GB: burn 500 per destroyed card. Activate only if you control a Gladiator Beast. If a card(s) is destroyed by battle or effect, its controller takes 500 per card.

## GLADIATOR_BEASTS_VALOR (trap)
- file: `src_custom/trap_effects/gladiator_beasts_valor.c`
- clone: `src_custom/trap_effects/gift_of_the_mystical_elf.c` (GIFT_OF_THE_MYSTICAL_ELF)
- text: Opp can only attack Gladiator Beasts. Activate only if you control a Gladiator Beast monster. Opp monsters cannot attack, except to attack Gladiator Beast monsters.

## VANQUISHING_LIGHT (trap)
- file: `src_custom/trap_effects/vanquishing_light.c`
- clone: `src_custom/trap_effects/blast_held_by_a_tribute.c` (BLAST_HELD_BY_A_TRIBUTE)
- text: Tribute LS; negate Summon and destroy. When a monster(s) would be Summoned: Tribute 1 Lightsworn monster; negate the Summon, and if you do, destroy that monster(s).

## GLADIATOR_BEAST_WAR_CHARIOT (trap)
- file: `src_custom/trap_effects/gladiator_beast_war_chariot.c`
- clone: `src_custom/trap_effects/royal_decree.c` (ROYAL_DECREE)
- text: Negate S/T while you control a GB. When an Effect Monster's effect is activated, if you control a face-up Gladiator Beast monster: Negate the activation and destroy it.

