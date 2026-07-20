# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MORPHTRONIC_ENGINE (spell)
- file: `src_custom/spell_effects/morphtronic_engine.c`
- clone: `src_custom/spell_effects/continuous_destruction_punch.c` (CONTINUOUS_DESTRUCTION_PUNCH)
- text: Equip only to a Level 3 Morphtronic monster. Its ATK becomes double its original ATK. During your second Standby Phase Equip only to a Level 3 Morphtronic monster. Its ATK becomes double its original ATK. During your second Standby Phase after this card's activation, destroy this card, and take damage equal to the original ATK of the equipped monster.

## COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS (spell)
- file: `src_custom/spell_effects/colosseum_cage_of_the_gladiator_beasts.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Counters boost Gladiator Beasts. Place 1 Counter on this card each time a monster is Special Summoned from either player's Deck. All Gladiator Beast monsters gain 100 ATK and DEF for each of these counters on this card. If this card would be destroyed by a card effect, you can discard 1 Colosseum - Cage of the Gladiator Beasts to prevent this card from being destroyed.

## GRAVEKEEPERS_INSCRIPTION (spell)
- file: `src_custom/spell_effects/gravekeepers_inscription.c`
- clone: `src_custom/spell_effects/call_of_the_mummy.c` (CALL_OF_THE_MUMMY)
- text: At the start of your Main Phase 1: Apply 1 of the following effects until the end of your opponent's turn. - Neither pl At the start of your Main Phase 1: Apply 1 of the following effects until the end of your opponent's turn. - Neither player can activate card effects in the GY. - Neither player can banish cards from the GY. - Neither player can Special Summon monsters from the GYs.

## MYSTIC_MINE (spell)
- file: `src_custom/spell_effects/mystic_mine.c`
- clone: `src_custom/spell_effects/continuous_destruction_punch.c` (CONTINUOUS_DESTRUCTION_PUNCH)
- text: Player with fewer monsters: no monster effects/attacks. Tie: destroy. If your opponent controls more monsters than you do, your opponent cannot activate monster effects or declare an attack. If you control more monsters than your opponent does, you cannot activate monster effects or declare an attack. Once per turn, during the End Phase, if both players control the same number of monsters: Destroy this card.
