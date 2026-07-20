# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## REPTILIANNE_SERVANT (permanent)
- file: `src_custom/permanent_effects/reptilianne_servant.c`
- clone: `src_custom/permanent_effects/reptilianne_naga.c` (REPTILIANNE_NAGA)
- text: Self-destroy if other face-up. Opp cannot attack this. Destroy this card if there are face-up monsters on the field other than this card. Destroy this card when it is targeted by the effect of a Spell or Trap Card. Neither player can Normal Summon a monster while this card is face-up on the field.

## GARONITH_LIGHTSWORN_DRAGON (permanent)
- file: `src_custom/permanent_effects/garonith_lightsworn_dragon.c`
- clone: `src_custom/permanent_effects/jenis_lightsworn_mender.c` (JENIS_LIGHTSWORN_MENDER)
- text: ATK per Lightsworn; pierce; mill 3. This card gains 300 ATK and DEF for each Lightsworn monster with a different name in your Graveyard. If this card attacks a Defense Position monster, inflict piercing battle damage to your opponent. During each of your End Phases: Send the top 3 cards of your Deck to the Graveyard.

## DESTINY_HERO_DOGMA (permanent)
- file: `src_custom/permanent_effects/destiny_hero_dogma.c`
- clone: `src_custom/permanent_effects/destiny_hero_defender.c` (DESTINY_HERO_DEFENDER)
- text: Destiny HERO - Dogma Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by Tributing 3 monsters, including at least 1 Destiny HERO monster. Once per turn, if you still control this face-up card during your opponent's next Standby Phase after you Special Summoned it this way: Halve your opponent's LP.

## HORUS_THE_BLACK_FLAME_DRAGON_LV4 (permanent)
- file: `src_custom/permanent_effects/horus_the_black_flame_dragon_lv4.c`
- clone: `src_custom/permanent_effects/dark_magician_of_chaos.c` (DARK_MAGICIAN_OF_CHAOS)
- text: Control of this face-up card cannot switch. During the End Phase, if this card destroyed a monster by  Control of this face-up card cannot switch. During the End Phase, if this card destroyed a monster by battle this turn: You can send this face-up card to the Graveyard; Special Summon 1 Horus the Black Flame Dragon LV6 from your hand or Deck.
