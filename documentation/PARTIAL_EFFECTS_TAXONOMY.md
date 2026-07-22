# Partial Effects Taxonomy

Auto-generated companion to [`PARTIAL_EFFECTS.md`](PARTIAL_EFFECTS.md).
Each `ponytail:` / `Ceiling:` note is tagged with its **primary missing engine surface** so Phase work in [`effect-data-system.md`](effect-data-system.md) can target events/ops that unblock many cards at once.

```bash
python3 tools/stub_effect_queue.py --write-list
```

**Last updated:** 2026-07-22 21:22 UTC  
**Ceiling lines tagged:** `54`  
**Partial files:** `36`

## Counts by missing surface

| Tag | Count | Suggested phase |
|-----|------:|-----------------|
| `other` | 20 | triage |
| `event.OnStandby` | 9 | 3 (OPT / turn flags) |
| `chain.Negate` | 5 | later / chain |
| `op.BanishTimed` | 4 | 1–3 |
| `extra.XyzLinkSynchro` | 3 | later / Extra Deck |
| `gate.Tribute` | 3 | 2–3 |
| `op.Search` | 3 | 1 |
| `event.OnSummon` | 2 | 3 |
| `ui.Choice` | 2 | 2 |
| `event.OnBattleDestroy` | 1 | 3 |
| `event.OnDestroy` | 1 | 3 |
| `stat.Continuous` | 1 | 1–3 |
| **total** | **54** | |

Highest-ROI unblock for this backlog is usually **`event.OnStandby` (OPT)** plus destroy/summon/battle listeners (Phase 3), not per-card rewrites.

## `event.OnBattleDestroy` (1)

- `ARMORY_ARM` (activated): L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE.

## `event.OnDestroy` (1)

- `SPELL_CHRONICLE` (spell): L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. Ceiling: activate discard+banish 5 only; unk4 counter slot unused.

## `event.OnSummon` (2)

- `SHADDOLL_SCHISM` (trap): L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker; banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.
- `VISION_HERO_GRAVITO` (activated): L114: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip zone API. OPT add 1 banished HERO monster to hand (EffectOpt; on-summon stand-in).

## `event.OnStandby` (9)

- `DARK_SUPREMACY` (trap): L53: GY banish shuffle HERO need GY ignition OPT. Ceiling: negate up to count face-up opp cards (monsters first) via unk4.
- `ATLANTEAN_HEAVY_INFANTRY` (activated): L111: extra Normal Summon Sea Serpent + sent-for-WATER destroy need summon/send hooks. OPT destroy 1 Set Spell/Trap.
- `DEEP_SEA_DIVA` (activated): L101: /* NS SS via TryDeepSeaDivaOnNormalSummon. Ceiling: OPT duplicate if NS already
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. OPT destroy 1 you control + 1 other field card.
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. OPT destroy opp cards up to different Attributes.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L86: once-per-turn not tracked without turn hook.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L110: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE. OPT mill 1 HERO from Deck (EffectOpt).
- `EVIL_HERO_MALICIOUS_BANE` (activated): L75: destruction immunity + HERO-only attack gate need destroy/attack hooks. OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4.
- `MORPHTRONIC_EARFON` (activated): L53: real Tuner flag / Equip double-attack need Synchro/equip hooks. OPT PickZone mark unk4 as Tuner stand-in.

## `extra.XyzLinkSynchro` (3)

- `SHADDOLL_CORE` (trap): L45: true trap-monster (still a Trap) + Attribute fusion substitute need Embodiment-style link; place SHADDOLL_CORE on monster row and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate.
- `URGENT_TUNING` (trap): L14: Synchro Summon during Battle Phase needs Synchro material/ED summon path outside this file (no in-file Synchro API). → Extra Deck Synchro SS.
- `LEVEL_EATER` (activated): L123: * Ceiling: SS self from GY; upgrade: TempLevel overlay on target. */

## `chain.Negate` (5)

- `DESTINY_HERO_DARK_ANGEL` (activated): L81: field spell-negate FALSE. Ceiling: FromHand discard → SS D-HERO to opp DEF.
- `DESTINY_HERO_DESTROY_DOGMA` (activated): L104: * destroy/negate FALSE. Ceiling: FromHand banish 3 Warrior/DARK → SS + burn 2000. */
- `DESTINY_HERO_PLASMA` (activated): L95: equip/absorb + half-ATK boost + continuous opp negate need equip hooks. Ceiling: destroy 1 opp monster.
- `DIVINE_SERPENT_GEH` (activated): L41: * Ceiling: destroy gate + battle negate need destroy/battle hooks.
- `RYKO_TWILIGHTSWORN_FIGHTER` (activated): L204: NS mill 3 stand-in for other-LS effect→mill; upgrade: chain hook.

## `gate.Tribute` (3)

