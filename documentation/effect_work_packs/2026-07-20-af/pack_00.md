# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GRAVEKEEPERS_COMMANDANT (activated)
- file: `src_custom/activated_effects/gravekeepers_commandant.c`
- clone: `src_custom/activated_effects/gravekeepers_guard.c` (GRAVEKEEPERS_GUARD)
- text: You can discard this card to the Graveyard; add 1 "Necrovalley" from your Deck to your hand. You can discard this card to the Graveyard; add 1 Necrovalley from your Deck to your hand.

## BIRDFACE (activated)
- file: `src_custom/activated_effects/birdface.c`
- clone: `src_custom/activated_effects/mask_of_darkness.c` (MASK_OF_DARKNESS)
- text: When destroyed by battle and sent to GY: add 1 Harpie Lady from Deck to hand. When this card is destroyed by battle and sent to the GY: You can add 1 Harpie Lady from your Deck to your hand.

## CHAINSAW_INSECT (activated)
- file: `src_custom/activated_effects/chainsaw_insect.c`
- clone: `src_custom/activated_effects/venom_serpent.c` (VENOM_SERPENT)
- text: At the end of the Damage Step, if this card attacked or was attacked: Your opponent draws 1 card. At the end of the Damage Step, if this card attacked or was attacked: Your opponent draws 1 card.

## FUSILIER_DRAGON_THE_DUAL_MODE_BEAST (activated)
- file: `src_custom/activated_effects/fusilier_dragon_the_dual_mode_beast.c`
- clone: `src_custom/activated_effects/venom_serpent.c` (VENOM_SERPENT)
- text: You can Normal Summon/Set this card without Tributing, but its original ATK and DEF become halved. You can Normal Summon/Set this card without Tributing, but its original ATK and DEF become halved.
