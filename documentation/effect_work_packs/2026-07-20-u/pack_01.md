# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## VENOM_BURN (trap)
- file: `src_custom/trap_effects/venom_burn.c`
- clone: `src_custom/trap_effects/dragon_s_rage.c` (DRAGON_S_RAGE)
- text: Remove Venom Counters; 700 damage each. Select 1 monster with a Venom Counter(s). Remove all Venom Counters from that card, and inflict 700 damage to your opponent for each Venom Counter removed.

## LIGHTSWORN_JUDGEMENT (trap)
- file: `src_custom/trap_effects/lightsworn_judgement.c`
- clone: `src_custom/trap_effects/light_spiral.c` (LIGHT_SPIRAL)
- text: Topdeck; mill to search JD. Place this card on top of the Deck. If this card is sent from the Deck to the Graveyard by a Lightsworn monster's effect: You can add 1 Judgment Dragon from your Deck to your hand.

## GLADIATOR_BEASTS_MEDUSA_SHIELD (trap)
- file: `src_custom/trap_effects/gladiator_beasts_medusa_shield.c`
- clone: `src_custom/trap_effects/light_spiral.c` (LIGHT_SPIRAL)
- text: Protect GB; negate; Set Trap from Deck. Target 1 Gladiator Beast you control; it cannot be destroyed by card effects. Once per turn: negate 1 opp monster effect. If sent to GY this turn: Set 1 Gladiator Beast Trap from Deck.

## AEGIS_OF_THE_OCEAN_DRAGON_LORD (trap)
- file: `src_custom/trap_effects/aegis_of_the_ocean_dragon_lord.c`
- clone: `src_custom/trap_effects/level_limit_area_a.c` (LEVEL_LIMIT_AREA_A)
- text: Until the End Phase, face-up Level 3 or lower WATER monsters you control cannot be destroyed by battle or by card effect Until the End Phase, face-up Level 3 or lower WATER monsters you control cannot be destroyed by battle or by card effects.
