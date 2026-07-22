# Partial Effects Taxonomy

Auto-generated companion to [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md).
Each `ponytail:` / `Ceiling:` note is tagged with its **primary missing engine surface** so Phase work in [`effect-data-system.md`](effect-data-system.md) can target events/ops that unblock many cards at once.

```bash
python3 tools/stub_effect_queue.py --write-list
```

**Last updated:** 2026-07-22 21:19 UTC  
**Ceiling lines tagged:** `90`  
**Partial files:** `72`

## Counts by missing surface

| Tag | Count | Suggested phase |
|-----|------:|-----------------|
| `other` | 32 | triage |
| `event.OnStandby` | 12 | 3 (OPT / turn flags) |
| `chain.Negate` | 11 | later / chain |
| `gate.Tribute` | 6 | 2–3 |
| `op.Search` | 6 | 1 |
| `extra.XyzLinkSynchro` | 5 | later / Extra Deck |
| `op.BanishTimed` | 5 | 1–3 |
| `event.OnSummon` | 4 | 3 |
| `event.OnBattleDestroy` | 3 | 3 |
| `ui.Choice` | 2 | 2 |
| `event.GyIgnition` | 1 | 3 |
| `event.OnDestroy` | 1 | 3 |
| `event.OnLpGain` | 1 | later / LP event |
| `stat.Continuous` | 1 | 1–3 |
| **total** | **90** | |

Highest-ROI unblock for this backlog is usually **`event.OnStandby` (OPT)** plus destroy/summon/battle listeners (Phase 3), not per-card rewrites.

## `event.OnBattleDestroy` (3)

- `AMAZONESS_HOT_SPRING` (trap): L46: * Ceiling: Pendulum Zone place + battle-damage gain LP OPT need hooks. */
- `ARMORY_ARM` (activated): L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE.
- `EVIL_HERO_WILD_CYCLONE` (permanent): L97: * Ceiling: attack S/T lock until end of Damage Step needs chain gate. */

## `event.OnDestroy` (1)

- `SPELL_CHRONICLE` (spell): L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. Ceiling: activate discard+banish 5 only; unk4 counter slot unused.

## `event.OnSummon` (4)

- `SHADDOLL_SCHISM` (trap): L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker; banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.
- `ANCIENT_GEAR_KNIGHT` (activated): L13: * Ceiling: Gemini Normal Monster treatment need summon hook. */
- `DESTINY_HERO_DUSKTOPIA` (activated): L47: * TryClearDestinyHeroDusktopiaProtectionEndPhase. Ceiling: Fusion on Summon
- `VISION_HERO_GRAVITO` (activated): L114: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip zone API. OPT add 1 banished HERO monster to hand (EffectOpt; on-summon stand-in).

## `event.OnStandby` (12)

- `DARK_SUPREMACY` (trap): L53: GY banish shuffle HERO need GY ignition OPT. Ceiling: negate up to count face-up opp cards (monsters first) via unk4.
- `ARCANITE_MAGICIAN` (activated): L160: Synchro +2 Spell Counters + +1000 ATK/counter need synchro/stat hooks. OPT remove 1 unk4 counter → destroy 1 opp (EffectOpt).
- `AROMAGE_ROSEMARY` (activated): L127: LP-higher Plant attack → opp monster effects locked need permanent/battle hooks. LP-gain position change via aroma_lp_gain.c. OPT change 1 face-up battle position (EffectOpt).
- `ATLANTEAN_HEAVY_INFANTRY` (activated): L111: extra Normal Summon Sea Serpent + sent-for-WATER destroy need summon/send hooks. OPT destroy 1 Set Spell/Trap.
- `CASTEL_THE_SKY_BLASTER_MUSKETEER` (activated): L138: detach/material + face-down branch need overlay engine. OPT return 1 face-up monster to the Deck.
- `DEEP_SEA_DIVA` (activated): L101: /* NS SS via TryDeepSeaDivaOnNormalSummon. Ceiling: OPT duplicate if NS already
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. OPT destroy 1 you control + 1 other field card.
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. OPT destroy opp cards up to different Attributes.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L86: once-per-turn not tracked without turn hook.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L110: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE. OPT mill 1 HERO from Deck (EffectOpt).
- `EVIL_HERO_MALICIOUS_BANE` (activated): L75: destruction immunity + HERO-only attack gate need destroy/attack hooks. OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4.
- `MORPHTRONIC_EARFON` (activated): L53: real Tuner flag / Equip double-attack need Synchro/equip hooks. OPT PickZone mark unk4 as Tuner stand-in.

## `event.GyIgnition` (1)

- `BLUE_EYES_ULTIMATE_SPIRIT_DRAGON` (activated): L25: * Ceiling: Quick field negate + destroy-SS FALSE; GY banish-lock FALSE. */

