# Partial Effects Taxonomy

Auto-generated companion to [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md).
Each `ponytail:` / `Ceiling:` note is tagged with its **primary missing engine surface** so Phase work in [`effect-data-system.md`](effect-data-system.md) can target events/ops that unblock many cards at once.

```bash
python3 tools/stub_effect_queue.py --write-list
```

**Last updated:** 2026-07-22 18:45 UTC  
**Ceiling lines tagged:** `384`  
**Partial files:** `347`

## Counts by missing surface

| Tag | Count | Suggested phase |
|-----|------:|-----------------|
| `event.OnStandby` | 173 | 3 (OPT / turn flags) |
| `other` | 98 | triage |
| `event.OnSummon` | 18 | 3 |
| `extra.XyzLinkSynchro` | 17 | later / Extra Deck |
| `chain.Negate` | 14 | later / chain |
| `gate.Tribute` | 14 | 2–3 |
| `event.GyIgnition` | 9 | 3 |
| `event.OnDestroy` | 9 | 3 |
| `op.BanishTimed` | 8 | 1–3 |
| `op.Search` | 7 | 1 |
| `event.OnBattleDestroy` | 5 | 3 |
| `ui.Choice` | 5 | 2 |
| `event.OnFusionSummon` | 3 | 3 (fusion callback) |
| `event.OnLpGain` | 3 | later / LP event |
| `stat.Continuous` | 1 | 1–3 |
| **total** | **384** | |

Highest-ROI unblock for this backlog is usually **`event.OnStandby` (OPT)** plus destroy/summon/battle listeners (Phase 3), not per-card rewrites.

## `event.OnBattleDestroy` (5)

- `AMAZONESS_HOT_SPRING` (trap): L46: * Ceiling: Pendulum Zone place + battle-damage gain LP OPT need hooks. */
- `ARMORY_ARM` (activated): L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE.
- `D_D_WARRIOR` (activated): L13: * battle_effects/d_d_warrior.c. Ceiling: not ignition-activatable here. */
- `HONEST` (activated): L95: /* Damage Step hand discard uses FromHand path. Ceiling: Main Phase
- `EVIL_HERO_WILD_CYCLONE` (permanent): L97: * Ceiling: attack S/T lock until end of Damage Step needs chain gate. */

## `event.OnDestroy` (9)

- `SPELL_CHRONICLE` (spell): L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. Ceiling: activate discard+banish 5 only; unk4 counter slot unused.
- `NECROVALLEY_TEMPLE` (trap): L129: destroy-Set Necrovalley S/T from Deck needs destroy hook — place Necrovalley from hand/GY when GK present; continuous −500 via overlay.
- `CURIOUS_THE_LIGHTSWORN_DOMINION` (activated): L33: Link Summon mill + leave-field GY add + mill-cascade need summon/ leave-field hooks. OPT mill 1 from Deck below.
- `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS` (activated): L34: * Duel_ZoneEffectCardId. Ceiling: destroy-revive/Set need destroy hooks.
- `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC` (activated): L34: * Duel_ZoneEffectCardId. Ceiling: destroy-revive/Set need destroy hooks.
- `ELDER_ENTITY_NORDEN` (activated): L73: banish-when-leaves needs leave-field hook; unk4 marks negated.
- `EVIL_HERO_DARKEST_KNIGHT` (activated): L173: * Ceiling: OPT SS 1 Fiend/Warrior from GY (leave-field stand-in). */
- `EVIL_HERO_VICIOUS_CLAWS` (activated): L46: GY destroy-revive + Dark Fusion destroy branch need GY/destroy hooks. Ceiling: FromHand target HERO → SS DEF +300 ATK stand-in.
- `GLADIATOR_BEAST_DARIUS` (activated): L177: /* GB-tag SS revive + leave-field shuffle need summon/leave hooks. Ceiling: OPT

## `event.OnSummon` (18)

- `SHADDOLL_SCHISM` (trap): L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker; banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.
- `ANCIENT_GEAR_KNIGHT` (activated): L13: * Ceiling: Gemini Normal Monster treatment need summon hook. */
- `ARCANA_FORCE_XV_THE_FIEND` (activated): L271: on-summon heads auto-picks first destroyable opp monster.
- `AROMAGE_JASMINE` (activated): L57: * Ceiling: extra Plant Normal Summon + draw-on-LP-gain need LP/summon hooks.
- `BLACK_ROSE_DRAGON` (activated): L158: Synchro Summon destroy-all needs summon hook. Ceiling: OPT banish 1 Plant from GY → opp DEF monster to ATK with 0 ATK (tempStage).
- `DARKLORD_DESIRE` (activated): L116: Fairy-only Tribute Summon + cannot SS need summon hooks. Ceiling: OPT -1000 ATK (tempStage) → send 1 opp monster to GY.
- `DESTINY_HERO_DUSKTOPIA` (activated): L47: * TryClearDestinyHeroDusktopiaProtectionEndPhase. Ceiling: Fusion on Summon
- `EVIL_HERO_INFERNAL_RIDER` (activated): L228: on-summon + HERO lock need summon/SS gates. Ceiling: OPT add Dark Fusion Deck/GY, else OPT banish self+4 GY → Set Super Poly.
- `EVIL_HERO_NEOS_LORD` (activated): L144: indestructible + on-SS/opp-GY-sent take-control triggers need continuous/summon hooks; OPT take control of 1 face-up opp monster.
- `EVIL_HERO_TOXIC_BUBBLE` (activated): L16: on-SS draw when Dark Fusion Fusion up needs summon hook. Not field-ignition activatable; SS-from-hand uses FromHand path.
- `GLADIATOR_BEAST_BESTIARI` (activated): L194: /* GB-tag SS destroy trigger need summon hook. Ceiling: OPT destroy 1 opp S/T;
- `GLADIATOR_BEAST_EQUESTE` (activated): L160: /* On-GB-tag SS add trigger need summon hook. Ceiling: OPT add 1 GB from GY to
- `GLADIATOR_BEAST_MURMILLO` (activated): L237: /* GB-tag SS destroy trigger need summon hook. Ceiling: OPT destroy face-up
- `MAZERA_DEVILLE` (activated): L53: /* on-SS-with-Pandemonium discard-3 needs summon hook. Ceiling: OPT
- `QUINTET_MAGICIAN` (activated): L65: * fusion/summon hooks. Ceiling: once via usage destroy all opp cards. */
- `ARCANA_FORCE_III_THE_EMPRESS` (permanent): L48: opp Normal Summon SS/discard triggers need summon hooks; unk4 only.
- `DESTINY_HERO_DREAD_SERVANT` (permanent): L77: * Ceiling: NS Clock Tower counters need summon hook. */
- `EVIL_HERO_INFERNO_WING_BACKFIRE` (permanent): L155: true trigger is Special Summon; on-summon stand-in covers SS path.

## `event.OnFusionSummon` (3)

- `ELEMENTAL_HERO_DARK_NEOS` (activated): L92: /* EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: contact Fusion need fusion hook. */
- `GLADIATOR_BEAST_GYZARUS` (activated): L175: * Ceiling: Contact Fusion SS destroy trigger + Extra Deck return. */
- `GLADIATOR_BEAST_ESSEDARII` (permanent): L8: Contact Fusion has no permanent ignition path.

## `event.OnStandby` (173)

