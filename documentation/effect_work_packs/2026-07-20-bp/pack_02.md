# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## THE_WHITE_STONE_OF_LEGEND (permanent)
- file: `src_custom/permanent_effects/the_white_stone_of_legend.c`
- clone: `src_custom/permanent_effects/elemental_hero_sunrise.c` (ELEMENTAL_HERO_SUNRISE)
- text: If sent to GY: add Blue-Eyes White Dragon. If this card is sent to the GY: Add 1 Blue-Eyes White Dragon from your Deck to your hand.

## HERO_KID (permanent)
- file: `src_custom/permanent_effects/hero_kid.c`
- clone: `src_custom/permanent_effects/fenrir.c` (FENRIR)
- text: On Special Summon: SS any number of Hero Kid from your Deck. When this card is Special Summoned: You can Special Summon any number of Hero Kid(s) from your Deck.

## WULF_LIGHTSWORN_BEAST (permanent)
- file: `src_custom/permanent_effects/wulf_lightsworn_beast.c`
- clone: `src_custom/permanent_effects/elemental_hero_shining_phoenix_enforcer.c` (ELEMENTAL_HERO_SHINING_PHOENIX_ENFORCER)
- text: If milled from Deck: SS this. Cannot be Normal Summoned/Set. Must be Special Summoned by a card effect. If this card is sent from your Deck to the GY: Special Summon it.

## REPTILIANNE_VIPER (permanent)
- file: `src_custom/permanent_effects/reptilianne_viper.c`
- clone: `src_custom/permanent_effects/elemental_hero_knospe.c` (ELEMENTAL_HERO_KNOSPE)
- text: On NS: take control of 1 face-up opp monster with 0 ATK. When this card is Normal Summoned, you can select and take control of 1 face-up monster with 0 ATK your opponent controls.
