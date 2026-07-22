# Partial Effects Taxonomy

Auto-generated companion to [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md).
Each `ponytail:` ceiling is tagged with its **primary missing engine surface** so Phase work in [`effect-data-system.md`](effect-data-system.md) can target events/ops that unblock many cards at once.

```bash
python3 tools/stub_effect_queue.py --write-list
```

**Last updated:** 2026-07-22 18:00 UTC  
**Ceiling lines tagged:** `211`  
**Partial files:** `186`

## Counts by missing surface

| Tag | Count | Suggested phase |
|-----|------:|-----------------|
| `other` | 69 | triage |
| `event.OnStandby` | 61 | 3 (OPT / turn flags) |
| `gate.Tribute` | 19 | 2–3 |
| `chain.Negate` | 16 | later / chain |
| `event.OnSummon` | 14 | 3 |
| `event.GyIgnition` | 6 | 3 |
| `event.OnBattleDestroy` | 6 | 3 |
| `event.OnDestroy` | 6 | 3 |
| `op.Search` | 6 | 1 |
| `op.BanishTimed` | 5 | 1–3 |
| `event.OnDamageCalc` | 1 | 3 |
| `stat.Continuous` | 1 | 1–3 |
| `ui.Choice` | 1 | 2 |
| **total** | **211** | |

Highest-ROI unblock for this backlog is usually **`event.OnStandby` (OPT)** plus destroy/summon/battle listeners (Phase 3), not per-card rewrites.

## `event.OnBattleDestroy` (6)

- `GRAVEKEEPERS_VASSAL` (activated): L12: battle damage as effect damage needs battle-damage type gate. Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle gate outside this file.
- `HONEST` (activated): L95: Damage Step hand discard uses FromHand path. Ceiling: Main Phase return this face-up card to the hand.
- `NEO_BLUE_EYES_ULTIMATE_DRAGON` (activated): L79: Damage Step / Fusion-Summon / protect-negate FALSE. Ceiling: OPT send BE Fusion-ish from Deck → unk4 extra-attack mark. (printed up-to-twice; OPT usage flag is the stand-in).
- `TETHYS_GODDESS_OF_LIGHT` (activated): L54: unk18 != 0 means battle/damage resolution is active.
- `TIMAEUS_THE_KNIGHT_OF_DESTINY` (activated): L53: unaffected + once-per-battle damage calc FALSE. Ceiling: OPT set ATK/DEF ≈ highest field ATK via tempStage.
- `TURBO_SYNCHRON` (activated): L12: attack-target DEF change + battle-damage SS from hand need battle hooks. Ceiling: not ignition-activatable here.

## `event.OnDamageCalc` (1)

- `TIMEAEUS_THE_UNITED_MAGICAL_DRAGON` (permanent): L121: unaffected-after-SS + battle ATK boost need continuous/battle hooks.

## `event.OnDestroy` (6)

- `GATE_GUARDIANS_COMBINED` (activated): L102: negate-on-target + leave-field SS FALSE. Ceiling: OPT destroy 1 opp card (negate stand-in).
- `MASTER_OF_CHAOS` (activated): L204: Fusion SS trigger + destroyed GY Spell add need summon/destroy hooks. Ceiling: OPT SS LIGHT/DARK from GY, else tribute LIGHT+DARK → banish.
- `POWER_TOOL_DRAGON` (activated): L55: reveal-3 opp-picks + equip destruction replace need reveal/destroy hooks. Ceiling: OPT add first Equip Spell from Deck.
- `THE_AGENT_OF_DESTRUCTION_VENUS` (activated): L192: leave-field Deck bottom for Shine Balls needs leave hook. Ceiling: OPT pay 500×N → SS N Mystical Shine Ball from banished/GY.
- `THEINEN_THE_GREAT_SPHINX` (activated): L39: Andro+Teleia destroy SS from hand/Deck needs destroy hook. Ceiling: OPT pay 500 → +7 tempStage (~3000 ATK).
- `DEEP_EYES_WHITE_DRAGON` (permanent): L98: Blue-Eyes destroy hand-SS + burn need GY/destroy hooks; on-summon ATK only.

## `event.OnSummon` (14)

