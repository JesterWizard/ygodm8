# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HARPIES_PET_PHANTASMAL_DRAGON (permanent)
- file: `src_custom/permanent_effects/harpies_pet_phantasmal_dragon.c`
- clone: `src_custom/permanent_effects/reptilianne_viper.c` (REPTILIANNE_VIPER)
- text: Direct attack. Protect Harpies. End Phase: detach 1 material. 3 Level 4 WIND monsters This card's effects can only be applied/resolved while it has Xyz Material. This card can attack your opponent directly. Your opponent cannot target any Harpie monsters with effects or for attacks. During each of your End Phases: Detach 1 Xyz Material from this card.

## VENNOMINON_THE_KING_OF_POISONOUS_SNAKES (permanent)
- file: `src_custom/permanent_effects/vennominon_the_king_of_poisonous_snakes.c`
- clone: `src_custom/permanent_effects/elemental_hero_escuridao.c` (ELEMENTAL_HERO_ESCURIDAO)
- text: ATK per Reptile. If destroyed: banish; SS self. Cannot be Special Summoned by another Effect Monster's effect. This card is unaffected by Venom Swamp. This card gains 500 ATK for each Reptile-Type monster in your Graveyard. When this card is destroyed by battle and sent to the Graveyard: You can banish 1 other Reptile-Type monster from your Graveyard; Special Summon this card.

## ELEMENTAL_HERO_AIR_NEOS (permanent)
- file: `src_custom/permanent_effects/elemental_hero_air_neos.c`
- clone: `src_custom/permanent_effects/elemental_hero_flare_neos.c` (ELEMENTAL_HERO_FLARE_NEOS)
- text: ATK = LP gap; return at End Phase. Elemental Hero Neos + Neo-Spacian Air Hummingbird This card can only be Special Summoned from your Extra Deck by returning the above cards you control to the Deck. (You do not use Polymerization.) While your Life Points are lower than your opponent's, this card gains ATK equal to the difference. This card returns to the Extra Deck during the End Phase.

## GLADIATOR_BEAST_ALEXANDER (permanent)
- file: `src_custom/permanent_effects/gladiator_beast_alexander.c`
- clone: `src_custom/permanent_effects/gladiator_beast_secutor.c` (GLADIATOR_BEAST_SECUTOR)
- text: Spell immune; tag out after battle. This card cannot be Special Summoned except by the effect of Gladiator Beast Dimacari. If this card was Special Summoned, it is unaffected by the effects of Spell Cards. At the end of the Battle Phase, if this card attacked or was attacked, you can return it to the Deck to Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Alexander.
