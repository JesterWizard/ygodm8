# Deferred Effects Backlog

Auto-generated living list of **engine gaps** still called out in effect-file comments (plain notes after `Ceiling:`/`ponytail:` soft-clears).
Use this to pick an engine surface and batch the cards that wait on it.
Stubs: [`STUB_EFFECTS.md`](STUB_EFFECTS.md). Ceiling markers: [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md). Migration: [`effect-data-system.md`](effect-data-system.md).

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials + deferred
```

**Last updated:** 2026-07-22 22:04 UTC  
**Files with deferred notes:** `150`  
**Notes tagged:** `157`

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
| `other` | 55 | 55 | triage |
| `gate.Tribute` | 22 | 20 | 2–3 |
| `extra.XyzLinkSynchro` | 21 | 21 | later / Extra Deck |
| `chain.Negate` | 14 | 14 | later / chain |
| `op.Search` | 10 | 10 | 1 |
| `gate.SendCost` | 7 | 7 | 3 (send-as-cost) |
| `op.BanishTimed` | 6 | 6 | 1–3 |
| `stat.Continuous` | 4 | 4 | 1–3 |
| `battle.AttackRedirect` | 3 | 3 | 3 (battle targeting) |
| `event.OnDestroy` | 3 | 3 | 3 |
| `ui.Choice` | 3 | 3 | 2 |
| `event.GyIgnition` | 2 | 2 | 3 |
| `event.OnFusionSummon` | 2 | 2 | 3 (fusion callback) |
| `event.OnSummon` | 2 | 2 | 3 |
| `battle.ExtraAttack` | 1 | 1 | 1–3 (unk4 mark) |
| `event.OnLpGain` | 1 | 1 | later / LP event |
| `event.OnStandby` | 1 | 1 | 3 (OPT / turn flags) |
| **total** | **157** | **150** | |

## `gate.SendCost` (7 notes)

### `ATLANTEAN_DRAGOONS` (activated)
- path: `src_custom/activated_effects/atlantean_dragoons.c`
- L136: Lv3- Sea Serpent direct via AtlanteanDragoons_CanSeaSerpentAttackDirectly. sent-for-WATER-effect search needs send hook. OPT add 1 Sea Serpent except self from Deck.

### `ATLANTEAN_MARKSMAN` (activated)
- path: `src_custom/activated_effects/atlantean_marksman.c`
- L148: combat damage Deck SS via ApplyAtlanteanMarksmanBattleEffect. sent-for-WATER destroy Set S/T needs send hook.

### `CURIOUS_THE_LIGHTSWORN_DOMINION` (activated)
- path: `src_custom/activated_effects/curious_the_lightsworn_dominion.c`
- L145: Leave-field GY add via CuriousTheLightswornDominion_EnsureInit. Link Summon mill + mill-cascade need summon/send hooks. OPT mill 1 from Deck below.

### `EL_SHADDOLL_MESHAHRAIL` (activated)
- path: `src_custom/activated_effects/el_shaddoll_meshahrail.c`
- L75: OPT pay 800 → add 1 Shaddoll or Void S/T from Deck (EffectOpt). unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks.

### `EVIL_HERO_NEOS_LORD` (activated)
- path: `src_custom/activated_effects/evil_hero_neos_lord.c`
- L185: On-SS take-control via TryEvilHeroNeosLordOnMonsterPlacement (EffectOpt). indestructible + opp-GY-sent take-control need continuous/send hooks. Field OPT take control of 1 face-up opp (EffectOpt; ignition stand-in).

### `QADSHADDOLL_KEIOS` (activated)
- path: `src_custom/activated_effects/qadshaddoll_keios.c`
- L50: FLIP vs sent-by-effect exclusivity + mill ATK gain need flip/send hooks. OPT SS 1 Shaddoll from hand face-up DEF.

### `REESHADDOLL_WENDIKURUHU` (activated)
- path: `src_custom/activated_effects/reeshaddoll_wendikuruhu.c`
- L73: Quick face-up→face-down follow-up + GY Shaddoll add need flip/send hooks. OPT flip all face-down monsters face-up DEF.

## `battle.AttackRedirect` (3 notes)

### `AMAZONESS_PET_LIGER_KING` (activated)
- path: `src_custom/activated_effects/amazoness_pet_liger_king.c`
- L191: OPT destroy Amazoness → SS Warrior GY via Activate. attack redirect FALSE.

### `EVIL_HERO_MALICIOUS_FIEND` (permanent)
- path: `src_custom/permanent_effects/evil_hero_malicious_fiend.c`
- L44: Pierce via ApplySimplePiercersBattleEffect; forced attack via EvilHeroMaliciousFiend_GetForcedAttackTarget + sForcedAttackRedirects.

### `SOUL_ABSORBING_BONE_TOWER` (activated)
- path: `src_custom/activated_effects/soul_absorbing_bone_tower.c`
- L91: Other-Zombie SS mill via TrySoulAbsorbingBoneTowerOnOtherZombieSummon. Attack redirect while another Zombie present needs battle hooks. Not field-ignition.

## `extra.XyzLinkSynchro` (21 notes)

### `AMAZONESS_HALL` (trap)
- path: `src_custom/trap_effects/amazoness_hall.c`
- L42: On activate: add 1 Amazoness from GY to hand. Extra Deck / Pendulum place + opp SS gain LP need hooks.

### `ANCIENT_GEAR_MEGATON_GOLEM` (activated)
- path: `src_custom/activated_effects/ancient_gear_megaton_golem.c`
- L213: OPT SS AG Golem from hand/GY. Pierce via ApplyAncientGearGolemPiercingBattleEffect. Leave → AG Golem hand/GY/Deck via AncientGearMegatonGolem_EnsureInit (Extra Deck Ultimate blocked). multi-attack.

### `CELESTIAL_KNIGHTLORD_PARSHATH` (activated)
- path: `src_custom/activated_effects/celestial_knightlord_parshath.c`
- L105: OPT discard 1 → add Sanctuary/mention, or Fairy if Sanctuary on field (EffectOpt). Link material + GY banish Fairy → SS Fairy need send/banish hooks.

### `CHIMERATECH_FORTRESS_DRAGON` (activated)
- path: `src_custom/activated_effects/chimeratech_fortress_dragon.c`
- L12: Fusion ATK overlay via ChimeratechFortressDragon_ApplyDynamicZoneStats. Not field-ignition.

### `CHIMERATECH_MEGAFLEET_DRAGON` (activated)
- path: `src_custom/activated_effects/chimeratech_megafleet_dragon.c`
- L12: Fusion ATK overlay via ChimeratechMegafleetDragon_ApplyDynamicZoneStats. Not field-ignition.

### `CRIMSON_DRAGON` (activated)
- path: `src_custom/activated_effects/crimson_dragon.c`
- L197: On-SS search via TryCrimsonDragonOnMonsterPlacement (EffectOpt). OPT search mentioning Crimson Dragon S/T (shares EffectOpt). Extra Deck Synchro SS FALSE; Deck Dragon stand-in.

### `CYBER_DRAGON_INFINITY` (activated)
- path: `src_custom/activated_effects/cyber_dragon_infinity.c`
- L131: ATK overlay via CyberDragonInfinity_ApplyDynamicZoneStats (+200 per tempStage). Xyz attach / negate FALSE. OPT ClearZone absorb + tempStage (EffectOpt).

### `DESTINY_HERO_DUSKTOPIA` (activated)
- path: `src_custom/activated_effects/destiny_hero_dusktopia.c`
- L46: Battle protect + no combat damage via DestinyHeroDusktopia_*; EP clear via TryClearDestinyHeroDusktopiaProtectionEndPhase. Fusion on Summon need fusion hook (Extra Deck fusion from hand/field).

### `FORMULA_SYNCHRON` (activated)
- path: `src_custom/activated_effects/formula_synchron.c`
- L32: extra procedure Summon draw trigger + opp-Main-Phase quick extra procedure need synchro/chain hooks. OPT draw 1 via usage when deck remains.

### `GLADIATOR_BEAST_GYZARUS` (activated)
- path: `src_custom/activated_effects/gladiator_beast_gyzarus.c`
- L174: Tag-out via GladiatorBeast_CanActivateDeckTagOutTwo. Contact Fusion SS destroy trigger + Extra Deck return not wired.

### `GRAVEKEEPERS_SHAMAN` (activated)
- path: `src_custom/activated_effects/gravekeepers_shaman.c`
- L62: DEF overlay via GravekeepersShaman_ApplyDynamicZoneStats. GY-effect negate + Necrovalley Field lock need permanent hooks.

### `HARPIES_PET_PHANTASMAL_DRAGON` (permanent)
- path: `src_custom/permanent_effects/harpies_pet_phantasmal_dragon.c`
- L8: Direct attack via HarpiesPetPhantasmalDragon_CanAttackDirectly. Harpie protect + End Phase detach need battle/xyz hooks.

### `LEVEL_EATER` (activated)
- path: `src_custom/activated_effects/level_eater.c`
- L122: no zone Level-mod field (level is ROM-only via gCardData_NEW). SS self from GY; upgrade: TempLevel overlay on target.

### `LEVIAIR_THE_SEA_DRAGON` (activated)
- path: `src_custom/activated_effects/leviair_the_sea_dragon.c`
- L107: Printed remainder omitted by this ruleset. Materials not checked; overlay detach before SS not wired.

### `LEV_SHADDOLL_FUSION` (spell)
- path: `src_custom/spell_effects/lev_shaddoll_fusion.c`
- L158: the face-up ignition still needs a monster-zone tribute picker and an Extra Deck special-summon flow, neither of which is owned by this spell activation dispatcher.

### `LIFE_STREAM_DRAGON` (activated)
- path: `src_custom/activated_effects/life_stream_dragon.c`
- L28: extra procedure LP=4000 trigger + no effect damage + Equip-banish destruction-replace need synchro/LP/battle hooks. OPT set LP to 4000 via usage.

### `NUMBER_39_UTOPIA` (activated)
- path: `src_custom/activated_effects/number_39_utopia.c`
- L12: Printed remainder omitted by this ruleset. XYZ material system outside this file. Not field-ignition.

### `ROAD_SYNCHRON` (activated)
- path: `src_custom/activated_effects/road_synchron.c`
- L12: extra procedure Level -2 (non-Road Warrior) + battle-hit Level +1 need synchro/battle hooks outside this file. Not field-ignition.

### `TATSUNOKO` (activated)
- path: `src_custom/activated_effects/tatsunoko.c`
- L12: Hand-as-extra procedure-material and unaffected-by-monster-effects need synchro/summon continuous hooks outside this file. Not field-ignition.

### `THUNDER_END_DRAGON` (activated)
- path: `src_custom/activated_effects/thunder_end_dragon.c`
- L59: Printed remainder omitted by this ruleset. Materials not checked; overlay detach before destroy not wired.

### `URGENT_TUNING` (trap)
- path: `src_custom/trap_effects/urgent_tuning.c`
- L14: Printed remainder omitted by this ruleset. summon path outside this file (no in-file Synchro API). shows text + self-destroy; upgrade: collect Tuners + non-Tuners → Extra Deck Synchro SS.

## `event.OnDestroy` (3 notes)

### `MASTER_OF_CHAOS` (activated)
- path: `src_custom/activated_effects/master_of_chaos.c`
- L204: Fusion SS trigger + destroyed GY Spell add need summon/destroy hooks. OPT SS LIGHT/DARK from GY, else tribute LIGHT+DARK → banish.

### `POWER_TOOL_DRAGON` (activated)
- path: `src_custom/activated_effects/power_tool_dragon.c`
- L55: reveal-3 opp-picks + equip destruction replace need reveal/destroy hooks. OPT add first Equip Spell from Deck.

### `SPELL_CHRONICLE` (spell)
- path: `src_custom/spell_effects/spell_chronicle.c`
- L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. activate discard+banish 5 only; unk4 counter slot unused.

## `event.OnSummon` (2 notes)

### `ANCIENT_GEAR_KNIGHT` (activated)
- path: `src_custom/activated_effects/ancient_gear_knight.c`
- L12: Attack S/T lock live via AncientGear_AttackerBlocksOppSpellTrap. Gemini Normal Monster treatment need summon hook.

### `DARKLORD_DESIRE` (activated)
- path: `src_custom/activated_effects/darklord_desire.c`
- L118: OPT -1000 ATK (tempStage) → send 1 opp monster to GY (EffectOpt). Fairy-only Tribute Summon + cannot SS need summon hooks.

## `event.OnFusionSummon` (2 notes)

### `ELEMENTAL_HERO_DARK_NEOS` (activated)
- path: `src_custom/activated_effects/elemental_hero_dark_neos.c`
- L92: EP Extra return via TryReturnContactFusionsAtEndPhase. Contact Fusion need fusion hook outside.

### `SECRETS_OF_DARK_MAGIC` (spell)
- path: `src_custom/spell_effects/secrets_of_dark_magic.c`
- L33: Local recipes that list Dark Magician / Dark Magician Girl as material. incomplete vs printed DM Fusion pool (Dragon Knight, etc.). Amulet Dragon + The Dark Magicians only; upgrade: add remaining DM Fusion recipes to thi

## `chain.Negate` (14 notes)

### `BLUE_EYES_ULTIMATE_SPIRIT_DRAGON` (activated)
- path: `src_custom/activated_effects/blue_eyes_ultimate_spirit_dragon.c`
- L24: OPT +2 tempStage (~+1000) as interrupt stand-in (EffectOpt). Quick field negate + destroy-SS FALSE; GY banish-lock FALSE.

### `DESTINY_HERO_DECIDER` (activated)
- path: `src_custom/activated_effects/destiny_hero_decider.c`
- L115: EP add on NS/SS via TryApplyDestinyHeroDeciderEndPhase. OPT add 1 HERO from GY to hand (EffectOpt). GY quick return-on-damage need chain hook.

### `DESTINY_HERO_DESTROY_DOGMA` (activated)
- path: `src_custom/activated_effects/destiny_hero_destroy_dogma.c`
- L103: Standby burn via TryApplyDestinyHeroDestroyDogmaStandby. Quick destroy/negate FALSE. FromHand banish 3 Warrior/DARK → SS + burn 2000.

### `DIVINE_SERPENT_GEH` (activated)
- path: `src_custom/activated_effects/divine_serpent_geh.c`
- L40: Printed remainder omitted by this ruleset. destroy gate + battle negate need destroy/battle hooks. field ignition FALSE.

### `GODDESS_BOW` (activated)
- path: `src_custom/activated_effects/goddess_bow.c`
- L12: Hermos fusion + equip + battle-phase interrupt/second attack need fusion/equip/chain hooks outside this file. Not field-ignition.

### `HERALD_OF_PERFECTION` (activated)
- path: `src_custom/activated_effects/herald_of_perfection.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition (either-turn discard Fairy → negate + destroy).

