# Partial Effects Taxonomy

Auto-generated companion to [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md).
Each `ponytail:` ceiling is tagged with its **primary missing engine surface** so Phase work in [`effect-data-system.md`](effect-data-system.md) can target events/ops that unblock many cards at once.

```bash
python3 tools/stub_effect_queue.py --write-list
```

**Last updated:** 2026-07-22 16:38 UTC  
**Ceiling lines tagged:** `556`  
**Partial files:** `475`

## Counts by missing surface

| Tag | Count | Suggested phase |
|-----|------:|-----------------|
| `other` | 181 | triage |
| `event.OnStandby` | 168 | 3 (OPT / turn flags) |
| `event.OnSummon` | 60 | 3 |
| `chain.Negate` | 33 | later / chain |
| `gate.Tribute` | 31 | 2–3 |
| `event.OnDestroy` | 16 | 3 |
| `event.OnBattleDestroy` | 14 | 3 |
| `op.Search` | 13 | 1 |
| `op.BanishTimed` | 12 | 1–3 |
| `event.GyIgnition` | 11 | 3 |
| `ui.Choice` | 10 | 2 |
| `stat.Continuous` | 5 | 1–3 |
| `event.OnDamageCalc` | 2 | 3 |
| **total** | **556** | |

Highest-ROI unblock for this backlog is usually **`event.OnStandby` (OPT)** plus destroy/summon/battle listeners (Phase 3), not per-card rewrites.

## `event.OnBattleDestroy` (14)

- `AMAZONESS_HOT_SPRING` (trap): L46: * ponytail: Pendulum Zone place + battle-damage gain LP OPT need hooks. */
- `ARMED_NEOS` (activated): L116: battle-destroy gain Extra tribute SS need battle/Extra hooks. Ceiling: OPT destroy opp monsters with Level ≤ highest Dragon Level in GY.
- `ARMORY_ARM` (activated): L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE.
- `D_D_WARRIOR` (activated): L12: after damage calc banish both needs battle hook. Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle gate outside this file.
- `DESTINY_HERO_CAPTAIN_TENACIOUS` (activated): L92: Standby Phase + battle-destroyed-since-last-Standby filter need phase/destroy hooks. Ceiling: OPT SS 1 D-HERO from your GY.
- `DESTINY_HERO_DOMINANCE` (activated): L89: battle-destroy draw + GY SS 3 D-HERO need battle/destroy hooks. Ceiling: OPT shuffle top 5 of your (else opp) Deck as look+reorder stand-in.
- `GRAVEKEEPERS_VASSAL` (activated): L12: battle damage as effect damage needs battle-damage type gate. Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle gate outside this file.
- `HONEST` (activated): L95: Damage Step hand discard uses FromHand path. Ceiling: Main Phase return this face-up card to the hand.
- `NEO_BLUE_EYES_ULTIMATE_DRAGON` (activated): L79: Damage Step / Fusion-Summon / protect-negate FALSE. Ceiling: OPT send BE Fusion-ish from Deck → unk4 extra-attack mark. (printed up-to-twice; OPT usage flag is the stand-in).
- `TETHYS_GODDESS_OF_LIGHT` (activated): L54: unk18 != 0 means battle/damage resolution is active.
- `TIMAEUS_THE_KNIGHT_OF_DESTINY` (activated): L53: unaffected + once-per-battle damage calc FALSE. Ceiling: OPT set ATK/DEF ≈ highest field ATK via tempStage.
- `TURBO_SYNCHRON` (activated): L12: attack-target DEF change + battle-damage SS from hand need battle hooks. Ceiling: not ignition-activatable here.
- `EVIL_HERO_INFERNO_WING_BACKFIRE` (permanent): L149: HERO battle-destroy 2100 burn needs battle-end hook.
- `EVIL_HERO_WILD_CYCLONE` (permanent): L97: * ponytail: attack S/T lock until end of Damage Step needs chain gate. */

## `event.OnDamageCalc` (2)

- `ELEMENTAL_HERO_CAPTAIN_GOLD` (permanent): L68: with Skyscraper active, prefer normal summon as a 2100 beater
- `TIMEAEUS_THE_UNITED_MAGICAL_DRAGON` (permanent): L121: unaffected-after-SS + battle ATK boost need continuous/battle hooks.

## `event.OnDestroy` (16)

- `SPELL_CHRONICLE` (spell): L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. Ceiling: activate discard+banish 5 only; unk4 counter slot unused.
- `CURIOUS_THE_LIGHTSWORN_DOMINION` (activated): L33: Link Summon mill + leave-field GY add + mill-cascade need summon/ leave-field hooks. Ceiling: OPT mill 1 from Deck.
- `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS` (activated): L33: name=DM + destroy-revive/Set need name/destroy hooks. Ceiling: not field-ignition; FromHand if Shining Sarcophagus.
- `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC` (activated): L33: name=DM + destroy-revive/Set need name/destroy hooks. Ceiling: not field-ignition; FromHand if Shining Sarcophagus.
- `ELDER_ENTITY_NORDEN` (activated): L73: banish-when-leaves needs leave-field hook; unk4 marks negated.
- `EVIL_HERO_DARKEST_KNIGHT` (activated): L90: opp ATK loss by materials + double attack need fusion/battle hooks. Ceiling: OPT SS 1 Fiend/Warrior from GY (leave-field stand-in).
- `EVIL_HERO_VICIOUS_CLAWS` (activated): L46: GY destroy-revive + Dark Fusion destroy branch need GY/destroy hooks. Ceiling: FromHand target HERO → SS DEF +300 ATK stand-in.
- `GATE_GUARDIANS_COMBINED` (activated): L102: negate-on-target + leave-field SS FALSE. Ceiling: OPT destroy 1 opp card (negate stand-in).
- `GLADIATOR_BEAST_DARIUS` (activated): L175: GB-tag SS revive trigger + leave-field shuffle + end-BP tag need summon/leave/battle hooks. Ceiling: OPT SS GB from GY negated, else tag-out.
- `MASTER_OF_CHAOS` (activated): L204: Fusion SS trigger + destroyed GY Spell add need summon/destroy hooks. Ceiling: OPT SS LIGHT/DARK from GY, else tribute LIGHT+DARK → banish.
- `POWER_TOOL_DRAGON` (activated): L55: reveal-3 opp-picks + equip destruction replace need reveal/destroy hooks. Ceiling: OPT add first Equip Spell from Deck.
- `THE_AGENT_OF_DESTRUCTION_VENUS` (activated): L192: leave-field Deck bottom for Shine Balls needs leave hook. Ceiling: OPT pay 500×N → SS N Mystical Shine Ball from banished/GY.
- `THEINEN_THE_GREAT_SPHINX` (activated): L39: Andro+Teleia destroy SS from hand/Deck needs destroy hook. Ceiling: OPT pay 500 → +7 tempStage (~3000 ATK).
- `DEEP_EYES_WHITE_DRAGON` (permanent): L98: Blue-Eyes destroy hand-SS + burn need GY/destroy hooks; on-summon ATK only.
- `GLADIATOR_BEAST_GAIODIAZ` (permanent): L8: battle DEF burn + GB tag-out need battle-end/destroy hooks.
- `GLADIATOR_BEAST_SAMNITE` (permanent): L8: battle search + GB tag-out need battle-end/destroy hooks.

## `event.OnSummon` (60)

