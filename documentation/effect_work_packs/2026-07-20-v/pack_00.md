# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## URGENT_TUNING (trap)
- file: `src_custom/trap_effects/urgent_tuning.c`
- clone: `src_custom/trap_effects/gift_of_the_mystical_elf.c` (GIFT_OF_THE_MYSTICAL_ELF)
- text: During the Battle Phase: Immediately after this effect resolves, Synchro Summon 1 Synchro Monster using monsters you con During the Battle Phase: Immediately after this effect resolves, Synchro Summon 1 Synchro Monster using monsters you control.

## DAMAGE_POLARIZER (trap)
- file: `src_custom/trap_effects/damage_polarizer.c`
- text: Activate only when an effect that inflicts damage is activated. Negate its activation and effect, and each player draws  Activate only when an effect that inflicts damage is activated. Negate its activation and effect, and each player draws 1 card.

## HUNTING_INSTINCT (trap)
- file: `src_custom/trap_effects/hunting_instinct.c`
- clone: `src_custom/trap_effects/embodiment_of_apophis.c` (EMBODIMENT_OF_APOPHIS)
- text: When a monster(s) is Special Summoned to your opponent's field (except during the Damage Step): Special Summon 1 Dinosau When a monster(s) is Special Summoned to your opponent's field (except during the Damage Step): Special Summon 1 Dinosaur monster from your hand.

## ARCANA_CALL (trap)
- file: `src_custom/trap_effects/arcana_call.c`
- clone: `src_custom/trap_effects/coffin_seller.c` (COFFIN_SELLER)
- text: Revive Arcana Force; apply coin effect. Select 1 Arcana Force monster you control. Remove from play 1 Arcana Force monster from either player's Graveyard. Until the End Phase, the selected monster's effect becomes the removed monster's effect for the same coin toss result.
