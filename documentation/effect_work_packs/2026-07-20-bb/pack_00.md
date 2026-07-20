# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## BLUE_EYES_SOLID_DRAGON (activated)
- file: `src_custom/activated_effects/blue_eyes_solid_dragon.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: If Normal or Special Summoned: target 1 face-up opponent monster; negate its effects. When opponent If this card is Normal or Special Summoned: You can target 1 face-up monster your opponent controls; negate its effects. When your opponent activates a card or effect (Quick Effect): You can shuffle this card from the field into the Deck, and if you do, Special Summon 1 Blue-Eyes White Dragon from your Deck. You can only use each effect of Blue-Eyes Solid Dragon once per turn.

## MORPHTRONIC_VACUUMEN (activated)
- file: `src_custom/activated_effects/morphtronic_vacuumen.c`
- clone: `src_custom/activated_effects/morphtronic_boomboxen.c` (MORPHTRONIC_BOOMBOXEN)
- text: - While in Attack Position: Once per turn, you can send 1 Equip Card equipped to this card to the Graveyard to inflict 5 - While in Attack Position: Once per turn, you can send 1 Equip Card equipped to this card to the Graveyard to inflict 500 damage to your opponent. - While in Defense Position: Once per turn, you can equip 1 face-up Attack Position monster your opponent controls to this card as an Equip Card. (You can only equip 1 monster at a time to this card by this effect.)

## MORPHTRONIC_MAGNEN_BAR (activated)
- file: `src_custom/activated_effects/morphtronic_magnen_bar.c`
- clone: `src_custom/activated_effects/morphtronic_boomboxen.c` (MORPHTRONIC_BOOMBOXEN)
- text: - While in Attack Position: Once per turn, if you control exactly 2 other face-up Attack Position monsters, and no addit - While in Attack Position: Once per turn, if you control exactly 2 other face-up Attack Position monsters, and no additional monsters, this card gains the combined ATK of the other two monsters you control until the End Phase. The other two monsters cannot attack the turn you activate this effect. - While in Defense Position: Monsters you control cannot attack.

## ELEMENTAL_HERO_DARK_NEOS (activated)
- file: `src_custom/activated_effects/elemental_hero_dark_neos.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: Negate 1 Effect monster; End return. Elemental HERO Neos + Neo-Spacian Dark Panther Must first be Special Summoned (from your Extra Deck) by shuffling the above cards you control into the Deck. (You do not use Polymerization.) If this card is not already targeting a monster with its effect: You can target 1 face-up Effect Monster on the field; while you control this face-up card, that target's effect on the field is negated. During the End Phase: Shuffle this card into the Extra Deck.
