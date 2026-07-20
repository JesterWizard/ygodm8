# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## END_OF_THE_WORLD (spell)
- file: `src_custom/spell_effects/end_of_the_world.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: This card is used to Ritual Summon Ruin, Queen of Oblivion or Demise, King of Armageddon. You must also Tribute mons This card is used to Ritual Summon Ruin, Queen of Oblivion or Demise, King of Armageddon. You must also Tribute monsters from your hand or field whose total Levels exactly equal the Level of the Ritual Monster you Ritual Summon.

## HIDDEN_TEMPLES_OF_NECROVALLEY (spell)
- file: `src_custom/spell_effects/hidden_temples_of_necrovalley.c`
- clone: `src_custom/spell_effects/ancient_rules.c` (ANCIENT_RULES)
- text: Activate only if both a "Gravekeeper's" monster and "Necrovalley" are on the field. Neither player can Special Summon mo Activate only if both a Gravekeeper's monster and Necrovalley are on the field. Neither player can Special Summon monsters, except Gravekeeper's monsters. If either a Gravekeeper's monster or Necrovalley is not on the field, destroy this card.

## DOCTOR_D (spell)
- file: `src_custom/spell_effects/doctor_d.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Banish 1 Destiny HERO from GY; add to hand or Special Summon 1 Destiny HERO from GY. Banish 1 Destiny HERO monster from your GY; add to your hand or Special Summon 1 Destiny HERO monster from your GY. You can banish this card from your GY, then target 2 Destiny HERO monsters you control; choose 1 of those monsters, its ATK becomes the other monster's ATK, until the end of this turn.

## AROMA_GARDEN (spell)
- file: `src_custom/spell_effects/aroma_garden.c`
- clone: `src_custom/spell_effects/attack_pheromones.c` (ATTACK_PHEROMONES)
- text: Once/turn with Aroma: +500 LP, monsters +500. If Aroma destroyed: gain 1000 LP. Once per turn, if you control an Aroma monster: You can gain 500 LP, also all monsters you control gain 500 ATK and DEF until the end of your opponent's next turn (even if this card leaves the field). If a face-up Aroma monster you control is destroyed by battle or card effect and sent to the Graveyard: Gain 1000 LP.
