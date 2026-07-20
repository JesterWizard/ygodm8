# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## TEST_BEAR (activated)
- file: `src_custom/activated_effects/test_bear.c`
- clone: `src_custom/activated_effects/test_tiger.c` (TEST_TIGER)
- text: Hand SS with GB; bounce for Deck SS. If you control a Gladiator Beast monster Special Summoned from the Deck/Extra Deck, you can Special Summon this card (from your hand). You can only Special Summon Test Bear once per turn this way. You can Tribute this card, then shuffle 1 Gladiator Beast monster from your hand or face-up field into the Deck/Extra Deck; Special Summon up to 2 Gladiator Beast monsters from your Deck. (This is treated as a Special Summon by a Gladiator Beast monster's effect.) Y

## AMAZONESS_PET_LIGER_KING (activated)
- file: `src_custom/activated_effects/amazoness_pet_liger_king.c`
- clone: `src_custom/activated_effects/azure_eyes_silver_dragon.c` (AZURE_EYES_SILVER_DRAGON)
- text: 1 Level 5 or higher "Amazoness" monster + 1 "Amazoness" monster
Your opponent's monsters cannot attack any monsters, ex 1 Level 5 or higher Amazoness monster + 1 Amazoness monster Your opponent's monsters cannot attack any monsters, except this one. You can target 1 Amazoness card you control and 1 Amazoness Warrior monster in your GY; destroy that card on the field, and if you do, Special Summon that other monster from the GY. This card cannot attack the turn this effect is activated. You can 

## AMAZONESS_EMPRESS (activated)
- file: `src_custom/activated_effects/amazoness_empress.c`
- clone: `src_custom/activated_effects/amazoness_trainee.c` (AMAZONESS_TRAINEE)
- text: "Amazoness Queen" + 1 "Amazoness" monster
Other "Amazoness" cards you control cannot be destroyed by battle or card eff Amazoness Queen + 1 Amazoness monster Other Amazoness cards you control cannot be destroyed by battle or card effects. If your Amazoness monster attacks a Defense Position monster, inflict piercing battle damage to your opponent. If this face-up Fusion Summoned card is destroyed by battle, or leaves the field because of an opponent's card effect while its owner controls it: Yo

## EVIL_HERO_INFERNAL_RIDER (activated)
- file: `src_custom/activated_effects/evil_hero_infernal_rider.c`
- clone: `src_custom/activated_effects/chimeratech_fortress_dragon.c` (CHIMERATECH_FORTRESS_DRAGON)
- text: On summon: add Dark Fusion. Banish 5 GY: Set Super Poly; HERO lock. If this card is Normal or Special Summoned: You can add 1 Dark Fusion from your Deck or GY to your hand. You can banish this card and 4 other monsters from your GY; Set 1 Super Polymerization from your Deck, also you cannot Special Summon (except HERO monsters), but you can Fusion Summon monsters that must be Special Summoned with Dark Fusion, using other cards' effects. These effects last until the end of your opponent's turn. 
