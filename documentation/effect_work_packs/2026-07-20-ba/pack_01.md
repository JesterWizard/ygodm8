# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MASTER_HYPERION (activated)
- file: `src_custom/activated_effects/master_hyperion.c`
- clone: `src_custom/activated_effects/herald_of_ulimateness.c` (HERALD_OF_ULIMATENESS)
- text: You can Special Summon this card (from your hand) by banishing 1 "The Agent" monster from your hand, field, or Graveyard You can Special Summon this card (from your hand) by banishing 1 The Agent monster from your hand, field, or Graveyard. Once per turn: You can banish 1 LIGHT Fairy-Type monster from your Graveyard, then target 1 card on the field; destroy that target. While The Sanctuary in the Sky is on the field, you can activate this effect up to twice per turn.

## DESTINY_HERO_DANGEROUS (activated)
- file: `src_custom/activated_effects/destiny_hero_dangerous.c`
- clone: `src_custom/activated_effects/destiny_hero_diamond_dude.c` (DESTINY_HERO_DIAMOND_DUDE)
- text: 1 Destiny HERO monster + 1 DARK Effect Monster
(Quick Effect): You can discard 1 card; send 1 Destiny HERO monster from  1 Destiny HERO monster + 1 DARK Effect Monster (Quick Effect): You can discard 1 card; send 1 Destiny HERO monster from your hand or Deck to the GY, and if you do, Destiny HERO monsters you control gain 200 ATK for each Destiny HERO monster in your GY until the end of this turn. You can only use this effect of Destiny HERO - Dangerous once per turn.

## DESTINY_HERO_DYNATAG (activated)
- file: `src_custom/activated_effects/destiny_hero_dynatag.c`
- clone: `src_custom/activated_effects/azure_eyes_silver_dragon.c` (AZURE_EYES_SILVER_DRAGON)
- text: During damage calculation, when you would take battle damage (Quick Effect): You can discard this card; make yourself ta During damage calculation, when you would take battle damage (Quick Effect): You can discard this card; make yourself take no battle damage from that battle, and if you do, each player takes 1000 damage. You can banish this card from your GY, then target 1 Destiny HERO monster you control; it gains 1000 ATK until the end of your opponent's next turn.

## CASTEL_THE_SKY_BLASTER_MUSKETEER (activated)
- file: `src_custom/activated_effects/castel_the_sky_blaster_musketeer.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: 2 Level 4 monsters
You can detach 1 material from this card, then target 1 face-up monster on the field; change it to fa 2 Level 4 monsters You can detach 1 material from this card, then target 1 face-up monster on the field; change it to face-down Defense Position. You can detach 2 materials from this card, then target 1 other face-up card on the field; shuffle it into the Deck. You can only use 1 Castel, the Skyblaster Musketeer effect per turn, and only once that turn.
