# Partial Effects Taxonomy

Auto-generated companion to [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md).
Each `ponytail:` / `Ceiling:` note is tagged with its **primary missing engine surface** so Phase work in [`effect-data-system.md`](effect-data-system.md) can target events/ops that unblock many cards at once.

```bash
python3 tools/stub_effect_queue.py --write-list
```

**Last updated:** 2026-07-22 20:10 UTC  
**Ceiling lines tagged:** `238`  
**Partial files:** `213`

## Counts by missing surface

| Tag | Count | Suggested phase |
|-----|------:|-----------------|
| `other` | 102 | triage |
| `event.OnStandby` | 48 | 3 (OPT / turn flags) |
| `extra.XyzLinkSynchro` | 18 | later / Extra Deck |
| `chain.Negate` | 14 | later / chain |
| `gate.Tribute` | 14 | 2–3 |
| `event.OnSummon` | 8 | 3 |
| `op.BanishTimed` | 8 | 1–3 |
| `op.Search` | 7 | 1 |
| `event.OnBattleDestroy` | 5 | 3 |
| `ui.Choice` | 5 | 2 |
| `event.OnFusionSummon` | 3 | 3 (fusion callback) |
| `event.GyIgnition` | 2 | 3 |
| `event.OnDestroy` | 2 | 3 |
| `event.OnLpGain` | 1 | later / LP event |
| `stat.Continuous` | 1 | 1–3 |
| **total** | **238** | |

Highest-ROI unblock for this backlog is usually **`event.OnStandby` (OPT)** plus destroy/summon/battle listeners (Phase 3), not per-card rewrites.

## `event.OnBattleDestroy` (5)

- `AMAZONESS_HOT_SPRING` (trap): L46: * Ceiling: Pendulum Zone place + battle-damage gain LP OPT need hooks. */
- `ARMORY_ARM` (activated): L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE.
- `DESTINY_HERO_DREAMER` (activated): L130: * Ceiling: true damage-calc GY SS timing needs battle hook. */
- `HONEST` (activated): L95: /* Damage Step hand discard uses FromHand path. Ceiling: Main Phase
- `EVIL_HERO_WILD_CYCLONE` (permanent): L97: * Ceiling: attack S/T lock until end of Damage Step needs chain gate. */

## `event.OnDestroy` (2)

- `SPELL_CHRONICLE` (spell): L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. Ceiling: activate discard+banish 5 only; unk4 counter slot unused.
- `ANCIENT_GEAR_MEGATON_GOLEM` (activated): L124: * Ceiling: multi-attack + leave-field SS FALSE. */

## `event.OnSummon` (8)

- `SHADDOLL_SCHISM` (trap): L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker; banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.
- `ANCIENT_GEAR_KNIGHT` (activated): L13: * Ceiling: Gemini Normal Monster treatment need summon hook. */
- `ARCANA_FORCE_XV_THE_FIEND` (activated): L271: on-summon heads auto-picks first destroyable opp monster.
- `DARKLORD_DESIRE` (activated): L116: Fairy-only Tribute Summon + cannot SS need summon hooks. OPT -1000 ATK (tempStage) → send 1 opp monster to GY.
- `DESTINY_HERO_DUSKTOPIA` (activated): L47: * TryClearDestinyHeroDusktopiaProtectionEndPhase. Ceiling: Fusion on Summon
- `EVIL_HERO_NEOS_LORD` (activated): L144: indestructible + on-SS/opp-GY-sent take-control triggers need continuous/summon hooks; OPT take control of 1 face-up opp monster.
- `ARCANA_FORCE_III_THE_EMPRESS` (permanent): L48: opp Normal Summon SS/discard triggers need summon hooks; unk4 only.
- `EVIL_HERO_INFERNO_WING_BACKFIRE` (permanent): L155: true trigger is Special Summon; on-summon stand-in covers SS path.

## `event.OnFusionSummon` (3)

- `ELEMENTAL_HERO_DARK_NEOS` (activated): L92: /* EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: contact Fusion need fusion hook. */
- `GLADIATOR_BEAST_GYZARUS` (activated): L175: * Ceiling: Contact Fusion SS destroy trigger + Extra Deck return. */
- `GLADIATOR_BEAST_ESSEDARII` (permanent): L8: Contact Fusion has no permanent ignition path.

