# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## NECROVALLEY_THRONE (spell)
- file: `src_custom/spell_effects/necrovalley_throne.c`
- clone: `src_custom/spell_effects/polymerization.c` (POLYMERIZATION)
- optional template: `--fill search NECROVALLEY_THRONE`
- text: Activate 1 of these effects. - Add 1 Gravekeeper's monster from your Deck to your hand. - Immediately after this eff Activate 1 of these effects. - Add 1 Gravekeeper's monster from your Deck to your hand. - Immediately after this effect resolves, Normal Summon 1 Gravekeeper's monster. You can only activate 1 Necrovalley Throne per turn.

## HYSTERIC_SIGN (spell)
- file: `src_custom/spell_effects/hysteric_sign.c`
- clone: `src_custom/spell_effects/e_emergency_call.c` (E_EMERGENCY_CALL)
- optional template: `--fill search HYSTERIC_SIGN`
- text: Search Elegant Egotist. If sent: End Phase search up to 3 Harpies. When this card is activated: Add 1 Elegant Egotist from your Deck or GY to your hand. During the End Phase, if this card is in the GY because it was sent there from the hand or field this turn: Add up to 3 Harpie cards with different names from each other from your Deck to your hand. You can only use 1 Hysteric Sign effect per turn, and only once that turn.

## THE_SACRED_WATERS_IN_THE_SKY (spell)
- file: `src_custom/spell_effects/the_sacred_waters_in_the_sky.c`
- clone: `src_custom/spell_effects/the_melody_of_awakening_dragon.c` (THE_MELODY_OF_AWAKENING_DRAGON)
- optional template: `--fill search THE_SACRED_WATERS_IN_THE_SKY`
- text: Activate 1 "The Sanctuary in the Sky" directly from your Deck, or add 1 monster that mentions "The Sanctuary in the Sky" Activate 1 The Sanctuary in the Sky directly from your Deck, or add 1 monster that mentions The Sanctuary in the Sky from your Deck to your hand, then, if The Sanctuary in the Sky is on the field or in either GY, you can gain 500 LP for each Hyperion and The Agent monster you control. If your monster that mentions The Sanctuary in the Sky would be destroyed by battle, you can 

## SUIT_OF_SWORD_X (spell)
- file: `src_custom/spell_effects/suit_of_sword_x.c`
- clone: `src_custom/spell_effects/block_attack.c` (BLOCK_ATTACK)
- text: Coin: wipe opp or your monsters. Toss a coin. Heads: destroy all opp monsters. Tails: destroy all monsters you control.
