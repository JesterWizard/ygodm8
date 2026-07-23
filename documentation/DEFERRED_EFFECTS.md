# Deferred Effects Backlog

Auto-generated living list of **engine gaps** still called out in effect-file comments (plain notes after `Ceiling:`/`ponytail:` soft-clears).
Use this to pick an engine surface and batch the cards that wait on it.
Stubs: [`STUB_EFFECTS.md`](STUB_EFFECTS.md). Ceiling markers: [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md). Migration: [`effect-data-system.md`](effect-data-system.md).

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials + deferred
```

**Last updated:** 2026-07-22 22:13 UTC  
**Files with deferred notes:** `94`  
**Notes tagged:** `105`

## Suggested tackle order

Difficulty order (easiest first) for the restored backlog:

1. **Extra Deck effects** — `extra.XyzLinkSynchro` / `event.OnFusionSummon`. Extra Deck exists in-game; do **not** soft-clear these as omitted.
2. **Chain / negate** — `chain.Negate` (Quick negate notes). Chain is on the horizon; keep this as the active follow-up list.
3. **Remaining UI / summon / destroy gates** — leftover `ui.Choice`, `gate.Tribute`, send-cost, etc.

Do not mark Extra Deck or chain debt as accepted omissions.

## Counts by missing surface

| Tag | Notes | Cards | Suggested phase |
|-----|------:|------:|-----------------|
| `extra.XyzLinkSynchro` | 61 | 55 | now (Extra Deck exists) |
| `chain.Negate` | 40 | 36 | next (chain on horizon) |
| `event.OnFusionSummon` | 3 | 3 | now (Extra Deck Fusion) |
| `event.OnSummon` | 1 | 1 | 3 |
| **total** | **105** | **94** | |

## `extra.XyzLinkSynchro` (61 notes)

### `AMAZONESS_HALL` (trap)
- path: `src_custom/trap_effects/amazoness_hall.c`
- L42: On activate: add 1 Amazoness from GY to hand. Extra Deck / Pendulum place + opp SS gain LP need hooks.

### `ANCIENT_GEAR_DUEL` (trap)
- path: `src_custom/trap_effects/ancient_gear_duel.c`
- L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks; mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate A

### `ANCIENT_GEAR_MEGATON_GOLEM` (activated)
- path: `src_custom/activated_effects/ancient_gear_megaton_golem.c`
- L140: Extra Deck Ultimate AG Golem SS blocked — AG Golem from hand/GY/Deck instead.
- L213: OPT SS AG Golem from hand/GY. Pierce via ApplyAncientGearGolemPiercingBattleEffect. Leave → AG Golem hand/GY/Deck via AncientGearMegatonGolem_EnsureInit (Extra Deck Ultimate blocked). multi-attack.

### `ARCANITE_MAGICIAN` (activated)
- path: `src_custom/activated_effects/arcanite_magician.c`
- L160: Synchro +2 Spell Counters + +1000 ATK/counter need synchro/stat hooks. OPT remove 1 unk4 counter → destroy 1 opp (EffectOpt).

### `BLUE_EYES_SPIRIT_DRAGON` (activated)
- path: `src_custom/activated_effects/blue_eyes_spirit_dragon.c`
- L65: OPT GY negate + Extra Synchro + EP destroy need chain/Extra hooks. OPT tribute self → SS LIGHT Dragon from Deck in DEF.

### `CELESTIAL_KNIGHTLORD_PARSHATH` (activated)
- path: `src_custom/activated_effects/celestial_knightlord_parshath.c`
- L105: OPT discard 1 → add Sanctuary/mention, or Fairy if Sanctuary on field (EffectOpt). Link material + GY banish Fairy → SS Fairy need send/banish hooks.

### `CHIMERATECH_FORTRESS_DRAGON` (activated)
- path: `src_custom/activated_effects/chimeratech_fortress_dragon.c`
- L12: Fusion ATK overlay via ChimeratechFortressDragon_ApplyDynamicZoneStats. Not field-ignition.

### `CHIMERATECH_MEGAFLEET_DRAGON` (activated)
- path: `src_custom/activated_effects/chimeratech_megafleet_dragon.c`
- L12: Fusion ATK overlay via ChimeratechMegafleetDragon_ApplyDynamicZoneStats. Not field-ignition.

### `CORAL_DRAGON` (activated)
- path: `src_custom/activated_effects/coral_dragon.c`
- L23: Any leave ≈ Synchro-Summoned leave; SS-origin flag not tracked.

### `CRIMSON_DRAGON` (activated)
- path: `src_custom/activated_effects/crimson_dragon.c`
- L124: Extra Deck Synchro SS FALSE; Deck Dragon stand-in.
- L197: On-SS search via TryCrimsonDragonOnMonsterPlacement (EffectOpt). OPT search mentioning Crimson Dragon S/T (shares EffectOpt). Extra Deck Synchro SS FALSE; Deck Dragon stand-in.

### `CYBER_DRAGON_INFINITY` (activated)
- path: `src_custom/activated_effects/cyber_dragon_infinity.c`
- L63: Xyz attach / negate FALSE. ClearZone absorb + +1 tempStage.
- L131: ATK overlay via CyberDragonInfinity_ApplyDynamicZoneStats (+200 per tempStage). Xyz attach / negate FALSE. OPT ClearZone absorb + tempStage (EffectOpt).

### `CYBER_SLASH_HARPIE_LADY` (activated)
- path: `src_custom/activated_effects/cyber_slash_harpie_lady.c`
- L198: Synchro treat-Harpie-as-Tuner missing. Quick bounce on S/T activate wired via ON_CARD_ACTIVATE + deferred PickZone.

### `CYBER_SLASH_HARPY_LADY` (activated)
- path: `src_custom/activated_effects/cyber_slash_harpy_lady.c`
- Shares CanActivate/Activate with `cyber_slash_harpie_lady.c`. Synchro treat-Harpie-as-Tuner missing.

### `DESTINY_HERO_DUSKTOPIA` (activated)
- path: `src_custom/activated_effects/destiny_hero_dusktopia.c`
- L46: Battle protect + no battle damage via DestinyHeroDusktopia_*; EP clear via TryClearDestinyHeroDusktopiaProtectionEndPhase. Fusion on Summon need fusion hook (Extra Deck fusion from hand/field).

### `DIVINER_OF_THE_HERALD` (activated)
- path: `src_custom/activated_effects/diviner_of_the_herald.c`
- L84: Extra Deck Fairy mill skipped.
- L105: Extra Deck Fairy mill skipped.

### `EBON_ILLUSION_MAGICIAN` (activated)
- path: `src_custom/activated_effects/ebon_illusion_magician.c`
- L78: Xyz detach cost + attack-banish FALSE. OPT SS Spellcaster Normal from hand/Deck (detach stand-in).

### `EVOLZAR_DOLKKA` (activated)
- path: `src_custom/activated_effects/evolzar_dolkka.c`
- L12: Quick Xyz detach + negate monster effect need chain/Xyz hooks outside this file. Not field-ignition.

### `FAVOURITE_CONTACT` (trap)
- path: `src_custom/trap_effects/favourite_contact.c`
- L48: Extra Deck Fusion ignoring summon conditions + materials to Deck bottom need fusion recipe API; return up to 2 HERO/Neos/ Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free.

### `FORMULA_SYNCHRON` (activated)
- path: `src_custom/activated_effects/formula_synchron.c`
- L32: Synchro Summon draw trigger + opp-Main-Phase quick Synchro need synchro/chain hooks. OPT draw 1 via usage when deck remains.

### `GAGAGIGO_THE_RISEN` (activated)
- path: `src_custom/activated_effects/gagagigo_the_risen.c`
- L12: No printed monster effect (Xyz materials only). Not field-ignition.
- L18: No printed monster effect (Xyz materials only). Not field-ignition.

### `GANDORA_X_THE_DRAGON_OF_DEMOLITION` (permanent)
- path: `src_custom/permanent_effects/gandora_x_the_dragon_of_demolition.c`
- L119: EP half LP needs EP hook; on-summon wipe only here. ATK overlay via GandoraX_ApplyDynamicZoneStats.

### `GANDORA_X_THE_DRAGON_OF_DESTRUCTION` (activated)
- path: `src_custom/activated_effects/gandora_x_the_dragon_of_destruction.c`
- L102: on-NS/SS-from-hand wipe needs summon hook. OPT destroy/burn + ATK overlay via GandoraX_ApplyDynamicZoneStats; EP self-destroy via TryApplyGandoraXEndPhase.

### `GLADIATOR_BEAST_ANDABATA` (activated)
- path: `src_custom/activated_effects/gladiator_beast_andabata.c`
- L135: Extra Deck return + Lv≤7 GB Fusion Extra SS need ED/Fusion APIs.

### `GLADIATOR_BEAST_GYZARUS` (activated)
- path: `src_custom/activated_effects/gladiator_beast_gyzarus.c`
- L174: Tag-out via GladiatorBeast_CanActivateDeckTagOutTwo. Contact Fusion SS destroy trigger + Extra Deck return not wired.

### `GRAVEKEEPERS_SHAMAN` (activated)
- path: `src_custom/activated_effects/gravekeepers_shaman.c`
- L62: DEF overlay via GravekeepersShaman_ApplyDynamicZoneStats. GY-effect negate + Necrovalley Field lock need permanent hooks.

### `GRAVEKEEPERS_SPIRITUALIST` (activated)
- path: `src_custom/activated_effects/gravekeepers_spiritualist.c`
- L12: Necrovalley-gated Spellcaster Fusion from Extra Deck needs fusion summon API outside this file. Not field-ignition.

### `HARPIES_PET_PHANTASMAL_DRAGON` (permanent)
- path: `src_custom/permanent_effects/harpies_pet_phantasmal_dragon.c`
- Direct attack / Harpie attack+effect protect / EP detach wired while materials remain. Xyz summon materials still require Extra Deck XYZ flow.

### `INSTANT_CONTACT` (spell)
- path: `src_custom/spell_effects/instant_contact.c`
- L153: Extra Deck off: offer matching Fusion recipe results by id.

### `INSTANT_FUSION` (spell)
- path: `src_custom/spell_effects/instant_fusion.c`
- L130: Extra Deck off: offer Level ≤5 Fusion recipe results by id.

### `LEVEL_EATER` (activated)
- path: `src_custom/activated_effects/level_eater.c`
- L122: no zone Level-mod field (level is ROM-only via gCardData_NEW). SS self from GY; upgrade: TempLevel overlay on target.
- L178: no zone Level-mod field (level is ROM-only via gCardData_NEW). SS self from GY; upgrade: TempLevel overlay on target.

### `LEVIAIR_THE_SEA_DRAGON` (activated)
- path: `src_custom/activated_effects/leviair_the_sea_dragon.c`
- L106: No Xyz detach cost; OPT SS banished Lv≤4 stand-in when RFP enabled. Materials not checked; overlay detach before SS not wired.

### `LEV_SHADDOLL_FUSION` (spell)
- path: `src_custom/spell_effects/lev_shaddoll_fusion.c`
- L158: the face-up ignition still needs a monster-zone tribute picker and an Extra Deck special-summon flow, neither of which is owned by this spell activation dispatcher.

### `LIFE_STREAM_DRAGON` (activated)
- path: `src_custom/activated_effects/life_stream_dragon.c`
- L28: Synchro LP=4000 trigger + no effect damage + Equip-banish destruction-replace need synchro/LP/battle hooks. OPT set LP to 4000 via usage.

### `MAGICAL_SCIENTIST` (activated)
- path: `src_custom/activated_effects/magical_scientist.c`
- L215: no direct attack + End Phase Extra Deck return need battle/EP hooks. pay 1000 → SS Lv≤6 Fusion from Extra/recipe list.

### `MINERVA_THE_ATHENIAN_LIGHTSWORN` (activated)
- path: `src_custom/activated_effects/minerva_the_athenian_lightsworn.c`
- L184: anti-banish continuous + Synchro material count need continuous/synchro hooks. OPT mill LS different Types (up to field LS count), or banish ≤4 LS GY → mill.

### `MINERVA_THE_EXHALTED_LIGHTSWORN` (activated)
- path: `src_custom/activated_effects/minerva_the_exhalted_lightsworn.c`
- L69: Xyz detach + destroy-on-death FALSE. OPT mill 3 → draw = Lightsworn among milled.

### `MORPHTRONIC_EARFON` (activated)
- path: `src_custom/activated_effects/morphtronic_earfon.c`
- L53: real Tuner flag / Equip double-attack need Synchro/equip hooks. OPT mark unk4 as Tuner stand-in.

### `NECROFACE` (activated)
- path: `src_custom/activated_effects/necroface.c`
- L106: tempStage unit is ~500 ATK, not printed +100; upgrade: exact overlay.

### `NEO_SPACIAN_DARK_PANTHER` (activated)
- path: `src_custom/activated_effects/neo_spacian_dark_panther.c`
- L12: Copy opp monster name/effects needs engine name/effect overlay outside this file. Not field-ignition.

### `NUMBER_39_UTOPIA` (activated)
- path: `src_custom/activated_effects/number_39_utopia.c`
- L12: Attack negate via detach + no-material self-destroy need battle hook and XYZ material system outside this file. Not field-ignition.

### `PROTECTOR_OF_THE_AGENTS_MOON` (activated)
- path: `src_custom/activated_effects/protector_of_the_agents_moon.c`
- L305: Link Summon trigger gate missing. OPT mill/add Sanctuary path, else OPT tribute Fairy → destroy 1 opp.

### `REPTILIANNE_ECHIDNA` (activated)
- path: `src_custom/activated_effects/reptilianne_echidna.c`
- L230: Link Summon trigger + Extra Deck lock FALSE. OPT set 1 opp face-up ATK to 0, else OPT add Reptiles up to 0-ATK count. Separate OPT flags share one MarkMonsterEffectUsed.

### `REPTILIANNE_LAMIA` (activated)
- path: `src_custom/activated_effects/reptilianne_lamia.c`
- L175: GY synchro-material ATK-0 need synchro hook. Remains. FromHand ATK-0 + SS via TrySpecialSummonReptilianneLamiaFromHand; not field-ignition.

### `ROAD_SYNCHRON` (activated)
- path: `src_custom/activated_effects/road_synchron.c`
- L12: Synchro Level -2 (non-Road Warrior) + battle-hit Level +1 need synchro/battle hooks outside this file. Not field-ignition.

### `SHADDOLL_FUSION` (spell)
- path: `src_custom/spell_effects/shaddoll_fusion.c`
- L49: Proxy for "Special Summoned from the Extra Deck" — Extra Deck colors on field.

### `SHADDOLL_SCHISM` (trap)
- path: `src_custom/trap_effects/shaddoll_schism.c`
- L65: Extra Deck not modeled — leave continuous face-up only.

### `TATSUNOKO` (activated)
- path: `src_custom/activated_effects/tatsunoko.c`
- L12: Hand-as-Synchro-material and unaffected-by-monster-effects need synchro/summon continuous hooks outside this file. Not field-ignition.

### `TEST_PANTHER` (activated)
- path: `src_custom/activated_effects/test_panther.c`
- L199: Link Summon trigger for search needs summon hook. OPT search GB from Deck, else bounce GB → SS different GB.

### `THUNDER_END_DRAGON` (activated)
- path: `src_custom/activated_effects/thunder_end_dragon.c`
- L59: No Xyz detach cost; OPT destroy-all-other-monsters stand-in. Materials not checked; overlay detach before destroy not wired.

### `TIME_THIEF_REDOER` (activated)
- path: `src_custom/activated_effects/time_thief_redoer.c`
- L140: detach materials + banish-until-EP FALSE. OPT draw 1 OR return 1 face-up opp monster to Deck.

### `TOADALLY_AWESOME` (activated)
- path: `src_custom/activated_effects/toadally_awesome.c`
- L212: detach/Standby/negate FALSE. OPT SS Frog from Deck, else OPT send Aqua → destroy 1 opp.

### `TRISHULA_DRAGON_OF_THE_ICE_BARRIER` (activated)
- path: `src_custom/activated_effects/trishula_dragon_of_the_ice_barrier.c`
- L114: Synchro Summon trigger needs synchro hook outside; once via usage banish random opp hand + 1 field + 1 GY when available.

### `TUNINGWARE` (activated)
- path: `src_custom/activated_effects/tuningware.c`
- L12: Synchro level-2 treatment + draw-on-material need synchro hooks outside this file. Not field-ignition.

### `T_G_HYPER_LIBRARIAN` (activated)
- path: `src_custom/activated_effects/t_g_hyper_librarian.c`
- L12: Synchro Summon draw trigger needs synchro hook outside this file. Not field-ignition.

### `URGENT_TUNING` (trap)
- path: `src_custom/trap_effects/urgent_tuning.c`
- L14: Synchro Summon during Battle Phase needs Synchro material/ED summon path outside this file (no in-file Synchro API). shows text + self-destroy; upgrade: collect Tuners + non-Tuners → Extra Deck Synchro SS.

## `event.OnSummon` (1 notes)

### `SHADDOLL_SCHISM` (trap)
- path: `src_custom/trap_effects/shaddoll_schism.c`
- L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker; banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.

## `event.OnFusionSummon` (3 notes)

### `ELEMENTAL_HERO_DARK_NEOS` (activated)
- path: `src_custom/activated_effects/elemental_hero_dark_neos.c`
- L92: EP Extra return via TryReturnContactFusionsAtEndPhase. Contact Fusion need fusion hook outside.

### `PREDAPLANT_VERTE_ANACONDA` (activated)
- path: `src_custom/activated_effects/predaplant_verte_anaconda.c`
- L131: DARK attribute mark + Poly/Fusion copy SS need attribute/fusion hooks. OPT pay 2000 LP → destroy 1 field card (EffectOpt; Fusion-copy stand-in).

### `SECRETS_OF_DARK_MAGIC` (spell)
- path: `src_custom/spell_effects/secrets_of_dark_magic.c`
- L33: Local recipes that list Dark Magician / Dark Magician Girl as material. incomplete vs printed DM Fusion pool (Dragon Knight, etc.). Amulet Dragon + The Dark Magicians only; upgrade: add remaining DM Fusion recipes to thi

## `chain.Negate` (40 notes)

### `ARCANA_FORCE_EX_THE_LIGHT_RULER` (permanent)
- path: `src_custom/permanent_effects/arcana_force_ex_the_light_ruler.c`
- L100: Tails negate FALSE; Heads only when GY→hand legal.
- L125: Tails Quick negate + battle add need chain/battle hooks.

### `ARCANA_KNIGHT_JOKER` (activated)
- path: `src_custom/activated_effects/arcana_knight_joker.c`
- L12: Discard matching type to negate activation needs chain/response hooks outside this file. Not field-ignition.

### `ASH_BLOSSOM_AND_JOYOUS_SPRING` (activated)
- path: `src_custom/activated_effects/ash_blossom_and_joyous_spring.c`
- L15: Printed quick discard negate uses FromHand path.
- L50: chain negate for add/SS/mill from Deck not wired; upgrade: chain interrupt hook when one exists.

### `BLUE_EYES_ULTIMATE_SPIRIT_DRAGON` (activated)
- path: `src_custom/activated_effects/blue_eyes_ultimate_spirit_dragon.c`
- L24: OPT +2 tempStage (~+1000) as negate stand-in (EffectOpt). Quick field negate + destroy-SS FALSE; GY banish-lock FALSE.

### `CYBER_KIRIN` (permanent)
- path: `src_custom/permanent_effects/cyber_kirin.c`
- L8: ATK-position spell/trap negate, battle-draw, and OPT tribute damage zero need continuous/battle/tribute hooks not wired for permanents.

### `DESTINY_HERO_DARK_ANGEL` (activated)
- path: `src_custom/activated_effects/destiny_hero_dark_angel.c`
- L81: field spell-negate FALSE. FromHand discard → SS D-HERO to opp DEF.

### `DESTINY_HERO_DECIDER` (activated)
- path: `src_custom/activated_effects/destiny_hero_decider.c`
- L115: EP add on NS/SS via TryApplyDestinyHeroDeciderEndPhase. OPT add 1 HERO from GY to hand (EffectOpt). GY quick return-on-damage need chain hook.

### `DESTINY_HERO_DESTROY_DOGMA` (activated)
- path: `src_custom/activated_effects/destiny_hero_destroy_dogma.c`
- L103: Standby burn via TryApplyDestinyHeroDestroyDogmaStandby. Quick destroy/negate FALSE. FromHand banish 3 Warrior/DARK → SS + burn 2000.

### `DESTINY_HERO_PLASMA` (activated)
- path: `src_custom/activated_effects/destiny_hero_plasma.c`
- L95: equip/absorb + half-ATK boost + continuous opp negate need equip hooks. destroy 1 opp monster.

### `DIVINE_SERPENT_GEH` (activated)
- path: `src_custom/activated_effects/divine_serpent_geh.c`
- L40: Untargetable via DivineSerpentGeh_IsTargetImmune; FromHand half-LP SS below. destroy gate + battle negate need destroy/battle hooks. field ignition FALSE.

### `DRAGON_MASTER_MAGIA` (permanent)
- path: `src_custom/permanent_effects/dragon_master_magia.c`
- L8: Quick negate-by-card-type needs chain/OPT hooks.

### `ELEMENTAL_HERO_NEBULA_NEOS` (activated)
- path: `src_custom/activated_effects/elemental_hero_nebula_neos.c`
- L120: Extra SS trigger FALSE. OPT draw = opp card count + negate via targeting; EP banish field via TryApplyElementalHeroNebulaNeosEndPhase.

### `EL_SHADDOLL_GRYSTA` (permanent)
- path: `src_custom/permanent_effects/el_shaddoll_grysta.c`
- L126: negate opp Special Summon + send Shaddoll from hand need SS chain hook.

### `EL_SHADDOLL_SHEKHINAGA` (permanent)
- path: `src_custom/permanent_effects/el_shaddoll_shekhinaga.c`
- L126: negate SS monster effect + send Shaddoll need effect-chain hook.

### `GLADIATOR_BEAST_HERAKLINOS` (activated)
- path: `src_custom/activated_effects/gladiator_beast_heraklinos.c`
- L150: Either-turn chain negate needs chain hook outside this file. OPT discard 1 → destroy 1 opponent card (EffectOpt).

### `GODDESS_BOW` (activated)
- path: `src_custom/activated_effects/goddess_bow.c`
- L12: Hermos fusion + equip + battle-phase negate/second attack need fusion/equip/chain hooks outside this file. Not field-ignition.

### `GRAVEKEEPERS_WATCHER` (activated)
- path: `src_custom/activated_effects/gravekeepers_watcher.c`
- L15: Either-turn chain negate when opp discards needs chain/negation hooks outside this file. Not field-ignition; discard-from-hand path below.
- L47: negate activation + destroy activated card not wired.

### `HERALD_OF_PERFECTION` (activated)
- path: `src_custom/activated_effects/herald_of_perfection.c`
- L12: Quick negate by sending Fairy from hand needs chain/negation hooks outside. Not field-ignition (either-turn discard Fairy → negate + destroy).

### `HERALD_OF_THE_ARC_LIGHT` (activated)
- path: `src_custom/activated_effects/herald_of_the_arc_light.c`
- L12: Deck/hand mill-banish + Quick tribute-negate need send/chain hooks outside. Not field-ignition (continuous banish + either-turn tribute-negate).

### `HERALD_OF_ULIMATENESS` (activated)
- path: `src_custom/activated_effects/herald_of_ulimateness.c`
- L12: Quick negate by sending Fairy from hand needs chain/negation hooks outside. Not field-ignition (either-turn discard Fairy → negate + destroy).

### `HERALD_OF_ULTIMATENESS` (activated)
- path: `src_custom/activated_effects/herald_of_ultimateness.c`
- L12: Quick negate by sending Fairy from hand needs chain/negation hooks outside. Not field-ignition (either-turn discard Fairy → negate + destroy).

### `HORUS_THE_BLACK_FLAME_DRAGON_LV8` (activated)
- path: `src_custom/activated_effects/horus_the_black_flame_dragon_lv8.c`
- L12: Spell immunity via IsImmuneToSpellEffectsOnField. either-turn Spell negate needs chain hook.

### `ILLUSION_OF_CHAOS` (activated)
- path: `src_custom/activated_effects/illusion_of_chaos.c`
- L135: Field bounce→SS DM negate FALSE. FromHand search only.

### `JAIN_TWILIGHTSWORN_GENERAL` (activated)
- path: `src_custom/activated_effects/jain_twilightsworn_general.c`
- L231: OPT banish 1 Lightsworn from hand/GY → weaken 1 face-up monster (EffectOpt). EP mill 2 via TryApplyTwilightswornEndPhase. other-Lightsworn- activated mill 2 needs chain hook.

### `LIGHTRAY_GEARFRIED` (activated)
- path: `src_custom/activated_effects/lightray_gearfried.c`
- L194: Quick negate S/T activation needs chain hooks. OPT banish Warrior GY → destroy 1 S/T.

### `LIGHT_AND_DARKNESS_DRAGON` (permanent)
- path: `src_custom/permanent_effects/light_and_darkness_dragon.c`
- L8: chain negate (−500 ATK/DEF) + GY destroy-all/SS need chain/GY hooks.

### `LORD_OF_THE_RED` (activated)
- path: `src_custom/activated_effects/lord_of_the_red.c`
- L115: either-turn chain on activation + S/T branch need chain hooks. OPT destroy 1 monster on the field.

### `LYLA_TWILIGHTSWORN_ENCHANTRESS` (activated)
- path: `src_custom/activated_effects/lyla_twilightsworn_enchantress.c`
- L207: OPT banish LS from hand/GY then destroy 1 face-up Spell/Trap (EffectOpt). EP mill 3 via TryApplyTwilightswornEndPhase. quick effect on Spell/Trap activation + mill 3 when other LS activates need chain hooks.

### `MASTERFLARE_HYPERION` (activated)
- path: `src_custom/activated_effects/masterflare_hyperion.c`
- L237: name/effect copy + Quick negate FALSE. OPT mill Agent/Sanctuary-mention, else OPT banish Fairy → destroy 1.

### `NATURIA_BEAST` (activated)
- path: `src_custom/activated_effects/naturia_beast.c`
- L12: Quick Effect spell negate + mill 2 need chain/negation hooks outside this file. Not field-ignition.

### `POWER_TOOL_BRAVER_DRAGON` (activated)
- path: `src_custom/activated_effects/power_tool_braver_dragon.c`
- L99: SS equip Equip Spells from Deck/GY hard; send-equip negate FALSE. OPT change battle position of 1 monster.

### `RYKO_TWILIGHTSWORN_FIGHTER` (activated)
- path: `src_custom/activated_effects/ryko_twilightsworn_fighter.c`
- L204: NS mill 3 stand-in for other-LS effect→mill; upgrade: chain hook.
- L220: NS mill 3 stand-in for other-LS effect→mill; upgrade: chain hook.

### `SILENT_SWORDSMAN` (activated)
- path: `src_custom/activated_effects/silent_swordsman.c`
- L133: Standby +500 via TryApplySilentSwordsmanStandby; OPT tempStage/destroy Spell unchanged. Quick Spell negate needs chain hook.

### `SILENT_SWORDSMAN_LV3` (activated)
- path: `src_custom/activated_effects/silent_swordsman_lv3.c`
- L70: Spell-target negate via IsImmuneToHarmfulTargetedEffectsOnField; Standby send self → SS LV5 wired below. summon/flip turn gate needs hooks.

### `SILENT_SWORDSMAN_ZERO` (activated)
- path: `src_custom/activated_effects/silent_swordsman_zero.c`
- L46: Standby Level/ATK via TryApplySilentSwordsmanZeroStandby; OPT +1 Level/+1 tempStage unchanged. Sarcophagus negate needs chain hook.

### `STARDUST_DRAGON` (activated)
- path: `src_custom/activated_effects/stardust_dragon.c`
- L12: Quick Effect tribute-negate-destroy + End Phase GY SS need chain and EP hooks outside this file. Not field-ignition.