## `event.OnStandby` (48)

- `DARK_SUPREMACY` (trap): L53: GY banish shuffle HERO need GY ignition OPT. Ceiling: negate up to count face-up opp cards (monsters first) via unk4.
- `ARCANA_FORCE_V_THE_HIEROPHANT` (activated): L86: discard summon-lock + FromHand paths. OPT coin → SS 1 Arcana Force from Deck.
- `ARCANA_FORCE_XV_THE_FIEND` (activated): L206: discard search + FromHand paths. OPT coin → destroy 1 monster or wipe field.
- `ARCANITE_MAGICIAN` (activated): L158: Synchro +2 Spell Counters + +1000 ATK/counter need synchro/stat hooks. OPT remove 1 unk4 counter (if >=1) → destroy 1 opp card.
- `AROMAGE_ROSEMARY` (activated): L125: LP-higher Plant attack → opp monster effects locked need permanent/battle hooks. LP-gain position change via aroma_lp_gain.c. OPT change 1 face-up battle position (ignition).
- `ATLANTEAN_HEAVY_INFANTRY` (activated): L111: extra Normal Summon Sea Serpent + sent-for-WATER destroy need summon/send hooks. OPT destroy 1 Set Spell/Trap.
- `BLUE_EYES_JET_DRAGON` (activated): L198: * Ceiling: field OPT bounce 1; FromHand if BEWD field/GY → SS.
- `BLUE_EYES_ULTIMATE_SPIRIT_DRAGON` (activated): L23: Quick field negate + destroy-SS FALSE; GY banish-lock FALSE. OPT +2 tempStage (~+1000) as negate stand-in.
- `CASTEL_THE_SKY_BLASTER_MUSKETEER` (activated): L138: detach/material + face-down branch need overlay engine. OPT return 1 face-up monster to the Deck.
- `CELESTIA_LIGHTSWORN_ANGEL` (activated): L140: * Ceiling: field OPT repeat (usage-gated). Auto-destroy up to 2 (no PickZone). */
- `CELESTIAL_KNIGHTLORD_PARSHATH` (activated): L104: Link material + GY banish Fairy → SS Fairy need send/banish hooks. OPT discard 1 → add Sanctuary/mention, or Fairy if Sanctuary on field.
- `CORAL_DRAGON` (activated): L114: GY draw when Synchro Summoned card sent from field needs GY hook. OPT discard 1 → destroy 1 opp card.
- `CRIMSON_DRAGON` (activated): L138: on-SS search + Extra Synchro return FALSE. OPT search mentioning Crimson Dragon S/T, else shuffle self → SS Dragon.
- `CYBER_DRAGON_INFINITY` (activated): L35: ATK summons keep isFaceUp=0 until EOT flip.
- `CYBER_SLASH_HARPIE_LADY` (activated): L196: Quick on S/T activation + Synchro/name hooks missing. OPT bounce 1 opp card or your Harpie to hand.
- `CYBER_SLASH_HARPY_LADY` (activated): L196: Quick on S/T activation + Synchro/name hooks missing. OPT bounce 1 opp card or your Harpie to hand.
- `DARK_HORUS` (activated): L99: after opp Main Phase Spell resolve trigger needs spell hook. OPT SS 1 Lv4 DARK from GY while face-up.
- `DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE` (activated): L61: name=DMG GY +300 mention FALSE. Ceiling: field OPT add Shining Sarcophagus from Deck.
- `DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE` (activated): L61: name=DMG GY +300 mention FALSE. Ceiling: field OPT add Shining Sarcophagus from Deck.
- `DECOY_DRAGON` (activated): L181: attack-target redirect needs battle targeting hook. OPT SS Lv7+ Dragon from GY once via usage when legal.
- `DEEP_SEA_DIVA` (activated): L101: /* NS SS via TryDeepSeaDivaOnNormalSummon. Ceiling: OPT duplicate if NS already
- `DESTINY_HERO_DENIER` (activated): L189: GY SS when other D-HERO present needs GY/once-per-duel hooks. OPT put 1 D-HERO from Deck/GY/banished on top of Deck.
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. OPT destroy 1 you control + 1 other field card.
- `EBON_ILLUSION_MAGICIAN` (activated): L78: Xyz detach cost + attack-banish FALSE. OPT SS Spellcaster Normal from hand/Deck (detach stand-in).
- `EL_SHADDOLL_MESHAHRAIL` (activated): L74: unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks. OPT pay 800 → add 1 Shaddoll or Void S/T from Deck.
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. OPT destroy opp cards up to different Attributes.
- `ELEMENTAL_HERO_SPIRIT_OF_NEOS` (activated): L154: attack-hand SS FALSE. OPT search Poly/E-HERO S/T, else OPT shuffle self → SS Normal E-HERO from Deck.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L86: once-per-turn not tracked without turn hook.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L109: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE. OPT mill 1 HERO from Deck.
- `EVIL_HERO_MALICIOUS_BANE` (activated): L75: destruction immunity + HERO-only attack gate need destroy/attack hooks. OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4.
- `GLADIATOR_BEAST_HERAKLINOS` (activated): L148: either-turn chain negate needs chain hook. OPT discard 1 → destroy 1 opponent card below.
- `JAIN_TWILIGHTSWORN_GENERAL` (activated): L229: other-Lightsworn-activated mill 2 needs chain hook. OPT banish 1 Lightsworn from hand/GY → weaken 1 face-up monster. EP mill 2 via TryApplyTwilightswornEndPhase.
- `LYLA_TWILIGHTSWORN_ENCHANTRESS` (activated): L205: quick effect on Spell/Trap activation + mill 3 when other LS activates need chain hooks. OPT banish LS from hand/GY then destroy 1 face-up Spell/Trap. EP mill 3 via TryApplyTwilightswornEndPhase.
- `MINERVA_LIGHTSWORN_MAIDEN` (activated): L125: * Ceiling: field OPT search LIGHT Dragon Lv≤ distinct LS names in GY. */
- `MORPHTRONIC_CELFON` (activated): L136: reveal/look UI missing; die roll + SS/add among top N. Ceiling: ATK OPT die→SS Lv≤4 Morphtronic; DEF OPT die→add Morphtronic.
- `MORPHTRONIC_EARFON` (activated): L48: real Tuner flag / Equip double-attack need Synchro/equip hooks. OPT PickZone mark unk4 as Tuner stand-in.
- `MORPHTRONIC_EARFON` (activated): L95: on-SS Tuner mark + Equip 2-attacks FALSE. OPT PickZone treat face-up as Tuner (unk4).
- `MORPHTRONIC_REMOTEN` (activated): L213: position-gated OPT search. ATK: banish GY Morphtronic → add same Lv. DEF: discard Morphtronic → add other same Lv.
- `MORPHTRONIC_SCANNEN` (activated): L194: FromHand banish Morphtronic → SS; ATK/DEF OPT search modes.
- `MORPHTRONIC_SCOPEN` (activated): L58: DEF Position → treat as Level 4 + EP destroy on ATK-mode SS need position/EP hooks; ATK Position OPT SS 1 Lv4 Morphtronic from hand.
- `MORPHTRONIC_SLINGEN` (activated): L160: DEF destroy-other-Morphtronic substitute needs destroy redirect hook. Ceiling: ATK OPT tribute 1 other Morphtronic → destroy 1 field card.
- `MORPHTRONIC_VACUUMEN` (activated): L24: send Equip → burn + DEF equip-take-control need equip hooks. Ceiling: ATK Position OPT burn 500.
- `RAIDEN_HAND_OF_THE_LIGHTSWORN` (activated): L61: /* EP mill via TryApplyRaidenEndPhase. Ceiling: Main Phase OPT mill 2. */
- `RYKO_TWILIGHTSWORN_FIGHTER` (activated): L191: NS/flip + other-Lightsworn mill 3 need summon/chain hooks. OPT banish LS from hand/GY then banish 1 field card; EP mill 3 via TryApplyTwilightswornEndPhase.
- `VISION_HERO_FARIS` (activated): L148: Continuous Trap place + ED HERO lock need place/ED hooks. OPT add 1 Vision HERO from Deck to hand wired below.
- `VISION_HERO_GRAVITO` (activated): L113: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip zone API. OPT add 1 banished HERO monster to hand.
- `VISION_HERO_INCREASE` (activated): L69: GY Continuous Trap place + tribute HERO SS-self FALSE. OPT SS Vision HERO Lv≤4 from Deck (ST-zone SS stand-in).
- `WEISS_LIGHTSWORN_ARCHFIEND` (activated): L167: /* sent-from-Deck-to-GY trigger needs mill/send hook. Ceiling: field OPT

## `event.GyIgnition` (2)

- `DESTINY_HERO_DREADNOUGHT_SERVANT` (activated): L89: GY banish destroy on Lv8 D-HERO SS FALSE. Ceiling: FromHand if control D-HERO or Field Spell → SS, destroy 1, add Poly.
- `DESTINY_HERO_DYNATAG` (activated): L134: GY banish ATK boost not wired; both players 1000 on FromHand.

## `event.OnLpGain` (1)

- `AMAZONESS_HALL` (trap): L43: * Ceiling: Extra Deck / Pendulum place + opp SS gain LP need hooks. */

