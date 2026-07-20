# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## INSTANT_CONTACT (spell)
- file: `src_custom/spell_effects/instant_contact.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Pay 1000; SS Extra HERO/Neo-Spacian. Pay 1000 LP; Special Summon 1 Level 7 or lower Elemental HERO or Neo-Spacian monster from your Extra Deck, ignoring its Summoning conditions. While Elemental HERO Neos is neither on your field nor in your GY, the Summoned monster cannot attack, its effects are negated, also it returns to the Extra Deck during the End Phase. You can only activate 1 Instant Contact per turn.

## THE_EYE_OF_TIMAEUS (spell)
- file: `src_custom/spell_effects/the_eye_of_timaeus.c`
- clone: `src_custom/spell_effects/the_a_forces.c` (THE_A_FORCES)
- text: (This card is also always treated as Legendary Dragon Timaeus.)
Target 1 Dark Magician monster you control; Fusion S (This card is also always treated as Legendary Dragon Timaeus.) Target 1 Dark Magician monster you control; Fusion Summon 1 Fusion Monster from your Extra Deck that lists that monster on the field as Fusion Material, using it as the Fusion Material. You can only activate 1 The Eye of Timaeus per turn.

## LIGHTSWORN_SANCTUARY (spell)
- file: `src_custom/spell_effects/lightsworn_sanctuary.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Recycle LS; Shine protects destroy. Once per turn: You can send 1 Lightsworn monster from your hand to the Graveyard, then target 1 other Lightsworn monster in your Graveyard; add it to your hand. Each time a card(s) is sent from your Deck to the Graveyard, place 1 Shine Counter on this card. If a Lightsworn card(s) you control would be destroyed by a card effect, you can remove 2 Shine Counters from your side of the field for each of those Lightsworn card(s) instead.

## ALLURING_MIRROR_SPLIT (spell)
- file: `src_custom/spell_effects/alluring_mirror_split.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Harpie Lady destroyed by battle: SS Harpie from Deck. If this destroyed: SS Harpie from GY. When a Harpie Lady or Harpie Lady Sisters you control is destroyed by battle: You can Special Summon 1 Harpie monster from your Deck with a different original name than the destroyed monster. If this card you control is destroyed by a Harpie card's effect or your opponent's card effect: Target 1 Harpie monster in your GY; Special Summon it. You can only use each effect of Alluring Mirror Split once per tu
