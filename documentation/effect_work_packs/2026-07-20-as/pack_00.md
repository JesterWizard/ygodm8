# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SHADDOLL_FALCO (activated)
- file: `src_custom/activated_effects/shaddoll_falco.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: FLIP: SS Shaddoll face-down. Sent by effect: SS this face-down. FLIP: You can target 1 Shaddoll monster in your GY, except Shaddoll Falco; Special Summon it in face-down Defense Position. If this card is sent to the GY by a card effect: You can Special Summon it in face-down Defense Position. You can only use 1 Shaddoll Falco effect per turn, and only once that turn.

## NAELSHADDOLL_ARIEL (activated)
- file: `src_custom/activated_effects/naelshaddoll_ariel.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: FLIP: SS banished Shaddoll. Sent by effect: banish up to 3 from GYs. FLIP: You can target 1 of your banished Shaddoll monsters; Special Summon it in face-up or face-down Defense Position. If this card is sent to the GY by a card effect: You can target up to 3 cards in the GY(s); banish them. You can only use 1 Naelshaddoll Ariel effect per turn, and only once that turn.

## TURBO_SYNCHRON (activated)
- file: `src_custom/activated_effects/turbo_synchron.c`
- clone: `src_custom/activated_effects/turbo_booster.c` (TURBO_BOOSTER)
- text: When this card declares an attack: You can change the attack target to Defense Position. When you take battle damage whi When this card declares an attack: You can change the attack target to Defense Position. When you take battle damage while this card is attacking: You can Special Summon 1 monster from your hand with ATK less than or equal to the battle damage you took.

## ELEMENTAL_HERO_GRAND_NEOS (activated)
- file: `src_custom/activated_effects/elemental_hero_grand_neos.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: Bounce 1 opp monster; End return. Elemental HERO Neos + Neo-Spacian Grand Mole Must first be Special Summoned (from your Extra Deck) by shuffling the above cards you control into the Deck. (You do not use Polymerization.) Once per turn: You can target 1 monster your opponent controls; return that target to the hand. During the End Phase: Shuffle this card into the Extra Deck.
