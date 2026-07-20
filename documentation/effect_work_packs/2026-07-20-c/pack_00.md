# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## GEARTOWN (spell)
- file: `src_custom/spell_effects/geartown.c`
- clone: `src_custom/spell_effects/guardian_treasure.c` (GUARDIAN_TREASURE)
- optional template: `--fill tribute_summon GEARTOWN`
- text: Both players can Normal Summon Ancient Gear monsters for 1 less Tribute. When this card is destroyed and sent to the G Both players can Normal Summon Ancient Gear monsters for 1 less Tribute. When this card is destroyed and sent to the Graveyard: You can Special Summon 1 Ancient Gear monster from your hand, Deck, or Graveyard.

## SCAPEGOAT (spell)
- file: `src_custom/spell_effects/scapegoat.c`
- clone: `src_custom/spell_effects/tribute_doll.c` (TRIBUTE_DOLL)
- optional template: `--fill tribute_summon SCAPEGOAT`
- text: Special Summon 4 Sheep Tokens (Beast/EARTH/Level 1/ATK 0/DEF 0) in Defense Position. They cannot be Tributed for a Tri Special Summon 4 Sheep Tokens (Beast/EARTH/Level 1/ATK 0/DEF 0) in Defense Position. They cannot be Tributed for a Tribute Summon. You cannot Summon other monsters the turn you activate this card (but you can Normal Set).

## ARCANA_READING (spell)
- file: `src_custom/spell_effects/arcana_reading.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- optional template: `--fill search ARCANA_READING`
- text: Coin: add Arcana Force or SS from GY. Toss a coin and apply this effect. If Light Barrier is in your Field Zone, you can choose the effect instead. Heads: Add 1 card from your Deck to your hand that has a coin tossing effect, except Arcana Reading. Tails: Your opponent adds 1 card from their Deck to their hand. You can banish this card from your GY; immediately after this effect resolves, Normal Summon 1 Arcana Force monster. You can only use each effect of Arcana Reading once per turn.

## TOON_WORLD (spell)
- file: `src_custom/spell_effects/toon_world.c`
- text: Activate this card by paying 1000 LP. Activate this card by paying 1000 LP.
