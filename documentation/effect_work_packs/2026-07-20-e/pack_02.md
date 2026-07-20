# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## LEVEL_TUNING (spell)
- file: `src_custom/spell_effects/level_tuning.c`
- clone: `src_custom/spell_effects/level_limit_area_b.c` (LEVEL_LIMIT_AREA_B)
- text: Reduce the Level of all face-up monsters you control by 1, until the End Phase. Reduce the Level of all face-up monsters you control by 1, until the End Phase.

## DARK_BURNING_ATTACK (spell)
- file: `src_custom/spell_effects/dark_burning_attack.c`
- clone: `src_custom/spell_effects/burden_of_the_mighty.c` (BURDEN_OF_THE_MIGHTY)
- text: If you control Dark Magician Girl: destroy all face-up opponent monsters. If you control a Dark Magician Girl monster: Destroy all face-up monsters your opponent controls.

## AQUA_JET (spell)
- file: `src_custom/spell_effects/aqua_jet.c`
- clone: `src_custom/spell_effects/h_heated_heart.c` (H_HEATED_HEART)
- text: Target 1 face-up Fish, Sea Serpent, or Aqua-Type monster you control; it gains 1000 ATK. Target 1 face-up Fish, Sea Serpent, or Aqua-Type monster you control; it gains 1000 ATK.

## CONTACT (spell)
- file: `src_custom/spell_effects/contact.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: Send Chrysalis; SS named monsters. Send all Chrysalis monsters you control to the Graveyard, and Special Summon 1 monster from your hand or Deck that is written in the card text of those cards.