- `GRAVEKEEPERS_HEADMAN` (activated): L95: on-Summon trigger + ATK/face-down DEF choice need summon hook. Ceiling: OPT SS 1 Lv4 Gravekeeper's from GY in ATK.
- `GRAVEKEEPERS_SPIRITUALIST` (activated): L12: Necrovalley-gated Spellcaster Fusion from Extra Deck needs fusion summon API. Ceiling: not ignition-activatable here.
- `HOLACTIE_THE_CREATOR_OF_LIGHT` (activated): L64: SS-this-card-wins-Duel needs win-on-summon hook; no duel_helpers win API. Ceiling: not field-ignition activatable; use FromHand tribute path.
- `MANJU_OF_THE_TEN_THOUSAND_HANDS` (activated): L113: Normal/Flip Summon trigger needs summon hook. Ceiling: once via usage if Ritual Monster or Ritual Spell in Deck and hand space.
- `MAZERA_DEVILLE` (activated): L53: on-SS-with-Pandemonium discard-3 needs summon hook. Ceiling: OPT discard 1 random opp + mill 3.
- `NEO_SPACIAN_MARINE_DOLPHIN` (activated): L79: treated-as Aqua Dolphin name + NEX-only SS need continuous/summon hooks.
- `QUINTET_MAGICIAN` (activated): L64: Fusion-with-5-Spellcasters gate + untributable/undestroyable need fusion/summon hooks. Ceiling: once via usage destroy all opp cards.
- `TEST_PANTHER` (activated): L199: Link Summon trigger for search needs summon hook. Ceiling: OPT search GB from Deck, else bounce GB → SS different GB.
- `THE_AGENT_OF_MYSTERU_EARTH` (activated): L110: Normal Summon trigger needs summon hook. Ceiling: OPT add 1 The Agent except Earth from Deck, or Master Hyperion if Sanctuary is face-up.
- `THE_SUPPRESSION_PLUTO` (activated): L213: on-summon text after field draw so Pluto is visible.
- `TIMEAUS_THE_UNITED_DRAGON` (activated): L147: Main Phase Fusion Summon needs fusion UI hook. Ceiling: SS from hand via send cost uses FromHand path.
- `WHITE_HORNED_DRAGON` (activated): L79: on-Normal/Special Summon trigger needs summon hook. Ceiling: OPT banish up to 5 opp GY Spells + tempStage once via usage.
- `DRAGON_SPIRIT_OF_WHITE` (permanent): L59: Quick Tribute → SS Blue-Eyes from hand needs tribute/summon hooks.
- `MAGICIAN_OF_DARK_ILLUSION` (permanent): L78: opp-turn hand SS + own S/T SS need chain hooks; on-summon GY SS only.

## `event.OnStandby` (61)

