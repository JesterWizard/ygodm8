# Partial Effects Backlog

Auto-generated living list of effect files with `ponytail:` ceilings (implemented, but missing hooks / engine pieces).
Find follow-up work here — stubs live in `STUB_EFFECTS.md`.
Rows vanish when all `ponytail:` comments are removed from the file.
Missing-surface tags: [`PARTIAL_EFFECTS_TAXONOMY.md`](PARTIAL_EFFECTS_TAXONOMY.md). Engine migration: [`effect-data-system.md`](effect-data-system.md).

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials + taxonomy
```

**Last updated:** 2026-07-22 17:42 UTC  
**Remaining partials:** `326`

## Counts by kind

| Kind | Count |
|------|------:|
| `spell` | 6 |
| `trap` | 10 |
| `activated` | 260 |
| `permanent` | 50 |
| **total** | **326** |

## spell (6)

### `FUSION_DESTINY`
- path: `src_custom/spell_effects/fusion_destiny.c`
- L34: * ponytail: incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous,

### `NEO_SPACE`
- path: `src_custom/spell_effects/neo_space.c`
- L94: gCardData_NEW — SetCardInfo would wipe stage/field ATK mid-overlay.

### `SCAPEGOAT`
- path: `src_custom/spell_effects/scapegoat.c`
- L10: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. Ceiling: wrong Type/Attribute (Fairy/LIGHT vs Beast/EARTH); upgrade: add SHEEP_TOKEN card data + art, then swap this define.
- L74: LockMonsterCardsInRow also blocks Normal Set of monsters. Ceiling: cannot allow Set while blocking Summon without a menu hook that distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.
- L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. Ceiling: best-effort lockMonster; upgrade: tribute validator excludes SCAPEGOAT_TOKEN_ID / token flag.

### `SECRETS_OF_DARK_MAGIC`
- path: `src_custom/spell_effects/secrets_of_dark_magic.c`
- L34: * ponytail: incomplete vs printed DM Fusion pool (Dragon Knight, etc.).

### `SPELL_CHRONICLE`
- path: `src_custom/spell_effects/spell_chronicle.c`
- L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished. Ceiling: cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.
- L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn. Ceiling: briefly hits GY; upgrade: direct deck→RFG.
- L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. Ceiling: activate discard+banish 5 only; unk4 counter slot unused.

### `SPELL_GEAR`
- path: `src_custom/spell_effects/spell_gear.c`
- L156: * ponytail: optional SS offered as auto-yes when legal. Ceiling: cannot skip

## trap (10)

### `AMAZONESS_HALL`
- path: `src_custom/trap_effects/amazoness_hall.c`
- L43: * ponytail: Extra Deck / Pendulum place + opp SS gain LP need hooks. */

### `AMAZONESS_HOT_SPRING`
- path: `src_custom/trap_effects/amazoness_hot_spring.c`
- L46: * ponytail: Pendulum Zone place + battle-damage gain LP OPT need hooks. */

### `ANCIENT_GEAR_DUEL`
- path: `src_custom/trap_effects/ancient_gear_duel.c`
- L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks. Ceiling: mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand-in from Deck/hand.

### `ANGELS_TEAR`
- path: `src_custom/trap_effects/angels_tear.c`
- L342: need 4 banish targets plus 1 summon target.

### `DARK_SUPREMACY`
- path: `src_custom/trap_effects/dark_supremacy.c`
- L38: "Spells that mention Dark Fusion" not scanned by text.
- L53: GY banish shuffle HERO need GY ignition OPT. Ceiling: negate up to count face-up opp cards (monsters first) via unk4.

### `FAVOURITE_CONTACT`
- path: `src_custom/trap_effects/favourite_contact.c`
- L48: Extra Deck Fusion ignoring summon conditions + materials to Deck bottom need fusion recipe API. Ceiling: return up to 2 HERO/Neos/ Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free.

### `HARPIE_LADY_ELEGANCE`
- path: `src_custom/trap_effects/harpie_lady_elegance.c`
- L47: * ponytail: WIND-only SS lock this turn + destroy-search Harpie Spell need hooks. */

### `SHADDOLL_CORE`
- path: `src_custom/trap_effects/shaddoll_core.c`
- L45: true trap-monster (still a Trap) + Attribute fusion substitute need Embodiment-style link. Ceiling: place SHADDOLL_CORE on monster row and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate.

### `SHADDOLL_SCHISM`
- path: `src_custom/trap_effects/shaddoll_schism.c`
- L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker. Ceiling: banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.

### `URGENT_TUNING`
- path: `src_custom/trap_effects/urgent_tuning.c`
- L14: Synchro Summon during Battle Phase needs Synchro material/ED summon path outside this file (no in-file Synchro API). Ceiling: shows text + self-destroy; upgrade: collect Tuners + non-Tuners → Extra Deck Synchro SS.

## activated (260)

### `DARK_ARMED_DRAGON`
- path: `src_custom/activated_effects/dark_armed_dragon.c`
- L174: allow self-target for faithful TCG simulation; player can choose suboptimally
- L317: auto-target. No GY picker (DeckMenu screen switch corrupts VRAM from inside monster effect handler) and no PickZone cursor state (200 conflicts with game loop after MonsterActionMenu case 4 returns). Picks the best field target via AiPickTarget logic. Upgrade path: dedicated cursor state + A/B handlers like Cannon Soldier.

### `DARK_DUST_SPIRIT`
- path: `src_custom/activated_effects/dark_dust_spirit.c`
- L22: hand normal/tribute summon copies isFaceUp=0; attack-position still counts
- L63: GBA "face-up" = isFaceUp bit; attack-position keeps isFaceUp=0 until flip

### `DARK_HORUS`
- path: `src_custom/activated_effects/dark_horus.c`
- L99: after opp Main Phase Spell resolve trigger needs spell hook. Ceiling: OPT SS 1 Lv4 DARK from GY while face-up.

### `DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE`
- path: `src_custom/activated_effects/dark_magician_girl_the_magician_s_apprentice.c`
- L61: name=DMG + GY +300 mention FALSE. Ceiling: field OPT add Shining Sarcophagus from Deck.
- L129: name becomes Dark Magician Girl FALSE (no name-override hook).

### `DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE`
- path: `src_custom/activated_effects/dark_magician_girl_the_magicians_apprentice.c`
- L61: name=DMG + GY +300 mention FALSE. Ceiling: field OPT add Shining Sarcophagus from Deck.
- L129: name becomes Dark Magician Girl FALSE (no name-override hook).

### `DARK_MAGICIAN_THE_DRAGON_KNIGHT`
- path: `src_custom/activated_effects/dark_magician_the_dragon_knight.c`
- L12: name becomes Dark Magician + S/T protection need permanent/name hooks. Ceiling: not ignition-activatable here; upgrade: permanent overlay.

### `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS`
- path: `src_custom/activated_effects/dark_magician_the_magician_of_black_chaos.c`
- L33: name=DM + destroy-revive/Set need name/destroy hooks. Ceiling: not field-ignition; FromHand if Shining Sarcophagus.

### `DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC`
- path: `src_custom/activated_effects/dark_magician_the_magician_of_black_magic.c`
- L33: name=DM + destroy-revive/Set need name/destroy hooks. Ceiling: not field-ignition; FromHand if Shining Sarcophagus.

### `DARK_STRIKE_FIGHTER`
- path: `src_custom/activated_effects/dark_strike_fighter.c`
- L127: Main Phase 1 gate not wired; allow once via usage any main phase.

### `DARKLORD_DESIRE`
- path: `src_custom/activated_effects/darklord_desire.c`
- L56: -2 tempStage (~1000 ATK, not exact); until EP clear needs EOT hook.
- L116: Fairy-only Tribute Summon + cannot SS need summon hooks. Ceiling: OPT -1000 ATK (tempStage) → send 1 opp monster to GY.

### `DARKNESS_NEOSPHERE`
- path: `src_custom/activated_effects/darkness_neosphere.c`
- L87: battle indestruct + trap bounce + attack-declare gate need battle/ phase hooks. Ceiling: not field-ignition activatable; SS uses FromHand path.
- L113: opp attack declare gate not wired; require 1 field + 1 hand Fiend.

### `DEEP_SEA_DIVA`
- path: `src_custom/activated_effects/deep_sea_diva.c`
- L58: Normal Summon trigger needs summon hook. Ceiling: once via usage while face-up if Lv≤3 Sea Serpent in Deck.

### `DESTINY_END_DRAGOON`
- path: `src_custom/activated_effects/destiny_end_dragoon.c`
- L65: cannot conduct Battle Phase — unk4 lock stand-in. GY revive FALSE.
- L105: GY revive FALSE. Ceiling: OPT destroy 1 opp monster + burn its ATK + cannot BP (unk4).

### `DESTINY_HERO_CAPTAIN_TENACIOUS`
- path: `src_custom/activated_effects/destiny_hero_captain_tenacious.c`
- L92: Standby Phase + battle-destroyed-since-last-Standby filter need phase/destroy hooks. Ceiling: OPT SS 1 D-HERO from your GY.

### `DESTINY_HERO_CELESTIAL`
- path: `src_custom/activated_effects/destiny_hero_celestial.c`
- L101: attack-declare destroy + GY draw-if-no-hand need battle/GY hooks. Ceiling: OPT destroy 1 face-up opp Spell + burn 500.

### `DESTINY_HERO_DARK_ANGEL`
- path: `src_custom/activated_effects/destiny_hero_dark_angel.c`
- L81: field spell-negate FALSE. Ceiling: FromHand discard → SS D-HERO to opp DEF.

### `DESTINY_HERO_DASHER`
- path: `src_custom/activated_effects/destiny_hero_dasher.c`
- L49: battle DEF change + draw-phase GY SS need battle/draw hooks. Ceiling: OPT tribute 1 other → +2 tempStage (~1000 ATK until End Phase).

### `DESTINY_HERO_DENIER`
- path: `src_custom/activated_effects/destiny_hero_denier.c`
- L189: GY SS when other D-HERO present needs GY/once-per-duel hooks. Ceiling: OPT put 1 D-HERO from Deck/GY/banished on top of Deck.

### `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER`
- path: `src_custom/activated_effects/destiny_hero_destroyer_phoenix_enforcer.c`
- L154: second target picker not chained; auto-destroy best remaining card.
- L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. Ceiling: OPT destroy 1 you control + 1 other field card.

### `DESTINY_HERO_DIAMOND_DUDE`
- path: `src_custom/activated_effects/destiny_hero_diamond_dude.c`
- L57: next-turn GY Normal Spell activation needs Main Phase hook.

### `DESTINY_HERO_DISK_COMMANDER`
- path: `src_custom/activated_effects/destiny_hero_disk_commander.c`
- L20: SS-from-GY trigger + once per duel. Ceiling: OPT draw 2 stand-in when on field; upgrade: GY SS dispatch + EFFECT_USAGE_ONCE.

### `DESTINY_HERO_DOMINANCE`
- path: `src_custom/activated_effects/destiny_hero_dominance.c`
- L66: look+reorder UI missing; RandRange shuffle of top N is stand-in.
- L89: battle-destroy draw + GY SS 3 D-HERO need battle/destroy hooks. Ceiling: OPT shuffle top 5 of your (else opp) Deck as look+reorder stand-in.

### `DESTINY_HERO_DREADNOUGHT_MASTER`
- path: `src_custom/activated_effects/destiny_hero_dreadnought_master.c`
- L60: SS trigger → OPT ignition; cards-mentioning-D-HERO FALSE. Ceiling: OPT add up to 2 Destiny HERO from Deck.

### `DESTINY_HERO_DREADNOUGHT_SERVANT`
- path: `src_custom/activated_effects/destiny_hero_dreadnought_servant.c`
- L89: GY banish destroy on Lv8 D-HERO SS FALSE. Ceiling: FromHand if control D-HERO or Field Spell → SS, destroy 1, add Poly.

### `DESTINY_HERO_DREAMER`
- path: `src_custom/activated_effects/destiny_hero_dreamer.c`
- L52: * ponytail: banish-on-leave need GY hook. Ceiling: GY ignition SS. */

### `DESTINY_HERO_DRILLDARK`
- path: `src_custom/activated_effects/destiny_hero_drilldark.c`
- L65: * ponytail: on-Summon trigger need summon hook.

### `DESTINY_HERO_DYNATAG`
- path: `src_custom/activated_effects/destiny_hero_dynatag.c`
- L134: GY banish ATK boost not wired; both players 1000 on FromHand.

### `DESTINY_HERO_DYSTOPIA`
- path: `src_custom/activated_effects/destiny_hero_dystopia.c`
- L203: on-SS burn + Quick destroy-if-ATK-changed need summon/ATK hooks. Ceiling: OPT pick Lv≤4 D-HERO in GY → burn its ATK.

### `DESTINY_HERO_MALICIOUS`
- path: `src_custom/activated_effects/destiny_hero_malicious.c`
- L43: GY ignition needs GY-menu wire. Ceiling: allow when Malicious in GY + another in Deck (callable if gMonEffect set to Malicious).

### `DESTINY_HERO_PLASMA`
- path: `src_custom/activated_effects/destiny_hero_plasma.c`
- L95: equip/absorb + half-ATK boost + continuous opp negate need equip hooks. Ceiling: destroy 1 opp monster.

### `DIVINE_SERPENT_GEH`
- path: `src_custom/activated_effects/divine_serpent_geh.c`
- L31: destroy gate + untargetable + battle negate need destroy/battle hooks. Ceiling: field ignition FALSE; FromHand pay half LP → SS only.

### `DIVINER_OF_THE_HERALD`
- path: `src_custom/activated_effects/diviner_of_the_herald.c`
- L89: on-NS/SS mill + tribute SS Fairy need summon/tribute hooks. Ceiling: OPT send 1 Fairy from Deck to GY (+unkTwo Level stand-in).
- L110: Level bump until EOT needs level-override hook; unkTwo stores milled Level.

### `EBON_ILLUSION_MAGICIAN`
- path: `src_custom/activated_effects/ebon_illusion_magician.c`
- L78: Xyz detach cost + attack-banish FALSE. Ceiling: OPT SS Spellcaster Normal from hand/Deck (detach stand-in).

### `EL_SHADDOLL_MESHAHRAIL`
- path: `src_custom/activated_effects/el_shaddoll_meshahrail.c`
- L74: unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks. Ceiling: OPT pay 800 → add 1 Shaddoll or Void S/T from Deck.

### `EL_SHADDOLL_WENDIGO`
- path: `src_custom/activated_effects/el_shaddoll_wendigo.c`
- L110: * ponytail: GY add Shaddoll S/T on send not wired. */

### `ELDER_ENTITY_NORDEN`
- path: `src_custom/activated_effects/elder_entity_norden.c`
- L73: banish-when-leaves needs leave-field hook; unk4 marks negated.
- L124: SS-trigger timing + banish-when-leaves need summon/leave hooks. Ceiling: OPT SS Lv≤4 from GY face-up DEF with unk4 negated mark.

### `ELEMENTAL_HERO_AQUA_NEOS`
- path: `src_custom/activated_effects/elemental_hero_aqua_neos.c`
- L20: Contact fusion need fusion hook; EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT discard 1, then destroy 1 random opponent hand card.

### `ELEMENTAL_HERO_BLAZEMAN`
- path: `src_custom/activated_effects/elemental_hero_blazeman.c`
- L222: on-summon does not consume effectUsedThisTurn — that flag is only for the menu activated effect (popup_2). Otherwise popup_2 can never fire the turn Blazeman is summoned.

### `ELEMENTAL_HERO_CHAOS_NEOS`
- path: `src_custom/activated_effects/elemental_hero_chaos_neos.c`
- L88: EP shuffle/Set-all + exact 3H/2H/1H/0H branch table FALSE. Ceiling: OPT 3 coin → destroy heads-count opp monsters.

### `ELEMENTAL_HERO_COSMO_NEOS`
- path: `src_custom/activated_effects/elemental_hero_cosmo_neos.c`
- L72: activation lock / End Phase field wipe FALSE. Ceiling: OPT destroy all opp Spell/Trap.

### `ELEMENTAL_HERO_DARK_NEOS`
- path: `src_custom/activated_effects/elemental_hero_dark_neos.c`
- L50: contact Fusion need fusion hook; EP Extra return via TryReturnContactFusionsAtEndPhase.

### `ELEMENTAL_HERO_GAIA`
- path: `src_custom/activated_effects/elemental_hero_gaia.c`
- L49: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.

### `ELEMENTAL_HERO_GRAND_NEOS`
- path: `src_custom/activated_effects/elemental_hero_grand_neos.c`
- L95: Contact fusion need fusion hook; EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT bounce 1 opponent monster to hand.

### `ELEMENTAL_HERO_GREAT_TORNADO`
- path: `src_custom/activated_effects/elemental_hero_great_tornado.c`
- L26: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.atk/def that the stat pipeline already computed for zone.

### `ELEMENTAL_HERO_LADY_HEAT`
- path: `src_custom/activated_effects/elemental_hero_lady_heat.c`
- L45: CanActivate runs before the menu flips a face-down activator

### `ELEMENTAL_HERO_MAGMA_NEOS`
- path: `src_custom/activated_effects/elemental_hero_magma_neos.c`
- L42: continuous 400/field + EP field bounce need permanent/EP hooks; EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT refresh tempStage from field card count.

### `ELEMENTAL_HERO_NEBULA_NEOS`
- path: `src_custom/activated_effects/elemental_hero_nebula_neos.c`
- L115: Extra SS trigger + EP banish field FALSE. Ceiling: OPT draw = opp card count, then mark 1 face-up negated.

### `ELEMENTAL_HERO_OCEAN`
- path: `src_custom/activated_effects/elemental_hero_ocean.c`
- L81: skip stale GY Ocean while the activator is still on field

### `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN`
- path: `src_custom/activated_effects/elemental_hero_shining_neos_wingman.c`
- L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. Ceiling: OPT destroy opp cards up to different Attributes.
- L177: multi-target picker not wired; auto-destroy highest-value opp cards.

### `ELEMENTAL_HERO_SPIRIT_OF_NEOS`
- path: `src_custom/activated_effects/elemental_hero_spirit_of_neos.c`
- L154: attack-hand SS FALSE. Ceiling: OPT search Poly/E-HERO S/T, else OPT shuffle self → SS Normal E-HERO from Deck.

### `ELEMENTAL_HERO_STORM_NEOS`
- path: `src_custom/activated_effects/elemental_hero_storm_neos.c`
- L86: contact Fusion + field shuffle need fusion/phase hooks; EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: OPT destroy all S/T on field.

### `ELEMENTAL_HERO_STRATOS`
- path: `src_custom/activated_effects/elemental_hero_stratos.c`
- L462: on-summon text after field draw so Stratos is visible.
- L465: no dedicated A/B choice UI — try search first; player can cancel the deck pick (B) to fall through to destroy when that option is legal.

### `ELEMENTAL_HERO_TERRA_FIRMA`
- path: `src_custom/activated_effects/elemental_hero_terra_firma.c`
- L42: fixed POV — only reveal the player's own monster row
- L70: attack-position summons stay isFaceUp=0 until end-of-turn flip

### `ENLIGHTENMENT_DRAGON`
- path: `src_custom/activated_effects/enlightenment_dragon.c`
- L138: Extra Summon conditions + destroy-add banished FALSE. Ceiling: OPT pay 2000 → banish all other field+both GYs, else OPT mill 4. Separate OPTs share one MarkMonsterEffectUsed.

### `EVIL_HERO_ADUSTED_GOLD`
- path: `src_custom/activated_effects/evil_hero_adusted_gold.c`
- L63: cannot attack without Fusion Monster needs attack gate hook. Ceiling: not field-ignition activatable; discard search uses FromHand path.
- L86: once-per-turn not tracked without turn hook.

### `EVIL_HERO_DARKEST_KNIGHT`
- path: `src_custom/activated_effects/evil_hero_darkest_knight.c`
- L90: opp ATK loss by materials + double attack need fusion/battle hooks. Ceiling: OPT SS 1 Fiend/Warrior from GY (leave-field stand-in).

### `EVIL_HERO_DEAD_END_PRISON`
- path: `src_custom/activated_effects/evil_hero_dead_end_prison.c`
- L109: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE. Ceiling: OPT mill 1 HERO from Deck.
- L151: Dark Fusion Fusion markers missing; any Fusion Monster stand-in.

### `EVIL_HERO_INFERNAL_RIDER`
- path: `src_custom/activated_effects/evil_hero_infernal_rider.c`
- L228: on-summon + HERO lock need summon/SS gates. Ceiling: OPT add Dark Fusion Deck/GY, else OPT banish self+4 GY → Set Super Poly.

### `EVIL_HERO_MALICIOUS_BANE`
- path: `src_custom/activated_effects/evil_hero_malicious_bane.c`
- L75: destruction immunity + HERO-only attack gate need destroy/attack hooks. Ceiling: OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4.
- L105: +200 ATK each via tempStage (~500/unit); attack lock only marks self unk4.

### `EVIL_HERO_NEOS_LORD`
- path: `src_custom/activated_effects/evil_hero_neos_lord.c`
- L144: indestructible + on-SS/opp-GY-sent take-control triggers need continuous/summon hooks. Ceiling: OPT take control of 1 face-up opp monster.

### `EVIL_HERO_SINISTER_NECROM`
- path: `src_custom/activated_effects/evil_hero_sinister_necrom.c`
- L103: GY ignition needs GY-menu wire. Ceiling: allow when Sinister Necrom in GY + Evil HERO in hand or Deck (callable if gMonEffect set).

### `EVIL_HERO_TOXIC_BUBBLE`
- path: `src_custom/activated_effects/evil_hero_toxic_bubble.c`
- L16: on-SS draw when Dark Fusion Fusion up needs summon hook. Ceiling: not field-ignition activatable; SS-from-hand uses FromHand path.
- L39: HERO-only SS lock + once-per-turn not tracked without turn hook.

### `EVIL_HERO_VICIOUS_CLAWS`
- path: `src_custom/activated_effects/evil_hero_vicious_claws.c`
- L46: GY destroy-revive + Dark Fusion destroy branch need GY/destroy hooks. Ceiling: FromHand target HERO → SS DEF +300 ATK stand-in.
- L96: +300 ≈ +1 tempStage (~500).

### `EVOLZAR_DOLKKA`
- path: `src_custom/activated_effects/evolzar_dolkka.c`
- L12: quick Xyz detach + negate monster effect need chain/Xyz hooks. Ceiling: not field-ignition here.

### `FELIS_LIGHTSWORN_ARCHER`
- path: `src_custom/activated_effects/felis_lightsworn_archer.c`
- L101: SS when sent from Deck to GY by monster effect needs mill/SS hook. Ceiling: ignition tribute self → destroy 1 opponent monster → mill 3.

### `FLAME_RULER`
- path: `src_custom/activated_effects/flame_ruler.c`
- L12: treat as 2 Tributes for FIRE Tribute Summon needs tribute-cost LynJump. Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle gate outside this file.

### `FOG_KING`
- path: `src_custom/activated_effects/fog_king.c`
- L12: tribute-flex Normal Summon, ATK = tributed ATK, and global tribute lock need summon/tribute continuous hooks. Ceiling: not field-ignition here.

### `FORMULA_SYNCHRON`
- path: `src_custom/activated_effects/formula_synchron.c`
- L32: Synchro Summon draw trigger + opp-Main-Phase quick Synchro need synchro/chain hooks. Ceiling: OPT draw 1 via usage when deck remains.

### `FUSILIER_DRAGON_THE_DUAL_MODE_BEAST`
- path: `src_custom/activated_effects/fusilier_dragon_the_dual_mode_beast.c`
- L12: NS without tribute + halved ATK/DEF needs summon tribute gate. Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon gate outside this file.

### `GAGAGIGO_THE_RISEN`
- path: `src_custom/activated_effects/gagagigo_the_risen.c`
- L12: Gagagigo the Risen has no printed monster effect (Xyz materials only). Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.

### `GAMECIAL_THE_SEA_TURTLE_KAIJU`
- path: `src_custom/activated_effects/gamecial_the_sea_turtle_kaiju.c`
- L68: SS to opp field + Quick remove Kaiju Counter FALSE. Ceiling: FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju).

### `GANDORA_G_THE_DRAGON_OF_DESTRUCTION`
- path: `src_custom/activated_effects/gandora_g_the_dragon_of_destruction.c`
- L125: destroy+banish → Duel_BanishZone (no GY).
- L151: +300 ATK/banished needs permanent/banish count hook. Ceiling: OPT pay half LP → banish all other field → SS Lv≤7 Sarc mention.

### `GATE_GUARDIANS_COMBINED`
- path: `src_custom/activated_effects/gate_guardians_combined.c`
- L102: negate-on-target + leave-field SS FALSE. Ceiling: OPT destroy 1 opp card (negate stand-in).

### `GODDESS_BOW`
- path: `src_custom/activated_effects/goddess_bow.c`
- L12: Hermos fusion + equip + battle-phase negate/second attack need fusion/equip/chain hooks. Ceiling: not ignition-activatable here.

### `GORZ_THE_EMISSARY_OF_DARKNESS`
- path: `src_custom/activated_effects/gorz_the_emissary_of_darkness.c`
- L34: damage-gate + Token FALSE. Ceiling: FromHand empty-field SS.

### `GRAVEKEEPERS_AMBUSHER`
- path: `src_custom/activated_effects/gravekeepers_ambusher.c`
- L146: flip trigger + Necrovalley search need flip/send hooks. Ceiling: OPT put 1 opponent GY card on bottom of their Deck.

### `GRAVEKEEPERS_CHIEF`
- path: `src_custom/activated_effects/gravekeepers_chief.c`
- L186: Tribute Summon trigger, once-only control, and Necrovalley GY immunity need summon/continuous hooks. Ceiling: OPT SS GK from GY.

### `GRAVEKEEPERS_CURSE`
- path: `src_custom/activated_effects/gravekeepers_curse.c`
- L20: printed is If Summoned trigger. Ceiling: allow once via usage when manually activated / summon-dispatch calls Activate.

### `GRAVEKEEPERS_DESCENDANT`
- path: `src_custom/activated_effects/gravekeepers_descendant.c`
- L29: attack-position summons keep isFaceUp=0 until end-of-turn flip.

### `GRAVEKEEPERS_GUARD`
- path: `src_custom/activated_effects/gravekeepers_guard.c`
- L85: FLIP trigger needs flip hook.

### `GRAVEKEEPERS_HEADMAN`
- path: `src_custom/activated_effects/gravekeepers_headman.c`
- L95: on-Summon trigger + ATK/face-down DEF choice need summon hook. Ceiling: OPT SS 1 Lv4 Gravekeeper's from GY in ATK.

### `GRAVEKEEPERS_HERATIC`
- path: `src_custom/activated_effects/gravekeepers_heratic.c`
- L12: continuous unaffected-while-Necrovalley needs permanent protection gate. Ceiling: not ignition-activatable here; upgrade: permanent effect while Duel_IsBackrowCardOnField(NECROVALLEY).

### `GRAVEKEEPERS_ORACLE`
- path: `src_custom/activated_effects/gravekeepers_oracle.c`
- L93: Tribute Summon sequence (destroy/flip/ATK) FALSE. Ceiling: OPT destroy up to 2 cards on opp field.
- L110: multi-target picker not wired; auto-destroy up to 2 opp cards.

### `GRAVEKEEPERS_SHAMAN`
- path: `src_custom/activated_effects/gravekeepers_shaman.c`
- L63: * ponytail: GY-effect negate + Necrovalley Field lock need permanent hooks. */

### `GRAVEKEEPERS_SPIRITUALIST`
- path: `src_custom/activated_effects/gravekeepers_spiritualist.c`
- L12: Necrovalley-gated Spellcaster Fusion from Extra Deck needs fusion summon API. Ceiling: not ignition-activatable here.

### `GRAVEKEEPERS_SPY`
- path: `src_custom/activated_effects/gravekeepers_spy.c`
- L58: FLIP trigger needs flip hook.

### `GRAVEKEEPERS_SUPERNATURALIST`
- path: `src_custom/activated_effects/gravekeepers_supernaturalist.c`
- L57: material ATK gain + Necrovalley destroy protect + EP schedule FALSE. Ceiling: OPT add Gravekeeper or Necrovalley from Deck now (EP add stand-in).

### `GRAVEKEEPERS_VASSAL`
- path: `src_custom/activated_effects/gravekeepers_vassal.c`
- L12: battle damage as effect damage needs battle-damage type gate. Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle gate outside this file.

### `GRAVEKEEPERS_VISIONARY`
- path: `src_custom/activated_effects/gravekeepers_visionary.c`
- L89: * ponytail: destroy-replace needs destroy gate. Ceiling: OPT discard GK stand-in. */

### `GRAVEKEEPERS_WATCHER`
- path: `src_custom/activated_effects/gravekeepers_watcher.c`
- L15: either-turn chain negate when opp discards needs chain/negation hooks. Ceiling: not field-ignition; discard-from-hand path below.
- L47: negate activation + destroy activated card not wired.

### `GREAT_POSEIDON_BEETLE`
- path: `src_custom/activated_effects/great_poseidon_beetle.c`
- L12: re-attack same target after surviving battle needs battle re-attack hook. Ceiling: not ignition-activatable here.

### `GREEN_GADGET`
- path: `src_custom/activated_effects/green_gadget.c`
- L60: NS/SS trigger needs summon hook. Ceiling: once via usage.

### `GUARDIAN_DREADSCYTHE`
- path: `src_custom/activated_effects/guardian_dreadscythe.c`
- L170: summon lock + GY revive loop need summon/leave hooks. Ceiling: OPT equip/add Reaper Scythe from Deck.

### `GUNGNIR_DRAGON_OF_THE_ICE_BARRIER`
- path: `src_custom/activated_effects/gungnir_dragon_of_the_ice_barrier.c`
- L195: 2-discard path auto-destroys 2 cards; upgrade: sequential PickZone.

### `HARPIE_CHANNELER`
- path: `src_custom/activated_effects/harpie_channeler.c`
- L84: Level 7 with Dragon + name becomes Harpie Lady need continuous/name hooks.

### `HARPIE_CONDUCTOR`
- path: `src_custom/activated_effects/harpie_conductor.c`
- L20: no SS-origin flag; face-up/ATK stand-in for Special Summoned.
- L99: name Lady + protect destroy redirect + on-Harpie-return trigger need name/destroy/return hooks. Ceiling: OPT bounce 1 face-up/ATK opp monster.

### `HARPIE_DANCER`
- path: `src_custom/activated_effects/harpie_dancer.c`
- L77: granted NS after bounce — clear block like Necrovalley Throne.
- L125: name becomes Harpie Lady on field/GY needs continuous rename hook.

### `HARPIE_HARPIST`
- path: `src_custom/activated_effects/harpie_harpist.c`
- L124: NS trigger + GY End Phase search FALSE as separate triggers. Ceiling: OPT bounce own WB + opp face-up, else OPT add Harpie from Deck.

### `HARPIE_ORACLE`
- path: `src_custom/activated_effects/harpie_oracle.c`
- L124: name becomes Harpie Lady + End Phase Sisters S/T add need name/EP hooks. Ceiling: OPT add 1 Harpie from GY to hand.

### `HARPIE_QUEEN`
- path: `src_custom/activated_effects/harpie_queen.c`
- L14: * ponytail: name becomes Harpie Lady on field/GY needs name override hook. */

### `HELIOS_TRICE_MEGISTUS`
- path: `src_custom/activated_effects/helios_trice_megistus.c`
- L67: * ponytail: extra attack if opp controls a monster needs multi-attack hook. */

### `HELSHADDOLL_HOLLOW`
- path: `src_custom/activated_effects/helshaddoll_hollow.c`
- L109: FLIP Extra mill + GY attribute mill need flip/send hooks. Ceiling: OPT banish 1 face-up opp monster.

### `HERALD_OF_PERFECTION`
- path: `src_custom/activated_effects/herald_of_perfection.c`
- L12: quick negate by sending Fairy from hand needs chain/negation hooks. Ceiling: not field-ignition activatable here; upgrade: either-turn chain interrupt → discard Fairy → negate + destroy activated card.

### `HERALD_OF_THE_ARC_LIGHT`
- path: `src_custom/activated_effects/herald_of_the_arc_light.c`
- L12: deck/hand mill-banish + Quick tribute-negate need send/chain hooks. Ceiling: not field-ignition activatable here; upgrade: continuous banish + either-turn chain interrupt → tribute self → negate + destroy.

### `HERALD_OF_ULIMATENESS`
- path: `src_custom/activated_effects/herald_of_ulimateness.c`
- L12: quick negate by sending Fairy from hand needs chain/negation hooks. Ceiling: not field-ignition activatable here; upgrade: either-turn chain interrupt → discard Fairy → negate + destroy activated card.

### `HERALD_OF_ULTIMATENESS`
- path: `src_custom/activated_effects/herald_of_ultimateness.c`
- L12: quick negate by sending Fairy from hand needs chain/negation hooks. Ceiling: not field-ignition activatable here; upgrade: either-turn chain interrupt → discard Fairy → negate + destroy activated card.

### `HOLACTIE_THE_CREATOR_OF_LIGHT`
- path: `src_custom/activated_effects/holactie_the_creator_of_light.c`
- L64: SS-this-card-wins-Duel needs win-on-summon hook; no duel_helpers win API. Ceiling: not field-ignition activatable; use FromHand tribute path.

### `HONEST`
- path: `src_custom/activated_effects/honest.c`
- L95: Damage Step hand discard uses FromHand path. Ceiling: Main Phase return this face-up card to the hand.

### `HORUS_THE_BLACK_FLAME_DRAGON_LV8`
- path: `src_custom/activated_effects/horus_the_black_flame_dragon_lv8.c`
- L12: /* Spell immunity via IsImmuneToSpellEffectsOnField. ponytail: either-turn Spell

### `HOURGLASS_OF_LIFE`
- path: `src_custom/activated_effects/hourglass_of_life.c`
- L11: updateGfx=FALSE — sub_8041CCC refreshes field after popup dismisses.

### `ILLUSION_OF_CHAOS`
- path: `src_custom/activated_effects/illusion_of_chaos.c`
- L135: field bounce→SS DM negate FALSE. Ceiling: FromHand search only.

### `JAIN_TWILIGHTSWORN_GENERAL`
- path: `src_custom/activated_effects/jain_twilightsworn_general.c`
- L151: until end of turn clear needs EOT tempStage reset hook.
- L229: other-Lightsworn-activated mill 2 needs chain hook. Ceiling: OPT banish 1 Lightsworn from hand/GY → weaken 1 face-up monster. EP mill 2 stand-in via TryApplyTwilightswornEndPhase.

### `JOWLS_OF_DARK_DEMISE`
- path: `src_custom/activated_effects/jowls_of_dark_demise.c`
- L70: Jowls direct-attack flag; cleared when zone resets

### `KAIBAMAN`
- path: `src_custom/activated_effects/kaibaman.c`
- L96: tribute-replacement in same zone; not a marked special summon (unk4 stays 0)

### `KEEPER_OF_DRAGON_MAGIC`
- path: `src_custom/activated_effects/keeper_of_dragon_magic.c`
- L185: reveal Fusion Extra material-name SS FALSE; any GY face-down stand-in. Ceiling: OPT discard → add Poly/Fusion Normal; else OPT SS any from GY face-down DEF.

### `LADY_OF_D`
- path: `src_custom/activated_effects/lady_of_d.c`
- L47: opp cannot target your face-up Dragons for attacks needs target- redirect hook. Ceiling: OPT discard 1 Dragon from hand (destroy-save stand-in).

### `LEGENDARY_KNIGHT_CRITIAS`
- path: `src_custom/activated_effects/legendary_knight_critias.c`
- L99: Legend of Heart SS + when-attacked Set Trap from GY need summon/battle hooks. Ceiling: OPT banish 1 face-up Spell/Trap on the field.

### `LEGENDARY_KNIGHT_HERMOS`
- path: `src_custom/activated_effects/legendary_knight_hermos.c`
- L99: Legend of Heart SS + when-attacked GY name/effect copy need summon/battle hooks. Ceiling: OPT banish 1 face-up Spell/Trap.

### `LEGENDARY_KNIGHT_TIMAEUS`
- path: `src_custom/activated_effects/legendary_knight_timaeus.c`
- L99: Legend of Heart SS + attacked-set-Spell-from-GY need summon/battle hooks. Ceiling: OPT banish 1 face-up Spell/Trap on the field.

### `LEKUNGA`
- path: `src_custom/activated_effects/lekunga.c`
- L12: no Lekunga Token card id — MOON_TOKEN stand-in. Ceiling: wrong Type/Attribute/stats (Fairy/LIGHT 0/0 vs Plant/WATER 700/700); upgrade: add LEKUNGA_TOKEN card data + art, then swap this define.

### `LEVEL_EATER`
- path: `src_custom/activated_effects/level_eater.c`
- L121: no zone Level-mod field (level is ROM-only via gCardData_NEW). Ceiling: SS self from GY; upgrade: TempLevel overlay on target.
- L177: GY ignition + cannot-be-Tributed-except-for-Tribute-Summon need GY-menu + tribute hooks. Ceiling: GY ignition when Lv5+ you control + empty zone (Treeborn pattern).

### `LEVIA_DRAGON_DAEDALUS`
- path: `src_custom/activated_effects/levia_dragon_daedalus.c`
- L122: walk gDuel.board directly; gFixedZones column order differs on opponent rows, so row/col checks against gMonEffect can skip the wrong slot.

### `LEVIAIR_THE_SEA_DRAGON`
- path: `src_custom/activated_effects/leviair_the_sea_dragon.c`
- L62: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- L107: no Xyz detach cost; OPT SS banished Lv≤4 stand-in when RFP enabled. Ceiling: materials not checked; upgrade: overlay detach before SS.

### `LIFE_STREAM_DRAGON`
- path: `src_custom/activated_effects/life_stream_dragon.c`
- L28: Synchro LP=4000 trigger + no effect damage + Equip-banish destruction-replace need synchro/LP/battle hooks. Ceiling: OPT set LP to 4000 via usage.

### `LIGHTRAY_GEARFRIED`
- path: `src_custom/activated_effects/lightray_gearfried.c`
- L194: Quick negate S/T activation needs chain hooks. Ceiling: OPT banish Warrior GY → destroy 1 S/T.

### `LIGHTSWORN_DRAGONLING`
- path: `src_custom/activated_effects/lightsworn_dragonling.c`
- L134: hand SS when Lightsworn in GY uses FromHand path. Ceiling: field OPT send 1 other Lightsworn from Deck to GY.

### `LORD_OF_THE_RED`
- path: `src_custom/activated_effects/lord_of_the_red.c`
- L115: either-turn chain on activation + S/T branch need chain hooks. Ceiling: OPT destroy 1 monster on the field.

### `LUMINA_TWILIGHTSWORN_SHAMAN`
- path: `src_custom/activated_effects/lumina_twilightsworn_shaman.c`
- L226: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.

### `LYLA_LIGHTSWORN_SORCERESS`
- path: `src_custom/activated_effects/lyla_lightsworn_sorceress.c`
- L124: /* EP mill via TryApplyLylaEndPhase; ponytail: position-lock after OPT needs

### `LYLA_TWILIGHTSWORN_ENCHANTRESS`
- path: `src_custom/activated_effects/lyla_twilightsworn_enchantress.c`
- L205: quick effect on Spell/Trap activation + mill 3 when other LS activates need chain hooks. Ceiling: OPT banish LS from hand/GY then destroy 1 face-up Spell/Trap. EP mill 3 stand-in via TryApplyTwilightswornEndPhase.

### `MA_AT`
- path: `src_custom/activated_effects/ma_at.c`
- L102: name-3 declare UI missing; add any excavated as stand-in.
- L134: name-3 excavate UI hard. Ceiling: OPT reveal top 3, add any, mill rest.

### `MAGICAL_MARIONETTE`
- path: `src_custom/activated_effects/magical_marionette.c`
- L117: Spell Counter on Spell resolve + +200 ATK/counter need spell/stat hooks. Ceiling: OPT remove 2 unk4 counters → destroy 1 monster.

### `MAGICAL_PLANT_MANDRAGOLA`
- path: `src_custom/activated_effects/magical_plant_mandragola.c`
- L12: FLIP place Spell Counters needs flip + counter storage. Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon gate outside this file.

### `MAGICAL_SCIENTIST`
- path: `src_custom/activated_effects/magical_scientist.c`
- L215: no direct attack + End Phase Extra Deck return need battle/EP hooks. Ceiling: pay 1000 → SS Lv≤6 Fusion from Extra/recipe list.

### `MAGICIANS_ROBE`
- path: `src_custom/activated_effects/magicians_robe.c`
- L56: opp-turn quick + GY SS banish-on-leave need phase/GY hooks. Ceiling: discard S/T from hand → SS DM from Deck via FromHand path.
- L76: opponent's turn gate not wired.

### `MAGICIANS_SOULS`
- path: `src_custom/activated_effects/magicians_souls.c`
- L143: Continuous Spell placement + DM/DMG GY SS branch need placement/ GY hooks. Ceiling: OPT send 1–2 S/T from hand/field → draw that many.

### `MAN_THRO_TRO`
- path: `src_custom/activated_effects/man_thro_tro.c`
- L21: Ojama Trio monster form is the only token-like field unit today

### `MANJU_OF_THE_TEN_THOUSAND_HANDS`
- path: `src_custom/activated_effects/manju_of_the_ten_thousand_hands.c`
- L113: Normal/Flip Summon trigger needs summon hook. Ceiling: once via usage if Ritual Monster or Ritual Spell in Deck and hand space.

### `MASTER_OF_CHAOS`
- path: `src_custom/activated_effects/master_of_chaos.c`
- L204: Fusion SS trigger + destroyed GY Spell add need summon/destroy hooks. Ceiling: OPT SS LIGHT/DARK from GY, else tribute LIGHT+DARK → banish.

### `MASTER_PEACE_THE_TRUE_DRACOSLAYING_KING`
- path: `src_custom/activated_effects/master_peace_the_true_dracoslaying_king.c`
- L54: Quick Effect destroy→banish stand-in via Duel_BanishZone.
- L111: Tribute Continuous S/T + unaffected-by-type FALSE. Ceiling: OPT banish 1 other field card (Quick destroy stand-in).

### `MASTERFLARE_HYPERION`
- path: `src_custom/activated_effects/masterflare_hyperion.c`
- L237: name/effect copy + Quick negate FALSE. Ceiling: OPT mill Agent/Sanctuary-mention, else OPT banish Fairy → destroy 1.

### `MAXX_C`
- path: `src_custom/activated_effects/maxx_c.c`
- L55: draw-on-opponent-Special-Summon this turn not wired; upgrade: SS hook + simple turn flag when one exists.

### `MAZERA_DEVILLE`
- path: `src_custom/activated_effects/mazera_deville.c`
- L53: on-SS-with-Pandemonium discard-3 needs summon hook. Ceiling: OPT discard 1 random opp + mill 3.

### `MEZUKI`
- path: `src_custom/activated_effects/mezuki.c`
- L169: GY ignition needs GY-menu wire. Ceiling: allow when Mezuki + another Zombie in expanded GY (callable if gMonEffect set to Mezuki).

### `MILLENNIUM_EYES_RESTRICT`
- path: `src_custom/activated_effects/millennium_eyes_restrict.c`
- L88: chain equip/absorb opp Effect Monster needs chain/control hooks. Ceiling: OPT destroy 1 opp monster.

### `MINERVA_THE_ATHENIAN_LIGHTSWORN`
- path: `src_custom/activated_effects/minerva_the_athenian_lightsworn.c`
- L184: anti-banish continuous + Synchro material count need continuous/synchro hooks. Ceiling: OPT mill LS different Types (up to field LS count), or banish ≤4 LS GY → mill.

### `MIRAGE_DRAGON`
- path: `src_custom/activated_effects/mirage_dragon.c`
- L12: opp cannot activate Traps in Battle Phase needs trap-activation gate. Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.

### `MIRROR_FORCE_DRAGON`
- path: `src_custom/activated_effects/mirror_force_dragon.c`
- L12: when targeted for attack/effect trigger needs protection hook. Ceiling: not ignition-activatable here; upgrade: trigger destroy-all.

### `MOLTEN_ZOMBIE`
- path: `src_custom/activated_effects/molten_zombie.c`
- L18: printed trigger is SS from GY. Ceiling: once via usage when Activate runs (summon-dispatch or manual).

### `MORPHTRONIC_BOOMBOXEN`
- path: `src_custom/activated_effects/morphtronic_boomboxen.c`
- L12: double attack in ATK + DEF negate-attack need battle/position hooks. Ceiling: not ignition-activatable here.

### `MORPHTRONIC_CAMERAN`
- path: `src_custom/activated_effects/morphtronic_cameran.c`
- L175: * ponytail: DEF Morphtronic untargetable needs targeting gate. */

### `MORPHTRONIC_CELFON`
- path: `src_custom/activated_effects/morphtronic_celfon.c`
- L136: reveal/look UI missing; die roll + SS/add among top N. Ceiling: ATK OPT die→SS Lv≤4 Morphtronic; DEF OPT die→add Morphtronic.

### `MORPHTRONIC_EARFON`
- path: `src_custom/activated_effects/morphtronic_earfon.c`
- L48: real Tuner flag / Equip double-attack need Synchro/equip hooks. Ceiling: OPT PickZone mark unk4 as Tuner stand-in.
- L95: on-SS Tuner mark + Equip 2-attacks FALSE. Ceiling: OPT PickZone treat face-up as Tuner (unk4).

### `MORPHTRONIC_LANTRON`
- path: `src_custom/activated_effects/morphtronic_lantron.c`
- L98: * ponytail: ATK redirect effect damage needs effect-damage hook. */

### `MORPHTRONIC_MAGNEN`
- path: `src_custom/activated_effects/morphtronic_magnen.c`
- L12: ATK-position highest-ATK-only attack target + DEF-position redirect-attack need battle/position hooks. Ceiling: not ignition here.

### `MORPHTRONIC_MAGNEN_BAR`
- path: `src_custom/activated_effects/morphtronic_magnen_bar.c`
- L55: exactly-2-other ATK gate + DEF cannot-attack need battle hooks. Ceiling: ATK Position OPT refresh tempStage from other ATK/500.

### `MORPHTRONIC_REMOTEN`
- path: `src_custom/activated_effects/morphtronic_remoten.c`
- L213: position-gated OPT search. ATK: banish GY Morphtronic → add same Lv. DEF: discard Morphtronic → add other same Lv.

### `MORPHTRONIC_SCANNEN`
- path: `src_custom/activated_effects/morphtronic_scannen.c`
- L194: FromHand banish Morphtronic → SS; ATK/DEF OPT search modes.

### `MORPHTRONIC_SCOPEN`
- path: `src_custom/activated_effects/morphtronic_scopen.c`
- L58: DEF Position → treat as Level 4 + EP destroy on ATK-mode SS need position/EP hooks. Ceiling: ATK Position OPT SS 1 Lv4 Morphtronic from hand.

### `MORPHTRONIC_SLINGEN`
- path: `src_custom/activated_effects/morphtronic_slingen.c`
- L160: DEF destroy-other-Morphtronic substitute needs destroy redirect hook. Ceiling: ATK OPT tribute 1 other Morphtronic → destroy 1 field card.

### `MORPHTRONIC_SMARTFON`
- path: `src_custom/activated_effects/morphtronic_smartfon.c`
- L228: reveal UI FALSE. Ceiling: ATK die excavate add; DEF GY add Morphtronic. FromHand: banish Morphtronic GY → SS.

### `MORPHTRONIC_STAPLEN`
- path: `src_custom/activated_effects/morphtronic_staplen.c`
- L102: * ponytail: ATK attack-redirect needs battle hook. Ceiling: OPT change 1 opp ATK to DEF. */

### `MORPHTRONIC_TELEFON`
- path: `src_custom/activated_effects/morphtronic_telefon.c`
- L176: reveal UI FALSE. Ceiling: ATK die→LP+SS Morph Lv≤roll; DEF die excavate add.

### `MORPHTRONIC_VACUUMEN`
- path: `src_custom/activated_effects/morphtronic_vacuumen.c`
- L24: send Equip → burn + DEF equip-take-control need equip hooks. Ceiling: ATK Position OPT burn 500.

### `NAELSHADDOLL_ARIEL`
- path: `src_custom/activated_effects/naelshaddoll_ariel.c`
- L72: FLIP SS banished Shaddoll + sent-by-effect branch need flip/RFP hooks. Ceiling: OPT banish up to 3 cards from either GY.

### `NATURIA_BEAST`
- path: `src_custom/activated_effects/naturia_beast.c`
- L12: Quick Effect spell negate + mill 2 need chain/negation hooks. Ceiling: not ignition-activatable here; upgrade: either-turn interrupt.

### `NECROFACE`
- path: `src_custom/activated_effects/necroface.c`
- L86: Normal Summon shuffle + banish-mill branches need summon/banish hooks. Ceiling: OPT shuffle all banished into Decks + tempStage per card.
- L107: tempStage unit is ~500 ATK, not printed +100; upgrade: exact overlay.

### `NEHSHADDOLL_GENIUS`
- path: `src_custom/activated_effects/nehshaddoll_genius.c`
- L54: until end of turn clear needs EOT unk4 reset hook.
- L110: FLIP Shaddoll unaffected + sent-by-effect branches need flip/send hooks. Ceiling: OPT negate 1 face-up Effect Monster (unk4).

### `NEO_BLUE_EYES_ULTIMATE_DRAGON`
- path: `src_custom/activated_effects/neo_blue_eyes_ultimate_dragon.c`
- L79: Damage Step / Fusion-Summon / protect-negate FALSE. Ceiling: OPT send BE Fusion-ish from Deck → unk4 extra-attack mark. (printed up-to-twice; OPT usage flag is the stand-in).
- L105: real multi-attack needs battle hook; unk4=2 extra-attack stand-in.

### `NEO_SPACE_CONNECTOR`
- path: `src_custom/activated_effects/neo_space_connector.c`
- L61: on-Normal-Summon trigger + tribute-bounce second effect need summon/tribute hooks. Ceiling: OPT SS Neo-Spacian or Neos from Deck DEF.

### `NEO_SPACIAN_DARK_PANTHER`
- path: `src_custom/activated_effects/neo_spacian_dark_panther.c`
- L12: copy opp monster name/effects needs engine name/effect overlay. Ceiling: not ignition-activatable here; upgrade: permanent/name/effect copy.

### `NEO_SPACIAN_MARINE_DOLPHIN`
- path: `src_custom/activated_effects/neo_spacian_marine_dolphin.c`
- L79: treated-as Aqua Dolphin name + NEX-only SS need continuous/summon hooks.

### `NIBIRU_THE_PRIMAL_BEING`
- path: `src_custom/activated_effects/nibiru_the_primal_being.c`
- L90: 5-summon gate + Primal Being Token to opp FALSE. Ceiling: FromHand wipe+SS if ≥5 face-up monsters on field.

### `NITRO_WARRIOR`
- path: `src_custom/activated_effects/nitro_warrior.c`
- L96: Spell ATK gain + battle-after destroy trigger FALSE. Ceiling: OPT change 1 face-up DEF opp monster to ATK (battle-after stand-in).

### `NUMBER_39_UTOPIA`
- path: `src_custom/activated_effects/number_39_utopia.c`
- L12: attack negate via detach + no-material self-destroy need battle hook and XYZ material system. Ceiling: not field-ignition activatable.

### `OJAMA_KING`
- path: `src_custom/activated_effects/ojama_king.c`
- L54: PickZone for up to 3 empty zones + continuous lock gate. Ceiling: auto-lock first 3 empty opp MMZ via isLocked (ignored by FirstEmptyZoneInRow today — same as Ground Collapse).

### `POSEIDRA_THE_ATLANTEAN_DRAGON`
- path: `src_custom/activated_effects/poseidra_the_atlantean_dragon.c`
- L284: hand SS uses FromHand path. Ceiling: GY ignition like Malicious.

### `POWER_TOOL_BRAVER_DRAGON`
- path: `src_custom/activated_effects/power_tool_braver_dragon.c`
- L99: SS equip Equip Spells from Deck/GY hard; send-equip negate FALSE. Ceiling: OPT change battle position of 1 monster.

### `POWER_TOOL_DRAGON`
- path: `src_custom/activated_effects/power_tool_dragon.c`
- L55: reveal-3 opp-picks + equip destruction replace need reveal/destroy hooks. Ceiling: OPT add first Equip Spell from Deck.

### `PREDAPLANT_VERTE_ANACONDA`
- path: `src_custom/activated_effects/predaplant_verte_anaconda.c`
- L129: DARK attribute mark + Poly/Fusion copy SS need attribute/fusion hooks. Ceiling: pay 2000 LP → destroy 1 field card.

### `PROTECTOR_OF_THE_AGENTS_MOON`
- path: `src_custom/activated_effects/protector_of_the_agents_moon.c`
- L252: dual PickZone needs scratch; auto first Fairy tribute.
- L305: Link Summon trigger gate missing. Ceiling: OPT mill/add Sanctuary path, else OPT tribute Fairy → destroy 1 opp.

### `PROTECTOR_OF_THE_SANCTUARY`
- path: `src_custom/activated_effects/protector_of_the_sanctuary.c`
- L12: opp cannot draw except Draw Phase needs draw-gate LynJump. Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.

### `PUNISHMENT_DRAGON`
- path: `src_custom/activated_effects/punishment_dragon.c`
- L191: hand SS via 4+ banished LS uses FromHand path; LS mill 4 needs effect-activation hook. Ceiling: pay 1000 → shuffle all banished into Decks.

### `QADSHADDOLL_KEIOS`
- path: `src_custom/activated_effects/qadshaddoll_keios.c`
- L50: FLIP vs sent-by-effect exclusivity + mill ATK gain need flip/send hooks. Ceiling: OPT SS 1 Shaddoll from hand face-up DEF.

### `QUINTET_MAGICIAN`
- path: `src_custom/activated_effects/quintet_magician.c`
- L64: Fusion-with-5-Spellcasters gate + untributable/undestroyable need fusion/summon hooks. Ceiling: once via usage destroy all opp cards.

### `RAIDEN_HAND_OF_THE_LIGHTSWORN`
- path: `src_custom/activated_effects/raiden_hand_of_the_lightsworn.c`
- L101: +1 tempStage (~500 ATK, not exact +200); until opp EP clear needs hook.

### `RAINBOW_DARK_DRAGON`
- path: `src_custom/activated_effects/rainbow_dark_dragon.c`
- L265: hand SS by banishing 7 different DARK uses FromHand path. Ceiling: OPT banish other DARK you control/from GY → +500 ATK each (tempStage).

### `REESHADDOLL_WENDI`
- path: `src_custom/activated_effects/reeshaddoll_wendi.c`
- L59: FLIP vs sent-by-effect face-down DEF branches need flip/send hooks. Ceiling: OPT SS 1 other Shaddoll from Deck face-up DEF.

### `REESHADDOLL_WENDIKURUHU`
- path: `src_custom/activated_effects/reeshaddoll_wendikuruhu.c`
- L73: Quick face-up→face-down follow-up + GY Shaddoll add need flip/send hooks. Ceiling: OPT flip all face-down monsters face-up DEF.

### `REPTILIANNE_ECHIDNA`
- path: `src_custom/activated_effects/reptilianne_echidna.c`
- L230: Link Summon trigger + Extra Deck lock FALSE. Ceiling: OPT set 1 opp face-up ATK to 0, else OPT add Reptiles up to 0-ATK count. Separate OPT flags share one MarkMonsterEffectUsed.

### `REPTILIANNE_LAMIA`
- path: `src_custom/activated_effects/reptilianne_lamia.c`
- L97: GY synchro-material ATK-0 need synchro hook. Ceiling: not field-ignition; FromHand ATK-0 + SS + self-damage.
- L146: FromHand targeting not wired; auto-pick highest original ATK opp.

### `REPTILIANNE_MEDUSA`
- path: `src_custom/activated_effects/reptilianne_medusa.c`
- L76: cannot change battle position needs position-change gate.

### `REPTILIANNE_VASKII`
- path: `src_custom/activated_effects/reptilianne_vaskii.c`
- L191: only-SS-by-tribute + unique-on-field need summon/field hooks. Ceiling: OPT destroy 1 face-up opp monster.
- L233: multi-zone tribute picker not wired; auto-tribute first two 0 ATK.

### `RESCUE_CAT`
- path: `src_custom/activated_effects/rescue_cat.c`
- L123: negated effects + End Phase destroy not applied; upgrade: summon flags + turn-end cleanup gate.

### `RESCUE_RABBIT`
- path: `src_custom/activated_effects/rescue_rabbit.c`
- L126: End Phase destroy + effect negate not applied; upgrade: turn-end gate.

### `RINYAN_LIGHTSWORN_ROGUE`
- path: `src_custom/activated_effects/rinyan_lightsworn_rogue.c`
- L41: FLIP trigger needs flip hook. Ceiling: once via usage if LS in GY.

### `ROAD_SYNCHRON`
- path: `src_custom/activated_effects/road_synchron.c`
- L12: Synchro Level -2 (non-Road Warrior) + battle-hit Level +1 need synchro/battle hooks. Ceiling: not ignition-activatable here.

### `ROYAL_MAGICAL_LIBRARY`
- path: `src_custom/activated_effects/royal_magical_library.c`
- L22: Spell Counters on Spell activation need spell-resolve hook. Ceiling: ignition only when unk4>=3 (never rises alone); upgrade: on Spell resolve → if face-up ROYAL_MAGICAL_LIBRARY then zone->unk4++ (cap 3).

### `RYKO_LIGHTSWORN_HUNTER`
- path: `src_custom/activated_effects/ryko_lightsworn_hunter.c`
- L107: FLIP trigger needs flip hook. Ceiling: once via usage.

### `RYKO_TWILIGHTSWORN_FIGHTER`
- path: `src_custom/activated_effects/ryko_twilightsworn_fighter.c`
- L191: NS/flip + other-Lightsworn mill 3 need summon/chain hooks. Ceiling: OPT banish LS from hand/GY then banish 1 field card; EP mill 3 stand-in via TryApplyTwilightswornEndPhase.

### `SHADDOLL_BEAST`
- path: `src_custom/activated_effects/shaddoll_beast.c`
- L20: FLIP draw2/discard1 and GY-sent draw1 share 1/turn exclusivity. Ceiling: OPT draw 1 stand-in for GY effect only; upgrade: flip + GY hooks.

### `SHADDOLL_DRAGON`
- path: `src_custom/activated_effects/shaddoll_dragon.c`
- L183: FLIP vs GY-sent exclusivity + trigger hooks deferred. Ceiling: bounce 1 opp card OR destroy 1 opp Spell/Trap once via usage.

### `SHADDOLL_FALCO`
- path: `src_custom/activated_effects/shaddoll_falco.c`
- L115: FLIP vs GY-sent exclusivity + SS-self-on-send need trigger hooks. Ceiling: OPT SS 1 other Shaddoll from GY face-down DEF.

### `SHADDOLL_HEDGEHOG`
- path: `src_custom/activated_effects/shaddoll_hedgehog.c`
- L112: FLIP S/T vs GY-sent monster exclusivity + trigger hooks deferred. Ceiling: OPT search 1 Shaddoll S/T or monster from Deck once via usage.

### `SHADDOLL_HOUND`
- path: `src_custom/activated_effects/shaddoll_hound.c`
- L93: FLIP vs sent-by-effect battle-position branch need flip/send hooks. Ceiling: OPT add 1 Shaddoll from GY to hand.

### `SHADDOLL_SQUAMATA`
- path: `src_custom/activated_effects/shaddoll_squamata.c`
- L154: FLIP destroy vs GY-sent mill exclusivity + trigger hooks deferred. Ceiling: destroy 1 opp monster OR mill 1 Shaddoll from Deck once via usage.

### `SILENT_SWORDSMAN`
- path: `src_custom/activated_effects/silent_swordsman.c`
- L134: * ponytail: Quick Spell negate needs chain hook. */

### `SILENT_SWORDSMAN_LV3`
- path: `src_custom/activated_effects/silent_swordsman_lv3.c`
- L71: * self → SS LV5 wired below. ponytail: summon/flip turn gate needs hooks. */

### `SILENT_SWORDSMAN_LV5`
- path: `src_custom/activated_effects/silent_swordsman_lv5.c`
- L71: * SS LV7 wired below. ponytail: Standby-after-direct-damage gate needs hook. */

### `SIMORGH_BIRD_OF_ANCESTRY`
- path: `src_custom/activated_effects/simorgh_bird_of_ancestry.c`
- L110: WIND tribute-reduce continuous + hand-as-Normal Monster need summon/permanent hooks. Ceiling: OPT return up to 2 opp cards to hand.

### `SKILLED_DARK_MAGICIAN`
- path: `src_custom/activated_effects/skilled_dark_magician.c`
- L80: Spell Counters on Spell activation need spell-resolve hook. Ceiling: ignition when unk4>=3 (never rises alone); upgrade: on Spell resolve → if face-up SKILLED_DARK_MAGICIAN then zone->unk4++ (cap 3).

### `SKILLED_WHITE_MAGICIAN`
- path: `src_custom/activated_effects/skilled_white_magician.c`
- L80: Spell Counters on Spell resolve need spell-resolve hook. Ceiling: ignition when unk4>=3; upgrade: on Spell resolve → unk4++ (cap 3).

### `SOUL_ABSORBING_BONE_TOWER`
- path: `src_custom/activated_effects/soul_absorbing_bone_tower.c`
- L12: attack redirect while another Zombie present + mill 2 on Zombie SS need continuous/SS hooks. Ceiling: not ignition-activatable here.

### `STARDUST_DRAGON`
- path: `src_custom/activated_effects/stardust_dragon.c`
- L12: Quick Effect tribute-negate-destroy + End Phase GY SS need chain and EP hooks. Ceiling: not ignition-activatable here.

### `T_G_HYPER_LIBRARIAN`
- path: `src_custom/activated_effects/t_g_hyper_librarian.c`
- L12: Synchro Summon draw trigger needs synchro hook. Ceiling: not ignition-activatable here; upgrade: synchro summon gate.

### `TATSUNOKO`
- path: `src_custom/activated_effects/tatsunoko.c`
- L12: hand-as-Synchro-material and unaffected-by-monster-effects need synchro/summon continuous hooks. Ceiling: not field-ignition here.

### `TEST_BEAR`
- path: `src_custom/activated_effects/test_bear.c`
- L237: Deck/ED-summoned GB gate for hand SS relaxed to any face-up GB. Ceiling: OPT tribute self + shuffle 1 GB → SS up to 2 GB from Deck.
- L287: printed needs GB SS from Deck/ED; stand-in = any face-up GB.

### `TEST_PANTHER`
- path: `src_custom/activated_effects/test_panther.c`
- L199: Link Summon trigger for search needs summon hook. Ceiling: OPT search GB from Deck, else bounce GB → SS different GB.

### `TETHYS_GODDESS_OF_LIGHT`
- path: `src_custom/activated_effects/tethys_goddess_of_light.c`
- L50: opening hand is seeded before duel gfx; skip like Solemn Wishes.
- L54: unk18 != 0 means battle/damage resolution is active.

### `THE_AGENT_OF_DESTRUCTION_VENUS`
- path: `src_custom/activated_effects/the_agent_of_destruction_venus.c`
- L66: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.
- L192: leave-field Deck bottom for Shine Balls needs leave hook. Ceiling: OPT pay 500×N → SS N Mystical Shine Ball from banished/GY.

### `THE_AGENT_OF_ENTROPY_URANUS`
- path: `src_custom/activated_effects/the_agent_of_entropy_uranus.c`
- L117: tempStage stores milled Level, not a true level change hook.

### `THE_AGENT_OF_JUDGMENT_SATURN`
- path: `src_custom/activated_effects/the_agent_of_judgment_saturn.c`
- L39: skip Battle Phase this turn needs phase-lock hook. Ceiling: tribute self → burn LP difference when Sanctuary face-up and LP higher.

### `THE_AGENT_OF_LIFE_NEPTUNE`
- path: `src_custom/activated_effects/the_agent_of_life_neptune.c`
- L160: tribute-lock + banish search FALSE. Ceiling: FromHand discard self → SS Agent (or Hyperion if Sanctuary).

### `THE_AGENT_OF_MIRACLES_JUPITER`
- path: `src_custom/activated_effects/the_agent_of_miracles_jupiter.c`
- L132: +800 ATK until EP needs exact stage/EP clear; Sanctuary RFG revive FALSE. Ceiling: banish Agent from GY → +2 tempStage on LIGHT Fairy.

### `THE_AGENT_OF_MYSTERU_EARTH`
- path: `src_custom/activated_effects/the_agent_of_mysteru_earth.c`
- L110: Normal Summon trigger needs summon hook. Ceiling: OPT add 1 The Agent except Earth from Deck, or Master Hyperion if Sanctuary is face-up.

### `THE_AGENT_OF_WISDOM_MERCURY`
- path: `src_custom/activated_effects/the_agent_of_wisdom_mercury.c`
- L20: Standby Phase empty-hand-last-EP check needs turn-end hook. Ceiling: once via usage if hand empty; upgrade: standby/end-phase gate.

### `THE_BLAZING_MARS`
- path: `src_custom/activated_effects/the_blazing_mars.c`
- L48: no multi-select GY banish + hand/GY activation path yet — banish 3 other monsters to Special Summon deferred until expanded GY targeting exists.
- L63: no Main Phase 1 gate yet — field burn is activatable in any main phase.

### `THE_EXECUTOR_OF_THE_UNDERWORLD_PLUTO`
- path: `src_custom/activated_effects/the_executor_of_the_underworld_pluto.c`
- L163: Quick via Sanctuary + GY add Sanctuary FALSE. Ceiling: OPT banish 1 monster from GY → flip 1 Effect Monster face-down DEF.

### `THE_LEGENDARY_EXODIA_INCARNATE`
- path: `src_custom/activated_effects/the_legendary_exodia_incarnate.c`
- L125: ATK gain / unaffected FALSE. Ceiling: OPT add Forbidden One from GY. FromHand tribute Forbidden One → SS.

### `THE_SUPPRESSION_PLUTO`
- path: `src_custom/activated_effects/the_suppression_pluto.c`
- L213: on-summon text after field draw so Pluto is visible.

### `THE_TRICKY`
- path: `src_custom/activated_effects/the_tricky.c`
- L74: discard pick excludes summon slot; upgrade path: exchange_hand_selection helper

### `THE_WINGED_DRAGON_OF_RA_SPHERE_MODE`
- path: `src_custom/activated_effects/the_winged_dragon_of_ra_sphere_mode.c`
- L57: hand permanent-effect scan is skipped when turn_off_visual_scanner is on (gHideEffectText), so use Blue Eyes Shining-style post-board-scan auto-summon.
- L159: in-place tribute replacement; Duel_SpecialSummon* needs an empty zone

### `THEINEN_THE_GREAT_SPHINX`
- path: `src_custom/activated_effects/theinen_the_great_sphinx.c`
- L39: Andro+Teleia destroy SS from hand/Deck needs destroy hook. Ceiling: OPT pay 500 → +7 tempStage (~3000 ATK).

### `THUNDER_DRAGON_TITAN`
- path: `src_custom/activated_effects/thunder_dragon_titan.c`
- L102: Thunder hand-effect trigger + GY-banish instead of destroy need chain/continuous hooks. Ceiling: OPT destroy 1 card on the field.

### `THUNDER_END_DRAGON`
- path: `src_custom/activated_effects/thunder_end_dragon.c`
- L59: no Xyz detach cost; OPT destroy-all-other-monsters stand-in. Ceiling: materials not checked; upgrade: overlay detach before destroy.

### `TIMAEUS_THE_KNIGHT_OF_DESTINY`
- path: `src_custom/activated_effects/timaeus_the_knight_of_destiny.c`
- L53: unaffected + once-per-battle damage calc FALSE. Ceiling: OPT set ATK/DEF ≈ highest field ATK via tempStage.

### `TIME_MAGIC_HAMMER`
- path: `src_custom/activated_effects/time_magic_hammer.c`
- L12: Hermos equip + battle-step dice banish need summon/equip/battle hooks. Ceiling: not field-ignition activatable here.

### `TIME_THIEF_REDOER`
- path: `src_custom/activated_effects/time_thief_redoer.c`
- L140: detach materials + banish-until-EP FALSE. Ceiling: OPT draw 1 OR return 1 face-up opp monster to Deck.

### `TIMEAUS_THE_UNITED_DRAGON`
- path: `src_custom/activated_effects/timeaus_the_united_dragon.c`
- L147: Main Phase Fusion Summon needs fusion UI hook. Ceiling: SS from hand via send cost uses FromHand path.

### `TOADALLY_AWESOME`
- path: `src_custom/activated_effects/toadally_awesome.c`
- L212: detach/Standby/negate FALSE. Ceiling: OPT SS Frog from Deck, else OPT send Aqua → destroy 1 opp.

### `TOHUSHADDOLL_GRYSTA`
- path: `src_custom/activated_effects/tohushaddoll_grysta.c`
- L22: FLIP copy + GY Fusion-by-banish need flip/GY hooks. Ceiling: OPT add Shaddoll Fusion from Deck.

### `TORNADO_BIRD`
- path: `src_custom/activated_effects/tornado_bird.c`
- L85: FLIP trigger needs flip hook. Ceiling: once via usage.

### `TRISHULA_DRAGON_OF_THE_ICE_BARRIER`
- path: `src_custom/activated_effects/trishula_dragon_of_the_ice_barrier.c`
- L114: Synchro Summon trigger needs synchro hook. Ceiling: once via usage banish random opp hand + 1 field + 1 GY when available.

### `TUALATIN`
- path: `src_custom/activated_effects/tualatin.c`
- L108: FromHand battle-wipe SS + Summon Attribute lock FALSE. Ceiling: OPT destroy all face-up monsters of first opp monster's Attribute.

### `TUNINGWARE`
- path: `src_custom/activated_effects/tuningware.c`
- L12: Synchro level-2 treatment + draw-on-material need synchro hooks. Ceiling: not ignition-activatable here; upgrade: synchro summon gate.

### `TURBO_BOOSTER`
- path: `src_custom/activated_effects/turbo_booster.c`
- L101: destroy only monsters that battled your monsters this turn needs battle-tracking hook. Ceiling: OPT tribute self then destroy 1 opponent monster; SS-from-hand uses FromHand path.
- L138: no Normal Summon-this-turn flag in engine; allow hand SS anytime. Upgrade: gate on turn flag once duel state tracks Normal Summons.

### `TURBO_SYNCHRON`
- path: `src_custom/activated_effects/turbo_synchron.c`
- L12: attack-target DEF change + battle-damage SS from hand need battle hooks. Ceiling: not ignition-activatable here.

### `TYRANT_BURST_DRAGON`
- path: `src_custom/activated_effects/tyrant_burst_dragon.c`
- L12: multi-attack + equip-to-monster need battle/equip continuous hooks. Ceiling: not ignition-activatable here; upgrade: permanent battle/equip gate.

### `ULTIMATE_CONDUCTOR_TYRANNO`
- path: `src_custom/activated_effects/ultimate_conductor_tyranno.c`
- L194: multi-attack + DEF burn/send need battle hooks. Ceiling: OPT destroy 1 of your monsters → flip all opp face-up monsters face-down DEF.

### `ULTIMATE_OBEDIENT_FIEND`
- path: `src_custom/activated_effects/ultimate_obedient_fiend.c`
- L12: solo-field + empty-hand attack restriction needs attack gate hook. Ceiling: not field-ignition activatable here.

### `ULTIMATE_TYRANNO`
- path: `src_custom/activated_effects/ultimate_tyranno.c`
- L12: multi-attack + Tyranno-only battle phase gate need battle hooks. Ceiling: not field-ignition activatable here.

### `VICTORIA`
- path: `src_custom/activated_effects/victoria.c`
- L177: continuous attack redirect for other face-up Fairies needs attack-target hook. Ceiling: OPT SS 1 Dragon from opponent's GY.

### `VISION_HERO_ADORATION`
- path: `src_custom/activated_effects/vision_hero_adoration.c`
- L105: until end of turn clear needs EOT tempStage reset hook.

### `VISION_HERO_FARIS`
- path: `src_custom/activated_effects/vision_hero_faris.c`
- L148: Continuous Trap place + ED HERO lock need place/ED hooks. Ceiling: OPT add 1 Vision HERO from Deck to hand.

### `VISION_HERO_GRAVITO`
- path: `src_custom/activated_effects/vision_hero_gravito.c`
- L64: no RemovedFromPlay_RemoveAt — shift RFP array in place after add. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- L113: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip zone API. Ceiling: OPT add 1 banished HERO monster to hand.

### `VISION_HERO_INCREASE`
- path: `src_custom/activated_effects/vision_hero_increase.c`
- L69: GY Continuous Trap place + tribute HERO SS-self FALSE. Ceiling: OPT SS Vision HERO Lv≤4 from Deck (ST-zone SS stand-in).

### `WEISS_LIGHTSWORN_ARCHFIEND`
- path: `src_custom/activated_effects/weiss_lightsworn_archfiend.c`
- L167: sent-from-Deck-to-GY trigger needs mill/send hook. Ceiling: field OPT SS 1 other Lightsworn from GY.

### `WHITE_HORNED_DRAGON`
- path: `src_custom/activated_effects/white_horned_dragon.c`
- L79: on-Normal/Special Summon trigger needs summon hook. Ceiling: OPT banish up to 5 opp GY Spells + tempStage once via usage.
- L101: +1 tempStage per banished (~500 ATK each, not exact +300).

### `YAMORIMORI`
- path: `src_custom/activated_effects/yamorimori.c`
- L124: GY ignition needs GY-menu wire. Ceiling: banish self from GY + own Reptile + opp face-up present → destroy opp face-up monster.

### `ZERADIAS_HERALD_OF_HEAVEN`
- path: `src_custom/activated_effects/zeradias_herald_of_heaven.c`
- L13: destroy self when Sanctuary absent needs continuous field check. Ceiling: not ignition-activatable here; upgrade: permanent maintenance hook.

## permanent (50)

### `AMEBA`
- path: `src_custom/permanent_effects/ameba.c`
- L23: AI candidate sim runs real effect code but restores duel state; do not queue burns that survive into the chosen action.
- L72: skip nested UpdateDuelGfxExceptField; caller just refreshed field.

### `BLUE_EYES_ALTERNATIVE_WHITE_DRAGON`
- path: `src_custom/permanent_effects/blue_eyes_alternative_white_dragon.c`
- L50: BEWD stays in hand as a visible cost; only the alt card is cleared

### `BLUE_EYES_SHINING_DRAGON`
- path: `src_custom/permanent_effects/blue_eyes_shining_dragon.c`
- L68: in-place BEUD zone replacement; Duel_SpecialSummon* only fills empty zones

### `BREAKER_THE_MAGICAL_WARRIOR`
- path: `src_custom/permanent_effects/breaker_the_magical_warrior.c`
- L15: hand normal summon copies isFaceUp=0; attack-position monsters still count.

### `CYBER_KIRIN`
- path: `src_custom/permanent_effects/cyber_kirin.c`
- L8: ATK-position spell/trap negate, battle-draw, and OPT tribute damage zero need continuous/battle/tribute hooks not wired for permanents.

### `DARK_MAGICIAN_OF_DESTRUCTION`
- path: `src_custom/permanent_effects/dark_magician_of_destruction.c`
- L131: deck-first add; DM preferred by scan order, no picker.

### `DARKLORD_NURSE_REFICULE`
- path: `src_custom/permanent_effects/darklord_nurse_reficule.c`
- L8: LP gain→damage redirect needs LP-change hook.

### `DEEP_EYES_WHITE_DRAGON`
- path: `src_custom/permanent_effects/deep_eyes_white_dragon.c`
- L98: Blue-Eyes destroy hand-SS + burn need GY/destroy hooks; on-summon ATK only.
- L121: first Dragon in GY stand-in for target picker.

### `DESPAIR_FROM_THE_DARK`
- path: `src_custom/permanent_effects/despair_from_the_dark.c`
- L47: opp hand/Deck send by card effect not tracked — GY-top SS only.

### `DESTINY_HERO_DOOM_OVERLORD`
- path: `src_custom/permanent_effects/destiny_hero_doom_overlord.c`
- L327: banish-until-Standby = permanent banish; DARK HERO SS lock not wired.

### `DESTINY_HERO_DREAD_SERVANT`
- path: `src_custom/permanent_effects/destiny_hero_dread_servant.c`
- L77: * ponytail: NS Clock Tower counters need summon hook. */

### `DESTINY_HERO_DREADMASTER`
- path: `src_custom/permanent_effects/destiny_hero_dreadmaster.c`
- L284: Clock Tower Prison gate skipped; on-summon destroy/SS stand-in. D-HERO battle protect + no BD via DestinyHeroDreadmaster_* while face-up.

### `DRAGON_MASTER_MAGIA`
- path: `src_custom/permanent_effects/dragon_master_magia.c`
- L8: Quick negate-by-card-type needs chain/OPT hooks.

### `DRAGON_SPIRIT_OF_WHITE`
- path: `src_custom/permanent_effects/dragon_spirit_of_white.c`
- L59: Quick Tribute → SS Blue-Eyes from hand needs tribute/summon hooks.

### `EL_SHADDOLL_GRYSTA`
- path: `src_custom/permanent_effects/el_shaddoll_grysta.c`
- L126: negate opp Special Summon + send Shaddoll from hand need SS chain hook.

### `EL_SHADDOLL_SHEKHINAGA`
- path: `src_custom/permanent_effects/el_shaddoll_shekhinaga.c`
- L126: negate SS monster effect + send Shaddoll need effect-chain hook.

### `ELEMENTAL_HERO_CAPTAIN_GOLD`
- path: `src_custom/permanent_effects/elemental_hero_captain_gold.c`
- L68: with Skyscraper active, prefer normal summon as a 2100 beater

### `ELEMENTAL_HERO_ELECTRUM`
- path: `src_custom/permanent_effects/elemental_hero_electrum.c`
- L67: no removed-from-play zone yet — shuffle banished/exiled monsters back into each owner's deck once Duel_BanishZone (or equivalent) exists.

### `ELEMENTAL_HERO_FLASH`
- path: `src_custom/permanent_effects/elemental_hero_flash.c`
- L47: no banished-zone + no multi-card GY search yet — banish 3 E-Heroes and add Normal Spell from GY deferred until banish + GY targeting exist.

### `ELEMENTAL_HERO_SUNRISE`
- path: `src_custom/permanent_effects/elemental_hero_sunrise.c`
- L105: GetTypeGroup/SetCardInfo would clobber gCardInfo.atk already computed.
- L143: never RefreshFieldMonsterStatOverlays here. Placement often runs with updateGfx=FALSE (AI summon / fusion). Overlay-only stamps without a full field draw leave level stars and ATK/DEF tiles on undrawn card faces — field-wide glitch on the opponent's turn. ATK boost applies via ApplyFieldZoneStatsToCardInfo on the next real gfx update.
- L464: true timing is attack declaration; resolve post-battle so PickZone can run from the main loop (same pattern as Core). Opponent-turn textboxes corrupt field VRAM — auto-resolve silently.

### `ELEMENTAL_HERO_THE_SHINING`
- path: `src_custom/permanent_effects/elemental_hero_the_shining.c`
- L64: return up to 2 banished E-HEROes to hand deferred — no multi-RFP return UI yet. ATK overlay via ApplyDynamicZoneStats.

### `EVIL_HERO_INFERNAL_PRODIGY`
- path: `src_custom/permanent_effects/evil_hero_infernal_prodigy.c`
- L40: empty-field hand SS is FromHand activated; End-Phase tribute draw via TryApplyEvilHeroInfernalProdigyEndPhase.

### `EVIL_HERO_INFERNO_WING_BACKFIRE`
- path: `src_custom/permanent_effects/evil_hero_inferno_wing_backfire.c`
- L128: true trigger is Special Summon; on-summon stand-in covers SS path.
- L149: HERO battle-destroy 2100 burn needs battle-end hook.

### `EVIL_HERO_WILD_CYCLONE`
- path: `src_custom/permanent_effects/evil_hero_wild_cyclone.c`
- L97: * ponytail: attack S/T lock until end of Damage Step needs chain gate. */

### `EXECUTOR_MAKYURA`
- path: `src_custom/permanent_effects/executor_makyura.c`
- L93: most non-zero trapEffect values are chain-only; allow continuous exceptions.

### `FIRE_PRINCESS`
- path: `src_custom/permanent_effects/fire_princess.c`
- L37: normal hand summon copies isFaceUp=0; attack-position monsters still count

### `GRANADORA`
- path: `src_custom/permanent_effects/granadora.c`
- L92: unk4==1 means summon effect already fired; 0/2 are fresh normal/special summon

### `GREAT_MAJU_GARZETT`
- path: `src_custom/permanent_effects/great_maju_garzett.c`
- L48: ram_map byte packing can leave u16 fields at odd EWRAM addresses;

### `GRINDER_GOLEM`
- path: `src_custom/permanent_effects/grinder_golem.c`
- L8: hand SS to opp field + Grinder Tokens + NS/Set lock need summon/token hooks.

### `HARPIES_PET_PHANTASMAL_DRAGON`
- path: `src_custom/permanent_effects/harpies_pet_phantasmal_dragon.c`
- L8: /* Direct attack via HarpiesPetPhantasmalDragon_CanAttackDirectly. ponytail:

### `HERO_KID`
- path: `src_custom/permanent_effects/hero_kid.c`
- L76: true trigger is Special Summon; on-summon stand-in covers SS path.

### `JENIS_LIGHTSWORN_MENDER`
- path: `src_custom/permanent_effects/jenis_lightsworn_mender.c`
- L53: LS-effect mill source not tracked — any deck mill this turn stand-in. EP burn/heal via TryApplyJenisEndPhase.

### `LEGENDARY_MAJU_GARZETT`
- path: `src_custom/permanent_effects/legendary_maju_garzett.c`
- L8: ATK = tributed originals needs hand-tribute SS stat capture; FromHand only.

### `LIGHT_AND_DARKNESS_DRAGON`
- path: `src_custom/permanent_effects/light_and_darkness_dragon.c`
- L8: chain negate (−500 ATK/DEF) + GY destroy-all/SS need chain/GY hooks.

### `LIGHT_SERPENT`
- path: `src_custom/permanent_effects/light_serpent.c`
- L31: hand send only — !gGraveyardSendWasFromField is the hand/deck stand-in.

### `MAGICIAN_OF_DARK_ILLUSION`
- path: `src_custom/permanent_effects/magician_of_dark_illusion.c`
- L78: opp-turn hand SS + own S/T SS need chain hooks; on-summon GY SS only.

### `MAGICIANS_ROD`
- path: `src_custom/permanent_effects/magicians_rod.c`
- L138: GY tribute Spellcaster → add this needs opp-turn quick hook.

### `MAJU_GARZETT`
- path: `src_custom/permanent_effects/maju_garzett.c`
- L48: ram_map byte packing can leave u16 fields at odd EWRAM addresses;

### `MOBIUS_THE_FROST_MONARCH`
- path: `src_custom/permanent_effects/mobius_the_frost_monarch.c`
- L175: up-to-2 targeting uses zone->unk4 as phase flag. 0 = not started, 1+ = at least one target destroyed (re-entered targeting). Upgrade path: bitfield on zone if unk4 is needed for other purposes.

### `PETEN_THE_DARK_CLOWN`
- path: `src_custom/permanent_effects/peten_the_dark_clown.c`
- L73: hand takes priority when both are available; deck is the fallback

### `RAVIEL_LORD_OF_PHANTASMS`
- path: `src_custom/permanent_effects/raviel_lord_of_phantasms.c`
- L137: triggers on any monster placement (Normal + Special). Card text says "Normal Summons" only — needs opts.markSpecialSummon check.

### `REPTILIANNE_GARDNA`
- path: `src_custom/permanent_effects/reptilianne_gardna.c`
- L8: destroyed→search Reptilianne needs destroy-to-GY permanent hook.

### `SPIRIT_OF_THE_POT_OF_GREED`
- path: `src_custom/permanent_effects/spirit_of_the_pot_of_greed.c`
- L11: normal hand summon copies isFaceUp=0; attack-position monsters still count

### `THE_BIG_SATURN`
- path: `src_custom/permanent_effects/the_big_saturn.c`
- L96: custom targeted spells store fixed-row origins in row2.
- L257: GY permanent scan misses some opponent-turn effect destroys (Core pattern).

### `THE_DARK_MAGICIANS`
- path: `src_custom/permanent_effects/the_dark_magicians.c`
- L154: OPT draw on S/T activation needs chain/OPT hooks.
- L177: Deck-first SS order; hand/GY picker not wired.

### `THE_TYRANT_NEPTUNE`
- path: `src_custom/permanent_effects/the_tyrant_neptune.c`
- L59: ram_map byte packing can leave u16 fields at odd EWRAM addresses;
- L451: draw Neptune on the field before popup / trunk picker.

### `THE_WICKED_AVATAR`
- path: `src_custom/permanent_effects/the_wicked_avatar.c`
- L177: after SwitchTurn(), zone POV is still the ended turn until the next UpdateDuelZonePtrs — use gWhoseTurn (new active) not INACTIVE_DUELIST.

### `THUNDER_DRAGON_COLOSSUS`
- path: `src_custom/permanent_effects/thunder_dragon_colossus.c`
- L8: opp search lock + battle/effect destroy→GY-banish need continuous/battle hooks.

### `TIMEAEUS_THE_UNITED_MAGICAL_DRAGON`
- path: `src_custom/permanent_effects/timeaeus_the_united_magical_dragon.c`
- L121: unaffected-after-SS + battle ATK boost need continuous/battle hooks.

### `VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES`
- path: `src_custom/permanent_effects/vennominaga_the_deity_of_poisonous_snakes.c`
- L54: S/T + monster immunity + 3-counter win need continuous/battle hooks.
