# Effect work pack 01 (3 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ARCANA_FORCE_EX_THE_DARK_RULER (permanent)
- file: `src_custom/permanent_effects/arcana_force_ex_the_dark_ruler.c`
- clone: `src_custom/permanent_effects/evil_dragon_ananta.c` (EVIL_DRAGON_ANANTA)
- text: Tribute 3. Coin: wipe field or your cards. Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by sending 3 monsters you control to the Graveyard, and cannot be Special Summoned by other ways. When this card is Special Summoned: Toss a coin and gain the appropriate effect. Heads: This card can make a second attack during each Battle Phase, but if it does so using this effect, change it to Defense Position at the end of the Battle Phase. Its battle position cannot be changed 

## DARK_MAGICIAN_OF_DESTRUCTION (permanent)
- file: `src_custom/permanent_effects/dark_magician_of_destruction.c`
- clone: `src_custom/permanent_effects/dark_magician_of_chaos.c` (DARK_MAGICIAN_OF_CHAOS)
- text: Fusion/alt SS after Spell. Name=Dark Magician. If SS: add DM or card mentioning it. Dark Magician + 1 LIGHT or DARK monster Must be either Fusion Summoned, or Special Summoned (from your Extra Deck) during the turn a Spell Card or effect is activated, by banishing 1 Level 6 or higher DARK Spellcaster monster you control as material. You can only Special Summon Dark Magician of Destruction once per turn this way, no matter which method you use. This card's name becomes Dark Magician while on the 

## ARCANA_FORCE_EX_THE_LIGHT_RULER (permanent)
- file: `src_custom/permanent_effects/arcana_force_ex_the_light_ruler.c`
- clone: `src_custom/permanent_effects/el_shaddoll_grysta.c` (EL_SHADDOLL_GRYSTA)
- text: Tribute 3. Coin: protect or negate via send. Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by sending 3 monsters you control to the Graveyard, and cannot be Special Summoned by other ways. When this card is Special Summoned: Toss a coin and gain the appropriate effect. Heads: When this card destroys an opponent's monster by battle and sends it to the Graveyard: You can target 1 card in your Graveyard; add that target to your hand. Tails: During either player's turn, wh
