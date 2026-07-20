# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## AROMAGE_LAUREL (activated)
- file: `src_custom/activated_effects/aromage_laurel.c`
- clone: `src_custom/activated_effects/aromage_cananga.c` (AROMAGE_CANANGA)
- text: If LP higher: SS from hand. If gain LP: Plant becomes Tuner. If to GY: +500 LP. If your LP are higher than your opponent's: You can Special Summon this card from your hand. If you gain LP: Target 1 non-Tuner Plant monster on the field; it is treated as a Tuner this turn. If this card is sent to the GY: You can gain 500 LP. You can only use each effect of Aromage Laurel once per turn.

## SIMORGH_BIRD_OF_ANCESTRY (activated)
- file: `src_custom/activated_effects/simorgh_bird_of_ancestry.c`
- clone: `src_custom/activated_effects/tatsunoko.c` (TATSUNOKO)
- text: Both players Tribute Summon WIND monsters with 1 less Tribute than required. If you Tribute Summon this card by Tributin Both players Tribute Summon WIND monsters with 1 less Tribute than required. If you Tribute Summon this card by Tributing only WIND monsters, return up to 2 cards your opponent controls to their owner's hand. This card is treated as a Normal Monster while in your hand.

## TEST_TIGER (activated)
- file: `src_custom/activated_effects/test_tiger.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: Hand SS with GB; Tribute for Deck SS. If you control a face-up Gladiator Beast monster, you can Special Summon this card (from your hand). You can Tribute this card to target 1 face-up Gladiator Beast monster you control; shuffle that target into the Deck, then Special Summon 1 Gladiator Beast from your Deck, and treat it as if it was Special Summoned by the effect of a Gladiator Beast monster.

## NECROFACE (activated)
- file: `src_custom/activated_effects/necroface.c`
- clone: `src_custom/activated_effects/aromage_cananga.c` (AROMAGE_CANANGA)
- text: If this card is Normal Summoned: Shuffle all banished cards into the Deck. This card gains 100 ATK for each card shuffle If this card is Normal Summoned: Shuffle all banished cards into the Deck. This card gains 100 ATK for each card shuffled into the Main Deck by this effect. If this card is banished: Each player banishes 5 cards from the top of their Deck (or their entire Deck, if less than 5).
