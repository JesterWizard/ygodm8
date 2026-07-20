# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GRINDER_GOLEM (permanent)
- file: `src_custom/permanent_effects/grinder_golem.c`
- clone: `src_custom/permanent_effects/dark_magician_of_chaos.c` (DARK_MAGICIAN_OF_CHAOS)
- text: SS to opp field; make 2 Tokens on yours. No NS/Set that turn. Cannot be Normal Summoned or Set. Must first be Special Summoned (from your hand) to your opponent's side of the field by Special Summoning 2 Grinder Tokens (Fiend-Type/DARK/Level 1/ATK 0/DEF 0) in face-up Attack Position on your side of the field. If you Special Summon this monster, you cannot Normal Summon or Set a monster during the same turn.

## EL_SHADDOLL_CONSTRUCT (permanent)
- file: `src_custom/permanent_effects/el_shaddoll_construct.c`
- clone: `src_custom/permanent_effects/el_shaddoll_winda.c` (EL_SHADDOLL_WINDA)
- text: On SS: mill Shaddoll. Battle vs SS: destroy. GY: add S/T. 1 Shaddoll monster + 1 LIGHT monster Must first be Fusion Summoned. If this card is Special Summoned: You can send 1 Shaddoll card from your Deck to the GY. At the start of the Damage Step, if this card battles a Special Summoned monster: Destroy that monster. If this card is sent to the GY: You can target 1 Shaddoll Spell/Trap in your GY; add it to your hand.

## DESTINY_HERO_DRAWHAND (permanent)
- file: `src_custom/permanent_effects/destiny_hero_drawhand.c`
- clone: `src_custom/permanent_effects/elemental_hero_escuridao.c` (ELEMENTAL_HERO_ESCURIDAO)
- text: If this card is Special Summoned by the effect of a HERO monster: You can make each player draw 1 card. During the nex If this card is Special Summoned by the effect of a HERO monster: You can make each player draw 1 card. During the next Standby Phase after this card was sent to the GY: You can Special Summon this card from your GY, but banish it when it leaves the field. You can only use each effect of Destiny HERO - Drawhand once per turn.

## THUNDER_DRAGON_COLOSSUS (permanent)
- file: `src_custom/permanent_effects/thunder_dragon_colossus.c`
- clone: `src_custom/permanent_effects/horus_the_black_flame_dragon_lv4.c` (HORUS_THE_BLACK_FLAME_DRAGON_LV4)
- text: Thunder Dragon + 1 Thunder monster Must be either Fusion Summoned, or Special Summoned during the turn a Thunder monster's effect was activated in the hand, by Tributing 1 Thunder Effect non-Fusion Monster (in which case you do not use Polymerization). Cards cannot be added from the Main Deck to your opponent's hand except by drawing them. If this card would be destroyed by battle or card effect, you can banish 1 Thunder monster from your GY instead.
