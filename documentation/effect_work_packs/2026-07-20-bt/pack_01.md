# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## OSHALEON (permanent)
- file: `src_custom/permanent_effects/oshaleon.c`
- clone: `src_custom/permanent_effects/reptilianne_gardna.c` (REPTILIANNE_GARDNA)
- text: Opp must attack this. If destroyed by battle: add Reptile ATK 500-. While you control this face-up Attack Position card, your opponent cannot select a monster other than Oshaleon as an attack target. When this card is destroyed by battle and sent to the Graveyard, you can add 1 Reptile-Type monster with 500 or less ATK from your Deck to your hand.

## GLADIATOR_BEAST_RETIARI (permanent)
- file: `src_custom/permanent_effects/gladiator_beast_retiari.c`
- clone: `src_custom/permanent_effects/gladiator_beast_secutor.c` (GLADIATOR_BEAST_SECUTOR)
- text: Banish from opp GY; tag out after. When this card is Special Summoned by the effect of a Gladiator Beast monster, you can remove from play 1 card from your opponent's Graveyard. At the end of the Battle Phase, if this card attacked or was attacked, you can return it to the Deck to Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Retiari.

## ARCANA_FORCE_XIV_TEMPERANCE (permanent)
- file: `src_custom/permanent_effects/arcana_force_xiv_temperance.c`
- clone: `src_custom/permanent_effects/arcana_force_vi_the_lovers.c` (ARCANA_FORCE_VI_THE_LOVERS)
- text: Coin: no battle damage. Discard: reduce to 0. During damage calculation, in either player's turn: You can discard this card; you take no Battle Damage from that battle. When this card is Summoned: Toss a coin and apply this effect. The effect lasts while this card is face-up on the field. Heads: Halve all Battle Damage you take. Tails: Halve all Battle Damage your opponent takes.

## EVIL_DRAGON_ANANTA (permanent)
- file: `src_custom/permanent_effects/evil_dragon_ananta.c`
- clone: `src_custom/permanent_effects/raviel_lord_of_phantasms.c` (RAVIEL_LORD_OF_PHANTASMS)
- text: SS by banishing Reptiles; ATK/DEF = count x 600. End Phase: destroy 1 card. This card cannot be Normal Summoned or Set. This card cannot be Special Summoned except by removing from play all Reptile-Type monsters from your side of the field and Graveyard. This card's ATK and DEF are each equal to the number of monsters you removed x 600. During each of your End Phases, destroy 1 card on the field.