- `DARK_SUPREMACY` (trap): L53: GY banish shuffle HERO need GY ignition OPT. Ceiling: negate up to count face-up opp cards (monsters first) via unk4.
- `AMAZONESS_PET_LIGER_KING` (activated): L191: OPT destroy Amazoness → SS Warrior GY. Residual: attack redirect FALSE.
- `AMAZONESS_SPIRITUALIST` (activated): L104: field OPT add Polymerization from Deck. Residual: hand/GY bounce→SS + ED lock need GY/ED hooks.
- `ANCIENT_FAIRY_DRAGON` (activated): L196: OPT SS Lv≤4 from hand; OPT destroy Field Spells + 1000 LP + add Field.
- `ANCIENT_GEAR_COMMANDER` (activated): L202: OPT send AG Golem hand/field/Deck → SS AG hand/Deck.
- `ANCIENT_GEAR_DARK_GOLEM` (activated): L60: OPT add up to 2 Ancient Gear/Geartown from Deck then discard 1.
- `ANCIENT_GEAR_DRAGON` (activated): L121: OPT send Machine hand/field or AG Golem from Deck to GY.
- `ANCIENT_GEAR_FRAME` (activated): L123: * Ceiling: OPT discard 1 → add AG Golem or S/T mentioning Golem from Deck. */
- `ANCIENT_GEAR_GADJILTRON_DRAGON` (activated): L108: * Ceiling: OPT destroy 1 DEF opp OR OPT burn 700. */
- `ANCIENT_GEAR_MEGATON_GOLEM` (activated): L124: * Ceiling: OPT SS AG Golem from hand/GY. */
- `ANCIENT_GEAR_STATUE` (activated): L111: OPT tribute self → SS AG Golem / mentions-Golem from hand/Deck.
- `ANCIENT_GEAR_TANKER` (activated): L237: * Ceiling: OPT SS AG from hand (GY if opp has monster), else OPT destroy your face-up.
- `APPRENTICE_ILLUSION_MAGICIAN` (activated): L120: on-NS/SS search auto + hand/field send +2000 Quick need summon/ damage hooks. Ceiling: OPT add Dark Magician from Deck.
- `ARCANA_FORCE_V_THE_HIEROPHANT` (activated): L86: discard summon-lock + FromHand paths. OPT coin → SS 1 Arcana Force from Deck.
- `ARCANA_FORCE_XII_THE_HANGMAN` (activated): L139: OPT coin → destroy+burn (heads own / tails opp). FromHand SS AF.
- `ARCANA_FORCE_XIX_THE_SUN` (activated): L81: OPT coin → flip all opp monsters DEF or destroy half yours.
- `ARCANA_FORCE_XV_THE_FIEND` (activated): L206: discard search + FromHand paths. OPT coin → destroy 1 monster or wipe field.
- `ARCANITE_MAGICIAN` (activated): L158: Synchro +2 Spell Counters + +1000 ATK/counter need synchro/stat hooks. Ceiling: OPT remove 1 unk4 counter (if >=1) → destroy 1 opp card.
- `ARMED_NEOS` (activated): L258: * Ceiling: OPT destroy opp monsters with Level ≤ highest Dragon Level in GY. */
- `AROMAGE_CANANGA` (activated): L176: * Ceiling: OPT bounce 1 opp Spell/Trap if hand room. */
- `AROMAGE_JASMINE` (activated): L58: * Ceiling: OPT draw 1 via usage. */
- `AROMAGE_LAUREL` (activated): L66: OPT add 1 Plant from Deck. Residual: LP-gain Tuner treat + sent-to-GY +500 LP need LP/send hooks.
- `AROMAGE_MARJORAM` (activated): L180: * Ceiling: destroy-SS + LP-gain trigger need destroy/LP hooks. Ceiling: OPT banish opp GY. */
- `AROMAGE_ROSEMARY` (activated): L125: LP-higher Plant attack → opp monster effects locked + LP-gain gate need permanent/LP hooks. Ceiling: OPT change 1 face-up battle position.
- `AROMALILITH_MAGNOLIA` (activated): L137: * Ceiling: OPT pay 2000 → banish up to Humid/Dried/Blessed Winds count. */
- `AROMALILITH_ROSALINA` (activated): L106: OPT SS 1 non-Tuner Aroma from Deck in DEF.
- `AROMALILITH_ROSEMARY` (activated): L57: OPT search Aroma from Deck.
- `AROMASERAPHY_ROSEMARY` (activated): L190: * Ceiling: OPT destroy 1 face-up opp. Residual: LP-gain negate needs LP hook. */
- `AROMASERAPHY_SWEET_MARJORAM` (activated): L100: * Ceiling: OPT search Aroma Plant. */
- `ATLANTEAN_DRAGOONS` (activated): L138: * Ceiling: OPT add 1 Sea Serpent except self from Deck. */
- `ATLANTEAN_HEAVY_INFANTRY` (activated): L111: extra Normal Summon Sea Serpent + sent-for-WATER destroy need summon/send hooks. Ceiling: OPT destroy 1 Set Spell/Trap.
- `BEAST_KING_BARBAROS` (activated): L115: * Ceiling: OPT stand-in for 3-Tribute destroy. */
- `BLUE_EYES_JET_DRAGON` (activated): L198: * Ceiling: field OPT bounce 1; FromHand if BEWD field/GY → SS.
- `BLUE_EYES_SPIRIT_DRAGON` (activated): L66: * Ceiling: OPT tribute self → SS LIGHT Dragon from Deck in DEF. */
- `BLUE_EYES_TYRANT_DRAGON` (activated): L95: * Set need battle/permanent hooks. Ceiling: OPT Set 1 Trap from GY to backrow. */
- `BLUE_EYES_ULTIMATE_SPIRIT_DRAGON` (activated): L23: Quick field negate + destroy-SS FALSE; GY banish-lock FALSE. Ceiling: OPT +2 tempStage (~+1000) as negate stand-in.
- `CASTEL_THE_SKY_BLASTER_MUSKETEER` (activated): L138: detach/material + face-down branch need overlay engine. Ceiling: OPT return 1 face-up monster to the Deck.
- `CELESTIA_LIGHTSWORN_ANGEL` (activated): L140: * Ceiling: field OPT repeat (usage-gated). Auto-destroy up to 2 (no PickZone). */
- `CELESTIAL_KNIGHTLORD_PARSHATH` (activated): L104: Link material + GY banish Fairy → SS Fairy need send/banish hooks. OPT discard 1 → add Sanctuary/mention, or Fairy if Sanctuary on field.
- `CORAL_DRAGON` (activated): L114: GY draw when Synchro Summoned card sent from field needs GY hook. Ceiling: OPT discard 1 → destroy 1 opp card.
- `CRIMSON_DRAGON` (activated): L138: on-SS search + Extra Synchro return FALSE. Ceiling: OPT search mentioning Crimson Dragon S/T, else shuffle self → SS Dragon.
- `CYBER_DRAGON_INFINITY` (activated): L35: ATK summons keep isFaceUp=0 until EOT flip.
- `CYBER_SLASH_HARPIE_LADY` (activated): L196: Quick on S/T activation + Synchro/name hooks missing. Ceiling: OPT bounce 1 opp card or your Harpie to hand.
- `CYBER_SLASH_HARPY_LADY` (activated): L196: Quick on S/T activation + Synchro/name hooks missing. Ceiling: OPT bounce 1 opp card or your Harpie to hand.
- `CYBER_VALLEY` (activated): L133: * Ceiling: OPT banish self+1 face-up monster → draw 2; else banish self → draw 1
- `DARK_HORUS` (activated): L99: after opp Main Phase Spell resolve trigger needs spell hook. Ceiling: OPT SS 1 Lv4 DARK from GY while face-up.
- `DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE` (activated): L61: name=DMG GY +300 mention FALSE. Ceiling: field OPT add Shining Sarcophagus from Deck.
- `DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE` (activated): L61: name=DMG GY +300 mention FALSE. Ceiling: field OPT add Shining Sarcophagus from Deck.
- `DECOY_DRAGON` (activated): L181: attack-target redirect needs battle targeting hook. OPT SS Lv7+ Dragon from GY once via usage when legal.
- `DEEP_SEA_DIVA` (activated): L101: /* NS SS via TryDeepSeaDivaOnNormalSummon. Ceiling: OPT duplicate if NS already
- `DESTINY_END_DRAGOON` (activated): L106: * Ceiling: OPT destroy 1 opp monster + burn its ATK + cannot BP (unk4). */
- `DESTINY_HERO_CELESTIAL` (activated): L156: * Ceiling: OPT destroy 1 face-up opp Spell + burn 500. */
- `DESTINY_HERO_DECIDER` (activated): L115: * return-on-damage need chain hook. Ceiling: OPT add 1 HERO from GY to hand. */
- `DESTINY_HERO_DENIER` (activated): L189: GY SS when other D-HERO present needs GY/once-per-duel hooks. Ceiling: OPT put 1 D-HERO from Deck/GY/banished on top of Deck.
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. Ceiling: OPT destroy 1 you control + 1 other field card.
- `DESTINY_HERO_DISK_COMMANDER` (activated): L20: SS-from-GY trigger + once per duel. Ceiling: OPT draw 2 stand-in when on field; upgrade: GY SS dispatch + EFFECT_USAGE_ONCE.
- `DESTINY_HERO_DREADNOUGHT_MASTER` (activated): L60: SS trigger → OPT ignition; cards-mentioning-D-HERO FALSE. Ceiling: OPT add up to 2 Destiny HERO from Deck.
- `DESTINY_HERO_DRILLDARK` (activated): L65: * Ceiling: OPT SS 1 D-HERO from hand with ATK≤ this card's ATK. */
- `DESTINY_HERO_DYSTOPIA` (activated): L203: on-SS burn + Quick destroy-if-ATK-changed need summon/ATK hooks. Ceiling: OPT pick Lv≤4 D-HERO in GY → burn its ATK.
- `DIVINER_OF_THE_HERALD` (activated): L89: on-NS/SS mill + tribute SS Fairy need summon/tribute hooks. OPT send 1 Fairy from Deck to GY (+unkTwo Level stand-in until EP clear).
- `EBON_ILLUSION_MAGICIAN` (activated): L78: Xyz detach cost + attack-banish FALSE. Ceiling: OPT SS Spellcaster Normal from hand/Deck (detach stand-in).
- `EL_SHADDOLL_MESHAHRAIL` (activated): L74: unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks. Ceiling: OPT pay 800 → add 1 Shaddoll or Void S/T from Deck.
- `ELDER_ENTITY_NORDEN` (activated): L124: SS-trigger timing + banish-when-leaves need summon/leave hooks. Ceiling: OPT SS Lv≤4 from GY face-up DEF with unk4 negated mark.
- `ELEMENTAL_HERO_AQUA_NEOS` (activated): L20: /* EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT discard 1, then destroy 1
- `ELEMENTAL_HERO_GLOW_NEOS` (activated): L115: * via ElementalHeroGlowNeos_* attack gates. Ceiling: OPT destroy 1 face-up
- `ELEMENTAL_HERO_GRAND_NEOS` (activated): L95: /* EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT bounce 1 opponent monster
- `ELEMENTAL_HERO_MAGMA_NEOS` (activated): L42: /* EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT refresh
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. Ceiling: OPT destroy opp cards up to different Attributes.
- `ELEMENTAL_HERO_SPIRIT_OF_NEOS` (activated): L154: attack-hand SS FALSE. Ceiling: OPT search Poly/E-HERO S/T, else OPT shuffle self → SS Normal E-HERO from Deck.
- `ELEMENTAL_HERO_STORM_NEOS` (activated): L86: /* EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT destroy all
- `ENLIGHTENMENT_DRAGON` (activated): L139: * Ceiling: OPT pay 2000 → banish all other field+both GYs, else OPT mill 4.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L86: once-per-turn not tracked without turn hook.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L109: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE. Ceiling: OPT mill 1 HERO from Deck.
- `EVIL_HERO_MALICIOUS_BANE` (activated): L75: destruction immunity + HERO-only attack gate need destroy/attack hooks. Ceiling: OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4.
- `EVIL_HERO_TOXIC_BUBBLE` (activated): L39: HERO-only SS lock + once-per-turn not tracked without turn hook.
- `FORMULA_SYNCHRON` (activated): L33: * synchro/chain hooks. Ceiling: OPT draw 1 via usage when deck remains. */
- `GANDORA_G_THE_DRAGON_OF_DESTRUCTION` (activated): L152: * Ceiling: OPT pay half LP → banish all other field → SS Lv≤7 Sarc mention. */
- `GATE_GUARDIANS_COMBINED` (activated): L103: * Ceiling: OPT destroy 1 opp card (negate stand-in). */
- `GLADIATOR_BEAST_ANDABATA` (activated): L158: OPT tag-out → SS 2 different GB from Deck.
- `GLADIATOR_BEAST_ATTORIX` (activated): L133: * Ceiling: OPT send 1 other GB from Deck to GY (unkTwo name copy) or tag-out. */
- `GLADIATOR_BEAST_AUGUSTUS` (activated): L48: OPT SS 1 other GB from hand in DEF.
- `GLADIATOR_BEAST_CLAUDIUS` (activated): L61: OPT SS Gladiator Beast from Deck (opp effect stand-in).
- `GLADIATOR_BEAST_DAREIOS` (activated): L179: OPT SS Lv≤4 GB from hand/GY, or any GB from Deck if opp has monster.
- `GLADIATOR_BEAST_DOMITIANUS` (activated): L133: OPT tag-out → SS 1–2 GB from Deck.
- `GLADIATOR_BEAST_DRAGASES` (activated): L157: OPT GB tag-out → SS 2 different from Deck.
- `GLADIATOR_BEAST_GISTEL` (activated): L162: OPT search Gladiator S/T, else tag-out. FromHand: reveal+SS both.
- `GLADIATOR_BEAST_HERAKLINOS` (activated): L148: either-turn chain negate needs chain hook. OPT discard 1 → destroy 1 opponent card below.
- `GLADIATOR_BEAST_LANISTA` (activated): L157: * Ceiling: OPT banish 1 GB from GY (unkTwo name copy) or tag-out. */
- `GLADIATOR_BEAST_NOXIOUS` (activated): L130: OPT mill 1 GB from Deck, else tag-out.
- `GLADIATOR_BEAST_SAGITTARII` (activated): L112: * Ceiling: OPT shuffle self into Deck then SS another Gladiator Beast from Deck.
- `GLADIATOR_BEAST_TAMER_EDITOR` (activated): L70: OPT SS Lv≥5 GB from Deck (Extra stand-in).
- `GLADIATOR_BEAST_VESPASIUS` (activated): L121: OPT tag-out shuffle→SS.
- `GRAVEKEEPERS_CHIEF` (activated): L187: * immunity need summon/continuous hooks. Ceiling: OPT SS GK from GY. */
- `GRAVEKEEPERS_HEADMAN` (activated): L96: * Ceiling: OPT SS 1 Lv4 Gravekeeper's from GY in ATK. */
- `GRAVEKEEPERS_ORACLE` (activated): L94: * Ceiling: OPT destroy up to 2 cards on opp field. */
- `GRAVEKEEPERS_SUPERNATURALIST` (activated): L58: * Ceiling: OPT add Gravekeeper or Necrovalley from Deck now (EP add stand-in). */
- `GRAVEKEEPERS_VISIONARY` (activated): L89: * destroy-replace needs destroy gate. Ceiling: OPT discard GK stand-in. */
- `GUARDIAN_DREADSCYTHE` (activated): L171: * Ceiling: OPT equip/add Reaper Scythe from Deck. */
- `HARPIE_HARPIST` (activated): L124: NS trigger + GY End Phase search need separate hooks. OPT bounce own WB + opp face-up, else OPT add Harpie from Deck.
- `JAIN_TWILIGHTSWORN_GENERAL` (activated): L229: other-Lightsworn-activated mill 2 needs chain hook. OPT banish 1 Lightsworn from hand/GY → weaken 1 face-up monster. EP mill 2 via TryApplyTwilightswornEndPhase.
- `JUNK_SYNCHRON` (activated): L124: * Ceiling: field OPT repeat (usage-gated below). */
- `KEEPER_OF_DRAGON_MAGIC` (activated): L186: * Ceiling: OPT discard → add Poly/Fusion Normal; else OPT SS any from GY face-down DEF. */
- `LADY_OF_D` (activated): L88: /* Dragon attack lock via LadyOfD_CanAttackMonsterZone. Ceiling: OPT discard
- `LEGENDARY_KNIGHT_CRITIAS` (activated): L100: * hooks. Ceiling: OPT banish 1 face-up Spell/Trap on the field. */
- `LEGENDARY_KNIGHT_HERMOS` (activated): L100: * summon/battle hooks. Ceiling: OPT banish 1 face-up Spell/Trap. */
- `LEGENDARY_KNIGHT_TIMAEUS` (activated): L100: * hooks. Ceiling: OPT banish 1 face-up Spell/Trap on the field. */
- `LIFE_STREAM_DRAGON` (activated): L29: * destruction-replace need synchro/LP/battle hooks. Ceiling: OPT set LP to
- `LIGHTRAY_GEARFRIED` (activated): L195: * Ceiling: OPT banish Warrior GY → destroy 1 S/T. */
- `LORD_OF_THE_RED` (activated): L116: * Ceiling: OPT destroy 1 monster on the field. */
- `LYLA_LIGHTSWORN_SORCERESS` (activated): L125: * Ceiling: OPT from face-up ATK → face-up DEF, destroy 1 opp S/T. */
- `LYLA_TWILIGHTSWORN_ENCHANTRESS` (activated): L205: quick effect on Spell/Trap activation + mill 3 when other LS activates need chain hooks. OPT banish LS from hand/GY then destroy 1 face-up Spell/Trap. EP mill 3 via TryApplyTwilightswornEndPhase.
- `MA_AT` (activated): L134: /* name-3 excavate UI hard. Ceiling: OPT reveal top 3, add any, mill rest. */
- `MAGICAL_MARIONETTE` (activated): L119: * Ceiling: OPT remove 2 unk4 counters → destroy 1 monster. */
- `MAGICIANS_SOULS` (activated): L144: * GY hooks. Ceiling: OPT send 1–2 S/T from hand/field → draw that many. */
- `MAJESTY_HYPERION` (activated): L367: * Ceiling: OPT banish Fairy hand/GY → destroy 1 card. FromHand banish Agent → SS. */
- `MASTER_OF_CHAOS` (activated): L205: * hooks. Ceiling: OPT SS LIGHT/DARK from GY, else tribute LIGHT+DARK → banish. */
- `MASTER_PEACE_THE_TRUE_DRACOSLAYING_KING` (activated): L112: * Ceiling: OPT banish 1 other field card (Quick destroy stand-in). */
- `MASTERFLARE_HYPERION` (activated): L238: * Ceiling: OPT mill Agent/Sanctuary-mention, else OPT banish Fairy → destroy 1. */
- `MILLENNIUM_EYES_RESTRICT` (activated): L89: * Ceiling: OPT destroy 1 opp monster. */
- `MINERVA_LIGHTSWORN_MAIDEN` (activated): L125: * Ceiling: field OPT search LIGHT Dragon Lv≤ distinct LS names in GY. */
- `MINERVA_THE_ATHENIAN_LIGHTSWORN` (activated): L185: * Ceiling: OPT mill LS different Types (up to field LS count), or banish ≤4 LS GY → mill. */
- `MINERVA_THE_EXHALTED_LIGHTSWORN` (activated): L69: /* Xyz detach + destroy-on-death FALSE. Ceiling: OPT mill 3 → draw = Lightsworn
- `MORPHTRONIC_CELFON` (activated): L136: reveal/look UI missing; die roll + SS/add among top N. Ceiling: ATK OPT die→SS Lv≤4 Morphtronic; DEF OPT die→add Morphtronic.
- `MORPHTRONIC_EARFON` (activated): L48: real Tuner flag / Equip double-attack need Synchro/equip hooks. Ceiling: OPT PickZone mark unk4 as Tuner stand-in.
- `MORPHTRONIC_EARFON` (activated): L95: on-SS Tuner mark + Equip 2-attacks FALSE. Ceiling: OPT PickZone treat face-up as Tuner (unk4).
- `MORPHTRONIC_REMOTEN` (activated): L213: position-gated OPT search. ATK: banish GY Morphtronic → add same Lv. DEF: discard Morphtronic → add other same Lv.
- `MORPHTRONIC_SCANNEN` (activated): L194: FromHand banish Morphtronic → SS; ATK/DEF OPT search modes.
- `MORPHTRONIC_SCOPEN` (activated): L58: DEF Position → treat as Level 4 + EP destroy on ATK-mode SS need position/EP hooks; ATK Position OPT SS 1 Lv4 Morphtronic from hand.
- `MORPHTRONIC_SLINGEN` (activated): L160: DEF destroy-other-Morphtronic substitute needs destroy redirect hook. Ceiling: ATK OPT tribute 1 other Morphtronic → destroy 1 field card.
- `MORPHTRONIC_VACUUMEN` (activated): L24: send Equip → burn + DEF equip-take-control need equip hooks. Ceiling: ATK Position OPT burn 500.
- `NAELSHADDOLL_ARIEL` (activated): L73: * Ceiling: OPT banish up to 3 cards from either GY. */
- `NECROFACE` (activated): L87: * hooks. Ceiling: OPT shuffle all banished into Decks + tempStage per card. */
- `NEHSHADDOLL_GENIUS` (activated): L111: * Ceiling: OPT negate 1 face-up Effect Monster (unk4). */
- `NEO_SPACE_CONNECTOR` (activated): L62: * summon/tribute hooks. Ceiling: OPT SS Neo-Spacian or Neos from Deck DEF. */
- `NITRO_WARRIOR` (activated): L97: * Ceiling: OPT change 1 face-up DEF opp monster to ATK (battle-after stand-in). */
- `ORICHALCOS_SHUNOROS` (activated): L125: * Ceiling: OPT +2 tempStage per opp monster (~1000 ATK each). */
- `POWER_TOOL_BRAVER_DRAGON` (activated): L100: * Ceiling: OPT change battle position of 1 monster. */
- `POWER_TOOL_DRAGON` (activated): L56: * hooks. Ceiling: OPT add first Equip Spell from Deck. */
- `PROTECTOR_OF_THE_AGENTS_MOON` (activated): L305: /* Link Summon trigger gate missing. Ceiling: OPT mill/add Sanctuary
- `QADSHADDOLL_KEIOS` (activated): L51: * hooks. Ceiling: OPT SS 1 Shaddoll from hand face-up DEF. */
- `RAIDEN_HAND_OF_THE_LIGHTSWORN` (activated): L61: /* EP mill via TryApplyRaidenEndPhase. Ceiling: Main Phase OPT mill 2. */
- `REESHADDOLL_WENDI` (activated): L60: * Ceiling: OPT SS 1 other Shaddoll from Deck face-up DEF. */
- `REESHADDOLL_WENDIKURUHU` (activated): L74: * hooks. Ceiling: OPT flip all face-down monsters face-up DEF. */
- `REPTILIANNE_ECHIDNA` (activated): L231: * Ceiling: OPT set 1 opp face-up ATK to 0, else OPT add Reptiles up to 0-ATK count.
- `REPTILIANNE_VASKII` (activated): L192: * Ceiling: OPT destroy 1 face-up opp monster. */
- `RYKO_TWILIGHTSWORN_FIGHTER` (activated): L191: NS/flip + other-Lightsworn mill 3 need summon/chain hooks. OPT banish LS from hand/GY then banish 1 field card; EP mill 3 via TryApplyTwilightswornEndPhase.
- `SHADDOLL_BEAST` (activated): L21: * Ceiling: OPT draw 1 stand-in for GY effect only; upgrade: flip + GY hooks. */
- `SHADDOLL_FALCO` (activated): L116: * Ceiling: OPT SS 1 other Shaddoll from GY face-down DEF. */
- `SHADDOLL_HEDGEHOG` (activated): L113: * Ceiling: OPT search 1 Shaddoll S/T or monster from Deck once via usage. */
- `SHADDOLL_HOUND` (activated): L94: * Ceiling: OPT add 1 Shaddoll from GY to hand. */
- `SILENT_MAGICIAN_LV4` (activated): L152: * Ceiling: OPT send self → SS LV8 from hand/Deck. */
- `SIMORGH_BIRD_OF_ANCESTRY` (activated): L111: * summon/permanent hooks. Ceiling: OPT return up to 2 opp cards to hand. */
- `TEST_BEAR` (activated): L238: * Ceiling: OPT tribute self + shuffle 1 GB → SS up to 2 GB from Deck. */
- `TEST_PANTHER` (activated): L200: * Ceiling: OPT search GB from Deck, else bounce GB → SS different GB. */
- `THE_AGENT_OF_DESTRUCTION_VENUS` (activated): L193: * Ceiling: OPT pay 500×N → SS N Mystical Shine Ball from banished/GY. */
- `THE_AGENT_OF_MYSTERU_EARTH` (activated): L110: OPT add 1 The Agent except Earth from Deck, or Master Hyperion if Sanctuary is face-up.
- `THE_EXECUTOR_OF_THE_UNDERWORLD_PLUTO` (activated): L164: * Ceiling: OPT banish 1 monster from GY → flip 1 Effect Monster face-down DEF. */
- `THE_LEGENDARY_EXODIA_INCARNATE` (activated): L126: * Ceiling: OPT add Forbidden One from GY. FromHand tribute Forbidden One → SS. */
- `THEINEN_THE_GREAT_SPHINX` (activated): L40: * Ceiling: OPT pay 500 → +7 tempStage (~3000 ATK). */
- `THESTALOS_THE_FIRESTORM_MONARCH` (activated): L111: * Ceiling: field OPT repeat (usage-gated below). */
- `THUNDER_DRAGON_TITAN` (activated): L103: * chain/continuous hooks. Ceiling: OPT destroy 1 card on the field. */
- `TIMAEUS_THE_KNIGHT_OF_DESTINY` (activated): L54: * Ceiling: OPT set ATK/DEF ≈ highest field ATK via tempStage. */
- `TIME_THIEF_REDOER` (activated): L141: * Ceiling: OPT draw 1 OR return 1 face-up opp monster to Deck. */
- `TOADALLY_AWESOME` (activated): L213: * Ceiling: OPT SS Frog from Deck, else OPT send Aqua → destroy 1 opp. */
- `TOHUSHADDOLL_GRYSTA` (activated): L23: * Ceiling: OPT add Shaddoll Fusion from Deck. */
- `TUALATIN` (activated): L109: * Ceiling: OPT destroy all face-up monsters of first opp monster's Attribute. */
- `TURBO_BOOSTER` (activated): L102: * battle-tracking hook. Ceiling: OPT tribute self then destroy 1 opponent
- `ULTIMATE_CONDUCTOR_TYRANNO` (activated): L195: * Ceiling: OPT destroy 1 of your monsters → flip all opp face-up monsters face-down DEF. */
- `VISION_HERO_FARIS` (activated): L148: Continuous Trap place + ED HERO lock need place/ED hooks. OPT add 1 Vision HERO from Deck to hand wired below.
- `VISION_HERO_GRAVITO` (activated): L113: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip zone API. Ceiling: OPT add 1 banished HERO monster to hand.
- `VISION_HERO_INCREASE` (activated): L69: GY Continuous Trap place + tribute HERO SS-self FALSE. OPT SS Vision HERO Lv≤4 from Deck (ST-zone SS stand-in).
- `WEISS_LIGHTSWORN_ARCHFIEND` (activated): L167: /* sent-from-Deck-to-GY trigger needs mill/send hook. Ceiling: field OPT
- `WHITE_HORNED_DRAGON` (activated): L79: OPT banish up to 5 opp GY Spells + tempStage once via usage.

## `event.GyIgnition` (9)

- `DESTINY_HERO_DREADNOUGHT_SERVANT` (activated): L89: GY banish destroy on Lv8 D-HERO SS FALSE. Ceiling: FromHand if control D-HERO or Field Spell → SS, destroy 1, add Poly.
- `DESTINY_HERO_DREAMER` (activated): L52: * Ceiling: banish-on-leave need GY hook. Ceiling: GY ignition SS. */
- `DESTINY_HERO_DYNATAG` (activated): L134: GY banish ATK boost not wired; both players 1000 on FromHand.
- `DESTINY_HERO_MALICIOUS` (activated): L43: GY ignition needs GY-menu wire. Ceiling: allow when Malicious in GY + another in Deck (callable if gMonEffect set to Malicious).
- `EVIL_HERO_SINISTER_NECROM` (activated): L103: GY ignition needs GY-menu wire; allow when Sinister Necrom in GY + Evil HERO in hand or Deck (callable if gMonEffect set).
- `LEVEL_EATER` (activated): L178: * GY-menu + tribute hooks. Ceiling: GY ignition when Lv5+ you control + empty
- `MEZUKI` (activated): L169: /* GY ignition needs GY-menu wire. Ceiling: allow when Mezuki +
- `POSEIDRA_THE_ATLANTEAN_DRAGON` (activated): L284: /* hand SS uses FromHand path. Ceiling: GY ignition like Malicious. */
- `YAMORIMORI` (activated): L124: /* GY ignition needs GY-menu wire. Ceiling: banish self from GY +

## `event.OnLpGain` (3)

- `AMAZONESS_HALL` (trap): L43: * Ceiling: Extra Deck / Pendulum place + opp SS gain LP need hooks. */
- `AROMAGE_BERGAMOT` (activated): L22: * Ceiling: LP-gain gate need permanent/LP hooks.
- `AROMAGE_CANANGA` (activated): L175: * Ceiling: LP-gain bounce trigger needs LP hook.