- `DESTINY_END_DRAGOON` (activated): L105: GY revive FALSE. Ceiling: OPT destroy 1 opp monster + burn its ATK + cannot BP (unk4).
- `ENLIGHTENMENT_DRAGON` (activated): L138: Extra Summon conditions + destroy-add banished FALSE. Ceiling: OPT pay 2000 → banish all other field+both GYs, else OPT mill 4. Separate OPTs share one MarkMonsterEffectUsed.
- `FORMULA_SYNCHRON` (activated): L32: Synchro Summon draw trigger + opp-Main-Phase quick Synchro need synchro/chain hooks. Ceiling: OPT draw 1 via usage when deck remains.
- `GANDORA_G_THE_DRAGON_OF_DESTRUCTION` (activated): L151: +300 ATK/banished needs permanent/banish count hook. Ceiling: OPT pay half LP → banish all other field → SS Lv≤7 Sarc mention.
- `GRAVEKEEPERS_AMBUSHER` (activated): L146: flip trigger + Necrovalley search need flip/send hooks. Ceiling: OPT put 1 opponent GY card on bottom of their Deck.
- `GRAVEKEEPERS_CHIEF` (activated): L186: Tribute Summon trigger, once-only control, and Necrovalley GY immunity need summon/continuous hooks. Ceiling: OPT SS GK from GY.
- `GRAVEKEEPERS_ORACLE` (activated): L93: Tribute Summon sequence (destroy/flip/ATK) FALSE. Ceiling: OPT destroy up to 2 cards on opp field.
- `GRAVEKEEPERS_SUPERNATURALIST` (activated): L57: material ATK gain + Necrovalley destroy protect + EP schedule FALSE. Ceiling: OPT add Gravekeeper or Necrovalley from Deck now (EP add stand-in).
- `GRAVEKEEPERS_VISIONARY` (activated): L89: * ponytail: destroy-replace needs destroy gate. Ceiling: OPT discard GK stand-in. */
- `GUARDIAN_DREADSCYTHE` (activated): L170: summon lock + GY revive loop need summon/leave hooks. Ceiling: OPT equip/add Reaper Scythe from Deck.
- `HELSHADDOLL_HOLLOW` (activated): L109: FLIP Extra mill + GY attribute mill need flip/send hooks. Ceiling: OPT banish 1 face-up opp monster.
- `KEEPER_OF_DRAGON_MAGIC` (activated): L185: reveal Fusion Extra material-name SS FALSE; any GY face-down stand-in. Ceiling: OPT discard → add Poly/Fusion Normal; else OPT SS any from GY face-down DEF.
- `LADY_OF_D` (activated): L47: opp cannot target your face-up Dragons for attacks needs target- redirect hook. Ceiling: OPT discard 1 Dragon from hand (destroy-save stand-in).
- `LEGENDARY_KNIGHT_CRITIAS` (activated): L99: Legend of Heart SS + when-attacked Set Trap from GY need summon/battle hooks. Ceiling: OPT banish 1 face-up Spell/Trap on the field.
- `LEGENDARY_KNIGHT_HERMOS` (activated): L99: Legend of Heart SS + when-attacked GY name/effect copy need summon/battle hooks. Ceiling: OPT banish 1 face-up Spell/Trap.
- `LEGENDARY_KNIGHT_TIMAEUS` (activated): L99: Legend of Heart SS + attacked-set-Spell-from-GY need summon/battle hooks. Ceiling: OPT banish 1 face-up Spell/Trap on the field.
- `LEVIAIR_THE_SEA_DRAGON` (activated): L107: no Xyz detach cost; OPT SS banished Lv≤4 stand-in when RFP enabled. Ceiling: materials not checked; upgrade: overlay detach before SS.
- `LIFE_STREAM_DRAGON` (activated): L28: Synchro LP=4000 trigger + no effect damage + Equip-banish destruction-replace need synchro/LP/battle hooks. Ceiling: OPT set LP to 4000 via usage.
- `LIGHTRAY_GEARFRIED` (activated): L194: Quick negate S/T activation needs chain hooks. Ceiling: OPT banish Warrior GY → destroy 1 S/T.
- `LIGHTSWORN_DRAGONLING` (activated): L134: hand SS when Lightsworn in GY uses FromHand path. Ceiling: field OPT send 1 other Lightsworn from Deck to GY.
- `LORD_OF_THE_RED` (activated): L115: either-turn chain on activation + S/T branch need chain hooks. Ceiling: OPT destroy 1 monster on the field.
- `MA_AT` (activated): L134: name-3 excavate UI hard. Ceiling: OPT reveal top 3, add any, mill rest.
- `MAGICAL_MARIONETTE` (activated): L117: Spell Counter on Spell resolve + +200 ATK/counter need spell/stat hooks. Ceiling: OPT remove 2 unk4 counters → destroy 1 monster.
- `MAGICIANS_SOULS` (activated): L143: Continuous Spell placement + DM/DMG GY SS branch need placement/ GY hooks. Ceiling: OPT send 1–2 S/T from hand/field → draw that many.
- `MASTER_PEACE_THE_TRUE_DRACOSLAYING_KING` (activated): L111: Tribute Continuous S/T + unaffected-by-type FALSE. Ceiling: OPT banish 1 other field card (Quick destroy stand-in).
- `MASTERFLARE_HYPERION` (activated): L237: name/effect copy + Quick negate FALSE. Ceiling: OPT mill Agent/Sanctuary-mention, else OPT banish Fairy → destroy 1.
- `MILLENNIUM_EYES_RESTRICT` (activated): L88: chain equip/absorb opp Effect Monster needs chain/control hooks. Ceiling: OPT destroy 1 opp monster.
- `MINERVA_THE_ATHENIAN_LIGHTSWORN` (activated): L184: anti-banish continuous + Synchro material count need continuous/synchro hooks. Ceiling: OPT mill LS different Types (up to field LS count), or banish ≤4 LS GY → mill.
- `NAELSHADDOLL_ARIEL` (activated): L72: FLIP SS banished Shaddoll + sent-by-effect branch need flip/RFP hooks. Ceiling: OPT banish up to 3 cards from either GY.
- `NECROFACE` (activated): L86: Normal Summon shuffle + banish-mill branches need summon/banish hooks. Ceiling: OPT shuffle all banished into Decks + tempStage per card.
- `NEO_SPACE_CONNECTOR` (activated): L61: on-Normal-Summon trigger + tribute-bounce second effect need summon/tribute hooks. Ceiling: OPT SS Neo-Spacian or Neos from Deck DEF.
- `NITRO_WARRIOR` (activated): L96: Spell ATK gain + battle-after destroy trigger FALSE. Ceiling: OPT change 1 face-up DEF opp monster to ATK (battle-after stand-in).
- `POWER_TOOL_BRAVER_DRAGON` (activated): L99: SS equip Equip Spells from Deck/GY hard; send-equip negate FALSE. Ceiling: OPT change battle position of 1 monster.
- `PROTECTOR_OF_THE_AGENTS_MOON` (activated): L305: Link Summon trigger gate missing. Ceiling: OPT mill/add Sanctuary path, else OPT tribute Fairy → destroy 1 opp.
- `QADSHADDOLL_KEIOS` (activated): L50: FLIP vs sent-by-effect exclusivity + mill ATK gain need flip/send hooks. Ceiling: OPT SS 1 Shaddoll from hand face-up DEF.
- `RAINBOW_DARK_DRAGON` (activated): L265: hand SS by banishing 7 different DARK uses FromHand path. Ceiling: OPT banish other DARK you control/from GY → +500 ATK each (tempStage).
- `REESHADDOLL_WENDI` (activated): L59: FLIP vs sent-by-effect face-down DEF branches need flip/send hooks. Ceiling: OPT SS 1 other Shaddoll from Deck face-up DEF.
- `REESHADDOLL_WENDIKURUHU` (activated): L73: Quick face-up→face-down follow-up + GY Shaddoll add need flip/send hooks. Ceiling: OPT flip all face-down monsters face-up DEF.
- `REPTILIANNE_ECHIDNA` (activated): L230: Link Summon trigger + Extra Deck lock FALSE. Ceiling: OPT set 1 opp face-up ATK to 0, else OPT add Reptiles up to 0-ATK count. Separate OPT flags share one MarkMonsterEffectUsed.
- `REPTILIANNE_VASKII` (activated): L191: only-SS-by-tribute + unique-on-field need summon/field hooks. Ceiling: OPT destroy 1 face-up opp monster.
- `SHADDOLL_BEAST` (activated): L20: FLIP draw2/discard1 and GY-sent draw1 share 1/turn exclusivity. Ceiling: OPT draw 1 stand-in for GY effect only; upgrade: flip + GY hooks.
- `SHADDOLL_FALCO` (activated): L115: FLIP vs GY-sent exclusivity + SS-self-on-send need trigger hooks. Ceiling: OPT SS 1 other Shaddoll from GY face-down DEF.
- `SHADDOLL_HEDGEHOG` (activated): L112: FLIP S/T vs GY-sent monster exclusivity + trigger hooks deferred. Ceiling: OPT search 1 Shaddoll S/T or monster from Deck once via usage.
- `SHADDOLL_HOUND` (activated): L93: FLIP vs sent-by-effect battle-position branch need flip/send hooks. Ceiling: OPT add 1 Shaddoll from GY to hand.
- `SIMORGH_BIRD_OF_ANCESTRY` (activated): L110: WIND tribute-reduce continuous + hand-as-Normal Monster need summon/permanent hooks. Ceiling: OPT return up to 2 opp cards to hand.
- `TEST_BEAR` (activated): L237: Deck/ED-summoned GB gate for hand SS relaxed to any face-up GB. Ceiling: OPT tribute self + shuffle 1 GB → SS up to 2 GB from Deck.
- `THE_EXECUTOR_OF_THE_UNDERWORLD_PLUTO` (activated): L163: Quick via Sanctuary + GY add Sanctuary FALSE. Ceiling: OPT banish 1 monster from GY → flip 1 Effect Monster face-down DEF.
- `THE_LEGENDARY_EXODIA_INCARNATE` (activated): L125: ATK gain / unaffected FALSE. Ceiling: OPT add Forbidden One from GY. FromHand tribute Forbidden One → SS.
- `THUNDER_DRAGON_TITAN` (activated): L102: Thunder hand-effect trigger + GY-banish instead of destroy need chain/continuous hooks. Ceiling: OPT destroy 1 card on the field.
- `THUNDER_END_DRAGON` (activated): L59: no Xyz detach cost; OPT destroy-all-other-monsters stand-in. Ceiling: materials not checked; upgrade: overlay detach before destroy.
- `TIME_THIEF_REDOER` (activated): L140: detach materials + banish-until-EP FALSE. Ceiling: OPT draw 1 OR return 1 face-up opp monster to Deck.
- `TOADALLY_AWESOME` (activated): L212: detach/Standby/negate FALSE. Ceiling: OPT SS Frog from Deck, else OPT send Aqua → destroy 1 opp.
- `TOHUSHADDOLL_GRYSTA` (activated): L22: FLIP copy + GY Fusion-by-banish need flip/GY hooks. Ceiling: OPT add Shaddoll Fusion from Deck.
- `TUALATIN` (activated): L108: FromHand battle-wipe SS + Summon Attribute lock FALSE. Ceiling: OPT destroy all face-up monsters of first opp monster's Attribute.
- `TURBO_BOOSTER` (activated): L101: destroy only monsters that battled your monsters this turn needs battle-tracking hook. Ceiling: OPT tribute self then destroy 1 opponent monster; SS-from-hand uses FromHand path.
- `ULTIMATE_CONDUCTOR_TYRANNO` (activated): L194: multi-attack + DEF burn/send need battle hooks. Ceiling: OPT destroy 1 of your monsters → flip all opp face-up monsters face-down DEF.
- `VICTORIA` (activated): L177: continuous attack redirect for other face-up Fairies needs attack-target hook. Ceiling: OPT SS 1 Dragon from opponent's GY.
- `WEISS_LIGHTSWORN_ARCHFIEND` (activated): L167: sent-from-Deck-to-GY trigger needs mill/send hook. Ceiling: field OPT SS 1 other Lightsworn from GY.
- `CYBER_KIRIN` (permanent): L8: ATK-position spell/trap negate, battle-draw, and OPT tribute damage zero need continuous/battle/tribute hooks not wired for permanents.
- `DRAGON_MASTER_MAGIA` (permanent): L8: Quick negate-by-card-type needs chain/OPT hooks.
- `THE_DARK_MAGICIANS` (permanent): L154: OPT draw on S/T activation needs chain/OPT hooks.

