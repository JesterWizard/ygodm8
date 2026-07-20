# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## YAMORIMORI (activated)
- file: `src_custom/activated_effects/yamorimori.c`
- clone: `src_custom/activated_effects/cyber_phoenix.c` (CYBER_PHOENIX)
- text: Banish from GY: set both, or destroy + ATK 0. You can banish this card from your GY, then target 1 Reptile monster you control and 1 face-up monster your opponent controls, to activate 1 of these effects; Change those monsters to face-down Defense Position. Destroy that monster you control, and if you do, change the ATK of the other monster to 0 until the end of this turn. You can only use this effect of Yamorimori once per turn.

## GLADIATOR_BEAST_AUGUSTUS (activated)
- file: `src_custom/activated_effects/gladiator_beast_augustus.c`
- clone: `src_custom/activated_effects/gladiator_beast_bestiari.c` (GLADIATOR_BEAST_BESTIARI)
- text: SS GB from hand; tag out after. When this card is Special Summoned by the effect of a Gladiator Beast monster: You can Special Summon 1 Gladiator Beast monster from your hand in Defense Position. Shuffle it into the Deck during the End Phase. At the end of the Battle Phase, if this card attacked or was attacked: You can shuffle it into the Deck; Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Augustus.

## ASH_BLOSSOM_AND_JOYOUS_SPRING (activated)
- file: `src_custom/activated_effects/ash_blossom_and_joyous_spring.c`
- clone: `src_custom/activated_effects/chimeratech_fortress_dragon.c` (CHIMERATECH_FORTRESS_DRAGON)
- text: When a card or effect is activated that includes any of these effects (Quick Effect): You can discard this card; negate  When a card or effect is activated that includes any of these effects (Quick Effect): You can discard this card; negate that effect. - Add a card from the Deck to the hand. - Special Summon from the Deck. - Send a card from the Deck to the GY. You can only use this effect of Ash Blossom & Joyous Spring once per turn.

## POSEIDRA_THE_ATLANTEAN_DRAGON (activated)
- file: `src_custom/activated_effects/poseidra_the_atlantean_dragon.c`
- clone: `src_custom/activated_effects/alector_sovereign_of_birds.c` (ALECTOR_SOVEREIGN_OF_BIRDS)
- text: You can Tribute 3 Level 3 or lower WATER monsters; Special Summon this card from your hand or Graveyard. When you do: Re You can Tribute 3 Level 3 or lower WATER monsters; Special Summon this card from your hand or Graveyard. When you do: Return all Spell and Trap Cards on the field to the hand, and if you do, if 3 or more cards are returned to the hand by this effect, all monsters your opponent currently controls lose 300 ATK for each.
