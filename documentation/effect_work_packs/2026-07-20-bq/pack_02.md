# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ARCANA_FORCE_IV_THE_EMPEROR (permanent)
- file: `src_custom/permanent_effects/arcana_force_iv_the_emperor.c`
- clone: `src_custom/permanent_effects/reptilianne_viper.c` (REPTILIANNE_VIPER)
- text: Coin: your or opp monsters gain 500 ATK. When this card is Summoned, toss a coin: Heads: All Arcana Force monsters you control gain 500 ATK. Tails: All Arcana Force monsters you control lose 500 ATK.

## SHIRE_LIGHTSWORN_SPIRIT (permanent)
- file: `src_custom/permanent_effects/shire_lightsworn_spirit.c`
- clone: `src_custom/permanent_effects/des_feral_imp.c` (DES_FERAL_IMP)
- text: +300 ATK per GY LS; End mill 2. This card gains 300 ATK for each Lightsworn monster with a different name in your Graveyard. During each of your End Phases: Send the top 2 cards of your Deck to the Graveyard.

## DESPAIR_FROM_THE_DARK (permanent)
- file: `src_custom/permanent_effects/despair_from_the_dark.c`
- clone: `src_custom/permanent_effects/wulf_lightsworn_beast.c` (WULF_LIGHTSWORN_BEAST)
- text: If this card is sent from your hand or Deck to your GY by an opponent's card effect: Special Summon this card. If this card is sent from your hand or Deck to your GY by an opponent's card effect: Special Summon this card.

## ARCANA_FORCE_VI_THE_LOVERS (permanent)
- file: `src_custom/permanent_effects/arcana_force_vi_the_lovers.c`
- clone: `src_custom/permanent_effects/arcana_force_viii_the_strength.c` (ARCANA_FORCE_VIII_THE_STRENGTH)
- text: Coin: double Tribute or cannot Tribute. When this card is Summoned, toss a coin: Heads: This card can be treated as 2 Tributes for the Tribute Summon of an Arcana Force monster. Tails: You cannot Tribute Summon Arcana Force monsters.