- `SHADDOLL_SCHISM` (trap): L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker. Ceiling: banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.
- `AMAZONESS_PRINCESS` (activated): L63: /* On-Summon search via TryAmazonessPrincessOnMonsterPlacement. ponytail:
- `AMULET_DRAGON` (activated): L254: on-summon text after field draw so Amulet Dragon is visible (fusion uses updateGfx=FALSE).
- `ANCIENT_GEAR_DRAGON` (activated): L121: Quick negate + tribute-less NS need negate/summon hooks. Ceiling: OPT send Machine hand/field or AG Golem from Deck to GY.
- `ANCIENT_GEAR_KNIGHT` (activated): L13: * ponytail: Gemini Normal Monster treatment need summon hook. */
- `ARCANA_FORCE_V_THE_HIEROPHANT` (activated): L86: on-Summon coin + discard summon-lock need summon/FromHand paths. Ceiling: OPT coin → SS 1 Arcana Force from Deck.
- `ARCANA_FORCE_XII_THE_HANGMAN` (activated): L139: on-Summon coin should fire at summon; OPT stand-in here. Ceiling: OPT coin → destroy+burn (heads own / tails opp). FromHand SS AF.
- `ARCANA_FORCE_XIX_THE_SUN` (activated): L81: on-Summon coin (Heads Set coin Spell / Tails wipe S/T) need summon hook. Ceiling: OPT coin → flip all opp monsters DEF or destroy half yours.
- `ARCANA_FORCE_XV_THE_FIEND` (activated): L206: on-Summon coin + discard search use summon/FromHand paths. Ceiling: OPT coin → destroy 1 monster or wipe field.
- `AROMAGE_JASMINE` (activated): L57: * ponytail: extra Plant Normal Summon + draw-on-LP-gain need LP/summon hooks.
- `ATHENA` (activated): L71: attack-position summons keep isFaceUp=0 until end-of-turn flip.
- `BEAST_KING_BARBAROS` (activated): L64: no-tribute 1900 ATK + tribute-3 summon gate need summon hooks. Ceiling: once via usage destroy all opp cards (tribute-3 stand-in).
- `BLACK_ROSE_DRAGON` (activated): L158: Synchro Summon destroy-all needs summon hook. Ceiling: OPT banish 1 Plant from GY → opp DEF monster to ATK with 0 ATK (tempStage).
- `CELESTIA_LIGHTSWORN_ANGEL` (activated): L89: Tribute Summon (by Lightsworn) trigger needs summon hook. Ceiling: once via usage — mill 4 then auto-destroy up to 2 opp cards (no player target pick; upgrade: PickZone for up to 2).
- `CHIMERATECH_FORTRESS_DRAGON` (activated): L12: original ATK = 1000 x fusion material count needs fusion/summon stat overlay hook. Ceiling: not field-ignition activatable here.
- `CHIMERATECH_MEGAFLEET_DRAGON` (activated): L12: original ATK = 1200 x fusion material count needs fusion/summon stat overlay hook. Ceiling: not ignition-activatable here.
- `DARKLORD_DESIRE` (activated): L116: Fairy-only Tribute Summon + cannot SS need summon hooks. Ceiling: OPT -1000 ATK (tempStage) → send 1 opp monster to GY.
- `DEEP_SEA_DIVA` (activated): L58: Normal Summon trigger needs summon hook. Ceiling: once via usage while face-up if Lv≤3 Sea Serpent in Deck.
- `DESTINY_HERO_DRILLDARK` (activated): L65: * ponytail: on-Summon trigger need summon hook.
- `DESTINY_HERO_DUSKTOPIA` (activated): L47: * TryClearDestinyHeroDusktopiaProtectionEndPhase. ponytail: Fusion on Summon
- `ELEMENTAL_HERO_BLAZEMAN` (activated): L222: on-summon does not consume effectUsedThisTurn — that flag is only for the menu activated effect (popup_2). Otherwise popup_2 can never fire the turn Blazeman is summoned.
- `ELEMENTAL_HERO_STRATOS` (activated): L462: on-summon text after field draw so Stratos is visible.
- `ELEMENTAL_HERO_TERRA_FIRMA` (activated): L70: attack-position summons stay isFaceUp=0 until end-of-turn flip
- `EVIL_HERO_INFERNAL_RIDER` (activated): L228: on-summon + HERO lock need summon/SS gates. Ceiling: OPT add Dark Fusion Deck/GY, else OPT banish self+4 GY → Set Super Poly.
- `EVIL_HERO_NEOS_LORD` (activated): L144: indestructible + on-SS/opp-GY-sent take-control triggers need continuous/summon hooks. Ceiling: OPT take control of 1 face-up opp monster.
- `EVIL_HERO_TOXIC_BUBBLE` (activated): L16: on-SS draw when Dark Fusion Fusion up needs summon hook. Ceiling: not field-ignition activatable; SS-from-hand uses FromHand path.
- `GLADIATOR_BEAST_SAGITTARII` (activated): L110: end-of-Battle-Phase + battled gate + discard-GB draw 2 on GB-SS need battle/summon hooks. Ceiling: OPT shuffle self into Deck then SS another Gladiator Beast from Deck.
- `GLADIATOR_BEAST_VESPASIUS` (activated): L121: FromHand battle SS + continuous +500 while GB-SS'd + end-BP battled gate need battle/summon hooks. Ceiling: OPT tag-out shuffle→SS.
- `GRAVEKEEPERS_DESCENDANT` (activated): L29: attack-position summons keep isFaceUp=0 until end-of-turn flip.
- `GRAVEKEEPERS_HEADMAN` (activated): L95: on-Summon trigger + ATK/face-down DEF choice need summon hook. Ceiling: OPT SS 1 Lv4 Gravekeeper's from GY in ATK.
- `GRAVEKEEPERS_SPIRITUALIST` (activated): L12: Necrovalley-gated Spellcaster Fusion from Extra Deck needs fusion summon API. Ceiling: not ignition-activatable here.
- `GREEN_GADGET` (activated): L60: NS/SS trigger needs summon hook. Ceiling: once via usage.
- `HOLACTIE_THE_CREATOR_OF_LIGHT` (activated): L64: SS-this-card-wins-Duel needs win-on-summon hook; no duel_helpers win API. Ceiling: not field-ignition activatable; use FromHand tribute path.
- `JUNK_SYNCHRON` (activated): L123: Normal Summon trigger needs summon hook. Ceiling: once via usage if GY Lv≤2.
- `MANJU_OF_THE_TEN_THOUSAND_HANDS` (activated): L113: Normal/Flip Summon trigger needs summon hook. Ceiling: once via usage if Ritual Monster or Ritual Spell in Deck and hand space.
- `MAZERA_DEVILLE` (activated): L53: on-SS-with-Pandemonium discard-3 needs summon hook. Ceiling: OPT discard 1 random opp + mill 3.
- `NEO_SPACIAN_MARINE_DOLPHIN` (activated): L79: treated-as Aqua Dolphin name + NEX-only SS need continuous/summon hooks.
- `QUINTET_MAGICIAN` (activated): L64: Fusion-with-5-Spellcasters gate + untributable/undestroyable need fusion/summon hooks. Ceiling: once via usage destroy all opp cards.
- `TEST_PANTHER` (activated): L199: Link Summon trigger for search needs summon hook. Ceiling: OPT search GB from Deck, else bounce GB → SS different GB.
- `THE_AGENT_OF_MYSTERU_EARTH` (activated): L110: Normal Summon trigger needs summon hook. Ceiling: OPT add 1 The Agent except Earth from Deck, or Master Hyperion if Sanctuary is face-up.
- `THE_SUPPRESSION_PLUTO` (activated): L213: on-summon text after field draw so Pluto is visible.
- `THESTALOS_THE_FIRESTORM_MONARCH` (activated): L55: Tribute Summon trigger needs summon hook. Ceiling: once via usage if opp hand.
- `TIMEAUS_THE_UNITED_DRAGON` (activated): L147: Main Phase Fusion Summon needs fusion UI hook. Ceiling: SS from hand via send cost uses FromHand path.
- `WHITE_HORNED_DRAGON` (activated): L79: on-Normal/Special Summon trigger needs summon hook. Ceiling: OPT banish up to 5 opp GY Spells + tempStage once via usage.
- `ARCANA_FORCE_I_THE_MAGICIAN` (permanent): L64: +1 tempStage (~500 ATK) on-summon; spell-trigger double ATK not wired.
- `ARCANA_FORCE_I_THE_MAGICIAN` (permanent): L69: tails LP heal on spell activation not wired; on-summon +500 opp LP only.
- `ARCANA_FORCE_III_THE_EMPRESS` (permanent): L48: opp Normal Summon SS/discard triggers need summon hooks; unk4 only.
- `ARCANA_FORCE_THE_CHAOS_RULER` (permanent): L162: true trigger is Special Summon; on-summon coin stand-in covers SS path.
- `DESTINY_HERO_DOGMA` (permanent): L77: true trigger is opp next Standby after 3-tribute SS; on-summon halve LP once.
- `DESTINY_HERO_DRAWHAND` (permanent): L98: HERO-effect SS gate not checked; on-summon mutual draw stand-in.
- `DESTINY_HERO_DREAD_SERVANT` (permanent): L77: * ponytail: NS Clock Tower counters need summon hook. */
- `DESTINY_HERO_DREADMASTER` (permanent): L284: Clock Tower Prison gate skipped; on-summon destroy/SS stand-in. D-HERO battle protect + no BD via DestinyHeroDreadmaster_* while face-up.
- `DRAGON_SPIRIT_OF_WHITE` (permanent): L59: Quick Tribute → SS Blue-Eyes from hand needs tribute/summon hooks.
- `EVIL_HERO_INFERNO_WING_BACKFIRE` (permanent): L128: true trigger is Special Summon; on-summon stand-in covers SS path.
- `EVIL_HERO_MALICIOUS_EDGE` (permanent): L9: * ponytail: 1-tribute summon gate need summon hook. */
- `GLADIATOR_BEAST_DIMACARI` (permanent): L8: double attack + GB tag-out need battle-end/summon hooks.
- `GLADIATOR_BEAST_TYGERIUS` (permanent): L110: GB tag-out + optional discard gate not wired; on-summon search stand-in.
- `HERO_KID` (permanent): L76: true trigger is Special Summon; on-summon stand-in covers SS path.
- `JUNK_WARRIOR` (permanent): L75: tempStage (~500/stage) on-summon only; no continuous recompute.
- `MAGICIAN_OF_DARK_ILLUSION` (permanent): L78: opp-turn hand SS + own S/T SS need chain hooks; on-summon GY SS only.

## `event.OnStandby` (168)