### `HERALD_OF_THE_ARC_LIGHT` (activated)
- path: `src_custom/activated_effects/herald_of_the_arc_light.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition (continuous banish + either-turn tribute-negate).

### `HERALD_OF_ULIMATENESS` (activated)
- path: `src_custom/activated_effects/herald_of_ulimateness.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition (either-turn discard Fairy → negate + destroy).

### `HERALD_OF_ULTIMATENESS` (activated)
- path: `src_custom/activated_effects/herald_of_ultimateness.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition (either-turn discard Fairy → negate + destroy).

### `HORUS_THE_BLACK_FLAME_DRAGON_LV8` (activated)
- path: `src_custom/activated_effects/horus_the_black_flame_dragon_lv8.c`
- L12: Spell immunity via IsImmuneToSpellEffectsOnField. either-turn Spell negate needs chain hook.

### `JAIN_TWILIGHTSWORN_GENERAL` (activated)
- path: `src_custom/activated_effects/jain_twilightsworn_general.c`
- L231: OPT banish 1 Lightsworn from hand/GY → weaken 1 face-up monster (EffectOpt). EP mill 2 via TryApplyTwilightswornEndPhase. other-Lightsworn- activated mill 2 needs chain hook.

### `LYLA_TWILIGHTSWORN_ENCHANTRESS` (activated)
- path: `src_custom/activated_effects/lyla_twilightsworn_enchantress.c`
- L207: OPT banish LS from hand/GY then destroy 1 face-up Spell/Trap (EffectOpt). EP mill 3 via TryApplyTwilightswornEndPhase. quick effect on Spell/Trap activation + mill 3 when other LS activates need chain hooks.

### `SILENT_SWORDSMAN` (activated)
- path: `src_custom/activated_effects/silent_swordsman.c`
- L133: Standby +500 via TryApplySilentSwordsmanStandby; OPT tempStage/destroy Spell unchanged. Quick Spell negate needs chain hook.

### `SILENT_SWORDSMAN_ZERO` (activated)
- path: `src_custom/activated_effects/silent_swordsman_zero.c`
- L46: Standby Level/ATK via TryApplySilentSwordsmanZeroStandby; OPT +1 Level/+1 tempStage unchanged. Sarcophagus negate needs chain hook.

## `gate.Tribute` (22 notes)

### `AMAZONESS_SPIRITUALIST` (activated)
- path: `src_custom/activated_effects/amazoness_spiritualist.c`
- L104: Field OPT add Polymerization from Deck. hand/GY bounce→SS + ED lock need GY/ED hooks.

### `ANCIENT_GEAR_STATUE` (activated)
- path: `src_custom/activated_effects/ancient_gear_statue.c`
- L112: Tribute self → SS AG Golem / mentions-Golem from hand/Deck (OPT via EffectOpt). FromHand SS when opp has more monsters — no OPT tracking.

### `BEAST_KING_BARBAROS` (activated)
- path: `src_custom/activated_effects/beast_king_barbaros.c`
- L114: No-tribute 1900 ATK via BeastKingBarbaros_ApplyDynamicZoneStats + tribute hook. OPT stand-in for 3-Tribute destroy.

### `CYBER_KIRIN` (permanent)
- path: `src_custom/permanent_effects/cyber_kirin.c`
- L8: ATK-position spell/trap interrupt, battle-draw, and OPT tribute damage zero need continuous/battle/tribute hooks not wired for permanents.

### `DIVINER_OF_THE_HERALD` (activated)
- path: `src_custom/activated_effects/diviner_of_the_herald.c`
- L105: On-NS/SS mill via TryDivinerOfTheHeraldOnMonsterPlacement (EffectOpt). tribute SS Fairy needs tribute hooks. OPT send 1 Fairy from Deck to GY (+unkTwo Level stand-in until EP clear).

### `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated)
- path: `src_custom/activated_effects/elemental_hero_shining_neos_wingman.c`
- L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. OPT destroy opp cards up to different Attributes.

