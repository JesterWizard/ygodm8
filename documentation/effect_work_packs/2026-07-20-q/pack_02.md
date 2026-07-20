# Effect work pack 02 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## ANCIENT_GEAR_FACTORY (spell)
- file: `src_custom/spell_effects/ancient_gear_factory.c`
- clone: `src_custom/spell_effects/twin_swords_of_flashing_light_tryce.c` (TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE)
- text: Reveal 1 Level 5 or higher Ancient Gear monster from your hand, then banish a number of Ancient Gear monsters from y Reveal 1 Level 5 or higher Ancient Gear monster from your hand, then banish a number of Ancient Gear monsters from your Graveyard, whose combined Levels are double the revealed monster's, and if you do, if you Normal Summon the revealed monster this turn, you must Normal Smmon it without Tributing.

## NEPHE_SHADDOLL_FUSION (spell)
- file: `src_custom/spell_effects/nephe_shaddoll_fusion.c`
- clone: `src_custom/spell_effects/dark_fusion.c` (DARK_FUSION)
- text: Equip Shaddoll; set Attribute. Fusion Summon Shaddoll Fusion using equipped. OPT. Activate this card by declaring 1 Attribute. Equip only to a Shaddoll monster, and it becomes that Attribute. During your Main Phase: You can Fusion Summon 1 Shaddoll Fusion Monster from your Extra Deck, using monsters from your hand or field as Fusion Material, including the equipped monster. You can only use this effect of Nephe Shaddoll Fusion once per turn.

## SOUL_SERVANT (spell)
- file: `src_custom/spell_effects/soul_servant.c`
- clone: `src_custom/spell_effects/realm_of_light.c` (REALM_OF_LIGHT)
- text: Stack DM card on Deck. GY: draw for Palladium/DM. Place 1 card on top of the Deck from your hand, Deck, or GY, that is Dark Magician or specifically lists Dark Magician or Dark Magician Girl in its text, except Soul Servant. During your Main Phase: You can banish this card from your GY; draw cards equal to the number of Palladium monsters, Dark Magician, and/or Dark Magician Girl, with different names, on the field and in the GYs. You can only use this effect of Soul Servant once per turn.

## EVIL_ASSAULT (spell)
- file: `src_custom/spell_effects/evil_assault.c`
- clone: `src_custom/spell_effects/dark_calling.c` (DARK_CALLING)
- text: Discard 1; add or SS Lv4- Evil HERO from Deck. GY: banish; add Dark Fusion. Discard 1 card; take 1 Level 4 or lower Evil HERO monster from your Deck and either add it to your hand or Special Summon it, also for the rest of this turn after this card resolves, you cannot Special Summon from the Extra Deck, except HERO monsters. If this card is in your GY, except the turn it was sent there: You can banish this card from your GY; add 1 Dark Fusion from your GY to your hand. You can only use each eff
