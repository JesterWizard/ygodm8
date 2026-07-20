# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## MAGICIAN_NAVIGATION (trap)
- file: `src_custom/trap_effects/magician_navigation.c`
- clone: `src_custom/trap_effects/soul_levy.c` (SOUL_LEVY)
- text: SS Dark Magician from hand, then Lv7- DARK Spellcaster from Deck. Special Summon 1 Dark Magician from your hand, then Special Summon 1 Level 7 or lower DARK Spellcaster monster from your Deck. If you control Dark Magician, except the turn this card was sent to the GY: You can banish this card from your GY, then target 1 face-up Spell/Trap your opponent controls; negate its effects until the end of this turn.

## TYRANT_WING (trap)
- file: `src_custom/trap_effects/tyrant_wing.c`
- clone: `src_custom/trap_effects/ambush_fangs.c` (AMBUSH_FANGS)
- text: Target 1 Dragon monster on the field; equip this card to it. It gains 400 ATK/DEF, also it can make up to 2 attacks on m Target 1 Dragon monster on the field; equip this card to it. It gains 400 ATK/DEF, also it can make up to 2 attacks on monsters during each Battle Phase. Once per turn, during the End Phase, if the monster equipped with this card by this effect attacked an opponent's monster this turn: Destroy this card.

## INFINITE_IMPERMANENCE (trap)
- file: `src_custom/trap_effects/infinite_impermanence.c`
- clone: `src_custom/trap_effects/morphtronic_bind.c` (MORPHTRONIC_BIND)
- text: Target 1 face-up monster your opponent controls; negate its effects (until the end of this turn), then, if this card was Target 1 face-up monster your opponent controls; negate its effects (until the end of this turn), then, if this card was Set before activation and is on the field at resolution, for the rest of this turn all other Spell/Trap effects in this column are negated. If you control no cards, you can activate this card from your hand.

## AMAZONESS_HOT_SPRING (trap)
- file: `src_custom/trap_effects/amazoness_hot_spring.c`
- clone: `src_custom/trap_effects/lightsworn_judgement.c` (LIGHTSWORN_JUDGEMENT)
- text: When this card is activated: You can take 1 "Amazoness" monster from your Deck, and either add it to your hand or (if it When this card is activated: You can take 1 Amazoness monster from your Deck, and either add it to your hand or (if it is a Pendulum Monster) place it in your Pendulum Zone. When you take battle damage while you control an Amazoness Monster Card: You can gain LP equal to the damage you took. You can only use this effect of Amazoness Hot Spring once per turn.
