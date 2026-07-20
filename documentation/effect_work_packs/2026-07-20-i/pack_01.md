# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ATTACK_PHEROMONES (spell)
- file: `src_custom/spell_effects/attack_pheromones.c`
- clone: `src_custom/spell_effects/burden_of_the_mighty.c` (BURDEN_OF_THE_MIGHTY)
- text: If a monster you control attacks a Defense Position monster, change that monster to face-up Attack If a monster you control attacks a Defense Position monster, change that monster to face-up Attack Position at the end of the Damage Step if your attacking monster is Reptile-Type.

## ANCIENT_GEAR_FIST (spell)
- file: `src_custom/spell_effects/ancient_gear_fist.c`
- clone: `src_custom/spell_effects/ancient_gear_workshop.c` (ANCIENT_GEAR_WORKSHOP)
- text: Equip only to an Ancient Gear monster. At the end of the Damage Step, if the equipped monster battled a monster and is Equip only to an Ancient Gear monster. At the end of the Damage Step, if the equipped monster battled a monster and is still on the field: Destroy the monster it battled.

## GLADIATOR_BEAST_BATTLE_HALBERD (spell)
- file: `src_custom/spell_effects/gladiator_beast_battle_halberd.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: On attack pop S/T; recycle on tag. Equip only to a Gladiator Beast monster. When it attacks, destroy 1 Spell or Trap Card at the end of the Damage Step. When the equipped monster is returned from your side of the field to the Deck and this card is sent to the Graveyard, return this card to your hand.

## MAGICIANS_RIGHT_HAND (spell)
- file: `src_custom/spell_effects/magicians_right_hand.c`
- clone: `src_custom/spell_effects/venom_swamp.c` (VENOM_SWAMP)
- text: Negate the effect of your opponent's first Spell Card or effect that resolves each turn while you control a Spellcaster Negate the effect of your opponent's first Spell Card or effect that resolves each turn while you control a Spellcaster monster, and if you do, or if it did not have an effect, destroy that card.
