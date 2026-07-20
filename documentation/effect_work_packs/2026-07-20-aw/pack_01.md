# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SHADDOLL_HOUND (activated)
- file: `src_custom/activated_effects/shaddoll_hound.c`
- clone: `src_custom/activated_effects/mask_of_darkness.c` (MASK_OF_DARKNESS)
- text: FLIP: add Shaddoll from GY. Sent by effect: change battle position. FLIP: You can target 1 Shaddoll card in your GY; add it to your hand. If this card is sent to the GY by a card effect: You can target 1 monster on the field; change its battle position. (Flip monsters' effects are not activated at this time, except Shaddoll monsters'.) You can only use 1 Shaddoll Hound effect per turn, and only once that turn.

## VISION_HERO_GRAVITO (activated)
- file: `src_custom/activated_effects/vision_hero_gravito.c`
- clone: `src_custom/activated_effects/vision_hero_adoration.c` (VISION_HERO_ADORATION)
- text: If this card is Normal or Special Summoned: You can target 1 of your banished HERO monsters; add it to your hand. You  If this card is Normal or Special Summoned: You can target 1 of your banished HERO monsters; add it to your hand. You can Tribute this card, then target 2 Vision HERO Monster Cards in your Spell & Trap Zone; Special Summon them. You can only use each effect of Vision HERO Gravito once per turn.

## GRAVEKEEPERS_SHAMAN (activated)
- file: `src_custom/activated_effects/gravekeepers_shaman.c`
- clone: `src_custom/activated_effects/dark_magician_the_dragon_knight.c` (DARK_MAGICIAN_THE_DRAGON_KNIGHT)
- text: Gains 200 DEF for each "Gravekeeper's" monster in your GY. Negate all monster effects that activate in the GY, except "G Gains 200 DEF for each Gravekeeper's monster in your GY. Negate all monster effects that activate in the GY, except Gravekeeper's monsters. While Necrovalley is on the field, your opponent cannot activate Field Spell Cards, also Field Spell Cards cannot be destroyed by your opponent's card effects.

## ALECTOR_SOVEREIGN_OF_BIRDS (activated)
- file: `src_custom/activated_effects/alector_sovereign_of_birds.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: If your opponent controls 2 or more face-up monsters of the same Attribute, you can Special Summon this card (from your  If your opponent controls 2 or more face-up monsters of the same Attribute, you can Special Summon this card (from your hand). Once per turn: You can target 1 face-up card on the field; that target's effects are negated during this turn. There can only be 1 face-up Alector, Sovereign of Birds on the field.
