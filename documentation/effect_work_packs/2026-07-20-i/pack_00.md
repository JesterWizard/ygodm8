# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## WATERHAZARD (spell)
- file: `src_custom/spell_effects/waterhazard.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Once per turn: You can Special Summon 1 Level 4 or lower WATER monster from your hand. You must control no monsters to a Once per turn: You can Special Summon 1 Level 4 or lower WATER monster from your hand. You must control no monsters to activate and to resolve this effect.

## MOLTING_ESCAPE (spell)
- file: `src_custom/spell_effects/molting_escape.c`
- clone: `src_custom/spell_effects/amazoness_fighting_spirit.c` (AMAZONESS_FIGHTING_SPIRIT)
- text: Equip Reptile. OPT battle protect; gains 300 ATK when applied. Equip only to a Reptile-Type monster. Once per turn, if the equipped monster would be destroyed by battle, it is not destroyed. The equipped monster gains 300 ATK at the end of the Damage Step each time this effect is applied.

## SKYSCRAPER_2_HERO_CITY (spell)
- file: `src_custom/spell_effects/skyscraper_2_hero_city.c`
- clone: `src_custom/spell_effects/dragons_mirror.c` (DRAGONS_MIRROR)
- text: Once per turn, during your Main Phase, if you control this card: You can target 1 Elemental HERO monster in your Grave Once per turn, during your Main Phase, if you control this card: You can target 1 Elemental HERO monster in your Graveyard that was destroyed by battle; Special Summon that target.

## SECOND_COIN_TOSS (spell)
- file: `src_custom/spell_effects/second_coin_toss.c`
- text: When a coin toss is performed, you can choose to redo the coin toss. (If the toss involved multiple coin flips, redo all When a coin toss is performed, you can choose to redo the coin toss. (If the toss involved multiple coin flips, redo all of them.) You can only use the effect of Second Coin Toss once per turn.
