# Partial Effects Taxonomy

Auto-generated companion to [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md).
Each `ponytail:` / `Ceiling:` note is tagged with its **primary missing engine surface** so Phase work in [`effect-data-system.md`](effect-data-system.md) can target events/ops that unblock many cards at once.

```bash
python3 tools/stub_effect_queue.py --write-list
```

**Last updated:** 2026-07-22 20:58 UTC  
**Ceiling lines tagged:** `177`  
**Partial files:** `154`

## Counts by missing surface

| Tag | Count | Suggested phase |
|-----|------:|-----------------|
| `other` | 74 | triage |
| `event.OnStandby` | 24 | 3 (OPT / turn flags) |
| `chain.Negate` | 15 | later / chain |
| `extra.XyzLinkSynchro` | 14 | later / Extra Deck |
| `gate.Tribute` | 10 | 2–3 |
| `event.OnSummon` | 8 | 3 |
| `op.BanishTimed` | 8 | 1–3 |
| `op.Search` | 8 | 1 |
| `event.OnBattleDestroy` | 5 | 3 |
| `event.OnFusionSummon` | 3 | 3 (fusion callback) |
| `ui.Choice` | 3 | 2 |
| `event.GyIgnition` | 2 | 3 |
| `event.OnDestroy` | 1 | 3 |
| `event.OnLpGain` | 1 | later / LP event |
| `stat.Continuous` | 1 | 1–3 |
| **total** | **177** | |

Highest-ROI unblock for this backlog is usually **`event.OnStandby` (OPT)** plus destroy/summon/battle listeners (Phase 3), not per-card rewrites.

## `event.OnBattleDestroy` (5)

- `AMAZONESS_HOT_SPRING` (trap): L46: * Ceiling: Pendulum Zone place + battle-damage gain LP OPT need hooks. */
- `ARMORY_ARM` (activated): L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE.
- `DESTINY_HERO_DREAMER` (activated): L130: * Ceiling: true damage-calc GY SS timing needs battle hook. */
- `HONEST` (activated): L95: /* Damage Step hand discard uses FromHand path. Ceiling: Main Phase
- `EVIL_HERO_WILD_CYCLONE` (permanent): L97: * Ceiling: attack S/T lock until end of Damage Step needs chain gate. */

## `event.OnDestroy` (1)

- `SPELL_CHRONICLE` (spell): L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. Ceiling: activate discard+banish 5 only; unk4 counter slot unused.

## `event.OnSummon` (8)

- `SHADDOLL_SCHISM` (trap): L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker; banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.
- `ANCIENT_GEAR_KNIGHT` (activated): L13: * Ceiling: Gemini Normal Monster treatment need summon hook. */
- `ARCANA_FORCE_XV_THE_FIEND` (activated): L271: on-summon heads auto-picks first destroyable opp monster.
- `DARKLORD_DESIRE` (activated): L119: * Ceiling: Fairy-only Tribute Summon + cannot SS need summon hooks. */
- `DESTINY_HERO_DUSKTOPIA` (activated): L47: * TryClearDestinyHeroDusktopiaProtectionEndPhase. Ceiling: Fusion on Summon
- `VISION_HERO_GRAVITO` (activated): L114: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip zone API. OPT add 1 banished HERO monster to hand (EffectOpt; on-summon stand-in).
- `ARCANA_FORCE_III_THE_EMPRESS` (permanent): L48: opp Normal Summon SS/discard triggers need summon hooks; unk4 only.
- `EVIL_HERO_INFERNO_WING_BACKFIRE` (permanent): L155: true trigger is Special Summon; on-summon stand-in covers SS path.

## `event.OnFusionSummon` (3)

- `ELEMENTAL_HERO_DARK_NEOS` (activated): L92: /* EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: contact Fusion need fusion hook. */
- `GLADIATOR_BEAST_GYZARUS` (activated): L175: * Ceiling: Contact Fusion SS destroy trigger + Extra Deck return. */
- `GLADIATOR_BEAST_ESSEDARII` (permanent): L8: Contact Fusion has no permanent ignition path.

## `event.OnStandby` (24)

