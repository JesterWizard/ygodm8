# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## FUSION_GATE (spell)
- file: `src_custom/spell_effects/fusion_gate.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: During the Main Phase, the turn player can Fusion Summon by banishing materials from their hand or field. While this card is on the field: The turn player can Fusion Summon 1 Fusion Monster from their Extra Deck, by banishing Fusion Materials listed on it from their hand or field.

## DIFFERENT_DIMENSION_CAPSULE (spell)
- file: `src_custom/spell_effects/different_dimension_capsule.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Select 1 card from your Deck and remove it from play face-down. During your 2nd Standby Phase after activation, destroy  Select 1 card from your Deck and remove it from play face-down. During your 2nd Standby Phase after activation, destroy this card and add the removed card to your hand.

## SHARD_OF_GREED (spell)
- file: `src_custom/spell_effects/shard_of_greed.c`
- clone: `src_custom/spell_effects/backup_squad.c` (BACKUP_SQUAD)
- text: Each time you draw a card(s) for your normal draw in your Draw Phase, place 1 Greed Counter on this card. You can send t Each time you draw a card(s) for your normal draw in your Draw Phase, place 1 Greed Counter on this card. You can send this card with 2 or more Greed Counters to the GY; draw 2 cards.

## INSTANT_NEO_SPACE (spell)
- file: `src_custom/spell_effects/instant_neo_space.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Keep Neos Fusion; revive Neos. Equip only to a Fusion Monster that lists Elemental HERO Neos as material. It does not have to activate its effect during the End Phase to shuffle itself into the Extra Deck. If the equipped monster leaves the field: You can Special Summon 1 Elemental HERO Neos from your hand, Deck, or GY.
