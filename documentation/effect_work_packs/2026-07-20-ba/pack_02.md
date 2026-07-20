# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## EVIL_HERO_TOXIC_BUBBLE (activated)
- file: `src_custom/activated_effects/evil_hero_toxic_bubble.c`
- clone: `src_custom/activated_effects/turbo_synchron.c` (TURBO_SYNCHRON)
- text: SS from hand (HERO lock). If Dark Fusion Fusion up: draw 2. You can Special Summon this card (from your hand), but you cannot Special Summon for the rest of this turn, except HERO monsters. You can only Special Summon Evil HERO Toxic Bubble once per turn this way. If this card is Special Summoned, and you control a Fusion Monster that must be Special Summoned with Dark Fusion: You can draw 2 cards. You can only use this effect of Evil HERO Toxic Bubble once per turn.

## GUARDIAN_EATOS (activated)
- file: `src_custom/activated_effects/guardian_eatos.c`
- clone: `src_custom/activated_effects/herald_of_ulimateness.c` (HERALD_OF_ULIMATENESS)
- text: If you have no monsters in your Graveyard, you can Special Summon this card (from your hand). You can send  If you have no monsters in your Graveyard, you can Special Summon this card (from your hand). You can send 1 of your Equip Spell Cards equipped to this card to the Graveyard, then target up to 3 monsters in your opponent's Graveyard; banish those targets, and if you do, this card gains 500 ATK for each monster banished by this effect, until the end of this turn.

## MILLENNIUM_EYES_RESTRICT (activated)
- file: `src_custom/activated_effects/millennium_eyes_restrict.c`
- clone: `src_custom/activated_effects/azure_eyes_silver_dragon.c` (AZURE_EYES_SILVER_DRAGON)
- text: Opp monster effect: equip their Effect Monster; gain ATK/DEF. Relinquished + 1 Effect Monster Once per turn, when your opponent activates a monster effect (Quick Effect): You can target 1 Effect Monster your opponent controls or in their GY; equip that target to this card you control. This card gains ATK/DEF equal to that equipped monster's. Monsters with that equipped monster's name cannot attack, also their effects on the field and their activated effects are negated.

## DARKNESS_NEOSPHERE (activated)
- file: `src_custom/activated_effects/darkness_neosphere.c`
- clone: `src_custom/activated_effects/herald_of_ulimateness.c` (HERALD_OF_ULIMATENESS)
- text: This card cannot be Normal Summoned or Set. This card cannot be Special Summoned except by sending 1 Fiend-Type monster  This card cannot be Normal Summoned or Set. This card cannot be Special Summoned except by sending 1 Fiend-Type monster you control and 1 Fiend-Type monster from your hand to the Graveyard when your opponent's monster declares an attack. This card cannot be destroyed by battle. Once per turn, you can return all face-up Trap Cards you control to the hand.
