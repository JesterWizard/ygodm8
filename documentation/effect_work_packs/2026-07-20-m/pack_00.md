# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## CYBERNETIC_ZONE (spell)
- file: `src_custom/spell_effects/cybernetic_zone.c`
- clone: `src_custom/spell_effects/venom_swamp.c` (VENOM_SWAMP)
- text: Select 1 face-up Machine-Type Fusion Monster you control and remove it from play until the End Phase of this turn. When  Select 1 face-up Machine-Type Fusion Monster you control and remove it from play until the End Phase of this turn. When that monster is returned to the field, double its ATK. During your next Standby Phase, destroy it.

## ANTE (spell)
- file: `src_custom/spell_effects/ante.c`
- clone: `src_custom/spell_effects/twin_swords_of_flashing_light_tryce.c` (TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE)
- text: Each Player reveals 1 card from their hand. If one card is higher Level than the other, the card with the lower Level is Each Player reveals 1 card from their hand. If one card is higher Level than the other, the card with the lower Level is sent to the Graveyard, and the player who revealed it takes 1000 damage. (Non-Monster Cards are treated as Level 0.)

## SHADDOLL_FUSION (spell)
- file: `src_custom/spell_effects/shaddoll_fusion.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Fusion Summon Shaddoll. If opp Extra: can use materials from Deck. Fusion Summon 1 Shaddoll Fusion Monster from your Extra Deck, using monsters from your hand or field as Fusion Material. If your opponent controls a monster that was Special Summoned from the Extra Deck, you can also use monsters in your Deck as Fusion Material. You can only activate 1 Shaddoll Fusion per turn.

## LIGHT_BARRIER (spell)
- file: `src_custom/spell_effects/light_barrier.c`
- clone: `src_custom/spell_effects/amazoness_fighting_spirit.c` (AMAZONESS_FIGHTING_SPIRIT)
- text: Choose Arcana coin; heal on battle. During your Standby Phase, toss a coin. If the result is Tails, the following effects are negated until your next Standby Phase: When you Summon an Arcana Force monster, choose which effect to apply without tossing a coin. If an Arcana Force monster destroys an opponent's monster by battle, you gain Life Points equal to the destroyed monster's original ATK.