## `event.GyIgnition` (6)

- `LEVEL_EATER` (activated): L177: GY ignition + cannot-be-Tributed-except-for-Tribute-Summon need GY-menu + tribute hooks. Ceiling: GY ignition when Lv5+ you control + empty zone (Treeborn pattern).
- `MEZUKI` (activated): L169: GY ignition needs GY-menu wire. Ceiling: allow when Mezuki + another Zombie in expanded GY (callable if gMonEffect set to Mezuki).
- `POSEIDRA_THE_ATLANTEAN_DRAGON` (activated): L284: hand SS uses FromHand path. Ceiling: GY ignition like Malicious.
- `THE_BLAZING_MARS` (activated): L48: no multi-select GY banish + hand/GY activation path yet — banish 3 other monsters to Special Summon deferred until expanded GY targeting exists.
- `YAMORIMORI` (activated): L124: GY ignition needs GY-menu wire. Ceiling: banish self from GY + own Reptile + opp face-up present → destroy opp face-up monster.
- `THUNDER_DRAGON_COLOSSUS` (permanent): L8: opp search lock + battle/effect destroy→GY-banish need continuous/battle hooks.

## `chain.Negate` (16)

- `EVOLZAR_DOLKKA` (activated): L12: quick Xyz detach + negate monster effect need chain/Xyz hooks. Ceiling: not field-ignition here.
- `GODDESS_BOW` (activated): L12: Hermos fusion + equip + battle-phase negate/second attack need fusion/equip/chain hooks. Ceiling: not ignition-activatable here.
- `GRAVEKEEPERS_SHAMAN` (activated): L63: * ponytail: GY-effect negate + Necrovalley Field lock need permanent hooks. */
- `GRAVEKEEPERS_WATCHER` (activated): L15: either-turn chain negate when opp discards needs chain/negation hooks. Ceiling: not field-ignition; discard-from-hand path below.
- `GRAVEKEEPERS_WATCHER` (activated): L47: negate activation + destroy activated card not wired.
- `HERALD_OF_PERFECTION` (activated): L12: quick negate by sending Fairy from hand needs chain/negation hooks. Ceiling: not field-ignition activatable here; upgrade: either-turn chain interrupt → discard Fairy → negate + destroy activated card.
- `HERALD_OF_THE_ARC_LIGHT` (activated): L12: deck/hand mill-banish + Quick tribute-negate need send/chain hooks. Ceiling: not field-ignition activatable here; upgrade: continuous banish + either-turn chain interrupt → tribute self → negate + destroy.
- `HERALD_OF_ULIMATENESS` (activated): L12: quick negate by sending Fairy from hand needs chain/negation hooks. Ceiling: not field-ignition activatable here; upgrade: either-turn chain interrupt → discard Fairy → negate + destroy activated card.
- `HERALD_OF_ULTIMATENESS` (activated): L12: quick negate by sending Fairy from hand needs chain/negation hooks. Ceiling: not field-ignition activatable here; upgrade: either-turn chain interrupt → discard Fairy → negate + destroy activated card.
- `ILLUSION_OF_CHAOS` (activated): L135: field bounce→SS DM negate FALSE. Ceiling: FromHand search only.
- `MASTER_PEACE_THE_TRUE_DRACOSLAYING_KING` (activated): L54: Quick Effect destroy→banish stand-in via Duel_BanishZone.
- `NATURIA_BEAST` (activated): L12: Quick Effect spell negate + mill 2 need chain/negation hooks. Ceiling: not ignition-activatable here; upgrade: either-turn interrupt.
- `NUMBER_39_UTOPIA` (activated): L12: attack negate via detach + no-material self-destroy need battle hook and XYZ material system. Ceiling: not field-ignition activatable.
- `SILENT_SWORDSMAN` (activated): L134: * ponytail: Quick Spell negate needs chain hook. */
- `STARDUST_DRAGON` (activated): L12: Quick Effect tribute-negate-destroy + End Phase GY SS need chain and EP hooks. Ceiling: not ignition-activatable here.
- `LIGHT_AND_DARKNESS_DRAGON` (permanent): L8: chain negate (−500 ATK/DEF) + GY destroy-all/SS need chain/GY hooks.