- `DARK_SUPREMACY` (trap): L53: GY banish shuffle HERO need GY ignition OPT. Ceiling: negate up to count face-up opp cards (monsters first) via unk4.
- `AMAZONESS_PET_LIGER_KING` (activated): L191: attack redirect FALSE. Ceiling: OPT destroy Amazoness → SS Warrior GY.
- `AMAZONESS_SPIRITUALIST` (activated): L104: hand/GY bounce→SS + ED lock need GY/ED hooks. Ceiling: field OPT add Polymerization from Deck.
- `ANCIENT_FAIRY_DRAGON` (activated): L196: true BP skip needs phase lock; unk4 stand-in. Ceiling: OPT SS Lv≤4 from hand; OPT destroy Field Spells + 1000 LP + add Field.
- `ANCIENT_GEAR_COMMANDER` (activated): L202: NS stand-in → SS AG; GY banish SS Golem FALSE. Ceiling: OPT send AG Golem hand/field/Deck → SS AG hand/Deck.
- `ANCIENT_GEAR_DARK_GOLEM` (activated): L60: name=AG Golem + cannot-Set lock FALSE. Ceiling: OPT add up to 2 Ancient Gear/Geartown from Deck then discard 1.
- `ANCIENT_GEAR_STATUE` (activated): L111: ignore summoning conditions partial via CannotBeSS check. Ceiling: OPT tribute self → SS AG Golem / mentions-Golem from hand/Deck.
- `ANCIENT_GEAR_STATUE` (activated): L189: once-per-turn FromHand not tracked without turn flag.
- `APPRENTICE_ILLUSION_MAGICIAN` (activated): L120: on-NS/SS search auto + hand/field send +2000 Quick need summon/ damage hooks. Ceiling: OPT add Dark Magician from Deck.
- `ARCANITE_MAGICIAN` (activated): L158: Synchro +2 Spell Counters + +1000 ATK/counter need synchro/stat hooks. Ceiling: OPT remove 1 unk4 counter (if >=1) → destroy 1 opp card.
- `AROMAGE_LAUREL` (activated): L66: LP-gain Tuner treat + sent-to-GY +500 LP need LP/send hooks. Ceiling: OPT add 1 Plant from Deck; upgrade: full Aroma branches.
- `AROMAGE_MARJORAM` (activated): L180: * ponytail: destroy-SS + LP-gain trigger need destroy/LP hooks. Ceiling: OPT banish opp GY. */
- `AROMAGE_ROSEMARY` (activated): L125: LP-higher Plant attack → opp monster effects locked + LP-gain gate need permanent/LP hooks. Ceiling: OPT change 1 face-up battle position.
- `AROMALILITH_ROSALINA` (activated): L106: discard quick LP + Plant-only SS lock need chain/SS hooks. Ceiling: OPT SS 1 non-Tuner Aroma from Deck in DEF.
- `AROMALILITH_ROSEMARY` (activated): L57: SS-trigger search + LP-gain Link-point SS + pointed tribute banish need summon/LP/Link hooks. Ceiling: OPT search Aroma from Deck.
- `AROMASERAPHY_ROSEMARY` (activated): L190: * ponytail: LP-gain negate needs LP hook. Ceiling: OPT destroy 1 face-up opp. */
- `ATLANTEAN_HEAVY_INFANTRY` (activated): L111: extra Normal Summon Sea Serpent + sent-for-WATER destroy need summon/send hooks. Ceiling: OPT destroy 1 Set Spell/Trap.
- `AZURE_EYES_SILVER_DRAGON` (activated): L48: until end of next turn clear needs EOT hook.
- `BLACK_WINGED_DRAGON` (activated): L95: damage redirect + Black Feather Counters + burn need damage hooks. Ceiling: OPT −2 tempStage on 1 face-up opp monster.
- `BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON` (activated): L98: protect + up-to-3-if-Alt-material need fusion/material hooks. Ceiling: OPT destroy 1 opp card; mark self unk4 cannot-attack.
- `BLUE_EYES_JET_DRAGON` (activated): L197: protect + destroy-trigger SS FALSE. Ceiling: field OPT bounce 1; FromHand if BEWD field/GY → SS.
- `BLUE_EYES_SPIRIT_DRAGON` (activated): L65: OPT GY negate + Extra Synchro + EP destroy need chain/Extra hooks. Ceiling: OPT tribute self → SS LIGHT Dragon from Deck in DEF.
- `BLUE_EYES_ULTIMATE_SPIRIT_DRAGON` (activated): L23: Quick field negate + destroy-SS FALSE; GY banish-lock FALSE. Ceiling: OPT +2 tempStage (~+1000) as negate stand-in.
- `CASTEL_THE_SKY_BLASTER_MUSKETEER` (activated): L138: detach/material + face-down branch need overlay engine. Ceiling: OPT return 1 face-up monster to the Deck.
- `CELESTIAL_KNIGHTLORD_PARSHATH` (activated): L104: Link material + GY banish Fairy → SS Fairy need send/banish hooks. Ceiling: OPT discard 1 → add Sanctuary/mention, or Fairy if Sanctuary on field.
- `CHIMERATECH_RAMPAGE_DRAGON` (activated): L86: on-Fusion destroy + multi-attack need fusion/battle hooks. Ceiling: OPT destroy up to 2 S/T on field.
- `CORAL_DRAGON` (activated): L114: GY draw when Synchro Summoned card sent from field needs GY hook. Ceiling: OPT discard 1 → destroy 1 opp card.
- `CRIMSON_DRAGON` (activated): L138: on-SS search + Extra Synchro return FALSE. Ceiling: OPT search mentioning Crimson Dragon S/T, else shuffle self → SS Dragon.
- `CYBER_DRAGON_INFINITY` (activated): L35: ATK summons keep isFaceUp=0 until EOT flip.
- `CYBER_SLASH_HARPIE_LADY` (activated): L196: Quick on S/T activation + Synchro/name hooks missing. Ceiling: OPT bounce 1 opp card or your Harpie to hand.
- `CYBER_SLASH_HARPY_LADY` (activated): L196: Quick on S/T activation + Synchro/name hooks missing. Ceiling: OPT bounce 1 opp card or your Harpie to hand.
- `CYBER_VALLEY` (activated): L128: attack-target banish + GY place-on-deck need battle/GY hooks. Ceiling: OPT banish self+1 face-up monster → draw 2; else banish self → draw 1.
- `DARK_HORUS` (activated): L99: after opp Main Phase Spell resolve trigger needs spell hook. Ceiling: OPT SS 1 Lv4 DARK from GY while face-up.
- `DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE` (activated): L61: name=DMG + GY +300 mention FALSE. Ceiling: field OPT add Shining Sarcophagus from Deck.
- `DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE` (activated): L61: name=DMG + GY +300 mention FALSE. Ceiling: field OPT add Shining Sarcophagus from Deck.
- `DARKLORD_DESIRE` (activated): L56: -2 tempStage (~1000 ATK, not exact); until EP clear needs EOT hook.
- `DECOY_DRAGON` (activated): L181: attack-target redirect needs battle targeting hook. Ceiling: OPT SS Lv7+ Dragon from GY once via usage when legal.
- `DESTINY_END_DRAGOON` (activated): L105: GY revive FALSE. Ceiling: OPT destroy 1 opp monster + burn its ATK + cannot BP (unk4).
- `DESTINY_HERO_CELESTIAL` (activated): L101: attack-declare destroy + GY draw-if-no-hand need battle/GY hooks. Ceiling: OPT destroy 1 face-up opp Spell + burn 500.
- `DESTINY_HERO_DASHER` (activated): L49: battle DEF change + draw-phase GY SS need battle/draw hooks. Ceiling: OPT tribute 1 other → +2 tempStage (~1000 ATK until End Phase).
- `DESTINY_HERO_DENIER` (activated): L189: GY SS when other D-HERO present needs GY/once-per-duel hooks. Ceiling: OPT put 1 D-HERO from Deck/GY/banished on top of Deck.
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. Ceiling: OPT destroy 1 you control + 1 other field card.
- `DESTINY_HERO_DISK_COMMANDER` (activated): L20: SS-from-GY trigger + once per duel. Ceiling: OPT draw 2 stand-in when on field; upgrade: GY SS dispatch + EFFECT_USAGE_ONCE.
- `DESTINY_HERO_DOOM_LORD` (activated): L67: * ponytail: return-in-2-Standbys needs Standby hook. Ceiling: OPT banish 1 opp monster. */
- `DESTINY_HERO_DREADNOUGHT_MASTER` (activated): L60: SS trigger → OPT ignition; cards-mentioning-D-HERO FALSE. Ceiling: OPT add up to 2 Destiny HERO from Deck.
- `DESTINY_HERO_DYSTOPIA` (activated): L203: on-SS burn + Quick destroy-if-ATK-changed need summon/ATK hooks. Ceiling: OPT pick Lv≤4 D-HERO in GY → burn its ATK.
- `DIVINER_OF_THE_HERALD` (activated): L89: on-NS/SS mill + tribute SS Fairy need summon/tribute hooks. Ceiling: OPT send 1 Fairy from Deck to GY (+unkTwo Level stand-in).
- `DIVINER_OF_THE_HERALD` (activated): L110: Level bump until EOT needs level-override hook; unkTwo stores milled Level.
- `EBON_ILLUSION_MAGICIAN` (activated): L78: Xyz detach cost + attack-banish FALSE. Ceiling: OPT SS Spellcaster Normal from hand/Deck (detach stand-in).
- `EL_SHADDOLL_MESHAHRAIL` (activated): L74: unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks. Ceiling: OPT pay 800 → add 1 Shaddoll or Void S/T from Deck.
- `ELDER_ENTITY_NORDEN` (activated): L124: SS-trigger timing + banish-when-leaves need summon/leave hooks. Ceiling: OPT SS Lv≤4 from GY face-up DEF with unk4 negated mark.
- `ELEMENTAL_HERO_AQUA_NEOS` (activated): L20: Contact fusion need fusion hook; EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT discard 1, then destroy 1 random opponent hand card.
- `ELEMENTAL_HERO_CHAOS_NEOS` (activated): L88: EP shuffle/Set-all + exact 3H/2H/1H/0H branch table FALSE. Ceiling: OPT 3 coin → destroy heads-count opp monsters.
- `ELEMENTAL_HERO_COSMO_NEOS` (activated): L72: activation lock / End Phase field wipe FALSE. Ceiling: OPT destroy all opp Spell/Trap.
- `ELEMENTAL_HERO_GRAND_NEOS` (activated): L95: Contact fusion need fusion hook; EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT bounce 1 opponent monster to hand.
- `ELEMENTAL_HERO_MAGMA_NEOS` (activated): L42: continuous 400/field + EP field bounce need permanent/EP hooks; EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT refresh tempStage from field card count.
- `ELEMENTAL_HERO_NEBULA_NEOS` (activated): L115: Extra SS trigger + EP banish field FALSE. Ceiling: OPT draw = opp card count, then mark 1 face-up negated.
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. Ceiling: OPT destroy opp cards up to different Attributes.
- `ELEMENTAL_HERO_SPIRIT_OF_NEOS` (activated): L154: attack-hand SS FALSE. Ceiling: OPT search Poly/E-HERO S/T, else OPT shuffle self → SS Normal E-HERO from Deck.
- `ELEMENTAL_HERO_STORM_NEOS` (activated): L86: contact Fusion + field shuffle need fusion/phase hooks; EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT destroy all S/T on field.
- `ENLIGHTENMENT_DRAGON` (activated): L138: Extra Summon conditions + destroy-add banished FALSE. Ceiling: OPT pay 2000 → banish all other field+both GYs, else OPT mill 4. Separate OPTs share one MarkMonsterEffectUsed.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L86: once-per-turn not tracked without turn hook.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L109: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE. Ceiling: OPT mill 1 HERO from Deck.
- `EVIL_HERO_MALICIOUS_BANE` (activated): L75: destruction immunity + HERO-only attack gate need destroy/attack hooks. Ceiling: OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4.
- `EVIL_HERO_TOXIC_BUBBLE` (activated): L39: HERO-only SS lock + once-per-turn not tracked without turn hook.
- `FORMULA_SYNCHRON` (activated): L32: Synchro Summon draw trigger + opp-Main-Phase quick Synchro need synchro/chain hooks. Ceiling: OPT draw 1 via usage when deck remains.
- `GANDORA_G_THE_DRAGON_OF_DESTRUCTION` (activated): L151: +300 ATK/banished needs permanent/banish count hook. Ceiling: OPT pay half LP → banish all other field → SS Lv≤7 Sarc mention.
- `GLADIATOR_BEAST_ANDABATA` (activated): L158: contact Fusion SS Lv≤7 GB Fusion from Extra needs Extra API. Ceiling: OPT tag-out → SS 2 different GB from Deck.
- `GLADIATOR_BEAST_ATTORIX` (activated): L130: on-GB-SS name/Level copy + end-of-BP battled tag gate need summon/ battle hooks. Ceiling: OPT send 1 other GB from Deck to GY (unkTwo name copy) or tag-out shuffle→SS.
- `GLADIATOR_BEAST_AUGUSTUS` (activated): L48: GB-SS trigger + end-of-BP tag-out need summon/battle hooks. Ceiling: OPT SS 1 other GB from hand in DEF.
- `GLADIATOR_BEAST_BESTIARI` (activated): L192: GB-tag SS destroy trigger + end-of-BP battled gate need summon/ battle hooks. Ceiling: OPT destroy 1 opp S/T, else tag-out shuffle→SS.
- `GLADIATOR_BEAST_CLAUDIUS` (activated): L61: double BP + opp-effect trigger FALSE. Ceiling: OPT SS Gladiator Beast from Deck (opp effect stand-in).
- `GLADIATOR_BEAST_DAREIOS` (activated): L179: Link Summon trigger + BP protect + Link Material lock FALSE. Ceiling: OPT SS Lv≤4 GB from hand/GY, or any GB from Deck if opp has monster.
- `GLADIATOR_BEAST_DOMITIANUS` (activated): L133: Quick negate/destroy + attack-redirect FALSE; end-BP battled gate missing. Ceiling: OPT tag-out → SS 1–2 GB from Deck.
- `GLADIATOR_BEAST_DRAGASES` (activated): L157: battle indestruct + opp chain block + end-of-BP battled gate need battle hooks. Ceiling: OPT GB tag-out → SS 2 different from Deck.
- `GLADIATOR_BEAST_EQUESTE` (activated): L158: on-GB-tag SS add trigger + end-of-BP battled gate need summon/battle hooks. Ceiling: OPT add 1 GB from GY to hand, else tag-out shuffle→SS.
- `GLADIATOR_BEAST_GISTEL` (activated): L162: on-GB-SS search + end-BP battled tag gate need summon/battle hooks. Ceiling: OPT search Gladiator S/T, else tag-out. FromHand: reveal+SS both.
- `GLADIATOR_BEAST_GYZARUS` (activated): L308: Contact SS destroy trigger + end-BP Extra tag need summon/battle/ Extra hooks. Ceiling: OPT destroy up to 2 monsters, else tag-out → SS 2.
- `GLADIATOR_BEAST_HERAKLINOS` (activated): L148: either-turn chain negate needs chain hook. Ceiling: OPT discard 1 → destroy 1 opponent card.
- `GLADIATOR_BEAST_HOPLOMUS` (activated): L110: end-of-Battle-Phase + attacked/was-attacked gate + DEF 2400 on GB tag-SS need battle/end-BP hooks. Ceiling: OPT shuffle self into Deck then SS another Gladiator Beast from Deck.
- `GLADIATOR_BEAST_LANISTA` (activated): L154: on-SS name copy + end-of-BP tag gate need summon/battle hooks. Ceiling: OPT banish 1 GB from GY (unkTwo name copy) or tag-out.
- `GLADIATOR_BEAST_LAQUARI` (activated): L110: end-of-Battle-Phase + attacked/was-attacked gate + ATK 2100 on GB tag-SS need battle/end-BP hooks. Ceiling: OPT shuffle self into Deck then SS another Gladiator Beast from Deck.
- `GLADIATOR_BEAST_MURMILLO` (activated): L235: GB-tag SS destroy trigger + end-of-BP battled gate need summon/ battle hooks. Ceiling: OPT destroy face-up monster, else tag-out shuffle→SS.
- `GLADIATOR_BEAST_NEROKIUS` (activated): L158: battle indestruct + opp chain block + end-of-BP gate need battle hooks. Ceiling: OPT tag-out → SS 2 different GB from Deck.
- `GLADIATOR_BEAST_NOXIOUS` (activated): L130: hand attack-redirect SS + battled tag gate need battle hooks. Ceiling: OPT mill 1 GB from Deck, else tag-out.
- `GLADIATOR_BEAST_TAMER_EDITOR` (activated): L70: Extra Deck Fusion SS + immunity + BP tag FALSE. Ceiling: OPT SS Lv≥5 GB from Deck (Extra stand-in).
- `GRAVEKEEPERS_AMBUSHER` (activated): L146: flip trigger + Necrovalley search need flip/send hooks. Ceiling: OPT put 1 opponent GY card on bottom of their Deck.
- `GRAVEKEEPERS_CHIEF` (activated): L186: Tribute Summon trigger, once-only control, and Necrovalley GY immunity need summon/continuous hooks. Ceiling: OPT SS GK from GY.
- `GRAVEKEEPERS_ORACLE` (activated): L93: Tribute Summon sequence (destroy/flip/ATK) FALSE. Ceiling: OPT destroy up to 2 cards on opp field.
- `GRAVEKEEPERS_SUPERNATURALIST` (activated): L57: material ATK gain + Necrovalley destroy protect + EP schedule FALSE. Ceiling: OPT add Gravekeeper or Necrovalley from Deck now (EP add stand-in).
- `GRAVEKEEPERS_VISIONARY` (activated): L89: * ponytail: destroy-replace needs destroy gate. Ceiling: OPT discard GK stand-in. */
- `GUARDIAN_DREADSCYTHE` (activated): L170: summon lock + GY revive loop need summon/leave hooks. Ceiling: OPT equip/add Reaper Scythe from Deck.
- `HARPIE_CONDUCTOR` (activated): L99: name Lady + protect destroy redirect + on-Harpie-return trigger need name/destroy/return hooks. Ceiling: OPT bounce 1 face-up/ATK opp monster.
- `HARPIE_HARPIST` (activated): L124: NS trigger + GY End Phase search FALSE as separate triggers. Ceiling: OPT bounce own WB + opp face-up, else OPT add Harpie from Deck.
- `HARPIE_ORACLE` (activated): L124: name becomes Harpie Lady + End Phase Sisters S/T add need name/EP hooks. Ceiling: OPT add 1 Harpie from GY to hand.
- `HELSHADDOLL_HOLLOW` (activated): L109: FLIP Extra mill + GY attribute mill need flip/send hooks. Ceiling: OPT banish 1 face-up opp monster.
- `JAIN_TWILIGHTSWORN_GENERAL` (activated): L151: until end of turn clear needs EOT tempStage reset hook.
- `JAIN_TWILIGHTSWORN_GENERAL` (activated): L229: other-Lightsworn-activated mill 2 needs chain hook. Ceiling: OPT banish 1 Lightsworn from hand/GY → weaken 1 face-up monster. EP mill 2 stand-in via TryApplyTwilightswornEndPhase.
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
- `LYLA_LIGHTSWORN_SORCERESS` (activated): L124: /* EP mill via TryApplyLylaEndPhase; ponytail: position-lock after OPT needs
- `LYLA_TWILIGHTSWORN_ENCHANTRESS` (activated): L205: quick effect on Spell/Trap activation + mill 3 when other LS activates need chain hooks. Ceiling: OPT banish LS from hand/GY then destroy 1 face-up Spell/Trap. EP mill 3 stand-in via TryApplyTwilightswornEndPhase.
- `MA_AT` (activated): L134: name-3 excavate UI hard. Ceiling: OPT reveal top 3, add any, mill rest.
- `MAGICAL_MARIONETTE` (activated): L117: Spell Counter on Spell resolve + +200 ATK/counter need spell/stat hooks. Ceiling: OPT remove 2 unk4 counters → destroy 1 monster.
- `MAGICIANS_SOULS` (activated): L143: Continuous Spell placement + DM/DMG GY SS branch need placement/ GY hooks. Ceiling: OPT send 1–2 S/T from hand/field → draw that many.
- `MASTER_PEACE_THE_TRUE_DRACOSLAYING_KING` (activated): L111: Tribute Continuous S/T + unaffected-by-type FALSE. Ceiling: OPT banish 1 other field card (Quick destroy stand-in).
- `MASTERFLARE_HYPERION` (activated): L237: name/effect copy + Quick negate FALSE. Ceiling: OPT mill Agent/Sanctuary-mention, else OPT banish Fairy → destroy 1.
- `MILLENNIUM_EYES_RESTRICT` (activated): L88: chain equip/absorb opp Effect Monster needs chain/control hooks. Ceiling: OPT destroy 1 opp monster.
- `MINERVA_THE_ATHENIAN_LIGHTSWORN` (activated): L184: anti-banish continuous + Synchro material count need continuous/synchro hooks. Ceiling: OPT mill LS different Types (up to field LS count), or banish ≤4 LS GY → mill.
- `MINERVA_THE_EXHALTED_LIGHTSWORN` (activated): L69: Xyz detach + destroy-on-death FALSE. OPT mill 3 → draw = Lightsworn among milled is wired above.
- `MORPHTRONIC_CELFON` (activated): L136: reveal/look UI missing; die roll + SS/add among top N. Ceiling: ATK OPT die→SS Lv≤4 Morphtronic; DEF OPT die→add Morphtronic.
- `MORPHTRONIC_EARFON` (activated): L48: real Tuner flag / Equip double-attack need Synchro/equip hooks. Ceiling: OPT PickZone mark unk4 as Tuner stand-in.
- `MORPHTRONIC_EARFON` (activated): L95: on-SS Tuner mark + Equip 2-attacks FALSE. Ceiling: OPT PickZone treat face-up as Tuner (unk4).
- `MORPHTRONIC_MAGNEN_BAR` (activated): L55: exactly-2-other ATK gate + DEF cannot-attack need battle hooks. Ceiling: ATK Position OPT refresh tempStage from other ATK/500.
- `MORPHTRONIC_REMOTEN` (activated): L213: position-gated OPT search. ATK: banish GY Morphtronic → add same Lv. DEF: discard Morphtronic → add other same Lv.
- `MORPHTRONIC_SCANNEN` (activated): L194: FromHand banish Morphtronic → SS; ATK/DEF OPT search modes.
- `MORPHTRONIC_SCOPEN` (activated): L58: DEF Position → treat as Level 4 + EP destroy on ATK-mode SS need position/EP hooks. Ceiling: ATK Position OPT SS 1 Lv4 Morphtronic from hand.
- `MORPHTRONIC_SLINGEN` (activated): L160: DEF destroy-other-Morphtronic substitute needs destroy redirect hook. Ceiling: ATK OPT tribute 1 other Morphtronic → destroy 1 field card.
- `MORPHTRONIC_STAPLEN` (activated): L102: * ponytail: ATK attack-redirect needs battle hook. Ceiling: OPT change 1 opp ATK to DEF. */
- `MORPHTRONIC_VACUUMEN` (activated): L24: send Equip → burn + DEF equip-take-control need equip hooks. Ceiling: ATK Position OPT burn 500.
- `NAELSHADDOLL_ARIEL` (activated): L72: FLIP SS banished Shaddoll + sent-by-effect branch need flip/RFP hooks. Ceiling: OPT banish up to 3 cards from either GY.
- `NECROFACE` (activated): L86: Normal Summon shuffle + banish-mill branches need summon/banish hooks. Ceiling: OPT shuffle all banished into Decks + tempStage per card.
- `NEHSHADDOLL_GENIUS` (activated): L54: until end of turn clear needs EOT unk4 reset hook.
- `NEHSHADDOLL_GENIUS` (activated): L110: FLIP Shaddoll unaffected + sent-by-effect branches need flip/send hooks. Ceiling: OPT negate 1 face-up Effect Monster (unk4).
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
- `RYKO_TWILIGHTSWORN_FIGHTER` (activated): L191: NS/flip + other-Lightsworn mill 3 need summon/chain hooks. Ceiling: OPT banish LS from hand/GY then banish 1 field card; EP mill 3 stand-in via TryApplyTwilightswornEndPhase.
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
- `VISION_HERO_ADORATION` (activated): L105: until end of turn clear needs EOT tempStage reset hook.
- `VISION_HERO_FARIS` (activated): L148: Continuous Trap place + ED HERO lock need place/ED hooks. Ceiling: OPT add 1 Vision HERO from Deck to hand.
- `VISION_HERO_GRAVITO` (activated): L113: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip zone API. Ceiling: OPT add 1 banished HERO monster to hand.
- `VISION_HERO_INCREASE` (activated): L69: GY Continuous Trap place + tribute HERO SS-self FALSE. Ceiling: OPT SS Vision HERO Lv≤4 from Deck (ST-zone SS stand-in).
- `WEISS_LIGHTSWORN_ARCHFIEND` (activated): L167: sent-from-Deck-to-GY trigger needs mill/send hook. Ceiling: field OPT SS 1 other Lightsworn from GY.
- `CYBER_KIRIN` (permanent): L8: ATK-position spell/trap negate, battle-draw, and OPT tribute damage zero need continuous/battle/tribute hooks not wired for permanents.
- `DRAGON_MASTER_MAGIA` (permanent): L8: Quick negate-by-card-type needs chain/OPT hooks.
- `THE_DARK_MAGICIANS` (permanent): L154: OPT draw on S/T activation needs chain/OPT hooks.

