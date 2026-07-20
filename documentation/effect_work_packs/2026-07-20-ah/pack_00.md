# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GRAVEKEEPERS_DESCENDANT (activated)
- file: `src_custom/activated_effects/gravekeepers_descendant.c`
- clone: `src_custom/activated_effects/gravekeepers_cannonholder.c` (GRAVEKEEPERS_CANNONHOLDER)
- text: You can Tribute 1 other face-up "Gravekeeper's" monster to target 1 card your opponent controls; destroy that target. You can Tribute 1 other face-up Gravekeeper's monster to target 1 card your opponent controls; destroy that target.

## EHREN_LIGHTSWORN_MONK (activated)
- file: `src_custom/activated_effects/ehren_lightsworn_monk.c`
- clone: `src_custom/activated_effects/jain_lightsworn_paladin.c` (JAIN_LIGHTSWORN_PALADIN)
- text: Shuffle Def monster; mill 3 at End. If this card attacks a Defense Position monster, before damage calculation: Shuffle that monster into the Deck. Once per turn, during your End Phase: Send the top 3 cards of your Deck to the Graveyard.

## DARK_MAGICIAN_THE_DRAGON_KNIGHT (activated)
- file: `src_custom/activated_effects/dark_magician_the_dragon_knight.c`
- clone: `src_custom/activated_effects/elemental_hero_neos_alius.c` (ELEMENTAL_HERO_NEOS_ALIUS)
- text: Dark Magician + 1 Dragon monster This card's name becomes Dark Magician while on the field or in the GY. Your opponent cannot target Spells/Traps you control with card effects, also they cannot be destroyed by your opponent's card effects.

## X_SABER_AIRBELLUM (activated)
- file: `src_custom/activated_effects/x_saber_airbellum.c`
- clone: `src_custom/activated_effects/des_koala.c` (DES_KOALA)
- text: If this card inflicts battle damage to your opponent by a direct attack: Discard 1 random card from your opponent's hand If this card inflicts battle damage to your opponent by a direct attack: Discard 1 random card from your opponent's hand.
