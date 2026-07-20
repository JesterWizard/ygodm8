# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## EVIL_HERO_INFERNAL_SNIPER (permanent)
- file: `src_custom/permanent_effects/evil_hero_infernal_sniper.c`
- clone: `src_custom/permanent_effects/evil_hero_infernal_prodigy.c` (EVIL_HERO_INFERNAL_PRODIGY)
- text: Dark Fusion. Spell immune. Standby: burn 1000 if face-up Defense. Elemental HERO Clayman + Elemental HERO Burstinatrix Must be Special Summoned with Dark Fusion and cannot be Special Summoned by other ways. This card cannot be destroyed by Spell Cards. During each of your Standby Phases: Inflict 1000 damage to your opponent. This card must be in face-up Defense Position to activate and to resolve this effect.

## EVIL_HERO_WILD_CYCLONE (permanent)
- file: `src_custom/permanent_effects/evil_hero_wild_cyclone.c`
- clone: `src_custom/permanent_effects/caius_the_shadow_monarch.c` (CAIUS_THE_SHADOW_MONARCH)
- text: On attack: lock S/T. On battle damage: destroy face-down S/T. Elemental HERO Avian + Elemental HERO Wildheart Must be Special Summoned with Dark Fusion and cannot be Special Summoned by other ways. If this card attacks, your opponent cannot activate any Spell/Trap Cards until the end of the Damage Step. When this card inflicts Battle Damage to your opponent: Destroy all face-down Spell and Trap Cards your opponent controls.

## GLADIATOR_BEAST_SAMNITE (permanent)
- file: `src_custom/permanent_effects/gladiator_beast_samnite.c`
- clone: `src_custom/permanent_effects/gladiator_beast_alexander.c` (GLADIATOR_BEAST_ALEXANDER)
- text: Search on battle kill; tag out. If this card was Special Summoned by the effect of a Gladiator Beast monster, when this card destroys an opponent's monster by battle and sends it to the Graveyard, you can add 1 Gladiator Beast card from your Deck to your hand. At the end of the Battle Phase, if this card attacked or was attacked, you can return it to the Deck to Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Samnite.

## EL_SHADDOLL_APKALLONE (permanent)
- file: `src_custom/permanent_effects/el_shaddoll_apkallone.c`
- clone: `src_custom/permanent_effects/el_shaddoll_winda.c` (EL_SHADDOLL_WINDA)
- text: On SS: negate face-up. GY: add Shaddoll, discard 1. 2 Shaddoll monsters with different Attributes Must first be Fusion Summoned. Cannot be destroyed by battle. You can only use each of the following effects of El Shaddoll Apkallone once per turn. If this card is Special Summoned: You can target 1 face-up card on the field; negate its effects. If this card is sent to the GY: You can add 1 Shaddoll card from your Deck or GY to your hand, then discard 1 card.