## `gate.Tribute` (19)

- `FELIS_LIGHTSWORN_ARCHER` (activated): L101: SS when sent from Deck to GY by monster effect needs mill/SS hook. Ceiling: ignition tribute self → destroy 1 opponent monster → mill 3.
- `FOG_KING` (activated): L12: tribute-flex Normal Summon, ATK = tributed ATK, and global tribute lock need summon/tribute continuous hooks. Ceiling: not field-ignition here.
- `FUSILIER_DRAGON_THE_DUAL_MODE_BEAST` (activated): L12: NS without tribute + halved ATK/DEF needs summon tribute gate. Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon gate outside this file.
- `GAMECIAL_THE_SEA_TURTLE_KAIJU` (activated): L68: SS to opp field + Quick remove Kaiju Counter FALSE. Ceiling: FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju).
- `KAIBAMAN` (activated): L96: tribute-replacement in same zone; not a marked special summon (unk4 stays 0)
- `LEKUNGA` (activated): L12: no Lekunga Token card id — MOON_TOKEN stand-in. Ceiling: wrong Type/Attribute/stats (Fairy/LIGHT 0/0 vs Plant/WATER 700/700); upgrade: add LEKUNGA_TOKEN card data + art, then swap this define.
- `MAGICAL_PLANT_MANDRAGOLA` (activated): L12: FLIP place Spell Counters needs flip + counter storage. Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon gate outside this file.
- `NIBIRU_THE_PRIMAL_BEING` (activated): L90: 5-summon gate + Primal Being Token to opp FALSE. Ceiling: FromHand wipe+SS if ≥5 face-up monsters on field.
- `PREDAPLANT_VERTE_ANACONDA` (activated): L129: DARK attribute mark + Poly/Fusion copy SS need attribute/fusion hooks. Ceiling: pay 2000 LP → destroy 1 field card.
- `PROTECTOR_OF_THE_AGENTS_MOON` (activated): L252: dual PickZone needs scratch; auto first Fairy tribute.
- `REPTILIANNE_VASKII` (activated): L233: multi-zone tribute picker not wired; auto-tribute first two 0 ATK.
- `T_G_HYPER_LIBRARIAN` (activated): L12: Synchro Summon draw trigger needs synchro hook. Ceiling: not ignition-activatable here; upgrade: synchro summon gate.
- `THE_AGENT_OF_JUDGMENT_SATURN` (activated): L39: skip Battle Phase this turn needs phase-lock hook. Ceiling: tribute self → burn LP difference when Sanctuary face-up and LP higher.
- `THE_AGENT_OF_LIFE_NEPTUNE` (activated): L160: tribute-lock + banish search FALSE. Ceiling: FromHand discard self → SS Agent (or Hyperion if Sanctuary).
- `THE_WINGED_DRAGON_OF_RA_SPHERE_MODE` (activated): L159: in-place tribute replacement; Duel_SpecialSummon* needs an empty zone
- `TUNINGWARE` (activated): L12: Synchro level-2 treatment + draw-on-material need synchro hooks. Ceiling: not ignition-activatable here; upgrade: synchro summon gate.
- `TURBO_BOOSTER` (activated): L138: no Normal Summon-this-turn flag in engine; allow hand SS anytime. Upgrade: gate on turn flag once duel state tracks Normal Summons.
- `LEGENDARY_MAJU_GARZETT` (permanent): L8: ATK = tributed originals needs hand-tribute SS stat capture; FromHand only.
- `MAGICIANS_ROD` (permanent): L138: GY tribute Spellcaster → add this needs opp-turn quick hook.

