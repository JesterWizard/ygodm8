# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HYSTERIC_PARTY (trap)
- file: `src_custom/trap_effects/hysteric_party.c`
- clone: `src_custom/trap_effects/a_hero_emerges.c` (A_HERO_EMERGES)
- text: Discard 1; SS Harpie Lady from GY. Leaving field destroys them. Activate this card by discarding 1 card; Special Summon as many copies of Harpie Lady as possible from your Graveyard. When this face-up card leaves the field, destroy those monsters.

## RITE_OF_SPIRIT (trap)
- file: `src_custom/trap_effects/rite_of_spirit.c`
- clone: `src_custom/trap_effects/embodiment_of_apophis.c` (EMBODIMENT_OF_APOPHIS)
- text: Target 1 Gravekeeper's monster in your GY; Special Summon that target. This card's activation and effect are unaffecte Target 1 Gravekeeper's monster in your GY; Special Summon that target. This card's activation and effect are unaffected by Necrovalley.

## MORPHTRONIC_MIXUP (trap)
- file: `src_custom/trap_effects/morphtronic_mixup.c`
- clone: `src_custom/trap_effects/royal_decree.c` (ROYAL_DECREE)
- text: If you control 2 or more face-up Morphtronic monsters, select 2 cards your opponent controls. Destroy 1 card of your o If you control 2 or more face-up Morphtronic monsters, select 2 cards your opponent controls. Destroy 1 card of your opponent's choice from those 2.

## PROPHECY (trap)
- file: `src_custom/trap_effects/prophecy.c`
- clone: `src_custom/trap_effects/skull_invitation.c` (SKULL_INVITATION)
- text: Select 1 random card in your opponents hand and predict whether its ATK is bigger or smaller than 2000. If y Select 1 random card in your opponents hand and predict whether its ATK is bigger or smaller than 2000. If you predict correctly you can add that card to your hand.
