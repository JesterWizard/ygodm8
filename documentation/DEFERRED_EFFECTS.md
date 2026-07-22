# Deferred Effects Backlog

Auto-generated living list of **engine gaps** still called out in effect-file comments (plain notes after `Ceiling:`/`ponytail:` soft-clears).
Use this to pick an engine surface and batch the cards that wait on it.
Stubs: [`STUB_EFFECTS.md`](STUB_EFFECTS.md). Ceiling markers: [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md). Migration: [`effect-data-system.md`](effect-data-system.md).

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials + deferred
```

**Last updated:** 2026-07-22 21:51 UTC  
**Files with deferred notes:** `307`  
**Notes tagged:** `355`

## Suggested tackle order

Difficulty order (easiest first) within the current surface work:

1. **Already-wired comment clears** — notes that only restate live hooks (Honest MP return, Dynatag/Dominance battle Apply*, Earfon PickZone).
2. **Single-target PickZone / trunk pick** — Dystopia on-SS GY pick, Chicken Game L/R+A 3-way.
3. **Sequential PickZone** — Brionac bounce-N, Gungnir destroy-2, Double Cyclone.
4. **OnSummon residuals** — Empress / Desire / Marine Dolphin / Sagittarii draw.
5. **OnBattleDestroy** — bump `EFFECT_EVENT_MAX_SUBSCRIBERS` first (23/24 full), then Dreamer timing / Vassal / Lantron / Turbo Synchron.
6. **Hard UI** — multi-select (Amulet/Magnolia), look+reorder (Dominance), reveal excavate (Smartfon/Telefon), DeckMenu+PickZone crash (Athena/Dark Armed).
7. **Post-battle softlocks** — Core / Ice Edge / Sunrise (needs main-loop queue).
8. **Hard deferred** — `chain.Negate`, Extra Deck / Pendulum, `gate.SendCost`, equip API (Armory Arm), win-on-summon (Holactie).

Tag fan-out reminder: `ui.Choice` / `event.OnSummon` / `event.OnDestroy` / `gate.Tribute` before Extra Deck / full chain.

## Counts by missing surface

| Tag | Notes | Cards | Suggested phase |
|-----|------:|------:|-----------------|
| `other` | 81 | 73 | triage |
| `extra.XyzLinkSynchro` | 58 | 55 | later / Extra Deck |
| `gate.Tribute` | 40 | 37 | 2–3 |
| `chain.Negate` | 39 | 36 | later / chain |
| `op.Search` | 21 | 21 | 1 |
| `ui.Choice` | 18 | 13 | 2 |
| `event.OnSummon` | 14 | 14 | 3 |
| `event.OnStandby` | 13 | 13 | 3 (OPT / turn flags) |
| `gate.SendCost` | 13 | 13 | 3 (send-as-cost) |
| `op.BanishTimed` | 11 | 11 | 1–3 |
| `event.OnBattleDestroy` | 10 | 10 | 3 |
| `battle.ExtraAttack` | 7 | 6 | 1–3 (unk4 mark) |
| `event.OnDestroy` | 7 | 7 | 3 |
| `battle.AttackRedirect` | 6 | 6 | 3 (battle targeting) |
| `stat.Continuous` | 6 | 6 | 1–3 |
| `event.GyIgnition` | 5 | 5 | 3 |
| `event.OnFusionSummon` | 3 | 3 | 3 (fusion callback) |
| `event.OnLpGain` | 2 | 2 | later / LP event |
| `event.OnDamageCalc` | 1 | 1 | 3 |
| **total** | **355** | **307** | |

## `gate.SendCost` (13 notes)

### `ATLANTEAN_DRAGOONS` (activated)
- path: `src_custom/activated_effects/atlantean_dragoons.c`
- L136: Lv3- Sea Serpent direct via AtlanteanDragoons_CanSeaSerpentAttackDirectly. sent-for-WATER-effect search needs send hook. OPT add 1 Sea Serpent except self from Deck.

### `ATLANTEAN_HEAVY_INFANTRY` (activated)
- path: `src_custom/activated_effects/atlantean_heavy_infantry.c`
- L111: extra Normal Summon Sea Serpent + sent-for-WATER destroy need summon/send hooks. OPT destroy 1 Set Spell/Trap.

### `ATLANTEAN_MARKSMAN` (activated)
- path: `src_custom/activated_effects/atlantean_marksman.c`
- L148: Battle-damage Deck SS via ApplyAtlanteanMarksmanBattleEffect. sent-for-WATER destroy Set S/T needs send hook.

### `CURIOUS_THE_LIGHTSWORN_DOMINION` (activated)
- path: `src_custom/activated_effects/curious_the_lightsworn_dominion.c`
- L145: Leave-field GY add via CuriousTheLightswornDominion_EnsureInit. Link Summon mill + mill-cascade need summon/send hooks. OPT mill 1 from Deck below.

### `EL_SHADDOLL_MESHAHRAIL` (activated)
- path: `src_custom/activated_effects/el_shaddoll_meshahrail.c`
- L75: OPT pay 800 → add 1 Shaddoll or Void S/T from Deck (EffectOpt). unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks.

### `EVIL_HERO_NEOS_LORD` (activated)
- path: `src_custom/activated_effects/evil_hero_neos_lord.c`
- L185: On-SS take-control via TryEvilHeroNeosLordOnMonsterPlacement (EffectOpt). indestructible + opp-GY-sent take-control need continuous/send hooks. Field OPT take control of 1 face-up opp (EffectOpt; ignition stand-in).

### `GRAVEKEEPERS_AMBUSHER` (activated)
- path: `src_custom/activated_effects/gravekeepers_ambusher.c`
- L146: flip trigger + Necrovalley search need flip/send hooks. OPT put 1 opponent GY card on bottom of their Deck.

### `HELSHADDOLL_HOLLOW` (activated)
- path: `src_custom/activated_effects/helshaddoll_hollow.c`
- L109: FLIP Extra mill + GY attribute mill need flip/send hooks. OPT banish 1 face-up opp monster.

### `NEHSHADDOLL_GENIUS` (activated)
- path: `src_custom/activated_effects/nehshaddoll_genius.c`
- L110: FLIP Shaddoll unaffected + sent-by-effect branches need flip/send hooks. OPT negate 1 face-up Effect Monster (unk4).

### `QADSHADDOLL_KEIOS` (activated)
- path: `src_custom/activated_effects/qadshaddoll_keios.c`
- L50: FLIP vs sent-by-effect exclusivity + mill ATK gain need flip/send hooks. OPT SS 1 Shaddoll from hand face-up DEF.

### `REESHADDOLL_WENDI` (activated)
- path: `src_custom/activated_effects/reeshaddoll_wendi.c`
- L59: FLIP vs sent-by-effect face-down DEF branches need flip/send hooks. OPT SS 1 other Shaddoll from Deck face-up DEF.

### `REESHADDOLL_WENDIKURUHU` (activated)
- path: `src_custom/activated_effects/reeshaddoll_wendikuruhu.c`
- L73: Quick face-up→face-down follow-up + GY Shaddoll add need flip/send hooks. OPT flip all face-down monsters face-up DEF.

### `SHADDOLL_HOUND` (activated)
- path: `src_custom/activated_effects/shaddoll_hound.c`
- L93: FLIP vs sent-by-effect battle-position branch need flip/send hooks. OPT add 1 Shaddoll from GY to hand.

## `battle.AttackRedirect` (6 notes)

### `AMAZONESS_PET_LIGER_KING` (activated)
- path: `src_custom/activated_effects/amazoness_pet_liger_king.c`
- L191: OPT destroy Amazoness → SS Warrior GY via Activate. attack redirect FALSE.

### `DECOY_DRAGON` (activated)
- path: `src_custom/activated_effects/decoy_dragon.c`
- L182: Attack-target redirect needs battle targeting hook. OPT SS Lv7+ Dragon from GY once via EffectOpt when legal.

### `EVIL_HERO_MALICIOUS_FIEND` (permanent)
- path: `src_custom/permanent_effects/evil_hero_malicious_fiend.c`
- L44: Pierce via ApplySimplePiercersBattleEffect; forced attack via EvilHeroMaliciousFiend_GetForcedAttackTarget + sForcedAttackRedirects.

### `HARPIE_CONDUCTOR` (activated)
- path: `src_custom/activated_effects/harpie_conductor.c`
- L231: protect destroy redirect needs destroy-sub hook.

### `MORPHTRONIC_SLINGEN` (activated)
- path: `src_custom/activated_effects/morphtronic_slingen.c`
- L162: DEF destroy-other-Morphtronic substitute needs destroy redirect hook outside. ATK OPT tribute 1 other Morphtronic → destroy 1 field card (EffectOpt).

### `SOUL_ABSORBING_BONE_TOWER` (activated)
- path: `src_custom/activated_effects/soul_absorbing_bone_tower.c`
- L91: Other-Zombie SS mill via TrySoulAbsorbingBoneTowerOnOtherZombieSummon. Attack redirect while another Zombie present needs battle hooks. Not field-ignition.

## `extra.XyzLinkSynchro` (58 notes)

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
- L198: Quick on S/T activation + Synchro/name hooks missing. OPT bounce 1 opp card or your Harpie to hand (EffectOpt).

### `CYBER_SLASH_HARPY_LADY` (activated)
- path: `src_custom/activated_effects/cyber_slash_harpy_lady.c`
- L198: Quick on S/T activation + Synchro/name hooks missing. OPT bounce 1 opp card or your Harpie to hand (EffectOpt).

### `DESTINY_HERO_DUSKTOPIA` (activated)
- path: `src_custom/activated_effects/destiny_hero_dusktopia.c`
- L46: Battle protect + no battle damage via DestinyHeroDusktopia_*; EP clear via TryClearDestinyHeroDusktopiaProtectionEndPhase. Fusion on Summon need fusion hook (Extra Deck fusion from hand/field).

### `DIVINER_OF_THE_HERALD` (activated)
- path: `src_custom/activated_effects/diviner_of_the_herald.c`
- L84: Extra Deck Fairy mill skipped.

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
- L8: Direct attack via HarpiesPetPhantasmalDragon_CanAttackDirectly. Harpie protect + End Phase detach need battle/xyz hooks.

### `INSTANT_CONTACT` (spell)
- path: `src_custom/spell_effects/instant_contact.c`
- L153: Extra Deck off: offer matching Fusion recipe results by id.

### `INSTANT_FUSION` (spell)
- path: `src_custom/spell_effects/instant_fusion.c`
- L130: Extra Deck off: offer Level ≤5 Fusion recipe results by id.

### `LEVEL_EATER` (activated)
- path: `src_custom/activated_effects/level_eater.c`
- L122: no zone Level-mod field (level is ROM-only via gCardData_NEW). SS self from GY; upgrade: TempLevel overlay on target.

### `LEVIAIR_THE_SEA_DRAGON` (activated)
- path: `src_custom/activated_effects/leviair_the_sea_dragon.c`
- L107: No Xyz detach cost; OPT SS banished Lv≤4 stand-in when RFP enabled. Materials not checked; overlay detach before SS not wired.

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
- L107: tempStage unit is ~500 ATK, not printed +100; upgrade: exact overlay.

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

## `event.OnBattleDestroy` (10 notes)

### `AMAZONESS_HOT_SPRING` (trap)
- path: `src_custom/trap_effects/amazoness_hot_spring.c`
- L45: On activate: add 1 Amazoness from Deck to hand. Pendulum Zone place + battle-damage gain LP OPT need hooks.

### `ARMORY_ARM` (activated)
- path: `src_custom/activated_effects/armory_arm.c`
- L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. FALSE.

### `BEAST_MACHINE_KING_BARBAROS_UR` (activated)
- path: `src_custom/activated_effects/beast_machine_king_barbaros_ur.c`
- L164: Opp takes no battle damage via ApplyBeastMachineKingBarbarosUrNoOppBattleDamage. multi-zone banish picker not wired; FromHand requires both types reachable.

### `DESTINY_HERO_DREAMER` (activated)
- path: `src_custom/activated_effects/destiny_hero_dreamer.c`
- L128: Battle protect via DestinyHeroDreamer_PreventsBattleDestroy. Leave-banish via DestinyHeroDreamer_EnsureInit (unk4 mark on GY SS). True damage-calc GY SS timing needs battle hook.

### `GRAVEKEEPERS_VASSAL` (activated)
- path: `src_custom/activated_effects/gravekeepers_vassal.c`
- L12: Battle damage as effect damage needs battle-damage type gate outside this file. Not field-ignition.

### `MAJESTY_HYPERION` (activated)
- path: `src_custom/activated_effects/majesty_hyperion.c`
- L366: Fairy battle-damage share via ApplyMajestyHyperionBattleDamageShare. OPT banish Fairy hand/GY → destroy 1 card. FromHand banish Agent → SS.

### `MORPHTRONIC_LANTRON` (activated)
- path: `src_custom/activated_effects/morphtronic_lantron.c`
- L97: DEF destroy → no battle damage via ApplyMorphtronicLantronNoBattleDamage. ATK effect-damage redirect needs effect-damage hook outside. Not field-ignition.

### `NEO_BLUE_EYES_ULTIMATE_DRAGON` (activated)
- path: `src_custom/activated_effects/neo_blue_eyes_ultimate_dragon.c`
- L79: Damage Step / Fusion-Summon / protect-negate FALSE. OPT send BE Fusion from Deck → unk4 extra-attack via usage below.

### `TIMAEUS_THE_KNIGHT_OF_DESTINY` (activated)
- path: `src_custom/activated_effects/timaeus_the_knight_of_destiny.c`
- L53: unaffected + once-per-battle damage calc FALSE. OPT set ATK/DEF ≈ highest field ATK via tempStage.

### `TURBO_SYNCHRON` (activated)
- path: `src_custom/activated_effects/turbo_synchron.c`
- L12: Attack-target DEF change + battle-damage SS from hand need battle hooks outside this file. Not field-ignition.

## `event.OnDamageCalc` (1 notes)

### `TIMEAEUS_THE_UNITED_MAGICAL_DRAGON` (permanent)
- path: `src_custom/permanent_effects/timeaeus_the_united_magical_dragon.c`
- L121: unaffected-after-SS + battle ATK boost need continuous/battle hooks.

## `event.OnDestroy` (7 notes)

### `DEEP_EYES_WHITE_DRAGON` (permanent)
- path: `src_custom/permanent_effects/deep_eyes_white_dragon.c`
- L98: Blue-Eyes destroy hand-SS + burn need GY/destroy hooks; on-summon ATK only.

### `GATE_GUARDIANS_COMBINED` (activated)
- path: `src_custom/activated_effects/gate_guardians_combined.c`
- L102: negate-on-target + leave-field SS FALSE. OPT destroy 1 opp card (negate stand-in).

### `MASTER_OF_CHAOS` (activated)
- path: `src_custom/activated_effects/master_of_chaos.c`
- L204: Fusion SS trigger + destroyed GY Spell add need summon/destroy hooks. OPT SS LIGHT/DARK from GY, else tribute LIGHT+DARK → banish.

### `POWER_TOOL_DRAGON` (activated)
- path: `src_custom/activated_effects/power_tool_dragon.c`
- L55: reveal-3 opp-picks + equip destruction replace need reveal/destroy hooks. OPT add first Equip Spell from Deck.

### `SPELL_CHRONICLE` (spell)
- path: `src_custom/spell_effects/spell_chronicle.c`
- L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. activate discard+banish 5 only; unk4 counter slot unused.

### `THEINEN_THE_GREAT_SPHINX` (activated)
- path: `src_custom/activated_effects/theinen_the_great_sphinx.c`
- L39: Andro+Teleia destroy SS from hand/Deck needs destroy hook. OPT pay 500 → +7 tempStage (~3000 ATK).

### `THE_AGENT_OF_DESTRUCTION_VENUS` (activated)
- path: `src_custom/activated_effects/the_agent_of_destruction_venus.c`
- L192: leave-field Deck bottom for Shine Balls needs leave hook. OPT pay 500×N → SS N Mystical Shine Ball from banished/GY.

## `event.OnSummon` (14 notes)

### `AMAZONESS_AUGUSTA` (activated)
- path: `src_custom/activated_effects/amazoness_augusta.c`
- L154: Continuous protect + Fusion Summon trigger only — not ignition.

### `ANCIENT_GEAR_KNIGHT` (activated)
- path: `src_custom/activated_effects/ancient_gear_knight.c`
- L12: Attack S/T lock live via AncientGear_AttackerBlocksOppSpellTrap. Gemini Normal Monster treatment need summon hook.

### `APPRENTICE_ILLUSION_MAGICIAN` (activated)
- path: `src_custom/activated_effects/apprentice_illusion_magician.c`
- L162: On-NS/SS search via TryApprenticeIllusionMagicianOnMonsterPlacement (EffectOpt). OPT add Dark Magician from Deck (shares EffectOpt with on-summon). hand/field send +2000 Quick need damage hooks.

### `ARCANA_FORCE_III_THE_EMPRESS` (permanent)
- path: `src_custom/permanent_effects/arcana_force_iii_the_empress.c`
- L48: Opp Normal Summon SS/discard triggers need summon hooks; unk4 only.

### `DARKLORD_DESIRE` (activated)
- path: `src_custom/activated_effects/darklord_desire.c`
- L118: OPT -1000 ATK (tempStage) → send 1 opp monster to GY (EffectOpt). Fairy-only Tribute Summon + cannot SS need summon hooks.

### `DRAGON_SPIRIT_OF_WHITE` (permanent)
- path: `src_custom/permanent_effects/dragon_spirit_of_white.c`
- L59: Quick Tribute → SS Blue-Eyes from hand needs tribute/summon hooks.

### `EVIL_HERO_INFERNAL_RIDER` (activated)
- path: `src_custom/activated_effects/evil_hero_infernal_rider.c`
- L268: On-summon add Dark Fusion via TryEvilHeroInfernalRiderOnMonsterPlacement (EffectOpt). OPT banish self+4 GY → Set Super Poly. HERO lock need SS gates.

### `GLADIATOR_BEAST_SAGITTARII` (activated)
- path: `src_custom/activated_effects/gladiator_beast_sagittarii.c`
- L111: End-of-BP + battled via GladiatorBeast_CanActivateTagOutEffect. OPT shuffle self into Deck then SS another Gladiator Beast from Deck. Residual: discard-GB draw 2 on GB-SS need summon hooks.

### `HOLACTIE_THE_CREATOR_OF_LIGHT` (activated)
- path: `src_custom/activated_effects/holactie_the_creator_of_light.c`
- L64: SS-this-card-wins-Duel needs win-on-summon hook; no duel_helpers win API. Not field-ignition activatable; use FromHand tribute path.

### `MAGICIAN_OF_DARK_ILLUSION` (permanent)
- path: `src_custom/permanent_effects/magician_of_dark_illusion.c`
- L78: opp-turn hand SS + own S/T SS need chain hooks; on-summon GY SS only.

### `NEO_SPACIAN_MARINE_DOLPHIN` (activated)
- path: `src_custom/activated_effects/neo_spacian_marine_dolphin.c`
- L79: treated-as Aqua Dolphin name + NEX-only SS need continuous/summon hooks.

### `QUINTET_MAGICIAN` (activated)
- path: `src_custom/activated_effects/quintet_magician.c`
- L114: On-summon wipe via TryQuintetMagicianOnMonsterPlacement. Untributable/undestroyable need continuous hooks. OPT destroy all opp cards (ignition).

### `SHADDOLL_SCHISM` (trap)
- path: `src_custom/trap_effects/shaddoll_schism.c`
- L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker; banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.

### `TIMEAUS_THE_UNITED_DRAGON` (activated)
- path: `src_custom/activated_effects/timeaus_the_united_dragon.c`
- L147: Main Phase Fusion Summon needs fusion UI hook. SS from hand via send cost uses FromHand path.

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

## `chain.Negate` (39 notes)

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

## `gate.Tribute` (40 notes)

### `ALECTOR_SOVEREIGN_OF_BIRDS` (activated)
- path: `src_custom/activated_effects/alector_sovereign_of_birds.c`
- L168: Hand SS when opp has 2+ same Attribute uses FromHand path.

### `AMAZONESS_SPIRITUALIST` (activated)
- path: `src_custom/activated_effects/amazoness_spiritualist.c`
- L104: Field OPT add Polymerization from Deck. hand/GY bounce→SS + ED lock need GY/ED hooks.

### `ANCIENT_GEAR_GADJILTRON_CHIMERA` (activated)
- path: `src_custom/activated_effects/ancient_gear_gadjiltron_chimera.c`
- L12: Green/Red/Yellow Gadget tribute branches need summon/tribute hooks. Not ignition-activatable here.

### `ANCIENT_GEAR_STATUE` (activated)
- path: `src_custom/activated_effects/ancient_gear_statue.c`
- L112: Tribute self → SS AG Golem / mentions-Golem from hand/Deck (OPT via EffectOpt). FromHand SS when opp has more monsters — no OPT tracking.

### `ARCANA_FORCE_VI_THE_LOVERS` (permanent)
- path: `src_custom/permanent_effects/arcana_force_vi_the_lovers.c`
- L48: Tribute engine not wired — unk4 marks double-tribute / no-tribute only.

### `BEAST_KING_BARBAROS` (activated)
- path: `src_custom/activated_effects/beast_king_barbaros.c`
- L114: No-tribute 1900 ATK via BeastKingBarbaros_ApplyDynamicZoneStats + tribute hook. OPT stand-in for 3-Tribute destroy.

### `DESTINY_HERO_DOOM_OVERLORD` (permanent)
- path: `src_custom/permanent_effects/destiny_hero_doom_overlord.c`
- L327: Banish-until-Standby = permanent banish; DARK HERO SS lock not wired.

### `DIVINER_OF_THE_HERALD` (activated)
- path: `src_custom/activated_effects/diviner_of_the_herald.c`
- L105: On-NS/SS mill via TryDivinerOfTheHeraldOnMonsterPlacement (EffectOpt). tribute SS Fairy needs tribute hooks. OPT send 1 Fairy from Deck to GY (+unkTwo Level stand-in until EP clear).

### `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated)
- path: `src_custom/activated_effects/elemental_hero_shining_neos_wingman.c`
- L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. OPT destroy opp cards up to different Attributes.

