# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HERALD_OF_CREATION (activated)
- file: `src_custom/activated_effects/herald_of_creation.c`
- clone: `src_custom/activated_effects/mask_of_darkness.c` (MASK_OF_DARKNESS)
- text: Once per turn: You can discard 1 card, then target 1 Level 7 or higher monster in your Graveyard; add that  Once per turn: You can discard 1 card, then target 1 Level 7 or higher monster in your Graveyard; add that target to your hand.

## REPTILIANNE_MEDUSA (activated)
- file: `src_custom/activated_effects/reptilianne_medusa.c`
- clone: `src_custom/activated_effects/elemental_hero_neos_alius.c` (ELEMENTAL_HERO_NEOS_ALIUS)
- text: Discard 1; select face-up opp monster; its ATK becomes 0. Send 1 card from your hand to the Graveyard and select 1 face-up monster your opponent controls. The ATK of the selected monster becomes 0, and it cannot change its battle position.

## LUMINA_LIGHTSWORN_SUMMONER (activated)
- file: `src_custom/activated_effects/lumina_lightsworn_summoner.c`
- clone: `src_custom/activated_effects/jain_lightsworn_paladin.c` (JAIN_LIGHTSWORN_PALADIN)
- text: Discard to SS low LS; mill 3. Once per turn: You can discard 1 card, then target 1 Level 4 or lower Lightsworn monster in your GY; Special Summon that target. Once per turn, during your End Phase: Send the top 3 cards of your Deck to the GY.

## VISION_HERO_ADORATION (activated)
- file: `src_custom/activated_effects/vision_hero_adoration.c`
- clone: `src_custom/activated_effects/copycat.c` (COPYCAT)
- text: 2 HERO monsters Once per turn: You can target 1 face-up monster your opponent controls and 1 other HERO monster you control; the opponent's targeted monster loses ATK and DEF equal to the ATK of your targeted monster, until the end of this turn.
