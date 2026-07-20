# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## DARK_HORUS (activated)
- file: `src_custom/activated_effects/dark_horus.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: Once per turn, after resolving a Spell Card that was activated during your opponent's Main Phase: You can target 1 Level Once per turn, after resolving a Spell Card that was activated during your opponent's Main Phase: You can target 1 Level 4 DARK monster in your Graveyard; Special Summon that target. This card must be face-up on the field to activate and to resolve this effect.

## MAGICAL_MARIONETTE (activated)
- file: `src_custom/activated_effects/magical_marionette.c`
- clone: `src_custom/activated_effects/amazoness_sage.c` (AMAZONESS_SAGE)
- text: Each time a Spell Card is activated, place 1 Spell Counter on this card when that Spell Card resolves. This card gains 2 Each time a Spell Card is activated, place 1 Spell Counter on this card when that Spell Card resolves. This card gains 200 ATK for each Spell Counter on it. You can remove 2 Spell Counters from this card, then target 1 monster on the field; destroy that target.

## MAGICAL_SCIENTIST (activated)
- file: `src_custom/activated_effects/magical_scientist.c`
- clone: `src_custom/activated_effects/elemental_hero_great_tornado.c` (ELEMENTAL_HERO_GREAT_TORNADO)
- text: Pay 1000 Life Points to Special Summon 1 level 6 or lower Fusion Monster from your Extra Deck in face-up Attack or Defen Pay 1000 Life Points to Special Summon 1 level 6 or lower Fusion Monster from your Extra Deck in face-up Attack or Defense Position. That Fusion Monster cannot attack your opponent's Life Points directly, and is returned to your Extra Deck at the end of the turn.

## MORPHTRONIC_CLOCKEN (activated)
- file: `src_custom/activated_effects/morphtronic_clocken.c`
- clone: `src_custom/activated_effects/morphtronic_datatron.c` (MORPHTRONIC_DATATRON)
- text: - While in Attack Position: This card gains 500 ATK for each Morph Counter on it. - While in Defense Position: Once per  - While in Attack Position: This card gains 500 ATK for each Morph Counter on it. - While in Defense Position: Once per turn, you can place 1 Morph Counter on this card. You can Tribute this card to inflict 1000 damage to your opponent for each Morph Counter on it.