### `EL_SHADDOLL_ANOYATYLLIS` (permanent)
- path: `src_custom/permanent_effects/el_shaddoll_anoyatyllis.c`
- L159: Hand/GY SS lock via ElShaddollAnoyatyllis_BlocksHandOrGySpecialSummon.

### `EVIL_HERO_TOXIC_BUBBLE` (activated)
- path: `src_custom/activated_effects/evil_hero_toxic_bubble.c`
- L89: HERO-only SS lock this turn needs summon gate.

### `FLAME_RULER` (activated)
- path: `src_custom/activated_effects/flame_ruler.c`
- L12: Treat as 2 Tributes for FIRE Tribute Summon needs tribute-cost LynJump outside this file. Not field-ignition.

### `FOG_KING` (activated)
- path: `src_custom/activated_effects/fog_king.c`
- L12: Tribute-flex Normal Summon, ATK = tributed ATK, and global tribute lock need summon/tribute continuous hooks outside this file. Not field-ignition.

### `FUSILIER_DRAGON_THE_DUAL_MODE_BEAST` (activated)
- path: `src_custom/activated_effects/fusilier_dragon_the_dual_mode_beast.c`
- L12: NS without tribute + halved ATK/DEF needs summon tribute gate outside this file. Not field-ignition.

### `GAMECIAL_THE_SEA_TURTLE_KAIJU` (activated)
- path: `src_custom/activated_effects/gamecial_the_sea_turtle_kaiju.c`
- L68: SS to opp field + Quick remove Kaiju Counter FALSE. FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju).

