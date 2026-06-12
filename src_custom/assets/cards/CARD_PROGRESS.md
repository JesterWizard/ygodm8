<!-- card-art-progress:auto:begin -->
# Custom Card Progress

Tracks **80×80 big art** in `80x80/` against cards wired in `tools/card_data_manifest.json` (from `SORCERER_OF_DARK_MAGIC` onward).

Full workflow: [documentation/adding-custom-cards.md](../../../documentation/adding-custom-cards.md)

Regenerate the summary and tables: `python3 tools/card_art_progress.py` (last run: 2026-06-12).

## Summary

| Status | Count |
|--------|------:|
| In game (manifest + art) | 46 |
| Art ready, needs manifest | 97 |
| In manifest, missing art | 0 |
| **Total PNGs in `80x80/`** | **143** |

## In game

Manifest entry exists and `80x80/<stem>.png` is present.

| `card_const` | Card name | Art file |
|--------------|-----------|----------|
| `SORCERER_OF_DARK_MAGIC` | Sorcerer of Dark Magic | `sorcerer_of_dark_magic.png` |
| `DECK_DESTRUCTION_VIRUS` | Deck Destruction Virus | `deck_destruction_virus.png` |
| `MAGICIANS_VALKYRIA` | Magician's Valkyria | `magicians_valkyria.png` |
| `BLUE_EYES_SHINING_DRAGON` | Blue-Eyes Shining Dragon | `blue_eyes_shining_dragon.png` |
| `PALADIN_OF_WHITE_DRAGON` | Paladin Of White Dragon | `paladin_of_white_dragon.png` |
| `CARD_OF_DEMISE` | Card Of Demise | `card_of_demise.png` |
| `CARD_OF_SANCTITY` | Card Of Sanctity | `card_of_sanctity.png` |
| `SHIELD_AND_SWORD` | Shield And Sword | `shield_and_sword.png` |
| `BLUE_EYES_CHAOS_MAX_DRAGON` | Blue-Eyes Chaos Max Dragon | `blue_eyes_chaos_max_dragon.png` |
| `CHAIN_ENERGY` | Chain Energy | `chain_energy.png` |
| `SPELL_CANCELLER` | Spell Canceller | `spell_canceller.png` |
| `EXCHANGE` | Exchange | `exchange.png` |
| `COPYCAT` | Copycat | `copycat.png` |
| `MAGE_POWER` | Mage Power | `mage_power.png` |
| `KAIBAMAN` | Kaibaman | `kaibaman.png` |
| `ULTIMATE_OFFERING` | Ultimate Offering | `ultimate_offering.png` |
| `UNITED_WE_STAND` | United We Stand | `united_we_stand.png` |
| `WAVE_MOTION_CANNON` | Wave Motion Cannon | `wave_motion_cannon.png` |
| `ST_JOAN` | St Joan | `st_joan.png` |
| `PYRAMID_OF_LIGHT` | Pyramid of Light | `pyramid_of_light.png` |
| `SOUL_EXCHANGE` | Soul Exchange | `soul_exchange.png` |
| `MYSTICAL_SPACE_TYPHOON` | Mystical Space Typhoon | `mystical_space_typhoon.png` |
| `RARE_METAL_DRAGON` | Rare Metal Dragon | `rare_metal_dragon.png` |
| `DOUBLE_SUMMON` | Double Summon | `double_summon.png` |
| `OBNOXIOUS_CELTIC_GUARDIAN` | Obnoxious Celtic Guardian | `obnoxious_celtic_guardian.png` |
| `MASK_OF_RESTRICT` | Mask of Restrict | `mask_of_restrict.png` |
| `FAIRY_BOX` | Fairy Box | `fairy_box.png` |
| `COST_DOWN` | Cost Down | `cost_down.png` |
| `BLUE_EYES_ALTERNATIVE_WHITE_DRAGON` | Blue-Eyes Alternative White Dragon | `blue_eyes_alternative_white_dragon.png` |
| `ANCIENT_RULES` | Ancient Rules | `ancient_rules.png` |
| `MAGIC_JAMMER` | Magic Jammer | `magic_jammer.png` |
| `SEAL_OF_ORICHALCOS` | Seal of Orichalcos | `seal_of_orichalcos.png` |
| `FAMILIAR_KNIGHT` | Familiar Knight | `familiar_knight.png` |
| `RIRYOKU` | Riryoku | `riryoku.png` |
| `SPEAR_DRAGON` | Spear Dragon | `spear_dragon.png` |
| `SAGES_STONE` | Sage's Stone | `sages_stone.png` |
| `BOWGANIAN` | Bowganian | `bowganian.png` |
| `DARK_MAGIC_CURTAIN` | Dark Magic Curtain | `dark_magic_curtain.png` |
| `CATS_EAR_TRIBE` | Cat's Ear Tribe | `cats_ear_tribe.png` |
| `CURE_MERMAID` | Cure Mermaid | `cure_mermaid.png` |
| `DES_KOALA` | Des Koala | `des_koala.png` |
| `SKILL_DRAIN` | Skill Drain | `skill_drain.png` |
| `GUARDIAN_TREASURE` | Guardian Treasure | `guardian_treasure.png` |
| `JAR_OF_GREED` | Jar of Greed | `jar_of_greed.png` |
| `MAD_SWORD_BEAST` | Mad Sword Beast | `mad_sword_beast.png` |
| `OJAMA_TRIO` | Ojama Trio | `ojama_trio.png` |

