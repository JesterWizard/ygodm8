# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ETERNAL_SOUL (trap)
- file: `src_custom/trap_effects/eternal_soul.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: Protect Dark Magician. OPT: SS it from hand/GY, or search Dark Magic Attack / Thousand Knives. Every Dark Magician in your Monster Zone is unaffected by your opponent's card effects. If this face-up card leaves the field: Destroy all monsters you control. You can only use the following effect of Eternal Soul once per turn. You can activate 1 of these effects; Special Summon 1 Dark Magician from your hand or GY. Add 1 Dark Magic Attack or Thousand Knives from your Deck to your hand.

## CHAIN_MATERIAL (trap)
- file: `src_custom/trap_effects/chain_material.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: This turn Fusion materials may be banished from field/Deck/hand/GY. No attack; ED Fusions die EP. Any time you Fusion Summon a monster this turn, you can remove from play, from your side of the field, Deck, hand or Graveyard, Fusion Material Monsters that are listed on the Fusion Monster Card, and use them as Fusion Material Monsters. You cannot attack during the turn this card is activated. If you used this effect for a Fusion Summon, the Summoned Fusion Monster(s) is destroyed during the End P

## MORPHTRONIC_IMPACT_RETURN (trap)
- file: `src_custom/trap_effects/morphtronic_impact_return.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: Target up to 2 Spells/Traps your opponent controls; shuffle 1 Morphtronic monster from your hand into the Deck, and if Target up to 2 Spells/Traps your opponent controls; shuffle 1 Morphtronic monster from your hand into the Deck, and if you do, shuffle the targeted card(s) into the Deck. You can banish this card from your GY, then target 1 of your Morphtronic monsters that is banished or in your GY; Special Summon it in Defense Position. You can only use 1 Morphtronic Impact Return effect per t

## NECROVALLEY_TEMPLE (trap)
- file: `src_custom/trap_effects/necrovalley_temple.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: While a Gravekeeper's monster(s) and Necrovalley are both on the field, monsters your opponent controls lose 500 ATK While a Gravekeeper's monster(s) and Necrovalley are both on the field, monsters your opponent controls lose 500 ATK/DEF. Once per turn, during the Main Phase, if you control no card in your Field Zone: You can activate 1 Necrovalley directly from your hand or GY. If this card in your possession is destroyed by an opponent's effect and sent to your GY: You can Set 1 Necrovalley Sp