### `GRAVEKEEPERS_CHIEF` (activated)
- path: `src_custom/activated_effects/gravekeepers_chief.c`
- L186: Tribute Summon trigger, once-only control, and Necrovalley GY immunity need summon/continuous hooks. OPT SS GK from GY.

### `GRAVEKEEPERS_ORACLE` (activated)
- path: `src_custom/activated_effects/gravekeepers_oracle.c`
- L93: Tribute Summon sequence (destroy/flip/ATK) FALSE. OPT destroy up to 2 cards on opp field.

### `HARPIE_LADY_ELEGANCE` (trap)
- path: `src_custom/trap_effects/harpie_lady_elegance.c`
- L47: Shuffle Sisters into Deck, then SS up to 3 different Harpies from hand/Deck/GY. WIND-only SS lock this turn via HarpieLadyElegance_MarkWindOnlyLock. Destroy → add Harpie from Deck via aroma_lp_gain.c (AromaLpGain_EnsureI

### `JUDGMENT_THE_DRAGON_OF_HEAVEN` (activated)
- path: `src_custom/activated_effects/judgment_the_dragon_of_heaven.c`
- L108: 4+ GY Tuners gate + Dragon-only SS lock need GY/SS hooks. EP mill 4 via TryApplyJudgmentEndPhase. OPT pay half LP → destroy all other field cards.

### `LEKUNGA` (activated)
- path: `src_custom/activated_effects/lekunga.c`
- L12: No Lekunga Token card id — MOON_TOKEN stand-in. Wrong Type/Attribute/stats (Fairy/LIGHT 0/0 vs Plant/WATER 700/700); add LEKUNGA_TOKEN card data + art, then swap this define.

### `LEVEL_EATER` (activated)
- path: `src_custom/activated_effects/level_eater.c`
- L178: GY ignition via CanActivateLevelEaterGy / gy_ignition table. cannot-be-Tributed-except-for-Tribute-Summon needs tribute hooks.

### `MAGICIANS_ROD` (permanent)
- path: `src_custom/permanent_effects/magicians_rod.c`
- L138: GY tribute Spellcaster → add this needs opp-turn quick hook.

### `MASTER_PEACE_THE_TRUE_DRACOSLAYING_KING` (activated)
- path: `src_custom/activated_effects/master_peace_the_true_dracoslaying_king.c`
- L111: Tribute Continuous S/T + unaffected-by-type FALSE. OPT banish 1 other field card (Quick destroy stand-in).

### `NEO_SPACE_CONNECTOR` (activated)
- path: `src_custom/activated_effects/neo_space_connector.c`
- L61: on-Normal-Summon trigger + tribute-bounce second effect need summon/tribute hooks. OPT SS Neo-Spacian or Neos from Deck DEF.

### `NIBIRU_THE_PRIMAL_BEING` (activated)
- path: `src_custom/activated_effects/nibiru_the_primal_being.c`
- L90: 5-summon gate + Primal Being Token to opp FALSE. FromHand wipe+SS if ≥5 face-up monsters on field.

### `PROTECTOR_OF_THE_AGENTS_MOON` (activated)
- path: `src_custom/activated_effects/protector_of_the_agents_moon.c`
- L252: dual PickZone needs scratch; auto first Fairy tribute.

### `REPTILIANNE_VASKII` (activated)
- path: `src_custom/activated_effects/reptilianne_vaskii.c`
- L191: only-SS-by-tribute + unique-on-field need summon/field hooks. OPT destroy 1 face-up opp monster.
- L233: multi-zone tribute picker not wired; auto-tribute first two 0 ATK.

### `SCAPEGOAT` (spell)
- path: `src_custom/spell_effects/scapegoat.c`
- L10: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. wrong Type/Attribute (Fairy/LIGHT vs Beast/EARTH); upgrade: add SHEEP_TOKEN card data + art, then swap this define.
- L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. best-effort lockMonster; upgrade: tribute validator excludes SCAPEGOAT_TOKEN_ID / token flag.

### `SIMORGH_BIRD_OF_ANCESTRY` (activated)
- path: `src_custom/activated_effects/simorgh_bird_of_ancestry.c`
- L110: WIND tribute-reduce continuous + hand-as-Normal Monster need summon/permanent hooks. OPT return up to 2 opp cards to hand.

### `THE_AGENT_OF_JUDGMENT_SATURN` (activated)
- path: `src_custom/activated_effects/the_agent_of_judgment_saturn.c`
- L39: skip Battle Phase this turn needs phase-lock hook. tribute self → burn LP difference when Sanctuary face-up and LP higher.

### `THE_AGENT_OF_LIFE_NEPTUNE` (activated)
- path: `src_custom/activated_effects/the_agent_of_life_neptune.c`
- L160: tribute-lock + banish search FALSE. FromHand discard self → SS Agent (or Hyperion if Sanctuary).

### `THE_LEGENDARY_EXODIA_INCARNATE` (activated)
- path: `src_custom/activated_effects/the_legendary_exodia_incarnate.c`
- L125: ATK gain / unaffected FALSE. OPT add Forbidden One from GY. FromHand tribute Forbidden One → SS.

### `THE_TYRANT_NEPTUNE` (permanent)
- path: `src_custom/permanent_effects/the_tyrant_neptune.c`
- L256: Only clear on FALSE. Never clear on TRUE — placement calls Set(TRUE) after tributes are already captured and must not wipe ATK/DEF / tribute ids.

### `TUALATIN` (activated)
- path: `src_custom/activated_effects/tualatin.c`
- L108: FromHand battle-wipe SS + Summon Attribute lock FALSE. OPT destroy all face-up monsters of first opp monster's Attribute.

### `TURBO_BOOSTER` (activated)
- path: `src_custom/activated_effects/turbo_booster.c`
- L101: destroy only monsters that battled your monsters this turn needs battle-tracking hook. OPT tribute self then destroy 1 opponent monster; SS-from-hand uses FromHand path.
- L138: no Normal Summon-this-turn flag in engine; allow hand SS anytime. Upgrade: gate on turn flag once duel state tracks Normal Summons.

### `VISION_HERO_FARIS` (activated)
- path: `src_custom/activated_effects/vision_hero_faris.c`
- L149: Continuous Trap place + ED HERO lock need place/ED hooks. OPT add 1 Vision HERO from Deck to hand (EffectOpt).

### `VISION_HERO_INCREASE` (activated)
- path: `src_custom/activated_effects/vision_hero_increase.c`
- L70: GY Continuous Trap place + tribute HERO SS-self FALSE. OPT SS Vision HERO Lv≤4 from Deck (ST-zone SS stand-in; EffectOpt).

## `event.OnStandby` (13 notes)

### `AMAZONESS_SCOUTS` (activated)
- path: `src_custom/activated_effects/amazoness_scouts.c`
- L79: Either-player quick timing not wired; once via usage on your turn only.

### `ANCIENT_GEAR_STATUE` (activated)
- path: `src_custom/activated_effects/ancient_gear_statue.c`
- L194: FromHand SS when opp has more monsters; once-per-turn not tracked.

### `DARK_STRIKE_FIGHTER` (activated)
- path: `src_custom/activated_effects/dark_strike_fighter.c`
- L127: Main Phase 1 gate not wired; allow once via usage any main phase.

### `DESPAIR_FROM_THE_DARK` (permanent)
- path: `src_custom/permanent_effects/despair_from_the_dark.c`
- L47: opp hand/Deck send by card effect not tracked — GY-top SS only.

### `DESTINY_HERO_CELESTIAL` (activated)
- path: `src_custom/activated_effects/destiny_hero_celestial.c`
- L60: Except-turn-sent not tracked; EffectOpt ≈ once/turn.

### `DESTINY_HERO_DENIER` (activated)
- path: `src_custom/activated_effects/destiny_hero_denier.c`
- L69: Once-per-duel ≈ EffectOpt (turn); duel-scoped latch not tracked.

### `EVIL_HERO_ADUSTED_GOLD` (activated)
- path: `src_custom/activated_effects/evil_hero_adusted_gold.c`
- L86: once-per-turn not tracked without turn hook.

### `EVIL_HERO_VICIOUS_CLAWS` (activated)
- path: `src_custom/activated_effects/evil_hero_vicious_claws.c`
- L121: Once-per-duel ≈ EffectOpt (turn); duel-scoped latch not tracked.

### `JENIS_LIGHTSWORN_MENDER` (permanent)
- path: `src_custom/permanent_effects/jenis_lightsworn_mender.c`
- L53: LS-effect mill source not tracked — any deck mill this turn stand-in. EP burn/heal via TryApplyJenisEndPhase.

### `RINYAN_LIGHTSWORN_ROGUE` (activated)
- path: `src_custom/activated_effects/rinyan_lightsworn_rogue.c`
- L41: FLIP trigger needs flip hook outside; once via usage if LS in GY.

### `RYKO_LIGHTSWORN_HUNTER` (activated)
- path: `src_custom/activated_effects/ryko_lightsworn_hunter.c`
- L107: FLIP trigger needs flip hook outside; once via usage.

### `THE_AGENT_OF_WISDOM_MERCURY` (activated)
- path: `src_custom/activated_effects/the_agent_of_wisdom_mercury.c`
- L20: Standby Phase empty-hand-last-EP check needs turn-end hook outside. Once via usage if hand empty (standby/end-phase gate not wired).

### `TORNADO_BIRD` (activated)
- path: `src_custom/activated_effects/tornado_bird.c`
- L85: FLIP trigger needs flip hook outside; once via usage.

## `event.GyIgnition` (5 notes)

### `DESTINY_HERO_DREADNOUGHT_SERVANT` (activated)
- path: `src_custom/activated_effects/destiny_hero_dreadnought_servant.c`
- L272: GY banish → opp Deck top on Lv8 D-HERO SS via TryDestinyHeroDreadnoughtServantOnMonsterPlacement. FromHand if control D-HERO or Field Spell → SS, destroy 1, add Poly.

### `POSEIDRA_THE_ATLANTEAN_DRAGON` (activated)
- path: `src_custom/activated_effects/poseidra_the_atlantean_dragon.c`
- L285: hand SS uses FromHand path. GY ignition via CanActivatePoseidraTheAtlanteanDragonGy.

### `THE_BLAZING_MARS` (activated)
- path: `src_custom/activated_effects/the_blazing_mars.c`
- L48: no multi-select GY banish + hand/GY activation path yet — banish 3 other monsters to Special Summon deferred until expanded GY targeting exists.

### `THUNDER_DRAGON_COLOSSUS` (permanent)
- path: `src_custom/permanent_effects/thunder_dragon_colossus.c`
- L8: opp search lock + battle/effect destroy→GY-banish need continuous/battle hooks.

### `THUNDER_DRAGON_TITAN` (activated)
- path: `src_custom/activated_effects/thunder_dragon_titan.c`
- L102: Thunder hand-effect trigger + GY-banish instead of destroy need chain/continuous hooks. OPT destroy 1 card on the field.

## `event.OnLpGain` (2 notes)

### `AROMAGE_ROSEMARY` (activated)
- path: `src_custom/activated_effects/aromage_rosemary.c`
- L127: LP-higher Plant attack → opp monster effects locked need permanent/battle hooks. LP-gain position change via aroma_lp_gain.c. OPT change 1 face-up battle position (EffectOpt).

### `DARKLORD_NURSE_REFICULE` (permanent)
- path: `src_custom/permanent_effects/darklord_nurse_reficule.c`
- L8: LP gain→damage redirect needs LP-change hook.

## `battle.ExtraAttack` (7 notes)

### `BLUE_EYES_TYRANT_DRAGON` (activated)
- path: `src_custom/activated_effects/blue_eyes_tyrant_dragon.c`
- L94: Trap immunity via IsImmuneToTrapEffectsOnField; multi-attack + battle-end Set need battle/permanent hooks. OPT Set 1 Trap from GY to backrow.

### `EVIL_HERO_INFERNAL_GAINER` (activated)
- path: `src_custom/activated_effects/evil_hero_infernal_gainer.c`
- L57: second Standby Phase GY return needs turn/Standby hook; unk4=2 extra attack via TryUnlockUnk4MarkedExtraAttack.
- L110: Main Phase 1 gate needs phase hook. Extra attack via TryUnlockUnk4MarkedExtraAttack when unk4=2; second Standby GY return needs Standby hook.

### `NEO_BLUE_EYES_ULTIMATE_DRAGON` (activated)
- path: `src_custom/activated_effects/neo_blue_eyes_ultimate_dragon.c`
- L104: real multi-attack needs battle hook; unk4=2 extra-attack stand-in.

### `TYRANT_BURST_DRAGON` (activated)
- path: `src_custom/activated_effects/tyrant_burst_dragon.c`
- L12: Multi-attack + equip-to-monster need battle/equip continuous hooks outside this file. Not field-ignition.

### `ULTIMATE_CONDUCTOR_TYRANNO` (activated)
- path: `src_custom/activated_effects/ultimate_conductor_tyranno.c`
- L194: multi-attack + DEF burn/send need battle hooks. OPT destroy 1 of your monsters → flip all opp face-up monsters face-down DEF.

### `ULTIMATE_TYRANNO` (activated)
- path: `src_custom/activated_effects/ultimate_tyranno.c`
- L12: Multi-attack + Tyranno-only battle phase gate need battle hooks outside this file. Not field-ignition.

## `stat.Continuous` (6 notes)

### `AMAZONESS_PET_LIGER` (activated)
- path: `src_custom/activated_effects/amazoness_pet_liger.c`
- L152: OPT stand-in for after-damage −800 + Amazoness attack lock. ATK via AmazonessPetLiger_ApplyDynamicZoneStats.

### `CYBER_ELTANIN` (activated)
- path: `src_custom/activated_effects/cyber_eltanin.c`
- L154: Continuous ATK/DEF via CyberEltanin_ApplyDynamicZoneStats; FromHand banish+SS path below.

### `EVIL_HERO_VICIOUS_CLAWS` (activated)
- path: `src_custom/activated_effects/evil_hero_vicious_claws.c`
- L178: GY destroy-revive via EvilHeroViciousClaws_EnsureInit. FromHand target HERO → SS DEF +300 ATK stand-in.

### `GANDORA_G_THE_DRAGON_OF_DESTRUCTION` (activated)
- path: `src_custom/activated_effects/gandora_g_the_dragon_of_destruction.c`
- L151: +300 ATK/banished needs permanent/banish count hook. OPT pay half LP → banish all other field → SS Lv≤7 Sarc mention.

### `RAINBOW_DARK_DRAGON` (activated)
- path: `src_custom/activated_effects/rainbow_dark_dragon.c`
- L265: hand SS by banishing 7 different DARK uses FromHand path. OPT banish other DARK you control/from GY → +500 ATK each (tempStage).

### `THE_AGENT_OF_MIRACLES_JUPITER` (activated)
- path: `src_custom/activated_effects/the_agent_of_miracles_jupiter.c`
- L132: +800 ATK until EP via ResetTempStagesForAllCards; Sanctuary RFG revive FALSE. OPT banish Agent from GY → +2 tempStage on LIGHT Fairy.

## `ui.Choice` (18 notes)

### `AMULET_DRAGON` (activated)
- path: `src_custom/activated_effects/amulet_dragon.c`
- L58: No multi-select GY UI — banish every Spell in both GYs (min.1 gate above).

### `AROMALILITH_MAGNOLIA` (activated)
- path: `src_custom/activated_effects/aromalilith_magnolia.c`
- L171: Auto-banish up to winds count (opp rows first); no multi-select UI.

### `ATHENA` (activated)
- path: `src_custom/activated_effects/athena.c`
- L363: Drop field-target cursor before GY deck menu — PickZone state + trunk view was crashing when the menu opened on confirm.

### `DARK_ARMED_DRAGON` (activated)
- path: `src_custom/activated_effects/dark_armed_dragon.c`
- L306: Cost: banish 1 DARK monster from own GY (auto-picks first found)
- L317: Auto-target. No GY picker (DeckMenu screen switch corrupts VRAM from inside monster effect handler) and no PickZone cursor state (200 conflicts with game loop after MonsterActionMenu case 4 returns). Picks the best field

### `DARK_MAGICIAN_OF_DESTRUCTION` (permanent)
- path: `src_custom/permanent_effects/dark_magician_of_destruction.c`
- L131: Deck-first add; DM preferred by scan order, no picker.

### `DESTINY_HERO_DOMINANCE` (activated)
- path: `src_custom/activated_effects/destiny_hero_dominance.c`
- L66: Look+reorder UI missing; RandRange shuffle of top N is stand-in.
- L89: OPT shuffle top 5 of your (else opp) Deck (look+reorder UI missing; RandRange stand-in). Battle draw/SS via ApplyDestinyHeroDominanceBattleEffects.

### `ELEMENTAL_HERO_CORE` (battle)
- path: `src_custom/battle_effects/elemental_hero_core.c`
- L206: Exclude Core before scanning — dest is the origin for PickZone validators.
- L292: Opponent turn: auto-destroy (PickZone softlocks in AI_Main).
- L339: Resolve only from post-battle sites (code_8043EF4 / AI_Main / etc.). Inline PickZone here is wiped by attack cleanup (gDuelCursor.state = 0) after pending is already consumed, softlocking the owner's turn.

### `ELEMENTAL_HERO_ICE_EDGE` (battle)
- path: `src_custom/battle_effects/elemental_hero_ice_edge.c`
- L202: Resolve only from post-battle sites (code_8043EF4 / AI_Main / etc.). Inline PickZone here is wiped by attack cleanup (gDuelCursor.state = 0).
- L237: Opponent turn: auto-destroy (PickZone softlocks in AI_Main).

### `ELEMENTAL_HERO_SUNRISE` (permanent)
- path: `src_custom/permanent_effects/elemental_hero_sunrise.c`
- L464: True timing is attack declaration; resolve post-battle so PickZone can run from the main loop (same pattern as Core). Opponent-turn textboxes corrupt field VRAM — auto-resolve silently.

### `MICHAEL_THE_ARCH_LIGHTSWORN` (activated)
- path: `src_custom/activated_effects/michael_the_arch_lightsworn.c`
- L60: Auto-shuffle up to MICHAEL_SHUFFLE_MAX other LS (no GY picker).

### `MORPHTRONIC_SMARTFON` (activated)
- path: `src_custom/activated_effects/morphtronic_smartfon.c`
- L229: ATK die excavate add; DEF GY add Morphtronic (EffectOpt). Reveal UI FALSE. FromHand: banish Morphtronic GY → SS.

### `MORPHTRONIC_TELEFON` (activated)
- path: `src_custom/activated_effects/morphtronic_telefon.c`
- L177: ATK die→LP+SS Morph Lv≤roll; DEF die excavate add (EffectOpt). Reveal UI FALSE.

### `OJAMA_KING` (activated)
- path: `src_custom/activated_effects/ojama_king.c`
- L54: PickZone for up to 3 empty zones + continuous lock gate. auto-lock first 3 empty opp MMZ via isLocked (ignored by FirstEmptyZoneInRow today — same as Ground Collapse).

## `op.Search` (21 notes)

### `ARCANA_FORCE_XV_THE_FIEND` (activated)
- path: `src_custom/activated_effects/arcana_force_xv_the_fiend.c`
- L214: Discard search + FromHand paths. OPT coin → destroy 1 monster or wipe field (EffectOpt).

### `DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE` (activated)
- path: `src_custom/activated_effects/dark_magician_girl_the_magicians_apprentice.c`
- L94: On-NS/SS search via TryDarkMagicianGirlTheMagiciansApprenticeOnMonsterPlacement. OPT add Shining Sarcophagus (shares EffectOpt). Name=DMG GY +300 mention FALSE.

### `DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE` (activated)
- path: `src_custom/activated_effects/dark_magician_girl_the_magician_s_apprentice.c`
- L94: On-NS/SS search via TryDarkMagicianGirlTheMagicianSApprenticeOnMonsterPlacement. OPT add Shining Sarcophagus (shares EffectOpt). Name=DMG GY +300 mention FALSE.

### `DESTINY_HERO_DREADNOUGHT_MASTER` (activated)
- path: `src_custom/activated_effects/destiny_hero_dreadnought_master.c`
- L118: On-SS add via TryDestinyHeroDreadnoughtMasterOnMonsterPlacement (EffectOpt). Cards-mentioning-D-HERO FALSE. OPT add up to 2 Destiny HERO from Deck (shares EffectOpt).

### `ELEMENTAL_HERO_SPIRIT_OF_NEOS` (activated)
- path: `src_custom/activated_effects/elemental_hero_spirit_of_neos.c`
- L225: Attack-hand SS FALSE. On-SS search via TryElementalHeroSpiritOfNeosOnMonsterPlacement (EffectOpt). OPT search Poly/E-HERO S/T (shares EffectOpt), else OPT shuffle self → SS Normal E-HERO.

### `ENLIGHTENMENT_DRAGON` (activated)
- path: `src_custom/activated_effects/enlightenment_dragon.c`
- L138: Extra Summon conditions + destroy-add banished FALSE. OPT pay 2000 → banish all other field+both GYs, else OPT mill 4. Separate OPTs share one MarkMonsterEffectUsed.

### `EVIL_HERO_ADUSTED_GOLD` (activated)
- path: `src_custom/activated_effects/evil_hero_adusted_gold.c`
- L63: cannot attack without Fusion Monster needs attack gate. Not field-ignition activatable; discard search uses FromHand path.

### `EVIL_HERO_DEAD_END_PRISON` (activated)
- path: `src_custom/activated_effects/evil_hero_dead_end_prison.c`
- L110: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE. OPT mill 1 HERO from Deck (EffectOpt).

### `GRAVEKEEPERS_SUPERNATURALIST` (activated)
- path: `src_custom/activated_effects/gravekeepers_supernaturalist.c`
- L57: material ATK gain + Necrovalley destroy protect + EP schedule FALSE. OPT add Gravekeeper or Necrovalley from Deck now (EP add stand-in).

### `GUARDIAN_DREADSCYTHE` (activated)
- path: `src_custom/activated_effects/guardian_dreadscythe.c`
- L170: summon lock + GY revive loop need summon/leave hooks. OPT equip/add Reaper Scythe from Deck.

### `HARPIE_HARPIST` (activated)
- path: `src_custom/activated_effects/harpie_harpist.c`
- L197: NS bounce via TryHarpieHarpistOnNormalSummon (EffectOpt). GY End Phase search (Lv4 WB ≤1500 ATK) needs EP hook. OPT bounce own WB + opp face-up (shares EffectOpt).

### `HUMID_WINDS` (trap)
- path: `src_custom/trap_effects/humid_winds.c`
- L89: On flip: try pay 1000 → search Aroma (one-shot stand-in for OPT ignition).

### `LIGHTSWORN_DRAGONLING` (activated)
- path: `src_custom/activated_effects/lightsworn_dragonling.c`
- L272: hand SS when Lightsworn in GY uses FromHand path. On-SS mill via TryLightswornDragonlingOnMonsterPlacement (EffectOpt). Leave → LIGHT Dragon 3000/2600 (or BEWD) via LightswornDragonling_EnsureInit. OPT send 1 other Light

### `LYLA_LIGHTSWORN_SORCERESS` (activated)
- path: `src_custom/activated_effects/lyla_lightsworn_sorceress.c`
- L124: EP mill via TryApplyLylaEndPhase; position-lock after OPT needs battle hook. OPT from face-up ATK → face-up DEF, destroy 1 opp S/T.

### `MORPHTRONIC_SCANNEN` (activated)
- path: `src_custom/activated_effects/morphtronic_scannen.c`
- L195: FromHand banish Morphtronic → SS. ATK/DEF OPT search modes (EffectOpt).

### `NECROFACE` (activated)
- path: `src_custom/activated_effects/necroface.c`
- L86: Normal Summon shuffle + banish-mill branches need summon/banish hooks. OPT shuffle all banished into Decks + tempStage per card.

### `PUNISHMENT_DRAGON` (activated)
- path: `src_custom/activated_effects/punishment_dragon.c`
- L192: Hand SS via 4+ banished LS uses FromHand path. OPT pay 1000 → shuffle all banished into Decks (EffectOpt). LS mill 4 needs effect-activation hook.

### `REPTILIANNE_GARDNA` (permanent)
- path: `src_custom/permanent_effects/reptilianne_gardna.c`
- L8: destroyed→search Reptilianne needs destroy-to-GY permanent hook.

### `RYKO_TWILIGHTSWORN_FIGHTER` (activated)
- path: `src_custom/activated_effects/ryko_twilightsworn_fighter.c`
- L220: NS mill via TryRykoTwilightswornFighterOnNormalSummon (other-LS stand-in). OPT banish LS hand/GY → banish 1 field (EffectOpt). EP mill via TryApplyTwilightswornEndPhase. flip trigger needs flip hook.

### `SPELL_CHRONICLE` (spell)
- path: `src_custom/spell_effects/spell_chronicle.c`
- L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished; cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.

### `TOHUSHADDOLL_GRYSTA` (activated)
- path: `src_custom/activated_effects/tohushaddoll_grysta.c`
- L22: FLIP copy + GY Fusion-by-banish need flip/GY hooks. OPT add Shaddoll Fusion from Deck.

## `op.BanishTimed` (11 notes)

### `BEAST_MACHINE_KING_BARBAROS_UR` (activated)
- path: `src_custom/activated_effects/beast_machine_king_barbaros_ur.c`
- L224: multi-zone banish picker not wired; require both types reachable.

### `CROSS_KEEPER` (activated)
- path: `src_custom/activated_effects/cross_keeper.c`
- L171: Fusion leave ≈ E-HERO Fusion SS while CK in GY; draw1 stand-in for banish→draw2→bottom. Upgrade: true SS trigger + banish cost.

### `CYBER_VALLEY` (activated)
- path: `src_custom/activated_effects/cyber_valley.c`
- L132: Attack-target banish + GY place-on-deck need battle/GY hooks. OPT banish self+1 face-up monster → draw 2; else banish self → draw 1 at end of Battle Phase via GladiatorBeast_InBattlePhase.

### `LEGENDARY_KNIGHT_CRITIAS` (activated)
- path: `src_custom/activated_effects/legendary_knight_critias.c`
- L99: Legend of Heart SS + when-attacked Set Trap from GY need summon/battle hooks. OPT banish 1 face-up Spell/Trap on the field.

### `LEGENDARY_KNIGHT_HERMOS` (activated)
- path: `src_custom/activated_effects/legendary_knight_hermos.c`
- L99: Legend of Heart SS + when-attacked GY name/effect copy need summon/battle hooks. OPT banish 1 face-up Spell/Trap.

### `LEGENDARY_KNIGHT_TIMAEUS` (activated)
- path: `src_custom/activated_effects/legendary_knight_timaeus.c`
- L99: Legend of Heart SS + attacked-set-Spell-from-GY need summon/battle hooks. OPT banish 1 face-up Spell/Trap on the field.

### `MAGICIANS_ROBE` (activated)
- path: `src_custom/activated_effects/magicians_robe.c`
- L56: Opp-turn quick + GY SS banish-on-leave need phase/GY hooks. Discard S/T from hand → SS DM from Deck via FromHand path.

### `NAELSHADDOLL_ARIEL` (activated)
- path: `src_custom/activated_effects/naelshaddoll_ariel.c`
- L72: FLIP SS banished Shaddoll + sent-by-effect branch need flip/RFP hooks. OPT banish up to 3 cards from either GY.

### `SPELL_CHRONICLE` (spell)
- path: `src_custom/spell_effects/spell_chronicle.c`
- L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn; briefly hits GY; upgrade: direct deck→RFG.

### `THE_EXECUTOR_OF_THE_UNDERWORLD_PLUTO` (activated)
- path: `src_custom/activated_effects/the_executor_of_the_underworld_pluto.c`
- L163: Quick via Sanctuary + GY add Sanctuary FALSE. OPT banish 1 monster from GY → flip 1 Effect Monster face-down DEF.

### `TIME_MAGIC_HAMMER` (activated)
- path: `src_custom/activated_effects/time_magic_hammer.c`
- L12: Hermos equip + battle-step dice banish need summon/equip/battle hooks outside this file. Not field-ignition.

## `other` (81 notes)

### `AMAZONESS_QUEEN` (activated)
- path: `src_custom/activated_effects/amazoness_queen.c`
- L67: Continuous battle protection — not ignition-activatable.

### `ANCIENT_FAIRY_DRAGON` (activated)
- path: `src_custom/activated_effects/ancient_fairy_dragon.c`
- L135: Cannot conduct Battle Phase stand-in (unk4 lock); true phase skip needs hook.

### `ANCIENT_GEAR` (activated)
- path: `src_custom/activated_effects/ancient_gear.c`
- L38: Printed SS is from hand — use FromHand path.

### `ANTI_SPELL_FRAGRANCE` (trap)
- path: `src_custom/trap_effects/anti_spell_fragrance.c`
- L43: Hand play / face-up field play without Set → blocked.

### `ARCANA_FORCE_0_THE_FOOL` (permanent)
- path: `src_custom/permanent_effects/arcana_force_0_the_fool.c`
- L56: Tails targeting immunity still needs target-hook; Heads battle protect is live.

### `ARCANA_FORCE_I_THE_MAGICIAN` (permanent)
- path: `src_custom/permanent_effects/arcana_force_i_the_magician.c`
- L68: Spell-trigger heads/tails not wired.

### `ARCANA_FORCE_THE_CHAOS_RULER` (permanent)
- path: `src_custom/permanent_effects/arcana_force_the_chaos_ruler.c`
- L198: Light Barrier opp-activation lock needs continuous field hook.

### `ARCANA_FORCE_V_THE_HIEROPHANT` (activated)
- path: `src_custom/activated_effects/arcana_force_v_the_hierophant.c`
- L87: OPT coin → SS 1 Arcana Force from Deck (EffectOpt). discard summon-lock + FromHand paths.
- L198: discard only; opp cannot respond to Arcana Summons needs turn flag hook.

### `ARCANA_FORCE_XVIII_THE_MOON` (permanent)
- path: `src_custom/permanent_effects/arcana_force_xviii_the_moon.c`
- L48: Standby Moon Token / End Phase give-control need turn hooks; unk4 only.

### `ARCANA_FORCE_XXI_THE_WORLD` (permanent)
- path: `src_custom/permanent_effects/arcana_force_xxi_the_world.c`
- L48: Skip-turn / opp GY-to-hand need turn hooks; unk4 marks coin only.

### `BLACK_WINGED_DRAGON` (activated)
- path: `src_custom/activated_effects/black_winged_dragon.c`
- L70: −700 ≈ −2 tempStage stand-in; counter/damage-redirect FALSE.
- L113: Damage redirect + Black Feather Counters + burn need damage hooks. OPT −2 tempStage on 1 face-up opp monster; ATK via ApplyBlackWingedDragonContinuousAtkToCardInfo.

### `BLUE_EYES_JET_DRAGON` (activated)
- path: `src_custom/activated_effects/blue_eyes_jet_dragon.c`
- L289: Battle/effect protect via BlueEyesJetDragon_Prevents* while BEWD on field/GY. BEWD/Alt destroy → SS Jet from hand via BlueEyesJetDragon_EnsureInit. Field OPT bounce 1; FromHand if BEWD field/GY → SS.

### `BLUE_EYES_SOLID_DRAGON` (activated)
- path: `src_custom/activated_effects/blue_eyes_solid_dragon.c`
- L49: Battle/effect protect via BlueEyesSolidDragon_Prevents*. Residual: summon Quick shuffle→SS BEWD + per-effect usage need hooks.

### `CANNONBALL_SPEAR_SHELLFISH` (permanent)
- path: `src_custom/permanent_effects/cannonball_spear_shellfish.c`
- L8: Continuous Umi spell-immunity via IsImmuneToSpellEffectsOnField — not ignition.

### `CHARM_OF_SHABTI` (activated)
- path: `src_custom/activated_effects/charm_of_shabti.c`
- L46: Printed effect is hand discard — use FromHand path.

### `CLEAR_VICE_DRAGON` (activated)
- path: `src_custom/activated_effects/clear_vice_dragon.c`
- L71: Battle ATK = 2× target via ApplyClearViceDragonDamageStepAtk. Clear World immunity + discard-to-save need continuous/destruction hooks.

### `DARKNESS_NEOSPHERE` (activated)
- path: `src_custom/activated_effects/darkness_neosphere.c`
- L87: Battle indestruct + trap bounce + attack-declare gate need battle/phase hooks outside this file. Not field-ignition; SS uses FromHand path.
- L113: Opp attack declare gate not wired; require 1 field + 1 hand Fiend.

### `DARK_HORUS` (activated)
- path: `src_custom/activated_effects/dark_horus.c`
- L100: After opp Main Phase Spell resolve trigger needs spell hook. OPT SS 1 Lv4 DARK from GY while face-up (EffectOpt).

### `DARK_MAGICIAN_THE_DRAGON_KNIGHT` (activated)
- path: `src_custom/activated_effects/dark_magician_the_dragon_knight.c`
- L63: Name=Dark Magician via DarkMagicianTheDragonKnight_TreatsNameAsDarkMagician + Duel_ZoneEffectCardId; S/T protect via DarkMagicianTheDragonKnight_ProtectsSpellTrap. Not field-ignition.

### `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS` (activated)
- path: `src_custom/activated_effects/dark_magician_the_magician_of_black_chaos.c`
- L33: Name=Dark Magician via DarkMagicianTheMagicianOfBlackChaos_TreatsNameAsDarkMagician + Duel_ZoneEffectCardId. Destroy-revive/Set via DarkMagicianDestroyRevive_EnsureInit. Not field-ignition; FromHand if Shining Sarcophagu

### `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC` (activated)
- path: `src_custom/activated_effects/dark_magician_the_magician_of_black_magic.c`
- L256: Name=Dark Magician via DarkMagicianTheMagicianOfBlackMagic_TreatsNameAsDarkMagician + Duel_ZoneEffectCardId. Destroy-revive/Set via DarkMagicianDestroyRevive_EnsureInit. Not field-ignition; FromHand if Shining Sarcophagu

### `DEEP_EYES_WHITE_DRAGON` (permanent)
- path: `src_custom/permanent_effects/deep_eyes_white_dragon.c`
- L121: first Dragon in GY stand-in for target picker.

### `DESTINY_END_DRAGOON` (activated)
- path: `src_custom/activated_effects/destiny_end_dragoon.c`
- L65: cannot conduct Battle Phase — unk4 lock stand-in. GY revive FALSE.
- L105: GY revive FALSE. OPT destroy 1 opp monster + burn its ATK + cannot BP (unk4).

### `DESTINY_HERO_BLADE_MASTER` (activated)
- path: `src_custom/activated_effects/destiny_hero_blade_master.c`
- L86: Printed effect is hand discard during opp Battle Phase — use FromHand path.

### `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated)
- path: `src_custom/activated_effects/destiny_hero_destroyer_phoenix_enforcer.c`
- L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. OPT destroy 1 you control + 1 other field card.

### `DESTINY_HERO_DIAMOND_DUDE` (activated)
- path: `src_custom/activated_effects/destiny_hero_diamond_dude.c`
- L57: Next-turn GY Normal Spell activation needs Main Phase hook.

### `DESTINY_HERO_DYSTOPIA` (activated)
- path: `src_custom/activated_effects/destiny_hero_dystopia.c`
- L257: On-SS burn via TryDestinyHeroDystopiaOnMonsterPlacement (EffectOpt). Quick destroy-if-ATK-changed needs ATK hooks. OPT pick Lv≤4 D-HERO in GY → burn its ATK.

### `ELEMENTAL_HERO_CHAOS_NEOS` (activated)
- path: `src_custom/activated_effects/elemental_hero_chaos_neos.c`
- L241: 3H Set-all needs set-from-deck hook; 2H/3H both shuffle all.

### `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated)
- path: `src_custom/activated_effects/elemental_hero_shining_neos_wingman.c`
- L177: multi-target picker not wired; auto-destroy highest-value opp cards.

### `EL_SHADDOLL_ANOYATYLLIS` (permanent)
- path: `src_custom/permanent_effects/el_shaddoll_anoyatyllis.c`
- L40: Monster ignition uses gMonEffect — allow those SS from hand/GY. Spell/Trap (and other non-mon) paths are blocked.

### `EVIL_HERO_MALICIOUS_BANE` (activated)
- path: `src_custom/activated_effects/evil_hero_malicious_bane.c`
- L75: destruction immunity + HERO-only attack gate need destroy/attack hooks. OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4.

### `EVIL_HERO_TOXIC_BUBBLE` (activated)
- path: `src_custom/activated_effects/evil_hero_toxic_bubble.c`
- L66: On-SS draw via TryEvilHeroToxicBubbleOnMonsterPlacement. Not field-ignition; SS-from-hand uses FromHand path.

### `FUSION_DESTINY` (spell)
- path: `src_custom/spell_effects/fusion_destiny.c`
- L33: Local recipes that list a Destiny HERO as material. incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous, DPE, Dusktopia need archetype / Level-gated wildcards not in fusion_recipes). Destiny End Dragoon only; 