## `stat.Continuous` (1)

- `THE_AGENT_OF_MIRACLES_JUPITER` (activated): L132: +800 ATK until EP needs exact stage/EP clear; Sanctuary RFG revive FALSE. Ceiling: banish Agent from GY → +2 tempStage on LIGHT Fairy.

## `ui.Choice` (1)

- `GUNGNIR_DRAGON_OF_THE_ICE_BARRIER` (activated): L195: 2-discard path auto-destroys 2 cards; upgrade: sequential PickZone.

## `op.Search` (6)

- `PUNISHMENT_DRAGON` (activated): L191: hand SS via 4+ banished LS uses FromHand path; LS mill 4 needs effect-activation hook. Ceiling: pay 1000 → shuffle all banished into Decks.
- `SHADDOLL_SQUAMATA` (activated): L154: FLIP destroy vs GY-sent mill exclusivity + trigger hooks deferred. Ceiling: destroy 1 opp monster OR mill 1 Shaddoll from Deck once via usage.
- `SOUL_ABSORBING_BONE_TOWER` (activated): L12: attack redirect while another Zombie present + mill 2 on Zombie SS need continuous/SS hooks. Ceiling: not ignition-activatable here.
- `THE_AGENT_OF_ENTROPY_URANUS` (activated): L117: tempStage stores milled Level, not a true level change hook.
- `JENIS_LIGHTSWORN_MENDER` (permanent): L53: LS-effect mill source not tracked — any deck mill this turn stand-in. EP burn/heal via TryApplyJenisEndPhase.
- `REPTILIANNE_GARDNA` (permanent): L8: destroyed→search Reptilianne needs destroy-to-GY permanent hook.

## `op.BanishTimed` (5)

- `GANDORA_G_THE_DRAGON_OF_DESTRUCTION` (activated): L125: destroy+banish → Duel_BanishZone (no GY).
- `MAGICIANS_ROBE` (activated): L56: opp-turn quick + GY SS banish-on-leave need phase/GY hooks. Ceiling: discard S/T from hand → SS DM from Deck via FromHand path.
- `TIME_MAGIC_HAMMER` (activated): L12: Hermos equip + battle-step dice banish need summon/equip/battle hooks. Ceiling: not field-ignition activatable here.
- `TRISHULA_DRAGON_OF_THE_ICE_BARRIER` (activated): L114: Synchro Summon trigger needs synchro hook. Ceiling: once via usage banish random opp hand + 1 field + 1 GY when available.
- `THE_WICKED_AVATAR` (permanent): L177: after SwitchTurn(), zone POV is still the ended turn until the next UpdateDuelZonePtrs — use gWhoseTurn (new active) not INACTIVE_DUELIST.

## `other` (69)