### `EVIL_HERO_INFERNAL_RIDER` (activated)
- path: `src_custom/activated_effects/evil_hero_infernal_rider.c`
- L268: Add Dark Fusion via TryEvilHeroInfernalRiderOnMonsterPlacement (EffectOpt). OPT banish self+4 GY → Set Super Poly. HERO lock need SS gates.

### `FLAME_RULER` (activated)
- path: `src_custom/activated_effects/flame_ruler.c`
- L12: Treat as 2 Tributes for FIRE Tribute Summon needs tribute-cost LynJump outside this file. Not field-ignition.

### `FOG_KING` (activated)
- path: `src_custom/activated_effects/fog_king.c`
- L12: Tribute-flex Normal Summon, ATK = tributed ATK, and global tribute lock need summon/tribute continuous hooks outside this file. Not field-ignition.

### `GAMECIAL_THE_SEA_TURTLE_KAIJU` (activated)
- path: `src_custom/activated_effects/gamecial_the_sea_turtle_kaiju.c`
- L68: Printed remainder omitted by this ruleset. FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju).

### `GRAVEKEEPERS_CHIEF` (activated)
- path: `src_custom/activated_effects/gravekeepers_chief.c`
- L186: Tribute Summon trigger, once-only control, and Necrovalley GY immunity need summon/continuous hooks. OPT SS GK from GY.

