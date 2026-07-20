# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ANCIENT_GEAR_STATUE (activated)
- file: `src_custom/activated_effects/ancient_gear_statue.c`
- clone: `src_custom/activated_effects/ancient_gear_beast.c` (ANCIENT_GEAR_BEAST)
- text: If your opponent controls more monsters than you do, you can Special Summon this card (from your hand). You can only Spe If your opponent controls more monsters than you do, you can Special Summon this card (from your hand). You can only Special Summon Ancient Gear Statue once per turn this way. You can Tribute this card; Special Summon from your hand or Deck, 1 Ancient Gear Golem or 1 monster that mentions it, except Ancient Gear Statue, ignoring its Summoning conditions. You can only use this 

## DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC (activated)
- file: `src_custom/activated_effects/dark_magician_the_magician_of_black_magic.c`
- clone: `src_custom/activated_effects/elemental_hero_magma_neos.c` (ELEMENTAL_HERO_MAGMA_NEOS)
- text: Name=DM on field. If Shining Sarcophagus: SS from hand. If destroyed: SS and Set DM Spell/Trap. This card's name becomes Dark Magician while on the field. You can only use each of the following effects of Dark Magician the Magician of Black Magic once per turn. If Shining Sarcophagus is on the field: You can Special Summon this card from your hand. If this card is destroyed by card effect and a Level 5 or higher monster is on the field: You can Special Summon this card, then you can Set 1 Spell/

## AMAZONESS_PET_LIGER (activated)
- file: `src_custom/activated_effects/amazoness_pet_liger.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: "Amazoness Tiger" + 1 "Amazoness" monster
Once per battle, if this card attacks, during damage calculation: You can mak Amazoness Tiger + 1 Amazoness monster Once per battle, if this card attacks, during damage calculation: You can make this card gain 500 ATK during that damage calculation only. If your Amazoness monster attacked an opponent's monster, after damage calculation: You can target 1 face-up monster your opponent controls; it loses 800 ATK. Monsters your opponent controls cannot atta

## MORPHTRONIC_STAPLEN (activated)
- file: `src_custom/activated_effects/morphtronic_staplen.c`
- clone: `src_custom/activated_effects/morphtronic_boomboxen.c` (MORPHTRONIC_BOOMBOXEN)
- text: - While in Attack Position: Your opponent cannot select another monster as an attack target. If this card is destroyed b - While in Attack Position: Your opponent cannot select another monster as an attack target. If this card is destroyed by battle, the monster that destroyed this card loses 300 ATK. - While in Defense Position: This card cannot be destroyed by battle. If this card is attacked, after damage calculation, select 1 face-up Attack Position monster your opponent controls. Change it 
