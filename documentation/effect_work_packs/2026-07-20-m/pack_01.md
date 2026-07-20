# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## WEAPON_CHANGE (spell)
- file: `src_custom/spell_effects/weapon_change.c`
- clone: `src_custom/spell_effects/amazoness_fighting_spirit.c` (AMAZONESS_FIGHTING_SPIRIT)
- text: Once during each of your Standby Phases: You can pay 700 Life Points, then target 1 Warrior or Machine-Type monster you  Once during each of your Standby Phases: You can pay 700 Life Points, then target 1 Warrior or Machine-Type monster you control; switch the current ATK and DEF of that target until the end of your opponent's next turn.

## CHAIN_SUMMONING (spell)
- file: `src_custom/spell_effects/chain_summoning.c`
- clone: `src_custom/spell_effects/chain_energy.c` (CHAIN_ENERGY)
- text: Activate as Chain Link 3 or higher: You can conduct up to 3 Normal Summons/Sets this turn, not just 1. You cannot activa Activate as Chain Link 3 or higher: You can conduct up to 3 Normal Summons/Sets this turn, not just 1. You cannot activate this card if multiple cards with the same name, or the effects of such cards, are already activated in that Chain.

## LEMURIA_THE_FORGOTTEN_CITY (spell)
- file: `src_custom/spell_effects/lemuria_the_forgotten_city.c`
- text: This card's name is treated as Umi. All WATER monsters gain 200 ATK and DEF. Once per turn, during your Main Phase: Yo This card's name is treated as Umi. All WATER monsters gain 200 ATK and DEF. Once per turn, during your Main Phase: You can have all WATER monsters you currently control gain Levels equal to the number of WATER monsters you currently control, until the End Phase.

## EVIL_MIND (spell)
- file: `src_custom/spell_effects/evil_mind.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: If Fiend: draw / search HERO or Dark Fusion / search Poly by GY count. If you control a Fiend monster: Activate 1 of these effects, based on the number of monsters in your opponent's GY; 1+: Draw 1 card. 4+: Add 1 HERO monster or 1 Dark Fusion from your Deck to your hand. 10+: Add 1 Polymerization Spell or 1 Fusion Spell from your Deck to your hand. You can only activate 1 Evil Mind per turn.