### `HARPIE_LADY_ELEGANCE` (trap)
- path: `src_custom/trap_effects/harpie_lady_elegance.c`
- L47: Shuffle Sisters into Deck, then SS up to 3 different Harpies from hand/Deck/GY. WIND-only SS lock this turn via HarpieLadyElegance_MarkWindOnlyLock. Destroy → add Harpie from Deck via aroma_lp_gain.c (AromaLpGain_EnsureI

### `HOLACTIE_THE_CREATOR_OF_LIGHT` (activated)
- path: `src_custom/activated_effects/holactie_the_creator_of_light.c`
- L64: Printed remainder omitted by this ruleset. Not field-ignition activatable; use FromHand tribute path.

### `LEKUNGA` (activated)
- path: `src_custom/activated_effects/lekunga.c`
- L12: Printed remainder omitted by this ruleset. Wrong Type/Attribute/stats (Fairy/LIGHT 0/0 vs Plant/WATER 700/700); add LEKUNGA_TOKEN card data + art, then swap this define.

### `LEVEL_EATER` (activated)
- path: `src_custom/activated_effects/level_eater.c`
- L178: GY ignition via CanActivateLevelEaterGy / gy_ignition table. cannot-be-Tributed-except-for-Tribute-Summon needs tribute hooks.

### `NEO_SPACE_CONNECTOR` (activated)
- path: `src_custom/activated_effects/neo_space_connector.c`
- L61: on-Normal-Summon trigger + tribute-bounce second effect need summon/tribute hooks. OPT SS Neo-Spacian or Neos from Deck DEF.

### `SCAPEGOAT` (spell)
- path: `src_custom/spell_effects/scapegoat.c`
- L10: Printed remainder omitted by this ruleset. wrong Type/Attribute (Fairy/LIGHT vs Beast/EARTH); upgrade: add SHEEP_TOKEN card data + art, then swap this define.
- L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. best-effort lockMonster; upgrade: tribute validator excludes SCAPEGOAT_TOKEN_ID / token flag.

### `SIMORGH_BIRD_OF_ANCESTRY` (activated)
- path: `src_custom/activated_effects/simorgh_bird_of_ancestry.c`
- L110: WIND tribute-reduce continuous + hand-as-Normal Monster need summon/permanent hooks. OPT return up to 2 opp cards to hand.

### `THE_LEGENDARY_EXODIA_INCARNATE` (activated)
- path: `src_custom/activated_effects/the_legendary_exodia_incarnate.c`
- L125: Printed remainder omitted by this ruleset. OPT add Forbidden One from GY. FromHand tribute Forbidden One → SS.

### `TURBO_BOOSTER` (activated)
- path: `src_custom/activated_effects/turbo_booster.c`
- L101: destroy only monsters that battled your monsters this turn needs battle-tracking hook. OPT tribute self then destroy 1 opponent monster; SS-from-hand uses FromHand path.
- L138: no Normal Summon-this-turn flag in engine; allow hand SS anytime. Upgrade: gate on turn flag once duel state tracks Normal Summons.

## `event.OnStandby` (1 notes)

### `THE_AGENT_OF_WISDOM_MERCURY` (activated)
- path: `src_custom/activated_effects/the_agent_of_wisdom_mercury.c`
- L20: Printed remainder omitted by this ruleset. Once via usage if hand empty (standby/end-phase gate not wired).

## `event.GyIgnition` (2 notes)

### `DESTINY_HERO_DREADNOUGHT_SERVANT` (activated)
- path: `src_custom/activated_effects/destiny_hero_dreadnought_servant.c`
- L272: GY banish → opp Deck top on Lv8 D-HERO SS via TryDestinyHeroDreadnoughtServantOnMonsterPlacement. FromHand if control D-HERO or Field Spell → SS, destroy 1, add Poly.

### `THUNDER_DRAGON_TITAN` (activated)
- path: `src_custom/activated_effects/thunder_dragon_titan.c`
- L102: Thunder hand-effect trigger + GY-banish instead of destroy need chain/continuous hooks. OPT destroy 1 card on the field.

## `event.OnLpGain` (1 notes)

### `AROMAGE_ROSEMARY` (activated)
- path: `src_custom/activated_effects/aromage_rosemary.c`
- L127: LP-higher Plant attack → opp monster effects locked need permanent/battle hooks. LP-gain position change via aroma_lp_gain.c. OPT change 1 face-up battle position (EffectOpt).

## `battle.ExtraAttack` (1 notes)

### `BLUE_EYES_TYRANT_DRAGON` (activated)
- path: `src_custom/activated_effects/blue_eyes_tyrant_dragon.c`
- L94: Trap immunity via IsImmuneToTrapEffectsOnField; multi-attack + battle-end Set need battle/permanent hooks. OPT Set 1 Trap from GY to backrow.

## `stat.Continuous` (4 notes)

### `ARCANITE_MAGICIAN` (activated)
- path: `src_custom/activated_effects/arcanite_magician.c`
- L160: extra procedure +2 Spell Counters + +1000 ATK/counter need extra procedure/stat hooks. OPT remove 1 unk4 counter → destroy 1 opp (EffectOpt).

### `CYBER_ELTANIN` (activated)
- path: `src_custom/activated_effects/cyber_eltanin.c`
- L154: Continuous ATK/DEF via CyberEltanin_ApplyDynamicZoneStats; FromHand banish+SS path below.

### `EVIL_HERO_VICIOUS_CLAWS` (activated)
- path: `src_custom/activated_effects/evil_hero_vicious_claws.c`
- L178: GY destroy-revive via EvilHeroViciousClaws_EnsureInit. FromHand target HERO → SS DEF +300 ATK stand-in.

### `THE_AGENT_OF_MIRACLES_JUPITER` (activated)
- path: `src_custom/activated_effects/the_agent_of_miracles_jupiter.c`
- L132: +800 ATK until EP via ResetTempStagesForAllCards; Sanctuary RFG revive FALSE. OPT banish Agent from GY → +2 tempStage on LIGHT Fairy.

## `ui.Choice` (3 notes)

### `DARK_ARMED_DRAGON` (activated)
- path: `src_custom/activated_effects/dark_armed_dragon.c`
- L317: Printed remainder omitted by this ruleset. from inside monster effect handler) and no PickZone cursor state (200 conflicts with game loop after MonsterActionMenu case 4 returns). Picks the best field target via AiPickTar

