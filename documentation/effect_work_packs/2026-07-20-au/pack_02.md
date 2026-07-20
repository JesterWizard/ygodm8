# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## LIGHTRAY_DAEDALUS (activated)
- file: `src_custom/activated_effects/lightray_daedalus.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by having 4 or more LIGHT monsters in your Grav Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by having 4 or more LIGHT monsters in your Graveyard, and cannot be Special Summoned by other ways. Once per turn: You can target 1 Field Spell Card and 2 other cards on the field; destroy them.

## NATURIA_BEAST (activated)
- file: `src_custom/activated_effects/naturia_beast.c`
- clone: `src_custom/activated_effects/destiny_hero_diamond_dude.c` (DESTINY_HERO_DIAMOND_DUDE)
- text: 1 EARTH Tuner + 1+ non-Tuner EARTH monsters 
When a Spell Card is activated (Quick Effect): You can send the top 2 card 1 EARTH Tuner + 1+ non-Tuner EARTH monsters When a Spell Card is activated (Quick Effect): You can send the top 2 cards of your Deck to the GY; negate the activation, and if you do, destroy it. This card must be face-up on the field to activate and to resolve this effect.

## MORPHTRONIC_CAMERAN (activated)
- file: `src_custom/activated_effects/morphtronic_cameran.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: - While in Attack Position: When this card is destroyed by battle, you can Special Summon 1 Level 4 or lower Morphtroni - While in Attack Position: When this card is destroyed by battle, you can Special Summon 1 Level 4 or lower Morphtronic monster from your hand or Graveyard, except Morphtronic Cameran. - While in Defense Position: Morphtronic monsters on the field cannot be targeted by effects.

## POWER_TOOL_DRAGON (activated)
- file: `src_custom/activated_effects/power_tool_dragon.c`
- clone: `src_custom/activated_effects/herald_of_perfection.c` (HERALD_OF_PERFECTION)
- text: OPT: reveal 3 Equips; opp adds 1. Destroy protect via Equip. 1 Tuner + 1 or more non-Tuner monsters Once per turn: You can reveal 3 Equip Spell Cards from your Deck, then your opponent randomly adds 1 of them to your hand, and you shuffle the rest back into your Deck. If this card would be destroyed while equipped with an Equip Spell Card(s), you can send 1 of those cards to the Graveyard instead.
