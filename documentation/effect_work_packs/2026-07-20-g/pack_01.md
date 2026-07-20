# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GLADIATOR_BEASTS_BATTLE_GLADIUS (spell)
- file: `src_custom/spell_effects/gladiator_beasts_battle_gladius.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: +300 ATK equip; recycle on tag. Equip only to a Gladiator Beast monster. It gains 300 ATK. When the equipped monster is returned from your side of the field to the Deck and this card is sent to the Graveyard, return this card to your hand.

## COLD_WAVE (spell)
- file: `src_custom/spell_effects/cold_wave.c`
- clone: `src_custom/spell_effects/mage_power.c` (MAGE_POWER)
- text: No Spell/Trap activations until your next Standby Phase. Activate only at start of Main Phase 1. This card can only be activated at the start of Main Phase 1. Until your next turn, you and your opponent cannot play or Set any Spell or Trap Cards.

## GRAVEKEEPERS_STELE (spell)
- file: `src_custom/spell_effects/gravekeepers_stele.c`
- clone: `src_custom/spell_effects/twin_swords_of_flashing_light_tryce.c` (TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE)
- text: Target 2 "Gravekeeper's" monsters in your GY; add those targets to your hand. This effect cannot be negated by the effec Target 2 Gravekeeper's monsters in your GY; add those targets to your hand. This effect cannot be negated by the effect of Necrovalley.

## FORBIDDEN_LANCE (spell)
- file: `src_custom/spell_effects/forbidden_lance.c`
- clone: `src_custom/spell_effects/h_heated_heart.c` (H_HEATED_HEART)
- text: Target 1 face-up monster on the field; until the end of this turn, that target loses 800 ATK, but is unaffected by the e Target 1 face-up monster on the field; until the end of this turn, that target loses 800 ATK, but is unaffected by the effects of other Spells/Traps.
