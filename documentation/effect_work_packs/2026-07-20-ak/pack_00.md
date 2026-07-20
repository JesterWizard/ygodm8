# Effect work pack 00 (4 cards)

Implement EVERY card in this pack. Clone from clone_path; match effect_text. Use duel_helpers.h. Spells: only edit the listed .c file. Activated/permanent may need monster_effects.h / dispatcher — serialize those. Do not leave TODO bodies. One make at the end of the whole batch.

## SILENT_SWORDSMAN_LV7 (activated)
- file: `src_custom/activated_effects/silent_swordsman_lv7.c`
- clone: `src_custom/activated_effects/elemental_hero_necroid_shaman.c` (ELEMENTAL_HERO_NECROID_SHAMAN)
- text: Cannot be Normal Summoned/Set. Must be Special Summoned by Silent Swordsman LV5, and cannot be Special Summoned by oth Cannot be Normal Summoned/Set. Must be Special Summoned by Silent Swordsman LV5, and cannot be Special Summoned by other ways. Negate all Spell effects on the field.

## LEVIAIR_THE_SEA_DRAGON (activated)
- file: `src_custom/activated_effects/leviair_the_sea_dragon.c`
- clone: `src_custom/activated_effects/elemental_hero_gaia.c` (ELEMENTAL_HERO_GAIA)
- text: 2 Level 3 monsters
Once per turn: You can detach 1 material from this card, then target 1 banished Level 4 or lower mon 2 Level 3 monsters Once per turn: You can detach 1 material from this card, then target 1 banished Level 4 or lower monster; Special Summon that target to your field.

## ROYAL_MAGICAL_LIBRARY (activated)
- file: `src_custom/activated_effects/royal_magical_library.c`
- clone: `src_custom/activated_effects/destiny_hero_disk_commander.c` (DESTINY_HERO_DISK_COMMANDER)
- text: Each time a Spell Card is activated, place 1 Spell Counter on this card when that Spell resolves (max. 3). You can remov Each time a Spell Card is activated, place 1 Spell Counter on this card when that Spell resolves (max. 3). You can remove 3 Spell Counters from this card; draw 1 card.

## MARSHMALLON (activated)
- file: `src_custom/activated_effects/marshmallon.c`
- clone: `src_custom/activated_effects/venom_boa.c` (VENOM_BOA)
- text: Cannot be destroyed by battle. After damage calculation, if this card was attacked, and was face-down at the start of th Cannot be destroyed by battle. After damage calculation, if this card was attacked, and was face-down at the start of the Damage Step: The attacking player takes 1000 damage.
