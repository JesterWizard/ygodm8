# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## REESHADDOLL_WENDIKURUHU (activated)
- file: `src_custom/activated_effects/reeshaddoll_wendikuruhu.c`
- clone: `src_custom/activated_effects/shaddoll_hound.c` (SHADDOLL_HOUND)
- text: Quick: flip monsters. Sent to GY: add 1 Shaddoll from GY. 1 Shaddoll monster + 1 WIND monster Must first be Fusion Summoned. (Quick Effect): You can change any number of face-down monsters on the field to face-up Defense Position, then you can change other face-up monsters on the field to face-down Defense Position up to the number of Flip monsters flipped face-up. You can only use this effect of Reeshaddoll Wendikurhu once per turn. If this card is sent to the GY: You can target 1 Shaddoll card

## REPTILIANNE_LAMIA (activated)
- file: `src_custom/activated_effects/reptilianne_lamia.c`
- clone: `src_custom/activated_effects/reptilianne_vaskii.c` (REPTILIANNE_VASKII)
- text: Hand: set ATK 0, SS this. Synchro Material: set ATK to 0. If this card is in your hand and all monsters you control are face-up Reptile monsters (min. 1): You can target 1 face-up monster your opponent controls; change its ATK to 0, and if you do, Special Summon this card, then take damage equal to that monster's original ATK. If this card is sent to the GY as Synchro Material: You can target up to 2 face-up monsters on the field; change their ATK to 0. You can only use 1 Reptilianne Lamia effec

## ELEMENTAL_HERO_SHINING_NEOS_WINGMAN (activated)
- file: `src_custom/activated_effects/elemental_hero_shining_neos_wingman.c`
- clone: `src_custom/activated_effects/darkblaze_dragon.c` (DARKBLAZE_DRAGON)
- text: Destroy by Attr; burn on battle. Elemental HERO Neos + 1 Wingman Fusion Monster Must be Fusion Summoned. Gains 300 ATK for each monster in your GY, also cannot be destroyed by card effects. If this card is Special Summoned: You can destroy cards your opponent controls up to the number of different Attributes among the monsters on the field. You can only use this effect of Elemental HERO Shining Neos Wingman once per turn. If this card destroys a monster by battle: Inflict damage to your opponent

## ARCANA_FORCE_XII_THE_HANGMAN (activated)
- file: `src_custom/activated_effects/arcana_force_xii_the_hangman.c`
- clone: `src_custom/activated_effects/arcana_force_v_the_hierophant.c` (ARCANA_FORCE_V_THE_HIEROPHANT)
- text: Reveal; SS Arcana Force. Coin destroy+burn. When a card or effect is activated (Quick Effect): You can reveal this card in your hand; Special Summon 1 Arcana Force monster from your hand in Defense Position. You can only use this effect of Arcana Force XII - The Hangman once per turn. If this card is Summoned: Toss a coin. Heads: Destroy 1 monster you control, and if you do, take damage equal to its original ATK. Tails: Destroy 1 monster your opponent controls, and if you do, inflict damage to y
