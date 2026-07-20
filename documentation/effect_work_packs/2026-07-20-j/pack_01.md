# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MAGICIANS_LEFT_HAND (spell)
- file: `src_custom/spell_effects/magicians_left_hand.c`
- clone: `src_custom/spell_effects/venom_swamp.c` (VENOM_SWAMP)
- text: Negate the effect of your opponent's first Trap Card or effect that resolves each turn while you control a Spellcaster m Negate the effect of your opponent's first Trap Card or effect that resolves each turn while you control a Spellcaster monster, and if you do, destroy that card.

## UNSTABLE_EVOLUTION (spell)
- file: `src_custom/spell_effects/unstable_evolution.c`
- clone: `src_custom/spell_effects/amazoness_fighting_spirit.c` (AMAZONESS_FIGHTING_SPIRIT)
- text: While your LP is lower than your opponent's, the equipped monster's original ATK becomes 2400. While your LP is higher,  While your LP is lower than your opponent's, the equipped monster's original ATK becomes 2400. While your LP is higher, the equipped monster's original ATK becomes 1000.

## DARK_CALLING (spell)
- file: `src_custom/spell_effects/dark_calling.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: FS with Dark Fusion materials banished from hand/GY. Treated as Dark Fusion. Fusion Summon 1 Fusion Monster from your Extra Deck, that must be Special Summoned with Dark Fusion, by banishing the Fusion Materials listed on it from your hand and/or GY. (This is treated as a Fusion Summon with Dark Fusion.)

## NEUTRON_BLAST (spell)
- file: `src_custom/spell_effects/neutron_blast.c`
- clone: `src_custom/spell_effects/h_heated_heart.c` (H_HEATED_HEART)
- text: BEUD attacks 2nd/3rd; opp cannot activate cards/effects when it attacks. Target 1 Fusion Summoned Blue-Eyes Ultimate Dragon you control; this turn, it can make a second and third attack during each Battle Phase, also when it attacks, your opponent's cards and effects cannot be activated until the end of the Damage Step.