## `event.GyIgnition` (11)

- `DESTINY_HERO_DREADNOUGHT_SERVANT` (activated): L89: GY banish destroy on Lv8 D-HERO SS FALSE. Ceiling: FromHand if control D-HERO or Field Spell → SS, destroy 1, add Poly.
- `DESTINY_HERO_DREAMER` (activated): L52: * ponytail: banish-on-leave need GY hook. Ceiling: GY ignition SS. */
- `DESTINY_HERO_DYNATAG` (activated): L134: GY banish ATK boost not wired; both players 1000 on FromHand.
- `DESTINY_HERO_MALICIOUS` (activated): L43: GY ignition needs GY-menu wire. Ceiling: allow when Malicious in GY + another in Deck (callable if gMonEffect set to Malicious).
- `EVIL_HERO_SINISTER_NECROM` (activated): L103: GY ignition needs GY-menu wire. Ceiling: allow when Sinister Necrom in GY + Evil HERO in hand or Deck (callable if gMonEffect set).
- `LEVEL_EATER` (activated): L177: GY ignition + cannot-be-Tributed-except-for-Tribute-Summon need GY-menu + tribute hooks. Ceiling: GY ignition when Lv5+ you control + empty zone (Treeborn pattern).
- `MEZUKI` (activated): L169: GY ignition needs GY-menu wire. Ceiling: allow when Mezuki + another Zombie in expanded GY (callable if gMonEffect set to Mezuki).
- `POSEIDRA_THE_ATLANTEAN_DRAGON` (activated): L284: hand SS uses FromHand path. Ceiling: GY ignition like Malicious.
- `THE_BLAZING_MARS` (activated): L48: no multi-select GY banish + hand/GY activation path yet — banish 3 other monsters to Special Summon deferred until expanded GY targeting exists.
- `YAMORIMORI` (activated): L124: GY ignition needs GY-menu wire. Ceiling: banish self from GY + own Reptile + opp face-up present → destroy opp face-up monster.
- `THUNDER_DRAGON_COLOSSUS` (permanent): L8: opp search lock + battle/effect destroy→GY-banish need continuous/battle hooks.

