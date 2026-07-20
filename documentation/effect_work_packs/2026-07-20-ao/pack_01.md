# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## TURBO_BOOSTER (activated)
- file: `src_custom/activated_effects/turbo_booster.c`
- clone: `src_custom/activated_effects/turbo_cannon.c` (TURBO_CANNON)
- text: If you have Normal Summoned a monster this turn, you can Special Summon this card from your hand. You can Tribute this c If you have Normal Summoned a monster this turn, you can Special Summon this card from your hand. You can Tribute this card to destroy 1 monster your opponent controls that battled one of your monsters this turn.

## GREEN_BABOON_DEFENDER_OF_THE_FOREST (activated)
- file: `src_custom/activated_effects/green_baboon_defender_of_the_forest.c`
- clone: `src_custom/activated_effects/elemental_hero_great_tornado.c` (ELEMENTAL_HERO_GREAT_TORNADO)
- text: If this card is in your hand or Graveyard when a face-up Beast-Type monster you control is destroyed and sent to the Gra If this card is in your hand or Graveyard when a face-up Beast-Type monster you control is destroyed and sent to the Graveyard (except during the Damage Step): You can pay 1000 Life Points; Special Summon this card.

## FELIS_LIGHTSWORN_ARCHER (activated)
- file: `src_custom/activated_effects/felis_lightsworn_archer.c`
- clone: `src_custom/activated_effects/substitoad.c` (SUBSTITOAD)
- text: SS from mill; Tribute destroy+mill. Cannot be Normal Summoned/Set. Must be Special Summoned by a card effect. If this card is sent from your Deck to the GY by a monster effect: Special Summon it. You can Tribute this card, then target 1 monster your opponent controls; destroy that target, then send the top 3 cards of your Deck to the GY.

## CRIMSON_BLADER (activated)
- file: `src_custom/activated_effects/crimson_blader.c`
- clone: `src_custom/activated_effects/dark_magician_the_dragon_knight.c` (DARK_MAGICIAN_THE_DRAGON_KNIGHT)
- text: 1 Tuner + 1 or more non-Tuner monsters
If this card destroys an opponent's monster by battle and sends it to the Graveya 1 Tuner + 1 or more non-Tuner monsters If this card destroys an opponent's monster by battle and sends it to the Graveyard: Your opponent cannot Normal or Special Summon Level 5 or higher monsters during their next turn.
