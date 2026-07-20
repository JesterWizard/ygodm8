# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DOPPELGANGER (trap)
- file: `src_custom/trap_effects/doppelganger.c`
- clone: `src_custom/trap_effects/dragon_s_rage.c` (DRAGON_S_RAGE)
- text: When you take damage from opponent monster effect, inflict same to opponent. When you take damage from the effect of a monster your opponent controls, inflict the same amount of damage to your opponent.

## LIGHTSWORN_BARRIER (trap)
- file: `src_custom/trap_effects/lightsworn_barrier.c`
- clone: `src_custom/trap_effects/light_spiral.c` (LIGHT_SPIRAL)
- text: Mill 2; negate attack on Lightsworn. When a Lightsworn monster you control is targeted for an attack: You can send the top 2 cards of your Deck to the Graveyard, then target the attacking monster; negate the attack.

## TOUR_OF_DOOM (trap)
- file: `src_custom/trap_effects/tour_of_doom.c`
- text: Coin: lock opp or your NS/Flip. During your opponent's Standby Phase, toss a coin. Heads: Your opponent cannot Normal Summon or Flip Summon until the End Phase. Tails: You cannot Normal Summon or Flip Summon during your next turn.

## ANTI_SPELL_FRAGRANCE (trap)
- file: `src_custom/trap_effects/anti_spell_fragrance.c`
- text: Both players must Set Spell Cards before activating them, and cannot activate them until their next turn after Setting t Both players must Set Spell Cards before activating them, and cannot activate them until their next turn after Setting them.
