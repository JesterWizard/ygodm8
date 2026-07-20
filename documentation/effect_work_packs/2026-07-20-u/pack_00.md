# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DES_COUNTERBLOW (trap)
- file: `src_custom/trap_effects/des_counterblow.c`
- clone: `src_custom/trap_effects/bottomless_shifting_sand.c` (BOTTOMLESS_SHIFTING_SAND)
- text: Destroy any monster that inflicts Battle Damage to a player's Life Points by attacking directly. Destroy any monster that inflicts Battle Damage to a player's Life Points by attacking directly.

## SNAKE_DEITYS_COMMAND (trap)
- file: `src_custom/trap_effects/snake_deitys_command.c`
- clone: `src_custom/trap_effects/snake_whistle.c` (SNAKE_WHISTLE)
- text: Reveal Venom in hand; negate opp Spell activation and destroy it. Activate by showing your opponent 1 Venom monster in your hand. Negate the activation and effect of an opponent's Spell Card, and destroy it.

## BACKFIRE (trap)
- file: `src_custom/trap_effects/backfire.c`
- clone: `src_custom/trap_effects/coffin_seller.c` (COFFIN_SELLER)
- text: If a face-up FIRE monster(s) you control is destroyed and sent to the GY: Inflict 500 damage to your opponent. If a face-up FIRE monster(s) you control is destroyed and sent to the GY: Inflict 500 damage to your opponent.

## RISE_OF_THE_SNAKE_DEITY (trap)
- file: `src_custom/trap_effects/rise_of_the_snake_deity.c`
- clone: `src_custom/trap_effects/level_limit_area_a.c` (LEVEL_LIMIT_AREA_A)
- text: When Vennominon destroyed: SS Vennominaga from hand/Deck. When a face-up Vennominon the King of Poisonous Snakes you control is destroyed, except by battle: Special Summon 1 Vennominaga the Deity of Poisonous Snakes from your hand or Deck.