- `DARK_SUPREMACY` (trap): L53: GY banish shuffle HERO need GY ignition OPT. Ceiling: negate up to count face-up opp cards (monsters first) via unk4.
- `ARCANA_FORCE_XV_THE_FIEND` (activated): L206: discard search + FromHand paths. OPT coin → destroy 1 monster or wipe field.
- `ARCANITE_MAGICIAN` (activated): L160: Synchro +2 Spell Counters + +1000 ATK/counter need synchro/stat hooks. OPT remove 1 unk4 counter → destroy 1 opp (EffectOpt).
- `AROMAGE_ROSEMARY` (activated): L127: LP-higher Plant attack → opp monster effects locked need permanent/battle hooks. LP-gain position change via aroma_lp_gain.c. OPT change 1 face-up battle position (EffectOpt).
- `ATLANTEAN_HEAVY_INFANTRY` (activated): L111: extra Normal Summon Sea Serpent + sent-for-WATER destroy need summon/send hooks. OPT destroy 1 Set Spell/Trap.
- `CASTEL_THE_SKY_BLASTER_MUSKETEER` (activated): L138: detach/material + face-down branch need overlay engine. OPT return 1 face-up monster to the Deck.
- `CYBER_DRAGON_INFINITY` (activated): L35: ATK summons keep isFaceUp=0 until EOT flip.
- `CYBER_SLASH_HARPIE_LADY` (activated): L198: Quick on S/T activation + Synchro/name hooks missing. OPT bounce 1 opp card or your Harpie to hand (EffectOpt).
- `CYBER_SLASH_HARPY_LADY` (activated): L198: Quick on S/T activation + Synchro/name hooks missing. OPT bounce 1 opp card or your Harpie to hand (EffectOpt).
- `DARK_HORUS` (activated): L100: after opp Main Phase Spell resolve trigger needs spell hook. OPT SS 1 Lv4 DARK from GY while face-up (EffectOpt).
- `DECOY_DRAGON` (activated): L182: attack-target redirect needs battle targeting hook. OPT SS Lv7+ Dragon from GY once via EffectOpt when legal.
- `DEEP_SEA_DIVA` (activated): L101: /* NS SS via TryDeepSeaDivaOnNormalSummon. Ceiling: OPT duplicate if NS already
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. OPT destroy 1 you control + 1 other field card.
- `EBON_ILLUSION_MAGICIAN` (activated): L78: Xyz detach cost + attack-banish FALSE. OPT SS Spellcaster Normal from hand/Deck (detach stand-in).
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. OPT destroy opp cards up to different Attributes.
- `ELEMENTAL_HERO_SPIRIT_OF_NEOS` (activated): L225: attack-hand SS FALSE. On-SS search via TryElementalHeroSpiritOfNeosOnMonsterPlacement (EffectOpt). OPT search Poly/E-HERO S/T (shares EffectOpt), else OPT shuffle self → SS Normal E-HERO.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L86: once-per-turn not tracked without turn hook.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L110: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE. OPT mill 1 HERO from Deck (EffectOpt).
- `EVIL_HERO_MALICIOUS_BANE` (activated): L75: destruction immunity + HERO-only attack gate need destroy/attack hooks. OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4.
- `MORPHTRONIC_EARFON` (activated): L53: real Tuner flag / Equip double-attack need Synchro/equip hooks. OPT PickZone mark unk4 as Tuner stand-in.
- `MORPHTRONIC_SCOPEN` (activated): L58: DEF Position → treat as Level 4 + EP destroy on ATK-mode SS need position/EP hooks; ATK Position OPT SS 1 Lv4 Morphtronic from hand.
- `MORPHTRONIC_VACUUMEN` (activated): L25: send Equip → burn + DEF equip-take-control need equip hooks. ATK Position OPT burn 500 (EffectOpt).
- `VISION_HERO_FARIS` (activated): L149: Continuous Trap place + ED HERO lock need place/ED hooks. OPT add 1 Vision HERO from Deck to hand (EffectOpt).
- `VISION_HERO_INCREASE` (activated): L70: GY Continuous Trap place + tribute HERO SS-self FALSE. OPT SS Vision HERO Lv≤4 from Deck (ST-zone SS stand-in; EffectOpt).

## `event.GyIgnition` (2)

- `BLUE_EYES_ULTIMATE_SPIRIT_DRAGON` (activated): L25: * Ceiling: Quick field negate + destroy-SS FALSE; GY banish-lock FALSE. */
- `CELESTIAL_KNIGHTLORD_PARSHATH` (activated): L106: * (EffectOpt). Ceiling: Link material + GY banish Fairy → SS Fairy need

