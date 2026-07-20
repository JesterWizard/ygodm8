# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ARMED_DRAGON_LV10 (activated)
- file: `src_custom/activated_effects/armed_dragon_lv10.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by Tributing 1 Armed Dragon LV7. You can send Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by Tributing 1 Armed Dragon LV7. You can send 1 card from your hand to the GY; destroy all face-up monsters your opponent controls.

## WHITE_HORNED_DRAGON (activated)
- file: `src_custom/activated_effects/white_horned_dragon.c`
- clone: `src_custom/activated_effects/chimeratech_fortress_dragon.c` (CHIMERATECH_FORTRESS_DRAGON)
- text: When this card is Normal or Special Summoned: Target up to 5 Spell Cards in your opponent's Graveyard; banish those targ When this card is Normal or Special Summoned: Target up to 5 Spell Cards in your opponent's Graveyard; banish those target(s), and if you do, this card gains 300 ATK for each card banished by this effect.

## BRIONAC_DRAGON_OF_THE_ICE_BARRIER (activated)
- file: `src_custom/activated_effects/brionac_dragon_of_the_ice_barrier.c`
- clone: `src_custom/activated_effects/mask_of_darkness.c` (MASK_OF_DARKNESS)
- text: Discard any number; bounce that many opponent cards to hand. Once per turn. 1 Tuner + 1+ non-Tuner monsters You can discard any number of cards to the GY, then target the same number of cards your opponent controls; return those cards to the hand. You can only use this effect of Brionac, Dragon of the Ice Barrier once per turn.

## LUMINA_TWILIGHTSWORN_SHAMAN (activated)
- file: `src_custom/activated_effects/lumina_twilightsworn_shaman.c`
- clone: `src_custom/activated_effects/lumina_lightsworn_summoner.c` (LUMINA_LIGHTSWORN_SUMMONER)
- text: SS banished LS; mill on LS effect. Once per turn: You can banish 1 Lightsworn monster from your hand or GY, then target 1 of your banished Lightsworn monsters, except Lumina, Twilightsworn Shaman; Special Summon it. Once per turn, if your other Lightsworn monster's effect is activated: Send the top 3 cards of your Deck to the GY.
