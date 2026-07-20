# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GANDORA_X_THE_DRAGON_OF_DEMOLITION (permanent)
- file: `src_custom/permanent_effects/gandora_x_the_dragon_of_demolition.c`
- clone: `src_custom/permanent_effects/caius_the_shadow_monarch.c` (CAIUS_THE_SHADOW_MONARCH)
- text: On summon from hand: nuke monsters, gain ATK = burn. End: half LP. When this card is Normal or Special Summoned from the hand: You can destroy as many other monsters on the field as possible, and if you do, inflict damage to your opponent equal to the highest original ATK on the field among those destroyed monsters (your choice, if tied). This card's ATK becomes equal to the damage inflicted to your opponent by this effect. Once per turn, during your End Phase: Halve your LP.

## EVIL_HERO_DARK_GAIA (permanent)
- file: `src_custom/permanent_effects/evil_hero_dark_gaia.c`
- clone: `src_custom/permanent_effects/evil_hero_malicious_fiend.c` (EVIL_HERO_MALICIOUS_FIEND)
- text: Dark Fusion. ATK = materials. On attack: flip opp Defense to Attack. 1 Fiend-Type monster + 1 Rock-Type monster Must be Special Summoned with Dark Fusion and cannot be Special Summoned by other ways. The original ATK of this card is equal to the combined original ATK of the Fusion Material Monsters used to Fusion Summon it. When this card declares an attack: You can change all Defense Position monsters your opponent controls to face-up Attack Position. (Flip Effects are not activated at this tim

## EL_SHADDOLL_SHEKHINAGA (permanent)
- file: `src_custom/permanent_effects/el_shaddoll_shekhinaga.c`
- clone: `src_custom/permanent_effects/el_shaddoll_winda.c` (EL_SHADDOLL_WINDA)
- text: Negate SS monster effect; destroy, send Shaddoll. GY: add S/T. 1 Shaddoll monster + 1 EARTH monster Must first be Fusion Summoned. When a Special Summoned monster activates its effect while you have a Shaddoll card in your hand (Quick Effect): You can negate the activation, and if you do, destroy that monster, then send 1 Shaddoll card from your hand to the GY. You can only use this effect of El Shaddoll Shekhinaga once per turn. If this card is sent to the GY: You can target 1 Shaddoll Spell/Tr

## TIMEAEUS_THE_UNITED_MAGICAL_DRAGON (permanent)
- file: `src_custom/permanent_effects/timeaeus_the_united_magical_dragon.c`
- clone: `src_custom/permanent_effects/el_shaddoll_winda.c` (EL_SHADDOLL_WINDA)
- text: Unaffected after SS. ATK boost. Destroy S/T. Dark Magician or Dark Magician Girl + 1 Dragon or Spellcaster monster After this card is Special Summoned, it is unaffected by other cards' effects until the end of your next turn. You can only use each of the following effects of Timaeus the United Magical Dragon once per turn. If this card battles, during damage calculation: You can make this card gain 100 ATK for each Spell in the GYs and banishment. During your opponent's turn (Quick Effect): You 
