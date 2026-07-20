# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GLADIATOR_BEAST_EQUESTE (activated)
- file: `src_custom/activated_effects/gladiator_beast_equeste.c`
- clone: `src_custom/activated_effects/gladiator_beast_bestiari.c` (GLADIATOR_BEAST_BESTIARI)
- text: Add GB from GY; tag out after. When this card is Special Summoned by the effect of a Gladiator Beast monster: Target 1 Gladiator Beast card in your Graveyard; add that target to your hand. At the end of the Battle Phase, if this card attacked or was attacked: You can shuffle it into the Deck; Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Equeste.

## SILENT_SWORDSMAN_LV5 (activated)
- file: `src_custom/activated_effects/silent_swordsman_lv5.c`
- clone: `src_custom/activated_effects/silent_swordsman_lv7.c` (SILENT_SWORDSMAN_LV7)
- text: Unaffected by your opponent's Spell effects. During your next Standby Phase after this card inflicts battle damage to yo Unaffected by your opponent's Spell effects. During your next Standby Phase after this card inflicts battle damage to your opponent by a direct attack: You can send this face-up card to the Graveyard; Special Summon 1 Silent Swordsman LV7 from your hand or Deck.

## MORPHTRONIC_SLINGEN (activated)
- file: `src_custom/activated_effects/morphtronic_slingen.c`
- clone: `src_custom/activated_effects/morphtronic_datatron.c` (MORPHTRONIC_DATATRON)
- text: - While in Attack Position: Once per turn, you can Tribute 1 Morphtronic monster, except Morphtronic Slingen, to des - While in Attack Position: Once per turn, you can Tribute 1 Morphtronic monster, except Morphtronic Slingen, to destroy 1 card on the field. - While in Defense Position: If this card would be destroyed, you can destroy another Morphtronic monster you control instead.

## ARCANA_FORCE_XIX_THE_SUN (activated)
- file: `src_custom/activated_effects/arcana_force_xix_the_sun.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: SS if coin card on field. Coin wipe monsters/ST. If a card that has a coin tossing effect is on the field: You can Special Summon this card from your hand. You can only use this effect of Arcana Force XIX - The Sun once per turn. If this card is Summoned: Toss a coin. Heads: Set 1 Spell from your Deck that has a coin tossing effect. Tails: Destroy all cards in the Spell & Trap Zones.