## `extra.XyzLinkSynchro` (17)

- `SHADDOLL_CORE` (trap): L45: true trap-monster (still a Trap) + Attribute fusion substitute need Embodiment-style link; place SHADDOLL_CORE on monster row and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate.
- `URGENT_TUNING` (trap): L14: Synchro Summon during Battle Phase needs Synchro material/ED summon path outside this file (no in-file Synchro API). → Extra Deck Synchro SS.
- `CRIMSON_DRAGON` (activated): L123: Extra Deck Synchro SS FALSE; Deck Dragon stand-in.
- `CYBER_DRAGON_INFINITY` (activated): L62: Xyz attach / negate FALSE. Ceiling: ClearZone absorb + +1 tempStage.
- `GAGAGIGO_THE_RISEN` (activated): L12: Gagagigo the Risen has no printed monster effect (Xyz materials only). duel gate outside activated_effects.
- `LEVEL_EATER` (activated): L122: * Ceiling: SS self from GY; upgrade: TempLevel overlay on target. */
- `LEVIAIR_THE_SEA_DRAGON` (activated): L108: * Ceiling: materials not checked; upgrade: overlay detach before SS. */
- `NUMBER_39_UTOPIA` (activated): L13: * hook and XYZ material system. Ceiling: not field-ignition activatable. */
- `ROAD_SYNCHRON` (activated): L13: * synchro/battle hooks. Ceiling: not ignition-activatable here. */
- `T_G_HYPER_LIBRARIAN` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: synchro summon gate. */
- `TATSUNOKO` (activated): L13: * synchro/summon continuous hooks. Ceiling: not field-ignition here. */
- `THUNDER_END_DRAGON` (activated): L60: * Ceiling: materials not checked; upgrade: overlay detach before destroy. */
- `TRISHULA_DRAGON_OF_THE_ICE_BARRIER` (activated): L114: /* Synchro Summon trigger needs synchro hook. Ceiling: once via usage banish
- `TUNINGWARE` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: synchro summon gate. */
- `ELEMENTAL_HERO_ELECTRUM` (permanent): L67: no removed-from-play zone yet — shuffle banished/exiled monsters back into each owner's deck once Duel_BanishZone exists. ATK overlay via ElementalHeroElectrum_ApplyDynamicZoneStats.
- `ELEMENTAL_HERO_THE_SHINING` (permanent): L64: return up to 2 banished E-HEROes to hand deferred — no multi-RFP return UI yet. ATK overlay via ElementalHeroTheShining_ApplyDynamicZoneStats.
- `HARPIES_PET_PHANTASMAL_DRAGON` (permanent): L9: * Ceiling: Harpie protect + End Phase detach need battle/xyz hooks. */

