# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MORALE_BOOST (spell)
- file: `src_custom/spell_effects/morale_boost.c`
- text: Equip Spell equipped: gain 1000 LP. Equip Spell leaves field: take 1000 damage. Each time a player equips an Equip Spell Card, increase the Life Points of the controller of that Equip Spell Card by 1000 points. Each time an Equip Spell Card is removed from the field, the controller of that Equip Spell Card takes 1000 points of damage.

## TWLIGHT_TWIN_DRAGONS (spell)
- file: `src_custom/spell_effects/twlight_twin_dragons.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Recycle JD/PD; mill top 4. If you control Punishment Dragon: Target 1 Judgment Dragon in your GY; add it to your hand, then send the top 4 cards of your Deck to the GY. If this card is sent from the Deck to the GY by a Lightsworn monster's effect: You can target 1 Punishment Dragon in your GY; add it to your hand, then banish the top 4 cards of your Deck.

## BUBBLE_BLASTER (spell)
- file: `src_custom/spell_effects/bubble_blaster.c`
- clone: `src_custom/spell_effects/continuous_destruction_punch.c` (CONTINUOUS_DESTRUCTION_PUNCH)
- text: Equip to E-HERO Bubbleman. +800 ATK. If destroyed by battle, destroy this instead; battle damage 0. You can only equip this card to Elemental Hero Bubbleman. Increase the ATK of the equipped monster by 800 points. If the equipped monster would be destroyed as a result of battle, destroy this card instead, and make the Battle Damage to the controller of the equipped monster 0.

## AROMA_GARDENING (spell)
- file: `src_custom/spell_effects/aroma_gardening.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: On Aroma Summon: +1000 LP. If attacked while LP lower: SS Aroma from Deck. If you Normal or Special Summon an Aroma monster(s) (except during the Damage Step): You can gain 1000 LP. When an opponent's monster declares an attack, while your LP are lower than your opponent's: You can Special Summon 1 Aroma monster from your Deck. You can only use each effect of Aroma Gardening once per turn.
