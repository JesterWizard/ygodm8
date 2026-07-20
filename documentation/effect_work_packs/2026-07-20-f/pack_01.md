# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MORPHTRONIC_ACCELERATOR (spell)
- file: `src_custom/spell_effects/morphtronic_accelerator.c`
- clone: `src_custom/spell_effects/polymerization.c` (POLYMERIZATION)
- text: Return 1 Morphtronic monster from your hand to the Deck. Destroy 1 card on the field, and draw 1 card. Return 1 Morphtronic monster from your hand to the Deck. Destroy 1 card on the field, and draw 1 card.

## DARK_BURNING_MAGIC (spell)
- file: `src_custom/spell_effects/dark_burning_magic.c`
- clone: `src_custom/spell_effects/dark_burning_attack.c` (DARK_BURNING_ATTACK)
- text: If you control Dark Magician and Dark Magician Girl: destroy all opponent cards. If you control monsters whose original names are Dark Magician and Dark Magician Girl: Destroy all cards your opponent controls.

## REPTILIANNE_SPAWN (spell)
- file: `src_custom/spell_effects/reptilianne_spawn.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: Banish 1 Reptilianne from GY; SS 2 Tokens (ATK/DEF 0). Remove from play 1 Reptilianne monster from your Graveyard. Special Summon 2 Reptilianne Tokens (Reptile-Type/EARTH/Level 1/ATK 0/DEF 0) to your side of the field.

## LIGHTSWORN_SABRE (spell)
- file: `src_custom/spell_effects/lightsworn_sabre.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: Equip Lightsworn +700; re-equip mill. Equip only to a Lightsworn monster. It gains 700 ATK. When this card is sent from your Deck to the Graveyard: You can target 1 Lightsworn monster you control; equip this card to that target.