## `event.OnLpGain` (1)

- `AMAZONESS_HALL` (trap): L43: * Ceiling: Extra Deck / Pendulum place + opp SS gain LP need hooks. */

## `extra.XyzLinkSynchro` (14)

- `SHADDOLL_CORE` (trap): L45: true trap-monster (still a Trap) + Attribute fusion substitute need Embodiment-style link; place SHADDOLL_CORE on monster row and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate.
- `URGENT_TUNING` (trap): L14: Synchro Summon during Battle Phase needs Synchro material/ED summon path outside this file (no in-file Synchro API). → Extra Deck Synchro SS.
- `CRIMSON_DRAGON` (activated): L124: Extra Deck Synchro SS FALSE; Deck Dragon stand-in.
- `CURIOUS_THE_LIGHTSWORN_DOMINION` (activated): L146: * Ceiling: Link Summon mill + mill-cascade need summon/send hooks.
- `CYBER_DRAGON_INFINITY` (activated): L62: Xyz attach / negate FALSE. Ceiling: ClearZone absorb + +1 tempStage.
- `LEVEL_EATER` (activated): L123: * Ceiling: SS self from GY; upgrade: TempLevel overlay on target. */
- `LEVIAIR_THE_SEA_DRAGON` (activated): L108: * Ceiling: materials not checked; upgrade: overlay detach before SS. */
- `NUMBER_39_UTOPIA` (activated): L13: * hook and XYZ material system. Ceiling: not field-ignition activatable. */
- `REPTILIANNE_LAMIA` (activated): L97: /* GY synchro-material ATK-0 need synchro hook. Ceiling: remains.
- `TATSUNOKO` (activated): L13: * synchro/summon continuous hooks. Ceiling: not field-ignition here. */
- `TRISHULA_DRAGON_OF_THE_ICE_BARRIER` (activated): L114: /* Synchro Summon trigger needs synchro hook. Ceiling: once via usage banish
- `ELEMENTAL_HERO_ELECTRUM` (permanent): L67: no removed-from-play zone yet — shuffle banished/exiled monsters back into each owner's deck once Duel_BanishZone exists. ATK overlay via ElementalHeroElectrum_ApplyDynamicZoneStats.
- `ELEMENTAL_HERO_THE_SHINING` (permanent): L64: return up to 2 banished E-HEROes to hand deferred — no multi-RFP return UI yet. ATK overlay via ElementalHeroTheShining_ApplyDynamicZoneStats.
- `HARPIES_PET_PHANTASMAL_DRAGON` (permanent): L9: * Ceiling: Harpie protect + End Phase detach need battle/xyz hooks. */

## `chain.Negate` (15)

