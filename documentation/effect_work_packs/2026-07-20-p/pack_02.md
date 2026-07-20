# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GENERATION_NEXT (spell)
- file: `src_custom/spell_effects/generation_next.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Add/SS Neo-HERO by LP gap. If your LP are lower than your opponent's: Add to your hand, or Special Summon, 1 Elemental HERO monster, Kuriboh monster, or Neo-Spacian monster from your Deck or GY, with ATK less than or equal to the difference in LPs, also for the rest of this turn, you cannot activate cards, or the effects of cards, with the same name as that card. You can only activate 1 Generation Next per turn.

## SPELL_GEAR (spell)
- file: `src_custom/spell_effects/spell_gear.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Send 3 Ancient Gear cards you control to the Graveyard. You can Special Summon up to 1 Ancient Gear Golem from your  Send 3 Ancient Gear cards you control to the Graveyard. You can Special Summon up to 1 Ancient Gear Golem from your hand and 1 from your Deck, ignoring the Summoning conditions. Then, destroy all monsters you control except Ancient Gear Golems. You cannot Normal Summon or Set until the end of your next turn.

## THE_CLAW_OF_HERMOS (spell)
- file: `src_custom/spell_effects/the_claw_of_hermos.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: (This card is also always treated as Legendary Dragon Hermos.)
Send 1 monster from your hand or field to the GY, of t (This card is also always treated as Legendary Dragon Hermos.) Send 1 monster from your hand or field to the GY, of the Type that is listed on a Fusion Monster that can only be Special Summoned with The Claw of Hermos (if that card is Set, reveal it), then Special Summon that Fusion Monster from your Extra Deck. You can only activate 1 The Claw of Hermos per turn.

## EN_WAVE (spell)
- file: `src_custom/spell_effects/en_wave.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Search Neo/Neos; GY revive E-HERO. If your Elemental HERO monster is used as material for a Fusion Summon, and sent to the GY or banished (except during the Damage Step): You can Special Summon 1 Neo-Spacian monster or 1 Elemental HERO Neos from your Deck. If a Neo-Spacian monster or Elemental HERO Neos you control or in your GY is shuffled into your Deck or Extra Deck (except during the Damage Step): You can Special Summon 1 Elemental HERO monster from your GY. You can only use each effect of E
