# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GLADIATOR_BEAST_ATTORIX (activated)
- file: `src_custom/activated_effects/gladiator_beast_attorix.c`
- clone: `src_custom/activated_effects/chimeratech_megafleet_dragon.c` (CHIMERATECH_MEGAFLEET_DRAGON)
- text: Copy GY GB name/Level; tag out. If this card is Special Summoned by the effect of a Gladiator Beast monster: You can send 1 Gladiator Beast monster from your Deck or Extra Deck to the GY, except Gladiator Beast Attorix; until the End Phase, this card's Level and name become the same as that monster sent to the GY. At the end of the Battle Phase, if this card battled: You can shuffle it into the Deck; Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Attorix.

## DESTINY_HERO_DREAMER (activated)
- file: `src_custom/activated_effects/destiny_hero_dreamer.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: During damage calculation, if your Destiny HERO monster battles and this card is in your GY: You can Special Summon th During damage calculation, if your Destiny HERO monster battles and this card is in your GY: You can Special Summon this card, and if you do, your monster cannot be destroyed by that battle, also you take no battle damage from that battle. If Summoned this way, banish this card when it leaves the field. You can only use this effect of Destiny HERO - Dreamer once per turn.

## EVIL_HERO_NEOS_LORD (activated)
- file: `src_custom/activated_effects/evil_hero_neos_lord.c`
- clone: `src_custom/activated_effects/azure_eyes_silver_dragon.c` (AZURE_EYES_SILVER_DRAGON)
- text: Indestructible. OPT: take control of 1 face-up opp monster. Elemental HERO Neos (or 1 Fusion Monster that mentions it) + 1 Effect Monster on the field Must be Special Summoned with Dark Fusion. Cannot be destroyed by battle or card effects. If this card is Special Summoned, or a monster(s) is sent to your opponent's GY while this card is on the field: You can target 1 face-up monster your opponent controls; take control of it. You can only use this effect of Evil HERO Neos Lord once per turn.

## ULTIMATE_ANCIENT_GEAR_GOLEM (activated)
- file: `src_custom/activated_effects/ultimate_ancient_gear_golem.c`
- clone: `src_custom/activated_effects/ancient_gear_beast.c` (ANCIENT_GEAR_BEAST)
- text: Ancient Gear Golem + 2 Ancient Gear monsters
Must be Fusion Summoned. If this card attacks a Defense Position monst Ancient Gear Golem + 2 Ancient Gear monsters Must be Fusion Summoned. If this card attacks a Defense Position monster, inflict piercing battle damage. If this card attacks, your opponent cannot activate Spell/Trap Cards until the end of the Damage Step. If this card is destroyed: You can target 1 Ancient Gear Golem in your GY; Special Summon it, ignoring its Summoning conditions.
