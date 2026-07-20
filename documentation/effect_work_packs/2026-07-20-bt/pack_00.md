# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## HORUS_THE_BLACK_FLAME_DRAGON_LV6 (permanent)
- file: `src_custom/permanent_effects/horus_the_black_flame_dragon_lv6.c`
- clone: `src_custom/permanent_effects/horus_the_black_flame_dragon_lv4.c` (HORUS_THE_BLACK_FLAME_DRAGON_LV4)
- text: This card is unaffected by Spell effects. During the End Phase, if this card destroyed a monster by battle  This card is unaffected by Spell effects. During the End Phase, if this card destroyed a monster by battle this turn: You can send this face-up card to the Graveyard; Special Summon 1 Horus the Black Flame Dragon LV8 from your hand or Deck.

## GLADIATOR_BEAST_DIMACARI (permanent)
- file: `src_custom/permanent_effects/gladiator_beast_dimacari.c`
- clone: `src_custom/permanent_effects/gladiator_beast_secutor.c` (GLADIATOR_BEAST_SECUTOR)
- text: Double attack; tag out after battle. If this card was Special Summoned by the effect of a Gladiator Beast monster, it can attack twice during each Battle Phase. At the end of the Battle Phase, if this card attacked or was attacked, you can return it to the Deck to Special Summon 1 Gladiator Beast monster from your Deck, except Gladiator Beast Dimacari.

## EL_SHADDOLL_WINDA (permanent)
- file: `src_custom/permanent_effects/el_shaddoll_winda.c`
- clone: `src_custom/permanent_effects/el_shaddoll_anoyatyllis.c` (EL_SHADDOLL_ANOYATYLLIS)
- text: Opp can't destroy this. SS lock once/turn each. GY: add S/T. 1 Shaddoll monster + 1 DARK monster Must first be Fusion Summoned. Cannot be destroyed by an opponent's card effects. Each player can only Special Summon monster(s) once per turn while this card is face-up on the field. If this card is sent to the GY: You can target 1 Shaddoll Spell/Trap in your GY; add it to your hand.

## ARCANA_FORCE_0_THE_FOOL (permanent)
- file: `src_custom/permanent_effects/arcana_force_0_the_fool.c`
- clone: `src_custom/permanent_effects/elemental_hero_sunrise.c` (ELEMENTAL_HERO_SUNRISE)
- text: Indestructible. Coin: immunity or self-negate. This card cannot be destroyed by battle. This card cannot be changed to Defense Position, except with a card effect. When this card is Summoned: Toss a coin and gain the appropriate effect. Heads: Negate your card effects that target this card, and destroy them. Tails: Negate your opponent's card effects that target this card, and destroy them.