- `ANCIENT_GEAR_ENGINEER` (activated): L14: * Ceiling: opp Trap activation negate on attack needs chain gate. */
- `ASH_BLOSSOM_AND_JOYOUS_SPRING` (activated): L50: chain negate for add/SS/mill from Deck not wired; upgrade: chain interrupt hook when one exists.
- `DESTINY_HERO_DARK_ANGEL` (activated): L81: field spell-negate FALSE. Ceiling: FromHand discard → SS D-HERO to opp DEF.
- `DESTINY_HERO_DECIDER` (activated): L116: * GY to hand (EffectOpt). Ceiling: GY quick return-on-damage need chain hook. */
- `DESTINY_HERO_DESTROY_DOGMA` (activated): L104: * destroy/negate FALSE. Ceiling: FromHand banish 3 Warrior/DARK → SS + burn 2000. */
- `DESTINY_HERO_PLASMA` (activated): L95: equip/absorb + half-ATK boost + continuous opp negate need equip hooks. Ceiling: destroy 1 opp monster.
- `DIVINE_SERPENT_GEH` (activated): L41: * Ceiling: destroy gate + battle negate need destroy/battle hooks.
- `HORUS_THE_BLACK_FLAME_DRAGON_LV8` (activated): L13: * Ceiling: either-turn Spell negate needs chain hook. */
- `ILLUSION_OF_CHAOS` (activated): L135: /* field bounce→SS DM negate FALSE. Ceiling: FromHand search only. */
- `LYLA_TWILIGHTSWORN_ENCHANTRESS` (activated): L208: * EP mill 3 via TryApplyTwilightswornEndPhase. Ceiling: quick effect on
- `RYKO_TWILIGHTSWORN_FIGHTER` (activated): L204: NS mill 3 stand-in for other-LS effect→mill; upgrade: chain hook.
- `SILENT_SWORDSMAN_ZERO` (activated): L47: * tempStage unchanged. Ceiling: Sarcophagus negate needs chain hook. */
- `ARCANA_FORCE_EX_THE_LIGHT_RULER` (permanent): L100: Tails negate FALSE; Heads only when GY→hand legal.
- `EL_SHADDOLL_GRYSTA` (permanent): L126: negate opp Special Summon + send Shaddoll from hand need SS chain hook.
- `EL_SHADDOLL_SHEKHINAGA` (permanent): L126: negate SS monster effect + send Shaddoll need effect-chain hook.

## `gate.Tribute` (10)