### `GAGAGIGO_THE_RISEN` (activated)
- path: `src_custom/activated_effects/gagagigo_the_risen.c`
- L18: Unreachable while CanActivate returns FALSE.

### `GORZ_THE_EMISSARY_OF_DARKNESS` (activated)
- path: `src_custom/activated_effects/gorz_the_emissary_of_darkness.c`
- L34: damage-gate + Token FALSE. FromHand empty-field SS.

### `GRAVEKEEPERS_COMMANDANT` (activated)
- path: `src_custom/activated_effects/gravekeepers_commandant.c`
- L13: Printed effect is hand discard — use FromHand path.

### `GRAVEKEEPERS_GUARD` (activated)
- path: `src_custom/activated_effects/gravekeepers_guard.c`
- L85: FLIP trigger needs flip hook.

### `GRAVEKEEPERS_ORACLE` (activated)
- path: `src_custom/activated_effects/gravekeepers_oracle.c`
- L110: multi-target picker not wired; auto-destroy up to 2 opp cards.

### `GRAVEKEEPERS_SPY` (activated)
- path: `src_custom/activated_effects/gravekeepers_spy.c`
- L58: FLIP trigger needs flip hook.

### `GREAT_POSEIDON_BEETLE` (activated)
- path: `src_custom/activated_effects/great_poseidon_beetle.c`
- L12: Re-attack same target after surviving battle needs battle re-attack hook outside this file. Not field-ignition.

