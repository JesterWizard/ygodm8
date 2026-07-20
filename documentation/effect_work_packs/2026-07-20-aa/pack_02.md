# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## NEXT (trap)
- file: `src_custom/trap_effects/next.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: SS Neo/Neos from hand/GY; lock ED. Special Summon any number of monsters with different names from your hand and/or GY, in Defense Position, that are all Neo-Spacian monsters or Elemental HERO Neos, but negate their effects, and as long as you control any of those Special Summoned monsters face-up, you cannot Special Summon monsters from the Extra Deck, except Fusion Monsters. You can only activate 1 NEXT per turn. If you control no cards, you can activate this card from your hand.

## FAVOURITE_CONTACT (trap)
- file: `src_custom/trap_effects/favourite_contact.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: Contact Fusion from anywhere. Special Summon 1 Fusion Monster from your Extra Deck that mentions a HERO monster as material, ignoring its Summoning conditions, by placing the Fusion Materials mentioned on it on the bottom of the Deck in any order, from among cards in your hand, field, GY, and/or your banished cards. If you placed Elemental HERO Neos into the Deck, neither player can return the monster Special Summoned by this effect to the Extra Deck. You can only activate 1 Favorite Contact per

## APPARATION (trap)
- file: `src_custom/trap_effects/apparation.c`
- clone: `src_custom/trap_effects/all_out_attacks.c` (ALL_OUT_ATTACKS)
- text: If a face-up HERO monster(s) you control is destroyed by battle or card effect: Special Summon 1 Level 4 or lower Vision HERO monster from your Deck, then you can halve the original ATK/DEF of 1 monster your opponent controls. You can only activate 1 Apparition per turn. If a face-up HERO monster(s) you control is destroyed by battle or card effect: Special Summon 1 Level 4 or lower Vision HERO monster from your Deck, then you can halve the original ATK/DEF of 1 monster your opponent controls. Y

## GLADIATOR_NAUMACHIA (trap)
- file: `src_custom/trap_effects/gladiator_naumachia.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: ATK = DEF boost; GY battle protect. While you control a Gladiator Beast monster, all monsters your opponent controls must attack, if able. Once per turn: You can shuffle 1 Gladiator Beast monster from your hand or GY into the Main Deck, then target 1 Gladiator Beast monster you control; it gains ATK equal to its original DEF until the end of this turn (even if this card leaves the field). If this card in the Spell & Trap Zone is destroyed by card effect: You can activate this effect; this turn, 
