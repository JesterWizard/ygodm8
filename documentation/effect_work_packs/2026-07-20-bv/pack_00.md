# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MAGICIANS_ROD (permanent)
- file: `src_custom/permanent_effects/magicians_rod.c`
- clone: `src_custom/permanent_effects/reptilianne_gardna.c` (REPTILIANNE_GARDNA)
- text: On NS: add S/T listing DM. GY: Tribute Spellcaster; add this. When this card is Normal Summoned: You can add 1 Spell/Trap from your Deck to your hand, that specifically lists the card Dark Magician in its text. During your opponent's turn, if you activate a Spell/Trap Card or effect while this card is in your GY (except during the Damage Step): You can Tribute 1 Spellcaster monster; add this card to your hand. You can only use each effect of Magician's Rod once per turn.

## EVIL_HERO_INFERNO_WING (permanent)
- file: `src_custom/permanent_effects/evil_hero_inferno_wing.c`
- clone: `src_custom/permanent_effects/elemental_hero_shining_flare_wingman.c` (ELEMENTAL_HERO_SHINING_FLARE_WINGMAN)
- text: Dark Fusion. Piercing. On battle destroy: burn higher ATK/DEF. Elemental HERO Avian + Elemental HERO Burstinatrix Must be Special Summoned with Dark Fusion and cannot be Special Summoned by other ways. If this card attacks a Defense Position monster, inflict piercing Battle Damage to your opponent. When this card destroys a monster by battle and sends it to the Graveyard: Inflict damage to your opponent equal to either the ATK or DEF (whichever is higher) of the destroyed monster in the Graveyar

## EL_SHADDOLL_GRYSTA (permanent)
- file: `src_custom/permanent_effects/el_shaddoll_grysta.c`
- clone: `src_custom/permanent_effects/el_shaddoll_winda.c` (EL_SHADDOLL_WINDA)
- text: Negate opp SS; destroy, send Shaddoll from hand. GY: add S/T. 1 Shaddoll monster + 1 FIRE monster Must first be Fusion Summoned. When your opponent would Special Summon a monster(s) while you have a Shaddoll card in your hand (Quick Effect): You can negate the Summon, and if you do, destroy that monster, then send 1 Shaddoll card from your hand to the GY. You can only use this effect of El Shaddoll Grysta once per turn. If this card is sent to the GY: You can target 1 Shaddoll Spell/Trap in your

## LIGHT_AND_DARKNESS_DRAGON (permanent)
- file: `src_custom/permanent_effects/light_and_darkness_dragon.c`
- clone: `src_custom/permanent_effects/el_shaddoll_winda.c` (EL_SHADDOLL_WINDA)
- text: Once/Chain: when activated, -500 ATK/DEF to negate. On destruction: clear field, SS GY monster. Cannot be Special Summoned. While face-up on the field, this card is also DARK-Attribute. Once per Chain, during either player's turn, when a Spell Card, Trap Card, or monster effect is activated: This card loses exactly 500 ATK and DEF and that activation is negated. When this card is destroyed and sent to the Graveyard: Target 1 monster in your Graveyard (if possible); destroy all cards you control,