## `chain.Negate` (33)

- `ANCIENT_GEAR_BEAST` (activated): L13: * ponytail: negate destroyed-in-battle monster effects need battle hook. */
- `ANCIENT_GEAR_ENGINEER` (activated): L13: * ponytail: trap negate + end-of-Damage-Step destroy need battle/trap hooks. */
- `ARCANA_KNIGHT_JOKER` (activated): L12: discard matching type to negate activation needs chain/response hooks. Ceiling: not ignition-activatable here.
- `ASH_BLOSSOM_AND_JOYOUS_SPRING` (activated): L50: chain negate for add/SS/mill from Deck not wired; upgrade: chain interrupt hook when one exists.
- `CYBER_DRAGON_INFINITY` (activated): L62: Xyz attach / negate FALSE. Ceiling: ClearZone absorb + +1 tempStage.
- `CYBER_PHOENIX` (activated): L48: * ponytail: ATK-position Machine S/T target-negate needs targeting gate. */
- `DESTINY_HERO_DARK_ANGEL` (activated): L81: field spell-negate FALSE. Ceiling: FromHand discard → SS D-HERO to opp DEF.
- `DESTINY_HERO_PLASMA` (activated): L95: equip/absorb + half-ATK boost + continuous opp negate need equip hooks. Ceiling: destroy 1 opp monster.
- `DIVINE_SERPENT_GEH` (activated): L31: destroy gate + untargetable + battle negate need destroy/battle hooks. Ceiling: field ignition FALSE; FromHand pay half LP → SS only.
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
- `MORPHTRONIC_BOOMBOXEN` (activated): L12: double attack in ATK + DEF negate-attack need battle/position hooks. Ceiling: not ignition-activatable here.
- `NATURIA_BEAST` (activated): L12: Quick Effect spell negate + mill 2 need chain/negation hooks. Ceiling: not ignition-activatable here; upgrade: either-turn interrupt.
- `NUMBER_39_UTOPIA` (activated): L12: attack negate via detach + no-material self-destroy need battle hook and XYZ material system. Ceiling: not field-ignition activatable.
- `RESCUE_CAT` (activated): L123: negated effects + End Phase destroy not applied; upgrade: summon flags + turn-end cleanup gate.
- `RESCUE_RABBIT` (activated): L126: End Phase destroy + effect negate not applied; upgrade: turn-end gate.
- `SILENT_SWORDSMAN` (activated): L134: * ponytail: Quick Spell negate needs chain hook. */
- `SILENT_SWORDSMAN_ZERO` (activated): L47: * tempStage unchanged. ponytail: Sarcophagus negate needs chain hook. */
- `STARDUST_DRAGON` (activated): L12: Quick Effect tribute-negate-destroy + End Phase GY SS need chain and EP hooks. Ceiling: not ignition-activatable here.
- `ARCANA_FORCE_EX_THE_LIGHT_RULER` (permanent): L100: Tails negate FALSE; Heads only when GY→hand legal.
- `ARCANA_FORCE_EX_THE_LIGHT_RULER` (permanent): L125: Tails Quick negate + battle add need chain/battle hooks.
- `EL_SHADDOLL_GRYSTA` (permanent): L126: negate opp Special Summon + send Shaddoll from hand need SS chain hook.
- `EL_SHADDOLL_SHEKHINAGA` (permanent): L126: negate SS monster effect + send Shaddoll need effect-chain hook.
- `LIGHT_AND_DARKNESS_DRAGON` (permanent): L8: chain negate (−500 ATK/DEF) + GY destroy-all/SS need chain/GY hooks.

## `gate.Tribute` (31)

- `SCAPEGOAT` (spell): L10: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. Ceiling: wrong Type/Attribute (Fairy/LIGHT vs Beast/EARTH); upgrade: add SHEEP_TOKEN card data + art, then swap this define.
- `SCAPEGOAT` (spell): L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. Ceiling: best-effort lockMonster; upgrade: tribute validator excludes SCAPEGOAT_TOKEN_ID / token flag.
- `SHADDOLL_CORE` (trap): L45: true trap-monster (still a Trap) + Attribute fusion substitute need Embodiment-style link. Ceiling: place SHADDOLL_CORE on monster row and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate.
- `ANCIENT_GEAR_GADJILTRON_CHIMERA` (activated): L12: Green/Red/Yellow Gadget tribute branches (+300 ATK, direct burn, battle burn) need summon/tribute hooks. Ceiling: not ignition-activatable.
- `ANDRO_SPHINX` (activated): L64: * ponytail: GY SS ban needs summon gate. */
- `ARCHLORD_KRISTYA` (activated): L322: engine treats level 5+ with no tribute as special-like (Cyber Dragon, etc.).
- `DARK_DUST_SPIRIT` (activated): L22: hand normal/tribute summon copies isFaceUp=0; attack-position still counts
- `FELIS_LIGHTSWORN_ARCHER` (activated): L101: SS when sent from Deck to GY by monster effect needs mill/SS hook. Ceiling: ignition tribute self → destroy 1 opponent monster → mill 3.
- `FLAME_RULER` (activated): L12: treat as 2 Tributes for FIRE Tribute Summon needs tribute-cost LynJump. Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle gate outside this file.
- `FOG_KING` (activated): L12: tribute-flex Normal Summon, ATK = tributed ATK, and global tribute lock need summon/tribute continuous hooks. Ceiling: not field-ignition here.
- `FUSILIER_DRAGON_THE_DUAL_MODE_BEAST` (activated): L12: NS without tribute + halved ATK/DEF needs summon tribute gate. Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon gate outside this file.
- `GAMECIAL_THE_SEA_TURTLE_KAIJU` (activated): L68: SS to opp field + Quick remove Kaiju Counter FALSE. Ceiling: FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju).
- `GRANMARG_THE_ROCK_MONARCH` (activated): L105: Tribute Summon trigger. Ceiling: once via usage if Set target.
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
- `ARCANA_FORCE_VI_THE_LOVERS` (permanent): L48: tribute engine not wired — unk4 marks double-tribute / no-tribute only.
- `BREAKER_THE_MAGICAL_WARRIOR` (permanent): L40: placement hook is hand normal/tribute summon only — special summons use duel_helpers
- `EVIL_HERO_INFERNAL_PRODIGY` (permanent): L8: empty-field hand SS is FromHand activated; End-Phase tribute draw needs turn hook.
- `LEGENDARY_MAJU_GARZETT` (permanent): L8: ATK = tributed originals needs hand-tribute SS stat capture; FromHand only.
- `MAGICIANS_ROD` (permanent): L138: GY tribute Spellcaster → add this needs opp-turn quick hook.

