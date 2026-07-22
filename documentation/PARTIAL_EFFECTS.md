# Partial Effects Backlog

Auto-generated living list of effect files with `ponytail:` or `Ceiling:` notes (implemented, but missing hooks / engine pieces).
Find follow-up work here — stubs live in `STUB_EFFECTS.md`.
Rows vanish when all `ponytail:` / `Ceiling:` comments are removed from the file.
Missing-surface tags: [`PARTIAL_EFFECTS_TAXONOMY.md`](PARTIAL_EFFECTS_TAXONOMY.md). Engine migration: [`effect-data-system.md`](effect-data-system.md).

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials + taxonomy
```

**Last updated:** 2026-07-22 21:22 UTC  
**Remaining partials:** `36`

## Counts by kind

| Kind | Count |
|------|------:|
| `spell` | 5 |
| `trap` | 6 |
| `activated` | 25 |
| **total** | **36** |

## spell (5)

### `FUSION_DESTINY`
- path: `src_custom/spell_effects/fusion_destiny.c`
- L34: * Ceiling: incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous,
- L36: * Ceiling: Destiny End Dragoon only; upgrade: add remaining Destiny HERO Fusion

### `LEV_SHADDOLL_FUSION`
- path: `src_custom/spell_effects/lev_shaddoll_fusion.c`
- L158: the face-up ignition still needs a monster-zone tribute picker and an Extra Deck special-summon flow, neither of which is owned by this spell activation dispatcher.

### `SCAPEGOAT`
- path: `src_custom/spell_effects/scapegoat.c`
- L10: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. SHEEP_TOKEN card data + art, then swap this define.
- L74: LockMonsterCardsInRow also blocks Normal Set of monsters. distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.
- L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. SCAPEGOAT_TOKEN_ID / token flag.

### `SECRETS_OF_DARK_MAGIC`
- path: `src_custom/spell_effects/secrets_of_dark_magic.c`
- L34: * Ceiling: incomplete vs printed DM Fusion pool (Dragon Knight, etc.).
- L35: * Ceiling: Amulet Dragon + The Dark Magicians only; upgrade: add remaining DM

### `SPELL_CHRONICLE`
- path: `src_custom/spell_effects/spell_chronicle.c`
- L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished; cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.
- L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn; briefly hits GY; upgrade: direct deck→RFG.
- L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. Ceiling: activate discard+banish 5 only; unk4 counter slot unused.

## trap (6)

### `ANCIENT_GEAR_DUEL`
- path: `src_custom/trap_effects/ancient_gear_duel.c`
- L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks; mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand-in from Deck/hand.

### `DARK_SUPREMACY`
- path: `src_custom/trap_effects/dark_supremacy.c`
- L38: "Spells that mention Dark Fusion" not scanned by text.
- L53: GY banish shuffle HERO need GY ignition OPT. Ceiling: negate up to count face-up opp cards (monsters first) via unk4.

### `FAVOURITE_CONTACT`
- path: `src_custom/trap_effects/favourite_contact.c`
- L48: Extra Deck Fusion ignoring summon conditions + materials to Deck bottom need fusion recipe API; return up to 2 HERO/Neos/ Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free.

### `SHADDOLL_CORE`
- path: `src_custom/trap_effects/shaddoll_core.c`
- L45: true trap-monster (still a Trap) + Attribute fusion substitute need Embodiment-style link; place SHADDOLL_CORE on monster row and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate.

### `SHADDOLL_SCHISM`
- path: `src_custom/trap_effects/shaddoll_schism.c`
- L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker; banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.

### `URGENT_TUNING`
- path: `src_custom/trap_effects/urgent_tuning.c`
- L14: Synchro Summon during Battle Phase needs Synchro material/ED summon path outside this file (no in-file Synchro API). → Extra Deck Synchro SS.

## activated (25)

### `ANCIENT_GEAR_MEGATON_GOLEM`
- path: `src_custom/activated_effects/ancient_gear_megaton_golem.c`
- L140: Extra Deck Ultimate AG Golem SS blocked — AG Golem from hand/GY/Deck instead.

### `ARCANA_FORCE_V_THE_HIEROPHANT`
- path: `src_custom/activated_effects/arcana_force_v_the_hierophant.c`
- L198: discard only; opp cannot respond to Arcana Summons needs turn flag hook.

### `ARMORY_ARM`
- path: `src_custom/activated_effects/armory_arm.c`
- L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE.

### `ATLANTEAN_HEAVY_INFANTRY`
- path: `src_custom/activated_effects/atlantean_heavy_infantry.c`
- L111: extra Normal Summon Sea Serpent + sent-for-WATER destroy need summon/send hooks. OPT destroy 1 Set Spell/Trap.

### `BEAST_MACHINE_KING_BARBAROS_UR`
- path: `src_custom/activated_effects/beast_machine_king_barbaros_ur.c`
- L224: multi-zone banish picker not wired; require both types reachable.

### `CROSS_KEEPER`
- path: `src_custom/activated_effects/cross_keeper.c`
- L171: Fusion leave ≈ E-HERO Fusion SS while CK in GY; draw1 stand-in for banish→draw2→bottom. Upgrade: true SS trigger + banish cost.

### `DEEP_SEA_DIVA`
- path: `src_custom/activated_effects/deep_sea_diva.c`
- L101: /* NS SS via TryDeepSeaDivaOnNormalSummon. Ceiling: OPT duplicate if NS already

### `DESTINY_HERO_DARK_ANGEL`
- path: `src_custom/activated_effects/destiny_hero_dark_angel.c`
- L81: field spell-negate FALSE. Ceiling: FromHand discard → SS D-HERO to opp DEF.

### `DESTINY_HERO_DESTROY_DOGMA`
- path: `src_custom/activated_effects/destiny_hero_destroy_dogma.c`
- L103: /* Standby burn via TryApplyDestinyHeroDestroyDogmaStandby. Ceiling: Quick
- L104: * destroy/negate FALSE. Ceiling: FromHand banish 3 Warrior/DARK → SS + burn 2000. */

### `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER`
- path: `src_custom/activated_effects/destiny_hero_destroyer_phoenix_enforcer.c`
- L154: second target picker not chained; auto-destroy best remaining card.
- L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. OPT destroy 1 you control + 1 other field card.

### `DESTINY_HERO_DREADNOUGHT_SERVANT`
- path: `src_custom/activated_effects/destiny_hero_dreadnought_servant.c`
- L78: auto-pick first opp card; upgrade: PickZone targeting.

### `DESTINY_HERO_DYSTOPIA`
- path: `src_custom/activated_effects/destiny_hero_dystopia.c`
- L225: printed is on-SS; any placement stand-in. Auto-pick highest ATK.

### `DESTINY_HERO_PLASMA`
- path: `src_custom/activated_effects/destiny_hero_plasma.c`
- L95: equip/absorb + half-ATK boost + continuous opp negate need equip hooks. Ceiling: destroy 1 opp monster.

### `DIVINE_SERPENT_GEH`
- path: `src_custom/activated_effects/divine_serpent_geh.c`
- L41: * Ceiling: destroy gate + battle negate need destroy/battle hooks.
- L42: * Ceiling: field ignition FALSE. */

### `DIVINER_OF_THE_HERALD`
- path: `src_custom/activated_effects/diviner_of_the_herald.c`
- L84: Extra Deck Fairy mill skipped.

### `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN`
- path: `src_custom/activated_effects/elemental_hero_shining_neos_wingman.c`
- L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. OPT destroy opp cards up to different Attributes.
- L177: multi-target picker not wired; auto-destroy highest-value opp cards.

### `EVIL_HERO_ADUSTED_GOLD`
- path: `src_custom/activated_effects/evil_hero_adusted_gold.c`
- L63: cannot attack without Fusion Monster needs attack gate. Not field-ignition activatable; discard search uses FromHand path.
- L86: once-per-turn not tracked without turn hook.

### `EVIL_HERO_DEAD_END_PRISON`
- path: `src_custom/activated_effects/evil_hero_dead_end_prison.c`
- L110: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE. OPT mill 1 HERO from Deck (EffectOpt).
- L159: Dark Fusion Fusion markers missing; any Fusion Monster stand-in.

### `EVIL_HERO_MALICIOUS_BANE`
- path: `src_custom/activated_effects/evil_hero_malicious_bane.c`
- L75: destruction immunity + HERO-only attack gate need destroy/attack hooks. OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4.
- L105: +200 ATK each via tempStage (~500/unit); attack lock only marks self unk4.

### `HARPIE_CONDUCTOR`
- path: `src_custom/activated_effects/harpie_conductor.c`
- L133: any other Harpie leave ≈ return-to-hand; upgrade: true bounce-origin flag.
- L231: protect destroy redirect needs destroy-sub hook.

### `LEVEL_EATER`
- path: `src_custom/activated_effects/level_eater.c`
- L123: * Ceiling: SS self from GY; upgrade: TempLevel overlay on target. */
- L179: * Ceiling: cannot-be-Tributed-except-for-Tribute-Summon needs tribute hooks. */

### `MORPHTRONIC_EARFON`
- path: `src_custom/activated_effects/morphtronic_earfon.c`
- L53: real Tuner flag / Equip double-attack need Synchro/equip hooks. OPT PickZone mark unk4 as Tuner stand-in.
- L94: Equip 2-attacks FALSE. On-SS mark self as Tuner (unk4).

### `OJAMA_KING`
- path: `src_custom/activated_effects/ojama_king.c`
- L54: PickZone for up to 3 empty zones + continuous lock gate. FirstEmptyZoneInRow today — same as Ground Collapse).

### `RYKO_TWILIGHTSWORN_FIGHTER`
- path: `src_custom/activated_effects/ryko_twilightsworn_fighter.c`
- L204: NS mill 3 stand-in for other-LS effect→mill; upgrade: chain hook.

### `VISION_HERO_GRAVITO`
- path: `src_custom/activated_effects/vision_hero_gravito.c`
- L65: no RemovedFromPlay_RemoveAt — shift RFP array in place after add. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- L114: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip zone API. OPT add 1 banished HERO monster to hand (EffectOpt; on-summon stand-in).
