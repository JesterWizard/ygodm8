# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SILENT_SWORDSMAN_LV3 (activated)
- file: `src_custom/activated_effects/silent_swordsman_lv3.c`
- clone: `src_custom/activated_effects/silent_swordsman_lv5.c` (SILENT_SWORDSMAN_LV5)
- text: Negate your opponent's Spell effects that target this card. During your Standby Phase: You can send this face-up card to Negate your opponent's Spell effects that target this card. During your Standby Phase: You can send this face-up card to the Graveyard; Special Summon 1 Silent Swordsman LV5 from your hand or Deck. You cannot activate this effect the turn this card is Summoned or flipped face-up.

## HOLACTIE_THE_CREATOR_OF_LIGHT (activated)
- file: `src_custom/activated_effects/holactie_the_creator_of_light.c`
- clone: `src_custom/activated_effects/test_tiger.c` (TEST_TIGER)
- text: Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by Tributing 3 monsters whose  Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by Tributing 3 monsters whose original names are Slifer the Sky Dragon, Obelisk the Tormentor, and The Winged Dragon of Ra. This card's Special Summon cannot be negated. The player that Special Summons this card wins the Duel.

## NEO_SPACIAN_MARINE_DOLPHIN (activated)
- file: `src_custom/activated_effects/neo_spacian_marine_dolphin.c`
- clone: `src_custom/activated_effects/neo_spacian_aqua_dolphin.c` (NEO_SPACIAN_AQUA_DOLPHIN)
- text: NEX only; Aqua Dolphin hand peek. This card's name is also treated as Neo-Spacian Aqua Dolphin. This card cannot be Special Summoned except with NEX. Once per turn, you can discard 1 card to look at your opponent's hand and select 1 Monster Card in it. If you control a monster with ATK greater than or equal to the selected monster's, destroy the selected monster and inflict 500 damage to your opponent.

## HERALD_OF_ULIMATENESS (activated)
- file: `src_custom/activated_effects/herald_of_ulimateness.c`
- clone: `src_custom/activated_effects/herald_of_perfection.c` (HERALD_OF_PERFECTION)
- text: You can Ritual Summon this card with Oracle of the Herald. Must be Ritual Summoned, and cannot be Special Summoned by other ways. During either player's turn, when your opponent would Special Summon a monster(s), OR activates a Spell Card, Trap Card, or monster effect: You can send 1 Fairy-Type monster from your hand to the Graveyard; negate the Special Summon or activation, and if you do, destroy that card.