## Todo — art ready, needs manifest

PNG is in `80x80/`; append a manifest entry and run `make`.

- [ ] `A_LEGENDARY_OCEAN` — `a_legendary_ocean.png`
- [ ] `AIRKNIGHT_PARSHAETH` — `airknight_parshaeth.png`
- [ ] `AMPHIBIOUS_BUGROTH_MK_3` — `amphibious_bugroth_mk_3.png`
- [ ] `ANDRO_SPHINX` — `andro_sphinx.png`
- [ ] `ATTACK_GUIDANCE_ARMOR` — `attack_guidance_armor.png`
- [ ] `AUTONOMOUS_ACTION_UNIT` — `autonomous_action_unit.png`
- [ ] `BACKFIRE` — `backfire.png`
- [ ] `BIG_BANG_SHOT` — `big_bang_shot.png`
- [ ] `BIRDFACE` — `birdface.png`
- [ ] `BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING` — `black_luster_soldier_envoy_of_the_beginning.png`
- [ ] `BLACK_TYRANNO` — `black_tyranno.png`
- [ ] `BLASTING_THE_RUINS` — `blasting_the_ruins.png`
- [ ] `BLOCK_ATTACK` — `block_attack.png`
- [ ] `BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON` — `blue_eyes_alternative_ultimate_dragon.png`
- [ ] `BLUE_EYES_CHAOS_DRAGON` — `blue_eyes_chaos_dragon.png`
- [ ] `BREAKER_THE_MAGICAL_WARRIOR` — `breaker_the_magical_warrior.png`
- [ ] `CALL_OF_THE_HAUNTED` — `call_of_the_haunted.png`
- [ ] `CARD_DESTRUCTION` — `card_destruction.png`
- [ ] `CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END` — `chaos_emperor_dragon_envoy_of_the_end.png`
- [ ] `CHAOS_FORM` — `chaos_form.png`
- [ ] `COFFIN_SELLER` — `coffin_seller.png`
- [ ] `COLD_WAVE` — `cold_wave.png`
- [ ] `CONFISCATION` — `confiscation.png`
- [ ] `CONTINUOUS_DESTRUCTION_PUNCH` — `continuous_destruction_punch.png`
- [ ] `CREATURE_SWAP` — `creature_swap.png`
- [ ] `CURSE_OF_DARKNESS` — `curse_of_darkness.png`
- [ ] `D.D_WARRIOR` — `d.d_warrior.png`
- [ ] `DARK_DRICERATOPS` — `dark_driceratops.png`
- [ ] `DARK_MAGICIAN_OF_CHAOS` — `dark_magician_of_chaos.png`
- [ ] `DARK_ROOM_OF_NIGHTMARE` — `dark_room_of_nightmare.png`
- [ ] `DARK_SNAKE_SYNDROME` — `dark_snake_syndrome.png`
- [ ] `DEDICATION_THROUGH_LIGHT_AND_DARKNESS` — `dedication_through_light_and_darkness.png`
- [ ] `DELINQUENT_DUO` — `delinquent_duo.png`
- [ ] `DES_COUNTERBLOW` — `des_counterblow.png`
- [ ] `DES_FERAL_IMP` — `des_feral_imp.png`
- [ ] `DIFFUSION_WAVE_MOTION` — `diffusion_wave_motion.png`
- [ ] `DOPPLEGANGER` — `doppleganger.png`
- [ ] `DOUBLE_COSTON` — `double_coston.png`
- [ ] `DOUBLE_SPELL` — `double_spell.png`
- [ ] `DRAGONS_RAGE` — `dragons_rage.png`
- [ ] `DRAINING_SHIELD` — `draining_shield.png`
- [ ] `DRILLAGO` — `drillago.png`
- [ ] `DROP_OFF` — `drop_off.png`
- [ ] `DUST_TORNADO` — `dust_tornado.png`
- [ ] `ECTOPLASMER` — `Ectoplasmer.png`
- [ ] `FIELDS_SANCTUARY` — `fields_sanctuary.png`
- [ ] `FIRE_PRINCESS` — `fire_princess.png`
- [ ] `GATE_GUARDIANS_COMBINED` — `gate_guardians_combined.png`
- [ ] `GIFT_OF_THE_MYSTICAL_ELF` — `gift_of_the_mystical_elf.png`
- [ ] `GILASAURAUS` — `gilasauraus.png`
- [ ] `GOBLIN_THIEF` — `goblin_thief.png`
- [ ] `GRACEFUL_CHARITY` — `graceful_charity.png`
- [ ] `GRAVITY_BIND` — `gravity_bind.png`
- [ ] `GREAT_MAJU_GARZETT` — `great_maju_garzett.png`
- [ ] `GREN_MAJU_DA_EIZA` — `gren_maju_da_eiza.png`
- [ ] `GUARDIAN_ANGEL_JOAN` — `guardian_angel_joan.png`
- [ ] `HARPIE_LADY_PHOENIX_FORMATION` — `harpie_lady_phoenix_formation.png`
- [ ] `HAYABUSA_KNIGHT` — `hayabusa_knight.png`
- [ ] `IMPERIAL_ORDER` — `imperial_order.png`
- [ ] `JUST_DESERTS` — `just_deserts.png`
- [ ] `KAISER_GLIDER` — `kaiser_glider.png`
- [ ] `MAGICAL_DIMENSION` — `magical_dimension.png`
- [ ] `MAGICAL_HATS` — `magical_hats.png`
- [ ] `MAJU_GARZETT` — `maju_garzett.png`
- [ ] `MASK_OF_DISPEL` — `mask_of_dispel.png`
- [ ] `MASK_OF_THE_ACCURSED` — `mask_of_the_accursed.png`
- [ ] `METEOR_OF_DESTRUCTION` — `meteor_of_destruction.png`
- [ ] `MIRROR_WALL` — `mirror_wall.png`
- [ ] `MONSTER_RECOVERY` — `monster_recovery.png`
- [ ] `NEGATIVE_ENERGY` — `negative_energy.png`
- [ ] `NEO_BLUE_EYES_ULTIMATE_DRAGON` — `neo_blue_eyes_ultimate_dragon.png`
- [ ] `NIGHTMARE_WHEEL` — `nightmare_wheel.png`
- [ ] `PETIT_THE_DARK_CLOWN` — `petit_the_dark_clown.png`
- [ ] `POLYMERIZATION` — `polymerization.png`
- [ ] `PROPHECY` — `prophecy.png`
- [ ] `RELOAD` — `reload.png`
- [ ] `REVERSE_OF_REVERSE` — `reverse_of_reverse.png`
- [ ] `RING_OF_DESTRUCTION` — `ring_of_destruction.png`
- [ ] `ROYAL_KNIGHT` — `royal_knight.png`
- [ ] `SCAPEGOAT` — `scapegoat.png`
- [ ] `SECRET_VILLAGE_OF_THE_SPELLCASTERS` — `secret_village_of_the_spellcasters.png`
- [ ] `SKILLED_DARK_MAGICIAN` — `skilled_dark_magician.png`
- [ ] `SKILLED_WHITE_MAGICIAN` — `skilled_white_magician.png`
- [ ] `SKULL_INVITATION` — `skull_invitation.png`
- [ ] `SOLEMN_WISHES` — `solemn_wishes.png`
- [ ] `SOUL_TAKER` — `soul_taker.png`
- [ ] `SPELL_ABSORPTION` — `spell_absorption.png`
- [ ] `SPHINX_TELEIA` — `sphinx_teleia.png`
- [ ] `SWIFT_GAIA_THE_FIERCE_KNIGHT` — `swift_gaia_the_fierce_knight.png`
- [ ] `THE_FLUTE_OF_SUMMONING_DRAGON` — `the_flute_of_summoning_dragon.png`
- [ ] `THEINEN_THE_GREAT_SPHINX` — `theinen_the_great_sphinx.png`
- [ ] `THOUSAND_KNIVES` — `thousand_knives.png`
- [ ] `TIME_SEAL` — `time_seal.png`
- [ ] `TOON_WORLD` — `toon_world.png`
- [ ] `UPSTART_GOBLIN` — `upstart_goblin.png`
- [ ] `WATAPON` — `watapon.png`
- [ ] `WHITE_DRAGON_RITUAL` — `white_dragon_ritual.png`

## Todo — in manifest, missing art

_No manifest entries are missing art right now._
<!-- card-art-progress:auto:end -->

## Backlog — needs art

Planned cards with no `80x80/<stem>.png` yet. Add lines here; they are preserved when you rerun this script.

```text
# CARD_CONST — optional note
```
