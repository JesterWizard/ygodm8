# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## CLOCK_TOWER_PRISON (spell)
- file: `src_custom/spell_effects/clock_tower_prison.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Opp SP: place 1 Clock Counter (max 4). 4+: no battle dmg. If destroyed: remove 1 counter. Once per turn, during your opponent's Standby Phase: Place 1 Clock Counter on this card. While there are 4 or more Clock Counters on this card, you do not take any battle damage. If this card with 4 or more Clock Counters is destroyed and sent to the GY: Special Summon 1 Destiny HERO - Dreadmaster from your hand or Deck.

## CHAOS_FORM (spell)
- file: `src_custom/spell_effects/chaos_form.c`
- clone: `src_custom/spell_effects/twin_swords_of_flashing_light_tryce.c` (TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE)
- text: Ritual Summon Chaos/Black Luster Soldier. Tribute hand/field; banish Blue-Eyes/DM from GY. This card can be used to Ritual Summon any Chaos or Black Luster Soldier Ritual Monster. You must also Tribute monsters from your hand or field and/or banish Blue-Eyes White Dragon or Dark Magician from your GY, whose total Levels exactly equal the Level of the Chaos or Black Luster Soldier Ritual Monster you Ritual Summon.

## EN_SHUFFLE (spell)
- file: `src_custom/spell_effects/en_shuffle.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Swap Neos/HERO; GY shuffle+draw. Shuffle 1 Elemental HERO or Neo-Spacian monster you control into the Deck, and if you do, Special Summon 1 Elemental HERO or Neo-Spacian monster with a different name from your Deck. You can banish this card from your GY; shuffle from your GY into the Deck, either 1 Elemental HERO monster and 1 Neo-Spacian monster, OR 1 Elemental HERO Neos, then draw 1 card. You can only use each effect of EN Shuffle once per turn.

## DARK_CONTACT (spell)
- file: `src_custom/spell_effects/dark_contact.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: OPT each: Dark Fusion FS by shuffle materials from field/GY/banish; or search Castle/Dark Fusion. Activate 1 of these effects (but you can only use each effect of Dark Contact once per turn); Fusion Summon 1 Fusion Monster from your Extra Deck that must be Special Summoned with Dark Fusion, by shuffling its materials from your field, GY, and/or banishment into the Deck. (This is treated as a Fusion Summon with Dark Fusion.) Add 1 Supreme King's Castle or Dark Fusion from your Deck to your hand.
