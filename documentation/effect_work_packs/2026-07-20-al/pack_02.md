# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GUNGNIR_DRAGON_OF_THE_ICE_BARRIER (activated)
- file: `src_custom/activated_effects/gungnir_dragon_of_the_ice_barrier.c`
- clone: `src_custom/activated_effects/amazoness_sage.c` (AMAZONESS_SAGE)
- text: 1 Tuner + 1 or more non-Tuner WATER monsters
Once per turn: You can discard up to 2 cards to the Graveyard to target the 1 Tuner + 1 or more non-Tuner WATER monsters Once per turn: You can discard up to 2 cards to the Graveyard to target the same number of cards your opponent controls; destroy them.

## JUNK_SYNCHRON (activated)
- file: `src_custom/activated_effects/junk_synchron.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: When Normal Summoned: Target 1 Level 2 or lower monster in your GY; Special Summon it in Defense Position with effects negated. When this card is Normal Summoned: You can target 1 Level 2 or lower monster in your Graveyard; Special Summon that target in Defense Position, but it has its effects negated.

## TRISHULA_DRAGON_OF_THE_ICE_BARRIER (activated)
- file: `src_custom/activated_effects/trishula_dragon_of_the_ice_barrier.c`
- clone: `src_custom/activated_effects/mask_of_darkness.c` (MASK_OF_DARKNESS)
- text: 1 Tuner + 2+ non-Tuner monsters
When this card is Synchro Summoned: You can banish up to 1 card each from your opponent' 1 Tuner + 2+ non-Tuner monsters When this card is Synchro Summoned: You can banish up to 1 card each from your opponent's hand, field, and GY. (The card in the hand is chosen at random.)

## SHADDOLL_DRAGON (activated)
- file: `src_custom/activated_effects/shaddoll_dragon.c`
- clone: `src_custom/activated_effects/mask_of_darkness.c` (MASK_OF_DARKNESS)
- text: FLIP: bounce 1 opp. Sent by effect: destroy 1 opp S/T. FLIP: You can target 1 card your opponent controls; return it to the hand. If this card is sent to the GY by a card effect: You can target 1 Spell/Trap on the field; destroy it. You can only use 1 Shaddoll Dragon effect per turn, and only once that turn.