## `chain.Negate` (14)

- `ANCIENT_GEAR_ENGINEER` (activated): L14: * Ceiling: opp Trap activation negate on attack needs chain gate. */
- `ARCANA_KNIGHT_JOKER` (activated): L12: discard matching type to negate activation needs chain/response hooks. Ceiling: not ignition-activatable here.
- `ASH_BLOSSOM_AND_JOYOUS_SPRING` (activated): L50: chain negate for add/SS/mill from Deck not wired; upgrade: chain interrupt hook when one exists.
- `DESTINY_HERO_DARK_ANGEL` (activated): L81: field spell-negate FALSE. Ceiling: FromHand discard → SS D-HERO to opp DEF.
- `DESTINY_HERO_DESTROY_DOGMA` (activated): L104: * destroy/negate FALSE. Ceiling: FromHand banish 3 Warrior/DARK → SS + burn 2000. */
- `DESTINY_HERO_PLASMA` (activated): L95: equip/absorb + half-ATK boost + continuous opp negate need equip hooks. Ceiling: destroy 1 opp monster.
- `DIVINE_SERPENT_GEH` (activated): L41: * Ceiling: destroy gate + battle negate need destroy/battle hooks.
- `GODDESS_BOW` (activated): L13: * fusion/equip/chain hooks. Ceiling: not ignition-activatable here. */
- `HORUS_THE_BLACK_FLAME_DRAGON_LV8` (activated): L13: * Ceiling: either-turn Spell negate needs chain hook. */
- `ILLUSION_OF_CHAOS` (activated): L135: /* field bounce→SS DM negate FALSE. Ceiling: FromHand search only. */
- `SILENT_SWORDSMAN_ZERO` (activated): L47: * tempStage unchanged. Ceiling: Sarcophagus negate needs chain hook. */
- `ARCANA_FORCE_EX_THE_LIGHT_RULER` (permanent): L100: Tails negate FALSE; Heads only when GY→hand legal.
- `EL_SHADDOLL_GRYSTA` (permanent): L126: negate opp Special Summon + send Shaddoll from hand need SS chain hook.
- `EL_SHADDOLL_SHEKHINAGA` (permanent): L126: negate SS monster effect + send Shaddoll need effect-chain hook.

