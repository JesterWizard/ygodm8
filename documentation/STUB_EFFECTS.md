# Stub Effects Backlog

Auto-generated living list of effect files that still contain `TODO` stubs.
Entries disappear when the effect body is implemented (re-run `--write-list`).

```bash
python3 tools/stub_effect_queue.py --write-list
```

**Last updated:** 2026-07-20 21:18 UTC  
**Remaining stubs:** `68`

## Counts by kind

| Kind | Count |
|------|------:|
| `permanent` | 57 |
| `battle` | 8 |
| `turn` | 3 |
| **total** | **68** |

## permanent (57)

| `card_const` | archetype | pattern | clone | path |
|--------------|-----------|---------|-------|------|
| `ARCANA_FORCE_0_THE_FOOL` | `ARCANA_FORCE` | — | `ELEMENTAL_HERO_SUNRISE` | `src_custom/permanent_effects/arcana_force_0_the_fool.c` |
| `ARCANA_FORCE_III_THE_EMPRESS` | `ARCANA_FORCE` | — | `ARCANA_FORCE_VII_THE_CHARIOT` | `src_custom/permanent_effects/arcana_force_iii_the_empress.c` |
| `ARCANA_FORCE_THE_CHAOS_RULER` | `ARCANA_FORCE` | — | `REPTILIANNE_GARDNA` | `src_custom/permanent_effects/arcana_force_the_chaos_ruler.c` |
| `ARCANA_FORCE_XIV_TEMPERANCE` | `ARCANA_FORCE` | — | `ARCANA_FORCE_VI_THE_LOVERS` | `src_custom/permanent_effects/arcana_force_xiv_temperance.c` |
| `ARCANA_FORCE_XVIII_THE_MOON` | `ARCANA_FORCE` | — | `ARCANA_FORCE_VII_THE_CHARIOT` | `src_custom/permanent_effects/arcana_force_xviii_the_moon.c` |
| `ARCANA_FORCE_EX_THE_DARK_RULER` | `ARCANA_FORCE_EX_THE` | — | `RAVIEL_LORD_OF_PHANTASMS` | `src_custom/permanent_effects/arcana_force_ex_the_dark_ruler.c` |
| `ARCANA_FORCE_EX_THE_LIGHT_RULER` | `ARCANA_FORCE_EX_THE` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/arcana_force_ex_the_light_ruler.c` |
| `DARK_MAGICIAN_OF_DESTRUCTION` | `DARK_MAGICIAN_OF` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/dark_magician_of_destruction.c` |
| `DEEP_EYES_WHITE_DRAGON` | `DEEP` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/deep_eyes_white_dragon.c` |
| `DESTINY_HERO_DOGMA` | `DESTINY_HERO` | — | `DESTINY_HERO_DEFENDER` | `src_custom/permanent_effects/destiny_hero_dogma.c` |
| `DESTINY_HERO_DOUBLE_DUDE` | `DESTINY_HERO` | — | `ELEMENTAL_HERO_SHINING_PHOENIX_ENFORCER` | `src_custom/permanent_effects/destiny_hero_double_dude.c` |
| `DESTINY_HERO_DRAWHAND` | `DESTINY_HERO` | — | `ELEMENTAL_HERO_ESCURIDAO` | `src_custom/permanent_effects/destiny_hero_drawhand.c` |
| `DESTINY_HERO_DREADMASTER` | `DESTINY_HERO` | — | `RAVIEL_LORD_OF_PHANTASMS` | `src_custom/permanent_effects/destiny_hero_dreadmaster.c` |
| `DESTINY_HERO_DREAD_SERVANT` | `DESTINY_HERO` | — | `ELEMENTAL_HERO_SUNRISE` | `src_custom/permanent_effects/destiny_hero_dread_servant.c` |
| `DESTINY_HERO_DOOM_OVERLORD` | `DESTINY_HERO_DOOM` | — | `DES_FERAL_IMP` | `src_custom/permanent_effects/destiny_hero_doom_overlord.c` |
| `DRAGON_MASTER_MAGIA` | `DRAGON` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/dragon_master_magia.c` |
| `DRAGON_SPIRIT_OF_WHITE` | `DRAGON` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/dragon_spirit_of_white.c` |
| `ELEMENTAL_HERO_AIR_NEOS` | `ELEMENTAL_HERO` | — | `ELEMENTAL_HERO_SUNRISE` | `src_custom/permanent_effects/elemental_hero_air_neos.c` |
| `ELEMENTAL_HERO_FLARE_NEOS` | `ELEMENTAL_HERO` | — | `ELEMENTAL_HERO_SUNRISE` | `src_custom/permanent_effects/elemental_hero_flare_neos.c` |
| `EL_SHADDOLL_ANOYATYLLIS` | `EL_SHADDOLL` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/el_shaddoll_anoyatyllis.c` |
| `EL_SHADDOLL_APKALLONE` | `EL_SHADDOLL` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/el_shaddoll_apkallone.c` |
| `EL_SHADDOLL_CONSTRUCT` | `EL_SHADDOLL` | — | `DES_FERAL_IMP` | `src_custom/permanent_effects/el_shaddoll_construct.c` |
| `EL_SHADDOLL_GRYSTA` | `EL_SHADDOLL` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/el_shaddoll_grysta.c` |
| `EL_SHADDOLL_SHEKHINAGA` | `EL_SHADDOLL` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/el_shaddoll_shekhinaga.c` |
| `EL_SHADDOLL_WINDA` | `EL_SHADDOLL` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/el_shaddoll_winda.c` |
| `EVIL_DRAGON_ANANTA` | `EVIL` | — | `RAVIEL_LORD_OF_PHANTASMS` | `src_custom/permanent_effects/evil_dragon_ananta.c` |
| `EVIL_HERO_DARK_GAIA` | `EVIL_HERO` | — | `ARCANA_FORCE_VII_THE_CHARIOT` | `src_custom/permanent_effects/evil_hero_dark_gaia.c` |
| `EVIL_HERO_WILD_CYCLONE` | `EVIL_HERO` | — | `CAIUS_THE_SHADOW_MONARCH` | `src_custom/permanent_effects/evil_hero_wild_cyclone.c` |
| `EVIL_HERO_INFERNAL_SNIPER` | `EVIL_HERO_INFERNAL` | — | `EVIL_HERO_INFERNAL_PRODIGY` | `src_custom/permanent_effects/evil_hero_infernal_sniper.c` |
| `EVIL_HERO_INFERNO_WING` | `EVIL_HERO_INFERNO` | — | `ELEMENTAL_HERO_SHINING_FLARE_WINGMAN` | `src_custom/permanent_effects/evil_hero_inferno_wing.c` |
| `EVIL_HERO_INFERNO_WING_BACKFIRE` | `EVIL_HERO_INFERNO` | — | `ELEMENTAL_HERO_SHINING_FLARE_WINGMAN` | `src_custom/permanent_effects/evil_hero_inferno_wing_backfire.c` |
| `EVIL_HERO_MALICIOUS_FIEND` | `EVIL_HERO_MALICIOUS` | — | `EVIL_HERO_MALICIOUS_EDGE` | `src_custom/permanent_effects/evil_hero_malicious_fiend.c` |
| `GANDORA_X_THE_DRAGON_OF_DEMOLITION` | `GANDORA_X_THE_DRAGON_OF` | — | `CAIUS_THE_SHADOW_MONARCH` | `src_custom/permanent_effects/gandora_x_the_dragon_of_demolition.c` |
| `GARONITH_LIGHTSWORN_DRAGON` | `GARONITH` | — | `JENIS_LIGHTSWORN_MENDER` | `src_custom/permanent_effects/garonith_lightsworn_dragon.c` |
| `GLADIATOR_BEAST_ALEXANDER` | `GLADIATOR_BEAST` | — | `GLADIATOR_BEAST_SECUTOR` | `src_custom/permanent_effects/gladiator_beast_alexander.c` |
| `GLADIATOR_BEAST_DIMACARI` | `GLADIATOR_BEAST` | — | `GLADIATOR_BEAST_SECUTOR` | `src_custom/permanent_effects/gladiator_beast_dimacari.c` |
| `GLADIATOR_BEAST_GAIODIAZ` | `GLADIATOR_BEAST` | — | `GLADIATOR_BEAST_SECUTOR` | `src_custom/permanent_effects/gladiator_beast_gaiodiaz.c` |
| `GLADIATOR_BEAST_OCTAVIUS` | `GLADIATOR_BEAST` | — | `GLADIATOR_BEAST_SECUTOR` | `src_custom/permanent_effects/gladiator_beast_octavius.c` |
| `GLADIATOR_BEAST_RETIARI` | `GLADIATOR_BEAST` | — | `GLADIATOR_BEAST_SECUTOR` | `src_custom/permanent_effects/gladiator_beast_retiari.c` |
| `GLADIATOR_BEAST_SAMNITE` | `GLADIATOR_BEAST` | — | `GLADIATOR_BEAST_SECUTOR` | `src_custom/permanent_effects/gladiator_beast_samnite.c` |
| `GLADIATOR_BEAST_SPARTACUS` | `GLADIATOR_BEAST` | — | `GLADIATOR_BEAST_SECUTOR` | `src_custom/permanent_effects/gladiator_beast_spartacus.c` |
| `GRINDER_GOLEM` | `GRINDER` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/grinder_golem.c` |
| `HARPIE_PERFUMER` | `HARPIE` | — | `REPTILIANNE_GARDNA` | `src_custom/permanent_effects/harpie_perfumer.c` |
| `HARPIES_PET_PHANTASMAL_DRAGON` | `HARPIES_PET` | — | `REPTILIANNE_VIPER` | `src_custom/permanent_effects/harpies_pet_phantasmal_dragon.c` |
| `HORUS_THE_BLACK_FLAME_DRAGON_LV4` | `HORUS_THE_BLACK_FLAME_DRAGON` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/horus_the_black_flame_dragon_lv4.c` |
| `HORUS_THE_BLACK_FLAME_DRAGON_LV6` | `HORUS_THE_BLACK_FLAME_DRAGON` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/horus_the_black_flame_dragon_lv6.c` |
| `LEGENDARY_MAJU_GARZETT` | `LEGENDARY` | — | `ELEMENTAL_HERO_SHINING_FLARE_WINGMAN` | `src_custom/permanent_effects/legendary_maju_garzett.c` |
| `LIGHT_AND_DARKNESS_DRAGON` | `LIGHT` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/light_and_darkness_dragon.c` |
| `MAGICIAN_OF_DARK_ILLUSION` | `MAGICIAN` | — | `DARK_MAGICIAN_OF_CHAOS` | `src_custom/permanent_effects/magician_of_dark_illusion.c` |
| `MAGICIANS_ROD` | `MAGICIANS` | — | `REPTILIANNE_GARDNA` | `src_custom/permanent_effects/magicians_rod.c` |
| `OSHALEON` | `OSHALEON` | — | `REPTILIANNE_GARDNA` | `src_custom/permanent_effects/oshaleon.c` |
| `REPTILIANNE_SERVANT` | `REPTILIANNE` | — | `REPTILIANNE_NAGA` | `src_custom/permanent_effects/reptilianne_servant.c` |
| `THE_DARK_MAGICIANS` | `THE_DARK` | — | `ELEMENTAL_HERO_THE_SHINING` | `src_custom/permanent_effects/the_dark_magicians.c` |
| `THUNDER_DRAGON_COLOSSUS` | `THUNDER_DRAGON` | — | `ELEMENTAL_HERO_THE_SHINING` | `src_custom/permanent_effects/thunder_dragon_colossus.c` |
| `TIMEAEUS_THE_UNITED_MAGICAL_DRAGON` | `TIMEAEUS` | — | `RAVIEL_LORD_OF_PHANTASMS` | `src_custom/permanent_effects/timeaeus_the_united_magical_dragon.c` |
| `VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES` | `VENNOMINAGA` | — | `ELEMENTAL_HERO_SHINING_FLARE_WINGMAN` | `src_custom/permanent_effects/vennominaga_the_deity_of_poisonous_snakes.c` |
| `VENNOMINON_THE_KING_OF_POISONOUS_SNAKES` | `VENNOMINON` | — | `ELEMENTAL_HERO_ESCURIDAO` | `src_custom/permanent_effects/vennominon_the_king_of_poisonous_snakes.c` |