## `event.OnLpGain` (1)

- `AMAZONESS_HALL` (trap): L43: * Ceiling: Extra Deck / Pendulum place + opp SS gain LP need hooks. */

## `extra.XyzLinkSynchro` (5)

- `SHADDOLL_CORE` (trap): L45: true trap-monster (still a Trap) + Attribute fusion substitute need Embodiment-style link; place SHADDOLL_CORE on monster row and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate.
- `URGENT_TUNING` (trap): L14: Synchro Summon during Battle Phase needs Synchro material/ED summon path outside this file (no in-file Synchro API). → Extra Deck Synchro SS.
- `CURIOUS_THE_LIGHTSWORN_DOMINION` (activated): L146: * Ceiling: Link Summon mill + mill-cascade need summon/send hooks.
- `LEVEL_EATER` (activated): L123: * Ceiling: SS self from GY; upgrade: TempLevel overlay on target. */
- `HARPIES_PET_PHANTASMAL_DRAGON` (permanent): L9: * Ceiling: Harpie protect + End Phase detach need battle/xyz hooks. */

## `chain.Negate` (11)

- `ANCIENT_GEAR_ENGINEER` (activated): L14: * Ceiling: opp Trap activation negate on attack needs chain gate. */
- `ASH_BLOSSOM_AND_JOYOUS_SPRING` (activated): L50: chain negate for add/SS/mill from Deck not wired; upgrade: chain interrupt hook when one exists.
- `DESTINY_HERO_DARK_ANGEL` (activated): L81: field spell-negate FALSE. Ceiling: FromHand discard → SS D-HERO to opp DEF.
- `DESTINY_HERO_DESTROY_DOGMA` (activated): L104: * destroy/negate FALSE. Ceiling: FromHand banish 3 Warrior/DARK → SS + burn 2000. */
- `DESTINY_HERO_PLASMA` (activated): L95: equip/absorb + half-ATK boost + continuous opp negate need equip hooks. Ceiling: destroy 1 opp monster.
- `DIVINE_SERPENT_GEH` (activated): L41: * Ceiling: destroy gate + battle negate need destroy/battle hooks.
- `HORUS_THE_BLACK_FLAME_DRAGON_LV8` (activated): L13: * Ceiling: either-turn Spell negate needs chain hook. */
- `LYLA_TWILIGHTSWORN_ENCHANTRESS` (activated): L208: * EP mill 3 via TryApplyTwilightswornEndPhase. Ceiling: quick effect on
- `RYKO_TWILIGHTSWORN_FIGHTER` (activated): L204: NS mill 3 stand-in for other-LS effect→mill; upgrade: chain hook.
- `EL_SHADDOLL_GRYSTA` (permanent): L126: negate opp Special Summon + send Shaddoll from hand need SS chain hook.
- `EL_SHADDOLL_SHEKHINAGA` (permanent): L126: negate SS monster effect + send Shaddoll need effect-chain hook.

## `gate.Tribute` (6)

