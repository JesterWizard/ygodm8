# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HERALD_OF_THE_ARC_LIGHT (activated)
- file: `src_custom/activated_effects/herald_of_the_arc_light.c`
- clone: `src_custom/activated_effects/herald_of_perfection.c` (HERALD_OF_PERFECTION)
- text: 1 Tuner + 1+ non-Tuner monsters
Any monster sent from the hand or Main Deck to the GY is banished instead. When a Spell 1 Tuner + 1+ non-Tuner monsters Any monster sent from the hand or Main Deck to the GY is banished instead. When a Spell/Trap Card, or monster effect, is activated (Quick Effect): You can Tribute this card; negate the activation, and if you do, destroy that card. If this card is sent to the GY: You can add 1 Ritual Monster or 1 Ritual Spell from your Deck to your hand.

## CHAOS_ANCIENT_GEAR_GIANT (activated)
- file: `src_custom/activated_effects/chaos_ancient_gear_giant.c`
- clone: `src_custom/activated_effects/ancient_gear_golem.c` (ANCIENT_GEAR_GOLEM)
- text: 4 Ancient Gear monsters
Must be Fusion Summoned and cannot be Special Summoned by other ways. Unaffected by Spell/Tra 4 Ancient Gear monsters Must be Fusion Summoned and cannot be Special Summoned by other ways. Unaffected by Spell/Trap effects. Your opponent's monsters cannot activate their effects during the Battle Phase. This card can attack all monsters your opponent controls, once each. If this card attacks a Defense Position monster, inflict piercing battle damage to your opponent.

## HELIOS_TRICE_MEGISTUS (activated)
- file: `src_custom/activated_effects/helios_trice_megistus.c`
- clone: `src_custom/activated_effects/crimson_blader.c` (CRIMSON_BLADER)
- text: You can Special Summon this card by Tributing 1 Helios Duo Megistus. This card's ATK and DEF are each equal to the num You can Special Summon this card by Tributing 1 Helios Duo Megistus. This card's ATK and DEF are each equal to the number of removed from play monsters x 300. After this card attacks, it can attack once more if your opponent controls a monster. If this card is destroyed by battle and sent to the Graveyard, Special Summon it during the End Phase and it gains 500 ATK and DEF.

## HARPIE_ORACLE (activated)
- file: `src_custom/activated_effects/harpie_oracle.c`
- clone: `src_custom/activated_effects/herald_of_ultimateness.c` (HERALD_OF_ULTIMATENESS)
- text: Name Lady. SS from hand with Lv5+ Harpie; GY search S/T. OPT. This card's name becomes Harpie Lady while on the field or in the GY. You can only use each of these effects of Harpie Oracle once per turn. If you control a Level 5 or higher Harpie monster: You can Special Summon this card from your hand. If this card is Normal or Special Summoned: You can add 1 Spell/Trap from your GY to your hand, that specifically lists the card Harpie Lady Sisters in its text, during the End Phase of this turn.
