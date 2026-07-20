# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MONTAGE_DRAGON (activated)
- file: `src_custom/activated_effects/montage_dragon.c`
- clone: `src_custom/activated_effects/chimeratech_fortress_dragon.c` (CHIMERATECH_FORTRESS_DRAGON)
- text: Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by sending 3 other monsters from your hand to t Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by sending 3 other monsters from your hand to the Graveyard, and cannot be Special Summoned by other ways. This card's ATK becomes the combined original Levels of the sent monsters x 300.

## MORPHTRONIC_LANTRON (activated)
- file: `src_custom/activated_effects/morphtronic_lantron.c`
- clone: `src_custom/activated_effects/morphtronic_datatron.c` (MORPHTRONIC_DATATRON)
- text: - While in Attack Position: Any effect damage you would take from an opponent's card effect is inflicted to your opponen - While in Attack Position: Any effect damage you would take from an opponent's card effect is inflicted to your opponent instead. - While in Defense Position: When this card is destroyed by battle and sent to the Graveyard, you take no Battle Damage this turn.

## GRAVEKEEPERS_HEADMAN (activated)
- file: `src_custom/activated_effects/gravekeepers_headman.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: If this card is Summoned: You can target 1 Level 4 "Gravekeeper's" monster in your GY; Special Summon it in Attack Posit If this card is Summoned: You can target 1 Level 4 Gravekeeper's monster in your GY; Special Summon it in Attack Position or face-down Defense Position. You can only use this effect of Gravekeeper's Headman once per turn. This effect is unaffected by Necrovalley.

## NEO_SPACE_CONNECTOR (activated)
- file: `src_custom/activated_effects/neo_space_connector.c`
- clone: `src_custom/activated_effects/chimeratech_megafleet_dragon.c` (CHIMERATECH_MEGAFLEET_DRAGON)
- text: NS: SS Neo/Neos; Tribute: GY SS. When this card is Normal Summoned: You can Special Summon 1 Neo-Spacian monster or 1 Elemental HERO Neos from your hand or Deck in Defense Position. You can Tribute this card, then target 1 Neo-Spacian monster or 1 Elemental HERO Neos in your GY; Special Summon it in Defense Position. You can only use each effect of Neo Space Connector once per turn.