- `LEV_SHADDOLL_FUSION` (spell): L158: the face-up ignition still needs a monster-zone tribute picker and an Extra Deck special-summon flow, neither of which is owned by this spell activation dispatcher.
- `SCAPEGOAT` (spell): L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. SCAPEGOAT_TOKEN_ID / token flag.
- `ANDRO_SPHINX` (activated): L64: * Ceiling: GY SS ban needs summon gate. */
- `GAMECIAL_THE_SEA_TURTLE_KAIJU` (activated): L69: * Ceiling: FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju). */
- `LEVEL_EATER` (activated): L179: * Ceiling: cannot-be-Tributed-except-for-Tribute-Summon needs tribute hooks. */
- `THE_AGENT_OF_JUDGMENT_SATURN` (activated): L39: /* skip Battle Phase this turn needs phase-lock hook. Ceiling: tribute

## `stat.Continuous` (1)

- `EVIL_HERO_MALICIOUS_BANE` (activated): L105: +200 ATK each via tempStage (~500/unit); attack lock only marks self unk4.

## `ui.Choice` (2)

- `DESTINY_HERO_DREADNOUGHT_SERVANT` (activated): L78: auto-pick first opp card; upgrade: PickZone targeting.
- `OJAMA_KING` (activated): L54: PickZone for up to 3 empty zones + continuous lock gate. FirstEmptyZoneInRow today — same as Ground Collapse).

## `op.Search` (6)

- `SPELL_CHRONICLE` (spell): L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished; cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.
- `ATLANTEAN_DRAGOONS` (activated): L137: * Ceiling: sent-for-WATER-effect search needs send hook.
- `DIVINER_OF_THE_HERALD` (activated): L84: Extra Deck Fairy mill skipped.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L63: cannot attack without Fusion Monster needs attack gate. Not field-ignition activatable; discard search uses FromHand path.
- `JAIN_TWILIGHTSWORN_GENERAL` (activated): L232: * EP mill 2 via TryApplyTwilightswornEndPhase. Ceiling: other-Lightsworn-
- `ELEMENTAL_HERO_FLASH` (permanent): L47: no banished-zone + no multi-card GY search yet — banish 3 E-Heroes and add Normal Spell from GY deferred until banish + GY targeting exist. Battle-destruction GY trigger wired above.

## `op.BanishTimed` (5)

- `SPELL_CHRONICLE` (spell): L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn; briefly hits GY; upgrade: direct deck→RFG.
- `ANCIENT_GEAR_DUEL` (trap): L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks; mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand-in from Deck/hand.
- `ANGELS_TEAR` (trap): L342: need 4 banish targets plus 1 summon target.
- `BEAST_MACHINE_KING_BARBAROS_UR` (activated): L224: multi-zone banish picker not wired; require both types reachable.
- `CROSS_KEEPER` (activated): L171: Fusion leave ≈ E-HERO Fusion SS while CK in GY; draw1 stand-in for banish→draw2→bottom. Upgrade: true SS trigger + banish cost.

## `other` (32)

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
- `DESTINY_HERO_DESTROY_DOGMA` (activated): L103: /* Standby burn via TryApplyDestinyHeroDestroyDogmaStandby. Ceiling: Quick
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L154: second target picker not chained; auto-destroy best remaining card.
- `DESTINY_HERO_DYSTOPIA` (activated): L225: printed is on-SS; any placement stand-in. Auto-pick highest ATK.
- `DIVINE_SERPENT_GEH` (activated): L42: * Ceiling: field ignition FALSE. */
- `EL_SHADDOLL_MESHAHRAIL` (activated): L76: * Ceiling: unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks. */
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L177: multi-target picker not wired; auto-destroy highest-value opp cards.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L159: Dark Fusion Fusion markers missing; any Fusion Monster stand-in.
- `EVIL_HERO_NEOS_LORD` (activated): L186: * Ceiling: indestructible + opp-GY-sent take-control need continuous/send hooks.
- `GORZ_THE_EMISSARY_OF_DARKNESS` (activated): L35: * Ceiling: FromHand empty-field SS. */
- `HARPIE_CONDUCTOR` (activated): L133: any other Harpie leave ≈ return-to-hand; upgrade: true bounce-origin flag.
- `HARPIE_CONDUCTOR` (activated): L231: protect destroy redirect needs destroy-sub hook.
- `MAGICAL_SCIENTIST` (activated): L216: * Ceiling: pay 1000 → SS Lv≤6 Fusion from Extra/recipe list. */
- `MORPHTRONIC_EARFON` (activated): L94: Equip 2-attacks FALSE. On-SS mark self as Tuner (unk4).
- `NIBIRU_THE_PRIMAL_BEING` (activated): L91: * Ceiling: FromHand wipe+SS if ≥5 face-up monsters on field. */
- `THE_AGENT_OF_LIFE_NEPTUNE` (activated): L161: * Ceiling: FromHand discard self → SS Agent (or Hyperion if Sanctuary). */
- `VISION_HERO_GRAVITO` (activated): L65: no RemovedFromPlay_RemoveAt — shift RFP array in place after add. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- `REPTILIANNE_SERVANT` (permanent): L120: * Ceiling: spell-target destroy needs continuous hook. */
