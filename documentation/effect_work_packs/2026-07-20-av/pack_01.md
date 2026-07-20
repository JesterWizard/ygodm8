# Effect work pack 01 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## LEGENDARY_KNIGHT_CRITIAS (activated)
- file: `src_custom/activated_effects/legendary_knight_critias.c`
- clone: `src_custom/activated_effects/legendary_knight_timaeus.c` (LEGENDARY_KNIGHT_TIMAEUS)
- text: Must be SS by Legend of Heart. When SS: banish face-up S/T. When attacked: Set a Trap from GY. Cannot be Normal Summoned/Set. Must be Special Summoned with Legend of Heart. When this card is Special Summoned: You can target 1 face-up Spell/Trap on the field; banish that target. When this card is targeted for an attack: You can target 1 Trap in your GY; Set that target. It can be activated this turn.

## TIME_MAGIC_HAMMER (activated)
- file: `src_custom/activated_effects/time_magic_hammer.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: Must be Special Summoned with The Claw of Hermos, using a Spellcaster monster. If this card is Special Summoned: Target 1 other face-up monster on the field; equip this card to it. At the start of the Damage Step, if it battles an opponent's monster: You can roll a six-sided die, and banish that opponent's monster until the Standby Phase of the Nth turn after this effect's activation (N = the result).

## CLEAR_VICE_DRAGON (activated)
- file: `src_custom/activated_effects/clear_vice_dragon.c`
- clone: `src_custom/activated_effects/aromage_cananga.c` (AROMAGE_CANANGA)
- text: You are unaffected by the effects of "Clear World". If this card attacks an opponent's monster, the ATK of this card bec You are unaffected by the effects of Clear World. If this card attacks an opponent's monster, the ATK of this card becomes twice the ATK of the attack target, during damage calculation only. If this card would be destroyed by an opponent's card effect, you can discard 1 card instead.

## CYBER_ELTANIN (activated)
- file: `src_custom/activated_effects/cyber_eltanin.c`
- clone: `src_custom/activated_effects/cyber_phoenix.c` (CYBER_PHOENIX)
- text: Cannot be NS/Set. SS by banishing LIGHT Machines. When Summoned: send all other face-ups to GY. Cannot be Normal Summoned/Set. Must be Special Summoned (from your hand) by banishing all LIGHT Machine monsters from your field and GY. This card's ATK/DEF become the number of monsters banished for its Special Summon x 500. If this card is Special Summoned: Send all other face-up monsters on the field to the GY.