## `stat.Continuous` (5)

- `ARMITYLE_THE_CHAOS_PHANTASM` (activated): L12: Extra Deck banish-fusion SS + battle indestructible + turn-only +10000 ATK need summon/permanent/battle hooks. Ceiling: not ignition here.
- `BAZOO_THE_SOUL_EATER` (activated): L130: unk4 = banish count for +300 ATK each; cleared each EP with tempStage reset — not exact until-opp-EP hook.
- `EVIL_HERO_MALICIOUS_BANE` (activated): L105: +200 ATK each via tempStage (~500/unit); attack lock only marks self unk4.
- `THE_AGENT_OF_MIRACLES_JUPITER` (activated): L132: +800 ATK until EP needs exact stage/EP clear; Sanctuary RFG revive FALSE. Ceiling: banish Agent from GY → +2 tempStage on LIGHT Fairy.
- `ELEMENTAL_HERO_THE_SHINING` (permanent): L64: return up to 2 banished E-HEROes to hand deferred — no multi-RFP return UI yet. ATK overlay via ApplyDynamicZoneStats.

## `ui.Choice` (10)

- `AMULET_DRAGON` (activated): L58: no multi-select GY UI — banish every Spell in both GYs (min.1 gate above).
- `ARCANA_FORCE_XII_THE_HANGMAN` (activated): L170: coin targeting uses auto-pick highest ATK; upgrade: PickZone.
- `AROMALILITH_MAGNOLIA` (activated): L172: no multi-select UI — auto-banish up to winds count (opp rows first).
- `ATHENA` (activated): L363: drop field-target cursor before GY deck menu — PickZone state + trunk view was crashing when the menu opened on confirm.
- `BRIONAC_DRAGON_OF_THE_ICE_BARRIER` (activated): L232: N-discard path auto-bounces N cards; upgrade: sequential PickZone.
- `DARK_ARMED_DRAGON` (activated): L317: auto-target. No GY picker (DeckMenu screen switch corrupts VRAM from inside monster effect handler) and no PickZone cursor state (200 conflicts with game loop after MonsterActionMenu case 4 returns). Picks the best field target via AiPickTarget logic. Upgrade path: dedicated cursor state + A/B handlers like Cannon Soldier.
- `ELEMENTAL_HERO_STRATOS` (activated): L465: no dedicated A/B choice UI — try search first; player can cancel the deck pick (B) to fall through to destroy when that option is legal.
- `GUNGNIR_DRAGON_OF_THE_ICE_BARRIER` (activated): L195: 2-discard path auto-destroys 2 cards; upgrade: sequential PickZone.
- `OJAMA_KING` (activated): L54: PickZone for up to 3 empty zones + continuous lock gate. Ceiling: auto-lock first 3 empty opp MMZ via isLocked (ignored by FirstEmptyZoneInRow today — same as Ground Collapse).
- `ELEMENTAL_HERO_SUNRISE` (permanent): L464: true timing is attack declaration; resolve post-battle so PickZone can run from the main loop (same pattern as Core). Opponent-turn textboxes corrupt field VRAM — auto-resolve silently.

## `op.Search` (13)

- `SPELL_CHRONICLE` (spell): L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished. Ceiling: cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.
- `HARPIE_LADY_ELEGANCE` (trap): L47: * ponytail: WIND-only SS lock this turn + destroy-search Harpie Spell need hooks. */
- `AROMASERAPHY_SWEET_MARJORAM` (activated): L100: * ponytail: Synchro Winds search + LP-gain destroy need summon/LP hooks.
- `ATLANTEAN_DRAGOONS` (activated): L137: * ponytail: sent-for-WATER-effect search needs send hook.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L63: cannot attack without Fusion Monster needs attack gate hook. Ceiling: not field-ignition activatable; discard search uses FromHand path.
- `PUNISHMENT_DRAGON` (activated): L191: hand SS via 4+ banished LS uses FromHand path; LS mill 4 needs effect-activation hook. Ceiling: pay 1000 → shuffle all banished into Decks.
- `SHADDOLL_SQUAMATA` (activated): L154: FLIP destroy vs GY-sent mill exclusivity + trigger hooks deferred. Ceiling: destroy 1 opp monster OR mill 1 Shaddoll from Deck once via usage.
- `SOUL_ABSORBING_BONE_TOWER` (activated): L12: attack redirect while another Zombie present + mill 2 on Zombie SS need continuous/SS hooks. Ceiling: not ignition-activatable here.
- `THE_AGENT_OF_ENTROPY_URANUS` (activated): L117: tempStage stores milled Level, not a true level change hook.
- `ELEMENTAL_HERO_FLASH` (permanent): L47: no banished-zone + no multi-card GY search yet — banish 3 E-Heroes and add Normal Spell from GY deferred until banish + GY targeting exist.
- `JENIS_LIGHTSWORN_MENDER` (permanent): L53: LS-effect mill source not tracked — any deck mill this turn stand-in. EP burn/heal via TryApplyJenisEndPhase.
- `LIGHT_SERPENT` (permanent): L31: hand send only — !gGraveyardSendWasFromField is the hand/deck stand-in.
- `REPTILIANNE_GARDNA` (permanent): L8: destroyed→search Reptilianne needs destroy-to-GY permanent hook.

## `op.BanishTimed` (12)

- `SPELL_CHRONICLE` (spell): L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn. Ceiling: briefly hits GY; upgrade: direct deck→RFG.
- `ANCIENT_GEAR_DUEL` (trap): L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks. Ceiling: mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand-in from Deck/hand.
- `ANGELS_TEAR` (trap): L342: need 4 banish targets plus 1 summon target.
- `BEAST_MACHINE_KING_BARBAROS_UR` (activated): L224: multi-zone banish picker not wired; require both types reachable.
- `GANDORA_G_THE_DRAGON_OF_DESTRUCTION` (activated): L125: destroy+banish → Duel_BanishZone (no GY).
- `MAGICIANS_ROBE` (activated): L56: opp-turn quick + GY SS banish-on-leave need phase/GY hooks. Ceiling: discard S/T from hand → SS DM from Deck via FromHand path.
- `MORPHTRONIC_SMARTFON` (activated): L228: reveal UI FALSE. Ceiling: ATK die excavate add; DEF GY add Morphtronic. FromHand: banish Morphtronic GY → SS.
- `TIME_MAGIC_HAMMER` (activated): L12: Hermos equip + battle-step dice banish need summon/equip/battle hooks. Ceiling: not field-ignition activatable here.
- `TRISHULA_DRAGON_OF_THE_ICE_BARRIER` (activated): L114: Synchro Summon trigger needs synchro hook. Ceiling: once via usage banish random opp hand + 1 field + 1 GY when available.
- `DESTINY_HERO_DOOM_OVERLORD` (permanent): L327: banish-until-Standby = permanent banish; DARK HERO SS lock not wired.
- `DESTINY_HERO_DRAWHAND` (permanent): L70: next Standby GY revive via TryApplyDestinyHeroDrawhandStandby.
- `THE_WICKED_AVATAR` (permanent): L177: after SwitchTurn(), zone POV is still the ended turn until the next UpdateDuelZonePtrs — use gWhoseTurn (new active) not INACTIVE_DUELIST.

## `other` (181)

