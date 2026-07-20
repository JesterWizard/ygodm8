# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## AROMASERAPHY_JASMINE (activated)
- file: `src_custom/activated_effects/aromaseraphy_jasmine.c`
- clone: `src_custom/activated_effects/aromaseraphy_rosemary.c` (AROMASERAPHY_ROSEMARY)
- text: If LP higher: battle immune. Tribute Link target: SS Plant. If gain LP: add Plant. 2 Plant monsters If your LP are higher than your opponent's, this card and any Plant monsters it points to cannot be destroyed by battle. You can Tribute 1 monster this card points to; Special Summon 1 Plant monster from your Deck in Defense Position. You can only use this effect of Aromaseraphy Jasmine once per turn. Once per turn, if you gain LP: Add 1 Plant monster from your Deck to your hand.

## ELEMENTAL_HERO_STORM_NEOS (activated)
- file: `src_custom/activated_effects/elemental_hero_storm_neos.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: Pop all S/T; End shuffle field. Elemental HERO Neos + Neo-Spacian Air Hummingbird + Neo-Spacian Aqua Dolphin Must first be Special Summoned (from your Extra Deck) by shuffling the above cards you control into the Deck. (You do not use Polymerization.) Once per turn: You can destroy all Spell and Trap Cards on the field. During the End Phase: Shuffle this card into the Extra Deck. When this card is shuffled into the Extra Deck this way: Shuffle all cards on the field into the Deck.

## DESTINY_HERO_DYSTOPIA (activated)
- file: `src_custom/activated_effects/destiny_hero_dystopia.c`
- clone: `src_custom/activated_effects/destiny_hero_dunker.c` (DESTINY_HERO_DUNKER)
- text: 2 Destiny HERO monsters If this card is Special Summoned: You can target 1 Level 4 or lower Destiny HERO monster in your GY; inflict damage to your opponent equal to that target's ATK. If this card's current ATK is different from its original ATK (except during the Damage Step) (Quick Effect): You can target 1 card on the field; destroy it, and if you do, this card's ATK becomes equal to this card's original ATK. You can only use each effect of Destiny HERO - Dystopia once per turn.

## PREDAPLANT_VERTE_ANACONDA (activated)
- file: `src_custom/activated_effects/predaplant_verte_anaconda.c`
- clone: `src_custom/activated_effects/azure_eyes_silver_dragon.c` (AZURE_EYES_SILVER_DRAGON)
- text: Make monster DARK. Pay 2000; copy Fusion/Poly from Deck. OPT. 2 Effect Monsters You can target 1 face-up monster on the field; it becomes DARK until the end of this turn. You can pay 2000 LP and send 1 Fusion or Polymerization Normal or Quick-Play Spell from your Deck to the GY; this effect becomes that Spell's effect when that card is activated, also, you cannot Special Summon monsters for the rest of this turn. You can only use each effect of Predaplant Verte Anaconda once per turn.
