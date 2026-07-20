# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HARPIES_HUNTING_GROUND (spell)
- file: `src_custom/spell_effects/harpies_hunting_ground.c`
- clone: `src_custom/spell_effects/ancient_rules.c` (ANCIENT_RULES)
- text: Winged Beast +200. On Harpie Lady/Sisters summon: destroy 1 S/T. All Winged Beast monsters gain 200 ATK/DEF. If any Harpie Lady or Harpie Lady Sisters is Normal or Special Summoned: The player who conducted the Summon targets 1 Spell/Trap on the field; that player destroys that target.

## DRAGON_SHRINE (spell)
- file: `src_custom/spell_effects/dragon_shrine.c`
- clone: `src_custom/spell_effects/dragons_mirror.c` (DRAGONS_MIRROR)
- text: Send 1 Dragon from Deck to GY; if Normal, may send 1 more. Once per turn. Send 1 Dragon monster from your Deck to the GY, then, if that monster in your GY is a Dragon Normal Monster, you can send 1 more Dragon monster from your Deck to the GY. You can only activate 1 Dragon Shrine per turn.

## MIRACLE_CONTACT (spell)
- file: `src_custom/spell_effects/miracle_contact.c`
- clone: `src_custom/spell_effects/miracle_fusion.c` (MIRACLE_FUSION)
- text: Contact Fusion Neos HERO from GY. Shuffle into the Deck, from your hand, field, or GY, the Fusion Materials that are listed on an Elemental HERO Fusion Monster that lists Elemental HERO Neos as Fusion Material, then Special Summon that Fusion Monster from your Extra Deck, ignoring its Summoning conditions.

## PSEUDO_SPACE (spell)
- file: `src_custom/spell_effects/pseudo_space.c`
- clone: `src_custom/spell_effects/dragons_mirror.c` (DRAGONS_MIRROR)
- text: Once per turn: You can banish 1 Field Spell Card from your Graveyard; until the End Phase, this card's name becomes that Once per turn: You can banish 1 Field Spell Card from your Graveyard; until the End Phase, this card's name becomes that card's original name, and replace this effect with that card's original effects.
