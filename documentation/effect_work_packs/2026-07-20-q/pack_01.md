# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MORPHTRONIC_MAP (spell)
- file: `src_custom/spell_effects/morphtronic_map.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Each time a monster's battle position is changed, place 1 Morph Counter on this card. All Morphtronic monsters gain 30 Each time a monster's battle position is changed, place 1 Morph Counter on this card. All Morphtronic monsters gain 300 ATK for each Morph Counter on this card. When this card is destroyed and sent from the field to the Graveyard, you can Special Summon 1 Morphtronic monster from your Graveyard.

## SECRETS_OF_DARK_MAGIC (spell)
- file: `src_custom/spell_effects/secrets_of_dark_magic.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Fusion or Ritual Summon using DARK Spellcaster materials. Activate 1 of the following effects; Fusion Summon 1 Fusion Monster from your Extra Deck, using monsters from your hand or field, including Dark Magician or Dark Magician Girl. Ritual Summon 1 Ritual Monster from your hand, by Tributing monsters from your hand or field, including Dark Magician or Dark Magician Girl, whose total Levels equal or exceed the Level of the Ritual Monster.

## FUSION_DESTINY (spell)
- file: `src_custom/spell_effects/fusion_destiny.c`
- clone: `src_custom/spell_effects/fusion_deployment.c` (FUSION_DEPLOYMENT)
- text: Summon a Fusion Monster that mentions Destiny HERO from hand or Deck as material. Destroy it during the End  Fusion Summon 1 Fusion Monster from your Extra Deck that lists a Destiny HERO monster as material, using monsters from your hand or Deck as Fusion Material, but destroy it during the End Phase of the next turn, also for the rest of this turn after this card resolves, you cannot Special Summon monsters, except DARK HERO monsters. You can only activate 1 Fusion Destiny per turn.

## AROMA_BLEND (spell)
- file: `src_custom/spell_effects/aroma_blend.c`
- clone: `src_custom/spell_effects/aroma_garden.c` (AROMA_GARDEN)
- text: Discard 1; place Humid/Dried/Blessed Winds. GY: Fusion Summon Plant Fusion Monster. Discard 1 card; place 1 Humid Winds, Dried Winds, or Blessed Winds from your hand or Deck, face-up in your Spell & Trap Zone. You can banish this card from your GY; Fusion Summon 1 Plant Fusion Monster from your Extra Deck, by banishing its materials from your hand or field. If your LP are higher than your opponent's, you can also banish Plant monsters from your GY as material. You can only use each effect of Aro
