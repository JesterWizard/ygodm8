# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## AROMAGE_JASMINE (activated)
- file: `src_custom/activated_effects/aromage_jasmine.c`
- clone: `src_custom/activated_effects/aromage_cananga.c` (AROMAGE_CANANGA)
- text: If LP higher: extra Plant Normal Summon. Once/turn if gain LP: draw 1. During your Main Phase, while your LP are higher than your opponent's, you can Normal Summon 1 Plant monster in addition to your Normal Summon/Set, except Aromage Jasmine. (You can only gain this effect once per turn.) Once per turn, if you gain LP: Draw 1 card.

## ANCIENT_GEAR_GOLEM (activated)
- file: `src_custom/activated_effects/ancient_gear_golem.c`
- clone: `src_custom/activated_effects/ancient_gear_soldier.c` (ANCIENT_GEAR_SOLDIER)
- text: Cannot be Special Summoned. If this card attacks, your opponent cannot activate any Spell/Trap Cards until the end of th Cannot be Special Summoned. If this card attacks, your opponent cannot activate any Spell/Trap Cards until the end of the Damage Step. If this card attacks a Defense Position monster, inflict piercing battle damage.

## GLADIATOR_BEAST_HOPLOMUS (activated)
- file: `src_custom/activated_effects/gladiator_beast_hoplomus.c`
- clone: `src_custom/activated_effects/elemental_hero_wildedge.c` (ELEMENTAL_HERO_WILDEDGE)
- text: DEF 2400 on tag-SS; tag out after. If this card was Special Summoned by the effect of a Gladiator Beast monster, its original DEF becomes 2400. At the end of the Battle Phase, if this card attacked or was attacked: You can shuffle it into the Deck; Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Hoplomus.

## LYLA_TWILIGHTSWORN_ENCHANTRESS (activated)
- file: `src_custom/activated_effects/lyla_twilightsworn_enchantress.c`
- clone: `src_custom/activated_effects/cyber_phoenix.c` (CYBER_PHOENIX)
- text: Banish LS; destroy S/T; mill 3. Once per turn, when a Spell/Trap Card or effect is activated (Quick Effect): You can banish 1 Lightsworn monster from your hand or GY, then target 1 face-up Spell/Trap on the field; destroy it. Once per turn, if your other Lightsworn monster's effect is activated: Send the top 3 cards of your Deck to the GY.