## battle (8)

| `card_const` | archetype | pattern | clone | path |
|--------------|-----------|---------|-------|------|
| `DON_ZALOOG` | `DON` | — | `THE_UNSTOPPABLE_EXODIA_INCARNATE` | `src_custom/battle_effects/don_zaloog.c` |
| `LIGHTNING_WARRIOR` | `LIGHTNING` | — | `HARPIE_LADY_3` | `src_custom/battle_effects/lightning_warrior.c` |
| `NEO_SPACIAN_GLOW_MOSS` | `NEO_SPACIAN` | — | `HARPIE_LADY_3` | `src_custom/battle_effects/neo_spacian_glow_moss.c` |
| `NEO_SPACIAN_GRAND_MOLE` | `NEO_SPACIAN` | — | `HARPIE_LADY_3` | `src_custom/battle_effects/neo_spacian_grand_mole.c` |
| `NEO_SPACIAN_TWINKLE_MOSS` | `NEO_SPACIAN` | — | `CYBER_BARRIER_DRAGON` | `src_custom/battle_effects/neo_spacian_twinkle_moss.c` |
| `RED_DRAGON_ARCHFIEND` | `RED` | — | `HARPIE_LADY_3` | `src_custom/battle_effects/red_dragon_archfiend.c` |
| `REPTILIANNE_GORGON` | `REPTILIANNE` | — | `HARPIE_LADY_3` | `src_custom/battle_effects/reptilianne_gorgon.c` |
| `REPTILIANNE_SCYLLA` | `REPTILIANNE` | — | `CYBER_BARRIER_DRAGON` | `src_custom/battle_effects/reptilianne_scylla.c` |

## turn (3)

| `card_const` | archetype | pattern | clone | path |
|--------------|-----------|---------|-------|------|
| `ARMED_DRAGON_LV3` | `ARMED_DRAGON` | — | `SINISTER_SERPENT` | `src_custom/turn_effects/armed_dragon_lv3.c` |
| `DESTINY_HERO_FEAR_MONGER` | `DESTINY_HERO` | — | `DARKLORD_MARIE` | `src_custom/turn_effects/destiny_hero_fear_monger.c` |
| `THE_WHITE_STONE_OF_ANCIENTS` | `THE_WHITE_STONE_OF` | — | `SINISTER_SERPENT` | `src_custom/turn_effects/the_white_stone_of_ancients.c` |