### `GRINDER_GOLEM` (permanent)
- path: `src_custom/permanent_effects/grinder_golem.c`
- L8: hand SS to opp field + Grinder Tokens + NS/Set lock need summon/token hooks.

### `HARPIE_CONDUCTOR` (activated)
- path: `src_custom/activated_effects/harpie_conductor.c`
- L55: No SS-origin flag; face-up/ATK stand-in for Special Summoned.
- L133: any other Harpie leave ≈ return-to-hand; upgrade: true bounce-origin flag.

### `HARPIE_QUEEN` (activated)
- path: `src_custom/activated_effects/harpie_queen.c`
- L13: Printed discard is hand — use FromHand path; name=Harpie Lady via HarpiePerfumer_TreatsNameAsHarpieLady + Duel_ZoneEffectCardId.

### `HORUS_THE_BLACK_FLAME_DRAGON_LV4` (permanent)
- path: `src_custom/permanent_effects/horus_the_black_flame_dragon_lv4.c`
- L8: Control lock needs continuous hook. EP send self → SS LV6 via TryApplyHorusEndPhase when this card destroyed a monster by battle.

### `KEEPER_OF_DRAGON_MAGIC` (activated)
- path: `src_custom/activated_effects/keeper_of_dragon_magic.c`
- L185: reveal Fusion Extra material-name SS FALSE; any GY face-down stand-in. OPT discard → add Poly/Fusion Normal; else OPT SS any from GY face-down DEF.

