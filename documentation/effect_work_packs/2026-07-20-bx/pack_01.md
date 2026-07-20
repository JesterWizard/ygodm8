# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## REPTILIANNE_GORGON (battle)
- file: `src_custom/battle_effects/reptilianne_gorgon.c`
- clone: `src_custom/battle_effects/harpie_lady_3.c` (HARPIE_LADY_3)
- text: After attack damage calc: that monster ATK becomes 0. If this card attacks a monster, after damage calculation: The ATK of that monster becomes 0, also it cannot change its battle position.

## DON_ZALOOG (battle)
- file: `src_custom/battle_effects/don_zaloog.c`
- clone: `src_custom/battle_effects/the_unstoppable_exodia_incarnate.c` (THE_UNSTOPPABLE_EXODIA_INCARNATE)
- text: Battle damage to opponent: discard 1 random card or send top 2 Deck cards to GY. When this card inflicts battle damage to your opponent: You can activate 1 of these effects; Discard 1 random card from their hand. Send the top 2 cards of their Deck to the GY.

## DESTINY_HERO_FEAR_MONGER (turn)
- file: `src_custom/turn_effects/destiny_hero_fear_monger.c`
- clone: `src_custom/turn_effects/darklord_marie.c` (DARKLORD_MARIE)
- text: During your Standby Phase, if this card is in your Graveyard because it was destroyed by battle and sent there since you During your Standby Phase, if this card is in your Graveyard because it was destroyed by battle and sent there since your last Standby Phase: Target 1 Destiny HERO monster in your Graveyard, except a Destiny HERO - Fear Monger; Special Summon that target.

## RED_DRAGON_ARCHFIEND (battle)
- file: `src_custom/battle_effects/red_dragon_archfiend.c`
- clone: `src_custom/battle_effects/harpie_lady_3.c` (HARPIE_LADY_3)
- text: Attacks Defense: destroy all opp Defense. EP: destroy other Attackers. 1 Tuner + 1 or more non-Tuner monsters After damage calculation, if this card attacks a Defense Position monster your opponent controls: Destroy all Defense Position monsters your opponent controls. During your End Phase: Destroy all other monsters you control that did not declare an attack this turn. This card must be face-up on the field to activate and to resolve this effect.