- `LEV_SHADDOLL_FUSION` (spell): L158: the face-up ignition still needs a monster-zone tribute picker and an Extra Deck special-summon flow, neither of which is owned by this spell activation dispatcher.
- `SCAPEGOAT` (spell): L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. SCAPEGOAT_TOKEN_ID / token flag.
- `ANDRO_SPHINX` (activated): L64: * Ceiling: GY SS ban needs summon gate. */
- `EVIL_HERO_TOXIC_BUBBLE` (activated): L89: HERO-only SS lock this turn needs summon gate.
- `FOG_KING` (activated): L13: * lock need summon/tribute continuous hooks. Ceiling: not field-ignition here. */
- `GAMECIAL_THE_SEA_TURTLE_KAIJU` (activated): L69: * Ceiling: FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju). */
- `LEKUNGA` (activated): L13: * Ceiling: wrong Type/Attribute/stats (Fairy/LIGHT 0/0 vs Plant/WATER 700/700);
- `LEVEL_EATER` (activated): L179: * Ceiling: cannot-be-Tributed-except-for-Tribute-Summon needs tribute hooks. */
- `THE_AGENT_OF_JUDGMENT_SATURN` (activated): L39: /* skip Battle Phase this turn needs phase-lock hook. Ceiling: tribute
- `ARCANA_FORCE_VI_THE_LOVERS` (permanent): L48: tribute engine not wired — unk4 marks double-tribute / no-tribute only.

## `stat.Continuous` (1)

- `EVIL_HERO_MALICIOUS_BANE` (activated): L105: +200 ATK each via tempStage (~500/unit); attack lock only marks self unk4.

## `ui.Choice` (3)

- `DARK_ARMED_DRAGON` (activated): L317: auto-target. No GY picker (DeckMenu screen switch corrupts VRAM from inside monster effect handler) and no PickZone cursor state (200 conflicts with game loop after MonsterActionMenu case 4 returns). Picks the best field target via AiPickTarget logic. Upgrade path: dedicated cursor state + A/B handlers like Cannon Soldier.
- `DESTINY_HERO_DREADNOUGHT_SERVANT` (activated): L78: auto-pick first opp card; upgrade: PickZone targeting.
- `OJAMA_KING` (activated): L54: PickZone for up to 3 empty zones + continuous lock gate. FirstEmptyZoneInRow today — same as Ground Collapse).

## `op.Search` (8)

- `SPELL_CHRONICLE` (spell): L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished; cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.
- `ATLANTEAN_DRAGOONS` (activated): L137: * Ceiling: sent-for-WATER-effect search needs send hook.
- `DIVINER_OF_THE_HERALD` (activated): L84: Extra Deck Fairy mill skipped.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L63: cannot attack without Fusion Monster needs attack gate. Not field-ignition activatable; discard search uses FromHand path.
- `HARPIE_HARPIST` (activated): L198: * Ceiling: GY End Phase search (Lv4 WB ≤1500 ATK) needs EP hook.
- `JAIN_TWILIGHTSWORN_GENERAL` (activated): L232: * EP mill 2 via TryApplyTwilightswornEndPhase. Ceiling: other-Lightsworn-
- `PUNISHMENT_DRAGON` (activated): L193: * banished into Decks (EffectOpt). Ceiling: LS mill 4 needs effect-activation
- `ELEMENTAL_HERO_FLASH` (permanent): L47: no banished-zone + no multi-card GY search yet — banish 3 E-Heroes and add Normal Spell from GY deferred until banish + GY targeting exist. Battle-destruction GY trigger wired above.

## `op.BanishTimed` (8)

- `SPELL_CHRONICLE` (spell): L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn; briefly hits GY; upgrade: direct deck→RFG.
- `ANCIENT_GEAR_DUEL` (trap): L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks; mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand-in from Deck/hand.
- `ANGELS_TEAR` (trap): L342: need 4 banish targets plus 1 summon target.
- `BEAST_MACHINE_KING_BARBAROS_UR` (activated): L224: multi-zone banish picker not wired; require both types reachable.
- `CROSS_KEEPER` (activated): L171: Fusion leave ≈ E-HERO Fusion SS while CK in GY; draw1 stand-in for banish→draw2→bottom. Upgrade: true SS trigger + banish cost.
- `HERALD_OF_THE_ARC_LIGHT` (activated): L13: * Ceiling: not field-ignition activatable here; upgrade: continuous banish +
- `MORPHTRONIC_SMARTFON` (activated): L228: reveal UI FALSE; ATK die excavate add; DEF GY add Morphtronic. FromHand: banish Morphtronic GY → SS.
- `DESTINY_HERO_DOOM_OVERLORD` (permanent): L327: banish-until-Standby = permanent banish; DARK HERO SS lock not wired.

## `other` (74)

- `FUSION_DESTINY` (spell): L34: * Ceiling: incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous,
- `FUSION_DESTINY` (spell): L36: * Ceiling: Destiny End Dragoon only; upgrade: add remaining Destiny HERO Fusion
- `SCAPEGOAT` (spell): L10: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. SHEEP_TOKEN card data + art, then swap this define.
- `SCAPEGOAT` (spell): L74: LockMonsterCardsInRow also blocks Normal Set of monsters. distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.
- `SECRETS_OF_DARK_MAGIC` (spell): L34: * Ceiling: incomplete vs printed DM Fusion pool (Dragon Knight, etc.).
- `SECRETS_OF_DARK_MAGIC` (spell): L35: * Ceiling: Amulet Dragon + The Dark Magicians only; upgrade: add remaining DM
- `DARK_SUPREMACY` (trap): L38: "Spells that mention Dark Fusion" not scanned by text.
- `FAVOURITE_CONTACT` (trap): L48: Extra Deck Fusion ignoring summon conditions + materials to Deck bottom need fusion recipe API; return up to 2 HERO/Neos/ Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free.
- `AMAZONESS_PET_LIGER_KING` (activated): L192: * Ceiling: attack redirect FALSE. */
- `AMAZONESS_SPIRITUALIST` (activated): L105: * Ceiling: hand/GY bounce→SS + ED lock need GY/ED hooks. */
- `ANCIENT_GEAR_MEGATON_GOLEM` (activated): L140: Extra Deck Ultimate AG Golem SS blocked — AG Golem from hand/GY/Deck instead.
- `APPRENTICE_ILLUSION_MAGICIAN` (activated): L164: * Ceiling: hand/field send +2000 Quick need damage hooks. */
- `ARCANA_FORCE_V_THE_HIEROPHANT` (activated): L198: discard only; opp cannot respond to Arcana Summons needs turn flag hook.
- `AROMAGE_JASMINE` (activated): L58: * Ceiling: extra Plant Normal Summon needs second NS allowance. */
- `ATLANTEAN_MARKSMAN` (activated): L149: * Ceiling: sent-for-WATER destroy Set S/T needs send hook. */
- `CLEAR_VICE_DRAGON` (activated): L72: * Ceiling: Clear World immunity + discard-to-save need continuous/destruction hooks. */
- `DARK_ARMED_DRAGON` (activated): L174: allow self-target for faithful TCG simulation; player can choose suboptimally
- `DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE` (activated): L96: * Ceiling: name=DMG GY +300 mention FALSE. */
- `DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE` (activated): L96: * Ceiling: name=DMG GY +300 mention FALSE. */
- `DARKBLAZE_DRAGON` (activated): L83: * Ceiling: GY SS double original ATK/DEF needs SS-origin flag. */
- `DARKNESS_NEOSPHERE` (activated): L87: battle indestruct + trap bounce + attack-declare gate need battle/ phase hooks. Ceiling: not field-ignition activatable; SS uses FromHand path.
- `DARKNESS_NEOSPHERE` (activated): L113: opp attack declare gate not wired; require 1 field + 1 hand Fiend.
- `DESTINY_HERO_DESTROY_DOGMA` (activated): L103: /* Standby burn via TryApplyDestinyHeroDestroyDogmaStandby. Ceiling: Quick
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L154: second target picker not chained; auto-destroy best remaining card.
- `DESTINY_HERO_DIAMOND_DUDE` (activated): L57: next-turn GY Normal Spell activation needs Main Phase hook.
- `DESTINY_HERO_DREADNOUGHT_MASTER` (activated): L119: * Ceiling: cards-mentioning-D-HERO FALSE.
- `DESTINY_HERO_DYSTOPIA` (activated): L225: printed is on-SS; any placement stand-in. Auto-pick highest ATK.
- `DIVINE_SERPENT_GEH` (activated): L42: * Ceiling: field ignition FALSE. */
- `EL_SHADDOLL_MESHAHRAIL` (activated): L76: * Ceiling: unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks. */
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L177: multi-target picker not wired; auto-destroy highest-value opp cards.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L159: Dark Fusion Fusion markers missing; any Fusion Monster stand-in.
- `EVIL_HERO_INFERNAL_RIDER` (activated): L270: * Ceiling: HERO lock need SS gates. */
- `EVIL_HERO_NEOS_LORD` (activated): L186: * Ceiling: indestructible + opp-GY-sent take-control need continuous/send hooks.
- `EVOLZAR_DOLKKA` (activated): L13: * Ceiling: not field-ignition here. */
- `GORZ_THE_EMISSARY_OF_DARKNESS` (activated): L35: * Ceiling: FromHand empty-field SS. */
- `GRAVEKEEPERS_WATCHER` (activated): L16: * hooks. Ceiling: not field-ignition; discard-from-hand path below. */
- `HARPIE_CONDUCTOR` (activated): L133: any other Harpie leave ≈ return-to-hand; upgrade: true bounce-origin flag.
- `HARPIE_CONDUCTOR` (activated): L231: protect destroy redirect needs destroy-sub hook.
- `HERALD_OF_PERFECTION` (activated): L13: * Ceiling: not field-ignition activatable here; upgrade: either-turn chain
- `HERALD_OF_ULIMATENESS` (activated): L13: * Ceiling: not field-ignition activatable here; upgrade: either-turn chain
- `HERALD_OF_ULTIMATENESS` (activated): L13: * Ceiling: not field-ignition activatable here; upgrade: either-turn chain
- `LEVIAIR_THE_SEA_DRAGON` (activated): L63: * Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt. */
- `LIGHTSWORN_DRAGONLING` (activated): L104: exact 3000/2600 preferred; BEWD fallback if none.
- `LUMINA_TWILIGHTSWORN_SHAMAN` (activated): L226: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.
- `MAGICAL_SCIENTIST` (activated): L216: * Ceiling: pay 1000 → SS Lv≤6 Fusion from Extra/recipe list. */
- `MAGICIANS_ROBE` (activated): L57: * Ceiling: discard S/T from hand → SS DM from Deck via FromHand path. */
- `MAN_THRO_TRO` (activated): L21: Ojama Trio monster form is the only token-like field unit today
- `MANJU_OF_THE_TEN_THOUSAND_HANDS` (activated): L113: once via usage if Ritual Monster or Ritual Spell in Deck and hand space.
- `MORPHTRONIC_EARFON` (activated): L94: Equip 2-attacks FALSE. On-SS mark self as Tuner (unk4).
- `MORPHTRONIC_LANTRON` (activated): L98: * Ceiling: ATK effect-damage redirect needs effect-damage hook. */
- `MORPHTRONIC_TELEFON` (activated): L176: reveal UI FALSE; ATK die→LP+SS Morph Lv≤roll; DEF die excavate add.
- `NIBIRU_THE_PRIMAL_BEING` (activated): L91: * Ceiling: FromHand wipe+SS if ≥5 face-up monsters on field. */
- `QUINTET_MAGICIAN` (activated): L115: * Ceiling: untributable/undestroyable need continuous hooks.
- `RINYAN_LIGHTSWORN_ROGUE` (activated): L41: /* FLIP trigger needs flip hook. Ceiling: once via usage if LS in GY. */
- `ROYAL_MAGICAL_LIBRARY` (activated): L23: * Ceiling: ignition only when unk4>=3. */
- `RYKO_LIGHTSWORN_HUNTER` (activated): L107: /* FLIP trigger needs flip hook. Ceiling: once via usage. */
- `SKILLED_DARK_MAGICIAN` (activated): L81: * Ceiling: ignition when unk4>=3. */
- `SKILLED_WHITE_MAGICIAN` (activated): L81: * Ceiling: ignition when unk4>=3. */
- `SOUL_ABSORBING_BONE_TOWER` (activated): L92: * Ceiling: attack redirect while another Zombie present needs battle hooks.
- `THE_AGENT_OF_LIFE_NEPTUNE` (activated): L161: * Ceiling: FromHand discard self → SS Agent (or Hyperion if Sanctuary). */
- `TIME_MAGIC_HAMMER` (activated): L13: * Ceiling: not field-ignition activatable here. */
- `TIMEAUS_THE_UNITED_DRAGON` (activated): L148: * Ceiling: SS from hand via send cost uses FromHand path. */
- `TORNADO_BIRD` (activated): L85: /* FLIP trigger needs flip hook. Ceiling: once via usage. */
- `ULTIMATE_OBEDIENT_FIEND` (activated): L13: * Ceiling: not field-ignition activatable here. */
- `ULTIMATE_TYRANNO` (activated): L13: * Ceiling: not field-ignition activatable here. */
- `VISION_HERO_GRAVITO` (activated): L65: no RemovedFromPlay_RemoveAt — shift RFP array in place after add. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- `ARCANA_FORCE_I_THE_MAGICIAN` (permanent): L68: spell-trigger heads/tails not wired.
- `ARCANA_FORCE_XVIII_THE_MOON` (permanent): L48: Standby Moon Token / End Phase give-control need turn hooks; unk4 only.
- `ARCANA_FORCE_XXI_THE_WORLD` (permanent): L48: skip-turn / opp GY-to-hand need turn hooks; unk4 marks coin only.
- `DARK_MAGICIAN_OF_DESTRUCTION` (permanent): L131: deck-first add; DM preferred by scan order, no picker.
- `DESTINY_HERO_DRAWHAND` (permanent): L140: HERO-effect SS gate not checked.
- `DESTINY_HERO_DREADMASTER` (permanent): L284: Clock Tower Prison gate skipped. D-HERO battle protect + no BD via DestinyHeroDreadmaster_* while face-up.
- `HERO_KID` (permanent): L76: true trigger is Special Summon of Level 4 or lower HERO.
- `REPTILIANNE_SERVANT` (permanent): L120: * Ceiling: spell-target destroy needs continuous hook. */
