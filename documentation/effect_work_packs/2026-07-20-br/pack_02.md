# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ARCANA_FORCE_VII_THE_CHARIOT (permanent)
- file: `src_custom/permanent_effects/arcana_force_vii_the_chariot.c`
- clone: `src_custom/permanent_effects/arcana_force_vi_the_lovers.c` (ARCANA_FORCE_VI_THE_LOVERS)
- text: Coin: revive after battle or give to opp. When this card is Summoned, toss a coin: Heads: If this card destroys an opponent's monster by battle, you can Special Summon that monster to your side of the field. Tails: Your opponent gains control of this card.

## ARCANA_FORCE_I_THE_MAGICIAN (permanent)
- file: `src_custom/permanent_effects/arcana_force_i_the_magician.c`
- clone: `src_custom/permanent_effects/reptilianne_viper.c` (REPTILIANNE_VIPER)
- text: Coin: Spells targeting this +/- 500 ATK. When this card is Summoned, toss a coin: Heads: When a Spell Card is activated, this card's ATK becomes double its original ATK until the End Phase of that turn. Tails: When a Spell Card is activated, your opponent gains 500 Life Points.

## EVIL_HERO_INFERNAL_PRODIGY (permanent)
- file: `src_custom/permanent_effects/evil_hero_infernal_prodigy.c`
- clone: `src_custom/permanent_effects/elemental_hero_the_shining.c` (ELEMENTAL_HERO_THE_SHINING)
- text: SS from hand if empty field. If Tributed for HERO: draw 1 at End Phase. If you control no monsters, you can Special Summon this card (from your hand) in Attack Position. Once per turn, during the End Phase, if this card was Tributed this turn to Tribute Summon a HERO monster: Draw 1 card.

## GAROTH_LIGHTSWORN_WARRIOR (permanent)
- file: `src_custom/permanent_effects/garoth_lightsworn_warrior.c`
- clone: `src_custom/permanent_effects/shire_lightsworn_spirit.c` (SHIRE_LIGHTSWORN_SPIRIT)
- text: On Lightsworn mill: mill 2; draw. Each time a card(s) is sent from your Deck to the GY by the effect of a Lightsworn monster you control, except Garoth, Lightsworn Warrior: Send the top 2 cards of your Deck to the GY, then draw 1 card for each Lightsworn monster sent to the GY by this effect.
