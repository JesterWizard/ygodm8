# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## IPIRIA (permanent)
- file: `src_custom/permanent_effects/ipiria.c`
- clone: `src_custom/permanent_effects/elemental_hero_sunrise.c` (ELEMENTAL_HERO_SUNRISE)
- text: If Summoned: draw 1. Once per turn. If this card is Summoned: Draw 1 card. You can only use this effect of Ipiria once per turn.

## ARCANA_FORCE_VIII_THE_STRENGTH (permanent)
- file: `src_custom/permanent_effects/arcana_force_viii_the_strength.c`
- clone: `src_custom/permanent_effects/elemental_hero_sunrise.c` (ELEMENTAL_HERO_SUNRISE)
- text: Coin: steal opp monster or lose yours. When Summoned: toss a coin. Heads: take control of 1 opp monster. Tails: opp takes control of 1 of yours (except this).

## KNIGHT_OF_PENTACLES (permanent)
- file: `src_custom/permanent_effects/knight_of_pentacles.c`
- clone: `src_custom/permanent_effects/elemental_hero_sunrise.c` (ELEMENTAL_HERO_SUNRISE)
- text: Coin: battle immune or fragile. When Summoned, toss a coin. Heads: cannot be destroyed by battle. Tails: cannot attack; if attacked by an opp monster, destroy this card.

## CYBER_KIRIN (permanent)
- file: `src_custom/permanent_effects/cyber_kirin.c`
- clone: `src_custom/permanent_effects/elemental_hero_sunrise.c` (ELEMENTAL_HERO_SUNRISE)
- text: While in Attack Position: negate Spell/Trap targeting this card. When destroyed by battle: draw 1. You can Tribute this card to make any effect damage you take this turn 0.