- `DESTINY_END_DRAGOON` (activated): L65: cannot conduct Battle Phase — unk4 lock stand-in. GY revive FALSE.
- `GORZ_THE_EMISSARY_OF_DARKNESS` (activated): L34: damage-gate + Token FALSE. Ceiling: FromHand empty-field SS.
- `GRAVEKEEPERS_CURSE` (activated): L20: printed is If Summoned trigger. Ceiling: allow once via usage when manually activated / summon-dispatch calls Activate.
- `GRAVEKEEPERS_GUARD` (activated): L85: FLIP trigger needs flip hook.
- `GRAVEKEEPERS_HERATIC` (activated): L12: continuous unaffected-while-Necrovalley needs permanent protection gate. Ceiling: not ignition-activatable here; upgrade: permanent effect while Duel_IsBackrowCardOnField(NECROVALLEY).
- `GRAVEKEEPERS_ORACLE` (activated): L110: multi-target picker not wired; auto-destroy up to 2 opp cards.
- `GRAVEKEEPERS_SPY` (activated): L58: FLIP trigger needs flip hook.
- `GREAT_POSEIDON_BEETLE` (activated): L12: re-attack same target after surviving battle needs battle re-attack hook. Ceiling: not ignition-activatable here.
- `HORUS_THE_BLACK_FLAME_DRAGON_LV8` (activated): L12: /* Spell immunity via IsImmuneToSpellEffectsOnField. ponytail: either-turn Spell
- `HOURGLASS_OF_LIFE` (activated): L11: updateGfx=FALSE — sub_8041CCC refreshes field after popup dismisses.
- `JOWLS_OF_DARK_DEMISE` (activated): L70: Jowls direct-attack flag; cleared when zone resets
- `LEVEL_EATER` (activated): L121: no zone Level-mod field (level is ROM-only via gCardData_NEW). Ceiling: SS self from GY; upgrade: TempLevel overlay on target.
- `LEVIA_DRAGON_DAEDALUS` (activated): L122: walk gDuel.board directly; gFixedZones column order differs on opponent rows, so row/col checks against gMonEffect can skip the wrong slot.
- `LEVIAIR_THE_SEA_DRAGON` (activated): L62: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- `MA_AT` (activated): L102: name-3 declare UI missing; add any excavated as stand-in.
- `MAGICAL_SCIENTIST` (activated): L215: no direct attack + End Phase Extra Deck return need battle/EP hooks. Ceiling: pay 1000 → SS Lv≤6 Fusion from Extra/recipe list.
- `MAGICIANS_ROBE` (activated): L76: opponent's turn gate not wired.
- `MAXX_C` (activated): L55: draw-on-opponent-Special-Summon this turn not wired; upgrade: SS hook + simple turn flag when one exists.
- `MIRAGE_DRAGON` (activated): L12: opp cannot activate Traps in Battle Phase needs trap-activation gate. Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.
- `MIRROR_FORCE_DRAGON` (activated): L12: when targeted for attack/effect trigger needs protection hook. Ceiling: not ignition-activatable here; upgrade: trigger destroy-all.
- `NECROFACE` (activated): L107: tempStage unit is ~500 ATK, not printed +100; upgrade: exact overlay.
- `NEO_BLUE_EYES_ULTIMATE_DRAGON` (activated): L105: real multi-attack needs battle hook; unk4=2 extra-attack stand-in.
- `NEO_SPACIAN_DARK_PANTHER` (activated): L12: copy opp monster name/effects needs engine name/effect overlay. Ceiling: not ignition-activatable here; upgrade: permanent/name/effect copy.
- `PROTECTOR_OF_THE_SANCTUARY` (activated): L12: opp cannot draw except Draw Phase needs draw-gate LynJump. Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.
- `REPTILIANNE_LAMIA` (activated): L97: GY synchro-material ATK-0 need synchro hook. Ceiling: not field-ignition; FromHand ATK-0 + SS + self-damage.
- `REPTILIANNE_LAMIA` (activated): L146: FromHand targeting not wired; auto-pick highest original ATK opp.
- `REPTILIANNE_MEDUSA` (activated): L76: cannot change battle position needs position-change gate.
- `RINYAN_LIGHTSWORN_ROGUE` (activated): L41: FLIP trigger needs flip hook. Ceiling: once via usage if LS in GY.
- `ROAD_SYNCHRON` (activated): L12: Synchro Level -2 (non-Road Warrior) + battle-hit Level +1 need synchro/battle hooks. Ceiling: not ignition-activatable here.
- `ROYAL_MAGICAL_LIBRARY` (activated): L22: Spell Counters on Spell activation need spell-resolve hook. Ceiling: ignition only when unk4>=3 (never rises alone); upgrade: on Spell resolve → if face-up ROYAL_MAGICAL_LIBRARY then zone->unk4++ (cap 3).
- `RYKO_LIGHTSWORN_HUNTER` (activated): L107: FLIP trigger needs flip hook. Ceiling: once via usage.
- `SHADDOLL_DRAGON` (activated): L183: FLIP vs GY-sent exclusivity + trigger hooks deferred. Ceiling: bounce 1 opp card OR destroy 1 opp Spell/Trap once via usage.
- `SILENT_SWORDSMAN_LV3` (activated): L71: * self → SS LV5 wired below. ponytail: summon/flip turn gate needs hooks. */
- `SILENT_SWORDSMAN_LV5` (activated): L71: * SS LV7 wired below. ponytail: Standby-after-direct-damage gate needs hook. */
- `SKILLED_DARK_MAGICIAN` (activated): L80: Spell Counters on Spell activation need spell-resolve hook. Ceiling: ignition when unk4>=3 (never rises alone); upgrade: on Spell resolve → if face-up SKILLED_DARK_MAGICIAN then zone->unk4++ (cap 3).
- `SKILLED_WHITE_MAGICIAN` (activated): L80: Spell Counters on Spell resolve need spell-resolve hook. Ceiling: ignition when unk4>=3; upgrade: on Spell resolve → unk4++ (cap 3).
- `TATSUNOKO` (activated): L12: hand-as-Synchro-material and unaffected-by-monster-effects need synchro/summon continuous hooks. Ceiling: not field-ignition here.
- `TEST_BEAR` (activated): L287: printed needs GB SS from Deck/ED; stand-in = any face-up GB.
- `TETHYS_GODDESS_OF_LIGHT` (activated): L50: opening hand is seeded before duel gfx; skip like Solemn Wishes.
- `THE_AGENT_OF_DESTRUCTION_VENUS` (activated): L66: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.
- `THE_AGENT_OF_WISDOM_MERCURY` (activated): L20: Standby Phase empty-hand-last-EP check needs turn-end hook. Ceiling: once via usage if hand empty; upgrade: standby/end-phase gate.
- `THE_BLAZING_MARS` (activated): L63: no Main Phase 1 gate yet — field burn is activatable in any main phase.
- `THE_TRICKY` (activated): L74: discard pick excludes summon slot; upgrade path: exchange_hand_selection helper
- `THE_WINGED_DRAGON_OF_RA_SPHERE_MODE` (activated): L57: hand permanent-effect scan is skipped when turn_off_visual_scanner is on (gHideEffectText), so use Blue Eyes Shining-style post-board-scan auto-summon.
- `TORNADO_BIRD` (activated): L85: FLIP trigger needs flip hook. Ceiling: once via usage.
- `TYRANT_BURST_DRAGON` (activated): L12: multi-attack + equip-to-monster need battle/equip continuous hooks. Ceiling: not ignition-activatable here; upgrade: permanent battle/equip gate.
- `ULTIMATE_OBEDIENT_FIEND` (activated): L12: solo-field + empty-hand attack restriction needs attack gate hook. Ceiling: not field-ignition activatable here.
- `ULTIMATE_TYRANNO` (activated): L12: multi-attack + Tyranno-only battle phase gate need battle hooks. Ceiling: not field-ignition activatable here.
- `WHITE_HORNED_DRAGON` (activated): L101: +1 tempStage per banished (~500 ATK each, not exact +300).
- `ZERADIAS_HERALD_OF_HEAVEN` (activated): L13: destroy self when Sanctuary absent needs continuous field check. Ceiling: not ignition-activatable here; upgrade: permanent maintenance hook.
- `BLUE_EYES_ALTERNATIVE_WHITE_DRAGON` (permanent): L50: BEWD stays in hand as a visible cost; only the alt card is cleared
- `BLUE_EYES_SHINING_DRAGON` (permanent): L68: in-place BEUD zone replacement; Duel_SpecialSummon* only fills empty zones
- `DARKLORD_NURSE_REFICULE` (permanent): L8: LP gain→damage redirect needs LP-change hook.
- `DEEP_EYES_WHITE_DRAGON` (permanent): L121: first Dragon in GY stand-in for target picker.
- `DESPAIR_FROM_THE_DARK` (permanent): L47: opp hand/Deck send by card effect not tracked — GY-top SS only.
- `EXECUTOR_MAKYURA` (permanent): L93: most non-zero trapEffect values are chain-only; allow continuous exceptions.
- `GREAT_MAJU_GARZETT` (permanent): L48: ram_map byte packing can leave u16 fields at odd EWRAM addresses;
- `GRINDER_GOLEM` (permanent): L8: hand SS to opp field + Grinder Tokens + NS/Set lock need summon/token hooks.
- `MAJU_GARZETT` (permanent): L48: ram_map byte packing can leave u16 fields at odd EWRAM addresses;
- `MOBIUS_THE_FROST_MONARCH` (permanent): L175: up-to-2 targeting uses zone->unk4 as phase flag. 0 = not started, 1+ = at least one target destroyed (re-entered targeting). Upgrade path: bitfield on zone if unk4 is needed for other purposes.
- `PETEN_THE_DARK_CLOWN` (permanent): L73: hand takes priority when both are available; deck is the fallback
- `RAVIEL_LORD_OF_PHANTASMS` (permanent): L137: triggers on any monster placement (Normal + Special). Card text says "Normal Summons" only — needs opts.markSpecialSummon check.
- `SPIRIT_OF_THE_POT_OF_GREED` (permanent): L11: normal hand summon copies isFaceUp=0; attack-position monsters still count
- `THE_BIG_SATURN` (permanent): L96: custom targeted spells store fixed-row origins in row2.
- `THE_BIG_SATURN` (permanent): L257: GY permanent scan misses some opponent-turn effect destroys (Core pattern).
- `THE_DARK_MAGICIANS` (permanent): L177: Deck-first SS order; hand/GY picker not wired.
- `THE_TYRANT_NEPTUNE` (permanent): L59: ram_map byte packing can leave u16 fields at odd EWRAM addresses;
- `THE_TYRANT_NEPTUNE` (permanent): L451: draw Neptune on the field before popup / trunk picker.
- `VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES` (permanent): L54: S/T + monster immunity + 3-counter win need continuous/battle hooks.
