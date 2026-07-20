# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DARKBLAZE_DRAGON (activated)
- file: `src_custom/activated_effects/darkblaze_dragon.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: If this card is Special Summoned from the Graveyard: Its ATK and DEF become double its original ATK and DEF. If this car If this card is Special Summoned from the Graveyard: Its ATK and DEF become double its original ATK and DEF. If this card destroys a monster by battle and sends it to the Graveyard: Inflict damage to your opponent equal to that monster's original ATK.

## LEGENDARY_KNIGHT_TIMAEUS (activated)
- file: `src_custom/activated_effects/legendary_knight_timaeus.c`
- clone: `src_custom/activated_effects/cyber_phoenix.c` (CYBER_PHOENIX)
- text: Must be SS by Legend of Heart. When SS: banish face-up S/T. When attacked: Set a Spell from GY. Cannot be Normal Summoned/Set. Must be Special Summoned with Legend of Heart. When this card is Special Summoned: You can target 1 face-up Spell/Trap on the field; banish that target. When this card is targeted for an attack: You can target 1 Spell in your GY; Set that target.

## THE_AGENT_OF_MYSTERU_EARTH (activated)
- file: `src_custom/activated_effects/the_agent_of_mysteru_earth.c`
- clone: `src_custom/activated_effects/the_agent_of_creation_venus.c` (THE_AGENT_OF_CREATION_VENUS)
- text: When this card is Normal Summoned, you can add 1 "The Agent" monster from your Deck to your hand, except "The Agent of M When this card is Normal Summoned, you can add 1 The Agent monster from your Deck to your hand, except The Agent of Mystery - Earth. While The Sanctuary in the Sky is face-up on the field, you can add 1 Master Hyperion from your Deck to your hand instead.

## STARDUST_DRAGON (activated)
- file: `src_custom/activated_effects/stardust_dragon.c`
- clone: `src_custom/activated_effects/reptilianne_vaskii.c` (REPTILIANNE_VASKII)
- text: Tribute to negate destruction; SS from GY later. 1 Tuner + 1+ non-Tuner monsters When a card or effect is activated that would destroy a card(s) on the field (Quick Effect): You can Tribute this card; negate the activation, and if you do, destroy it. During the End Phase, if this effect was activated this turn (and was not negated): You can Special Summon this card from your GY.
