# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## JAIN_LIGHTSWORN_PALADIN (activated)
- file: `src_custom/activated_effects/jain_lightsworn_paladin.c`
- clone: `src_custom/activated_effects/elemental_hero_neos_alius.c` (ELEMENTAL_HERO_NEOS_ALIUS)
- text: Piercing; mill 2 at End Phase. If this card attacks an opponent's monster, it gains 300 ATK during the Damage Step only. Once per turn, during your End Phase: Send the top 2 cards of your Deck to the Graveyard.

## GRAVEKEEPERS_HERATIC (activated)
- file: `src_custom/activated_effects/gravekeepers_heratic.c`
- clone: `src_custom/activated_effects/venom_boa.c` (VENOM_BOA)
- text: This card on the field is unaffected by all other card effects, as long as "Necrovalley" is also on the field. This card on the field is unaffected by all other card effects, as long as Necrovalley is also on the field.

## ATLANTEAN_ATTACK_SQUAD (activated)
- file: `src_custom/activated_effects/atlantean_attack_squad.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: This card gains 800 ATK while you control a face-up Fish, Sea Serpent, or Aqua-Type monster other than this card. This card gains 800 ATK while you control a face-up Fish, Sea Serpent, or Aqua-Type monster other than this card.

## HARPIE_QUEEN (activated)
- file: `src_custom/activated_effects/harpie_queen.c`
- clone: `src_custom/activated_effects/mask_of_darkness.c` (MASK_OF_DARKNESS)
- text: Name Lady. Discard this; add Harpies' Hunting Ground from Deck. This card's name becomes Harpie Lady while on the field or in the GY. You can discard this card to the GY; add 1 Harpies' Hunting Ground from your Deck to your hand.