## `extra.XyzLinkSynchro` (18)

- `SHADDOLL_CORE` (trap): L45: true trap-monster (still a Trap) + Attribute fusion substitute need Embodiment-style link; place SHADDOLL_CORE on monster row and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate.
- `URGENT_TUNING` (trap): L14: Synchro Summon during Battle Phase needs Synchro material/ED summon path outside this file (no in-file Synchro API). → Extra Deck Synchro SS.
- `CRIMSON_DRAGON` (activated): L123: Extra Deck Synchro SS FALSE; Deck Dragon stand-in.
- `CURIOUS_THE_LIGHTSWORN_DOMINION` (activated): L146: * Ceiling: Link Summon mill + mill-cascade need summon/send hooks.
- `CYBER_DRAGON_INFINITY` (activated): L62: Xyz attach / negate FALSE. Ceiling: ClearZone absorb + +1 tempStage.
- `GAGAGIGO_THE_RISEN` (activated): L12: Gagagigo the Risen has no printed monster effect (Xyz materials only). duel gate outside activated_effects.
- `LEVEL_EATER` (activated): L123: * Ceiling: SS self from GY; upgrade: TempLevel overlay on target. */
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
- `EVIL_HERO_TOXIC_BUBBLE` (activated): L89: HERO-only SS lock this turn needs summon gate.
- `FELIS_LIGHTSWORN_ARCHER` (activated): L102: * hook. Ceiling: ignition tribute self → destroy 1 opponent monster → mill 3. */
- `FLAME_RULER` (activated): L12: treat as 2 Tributes for FIRE Tribute Summon needs tribute-cost LynJump. gate outside this file.
- `FOG_KING` (activated): L13: * lock need summon/tribute continuous hooks. Ceiling: not field-ignition here. */
- `GAMECIAL_THE_SEA_TURTLE_KAIJU` (activated): L69: * Ceiling: FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju). */
- `GRAVEKEEPERS_VASSAL` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle
- `HOLACTIE_THE_CREATOR_OF_LIGHT` (activated): L65: * Ceiling: not field-ignition activatable; use FromHand tribute path. */
- `LEKUNGA` (activated): L13: * Ceiling: wrong Type/Attribute/stats (Fairy/LIGHT 0/0 vs Plant/WATER 700/700);
- `LEVEL_EATER` (activated): L179: * Ceiling: cannot-be-Tributed-except-for-Tribute-Summon needs tribute hooks. */
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
- `ATLANTEAN_DRAGOONS` (activated): L137: * Ceiling: sent-for-WATER-effect search needs send hook.
- `DIVINER_OF_THE_HERALD` (activated): L84: Extra Deck Fairy mill skipped.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L63: cannot attack without Fusion Monster needs attack gate. Not field-ignition activatable; discard search uses FromHand path.
- `HARPIE_HARPIST` (activated): L198: * Ceiling: GY End Phase search (Lv4 WB ≤1500 ATK) needs EP hook.
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