## `gate.Tribute` (14)

- `LEV_SHADDOLL_FUSION` (spell): L158: the face-up ignition still needs a monster-zone tribute picker and an Extra Deck special-summon flow, neither of which is owned by this spell activation dispatcher.
- `SCAPEGOAT` (spell): L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. SCAPEGOAT_TOKEN_ID / token flag.
- `ANDRO_SPHINX` (activated): L64: * Ceiling: GY SS ban needs summon gate. */
- `AROMASERAPHY_JASMINE` (activated): L216: * Ceiling: tribute 1 you control → SS Plant from Deck. */
- `FELIS_LIGHTSWORN_ARCHER` (activated): L102: * hook. Ceiling: ignition tribute self → destroy 1 opponent monster → mill 3. */
- `FLAME_RULER` (activated): L12: treat as 2 Tributes for FIRE Tribute Summon needs tribute-cost LynJump. gate outside this file.
- `FOG_KING` (activated): L13: * lock need summon/tribute continuous hooks. Ceiling: not field-ignition here. */
- `GAMECIAL_THE_SEA_TURTLE_KAIJU` (activated): L69: * Ceiling: FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju). */
- `GRAVEKEEPERS_VASSAL` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle
- `HELSHADDOLL_HOLLOW` (activated): L109: /* FLIP Extra mill + GY attribute mill need flip/send hooks. Ceiling:
- `HOLACTIE_THE_CREATOR_OF_LIGHT` (activated): L65: * Ceiling: not field-ignition activatable; use FromHand tribute path. */
- `LEKUNGA` (activated): L13: * Ceiling: wrong Type/Attribute/stats (Fairy/LIGHT 0/0 vs Plant/WATER 700/700);
- `THE_AGENT_OF_JUDGMENT_SATURN` (activated): L39: /* skip Battle Phase this turn needs phase-lock hook. Ceiling: tribute
- `ARCANA_FORCE_VI_THE_LOVERS` (permanent): L48: tribute engine not wired — unk4 marks double-tribute / no-tribute only.

## `stat.Continuous` (1)

- `EVIL_HERO_MALICIOUS_BANE` (activated): L105: +200 ATK each via tempStage (~500/unit); attack lock only marks self unk4.

## `ui.Choice` (5)

- `AMULET_DRAGON` (activated): L58: no multi-select GY UI — banish every Spell in both GYs (min.1 gate above).
- `ARCANA_FORCE_XII_THE_HANGMAN` (activated): L166: coin targeting uses auto-pick highest ATK; upgrade: PickZone.
- `BRIONAC_DRAGON_OF_THE_ICE_BARRIER` (activated): L232: N-discard path auto-bounces N cards; upgrade: sequential PickZone.
- `DARK_ARMED_DRAGON` (activated): L317: auto-target. No GY picker (DeckMenu screen switch corrupts VRAM from inside monster effect handler) and no PickZone cursor state (200 conflicts with game loop after MonsterActionMenu case 4 returns). Picks the best field target via AiPickTarget logic. Upgrade path: dedicated cursor state + A/B handlers like Cannon Soldier.
- `OJAMA_KING` (activated): L54: PickZone for up to 3 empty zones + continuous lock gate. FirstEmptyZoneInRow today — same as Ground Collapse).

## `op.Search` (7)

- `SPELL_CHRONICLE` (spell): L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished; cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.
- `HARPIE_LADY_ELEGANCE` (trap): L49: * Ceiling: destroy-search Harpie Spell need hooks. */
- `ATLANTEAN_DRAGOONS` (activated): L137: * Ceiling: sent-for-WATER-effect search needs send hook.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L63: cannot attack without Fusion Monster needs attack gate. Not field-ignition activatable; discard search uses FromHand path.
- `GRAVEKEEPERS_AMBUSHER` (activated): L146: /* flip trigger + Necrovalley search need flip/send hooks. Ceiling:
- `SHADDOLL_SQUAMATA` (activated): L155: * Ceiling: destroy 1 opp monster OR mill 1 Shaddoll from Deck once via usage. */
- `ELEMENTAL_HERO_FLASH` (permanent): L47: no banished-zone + no multi-card GY search yet — banish 3 E-Heroes and add Normal Spell from GY deferred until banish + GY targeting exist. Battle-destruction GY trigger wired above.

