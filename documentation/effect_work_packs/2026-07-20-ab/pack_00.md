# Effect work pack 00 (2 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HARPIE_LADY_ELEGANCE (trap)
- file: `src_custom/trap_effects/harpie_lady_elegance.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: Shuffle Sisters; SS 3 Harpies. Hand-activatable. Search if destroyed. Shuffle 1 Harpie Lady Sisters from your Monster Zone into the Deck, then you can Special Summon 3 Harpie monsters with different original names, 1 each from your hand, Deck, and GY. For the rest of this turn after this card resolves, you cannot Special Summon monsters, except WIND monsters. If this card you control is destroyed by a Harpie card's effect or your opponent's card effect: Add 1 Harpie monster from your Deck to you

## AMAZONESS_ONSLAUGHT (trap)
- file: `src_custom/trap_effects/amazoness_onslaught.c`
- clone: `src_custom/trap_effects/gladiator_naumachia.c` (GLADIATOR_NAUMACHIA)
- text: Once per turn, during the Battle Phase: You can Special Summon 1 "Amazoness" monster from your hand, and if you do, it g Once per turn, during the Battle Phase: You can Special Summon 1 Amazoness monster from your hand, and if you do, it gains 500 ATK until the end of this turn (even if this card leaves the field). After damage calculation, if your Amazoness monster battled an opponent's monster while this card is already face-up in your Spell & Trap Zone: You can banish that opponent's monster.
