# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DARK_GREPHER (activated)
- file: `src_custom/activated_effects/dark_grepher.c`
- clone: `src_custom/activated_effects/amazoness_trainee.c` (AMAZONESS_TRAINEE)
- text: You can Special Summon this card (from your hand) by discarding 1 Level 5 or higher DARK monster. Once per turn: You can You can Special Summon this card (from your hand) by discarding 1 Level 5 or higher DARK monster. Once per turn: You can discard 1 DARK monster; send 1 DARK monster from your Deck to the GY.

## THE_CREATOR (activated)
- file: `src_custom/activated_effects/the_creator.c`
- clone: `src_custom/activated_effects/the_suppression_pluto.c` (THE_SUPPRESSION_PLUTO)
- text: Cannot be Special Summoned from the Graveyard. Once per turn: You can target 1 monster in your Graveyard; send 1 card fr Cannot be Special Summoned from the Graveyard. Once per turn: You can target 1 monster in your Graveyard; send 1 card from your hand to the Graveyard, and if you do, Special Summon that target.

## CHIMERATECH_FORTRESS_DRAGON (activated)
- file: `src_custom/activated_effects/chimeratech_fortress_dragon.c`
- clone: `src_custom/activated_effects/nimble_momonga.c` (NIMBLE_MOMONGA)
- text: Cyber Dragon + 1+ Machine monsters Cannot be used as Fusion Material. Must first be Special Summoned (from your Extra Deck) by sending the above cards from either field to the GY. (You do not use Polymerization.) The original ATK of this card becomes 1000 x the number of Fusion Materials used for its Special Summon.

## NEO_SPACIAN_AQUA_DOLPHIN (activated)
- file: `src_custom/activated_effects/neo_spacian_aqua_dolphin.c`
- clone: `src_custom/activated_effects/neo_spacian_air_hummingbird.c` (NEO_SPACIAN_AIR_HUMMINGBIRD)
- text: Discard; peek hand; destroy or burn. Once per turn: You can discard 1 card; look at your opponent's hand and choose 1 monster. If you control a monster with ATK greater than or equal to the ATK of the chosen card, destroy the chosen card, and if you do, inflict 500 damage to your opponent. Otherwise, take 500 damage.