### `LEVIAIR_THE_SEA_DRAGON` (activated)
- path: `src_custom/activated_effects/leviair_the_sea_dragon.c`
- L62: No RemovedFromPlay_RemoveAt — shift RFP array in place after SS. Local mutate of gRemovedFromPlay; RemovedFromPlay_RemoveAt not wired.

### `LUMINA_TWILIGHTSWORN_SHAMAN` (activated)
- path: `src_custom/activated_effects/lumina_twilightsworn_shaman.c`
- L226: No RemovedFromPlay_RemoveAt — shift RFP array in place after SS.

### `MAGICAL_PLANT_MANDRAGOLA` (activated)
- path: `src_custom/activated_effects/magical_plant_mandragola.c`
- L12: FLIP place Spell Counters needs flip + counter storage outside this file. Not field-ignition.

### `MAGICIANS_ROBE` (activated)
- path: `src_custom/activated_effects/magicians_robe.c`
- L76: opponent's turn gate not wired.

### `MAGICIANS_SOULS` (activated)
- path: `src_custom/activated_effects/magicians_souls.c`
- L143: Continuous Spell placement + DM/DMG GY SS branch need placement/ GY hooks. OPT send 1–2 S/T from hand/field → draw that many.

### `MAJESTIC_MECH_GORYU` (activated)
- path: `src_custom/activated_effects/majestic_mech_goryu.c`
- L32: Pierce via ApplySimplePiercersBattleEffect; EP self-send via TryApplyMajesticMechGoryuEndPhase. Not ignition-activatable.