### `ELEMENTAL_HERO_CORE` (battle)
- path: `src_custom/battle_effects/elemental_hero_core.c`
- L339: Resolve only from post-battle sites (code_8043EF4 / AI_Main / etc.). Inline PickZone here is wiped by attack cleanup (gDuelCursor.state = 0) after pending is already consumed, softlocking the owner's turn.

### `ELEMENTAL_HERO_ICE_EDGE` (battle)
- path: `src_custom/battle_effects/elemental_hero_ice_edge.c`
- L202: Resolve only from post-battle sites (code_8043EF4 / AI_Main / etc.). Inline PickZone here is wiped by attack cleanup (gDuelCursor.state = 0).

## `op.Search` (10 notes)

### `APPRENTICE_ILLUSION_MAGICIAN` (activated)
- path: `src_custom/activated_effects/apprentice_illusion_magician.c`
- L162: NS/SS search via TryApprenticeIllusionMagicianOnMonsterPlacement (EffectOpt). OPT add Dark Magician from Deck (shares EffectOpt). hand/field send +2000 Quick need damage hooks.

### `DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE` (activated)
- path: `src_custom/activated_effects/dark_magician_girl_the_magicians_apprentice.c`
- L94: On-NS/SS search via TryDarkMagicianGirlTheMagiciansApprenticeOnMonsterPlacement. OPT add Shining Sarcophagus (shares EffectOpt). Name=DMG GY +300 mention FALSE.

### `DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE` (activated)
- path: `src_custom/activated_effects/dark_magician_girl_the_magician_s_apprentice.c`
- L94: On-NS/SS search via TryDarkMagicianGirlTheMagicianSApprenticeOnMonsterPlacement. OPT add Shining Sarcophagus (shares EffectOpt). Name=DMG GY +300 mention FALSE.

### `DESTINY_HERO_DREADNOUGHT_MASTER` (activated)
- path: `src_custom/activated_effects/destiny_hero_dreadnought_master.c`
- L118: On-SS add via TryDestinyHeroDreadnoughtMasterOnMonsterPlacement (EffectOpt). Cards-mentioning-D-HERO FALSE. OPT add up to 2 Destiny HERO from Deck (shares EffectOpt).

### `EVIL_HERO_ADUSTED_GOLD` (activated)
- path: `src_custom/activated_effects/evil_hero_adusted_gold.c`
- L63: cannot attack without Fusion Monster needs attack gate. Not field-ignition activatable; discard search uses FromHand path.

