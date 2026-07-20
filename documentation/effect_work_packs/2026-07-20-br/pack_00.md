# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## JUNK_WARRIOR (permanent)
- file: `src_custom/permanent_effects/junk_warrior.c`
- clone: `src_custom/permanent_effects/reptilianne_viper.c` (REPTILIANNE_VIPER)
- text: If Synchro Summoned: gains ATK equal to Lv2- monsters you control. Junk Synchron + 1 or more non-Tuner monsters If this card is Synchro Summoned: It gains ATK equal to the total ATK of all Level 2 or lower monsters you currently control.

## GLADIATOR_BEAST_TYGERIUS (permanent)
- file: `src_custom/permanent_effects/gladiator_beast_tygerius.c`
- clone: `src_custom/permanent_effects/gladiator_beast_torax.c` (GLADIATOR_BEAST_TORAX)
- text: Discard; search GB; tag out. This card cannot be used as a Fusion Material Monster. When this card is Special Summoned by the effect of a Gladiator Beast monster, you can discard 1 Gladiator Beast card to add 1 Gladiator Beast monster from your Deck to your hand.

## GLADIATOR_BEAST_SECUTOR (permanent)
- file: `src_custom/permanent_effects/gladiator_beast_secutor.c`
- clone: `src_custom/permanent_effects/gladiator_beast_torax.c` (GLADIATOR_BEAST_TORAX)
- text: Tag out into 2 Gladiator Beasts. If this card was Special Summoned by the effect of a Gladiator Beast monster, then at the end of any Battle Phase in which this card attacked or was attacked: Special Summon 2 Gladiator Beast monsters from your Deck, except Gladiator Beast Secutor.

## ARCANA_FORCE_XXI_THE_WORLD (permanent)
- file: `src_custom/permanent_effects/arcana_force_xxi_the_world.c`
- clone: `src_custom/permanent_effects/arcana_force_vi_the_lovers.c` (ARCANA_FORCE_VI_THE_LOVERS)
- text: Coin: skip opp turn or your next turn. When this card is Summoned, toss a coin: Heads: During your End Phase, you can send 2 monsters you control to the Graveyard to skip your opponent's next turn. Tails: During your opponent's Draw Phase, add the top card of their Graveyard to their hand.
