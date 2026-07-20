# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HERALD_OF_ULTIMATENESS (activated)
- file: `src_custom/activated_effects/herald_of_ultimateness.c`
- clone: `src_custom/activated_effects/herald_of_perfection.c` (HERALD_OF_PERFECTION)
- text: Send Fairy from hand; negate opp SS or Spell/Trap/monster. You can Ritual Summon this card with Oracle of the Herald. Must be Ritual Summoned, and cannot be Special Summoned by other ways. During either player's turn, when your opponent would Special Summon a monster(s), OR activates a Spell Card, Trap Card, or monster effect: You can send 1 Fairy-Type monster from your hand to the Graveyard; negate the Special Summon or activation, and if you do, destroy that card.

## THUNDER_DRAGON_TITAN (activated)
- file: `src_custom/activated_effects/thunder_dragon_titan.c`
- clone: `src_custom/activated_effects/herald_of_ulimateness.c` (HERALD_OF_ULIMATENESS)
- text: 3 Thunder Dragon monsters Must be either Fusion Summoned, or Special Summoned by banishing 1 Thunder monster from your hand and 1 Thunder Fusion Monster you control, except Thunder Dragon Titan (in which case you do not use Polymerization). When a Thunder monster's effect is activated in the hand, even during the Damage Step (Quick Effect): You can destroy 1 card on the field. If this card would be destroyed by card effect, you can banish 2 cards from your GY instead.

## DESTINY_HERO_DUSKTOPIA (activated)
- file: `src_custom/activated_effects/destiny_hero_dusktopia.c`
- clone: `src_custom/activated_effects/gravekeepers_spiritualist.c` (GRAVEKEEPERS_SPIRITUALIST)
- text: 1 Destiny HERO Fusion Monster + 1 Destiny HERO monster If this card is Fusion Summoned: You can Fusion Summon 1 Fusion Monster from your Extra Deck, using monsters from your hand or field as Fusion Material. Once per turn (Quick Effect): You can target 1 monster on the field; make it unable to be destroyed by battle or card effects, and if you do, neither player takes any battle damage from attacks involving that monster (these effects last until the end of this turn).

## ELEMENTAL_HERO_MAGMA_NEOS (activated)
- file: `src_custom/activated_effects/elemental_hero_magma_neos.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: ATK boost; End bounce whole field. Elemental HERO Neos + Neo-Spacian Flare Scarab + Neo-Spacian Grand Mole Must first be Special Summoned (from your Extra Deck) by shuffling the above cards you control into the Deck. (You do not use Polymerization.) This card gains 400 ATK for each card on the field. Once per turn, during the End Phase: Shuffle this card into the Extra Deck. If this card is shuffled into the Extra Deck this way: Return all cards on the field to the hand.