## `op.BanishTimed` (8)

- `SPELL_CHRONICLE` (spell): L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn; briefly hits GY; upgrade: direct deck→RFG.
- `ANCIENT_GEAR_DUEL` (trap): L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks; mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand-in from Deck/hand.
- `ANGELS_TEAR` (trap): L342: need 4 banish targets plus 1 summon target.
- `BEAST_MACHINE_KING_BARBAROS_UR` (activated): L224: multi-zone banish picker not wired; require both types reachable.
- `HERALD_OF_THE_ARC_LIGHT` (activated): L13: * Ceiling: not field-ignition activatable here; upgrade: continuous banish +
- `MICHAEL_THE_ARCH_LIGHTSWORN` (activated): L140: * Ceiling: pay 1000 LP → banish 1 field card. */
- `MORPHTRONIC_SMARTFON` (activated): L228: reveal UI FALSE; ATK die excavate add; DEF GY add Morphtronic. FromHand: banish Morphtronic GY → SS.
- `DESTINY_HERO_DOOM_OVERLORD` (permanent): L327: banish-until-Standby = permanent banish; DARK HERO SS lock not wired.

## `other` (98)

- `FUSION_DESTINY` (spell): L34: * Ceiling: incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous,
- `FUSION_DESTINY` (spell): L36: * Ceiling: Destiny End Dragoon only; upgrade: add remaining Destiny HERO Fusion
- `SCAPEGOAT` (spell): L10: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. SHEEP_TOKEN card data + art, then swap this define.
- `SCAPEGOAT` (spell): L74: LockMonsterCardsInRow also blocks Normal Set of monsters. distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.
- `SECRETS_OF_DARK_MAGIC` (spell): L34: * Ceiling: incomplete vs printed DM Fusion pool (Dragon Knight, etc.).
- `SECRETS_OF_DARK_MAGIC` (spell): L35: * Ceiling: Amulet Dragon + The Dark Magicians only; upgrade: add remaining DM
- `SPELL_GEAR` (spell): L156: * Ceiling: optional SS offered as auto-yes when legal; cannot skip
- `DARK_SUPREMACY` (trap): L38: "Spells that mention Dark Fusion" not scanned by text.
- `FAVOURITE_CONTACT` (trap): L48: Extra Deck Fusion ignoring summon conditions + materials to Deck bottom need fusion recipe API; return up to 2 HERO/Neos/ Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free.
- `AMAZONESS_PRINCESS` (activated): L65: * Ceiling: battle-declare send→SS need battle hook. */
- `ANCIENT_GEAR_GADJILTRON_CHIMERA` (activated): L13: * Ceiling: not ignition-activatable. */
- `ARCANA_FORCE_V_THE_HIEROPHANT` (activated): L189: discard only; opp cannot respond to Arcana Summons needs turn flag hook.
- `ARCANA_FORCE_XIX_THE_SUN` (activated): L137: requires coin-toss card on field — skipped; SS anytime when legal.
- `ATLANTEAN_MARKSMAN` (activated): L149: * Ceiling: sent-for-WATER destroy Set S/T needs send hook. */
- `CHIMERATECH_FORTRESS_DRAGON` (activated): L13: * Ceiling: not field-ignition activatable here. */
- `CHIMERATECH_MEGAFLEET_DRAGON` (activated): L13: * Ceiling: not field-ignition activatable here. */
- `CLEAR_VICE_DRAGON` (activated): L72: * Ceiling: Clear World immunity + discard-to-save need continuous/destruction hooks.
- `CLEAR_VICE_DRAGON` (activated): L73: * Ceiling: not ignition-activatable here. */
- `CROSS_KEEPER` (activated): L145: GY draw-on-E-HERO-Fusion need Fusion/GY hooks. Ceiling: send self → SS Elemental HERO or Neo-Spacian from hand/GY.
- `DARK_ARMED_DRAGON` (activated): L174: allow self-target for faithful TCG simulation; player can choose suboptimally
- `DARK_MAGICIAN_THE_DRAGON_KNIGHT` (activated): L65: * Ceiling: not ignition-activatable here. */
- `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS` (activated): L35: * Ceiling: not field-ignition; FromHand if Shining Sarcophagus. */
- `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC` (activated): L35: * Ceiling: not field-ignition; FromHand if Shining Sarcophagus. */
- `DARK_STRIKE_FIGHTER` (activated): L127: Main Phase 1 gate not wired; allow once via usage any main phase.
- `DARKBLAZE_DRAGON` (activated): L83: * Ceiling: GY SS double original ATK/DEF needs SS-origin flag. */
- `DARKNESS_NEOSPHERE` (activated): L87: battle indestruct + trap bounce + attack-declare gate need battle/ phase hooks. Ceiling: not field-ignition activatable; SS uses FromHand path.
- `DARKNESS_NEOSPHERE` (activated): L113: opp attack declare gate not wired; require 1 field + 1 hand Fiend.
- `DESTINY_HERO_CELESTIAL` (activated): L155: * Ceiling: GY draw-if-no-hand need GY hooks.
- `DESTINY_HERO_DECIDER` (activated): L114: /* EP add on NS/SS via TryApplyDestinyHeroDeciderEndPhase. Ceiling: GY quick
- `DESTINY_HERO_DESTROY_DOGMA` (activated): L103: /* Standby burn via TryApplyDestinyHeroDestroyDogmaStandby. Ceiling: Quick
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L154: second target picker not chained; auto-destroy best remaining card.
- `DESTINY_HERO_DIAMOND_DUDE` (activated): L57: next-turn GY Normal Spell activation needs Main Phase hook.
- `DESTINY_HERO_DOMINANCE` (activated): L66: look+reorder UI missing; RandRange shuffle of top N is stand-in.
- `DIVINE_SERPENT_GEH` (activated): L42: * Ceiling: field ignition FALSE. */
- `EL_SHADDOLL_WENDIGO` (activated): L110: * Ceiling: GY add Shaddoll S/T on send not wired. */
- `ELEMENTAL_HERO_CHAOS_NEOS` (activated): L241: 3H Set-all needs set-from-deck hook; 2H/3H both shuffle all.
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L177: multi-target picker not wired; auto-destroy highest-value opp cards.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L151: Dark Fusion Fusion markers missing; any Fusion Monster stand-in.
- `EVIL_HERO_VICIOUS_CLAWS` (activated): L96: +300 ≈ +1 tempStage (~500).
- `EVOLZAR_DOLKKA` (activated): L13: * Ceiling: not field-ignition here. */
- `FUSILIER_DRAGON_THE_DUAL_MODE_BEAST` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon
- `GORZ_THE_EMISSARY_OF_DARKNESS` (activated): L35: * Ceiling: FromHand empty-field SS. */
- `GRANMARG_THE_ROCK_MONARCH` (activated): L159: * Ceiling: once via usage if Set target. */
- `GRAVEKEEPERS_CURSE` (activated): L20: /* printed is If Summoned trigger. Ceiling: allow once via usage
- `GRAVEKEEPERS_SPIRITUALIST` (activated): L13: * summon API. Ceiling: not ignition-activatable here. */
- `GRAVEKEEPERS_WATCHER` (activated): L16: * hooks. Ceiling: not field-ignition; discard-from-hand path below. */
- `GREAT_POSEIDON_BEETLE` (activated): L13: * re-attack hook. Ceiling: not ignition-activatable here. */
- `GREEN_GADGET` (activated): L62: once via usage.
- `HARPIE_CONDUCTOR` (activated): L100: * Ceiling: protect destroy redirect + on-Harpie-return trigger need hooks. */
- `HERALD_OF_PERFECTION` (activated): L13: * Ceiling: not field-ignition activatable here; upgrade: either-turn chain
- `HERALD_OF_ULIMATENESS` (activated): L13: * Ceiling: not field-ignition activatable here; upgrade: either-turn chain
- `HERALD_OF_ULTIMATENESS` (activated): L13: * Ceiling: not field-ignition activatable here; upgrade: either-turn chain
- `JUDGMENT_THE_DRAGON_OF_HEAVEN` (activated): L108: * TryApplyJudgmentEndPhase. Ceiling: pay half LP → destroy all other field cards. */
- `LEVIAIR_THE_SEA_DRAGON` (activated): L63: * Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt. */
- `LIGHTSWORN_DRAGONLING` (activated): L134: /* hand SS when Lightsworn in GY uses FromHand path. Ceiling: field
- `LUMINA_TWILIGHTSWORN_SHAMAN` (activated): L226: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.
- `MAGICAL_PLANT_MANDRAGOLA` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon
- `MAGICAL_SCIENTIST` (activated): L216: * Ceiling: pay 1000 → SS Lv≤6 Fusion from Extra/recipe list. */
- `MAGICIANS_ROBE` (activated): L57: * Ceiling: discard S/T from hand → SS DM from Deck via FromHand path. */
- `MAN_THRO_TRO` (activated): L21: Ojama Trio monster form is the only token-like field unit today
- `MANJU_OF_THE_TEN_THOUSAND_HANDS` (activated): L113: once via usage if Ritual Monster or Ritual Spell in Deck and hand space.
- `MIRROR_FORCE_DRAGON` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: trigger destroy-all. */
- `MOLTEN_ZOMBIE` (activated): L18: printed trigger is SS from GY; once via usage when Activate runs (summon-dispatch or manual).
- `MORPHTRONIC_LANTRON` (activated): L98: * Ceiling: ATK effect-damage redirect needs effect-damage hook. */
- `MORPHTRONIC_TELEFON` (activated): L176: reveal UI FALSE; ATK die→LP+SS Morph Lv≤roll; DEF die excavate add.
- `NATURIA_BEAST` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: either-turn interrupt. */
- `NEO_SPACIAN_DARK_PANTHER` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: permanent/name/effect copy. */
- `NIBIRU_THE_PRIMAL_BEING` (activated): L91: * Ceiling: FromHand wipe+SS if ≥5 face-up monsters on field. */
- `PREDAPLANT_VERTE_ANACONDA` (activated): L130: * hooks. Ceiling: pay 2000 LP → destroy 1 field card. */
- `PUNISHMENT_DRAGON` (activated): L192: * effect-activation hook. Ceiling: pay 1000 → shuffle all banished into Decks. */
- `RAINBOW_DARK_DRAGON` (activated): L265: /* hand SS by banishing 7 different DARK uses FromHand path. Ceiling:
- `REPTILIANNE_LAMIA` (activated): L98: * Ceiling: not field-ignition; FromHand ATK-0 + SS + self-damage. */
- `RINYAN_LIGHTSWORN_ROGUE` (activated): L41: /* FLIP trigger needs flip hook. Ceiling: once via usage if LS in GY. */
- `ROYAL_MAGICAL_LIBRARY` (activated): L23: * Ceiling: ignition only when unk4>=3. */
- `RYKO_LIGHTSWORN_HUNTER` (activated): L107: /* FLIP trigger needs flip hook. Ceiling: once via usage. */
- `SHADDOLL_DRAGON` (activated): L183: /* FLIP vs GY-sent exclusivity + trigger hooks deferred. Ceiling: bounce 1
- `SKILLED_DARK_MAGICIAN` (activated): L81: * Ceiling: ignition when unk4>=3. */
- `SKILLED_WHITE_MAGICIAN` (activated): L81: * Ceiling: ignition when unk4>=3. */
- `SOUL_ABSORBING_BONE_TOWER` (activated): L13: * SS need continuous/SS hooks. Ceiling: not ignition-activatable here. */
- `STARDUST_DRAGON` (activated): L13: * and EP hooks. Ceiling: not ignition-activatable here. */
- `THE_AGENT_OF_LIFE_NEPTUNE` (activated): L161: * Ceiling: FromHand discard self → SS Agent (or Hyperion if Sanctuary). */
- `THE_AGENT_OF_WISDOM_MERCURY` (activated): L21: * Ceiling: once via usage if hand empty; upgrade: standby/end-phase gate. */
- `TIME_MAGIC_HAMMER` (activated): L13: * Ceiling: not field-ignition activatable here. */
- `TIMEAUS_THE_UNITED_DRAGON` (activated): L148: * Ceiling: SS from hand via send cost uses FromHand path. */
- `TORNADO_BIRD` (activated): L85: /* FLIP trigger needs flip hook. Ceiling: once via usage. */
- `TURBO_SYNCHRON` (activated): L13: * hooks. Ceiling: not ignition-activatable here. */
- `TYRANT_BURST_DRAGON` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: permanent battle/equip gate. */
- `ULTIMATE_OBEDIENT_FIEND` (activated): L13: * Ceiling: not field-ignition activatable here. */
- `ULTIMATE_TYRANNO` (activated): L13: * Ceiling: not field-ignition activatable here. */
- `VISION_HERO_GRAVITO` (activated): L64: no RemovedFromPlay_RemoveAt — shift RFP array in place after add. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- `ARCANA_FORCE_I_THE_MAGICIAN` (permanent): L68: spell-trigger heads/tails not wired.
- `ARCANA_FORCE_XVIII_THE_MOON` (permanent): L48: Standby Moon Token / End Phase give-control need turn hooks; unk4 only.
- `ARCANA_FORCE_XXI_THE_WORLD` (permanent): L48: skip-turn / opp GY-to-hand need turn hooks; unk4 marks coin only.
- `DARK_MAGICIAN_OF_DESTRUCTION` (permanent): L131: deck-first add; DM preferred by scan order, no picker.
- `DESTINY_HERO_DRAWHAND` (permanent): L140: HERO-effect SS gate not checked.
- `DESTINY_HERO_DREADMASTER` (permanent): L284: Clock Tower Prison gate skipped. D-HERO battle protect + no BD via DestinyHeroDreadmaster_* while face-up.
- `HERO_KID` (permanent): L76: true trigger is Special Summon of Level 4 or lower HERO.
- `REPTILIANNE_SERVANT` (permanent): L120: * Ceiling: spell-target destroy needs continuous hook. */
