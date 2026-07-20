# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DESTINY_HERO_DRILLDARK (activated)
- file: `src_custom/activated_effects/destiny_hero_drilldark.c`
- clone: `src_custom/activated_effects/turbo_synchron.c` (TURBO_SYNCHRON)
- text: If this card is Normal or Special Summoned: You can Special Summon 1 Destiny HERO monster from your hand with ATK less If this card is Normal or Special Summoned: You can Special Summon 1 Destiny HERO monster from your hand with ATK less than or equal to this card's ATK on the field. You can only use this effect of Destiny HERO - Drilldark once per turn. If this card attacks a Defense Position monster, inflict piercing battle damage to your opponent.

## AMAZONESS_SPY (activated)
- file: `src_custom/activated_effects/amazoness_spy.c`
- clone: `src_custom/activated_effects/amazoness_trainee.c` (AMAZONESS_TRAINEE)
- text: You can reveal 1 other "Amazoness" monster in your hand; Special Summon this card from your hand. You can only use this  You can reveal 1 other Amazoness monster in your hand; Special Summon this card from your hand. You can only use this effect of Amazoness Spy once per turn. When this card is destroyed by battle and sent to the GY: You can target 1 Amazoness monster in your GY, except Amazoness Spy; return it to the hand, or shuffle it into the Deck.

## AROMALILITH_ROSALINA (activated)
- file: `src_custom/activated_effects/aromalilith_rosalina.c`
- clone: `src_custom/activated_effects/azure_eyes_silver_dragon.c` (AZURE_EYES_SILVER_DRAGON)
- text: Discard: gain half ATK LP. If Summoned: SS non-Tuner Aroma from Deck (Plant SS only). (Quick Effect): You can discard this card, then target 1 Aroma monster you control; gain LP equal to half its ATK. If this card is Normal or Special Summoned: You can Special Summon 1 non-Tuner Aroma monster from your Deck, also you cannot Special Summon for the rest of this turn, except Plant monsters. You can only use each effect of Aromalilith Rosalina once per turn.

## LORD_OF_THE_RED (activated)
- file: `src_custom/activated_effects/lord_of_the_red.c`
- clone: `src_custom/activated_effects/ancient_gear_engineer.c` (ANCIENT_GEAR_ENGINEER)
- text: Once per turn, when a card/effect activates: destroy 1 monster or 1 S/T on the field. You can Ritual Summon this card with Red-Eyes Transmigration. Once per turn, during either player's turn, when a card or effect is activated, except Lord of the Red: You can target 1 monster on the field; destroy it. Once per turn, during either player's turn, when a card or effect is activated, except Lord of the Red: You can target 1 Spell/Trap Card on the field; destroy it.
