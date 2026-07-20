# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ATLANTEAN_HEAVY_INFANTRY (activated)
- file: `src_custom/activated_effects/atlantean_heavy_infantry.c`
- clone: `src_custom/activated_effects/atlantean_attack_squad.c` (ATLANTEAN_ATTACK_SQUAD)
- text: During your Main Phase, you can Normal Summon 1 Level 4 or lower Sea Serpent-Type monster in addition to your Normal Sum During your Main Phase, you can Normal Summon 1 Level 4 or lower Sea Serpent-Type monster in addition to your Normal Summon/Set. (You can only gain this effect once per turn.) When this card is sent to the Graveyard to activate a WATER monster's effect: Target 1 face-up card your opponent controls; destroy that target.

## AZURE_EYES_SILVER_DRAGON (activated)
- file: `src_custom/activated_effects/azure_eyes_silver_dragon.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: 1 Tuner + 1+ non-Tuner Normal Monsters. If Special Summoned: until end of next turn, Dragon monsters you 1 Tuner + 1+ non-Tuner Normal Monsters If this card is Special Summoned: Until the end of the next turn, neither player can target Dragon monsters you currently control with card effects, also they cannot be destroyed by card effects. Once per turn, during your Standby Phase: You can target 1 Normal Monster in your GY; Special Summon it.

## NEHSHADDOLL_GENIUS (activated)
- file: `src_custom/activated_effects/nehshaddoll_genius.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: FLIP: Shaddoll unaffected. Sent by effect: lock 1 Effect Monster. FLIP: You can target 1 Shaddoll monster you control; that face-up monster is unaffected by monster effects this turn, except its own. If this card is sent to the GY by card effect: You can target 1 Effect Monster on the field; neither player can activate that target's effects on the field this turn. You can only use 1 Nehshaddoll Genius effect per turn, and only once that turn.

## MINERVA_LIGHTSWORN_MAIDEN (activated)
- file: `src_custom/activated_effects/minerva_lightsworn_maiden.c`
- clone: `src_custom/activated_effects/amazoness_trainee.c` (AMAZONESS_TRAINEE)
- text: Search LIGHT Dragon; mill effects. When this card is Normal Summoned: You can add 1 LIGHT Dragon-Type monster from your Deck to your hand, whose Level is less than or equal to the total number of Lightsworn monsters with different names in your Graveyard. If this card is sent from the hand or Deck to the Graveyard: Send the top card of your Deck to the Graveyard. During each of your End Phases: Send the top 2 cards of your Deck to the Graveyard.