### `HARPIE_HARPIST` (activated)
- path: `src_custom/activated_effects/harpie_harpist.c`
- L197: NS bounce via TryHarpieHarpistOnNormalSummon (EffectOpt). GY End Phase search (Lv4 WB ≤1500 ATK) needs EP hook. OPT bounce own WB + opp face-up (shares EffectOpt).

### `NECROFACE` (activated)
- path: `src_custom/activated_effects/necroface.c`
- L86: Normal Summon shuffle + banish-mill branches need summon/banish hooks. OPT shuffle all banished into Decks + tempStage per card.

### `PUNISHMENT_DRAGON` (activated)
- path: `src_custom/activated_effects/punishment_dragon.c`
- L192: Printed remainder omitted by this ruleset. banished into Decks (EffectOpt). LS mill 4 needs effect-activation hook.

### `RYKO_TWILIGHTSWORN_FIGHTER` (activated)
- path: `src_custom/activated_effects/ryko_twilightsworn_fighter.c`
- L220: NS mill via TryRykoTwilightswornFighterOnNormalSummon (other-LS stand-in). OPT banish LS hand/GY → banish 1 field (EffectOpt). EP mill via TryApplyTwilightswornEndPhase. flip trigger needs flip hook.

### `SPELL_CHRONICLE` (spell)
- path: `src_custom/spell_effects/spell_chronicle.c`
- L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished; cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.

## `op.BanishTimed` (6 notes)

### `ANCIENT_GEAR_DUEL` (trap)
- path: `src_custom/trap_effects/ancient_gear_duel.c`
- L45: Printed remainder omitted by this ruleset. need protection/fusion/battle hooks; mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand

### `CROSS_KEEPER` (activated)
- path: `src_custom/activated_effects/cross_keeper.c`
- L171: Fusion leave ≈ E-HERO Fusion SS while CK in GY; draw1 proxy of banish→draw2→bottom. Upgrade: true SS trigger + banish cost.

### `LEGENDARY_KNIGHT_CRITIAS` (activated)
- path: `src_custom/activated_effects/legendary_knight_critias.c`
- L99: Legend of Heart SS + when-attacked Set Trap from GY need summon/battle hooks. OPT banish 1 face-up Spell/Trap on the field.

### `LEGENDARY_KNIGHT_HERMOS` (activated)
- path: `src_custom/activated_effects/legendary_knight_hermos.c`
- L99: Legend of Heart SS + when-attacked GY name/effect copy need summon/battle hooks. OPT banish 1 face-up Spell/Trap.

### `LEGENDARY_KNIGHT_TIMAEUS` (activated)
- path: `src_custom/activated_effects/legendary_knight_timaeus.c`
- L99: Legend of Heart SS + attacked-set-Spell-from-GY need summon/battle hooks. OPT banish 1 face-up Spell/Trap on the field.

### `SPELL_CHRONICLE` (spell)
- path: `src_custom/spell_effects/spell_chronicle.c`
- L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn; briefly hits GY; upgrade: direct deck→RFG.

## `other` (55 notes)

### `ANCIENT_GEAR_GADJILTRON_CHIMERA` (activated)
- path: `src_custom/activated_effects/ancient_gear_gadjiltron_chimera.c`
- L12: Printed remainder omitted by this ruleset. Not ignition-activatable here.

### `ARCANA_FORCE_V_THE_HIEROPHANT` (activated)
- path: `src_custom/activated_effects/arcana_force_v_the_hierophant.c`
- L87: OPT coin → SS 1 Arcana Force from Deck (EffectOpt). discard summon-lock + FromHand paths.

### `ARCANA_KNIGHT_JOKER` (activated)
- path: `src_custom/activated_effects/arcana_knight_joker.c`
- L12: Printed remainder omitted by this ruleset. outside this file. Not field-ignition.

### `BLUE_EYES_JET_DRAGON` (activated)
- path: `src_custom/activated_effects/blue_eyes_jet_dragon.c`
- L289: Battle/effect protect via BlueEyesJetDragon_Prevents* while BEWD on field/GY. BEWD/Alt destroy → SS Jet from hand via BlueEyesJetDragon_EnsureInit. Field OPT bounce 1; FromHand if BEWD field/GY → SS.

### `BLUE_EYES_SOLID_DRAGON` (activated)
- path: `src_custom/activated_effects/blue_eyes_solid_dragon.c`
- L49: Battle/effect protect via BlueEyesSolidDragon_Prevents*. Residual: summon Quick shuffle→SS BEWD + per-effect usage need hooks.

### `CLEAR_VICE_DRAGON` (activated)
- path: `src_custom/activated_effects/clear_vice_dragon.c`
- L71: Battle ATK = 2× target via ApplyClearViceDragonDamageStepAtk. Clear World immunity + discard-to-save need continuous/destruction hooks.

### `DARKNESS_NEOSPHERE` (activated)
- path: `src_custom/activated_effects/darkness_neosphere.c`
- L87: Battle indestruct + trap bounce + attack-declare gate need battle/phase hooks outside this file. Not field-ignition; SS uses FromHand path.

### `DARK_MAGICIAN_THE_DRAGON_KNIGHT` (activated)
- path: `src_custom/activated_effects/dark_magician_the_dragon_knight.c`
- L63: Name=Dark Magician via DarkMagicianTheDragonKnight_TreatsNameAsDarkMagician + Duel_ZoneEffectCardId; S/T protect via DarkMagicianTheDragonKnight_ProtectsSpellTrap. Not field-ignition.

### `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS` (activated)
- path: `src_custom/activated_effects/dark_magician_the_magician_of_black_chaos.c`
- L33: Name=Dark Magician via DarkMagicianTheMagicianOfBlackChaos_TreatsNameAsDarkMagician + Duel_ZoneEffectCardId. Destroy-revive/Set via DarkMagicianDestroyRevive_EnsureInit. Not field-ignition; FromHand if Shining Sarcophagu

