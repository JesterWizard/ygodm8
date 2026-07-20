# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SUMMONERS_ART (spell)
- file: `src_custom/spell_effects/summoners_art.c`
- clone: `src_custom/spell_effects/polymerization.c` (POLYMERIZATION)
- optional template: `--fill search SUMMONERS_ART`
- text: Add 1 Level 5 or higher Normal Monster from your Deck to your hand. Add 1 Level 5 or higher Normal Monster from your Deck to your hand.

## ACE_OF_SWORD (spell)
- file: `src_custom/spell_effects/ace_of_sword.c`
- clone: `src_custom/spell_effects/h_heated_heart.c` (H_HEATED_HEART)
- optional template: `--fill burn ACE_OF_SWORD`
- text: Coin: burn or take selected ATK. Select 1 face-up monster; toss a coin. Heads: inflict damage equal to its ATK. Tails: you take damage equal to its ATK.

## TWISTER (spell)
- file: `src_custom/spell_effects/twister.c`
- clone: `src_custom/spell_effects/block_attack.c` (BLOCK_ATTACK)
- optional template: `--fill destroy_zone TWISTER`
- text: Pay 500 LP, then target 1 face-up Spell/Trap on the field; destroy that target. Pay 500 LP, then target 1 face-up Spell/Trap on the field; destroy that target.

## DOUBLE_CYCLONE (spell)
- file: `src_custom/spell_effects/double_cyclone.c`
- clone: `src_custom/spell_effects/double_summon.c` (DOUBLE_SUMMON)
- optional template: `--fill destroy_zone DOUBLE_CYCLONE`
- text: Target 1 Spell/Trap you control and 1 Spell/Trap your opponent controls; destroy them. Target 1 Spell/Trap you control and 1 Spell/Trap your opponent controls; destroy them.
