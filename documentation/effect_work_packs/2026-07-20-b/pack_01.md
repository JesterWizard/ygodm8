# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## COCOON_REBIRTH (spell)
- file: `src_custom/spell_effects/cocoon_rebirth.c`
- clone: `src_custom/spell_effects/tribute_doll.c` (TRIBUTE_DOLL)
- optional template: `--fill tribute_summon COCOON_REBIRTH`
- text: Tribute Chrysalis; SS its Neo-Spacian. You can Tribute 1 face-up Chrysalis monster you control to Special Summon 1 Neo-Spacian monster written in the card text of that card from either player's Graveyard.

## MORPHTRONIC_RUSTY_ENGINE (spell)
- file: `src_custom/spell_effects/morphtronic_rusty_engine.c`
- clone: `src_custom/spell_effects/big_bang_shot.c` (BIG_BANG_SHOT)
- optional template: `--fill burn MORPHTRONIC_RUSTY_ENGINE`
- text: Equip only to a Morphtronic monster. If the equipped monster is destroyed, inflict damage to each player equal to its  Equip only to a Morphtronic monster. If the equipped monster is destroyed, inflict damage to each player equal to its original ATK.

## BACKUP_SQUAD (spell)
- file: `src_custom/spell_effects/backup_squad.c`
- clone: `src_custom/spell_effects/card_destruction.c` (CARD_DESTRUCTION)
- optional template: `--fill draw_n BACKUP_SQUAD`
- text: Each time you take 1000 or more damage by your opponent's card effect or their monster's attack: Draw 1 card for every 1 Each time you take 1000 or more damage by your opponent's card effect or their monster's attack: Draw 1 card for every 1000 damage you took.

## MONSTER_GATE (spell)
- file: `src_custom/spell_effects/monster_gate.c`
- clone: `src_custom/spell_effects/tribute_doll.c` (TRIBUTE_DOLL)
- optional template: `--fill tribute_summon MONSTER_GATE`
- text: Tribute 1 monster. Excavate until a Normal Summonable monster found. Special Summon it, send rest to GY. Tribute 1 monster; excavate cards from the top of your Deck until you excavate a monster that can be Normal Summoned/Set. Special Summon it, also send the other excavated cards to the GY.
