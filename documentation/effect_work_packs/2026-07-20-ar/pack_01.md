# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## LIFE_STREAM_DRAGON (activated)
- file: `src_custom/activated_effects/life_stream_dragon.c`
- clone: `src_custom/activated_effects/destiny_hero_diamond_dude.c` (DESTINY_HERO_DIAMOND_DUDE)
- text: 1 Tuner + Power Tool Dragon
When this card is Synchro Summoned: You can make your LP become 4000. You take no effect d 1 Tuner + Power Tool Dragon When this card is Synchro Summoned: You can make your LP become 4000. You take no effect damage. If this face-up card on the field would be destroyed, you can banish 1 Equip Spell Card from your Graveyard instead.

## ANCIENT_GEAR_BEAST (activated)
- file: `src_custom/activated_effects/ancient_gear_beast.c`
- clone: `src_custom/activated_effects/ancient_gear_golem.c` (ANCIENT_GEAR_GOLEM)
- text: Cannot be Special Summoned. If this card attacks, your opponent cannot activate any Spell/Trap Cards until the end of th Cannot be Special Summoned. If this card attacks, your opponent cannot activate any Spell/Trap Cards until the end of the Damage Step. Negate the effects of an opponent's monster destroyed by battle with this card (including in the Graveyard).

## GLADIATOR_BEAST_BESTIARI (activated)
- file: `src_custom/activated_effects/gladiator_beast_bestiari.c`
- clone: `src_custom/activated_effects/gladiator_beast_murmillo.c` (GLADIATOR_BEAST_MURMILLO)
- text: Destroy S/T; tag out after battle. If this card is Special Summoned by the effect of a Gladiator Beast monster: Target 1 Spell/Trap Card on the field; destroy that target. At the end of the Battle Phase, if this card attacked or was attacked: You can shuffle it into the Deck; Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Bestiari.

## GRAVEKEEPERS_WATCHER (activated)
- file: `src_custom/activated_effects/gravekeepers_watcher.c`
- clone: `src_custom/activated_effects/herald_of_perfection.c` (HERALD_OF_PERFECTION)
- text: During either player's turn, when your opponent activates a Spell/Trap Card or monster effect that could make them disca During either player's turn, when your opponent activates a Spell/Trap Card or monster effect that could make them discard when it resolves: You can send this card from your hand to the Graveyard; negate the activation, and if you do, destroy it.