### `MAXX_C` (activated)
- path: `src_custom/activated_effects/maxx_c.c`
- L20: Printed effect sends from hand during either turn — use FromHand path.
- L55: draw-on-opponent-Special-Summon this turn not wired; upgrade: SS hook + simple turn flag when one exists.

### `MILLENNIUM_EYES_RESTRICT` (activated)
- path: `src_custom/activated_effects/millennium_eyes_restrict.c`
- L88: chain equip/absorb opp Effect Monster needs chain/control hooks. OPT destroy 1 opp monster.

### `MIRROR_FORCE_DRAGON` (activated)
- path: `src_custom/activated_effects/mirror_force_dragon.c`
- L12: when targeted for attack/effect trigger needs protection hook. Not ignition-activatable; upgrade: trigger destroy-all.

### `MORPHTRONIC_EARFON` (activated)
- path: `src_custom/activated_effects/morphtronic_earfon.c`
- L94: Equip 2-attacks FALSE. On-SS mark self as Tuner (unk4).
- L111: On-SS Tuner mark via TryMorphtronicEarfonOnMonsterPlacement. Equip 2-attacks FALSE. OPT mark face-up monster as Tuner (unk4 stand-in).

### `MORPHTRONIC_SCOPEN` (activated)
- path: `src_custom/activated_effects/morphtronic_scopen.c`
- L59: DEF Position → treat as Level 4 + EP destroy on ATK-mode SS need position/EP hooks outside. ATK Position OPT SS 1 Lv4 Morphtronic from hand (EffectOpt).

