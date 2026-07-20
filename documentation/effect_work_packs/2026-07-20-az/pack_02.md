# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## TIMEAUS_THE_UNITED_DRAGON (activated)
- file: `src_custom/activated_effects/timeaus_the_united_dragon.c`
- clone: `src_custom/activated_effects/ancient_gear_beast.c` (ANCIENT_GEAR_BEAST)
- text: Send mat to SS. Main: Fusion with Spellcaster. You can send 1 Spellcaster monster, or 1 Spell/Trap that mentions Dark Magician, from your hand or face-up field to the GY; Special Summon this card from your hand. During your Main Phase: You can Fusion Summon 1 Fusion Monster from your Extra Deck, using monsters from your hand or field as material, including a Spellcaster monster. You can only use each effect of Timaeus the United Dragon once per turn.

## ANCIENT_SACRED_WYVERN (activated)
- file: `src_custom/activated_effects/ancient_sacred_wyvern.c`
- clone: `src_custom/activated_effects/ancient_gear.c` (ANCIENT_GEAR)
- text: 1 LIGHT Tuner + 1 or more non-Tuner monsters
While your LP is higher than your opponent's, this card gains ATK equal to  1 LIGHT Tuner + 1 or more non-Tuner monsters While your LP is higher than your opponent's, this card gains ATK equal to the difference. While your LP is lower than your opponent's, this card loses ATK equal to the difference. When this card is destroyed by battle and sent to the Graveyard: You can pay 1000 LP; Special Summon this card.

## MAGICIANS_ROBE (activated)
- file: `src_custom/activated_effects/magicians_robe.c`
- clone: `src_custom/activated_effects/chimeratech_fortress_dragon.c` (CHIMERATECH_FORTRESS_DRAGON)
- text: Opp turn: discard S/T; SS DM from Deck. GY: SS self, banish later. During your opponent's turn (Quick Effect): You can discard 1 Spell/Trap; Special Summon 1 Dark Magician from your Deck. During your opponent's turn, if you activate a Spell/Trap Card or effect while this card is in your GY (except during the Damage Step): You can Special Summon this card, but banish it when it leaves the field. You can only use each effect of Magician's Robe once per turn.

## DESTINY_HERO_DENIER (activated)
- file: `src_custom/activated_effects/destiny_hero_denier.c`
- clone: `src_custom/activated_effects/chimeratech_megafleet_dragon.c` (CHIMERATECH_MEGAFLEET_DRAGON)
- text: Destiny HERO - Denier If this card is Normal or Special Summoned: You can take 1 of your Destiny HERO monsters from your Deck, GY, or that is banished, and place it on top of your Deck. You can only use this effect of Destiny HERO - Denier once per turn. If you have a Destiny HERO monster on your field or in your GY, other than Destiny HERO - Denier: You can Special Summon this card from your GY. You can only use this effect of Destiny HERO - Denier once per Duel.