### `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC` (activated)
- path: `src_custom/activated_effects/dark_magician_the_magician_of_black_magic.c`
- L256: Name=Dark Magician via DarkMagicianTheMagicianOfBlackMagic_TreatsNameAsDarkMagician + Duel_ZoneEffectCardId. Destroy-revive/Set via DarkMagicianDestroyRevive_EnsureInit. Not field-ignition; FromHand if Shining Sarcophagu

### `DESTINY_HERO_DARK_ANGEL` (activated)
- path: `src_custom/activated_effects/destiny_hero_dark_angel.c`
- L81: Printed remainder omitted by this ruleset. FromHand discard → SS D-HERO to opp DEF.

### `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated)
- path: `src_custom/activated_effects/destiny_hero_destroyer_phoenix_enforcer.c`
- L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. OPT destroy 1 you control + 1 other field card.

### `DESTINY_HERO_DYSTOPIA` (activated)
- path: `src_custom/activated_effects/destiny_hero_dystopia.c`
- L257: On-SS burn via TryDestinyHeroDystopiaOnMonsterPlacement (EffectOpt). Quick destroy-if-ATK-changed needs ATK hooks. OPT pick Lv≤4 D-HERO in GY → burn its ATK.

### `DESTINY_HERO_PLASMA` (activated)
- path: `src_custom/activated_effects/destiny_hero_plasma.c`
- L95: equip/absorb + half-ATK boost + continuous opp interrupt need equip hooks. destroy 1 opp monster.

### `EL_SHADDOLL_ANOYATYLLIS` (permanent)
- path: `src_custom/permanent_effects/el_shaddoll_anoyatyllis.c`
- L40: Monster ignition uses gMonEffect — allow those SS from hand/GY. Spell/Trap (and other non-mon) paths are blocked.

### `EVIL_HERO_INFERNAL_GAINER` (activated)
- path: `src_custom/activated_effects/evil_hero_infernal_gainer.c`
- L110: Printed remainder omitted by this ruleset. when unk4=2; second Standby GY return needs Standby hook.

### `EVIL_HERO_TOXIC_BUBBLE` (activated)
- path: `src_custom/activated_effects/evil_hero_toxic_bubble.c`
- L66: On-SS draw via TryEvilHeroToxicBubbleOnMonsterPlacement. Not field-ignition; SS-from-hand uses FromHand path.

### `EVOLZAR_DOLKKA` (activated)
- path: `src_custom/activated_effects/evolzar_dolkka.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition.

### `FUSILIER_DRAGON_THE_DUAL_MODE_BEAST` (activated)
- path: `src_custom/activated_effects/fusilier_dragon_the_dual_mode_beast.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition.

### `FUSION_DESTINY` (spell)
- path: `src_custom/spell_effects/fusion_destiny.c`
- L33: Local recipes that list a Destiny HERO as material. incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous, DPE, Dusktopia need archetype / Level-gated wildcards not in fusion_recipes). Destiny End Dragoon only; 

### `GORZ_THE_EMISSARY_OF_DARKNESS` (activated)
- path: `src_custom/activated_effects/gorz_the_emissary_of_darkness.c`
- L34: Printed remainder omitted by this ruleset. FromHand empty-field SS.

### `GRAVEKEEPERS_SPIRITUALIST` (activated)
- path: `src_custom/activated_effects/gravekeepers_spiritualist.c`
- L12: Printed remainder omitted by this ruleset. summon API outside this file. Not field-ignition.

### `GRAVEKEEPERS_WATCHER` (activated)
- path: `src_custom/activated_effects/gravekeepers_watcher.c`
- L15: Printed remainder omitted by this ruleset. outside this file. Not field-ignition; discard-from-hand path below.

### `GREAT_POSEIDON_BEETLE` (activated)
- path: `src_custom/activated_effects/great_poseidon_beetle.c`
- L12: Printed remainder omitted by this ruleset. outside this file. Not field-ignition.

### `LEVIAIR_THE_SEA_DRAGON` (activated)
- path: `src_custom/activated_effects/leviair_the_sea_dragon.c`
- L62: Printed remainder omitted by this ruleset. Local mutate of gRemovedFromPlay; RemovedFromPlay_RemoveAt not wired.

### `MAGICAL_PLANT_MANDRAGOLA` (activated)
- path: `src_custom/activated_effects/magical_plant_mandragola.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition.

### `MAGICIANS_ROBE` (activated)
- path: `src_custom/activated_effects/magicians_robe.c`
- L56: Printed remainder omitted by this ruleset. Discard S/T from hand → SS DM from Deck via FromHand path.

### `MAGICIANS_SOULS` (activated)
- path: `src_custom/activated_effects/magicians_souls.c`
- L143: Continuous Spell placement + DM/DMG GY SS branch need placement/ GY hooks. OPT send 1–2 S/T from hand/field → draw that many.

### `MAJESTIC_MECH_GORYU` (activated)
- path: `src_custom/activated_effects/majestic_mech_goryu.c`
- L32: Pierce via ApplySimplePiercersBattleEffect; EP self-send via TryApplyMajesticMechGoryuEndPhase. Not ignition-activatable.

### `MIRROR_FORCE_DRAGON` (activated)
- path: `src_custom/activated_effects/mirror_force_dragon.c`
- L12: Printed remainder omitted by this ruleset. Not ignition-activatable; upgrade: trigger destroy-all.

### `MORPHTRONIC_EARFON` (activated)
- path: `src_custom/activated_effects/morphtronic_earfon.c`
- L111: On-SS Tuner mark via TryMorphtronicEarfonOnMonsterPlacement. Equip 2-attacks FALSE. OPT mark face-up monster as Tuner (unk4 stand-in).

### `MORPHTRONIC_SCOPEN` (activated)
- path: `src_custom/activated_effects/morphtronic_scopen.c`
- L59: DEF Position → treat as Level 4 + EP destroy on ATK-mode SS need position/EP hooks outside. ATK Position OPT SS 1 Lv4 Morphtronic from hand (EffectOpt).

### `NATURIA_BEAST` (activated)
- path: `src_custom/activated_effects/naturia_beast.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition.