### `MORPHTRONIC_VACUUMEN` (activated)
- path: `src_custom/activated_effects/morphtronic_vacuumen.c`
- L25: Send Equip → burn + DEF equip-take-control need equip hooks. ATK Position OPT burn 500 (EffectOpt).

### `NITRO_WARRIOR` (activated)
- path: `src_custom/activated_effects/nitro_warrior.c`
- L96: Spell ATK gain + battle-after destroy trigger FALSE. OPT change 1 face-up DEF opp monster to ATK (battle-after stand-in).

### `OBLITERATE_BLAZE` (spell)
- path: `src_custom/spell_effects/obliterate_blaze.c`
- L68: Mark granted effects via unk4 bit — secondary pay-half / equip / pierce need hooks.

### `REPTILIANNE_SERVANT` (permanent)
- path: `src_custom/permanent_effects/reptilianne_servant.c`
- L118: Cannot-be-attacked via sAttackGates + ReptilianneServant_HasOtherFaceUpMonster; Reptile NS lock via ReptilianneServant_BlocksNormalSummonReptile. spell-target destroy needs continuous hook.

### `SCAPEGOAT` (spell)
- path: `src_custom/spell_effects/scapegoat.c`
- L74: LockMonsterCardsInRow also blocks Normal Set of monsters. cannot allow Set while blocking Summon without a menu hook that distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.

### `SHADDOLL_BEAST` (activated)
- path: `src_custom/activated_effects/shaddoll_beast.c`
- L20: FLIP draw2/discard1 and GY-sent draw1 share 1/turn exclusivity. OPT draw 1 stand-in for GY effect only; upgrade: flip + GY hooks.

### `SHADDOLL_FALCO` (activated)
- path: `src_custom/activated_effects/shaddoll_falco.c`
- L115: FLIP vs GY-sent exclusivity + SS-self-on-send need trigger hooks. OPT SS 1 other Shaddoll from GY face-down DEF.

### `SILENT_MAGICIAN_LV8` (activated)
- path: `src_custom/activated_effects/silent_magician_lv8.c`
- L23: Spell immunity via IsImmuneToSpellEffectsOnField and SilentMagicianLv8_PreventsDestroy; not ignition-activatable.

### `SILENT_SWORDSMAN_LV5` (activated)
- path: `src_custom/activated_effects/silent_swordsman_lv5.c`
- L70: Unaffected by opp Spell via IsImmuneToSpellEffectsOnField; OPT send self → SS LV7 wired below. Standby-after-direct-damage gate needs hook.

### `SILENT_SWORDSMAN_LV7` (activated)
- path: `src_custom/activated_effects/silent_swordsman_lv7.c`
- L11: Spell immunity via IsImmuneToSpellEffectsOnField; not ignition-activatable.

### `SPELL_GEAR` (spell)
- path: `src_custom/spell_effects/spell_gear.c`
- L155: "You can" — AI always summons when able; player path same (no skip UI). Optional SS offered as auto-yes when legal; cannot skip a legal hand/Deck AGG SS (skip UI unsupported). Upgrade: A/B confirm per location.

### `THE_AGENT_OF_DESTRUCTION_VENUS` (activated)
- path: `src_custom/activated_effects/the_agent_of_destruction_venus.c`
- L66: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.

### `THE_DARK_MAGICIANS` (permanent)
- path: `src_custom/permanent_effects/the_dark_magicians.c`
- L154: OPT draw on S/T activation needs chain/OPT hooks.
- L177: Deck-first SS order; hand/GY picker not wired.

### `ULTIMATE_OBEDIENT_FIEND` (activated)
- path: `src_custom/activated_effects/ultimate_obedient_fiend.c`
- L12: Solo-field + empty-hand attack restriction needs attack gate hook outside this file. Not field-ignition.

### `VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES` (permanent)
- path: `src_custom/permanent_effects/vennominaga_the_deity_of_poisonous_snakes.c`
- L54: S/T + monster immunity + 3-counter win need continuous/battle hooks.

### `VISION_HERO_GRAVITO` (activated)
- path: `src_custom/activated_effects/vision_hero_gravito.c`
- L65: no RemovedFromPlay_RemoveAt — shift RFP array in place after add. local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.

### `WARRIOR_OF_ATLANTIS` (activated)
- path: `src_custom/activated_effects/warrior_of_atlantis.c`
- L13: Printed effect is hand discard — use FromHand path.