## `other` (102)

- `FUSION_DESTINY` (spell): L34: * Ceiling: incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous,
- `FUSION_DESTINY` (spell): L36: * Ceiling: Destiny End Dragoon only; upgrade: add remaining Destiny HERO Fusion
- `SCAPEGOAT` (spell): L10: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. SHEEP_TOKEN card data + art, then swap this define.
- `SCAPEGOAT` (spell): L74: LockMonsterCardsInRow also blocks Normal Set of monsters. distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.
- `SECRETS_OF_DARK_MAGIC` (spell): L34: * Ceiling: incomplete vs printed DM Fusion pool (Dragon Knight, etc.).
- `SECRETS_OF_DARK_MAGIC` (spell): L35: * Ceiling: Amulet Dragon + The Dark Magicians only; upgrade: add remaining DM
- `SPELL_GEAR` (spell): L156: * Ceiling: optional SS offered as auto-yes when legal; cannot skip
- `DARK_SUPREMACY` (trap): L38: "Spells that mention Dark Fusion" not scanned by text.
- `FAVOURITE_CONTACT` (trap): L48: Extra Deck Fusion ignoring summon conditions + materials to Deck bottom need fusion recipe API; return up to 2 HERO/Neos/ Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free.
- `AMAZONESS_PET_LIGER_KING` (activated): L192: * Ceiling: attack redirect FALSE. */
- `AMAZONESS_SPIRITUALIST` (activated): L105: * Ceiling: hand/GY bounce→SS + ED lock need GY/ED hooks. */
- `ANCIENT_GEAR_GADJILTRON_CHIMERA` (activated): L13: * Ceiling: not ignition-activatable. */
- `APPRENTICE_ILLUSION_MAGICIAN` (activated): L164: * Ceiling: hand/field send +2000 Quick need damage hooks. */
- `ARCANA_FORCE_V_THE_HIEROPHANT` (activated): L189: discard only; opp cannot respond to Arcana Summons needs turn flag hook.
- `ARCANA_FORCE_XIX_THE_SUN` (activated): L137: requires coin-toss card on field — skipped; SS anytime when legal.
- `AROMAGE_JASMINE` (activated): L58: * Ceiling: extra Plant Normal Summon needs second NS allowance. */
- `ATLANTEAN_MARKSMAN` (activated): L149: * Ceiling: sent-for-WATER destroy Set S/T needs send hook. */
- `CHIMERATECH_FORTRESS_DRAGON` (activated): L13: * Ceiling: not field-ignition activatable here. */
- `CHIMERATECH_MEGAFLEET_DRAGON` (activated): L13: * Ceiling: not field-ignition activatable here. */
- `CLEAR_VICE_DRAGON` (activated): L72: * Ceiling: Clear World immunity + discard-to-save need continuous/destruction hooks.
- `CLEAR_VICE_DRAGON` (activated): L73: * Ceiling: not ignition-activatable here. */
- `CROSS_KEEPER` (activated): L145: GY draw-on-E-HERO-Fusion need Fusion/GY hooks. Ceiling: send self → SS Elemental HERO or Neo-Spacian from hand/GY.
- `DARK_ARMED_DRAGON` (activated): L174: allow self-target for faithful TCG simulation; player can choose suboptimally
- `DARK_MAGICIAN_THE_DRAGON_KNIGHT` (activated): L65: * Ceiling: not ignition-activatable here. */
- `DARK_STRIKE_FIGHTER` (activated): L127: Main Phase 1 gate not wired; allow once via usage any main phase.
- `DARKBLAZE_DRAGON` (activated): L83: * Ceiling: GY SS double original ATK/DEF needs SS-origin flag. */
- `DARKNESS_NEOSPHERE` (activated): L87: battle indestruct + trap bounce + attack-declare gate need battle/ phase hooks. Ceiling: not field-ignition activatable; SS uses FromHand path.
- `DARKNESS_NEOSPHERE` (activated): L113: opp attack declare gate not wired; require 1 field + 1 hand Fiend.
- `DESTINY_HERO_CELESTIAL` (activated): L155: * Ceiling: GY draw-if-no-hand need GY hooks.
- `DESTINY_HERO_DECIDER` (activated): L114: /* EP add on NS/SS via TryApplyDestinyHeroDeciderEndPhase. Ceiling: GY quick
- `DESTINY_HERO_DESTROY_DOGMA` (activated): L103: /* Standby burn via TryApplyDestinyHeroDestroyDogmaStandby. Ceiling: Quick
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L154: second target picker not chained; auto-destroy best remaining card.
- `DESTINY_HERO_DIAMOND_DUDE` (activated): L57: next-turn GY Normal Spell activation needs Main Phase hook.
- `DESTINY_HERO_DISK_COMMANDER` (activated): L28: printed is SS from GY once per Duel; any-placement + EffectOpt stand-in.
- `DESTINY_HERO_DOMINANCE` (activated): L66: look+reorder UI missing; RandRange shuffle of top N is stand-in.
- `DESTINY_HERO_DREADNOUGHT_MASTER` (activated): L119: * Ceiling: cards-mentioning-D-HERO FALSE.
- `DESTINY_HERO_DYSTOPIA` (activated): L225: printed is on-SS; any placement stand-in. Auto-pick highest ATK.
- `DIVINE_SERPENT_GEH` (activated): L42: * Ceiling: field ignition FALSE. */
- `EL_SHADDOLL_WENDIGO` (activated): L110: * Ceiling: GY add Shaddoll S/T on send not wired. */
- `ELEMENTAL_HERO_CHAOS_NEOS` (activated): L241: 3H Set-all needs set-from-deck hook; 2H/3H both shuffle all.
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L177: multi-target picker not wired; auto-destroy highest-value opp cards.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L151: Dark Fusion Fusion markers missing; any Fusion Monster stand-in.
- `EVIL_HERO_INFERNAL_RIDER` (activated): L270: * Ceiling: HERO lock need SS gates. */
- `EVIL_HERO_VICIOUS_CLAWS` (activated): L121: once-per-duel ≈ EffectOpt (turn); upgrade: duel-scoped latch.
- `EVOLZAR_DOLKKA` (activated): L13: * Ceiling: not field-ignition here. */
- `FUSILIER_DRAGON_THE_DUAL_MODE_BEAST` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon
- `GORZ_THE_EMISSARY_OF_DARKNESS` (activated): L35: * Ceiling: FromHand empty-field SS. */
- `GRANMARG_THE_ROCK_MONARCH` (activated): L159: * Ceiling: once via usage if Set target. */
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
- `LIGHTSWORN_DRAGONLING` (activated): L191: * Ceiling: GY-send add Dragon 3000 ATK/2600 DEF needs leave/send hook.
- `LUMINA_TWILIGHTSWORN_SHAMAN` (activated): L226: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.
- `MAGICAL_PLANT_MANDRAGOLA` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon
- `MAGICAL_SCIENTIST` (activated): L216: * Ceiling: pay 1000 → SS Lv≤6 Fusion from Extra/recipe list. */
- `MAGICIANS_ROBE` (activated): L57: * Ceiling: discard S/T from hand → SS DM from Deck via FromHand path. */
- `MAN_THRO_TRO` (activated): L21: Ojama Trio monster form is the only token-like field unit today
- `MANJU_OF_THE_TEN_THOUSAND_HANDS` (activated): L113: once via usage if Ritual Monster or Ritual Spell in Deck and hand space.
- `MIRROR_FORCE_DRAGON` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: trigger destroy-all. */
- `MOLTEN_ZOMBIE` (activated): L28: printed is SS from GY; any placement stand-in.
- `MORPHTRONIC_LANTRON` (activated): L98: * Ceiling: ATK effect-damage redirect needs effect-damage hook. */
- `MORPHTRONIC_TELEFON` (activated): L176: reveal UI FALSE; ATK die→LP+SS Morph Lv≤roll; DEF die excavate add.
- `NATURIA_BEAST` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: either-turn interrupt. */
- `NEO_SPACIAN_DARK_PANTHER` (activated): L13: * Ceiling: not ignition-activatable here; upgrade: permanent/name/effect copy. */
- `NIBIRU_THE_PRIMAL_BEING` (activated): L91: * Ceiling: FromHand wipe+SS if ≥5 face-up monsters on field. */
- `PREDAPLANT_VERTE_ANACONDA` (activated): L130: * hooks. Ceiling: pay 2000 LP → destroy 1 field card. */
- `PUNISHMENT_DRAGON` (activated): L192: * effect-activation hook. Ceiling: pay 1000 → shuffle all banished into Decks. */
- `QUINTET_MAGICIAN` (activated): L115: * Ceiling: untributable/undestroyable need continuous hooks.
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
