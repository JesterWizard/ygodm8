# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HARPIE_DANCER (activated)
- file: `src_custom/activated_effects/harpie_dancer.c`
- clone: `src_custom/activated_effects/mask_of_darkness.c` (MASK_OF_DARKNESS)
- text: Return 1 WIND; then Normal Summon 1 WIND. Name Lady. OPT. You can target 1 WIND monster you control; return it to the hand, then you can Normal Summon 1 WIND monster. You can only use this effect of Harpie Dancer once per turn. This card's name becomes Harpie Lady while on the field or in the GY.

## TURBO_ROCKET (activated)
- file: `src_custom/activated_effects/turbo_rocket.c`
- clone: `src_custom/activated_effects/turbo_cannon.c` (TURBO_CANNON)
- text: While attacking, this card cannot be destroyed by battle. If this card attacks, after damage calculation, inflict damage While attacking, this card cannot be destroyed by battle. If this card attacks, after damage calculation, inflict damage equal to half the ATK of the attack target to your opponent.

## AMAZONESS_TRAINEE (activated)
- file: `src_custom/activated_effects/amazoness_trainee.c`
- clone: `src_custom/activated_effects/ehren_lightsworn_monk.c` (EHREN_LIGHTSWORN_MONK)
- text: Monsters destroyed by battle with this card are returned to the bottom of the Deck instead of going to the GY. If this c Monsters destroyed by battle with this card are returned to the bottom of the Deck instead of going to the GY. If this card destroys an opponent's monster by battle: It gains 200 ATK.

## RESCUE_RABBIT (activated)
- file: `src_custom/activated_effects/rescue_rabbit.c`
- clone: `src_custom/activated_effects/rescue_cat.c` (RESCUE_CAT)
- text: Banish; SS 2 same Normal from Deck. Cannot be Special Summoned from the Deck. You can banish this face-up card you control; Special Summon 2 Level 4 or lower Normal Monsters with the same name from your Deck, but destroy them during the End Phase. You can only use this effect of Rescue Rabbit once per turn.
