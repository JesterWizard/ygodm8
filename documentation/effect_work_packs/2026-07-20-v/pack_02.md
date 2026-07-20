# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HUMID_WINDS (trap)
- file: `src_custom/trap_effects/humid_winds.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: Pay 1000: search Aroma. If LP lower: gain 500. Each OPT. You can pay 1000 LP; add 1 Aroma monster from your Deck to your hand. If your LP is lower than your opponent's: You can gain 500 LP. You can only use each effect of Humid Winds once per turn.

## SOUL_LEVY (trap)
- file: `src_custom/trap_effects/soul_levy.c`
- clone: `src_custom/trap_effects/light_spiral.c` (LIGHT_SPIRAL)
- text: You can only control 1 Soul Levy. Each time your opponent Special Summons a monster(s), send the top 3 cards of your o You can only control 1 Soul Levy. Each time your opponent Special Summons a monster(s), send the top 3 cards of your opponent's Deck to the GY.

## MORPHTRONIC_BIND (trap)
- file: `src_custom/trap_effects/morphtronic_bind.c`
- clone: `src_custom/trap_effects/morphtronic_monitron.c` (MORPHTRONIC_MONITRON)
- text: While you control a face-up Morphtronic monster, all Level 4 or higher monsters your opponent controls cannot attack o While you control a face-up Morphtronic monster, all Level 4 or higher monsters your opponent controls cannot attack or change their battle positions.

## MAGICIANS_CIRCLE (trap)
- file: `src_custom/trap_effects/magicians_circle.c`
- clone: `src_custom/trap_effects/embodiment_of_apophis.c` (EMBODIMENT_OF_APOPHIS)
- text: When a Spellcaster monster declares an attack: Each player Special Summons 1 Spellcaster monster with 2000 or less ATK f When a Spellcaster monster declares an attack: Each player Special Summons 1 Spellcaster monster with 2000 or less ATK from their Deck in Attack Position.
