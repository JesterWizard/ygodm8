# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ROYAL_TRIBUTE (spell)
- file: `src_custom/spell_effects/royal_tribute.c`
- text: If you control Necrovalley: Both players discard any monsters in their hands. If you control Necrovalley: Both players discard any monsters in their hands.

## MYSTIK_WOK (spell)
- file: `src_custom/spell_effects/mystik_wok.c`
- clone: `src_custom/spell_effects/dark_room_of_nightmare.c` (DARK_ROOM_OF_NIGHTMARE)
- text: Tribute 1 monster. Select either its ATK or DEF and gain that many Life Points. Tribute 1 monster. Select either its ATK or DEF and gain that many Life Points.

## NEX (spell)
- file: `src_custom/spell_effects/nex.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: Send Neo-Spacian; SS its Lv4 form. Send 1 face-up Neo-Spacian monster you control to the Graveyard. Special Summon 1 Level 4 monster with the same name from your Extra Deck.

## DIMENSION_FUSION (spell)
- file: `src_custom/spell_effects/dimension_fusion.c`
- clone: `src_custom/spell_effects/court_of_justice.c` (COURT_OF_JUSTICE)
- text: Pay 2000 LP. Both players Special Summon as many banished monsters as possible. Pay 2000 Life Points. Both players Special Summon as many of their removed from play monsters as possible.