### `NEO_SPACIAN_DARK_PANTHER` (activated)
- path: `src_custom/activated_effects/neo_spacian_dark_panther.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition.

### `NIBIRU_THE_PRIMAL_BEING` (activated)
- path: `src_custom/activated_effects/nibiru_the_primal_being.c`
- L90: Printed remainder omitted by this ruleset. FromHand wipe+SS if ≥5 face-up monsters on field.

### `OBLITERATE_BLAZE` (spell)
- path: `src_custom/spell_effects/obliterate_blaze.c`
- L68: Mark granted effects via unk4 bit — secondary pay-half / equip / pierce need hooks.

### `QUINTET_MAGICIAN` (activated)
- path: `src_custom/activated_effects/quintet_magician.c`
- L114: Field wipe via TryQuintetMagicianOnMonsterPlacement. Untributable/undestroyable need continuous hooks. OPT destroy all opp cards.

### `REPTILIANNE_LAMIA` (activated)
- path: `src_custom/activated_effects/reptilianne_lamia.c`
- L175: Printed remainder omitted by this ruleset. FromHand ATK-0 + SS via TrySpecialSummonReptilianneLamiaFromHand; not field-ignition.

### `REPTILIANNE_SERVANT` (permanent)
- path: `src_custom/permanent_effects/reptilianne_servant.c`
- L118: Cannot-be-attacked via sAttackGates + ReptilianneServant_HasOtherFaceUpMonster; Reptile NS lock via ReptilianneServant_BlocksNormalSummonReptile. spell-target destroy needs continuous hook.

### `SCAPEGOAT` (spell)
- path: `src_custom/spell_effects/scapegoat.c`
- L74: LockMonsterCardsInRow also blocks Normal Set of monsters. cannot allow Set while blocking Summon without a menu hook that distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.

### `SHADDOLL_BEAST` (activated)
- path: `src_custom/activated_effects/shaddoll_beast.c`
- L20: FLIP draw2/discard1 and GY-sent draw1 share 1/turn exclusivity. OPT draw 1 stand-in for GY effect only; upgrade: flip + GY hooks.

### `SILENT_MAGICIAN_LV8` (activated)
- path: `src_custom/activated_effects/silent_magician_lv8.c`
- L23: Spell immunity via IsImmuneToSpellEffectsOnField and SilentMagicianLv8_PreventsDestroy; not ignition-activatable.

### `SILENT_SWORDSMAN_LV3` (activated)
- path: `src_custom/activated_effects/silent_swordsman_lv3.c`
- L70: Spell-target interrupt via IsImmuneToHarmfulTargetedEffectsOnField; Standby send self → SS LV5 wired below. summon/flip turn gate needs hooks.

### `SILENT_SWORDSMAN_LV5` (activated)
- path: `src_custom/activated_effects/silent_swordsman_lv5.c`
- L70: Unaffected by opp Spell via IsImmuneToSpellEffectsOnField; OPT send self → SS LV7 wired below. Standby-after-direct-damage gate needs hook.

### `SPELL_GEAR` (spell)
- path: `src_custom/spell_effects/spell_gear.c`
- L155: "You can" — AI always summons when able; player path same (no skip UI). Optional SS offered as auto-yes when legal; cannot skip a legal hand/Deck AGG SS (skip UI unsupported). Upgrade: A/B confirm per location.

### `STARDUST_DRAGON` (activated)
- path: `src_custom/activated_effects/stardust_dragon.c`
- L12: Printed remainder omitted by this ruleset. outside this file. Not field-ignition.

### `THE_AGENT_OF_LIFE_NEPTUNE` (activated)
- path: `src_custom/activated_effects/the_agent_of_life_neptune.c`
- L160: Printed remainder omitted by this ruleset. FromHand discard self → SS Agent (or Hyperion if Sanctuary).

### `TIMEAUS_THE_UNITED_DRAGON` (activated)
- path: `src_custom/activated_effects/timeaus_the_united_dragon.c`
- L147: Printed remainder omitted by this ruleset. SS from hand via send cost uses FromHand path.

### `TIME_MAGIC_HAMMER` (activated)
- path: `src_custom/activated_effects/time_magic_hammer.c`
- L12: Printed remainder omitted by this ruleset. outside this file. Not field-ignition.

### `TUNINGWARE` (activated)
- path: `src_custom/activated_effects/tuningware.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition.

### `TYRANT_BURST_DRAGON` (activated)
- path: `src_custom/activated_effects/tyrant_burst_dragon.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition.

### `T_G_HYPER_LIBRARIAN` (activated)
- path: `src_custom/activated_effects/t_g_hyper_librarian.c`
- L12: Printed remainder omitted by this ruleset. Not field-ignition.

### `ULTIMATE_OBEDIENT_FIEND` (activated)
- path: `src_custom/activated_effects/ultimate_obedient_fiend.c`
- L12: Printed remainder omitted by this ruleset. outside this file. Not field-ignition.

### `ULTIMATE_TYRANNO` (activated)
- path: `src_custom/activated_effects/ultimate_tyranno.c`
- L12: Printed remainder omitted by this ruleset. outside this file. Not field-ignition.

### `VISION_HERO_GRAVITO` (activated)
- path: `src_custom/activated_effects/vision_hero_gravito.c`
- L65: Printed remainder omitted by this ruleset. local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
