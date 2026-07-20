# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ARMED_DRAGON_LV7 (activated)
- file: `src_custom/activated_effects/armed_dragon_lv7.c`
- clone: `src_custom/activated_effects/armed_dragon_lv10.c` (ARMED_DRAGON_LV10)
- text: Cannot be Normal Summoned/Set. Must be Special Summoned by Armed Dragon LV5. You can send 1 monster from your hand to  Cannot be Normal Summoned/Set. Must be Special Summoned by Armed Dragon LV5. You can send 1 monster from your hand to the GY; destroy all monsters your opponent controls with ATK less than or equal to that sent monster's ATK.

## TREEBORN_FROG (activated)
- file: `src_custom/activated_effects/treeborn_frog.c`
- clone: `src_custom/activated_effects/chimeratech_fortress_dragon.c` (CHIMERATECH_FORTRESS_DRAGON)
- text: Once per turn, during your Standby Phase, if this card is in your Graveyard and you do not control "Treeborn Frog": You  Once per turn, during your Standby Phase, if this card is in your Graveyard and you do not control Treeborn Frog: You can Special Summon this card. You must control no Spell/Trap Cards to activate and to resolve this effect.

## GLADIATOR_BEAST_SAGITTARII (activated)
- file: `src_custom/activated_effects/gladiator_beast_sagittarii.c`
- clone: `src_custom/activated_effects/gladiator_beast_hoplomus.c` (GLADIATOR_BEAST_HOPLOMUS)
- text: Discard; destroy S/T; tag out. If this card is Special Summoned by the effect of a Gladiator Beast monster: You can discard 1 Gladiator Beast card; draw 2 cards. At the end of the Battle Phase, if this card battled: You can shuffle this card into the Deck; Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Sagittarii.

## GRAVEKEEPERS_VISIONARY (activated)
- file: `src_custom/activated_effects/gravekeepers_visionary.c`
- clone: `src_custom/activated_effects/gravekeepers_descendant.c` (GRAVEKEEPERS_DESCENDANT)
- text: You can Tribute Summon this card by Tributing 1 Gravekeeper's monster. This card gains 200 ATK for each Gravekeeper's You can Tribute Summon this card by Tributing 1 Gravekeeper's monster. This card gains 200 ATK for each Gravekeeper's monster in your Graveyard. If this face-up card would be destroyed, you can discard 1 Gravekeeper's monster instead.
