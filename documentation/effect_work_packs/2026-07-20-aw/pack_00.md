# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HARPIE_CHANNELER (activated)
- file: `src_custom/activated_effects/harpie_channeler.c`
- clone: `src_custom/activated_effects/chimeratech_megafleet_dragon.c` (CHIMERATECH_MEGAFLEET_DRAGON)
- text: Discard Harpie; SS Harpie from Deck. Lv7 with Dragon. Name Lady. You can discard 1 Harpie card; Special Summon 1 Harpie monster from your Deck in face-up Defense Position, except Harpie Channeler. You can only use this effect of Harpie Channeler once per turn. While you control a Dragon-Type monster, this card's Level becomes 7. This card's name becomes Harpie Lady while it is on the field or in the Graveyard.

## GRAVEKEEPERS_SPIRITUALIST (activated)
- file: `src_custom/activated_effects/gravekeepers_spiritualist.c`
- clone: `src_custom/activated_effects/gravekeepers_guard.c` (GRAVEKEEPERS_GUARD)
- text: During your Main Phase, if "Necrovalley" is on the field: You can Fusion Summon 1 Spellcaster Fusion Monster from your E During your Main Phase, if Necrovalley is on the field: You can Fusion Summon 1 Spellcaster Fusion Monster from your Extra Deck, using this card you control and other monsters from your hand or field as Fusion Material. You can only use this effect of Gravekeeper's Spiritualist once per turn.

## ORICHALCOS_SHUNOROS (activated)
- file: `src_custom/activated_effects/orichalcos_shunoros.c`
- clone: `src_custom/activated_effects/elemental_hero_great_tornado.c` (ELEMENTAL_HERO_GREAT_TORNADO)
- text: This card cannot be Normal Summoned or Set. If a Normal Monster you control is destroyed by battle, you can Special Summ This card cannot be Normal Summoned or Set. If a Normal Monster you control is destroyed by battle, you can Special Summon this card from your hand. This card gains 1000 ATK for each monster your opponent controls. Face-up Level 4 Normal Monsters on the field cannot be destroyed by card effects.

## WEISS_LIGHTSWORN_ARCHFIEND (activated)
- file: `src_custom/activated_effects/weiss_lightsworn_archfiend.c`
- clone: `src_custom/activated_effects/chimeratech_megafleet_dragon.c` (CHIMERATECH_MEGAFLEET_DRAGON)
- text: Topdeck LS to SS; mill 2; GY SS. You can place 1 other Lightsworn card from your hand on top of the Deck; Special Summon this card from your hand, then send the top 2 cards of your Deck to the GY. If this card is sent from the Deck to the GY: You can target 1 Lightsworn monster in your GY, except Weiss, Lightsworn Archfiend; Special Summon it. You can only use each effect of Weiss, Lightsworn Archfiend once per turn.
