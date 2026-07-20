# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## RYKO_LIGHTSWORN_HUNTER (activated)
- file: `src_custom/activated_effects/ryko_lightsworn_hunter.c`
- clone: `src_custom/activated_effects/elemental_hero_tempest.c` (ELEMENTAL_HERO_TEMPEST)
- text: FLIP: destroy 1; mill top 3. FLIP: Apply these effects (simultaneously). You can destroy 1 card on the field. Send the top 3 cards of your Deck to the GY.

## FLAME_RULER (activated)
- file: `src_custom/activated_effects/flame_ruler.c`
- clone: `src_custom/activated_effects/granmarg_the_rock_monarch.c` (GRANMARG_THE_ROCK_MONARCH)
- text: This card can be treated as 2 Tributes for the Tribute Summon of a FIRE monster. This card can be treated as 2 Tributes for the Tribute Summon of a FIRE monster.

## THE_CALCULATOR (activated)
- file: `src_custom/activated_effects/the_calculator.c`
- clone: `src_custom/activated_effects/venom_serpent.c` (VENOM_SERPENT)
- text: The ATK of this card is the combined Levels of all face-up monsters you control x 300. The ATK of this card is the combined Levels of all face-up monsters you control x 300.

## WARM_WORM (activated)
- file: `src_custom/activated_effects/warm_worm.c`
- clone: `src_custom/activated_effects/nimble_momonga.c` (NIMBLE_MOMONGA)
- text: If this card is destroyed, send the top 3 cards of your opponent's Deck to the Graveyard. If this card is destroyed, send the top 3 cards of your opponent's Deck to the Graveyard.
