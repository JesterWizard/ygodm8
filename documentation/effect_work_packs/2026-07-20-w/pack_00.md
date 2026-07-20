# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SOLEMN_JUDGMENT (trap)
- file: `src_custom/trap_effects/solemn_judgment.c`
- clone: `src_custom/trap_effects/solemn_wishes.c` (SOLEMN_WISHES)
- text: When a monster(s) would be Summoned, OR a Spell/Trap Card is activated: Pay half your LP; negate the Summon or activatio When a monster(s) would be Summoned, OR a Spell/Trap Card is activated: Pay half your LP; negate the Summon or activation, and if you do, destroy that card.

## TRAP_DUSTSHOOT (trap)
- file: `src_custom/trap_effects/trap_dustshoot.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: Activate only if your opponent has 4 or more cards in their hand. Look at your opponent's hand, select 1 Monster Card in Activate only if your opponent has 4 or more cards in their hand. Look at your opponent's hand, select 1 Monster Card in it, and return that card to its owner's Deck.

## DESTINED_RIVALS (trap)
- file: `src_custom/trap_effects/destined_rivals.c`
- clone: `src_custom/trap_effects/morphtronic_bind.c` (MORPHTRONIC_BIND)
- text: If you control Blue-Eyes or Dark Magician: negate all opp face-up monster effects. If you control Blue-Eyes White Dragon or Dark Magician: Negate the effects of all face-up monsters your opponent currently controls, until the end of this turn. You can only activate 1 Destined Rivals per turn.

## METEORAIN (trap)
- file: `src_custom/trap_effects/meteorain.c`
- clone: `src_custom/trap_effects/dragon_s_rage.c` (DRAGON_S_RAGE)
- text: This turn, attacks on Defense monsters with higher ATK than their DEF inflict piercing damage. During this turn, when your monsters attack with an ATK that is higher than the DEF of your opponent's Defense Position monster, inflict the difference as Battle Damage to your opponent's Life Points.