- `LEV_SHADDOLL_FUSION` (spell): L158: the face-up ignition still needs a monster-zone tribute picker and an Extra Deck special-summon flow, neither of which is owned by this spell activation dispatcher.
- `SCAPEGOAT` (spell): L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. SCAPEGOAT_TOKEN_ID / token flag.
- `LEVEL_EATER` (activated): L179: * Ceiling: cannot-be-Tributed-except-for-Tribute-Summon needs tribute hooks. */

## `stat.Continuous` (1)

- `EVIL_HERO_MALICIOUS_BANE` (activated): L105: +200 ATK each via tempStage (~500/unit); attack lock only marks self unk4.

## `ui.Choice` (2)

- `DESTINY_HERO_DREADNOUGHT_SERVANT` (activated): L78: auto-pick first opp card; upgrade: PickZone targeting.
- `OJAMA_KING` (activated): L54: PickZone for up to 3 empty zones + continuous lock gate. FirstEmptyZoneInRow today — same as Ground Collapse).

## `op.Search` (3)

- `SPELL_CHRONICLE` (spell): L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished; cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.
- `DIVINER_OF_THE_HERALD` (activated): L84: Extra Deck Fairy mill skipped.
- `EVIL_HERO_ADUSTED_GOLD` (activated): L63: cannot attack without Fusion Monster needs attack gate. Not field-ignition activatable; discard search uses FromHand path.

## `op.BanishTimed` (4)

- `SPELL_CHRONICLE` (spell): L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn; briefly hits GY; upgrade: direct deck→RFG.
- `ANCIENT_GEAR_DUEL` (trap): L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks; mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand-in from Deck/hand.
- `BEAST_MACHINE_KING_BARBAROS_UR` (activated): L224: multi-zone banish picker not wired; require both types reachable.
- `CROSS_KEEPER` (activated): L171: Fusion leave ≈ E-HERO Fusion SS while CK in GY; draw1 stand-in for banish→draw2→bottom. Upgrade: true SS trigger + banish cost.

## `other` (20)

- `FUSION_DESTINY` (spell): L34: * Ceiling: incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous,
- `FUSION_DESTINY` (spell): L36: * Ceiling: Destiny End Dragoon only; upgrade: add remaining Destiny HERO Fusion
- `SCAPEGOAT` (spell): L10: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. SHEEP_TOKEN card data + art, then swap this define.
- `SCAPEGOAT` (spell): L74: LockMonsterCardsInRow also blocks Normal Set of monsters. distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.
- `SECRETS_OF_DARK_MAGIC` (spell): L34: * Ceiling: incomplete vs printed DM Fusion pool (Dragon Knight, etc.).
- `SECRETS_OF_DARK_MAGIC` (spell): L35: * Ceiling: Amulet Dragon + The Dark Magicians only; upgrade: add remaining DM
- `DARK_SUPREMACY` (trap): L38: "Spells that mention Dark Fusion" not scanned by text.
- `FAVOURITE_CONTACT` (trap): L48: Extra Deck Fusion ignoring summon conditions + materials to Deck bottom need fusion recipe API; return up to 2 HERO/Neos/ Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free.
- `ANCIENT_GEAR_MEGATON_GOLEM` (activated): L140: Extra Deck Ultimate AG Golem SS blocked — AG Golem from hand/GY/Deck instead.
- `ARCANA_FORCE_V_THE_HIEROPHANT` (activated): L198: discard only; opp cannot respond to Arcana Summons needs turn flag hook.
- `DESTINY_HERO_DESTROY_DOGMA` (activated): L103: /* Standby burn via TryApplyDestinyHeroDestroyDogmaStandby. Ceiling: Quick
- `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER` (activated): L154: second target picker not chained; auto-destroy best remaining card.
- `DESTINY_HERO_DYSTOPIA` (activated): L225: printed is on-SS; any placement stand-in. Auto-pick highest ATK.
- `DIVINE_SERPENT_GEH` (activated): L42: * Ceiling: field ignition FALSE. */
- `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN` (activated): L177: multi-target picker not wired; auto-destroy highest-value opp cards.
- `EVIL_HERO_DEAD_END_PRISON` (activated): L159: Dark Fusion Fusion markers missing; any Fusion Monster stand-in.
- `HARPIE_CONDUCTOR` (activated): L133: any other Harpie leave ≈ return-to-hand; upgrade: true bounce-origin flag.
- `HARPIE_CONDUCTOR` (activated): L231: protect destroy redirect needs destroy-sub hook.
- `MORPHTRONIC_EARFON` (activated): L94: Equip 2-attacks FALSE. On-SS mark self as Tuner (unk4).
- `VISION_HERO_GRAVITO` (activated): L65: no RemovedFromPlay_RemoveAt — shift RFP array in place after add. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
