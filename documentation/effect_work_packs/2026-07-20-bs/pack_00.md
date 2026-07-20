# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ARCANA_FORCE_XVIII_THE_MOON (permanent)
- file: `src_custom/permanent_effects/arcana_force_xviii_the_moon.c`
- clone: `src_custom/permanent_effects/arcana_force_vii_the_chariot.c` (ARCANA_FORCE_VII_THE_CHARIOT)
- text: Coin: SS Moon Token or change to Def. When this card is Summoned, toss a coin: Heads: During your Standby Phase, you can Special Summon 1 Moon Token (Fairy-Type/LIGHT/Level 1/ATK 0/DEF 0). Tails: During each of your End Phases, select 1 monster you control and give control of it to your opponent.

## EL_SHADDOLL_ANOYATYLLIS (permanent)
- file: `src_custom/permanent_effects/el_shaddoll_anoyatyllis.c`
- clone: `src_custom/permanent_effects/dark_magician_of_chaos.c` (DARK_MAGICIAN_OF_CHAOS)
- text: Lock SS from hand/GY via S/T. GY: add Shaddoll S/T from GY. 1 Shaddoll monster + 1 WATER monster Must first be Fusion Summoned. Neither player can Special Summon monsters from the hand or GY using Spell/Trap effects. If this card is sent to the GY: You can target 1 Shaddoll Spell/Trap in your GY; add it to your hand.

## GLADIATOR_BEAST_OCTAVIUS (permanent)
- file: `src_custom/permanent_effects/gladiator_beast_octavius.c`
- clone: `src_custom/permanent_effects/gladiator_beast_secutor.c` (GLADIATOR_BEAST_SECUTOR)
- text: Pop Set S/T; discard; tag out. When this card is Special Summoned by the effect of a Gladiator Beast monster: Target 1 face-down Spell or Trap Card in the Spell & Trap Card Zone; destroy that target. At the end of your Battle Phase, if this card attacked or was attacked: Shuffle this card into the Deck or discard 1 card.

## EVIL_HERO_MALICIOUS_FIEND (permanent)
- file: `src_custom/permanent_effects/evil_hero_malicious_fiend.c`
- clone: `src_custom/permanent_effects/evil_hero_malicious_edge.c` (EVIL_HERO_MALICIOUS_EDGE)
- text: Opp Battle Phase: their monsters must attack this if able. Evil HERO Malicious Edge + 1 Level 6 or higher Fiend monster Must be Special Summoned with Dark Fusion. During your opponent's Battle Phase, all monsters they control are changed to face-up Attack Position, and each monster they control must attack this card, if able.
