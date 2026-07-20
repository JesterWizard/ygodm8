# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DEMISE_KING_OF_ARMAGEDDON (activated)
- file: `src_custom/activated_effects/demise_king_of_armageddon.c`
- clone: `src_custom/activated_effects/elemental_hero_tempest.c` (ELEMENTAL_HERO_TEMPEST)
- text: You can Ritual Summon this card with End of the World. You can pay 2000 LP; destroy all other cards on the field.

## VENOM_SERPENT (activated)
- file: `src_custom/activated_effects/venom_serpent.c`
- clone: `src_custom/activated_effects/light_end_dragon.c` (LIGHT_END_DRAGON)
- text: OPT: place 1 Venom Counter on opp monster. Once per turn, you can place 1 Venom Counter on 1 monster your opponent controls.

## GRAVEKEEPERS_CURSE (activated)
- file: `src_custom/activated_effects/gravekeepers_curse.c`
- clone: `src_custom/activated_effects/dice_jar.c` (DICE_JAR)
- text: If this card is Summoned: Inflict 500 damage to your opponent. If this card is Summoned: Inflict 500 damage to your opponent.

## MIRAGE_DRAGON (activated)
- file: `src_custom/activated_effects/mirage_dragon.c`
- clone: `src_custom/activated_effects/elemental_hero_ocean.c` (ELEMENTAL_HERO_OCEAN)
- text: Your opponent cannot activate Trap Cards during the Battle Phase. Your opponent cannot activate Trap Cards during the Battle Phase.
