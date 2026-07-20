# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SHADDOLL_BEAST (activated)
- file: `src_custom/activated_effects/shaddoll_beast.c`
- clone: `src_custom/activated_effects/elemental_hero_bubbleman.c` (ELEMENTAL_HERO_BUBBLEMAN)
- text: FLIP: draw 2, discard 1. Sent by effect: draw 1. 1/turn. FLIP: You can draw 2 cards, then discard 1 card. If this card is sent to the GY by a card effect: You can draw 1 card. You can only use 1 Shaddoll Beast effect per turn, and only once that turn.

## GRAVEKEEPERS_PRIESTESS (activated)
- file: `src_custom/activated_effects/gravekeepers_priestess.c`
- clone: `src_custom/activated_effects/gravekeepers_guard.c` (GRAVEKEEPERS_GUARD)
- text: While there is no face-up Field Spell, the field is treated as "Necrovalley". All "Gravekeeper's" monsters on the field  While there is no face-up Field Spell, the field is treated as Necrovalley. All Gravekeeper's monsters on the field gain 200 ATK/DEF.

## EVIL_HERO_LIGHTNING_GOLEM (activated)
- file: `src_custom/activated_effects/evil_hero_lightning_golem.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: Dark Fusion. OPT: destroy 1 monster on the field. Elemental HERO Sparkman + Elemental HERO Clayman Must be Special Summoned with Dark Fusion and cannot be Special Summoned by other ways. Once per turn: You can target 1 monster on the field; destroy that target.

## CHARM_OF_SHABTI (activated)
- file: `src_custom/activated_effects/charm_of_shabti.c`
- clone: `src_custom/activated_effects/venom_boa.c` (VENOM_BOA)
- text: During either player's turn: You can discard this card; until the End Phase, "Gravekeeper's" monsters you control cannot During either player's turn: You can discard this card; until the End Phase, Gravekeeper's monsters you control cannot be destroyed by battle.
