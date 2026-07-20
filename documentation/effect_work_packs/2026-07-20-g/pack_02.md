# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SURFACE (spell)
- file: `src_custom/spell_effects/surface.c`
- clone: `src_custom/spell_effects/h_heated_heart.c` (H_HEATED_HEART)
- text: Target 1 Level 3 or lower Fish, Sea Serpent, or Aqua monster in your GY; Special Summon it in face-up Defense Position. Target 1 Level 3 or lower Fish, Sea Serpent, or Aqua monster in your GY; Special Summon it in face-up Defense Position.

## AMAZONESS_FIGHTING_SPIRIT (spell)
- file: `src_custom/spell_effects/amazoness_fighting_spirit.c`
- clone: `src_custom/spell_effects/kaiser_colosseum.c` (KAISER_COLOSSEUM)
- text: If an "Amazoness" monster attacks a monster with higher ATK, the attacking monster gains 1000 ATK during damage calculat If an Amazoness monster attacks a monster with higher ATK, the attacking monster gains 1000 ATK during damage calculation only.

## RETURN_OF_THE_DRAGON_LORDS (spell)
- file: `src_custom/spell_effects/return_of_the_dragon_lords.c`
- clone: `src_custom/spell_effects/ancient_rules.c` (ANCIENT_RULES)
- text: SS Lv7/8 Dragon from GY. GY: banish instead of destroy Dragon. Target 1 Level 7 or 8 Dragon monster in your GY; Special Summon it. If a Dragon monster(s) you control would be destroyed by battle or card effect, you can banish this card from your GY instead.

## DARK_FUSION (spell)
- file: `src_custom/spell_effects/dark_fusion.c`
- clone: `src_custom/spell_effects/polymerization.c` (POLYMERIZATION)
- text: Fusion Summon 1 Fiend Fusion using hand/field materials. Opponent cannot target it this turn. Fusion Summon 1 Fiend Fusion Monster from your Extra Deck, using monsters from your hand or field as Fusion Material. Your opponent cannot target it with card effects this turn.