- `FUSION_DESTINY` (spell): L34: * ponytail: incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous,
- `NEO_SPACE` (spell): L94: gCardData_NEW — SetCardInfo would wipe stage/field ATK mid-overlay.
- `SCAPEGOAT` (spell): L74: LockMonsterCardsInRow also blocks Normal Set of monsters. Ceiling: cannot allow Set while blocking Summon without a menu hook that distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.
- `SECRETS_OF_DARK_MAGIC` (spell): L34: * ponytail: incomplete vs printed DM Fusion pool (Dragon Knight, etc.).
- `SPELL_GEAR` (spell): L156: * ponytail: optional SS offered as auto-yes when legal. Ceiling: cannot skip
- `AMAZONESS_HALL` (trap): L43: * ponytail: Extra Deck / Pendulum place + opp SS gain LP need hooks. */
- `DARK_SUPREMACY` (trap): L38: "Spells that mention Dark Fusion" not scanned by text.
- `FAVOURITE_CONTACT` (trap): L48: Extra Deck Fusion ignoring summon conditions + materials to Deck bottom need fusion recipe API. Ceiling: return up to 2 HERO/Neos/ Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free.
- `URGENT_TUNING` (trap): L14: Synchro Summon during Battle Phase needs Synchro material/ED summon path outside this file (no in-file Synchro API). Ceiling: shows text + self-destroy; upgrade: collect Tuners + non-Tuners → Extra Deck Synchro SS.
- `AMAZONESS_BABY_TIGER` (activated): L88: * ponytail: printed name=Amazoness-Tiger needs name-override hook. Ceiling: SS from hand only. */
- `ANCIENT_FAIRY_DRAGON` (activated): L135: cannot conduct Battle Phase — unk4 lock stand-in.
- `ANCIENT_GEAR_GADJILTRON_DRAGON` (activated): L108: * ponytail: burn/draw FALSE.
- `ANCIENT_GEAR_GOLEM_ULTIMATE_POUND` (activated): L85: real multi-attack needs battle hook; unk4=2 extra-attack stand-in.
- `ARCANA_FORCE_V_THE_HIEROPHANT` (activated): L153: discard only; opp cannot respond to Arcana Summons needs turn flag hook.
- `ARCANA_FORCE_XIX_THE_SUN` (activated): L121: requires coin-toss card on field — skipped; SS anytime when legal.
- `AROMAGE_BERGAMOT` (activated): L22: * ponytail: LP-gain gate + until opp EP clear need permanent/LP hooks.
- `AROMAGE_CANANGA` (activated): L175: * ponytail: LP-gain bounce trigger needs LP hook.
- `AROMASERAPHY_JASMINE` (activated): L48: no Link points — all your Plants while Jasmine face-up and LP higher.
- `ATLANTEAN_MARKSMAN` (activated): L149: * ponytail: sent-for-WATER destroy Set S/T needs send hook. */
- `BARRIER_STATUE_OF_THE_STORMWINDS` (activated): L12: no SS except WIND needs Special Summon lock gate. Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.
- `BLACK_WINGED_DRAGON` (activated): L52: −700 ≈ −2 tempStage (~−1000); counter/damage-redirect FALSE.
- `BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON` (activated): L55: cannot-attack-this-turn needs attack-gate; mark unk4.
- `BLUE_EYES_SOLID_DRAGON` (activated): L49: summon Quick shuffle→SS BEWD + per-effect usage need hooks.
- `CHAOS_ANCIENT_GEAR_GIANT` (activated): L12: Fusion-only + Spell/Trap immunity + battle-phase opp effect lock + multi-attack need fusion/battle hooks. Pierce via ApplySimplePiercersBattleEffect. Ceiling: not ignition-activatable here.
- `CLEAR_VICE_DRAGON` (activated): L72: * ponytail: Clear World immunity + discard-to-save need continuous/destruction hooks.
- `CRIMSON_DRAGON` (activated): L123: Extra Deck Synchro SS FALSE; Deck Dragon stand-in.
- `CROSS_KEEPER` (activated): L145: GY draw-on-E-HERO-Fusion need Fusion/GY hooks. Ceiling: send self → SS Elemental HERO or Neo-Spacian from hand/GY.
- `CYBER_LASER_DRAGON` (activated): L17: targets face-up monsters on opponent's side with ATK >= 2400 or DEF >= 2400. Upgrade path: scan backrow S/T cards if the card text ever changes.
- `CYBER_VALLEY` (activated): L107: end Battle Phase needs phase hook; draw 1 is attack-target stand-in.
- `CYBERNETIC_MAGICIAN` (activated): L63: until End Phase clear needs EP tempStage reset hook.
- `DARK_ARMED_DRAGON` (activated): L174: allow self-target for faithful TCG simulation; player can choose suboptimally
- `DARK_DUST_SPIRIT` (activated): L63: GBA "face-up" = isFaceUp bit; attack-position keeps isFaceUp=0 until flip
- `DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE` (activated): L129: name becomes Dark Magician Girl FALSE (no name-override hook).
- `DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE` (activated): L129: name becomes Dark Magician Girl FALSE (no name-override hook).
- `DARK_MAGICIAN_THE_DRAGON_KNIGHT` (activated): L12: name becomes Dark Magician + S/T protection need permanent/name hooks. Ceiling: not ignition-activatable here; upgrade: permanent overlay.
- `DARK_STRIKE_FIGHTER` (activated): L127: Main Phase 1 gate not wired; allow once via usage any main phase.
- `DARKBLAZE_DRAGON` (activated): L83: * ponytail: GY SS double original ATK/DEF needs SS-origin flag. */
- `DARKNESS_NEOSPHERE` (activated): L87: battle indestruct + trap bounce + attack-declare gate need battle/ phase hooks. Ceiling: not field-ignition activatable; SS uses FromHand path.
- `DARKNESS_NEOSPHERE` (activated): L113: opp attack declare gate not wired; require 1 field + 1 hand Fiend.
- `DESTINY_END_DRAGOON` (activated): L65: cannot conduct Battle Phase — unk4 lock stand-in. GY revive FALSE.
- `DESTINY_HERO_BLADE_MASTER` (activated): L89: opponent Battle Phase gate not wired; allow when face-up D-HERO on field. Ceiling: discard anytime from hand; upgrade: opp BP phase hook.
- `DESTINY_HERO_DECIDER` (activated): L114: /* EP add on NS/SS via TryApplyDestinyHeroDeciderEndPhase. ponytail: GY quick
- `DESTINY_HERO_DESTROY_DOGMA` (activated): L103: /* Standby burn via TryApplyDestinyHeroDestroyDogmaStandby. ponytail: Quick
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L154: second target picker not chained; auto-destroy best remaining card.
- `DESTINY_HERO_DIAMOND_DUDE` (activated): L57: next-turn GY Normal Spell activation needs Main Phase hook.
- `DESTINY_HERO_DOMINANCE` (activated): L66: look+reorder UI missing; RandRange shuffle of top N is stand-in.
- `EL_SHADDOLL_WENDIGO` (activated): L110: * ponytail: GY add Shaddoll S/T on send not wired. */
- `ELEMENTAL_HERO_DARK_NEOS` (activated): L50: contact Fusion need fusion hook; EP Extra return via TryReturnContactFusionsAtEndPhase.
- `ELEMENTAL_HERO_GAIA` (activated): L49: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.
- `ELEMENTAL_HERO_GREAT_TORNADO` (activated): L26: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.atk/def that the stat pipeline already computed for zone.
- `ELEMENTAL_HERO_LADY_HEAT` (activated): L45: CanActivate runs before the menu flips a face-down activator
- `ELEMENTAL_HERO_OCEAN` (activated): L81: skip stale GY Ocean while the activator is still on field
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L177: multi-target picker not wired; auto-destroy highest-value opp cards.
- `ELEMENTAL_HERO_TERRA_FIRMA` (activated): L42: fixed POV — only reveal the player's own monster row
- `EVIL_HERO_DEAD_END_PRISON` (activated): L151: Dark Fusion Fusion markers missing; any Fusion Monster stand-in.
- `EVIL_HERO_VICIOUS_CLAWS` (activated): L96: +300 ≈ +1 tempStage (~500).
- `GAGAGIGO_THE_RISEN` (activated): L12: Gagagigo the Risen has no printed monster effect (Xyz materials only). Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.
- `GLADIATOR_BEAST_ANDABATA` (activated): L135: Extra Deck return + Lv≤7 GB Fusion Extra SS need ED/Fusion APIs.
- `GLADIATOR_BEAST_ATTORIX` (activated): L157: copied name/Level until End Phase needs name-override hook; unkTwo stores sent card id as stand-in.
- `GLADIATOR_BEAST_GYZARUS` (activated): L183: Extra Deck return needs ED API; deck-top stand-in like other GB tags.
- `GLADIATOR_BEAST_LANISTA` (activated): L181: copied name until End Phase needs name-override hook; unkTwo stores copied card id as stand-in.
- `GLADIATOR_BEAST_NEROKIUS` (activated): L135: Extra Deck return + battle protection need ED/battle hooks.
- `GORZ_THE_EMISSARY_OF_DARKNESS` (activated): L34: damage-gate + Token FALSE. Ceiling: FromHand empty-field SS.
- `GRAVEKEEPERS_CURSE` (activated): L20: printed is If Summoned trigger. Ceiling: allow once via usage when manually activated / summon-dispatch calls Activate.
- `GRAVEKEEPERS_GUARD` (activated): L85: FLIP trigger needs flip hook.
- `GRAVEKEEPERS_HERATIC` (activated): L12: continuous unaffected-while-Necrovalley needs permanent protection gate. Ceiling: not ignition-activatable here; upgrade: permanent effect while Duel_IsBackrowCardOnField(NECROVALLEY).
- `GRAVEKEEPERS_ORACLE` (activated): L110: multi-target picker not wired; auto-destroy up to 2 opp cards.
- `GRAVEKEEPERS_SPY` (activated): L58: FLIP trigger needs flip hook.
- `GREAT_POSEIDON_BEETLE` (activated): L12: re-attack same target after surviving battle needs battle re-attack hook. Ceiling: not ignition-activatable here.
- `HARPIE_CHANNELER` (activated): L84: Level 7 with Dragon + name becomes Harpie Lady need continuous/name hooks.
- `HARPIE_CONDUCTOR` (activated): L20: no SS-origin flag; face-up/ATK stand-in for Special Summoned.
- `HARPIE_DANCER` (activated): L77: granted NS after bounce — clear block like Necrovalley Throne.
- `HARPIE_DANCER` (activated): L125: name becomes Harpie Lady on field/GY needs continuous rename hook.
- `HARPIE_QUEEN` (activated): L14: * ponytail: name becomes Harpie Lady on field/GY needs name override hook. */
- `HELIOS_TRICE_MEGISTUS` (activated): L67: * ponytail: extra attack if opp controls a monster needs multi-attack hook. */
- `HORUS_THE_BLACK_FLAME_DRAGON_LV8` (activated): L12: /* Spell immunity via IsImmuneToSpellEffectsOnField. ponytail: either-turn Spell
- `HOURGLASS_OF_LIFE` (activated): L11: updateGfx=FALSE — sub_8041CCC refreshes field after popup dismisses.
- `JOWLS_OF_DARK_DEMISE` (activated): L70: Jowls direct-attack flag; cleared when zone resets
- `LEVEL_EATER` (activated): L121: no zone Level-mod field (level is ROM-only via gCardData_NEW). Ceiling: SS self from GY; upgrade: TempLevel overlay on target.
- `LEVIA_DRAGON_DAEDALUS` (activated): L122: walk gDuel.board directly; gFixedZones column order differs on opponent rows, so row/col checks against gMonEffect can skip the wrong slot.
- `LEVIAIR_THE_SEA_DRAGON` (activated): L62: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- `LUMINA_TWILIGHTSWORN_SHAMAN` (activated): L226: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.
- `MA_AT` (activated): L102: name-3 declare UI missing; add any excavated as stand-in.
- `MAGICAL_SCIENTIST` (activated): L215: no direct attack + End Phase Extra Deck return need battle/EP hooks. Ceiling: pay 1000 → SS Lv≤6 Fusion from Extra/recipe list.
- `MAGICIANS_ROBE` (activated): L76: opponent's turn gate not wired.
- `MAN_THRO_TRO` (activated): L21: Ojama Trio monster form is the only token-like field unit today
- `MAXX_C` (activated): L55: draw-on-opponent-Special-Summon this turn not wired; upgrade: SS hook + simple turn flag when one exists.
- `MIRAGE_DRAGON` (activated): L12: opp cannot activate Traps in Battle Phase needs trap-activation gate. Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.
- `MIRROR_FORCE_DRAGON` (activated): L12: when targeted for attack/effect trigger needs protection hook. Ceiling: not ignition-activatable here; upgrade: trigger destroy-all.
- `MOLTEN_ZOMBIE` (activated): L18: printed trigger is SS from GY. Ceiling: once via usage when Activate runs (summon-dispatch or manual).
- `MORPHTRONIC_CAMERAN` (activated): L175: * ponytail: DEF Morphtronic untargetable needs targeting gate. */
- `MORPHTRONIC_LANTRON` (activated): L98: * ponytail: ATK redirect effect damage needs effect-damage hook. */
- `MORPHTRONIC_MAGNEN` (activated): L12: ATK-position highest-ATK-only attack target + DEF-position redirect-attack need battle/position hooks. Ceiling: not ignition here.
- `MORPHTRONIC_TELEFON` (activated): L176: reveal UI FALSE. Ceiling: ATK die→LP+SS Morph Lv≤roll; DEF die excavate add.
- `NECROFACE` (activated): L107: tempStage unit is ~500 ATK, not printed +100; upgrade: exact overlay.
- `NEO_BLUE_EYES_ULTIMATE_DRAGON` (activated): L105: real multi-attack needs battle hook; unk4=2 extra-attack stand-in.
- `NEO_SPACIAN_DARK_PANTHER` (activated): L12: copy opp monster name/effects needs engine name/effect overlay. Ceiling: not ignition-activatable here; upgrade: permanent/name/effect copy.
- `PROTECTOR_OF_THE_SANCTUARY` (activated): L12: opp cannot draw except Draw Phase needs draw-gate LynJump. Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.
- `RAIDEN_HAND_OF_THE_LIGHTSWORN` (activated): L101: +1 tempStage (~500 ATK, not exact +200); until opp EP clear needs hook.
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
- `VENOM_BOA` (activated): L87: cannot-attack-this-turn needs attack gate on unk4.
- `VENOM_SNAKE` (activated): L87: cannot-attack-this-turn needs attack gate on unk4.
- `VISION_HERO_GRAVITO` (activated): L64: no RemovedFromPlay_RemoveAt — shift RFP array in place after add. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- `WHITE_HORNED_DRAGON` (activated): L101: +1 tempStage per banished (~500 ATK each, not exact +300).
- `ZERADIAS_HERALD_OF_HEAVEN` (activated): L13: destroy self when Sanctuary absent needs continuous field check. Ceiling: not ignition-activatable here; upgrade: permanent maintenance hook.
- `AMEBA` (permanent): L23: AI candidate sim runs real effect code but restores duel state; do not queue burns that survive into the chosen action.
- `AMEBA` (permanent): L72: skip nested UpdateDuelGfxExceptField; caller just refreshed field.
- `ARCANA_FORCE_IV_THE_EMPEROR` (permanent): L86: ±500 ATK uses tempStage (~500/stage); only your Arcana Force on field.
- `ARCANA_FORCE_THE_CHAOS_RULER` (permanent): L198: Light Barrier opp-activation lock needs continuous field hook.
- `ARCANA_FORCE_XVIII_THE_MOON` (permanent): L48: Standby Moon Token / End Phase give-control need turn hooks; unk4 only.
- `ARCANA_FORCE_XXI_THE_WORLD` (permanent): L48: skip-turn / opp GY-to-hand need turn hooks; unk4 marks coin only.
- `BLUE_EYES_ALTERNATIVE_WHITE_DRAGON` (permanent): L50: BEWD stays in hand as a visible cost; only the alt card is cleared
- `BLUE_EYES_SHINING_DRAGON` (permanent): L68: in-place BEUD zone replacement; Duel_SpecialSummon* only fills empty zones
- `BREAKER_THE_MAGICAL_WARRIOR` (permanent): L15: hand normal summon copies isFaceUp=0; attack-position monsters still count
- `DARK_MAGICIAN_OF_DESTRUCTION` (permanent): L131: deck-first add; DM preferred by scan order, no picker.
- `DARKLORD_NURSE_REFICULE` (permanent): L8: LP gain→damage redirect needs LP-change hook.
- `DEEP_EYES_WHITE_DRAGON` (permanent): L121: first Dragon in GY stand-in for target picker.
- `DESPAIR_FROM_THE_DARK` (permanent): L47: opp hand/Deck send by card effect not tracked — GY-top SS only.
- `ELEMENTAL_HERO_ELECTRUM` (permanent): L67: no removed-from-play zone yet — shuffle banished/exiled monsters back into each owner's deck once Duel_BanishZone (or equivalent) exists.
- `ELEMENTAL_HERO_SUNRISE` (permanent): L105: GetTypeGroup/SetCardInfo would clobber gCardInfo.atk already computed.
- `ELEMENTAL_HERO_SUNRISE` (permanent): L143: never RefreshFieldMonsterStatOverlays here. Placement often runs with updateGfx=FALSE (AI summon / fusion). Overlay-only stamps without a full field draw leave level stars and ATK/DEF tiles on undrawn card faces — field-wide glitch on the opponent's turn. ATK boost applies via ApplyFieldZoneStatsToCardInfo on the next real gfx update.
- `EVIL_HERO_DARK_GAIA` (permanent): L8: ATK = fusion materials + flip opp Defense→Attack need fusion/battle hooks.
- `EVIL_HERO_MALICIOUS_FIEND` (permanent): L8: forced attack + face-up Attack Position need battle redirect hooks.
- `EXECUTOR_MAKYURA` (permanent): L93: most non-zero trapEffect values are chain-only; allow continuous exceptions.
- `FIRE_PRINCESS` (permanent): L37: normal hand summon copies isFaceUp=0; attack-position monsters still count
- `GLADIATOR_BEAST_ALEXANDER` (permanent): L8: spell immunity + GB tag-out need continuous/battle-end hooks.
- `GLADIATOR_BEAST_ESSEDARII` (permanent): L8: Contact Fusion has no permanent ignition path.
- `GLADIATOR_BEAST_OCTAVIUS` (permanent): L139: GB-tag SS + battle-end tag-out need summon/battle-end hooks.
- `GLADIATOR_BEAST_RETIARI` (permanent): L110: GB tag-out after battle needs battle-end hook.
- `GLADIATOR_BEAST_SECUTOR` (permanent): L8: battle-end tag SS 2 GB from Deck needs battle-end hook.
- `GLADIATOR_BEAST_SPARTACUS` (permanent): L95: Hoplomus-only SS + GB tag-out need summon/battle-end hooks.
- `GLADIATOR_BEAST_TORAX` (permanent): L8: GB tag-out draw after battle needs battle-end hook.
- `GRANADORA` (permanent): L92: unk4==1 means summon effect already fired; 0/2 are fresh normal/special summon
- `GREAT_MAJU_GARZETT` (permanent): L48: ram_map byte packing can leave u16 fields at odd EWRAM addresses;
- `GRINDER_GOLEM` (permanent): L8: hand SS to opp field + Grinder Tokens + NS/Set lock need summon/token hooks.
- `HARPIE_PERFUMER` (permanent): L134: name becomes Harpie Lady on field/GY needs name-override hook.
- `HARPIES_PET_PHANTASMAL_DRAGON` (permanent): L8: /* Direct attack via HarpiesPetPhantasmalDragon_CanAttackDirectly. ponytail:
- `KNIGHT_OF_PENTACLES` (permanent): L72: Tails "destroy when attacked" needs battle-step hook; unk4 tails = no attack only.
- `MAJU_GARZETT` (permanent): L48: ram_map byte packing can leave u16 fields at odd EWRAM addresses;
- `MOBIUS_THE_FROST_MONARCH` (permanent): L175: up-to-2 targeting uses zone->unk4 as phase flag. 0 = not started, 1+ = at least one target destroyed (re-entered targeting). Upgrade path: bitfield on zone if unk4 is needed for other purposes.
- `OSHALEON` (permanent): L109: must-attack-this restriction needs attack-gate hook.
- `PETEN_THE_DARK_CLOWN` (permanent): L73: hand takes priority when both are available; deck is the fallback
- `RAVIEL_LORD_OF_PHANTASMS` (permanent): L137: triggers on any monster placement (Normal + Special). Card text says "Normal Summons" only — needs opts.markSpecialSummon check.
- `REPTILIANNE_SERVANT` (permanent): L74: cannot-be-attacked + NS lock + spell-target destroy need battle/continuous hooks.
- `SHATIEL` (permanent): L51: GetTypeGroup/SetCardInfo would clobber gCardInfo mid-pipeline.
- `SPIRIT_OF_THE_POT_OF_GREED` (permanent): L11: normal hand summon copies isFaceUp=0; attack-position monsters still count
- `THE_BIG_SATURN` (permanent): L96: custom targeted spells store fixed-row origins in row2.
- `THE_BIG_SATURN` (permanent): L257: GY permanent scan misses some opponent-turn effect destroys (Core pattern).
- `THE_DARK_MAGICIANS` (permanent): L177: Deck-first SS order; hand/GY picker not wired.
- `THE_DESPAIR_URANUS` (permanent): L19: GetTypeGroup → SetCardInfo clobbers gCardInfo.atk/def mid-pipeline.
- `THE_DESPAIR_URANUS` (permanent): L96: gCardInfo is already set for this zone by the caller.
- `THE_TRIPPER_MERCURY` (permanent): L179: SetCardInfo would reset gCardInfo.atk/def back to printed base.
- `THE_TYRANT_NEPTUNE` (permanent): L59: ram_map byte packing can leave u16 fields at odd EWRAM addresses;
- `THE_TYRANT_NEPTUNE` (permanent): L451: draw Neptune on the field before popup / trunk picker.
- `THE_WICKED_DREADROOT` (permanent): L30: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.atk/def that the stat pipeline already computed for zone.
- `VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES` (permanent): L54: S/T + monster immunity + 3-counter win need continuous/battle hooks.
- `YOWIE` (permanent): L51: opp skip Draw Phase needs turn hook; unk4 marks alone-summon only.
- `ZERIEL` (permanent): L44: GetTypeGroup/SetCardInfo would clobber gCardInfo.atk already computed.
