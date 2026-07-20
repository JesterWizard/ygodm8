# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MARCH_OF_THE_DARK_BRIGADE (spell)
- file: `src_custom/spell_effects/march_of_the_dark_brigade.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Add LS from GY; banish Level cards. Target 1 Lightsworn monster in your GY that has a Level; add it to your hand, then banish a number of cards from the top of your Deck equal to the original Level of that monster in your hand. You can only activate 1 March of the Dark Brigade per turn.

## INFERNO_FIRE_BLAST (spell)
- file: `src_custom/spell_effects/inferno_fire_blast.c`
- clone: `src_custom/spell_effects/h_heated_heart.c` (H_HEATED_HEART)
- text: Target 1 "Red-Eyes B. Dragon" in your Monster Zone; inflict damage to your opponent equal to its original ATK. "Red-Eyes Target 1 Red-Eyes B. Dragon in your Monster Zone; inflict damage to your opponent equal to its original ATK. Red-Eyes B. Dragon cannot attack the turn you activate this card.

## VENOM_SHOT (spell)
- file: `src_custom/spell_effects/venom_shot.c`
- clone: `src_custom/spell_effects/venom_swamp.c` (VENOM_SWAMP)
- text: Send Reptile; place 2 Venom Counters. Activate only while you control a face-up Venom monster, Vennominaga the Deity of Poisonous Snakes, or Vennominon the King of Poisonous Snakes. Send 1 Reptile-Type monster from your Deck to the Graveyard and place 2 Venom Counters on 1 face-up monster your opponent controls.

## CONTINUOUS_DESTRUCTION_PUNCH (spell)
- file: `src_custom/spell_effects/continuous_destruction_punch.c`
- clone: `src_custom/spell_effects/venom_swamp.c` (VENOM_SWAMP)
- text: If attacked DEF monster has higher DEF than attackers ATK: destroy attacker after damage calc. If the DEF of the attacked Defense Position monster on your side of the field is higher than the ATK of the attacking monster on your opponent's side of the field, destroy the attacking monster. Damage calculation is applied normally.
