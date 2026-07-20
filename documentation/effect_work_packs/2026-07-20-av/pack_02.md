# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## RAIDEN_HAND_OF_THE_LIGHTSWORN (activated)
- file: `src_custom/activated_effects/raiden_hand_of_the_lightsworn.c`
- clone: `src_custom/activated_effects/amazoness_trainee.c` (AMAZONESS_TRAINEE)
- text: Mill 2 for ATK; End Phase mill 2. During your Main Phase: You can send the top 2 cards of your Deck to the GY, then if any Lightsworn monsters were sent to the GY by this effect, this card gains 200 ATK until the end of your opponent's turn. You can only use this effect of Raiden, Hand of the Lightsworn once per turn. Once per turn, during your End Phase: Send the top 2 cards of your Deck to the GY.

## ARMITYLE_THE_CHAOS_PHANTASM (activated)
- file: `src_custom/activated_effects/armityle_the_chaos_phantasm.c`
- clone: `src_custom/activated_effects/test_tiger.c` (TEST_TIGER)
- text: Uria, Lord of Searing Flames + Hamon, Lord of Striking Thunder + Raviel, Lord of Phantasms
Must first be Special  Uria, Lord of Searing Flames + Hamon, Lord of Striking Thunder + Raviel, Lord of Phantasms Must first be Special Summoned (from your Extra Deck) by banishing the above cards you control. (You do not use Polymerization.) Cannot be destroyed by battle. Gains 10,000 ATK during your turn only.

## MUCUS_YOLK (activated)
- file: `src_custom/activated_effects/mucus_yolk.c`
- clone: `src_custom/activated_effects/elemental_hero_lady_heat.c` (ELEMENTAL_HERO_LADY_HEAT)
- text: This card can attack your opponent's Life Points directly. Each time this card inflicts Battle Damage to your opponent's This card can attack your opponent's Life Points directly. Each time this card inflicts Battle Damage to your opponent's Life Points, increase the ATK of this card by 1000 points during your next Standby Phase. The ATK increase lasts as long as this card remains face-up on the field.

## HELIOS_DUO_MEGISTUS (activated)
- file: `src_custom/activated_effects/helios_duo_megistus.c`
- clone: `src_custom/activated_effects/test_tiger.c` (TEST_TIGER)
- text: You can Special Summon this card by Tributing 1 Helios - The Primordial Sun. This card's ATK and DEF are equal to the You can Special Summon this card by Tributing 1 Helios - The Primordial Sun. This card's ATK and DEF are equal to the number of removed from play monsters x 200. If this card is destroyed by battle and sent to the Graveyard, Special Summon it during the End Phase, and it gains 300 ATK and DEF.
