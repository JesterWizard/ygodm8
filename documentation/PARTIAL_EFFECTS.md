# Partial Effects Backlog

Auto-generated living list of effect files with `ponytail:` or `Ceiling:` notes (implemented, but missing hooks / engine pieces).
Find follow-up work here — stubs live in `STUB_EFFECTS.md`.
Rows vanish when all `ponytail:` / `Ceiling:` comments are removed from the file.
Missing-surface tags: [`PARTIAL_EFFECTS_TAXONOMY.md`](PARTIAL_EFFECTS_TAXONOMY.md). Engine migration: [`effect-data-system.md`](effect-data-system.md).

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials + taxonomy
```

**Last updated:** 2026-07-22 19:39 UTC  
**Remaining partials:** `225`

## Counts by kind

| Kind | Count |
|------|------:|
| `spell` | 6 |
| `trap` | 9 |
| `activated` | 188 |
| `permanent` | 22 |
| **total** | **225** |

## spell (6)

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

### `SPELL_GEAR`
- path: `src_custom/spell_effects/spell_gear.c`
- L156: * Ceiling: optional SS offered as auto-yes when legal; cannot skip

## trap (9)

### `AMAZONESS_HALL`
- path: `src_custom/trap_effects/amazoness_hall.c`
- L43: * Ceiling: Extra Deck / Pendulum place + opp SS gain LP need hooks. */

### `AMAZONESS_HOT_SPRING`
- path: `src_custom/trap_effects/amazoness_hot_spring.c`
- L46: * Ceiling: Pendulum Zone place + battle-damage gain LP OPT need hooks. */

### `ANCIENT_GEAR_DUEL`
- path: `src_custom/trap_effects/ancient_gear_duel.c`
- L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks; mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand-in from Deck/hand.

### `ANGELS_TEAR`
- path: `src_custom/trap_effects/angels_tear.c`
- L342: need 4 banish targets plus 1 summon target.

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

## activated (188)

### `AMAZONESS_PET_LIGER_KING`
- path: `src_custom/activated_effects/amazoness_pet_liger_king.c`
- L192: * Ceiling: attack redirect FALSE. */

### `AMAZONESS_SPIRITUALIST`
- path: `src_custom/activated_effects/amazoness_spiritualist.c`
- L105: * Ceiling: hand/GY bounce→SS + ED lock need GY/ED hooks. */

### `AMULET_DRAGON`
- path: `src_custom/activated_effects/amulet_dragon.c`
- L58: no multi-select GY UI — banish every Spell in both GYs (min.1 gate above).

### `ANCIENT_GEAR_ENGINEER`
- path: `src_custom/activated_effects/ancient_gear_engineer.c`
- L14: * Ceiling: opp Trap activation negate on attack needs chain gate. */

### `ANCIENT_GEAR_GADJILTRON_CHIMERA`
- path: `src_custom/activated_effects/ancient_gear_gadjiltron_chimera.c`
- L13: * Ceiling: not ignition-activatable. */

### `ANCIENT_GEAR_KNIGHT`
- path: `src_custom/activated_effects/ancient_gear_knight.c`
- L13: * Ceiling: Gemini Normal Monster treatment need summon hook. */

### `ANCIENT_GEAR_MEGATON_GOLEM`
- path: `src_custom/activated_effects/ancient_gear_megaton_golem.c`
- L124: * Ceiling: multi-attack + leave-field SS FALSE. */

### `ANDRO_SPHINX`
- path: `src_custom/activated_effects/andro_sphinx.c`
- L64: * Ceiling: GY SS ban needs summon gate. */

### `APPRENTICE_ILLUSION_MAGICIAN`
- path: `src_custom/activated_effects/apprentice_illusion_magician.c`
- L164: * Ceiling: hand/field send +2000 Quick need damage hooks. */

### `ARCANA_FORCE_V_THE_HIEROPHANT`
- path: `src_custom/activated_effects/arcana_force_v_the_hierophant.c`
- L86: discard summon-lock + FromHand paths. OPT coin → SS 1 Arcana Force from Deck.
- L189: discard only; opp cannot respond to Arcana Summons needs turn flag hook.

### `ARCANA_FORCE_XII_THE_HANGMAN`
- path: `src_custom/activated_effects/arcana_force_xii_the_hangman.c`
- L166: coin targeting uses auto-pick highest ATK; upgrade: PickZone.

### `ARCANA_FORCE_XIX_THE_SUN`
- path: `src_custom/activated_effects/arcana_force_xix_the_sun.c`
- L137: requires coin-toss card on field — skipped; SS anytime when legal.

### `ARCANA_FORCE_XV_THE_FIEND`
- path: `src_custom/activated_effects/arcana_force_xv_the_fiend.c`
- L206: discard search + FromHand paths. OPT coin → destroy 1 monster or wipe field.
- L271: on-summon heads auto-picks first destroyable opp monster.

### `ARCANA_KNIGHT_JOKER`
- path: `src_custom/activated_effects/arcana_knight_joker.c`
- L12: discard matching type to negate activation needs chain/response hooks. Ceiling: not ignition-activatable here.

### `ARCANITE_MAGICIAN`
- path: `src_custom/activated_effects/arcanite_magician.c`
- L158: Synchro +2 Spell Counters + +1000 ATK/counter need synchro/stat hooks. OPT remove 1 unk4 counter (if >=1) → destroy 1 opp card.

### `ARMORY_ARM`
- path: `src_custom/activated_effects/armory_arm.c`
- L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE.

### `AROMAGE_JASMINE`
- path: `src_custom/activated_effects/aromage_jasmine.c`
- L58: * Ceiling: extra Plant Normal Summon needs second NS allowance. */

### `AROMAGE_ROSEMARY`
- path: `src_custom/activated_effects/aromage_rosemary.c`
- L125: LP-higher Plant attack → opp monster effects locked need permanent/battle hooks. LP-gain position change via aroma_lp_gain.c. OPT change 1 face-up battle position (ignition).

### `ASH_BLOSSOM_AND_JOYOUS_SPRING`
- path: `src_custom/activated_effects/ash_blossom_and_joyous_spring.c`
- L50: chain negate for add/SS/mill from Deck not wired; upgrade: chain interrupt hook when one exists.

### `ATLANTEAN_DRAGOONS`
- path: `src_custom/activated_effects/atlantean_dragoons.c`
- L137: * Ceiling: sent-for-WATER-effect search needs send hook.

### `ATLANTEAN_HEAVY_INFANTRY`
- path: `src_custom/activated_effects/atlantean_heavy_infantry.c`
- L111: extra Normal Summon Sea Serpent + sent-for-WATER destroy need summon/send hooks. OPT destroy 1 Set Spell/Trap.

### `ATLANTEAN_MARKSMAN`
- path: `src_custom/activated_effects/atlantean_marksman.c`
- L149: * Ceiling: sent-for-WATER destroy Set S/T needs send hook. */

### `BEAST_MACHINE_KING_BARBAROS_UR`
- path: `src_custom/activated_effects/beast_machine_king_barbaros_ur.c`
- L224: multi-zone banish picker not wired; require both types reachable.

### `BLACK_ROSE_DRAGON`
- path: `src_custom/activated_effects/black_rose_dragon.c`
- L158: Synchro Summon destroy-all needs summon hook. OPT banish 1 Plant from GY → opp DEF monster to ATK with 0 ATK (tempStage).

### `BLUE_EYES_JET_DRAGON`
- path: `src_custom/activated_effects/blue_eyes_jet_dragon.c`
- L198: * Ceiling: field OPT bounce 1; FromHand if BEWD field/GY → SS.

### `BLUE_EYES_ULTIMATE_SPIRIT_DRAGON`
- path: `src_custom/activated_effects/blue_eyes_ultimate_spirit_dragon.c`
- L23: Quick field negate + destroy-SS FALSE; GY banish-lock FALSE. OPT +2 tempStage (~+1000) as negate stand-in.

### `BRIONAC_DRAGON_OF_THE_ICE_BARRIER`
- path: `src_custom/activated_effects/brionac_dragon_of_the_ice_barrier.c`
- L232: N-discard path auto-bounces N cards; upgrade: sequential PickZone.

### `CASTEL_THE_SKY_BLASTER_MUSKETEER`
- path: `src_custom/activated_effects/castel_the_sky_blaster_musketeer.c`
- L138: detach/material + face-down branch need overlay engine. OPT return 1 face-up monster to the Deck.

### `CELESTIA_LIGHTSWORN_ANGEL`
- path: `src_custom/activated_effects/celestia_lightsworn_angel.c`
- L140: * Ceiling: field OPT repeat (usage-gated). Auto-destroy up to 2 (no PickZone). */

### `CELESTIAL_KNIGHTLORD_PARSHATH`
- path: `src_custom/activated_effects/celestial_knightlord_parshath.c`
- L104: Link material + GY banish Fairy → SS Fairy need send/banish hooks. OPT discard 1 → add Sanctuary/mention, or Fairy if Sanctuary on field.

### `CHIMERATECH_FORTRESS_DRAGON`
- path: `src_custom/activated_effects/chimeratech_fortress_dragon.c`
- L13: * Ceiling: not field-ignition activatable here. */

### `CHIMERATECH_MEGAFLEET_DRAGON`
- path: `src_custom/activated_effects/chimeratech_megafleet_dragon.c`
- L13: * Ceiling: not field-ignition activatable here. */

### `CLEAR_VICE_DRAGON`
- path: `src_custom/activated_effects/clear_vice_dragon.c`
- L72: * Ceiling: Clear World immunity + discard-to-save need continuous/destruction hooks.
- L73: * Ceiling: not ignition-activatable here. */

### `CORAL_DRAGON`
- path: `src_custom/activated_effects/coral_dragon.c`
- L114: GY draw when Synchro Summoned card sent from field needs GY hook. OPT discard 1 → destroy 1 opp card.

### `CRIMSON_DRAGON`
- path: `src_custom/activated_effects/crimson_dragon.c`
- L123: Extra Deck Synchro SS FALSE; Deck Dragon stand-in.
- L138: on-SS search + Extra Synchro return FALSE. OPT search mentioning Crimson Dragon S/T, else shuffle self → SS Dragon.

### `CROSS_KEEPER`
- path: `src_custom/activated_effects/cross_keeper.c`
- L145: GY draw-on-E-HERO-Fusion need Fusion/GY hooks. Ceiling: send self → SS Elemental HERO or Neo-Spacian from hand/GY.

### `CURIOUS_THE_LIGHTSWORN_DOMINION`
- path: `src_custom/activated_effects/curious_the_lightsworn_dominion.c`
- L146: * Ceiling: Link Summon mill + mill-cascade need summon/send hooks.

### `CYBER_DRAGON_INFINITY`
- path: `src_custom/activated_effects/cyber_dragon_infinity.c`
- L35: ATK summons keep isFaceUp=0 until EOT flip.
- L62: Xyz attach / negate FALSE. Ceiling: ClearZone absorb + +1 tempStage.

### `CYBER_SLASH_HARPIE_LADY`
- path: `src_custom/activated_effects/cyber_slash_harpie_lady.c`
- L196: Quick on S/T activation + Synchro/name hooks missing. OPT bounce 1 opp card or your Harpie to hand.

### `CYBER_SLASH_HARPY_LADY`
- path: `src_custom/activated_effects/cyber_slash_harpy_lady.c`
- L196: Quick on S/T activation + Synchro/name hooks missing. OPT bounce 1 opp card or your Harpie to hand.

### `D_D_WARRIOR`
- path: `src_custom/activated_effects/d_d_warrior.c`
- L13: * battle_effects/d_d_warrior.c. Ceiling: not ignition-activatable here. */

### `DARK_ARMED_DRAGON`
- path: `src_custom/activated_effects/dark_armed_dragon.c`
- L174: allow self-target for faithful TCG simulation; player can choose suboptimally
- L317: auto-target. No GY picker (DeckMenu screen switch corrupts VRAM from inside monster effect handler) and no PickZone cursor state (200 conflicts with game loop after MonsterActionMenu case 4 returns). Picks the best field target via AiPickTarget logic. Upgrade path: dedicated cursor state + A/B handlers like Cannon Soldier.

### `DARK_HORUS`
- path: `src_custom/activated_effects/dark_horus.c`
- L99: after opp Main Phase Spell resolve trigger needs spell hook. OPT SS 1 Lv4 DARK from GY while face-up.

### `DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE`
- path: `src_custom/activated_effects/dark_magician_girl_the_magician_s_apprentice.c`
- L61: name=DMG GY +300 mention FALSE. Ceiling: field OPT add Shining Sarcophagus from Deck.

### `DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE`
- path: `src_custom/activated_effects/dark_magician_girl_the_magicians_apprentice.c`
- L61: name=DMG GY +300 mention FALSE. Ceiling: field OPT add Shining Sarcophagus from Deck.

### `DARK_MAGICIAN_THE_DRAGON_KNIGHT`
- path: `src_custom/activated_effects/dark_magician_the_dragon_knight.c`
- L65: * Ceiling: not ignition-activatable here. */

### `DARK_STRIKE_FIGHTER`
- path: `src_custom/activated_effects/dark_strike_fighter.c`
- L127: Main Phase 1 gate not wired; allow once via usage any main phase.

### `DARKBLAZE_DRAGON`
- path: `src_custom/activated_effects/darkblaze_dragon.c`
- L83: * Ceiling: GY SS double original ATK/DEF needs SS-origin flag. */

### `DARKLORD_DESIRE`
- path: `src_custom/activated_effects/darklord_desire.c`
- L116: Fairy-only Tribute Summon + cannot SS need summon hooks. OPT -1000 ATK (tempStage) → send 1 opp monster to GY.

### `DARKNESS_NEOSPHERE`
- path: `src_custom/activated_effects/darkness_neosphere.c`
- L87: battle indestruct + trap bounce + attack-declare gate need battle/ phase hooks. Ceiling: not field-ignition activatable; SS uses FromHand path.
- L113: opp attack declare gate not wired; require 1 field + 1 hand Fiend.

### `DECOY_DRAGON`
- path: `src_custom/activated_effects/decoy_dragon.c`
- L181: attack-target redirect needs battle targeting hook. OPT SS Lv7+ Dragon from GY once via usage when legal.

### `DEEP_SEA_DIVA`
- path: `src_custom/activated_effects/deep_sea_diva.c`
- L101: /* NS SS via TryDeepSeaDivaOnNormalSummon. Ceiling: OPT duplicate if NS already

### `DESTINY_HERO_CELESTIAL`
- path: `src_custom/activated_effects/destiny_hero_celestial.c`
- L155: * Ceiling: GY draw-if-no-hand need GY hooks.

### `DESTINY_HERO_DARK_ANGEL`
- path: `src_custom/activated_effects/destiny_hero_dark_angel.c`
- L81: field spell-negate FALSE. Ceiling: FromHand discard → SS D-HERO to opp DEF.

### `DESTINY_HERO_DECIDER`
- path: `src_custom/activated_effects/destiny_hero_decider.c`
- L114: /* EP add on NS/SS via TryApplyDestinyHeroDeciderEndPhase. Ceiling: GY quick

### `DESTINY_HERO_DENIER`
- path: `src_custom/activated_effects/destiny_hero_denier.c`
- L189: GY SS when other D-HERO present needs GY/once-per-duel hooks. OPT put 1 D-HERO from Deck/GY/banished on top of Deck.

### `DESTINY_HERO_DESTROY_DOGMA`
- path: `src_custom/activated_effects/destiny_hero_destroy_dogma.c`
- L103: /* Standby burn via TryApplyDestinyHeroDestroyDogmaStandby. Ceiling: Quick
- L104: * destroy/negate FALSE. Ceiling: FromHand banish 3 Warrior/DARK → SS + burn 2000. */

### `DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER`
- path: `src_custom/activated_effects/destiny_hero_destroyer_phoenix_enforcer.c`
- L154: second target picker not chained; auto-destroy best remaining card.
- L227: Quick destroy + GY revive + continuous ATK loss need quick/GY/ permanent hooks. OPT destroy 1 you control + 1 other field card.

### `DESTINY_HERO_DIAMOND_DUDE`
- path: `src_custom/activated_effects/destiny_hero_diamond_dude.c`
- L57: next-turn GY Normal Spell activation needs Main Phase hook.

### `DESTINY_HERO_DISK_COMMANDER`
- path: `src_custom/activated_effects/destiny_hero_disk_commander.c`
- L20: SS-from-GY trigger + once per duel. OPT draw 2 stand-in when on field; upgrade: GY SS dispatch + EFFECT_USAGE_ONCE.

### `DESTINY_HERO_DOMINANCE`
- path: `src_custom/activated_effects/destiny_hero_dominance.c`
- L66: look+reorder UI missing; RandRange shuffle of top N is stand-in.

### `DESTINY_HERO_DREADNOUGHT_MASTER`
- path: `src_custom/activated_effects/destiny_hero_dreadnought_master.c`
- L60: SS trigger → OPT ignition; cards-mentioning-D-HERO FALSE. OPT add up to 2 Destiny HERO from Deck.

### `DESTINY_HERO_DREADNOUGHT_SERVANT`
- path: `src_custom/activated_effects/destiny_hero_dreadnought_servant.c`
- L89: GY banish destroy on Lv8 D-HERO SS FALSE. Ceiling: FromHand if control D-HERO or Field Spell → SS, destroy 1, add Poly.

### `DESTINY_HERO_DREAMER`
- path: `src_custom/activated_effects/destiny_hero_dreamer.c`
- L52: * Ceiling: banish-on-leave need GY hook. Ceiling: GY ignition SS. */

### `DESTINY_HERO_DUSKTOPIA`
- path: `src_custom/activated_effects/destiny_hero_dusktopia.c`
- L47: * TryClearDestinyHeroDusktopiaProtectionEndPhase. Ceiling: Fusion on Summon

### `DESTINY_HERO_DYNATAG`
- path: `src_custom/activated_effects/destiny_hero_dynatag.c`
- L134: GY banish ATK boost not wired; both players 1000 on FromHand.

### `DESTINY_HERO_DYSTOPIA`
- path: `src_custom/activated_effects/destiny_hero_dystopia.c`
- L203: on-SS burn + Quick destroy-if-ATK-changed need summon/ATK hooks. OPT pick Lv≤4 D-HERO in GY → burn its ATK.

### `DESTINY_HERO_MALICIOUS`
- path: `src_custom/activated_effects/destiny_hero_malicious.c`
- L43: GY ignition needs GY-menu wire. Ceiling: allow when Malicious in GY + another in Deck (callable if gMonEffect set to Malicious).

### `DESTINY_HERO_PLASMA`
- path: `src_custom/activated_effects/destiny_hero_plasma.c`
- L95: equip/absorb + half-ATK boost + continuous opp negate need equip hooks. Ceiling: destroy 1 opp monster.

### `DIVINE_SERPENT_GEH`
- path: `src_custom/activated_effects/divine_serpent_geh.c`
- L41: * Ceiling: destroy gate + battle negate need destroy/battle hooks.
- L42: * Ceiling: field ignition FALSE. */

### `DIVINER_OF_THE_HERALD`
- path: `src_custom/activated_effects/diviner_of_the_herald.c`
- L89: on-NS/SS mill + tribute SS Fairy need summon/tribute hooks. OPT send 1 Fairy from Deck to GY (+unkTwo Level stand-in until EP clear).

### `EBON_ILLUSION_MAGICIAN`
- path: `src_custom/activated_effects/ebon_illusion_magician.c`
- L78: Xyz detach cost + attack-banish FALSE. OPT SS Spellcaster Normal from hand/Deck (detach stand-in).

### `EL_SHADDOLL_MESHAHRAIL`
- path: `src_custom/activated_effects/el_shaddoll_meshahrail.c`
- L74: unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks. OPT pay 800 → add 1 Shaddoll or Void S/T from Deck.

### `EL_SHADDOLL_WENDIGO`
- path: `src_custom/activated_effects/el_shaddoll_wendigo.c`
- L110: * Ceiling: GY add Shaddoll S/T on send not wired. */

### `ELDER_ENTITY_NORDEN`
- path: `src_custom/activated_effects/elder_entity_norden.c`
- L167: * Ceiling: SS-trigger timing needs summon hook.

### `ELEMENTAL_HERO_CHAOS_NEOS`
- path: `src_custom/activated_effects/elemental_hero_chaos_neos.c`
- L241: 3H Set-all needs set-from-deck hook; 2H/3H both shuffle all.

### `ELEMENTAL_HERO_DARK_NEOS`
- path: `src_custom/activated_effects/elemental_hero_dark_neos.c`
- L92: /* EP Extra return via TryReturnContactFusionsAtEndPhase. Ceiling: contact Fusion need fusion hook. */

### `ELEMENTAL_HERO_SHINING_NEOS_WINGMAN`
- path: `src_custom/activated_effects/elemental_hero_shining_neos_wingman.c`
- L150: GY ATK gain + effect destroy immunity + battle burn need permanent/ battle hooks. OPT destroy opp cards up to different Attributes.
- L177: multi-target picker not wired; auto-destroy highest-value opp cards.

### `ELEMENTAL_HERO_SPIRIT_OF_NEOS`
- path: `src_custom/activated_effects/elemental_hero_spirit_of_neos.c`
- L154: attack-hand SS FALSE. OPT search Poly/E-HERO S/T, else OPT shuffle self → SS Normal E-HERO from Deck.

### `EVIL_HERO_ADUSTED_GOLD`
- path: `src_custom/activated_effects/evil_hero_adusted_gold.c`
- L63: cannot attack without Fusion Monster needs attack gate. Not field-ignition activatable; discard search uses FromHand path.
- L86: once-per-turn not tracked without turn hook.

### `EVIL_HERO_DEAD_END_PRISON`
- path: `src_custom/activated_effects/evil_hero_dead_end_prison.c`
- L109: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE. OPT mill 1 HERO from Deck.
- L151: Dark Fusion Fusion markers missing; any Fusion Monster stand-in.

### `EVIL_HERO_INFERNAL_RIDER`
- path: `src_custom/activated_effects/evil_hero_infernal_rider.c`
- L228: on-summon + HERO lock need summon/SS gates. OPT add Dark Fusion Deck/GY, else OPT banish self+4 GY → Set Super Poly.

### `EVIL_HERO_MALICIOUS_BANE`
- path: `src_custom/activated_effects/evil_hero_malicious_bane.c`
- L75: destruction immunity + HERO-only attack gate need destroy/attack hooks. OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4.
- L105: +200 ATK each via tempStage (~500/unit); attack lock only marks self unk4.

### `EVIL_HERO_NEOS_LORD`
- path: `src_custom/activated_effects/evil_hero_neos_lord.c`
- L144: indestructible + on-SS/opp-GY-sent take-control triggers need continuous/summon hooks; OPT take control of 1 face-up opp monster.

### `EVIL_HERO_SINISTER_NECROM`
- path: `src_custom/activated_effects/evil_hero_sinister_necrom.c`
- L103: GY ignition needs GY-menu wire; allow when Sinister Necrom in GY + Evil HERO in hand or Deck (callable if gMonEffect set).

### `EVIL_HERO_TOXIC_BUBBLE`
- path: `src_custom/activated_effects/evil_hero_toxic_bubble.c`
- L16: on-SS draw when Dark Fusion Fusion up needs summon hook. Not field-ignition activatable; SS-from-hand uses FromHand path.
- L39: HERO-only SS lock + once-per-turn not tracked without turn hook.

### `EVIL_HERO_VICIOUS_CLAWS`
- path: `src_custom/activated_effects/evil_hero_vicious_claws.c`
- L121: once-per-duel ≈ EffectOpt (turn); upgrade: duel-scoped latch.

### `EVOLZAR_DOLKKA`
- path: `src_custom/activated_effects/evolzar_dolkka.c`
- L13: * Ceiling: not field-ignition here. */

### `FELIS_LIGHTSWORN_ARCHER`
- path: `src_custom/activated_effects/felis_lightsworn_archer.c`
- L102: * hook. Ceiling: ignition tribute self → destroy 1 opponent monster → mill 3. */

### `FLAME_RULER`
- path: `src_custom/activated_effects/flame_ruler.c`
- L12: treat as 2 Tributes for FIRE Tribute Summon needs tribute-cost LynJump. gate outside this file.

### `FOG_KING`
- path: `src_custom/activated_effects/fog_king.c`
- L13: * lock need summon/tribute continuous hooks. Ceiling: not field-ignition here. */

### `FUSILIER_DRAGON_THE_DUAL_MODE_BEAST`
- path: `src_custom/activated_effects/fusilier_dragon_the_dual_mode_beast.c`
- L13: * Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon

### `GAGAGIGO_THE_RISEN`
- path: `src_custom/activated_effects/gagagigo_the_risen.c`
- L12: Gagagigo the Risen has no printed monster effect (Xyz materials only). duel gate outside activated_effects.

### `GAMECIAL_THE_SEA_TURTLE_KAIJU`
- path: `src_custom/activated_effects/gamecial_the_sea_turtle_kaiju.c`
- L69: * Ceiling: FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju). */

### `GLADIATOR_BEAST_GYZARUS`
- path: `src_custom/activated_effects/gladiator_beast_gyzarus.c`
- L175: * Ceiling: Contact Fusion SS destroy trigger + Extra Deck return. */

### `GLADIATOR_BEAST_HERAKLINOS`
- path: `src_custom/activated_effects/gladiator_beast_heraklinos.c`
- L148: either-turn chain negate needs chain hook. OPT discard 1 → destroy 1 opponent card below.

### `GODDESS_BOW`
- path: `src_custom/activated_effects/goddess_bow.c`
- L13: * fusion/equip/chain hooks. Ceiling: not ignition-activatable here. */

### `GORZ_THE_EMISSARY_OF_DARKNESS`
- path: `src_custom/activated_effects/gorz_the_emissary_of_darkness.c`
- L35: * Ceiling: FromHand empty-field SS. */

### `GRANMARG_THE_ROCK_MONARCH`
- path: `src_custom/activated_effects/granmarg_the_rock_monarch.c`
- L159: * Ceiling: once via usage if Set target. */

### `GRAVEKEEPERS_CURSE`
- path: `src_custom/activated_effects/gravekeepers_curse.c`
- L20: /* printed is If Summoned trigger. Ceiling: allow once via usage

### `GRAVEKEEPERS_SPIRITUALIST`
- path: `src_custom/activated_effects/gravekeepers_spiritualist.c`
- L13: * summon API. Ceiling: not ignition-activatable here. */

### `GRAVEKEEPERS_VASSAL`
- path: `src_custom/activated_effects/gravekeepers_vassal.c`
- L13: * Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle

### `GRAVEKEEPERS_WATCHER`
- path: `src_custom/activated_effects/gravekeepers_watcher.c`
- L16: * hooks. Ceiling: not field-ignition; discard-from-hand path below. */

### `GREAT_POSEIDON_BEETLE`
- path: `src_custom/activated_effects/great_poseidon_beetle.c`
- L13: * re-attack hook. Ceiling: not ignition-activatable here. */

### `GREEN_GADGET`
- path: `src_custom/activated_effects/green_gadget.c`
- L62: once via usage.

### `HARPIE_CONDUCTOR`
- path: `src_custom/activated_effects/harpie_conductor.c`
- L100: * Ceiling: protect destroy redirect + on-Harpie-return trigger need hooks. */

### `HARPIE_HARPIST`
- path: `src_custom/activated_effects/harpie_harpist.c`
- L124: NS trigger + GY End Phase search need separate hooks. OPT bounce own WB + opp face-up, else OPT add Harpie from Deck.

### `HERALD_OF_PERFECTION`
- path: `src_custom/activated_effects/herald_of_perfection.c`
- L13: * Ceiling: not field-ignition activatable here; upgrade: either-turn chain

### `HERALD_OF_THE_ARC_LIGHT`
- path: `src_custom/activated_effects/herald_of_the_arc_light.c`
- L13: * Ceiling: not field-ignition activatable here; upgrade: continuous banish +

### `HERALD_OF_ULIMATENESS`
- path: `src_custom/activated_effects/herald_of_ulimateness.c`
- L13: * Ceiling: not field-ignition activatable here; upgrade: either-turn chain

### `HERALD_OF_ULTIMATENESS`
- path: `src_custom/activated_effects/herald_of_ultimateness.c`
- L13: * Ceiling: not field-ignition activatable here; upgrade: either-turn chain

### `HOLACTIE_THE_CREATOR_OF_LIGHT`
- path: `src_custom/activated_effects/holactie_the_creator_of_light.c`
- L65: * Ceiling: not field-ignition activatable; use FromHand tribute path. */

### `HONEST`
- path: `src_custom/activated_effects/honest.c`
- L95: /* Damage Step hand discard uses FromHand path. Ceiling: Main Phase

### `HORUS_THE_BLACK_FLAME_DRAGON_LV8`
- path: `src_custom/activated_effects/horus_the_black_flame_dragon_lv8.c`
- L13: * Ceiling: either-turn Spell negate needs chain hook. */

### `ILLUSION_OF_CHAOS`
- path: `src_custom/activated_effects/illusion_of_chaos.c`
- L135: /* field bounce→SS DM negate FALSE. Ceiling: FromHand search only. */

### `JAIN_TWILIGHTSWORN_GENERAL`
- path: `src_custom/activated_effects/jain_twilightsworn_general.c`
- L229: other-Lightsworn-activated mill 2 needs chain hook. OPT banish 1 Lightsworn from hand/GY → weaken 1 face-up monster. EP mill 2 via TryApplyTwilightswornEndPhase.

### `JUDGMENT_THE_DRAGON_OF_HEAVEN`
- path: `src_custom/activated_effects/judgment_the_dragon_of_heaven.c`
- L108: * TryApplyJudgmentEndPhase. Ceiling: pay half LP → destroy all other field cards. */

### `JUNK_SYNCHRON`
- path: `src_custom/activated_effects/junk_synchron.c`
- L124: * Ceiling: field OPT repeat (usage-gated below). */

### `LEKUNGA`
- path: `src_custom/activated_effects/lekunga.c`
- L13: * Ceiling: wrong Type/Attribute/stats (Fairy/LIGHT 0/0 vs Plant/WATER 700/700);

### `LEVEL_EATER`
- path: `src_custom/activated_effects/level_eater.c`
- L122: * Ceiling: SS self from GY; upgrade: TempLevel overlay on target. */
- L178: * GY-menu + tribute hooks. Ceiling: GY ignition when Lv5+ you control + empty

### `LEVIAIR_THE_SEA_DRAGON`
- path: `src_custom/activated_effects/leviair_the_sea_dragon.c`
- L63: * Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt. */
- L108: * Ceiling: materials not checked; upgrade: overlay detach before SS. */

### `LIGHTSWORN_DRAGONLING`
- path: `src_custom/activated_effects/lightsworn_dragonling.c`
- L134: /* hand SS when Lightsworn in GY uses FromHand path. Ceiling: field

### `LUMINA_TWILIGHTSWORN_SHAMAN`
- path: `src_custom/activated_effects/lumina_twilightsworn_shaman.c`
- L226: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.

### `LYLA_TWILIGHTSWORN_ENCHANTRESS`
- path: `src_custom/activated_effects/lyla_twilightsworn_enchantress.c`
- L205: quick effect on Spell/Trap activation + mill 3 when other LS activates need chain hooks. OPT banish LS from hand/GY then destroy 1 face-up Spell/Trap. EP mill 3 via TryApplyTwilightswornEndPhase.

### `MAGICAL_PLANT_MANDRAGOLA`
- path: `src_custom/activated_effects/magical_plant_mandragola.c`
- L13: * Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon

### `MAGICAL_SCIENTIST`
- path: `src_custom/activated_effects/magical_scientist.c`
- L216: * Ceiling: pay 1000 → SS Lv≤6 Fusion from Extra/recipe list. */

### `MAGICIANS_ROBE`
- path: `src_custom/activated_effects/magicians_robe.c`
- L57: * Ceiling: discard S/T from hand → SS DM from Deck via FromHand path. */

### `MAN_THRO_TRO`
- path: `src_custom/activated_effects/man_thro_tro.c`
- L21: Ojama Trio monster form is the only token-like field unit today

### `MANJU_OF_THE_TEN_THOUSAND_HANDS`
- path: `src_custom/activated_effects/manju_of_the_ten_thousand_hands.c`
- L113: once via usage if Ritual Monster or Ritual Spell in Deck and hand space.

### `MEZUKI`
- path: `src_custom/activated_effects/mezuki.c`
- L169: /* GY ignition needs GY-menu wire. Ceiling: allow when Mezuki +

### `MICHAEL_THE_ARCH_LIGHTSWORN`
- path: `src_custom/activated_effects/michael_the_arch_lightsworn.c`
- L140: * Ceiling: pay 1000 LP → banish 1 field card. */

### `MINERVA_LIGHTSWORN_MAIDEN`
- path: `src_custom/activated_effects/minerva_lightsworn_maiden.c`
- L125: * Ceiling: field OPT search LIGHT Dragon Lv≤ distinct LS names in GY. */

### `MIRROR_FORCE_DRAGON`
- path: `src_custom/activated_effects/mirror_force_dragon.c`
- L13: * Ceiling: not ignition-activatable here; upgrade: trigger destroy-all. */

### `MOLTEN_ZOMBIE`
- path: `src_custom/activated_effects/molten_zombie.c`
- L18: printed trigger is SS from GY; once via usage when Activate runs (summon-dispatch or manual).

### `MORPHTRONIC_CELFON`
- path: `src_custom/activated_effects/morphtronic_celfon.c`
- L136: reveal/look UI missing; die roll + SS/add among top N. Ceiling: ATK OPT die→SS Lv≤4 Morphtronic; DEF OPT die→add Morphtronic.

### `MORPHTRONIC_EARFON`
- path: `src_custom/activated_effects/morphtronic_earfon.c`
- L48: real Tuner flag / Equip double-attack need Synchro/equip hooks. OPT PickZone mark unk4 as Tuner stand-in.
- L95: on-SS Tuner mark + Equip 2-attacks FALSE. OPT PickZone treat face-up as Tuner (unk4).

### `MORPHTRONIC_LANTRON`
- path: `src_custom/activated_effects/morphtronic_lantron.c`
- L98: * Ceiling: ATK effect-damage redirect needs effect-damage hook. */

### `MORPHTRONIC_REMOTEN`
- path: `src_custom/activated_effects/morphtronic_remoten.c`
- L213: position-gated OPT search. ATK: banish GY Morphtronic → add same Lv. DEF: discard Morphtronic → add other same Lv.

### `MORPHTRONIC_SCANNEN`
- path: `src_custom/activated_effects/morphtronic_scannen.c`
- L194: FromHand banish Morphtronic → SS; ATK/DEF OPT search modes.

### `MORPHTRONIC_SCOPEN`
- path: `src_custom/activated_effects/morphtronic_scopen.c`
- L58: DEF Position → treat as Level 4 + EP destroy on ATK-mode SS need position/EP hooks; ATK Position OPT SS 1 Lv4 Morphtronic from hand.

### `MORPHTRONIC_SLINGEN`
- path: `src_custom/activated_effects/morphtronic_slingen.c`
- L160: DEF destroy-other-Morphtronic substitute needs destroy redirect hook. Ceiling: ATK OPT tribute 1 other Morphtronic → destroy 1 field card.

### `MORPHTRONIC_SMARTFON`
- path: `src_custom/activated_effects/morphtronic_smartfon.c`
- L228: reveal UI FALSE; ATK die excavate add; DEF GY add Morphtronic. FromHand: banish Morphtronic GY → SS.

### `MORPHTRONIC_TELEFON`
- path: `src_custom/activated_effects/morphtronic_telefon.c`
- L176: reveal UI FALSE; ATK die→LP+SS Morph Lv≤roll; DEF die excavate add.

### `MORPHTRONIC_VACUUMEN`
- path: `src_custom/activated_effects/morphtronic_vacuumen.c`
- L24: send Equip → burn + DEF equip-take-control need equip hooks. Ceiling: ATK Position OPT burn 500.

### `NATURIA_BEAST`
- path: `src_custom/activated_effects/naturia_beast.c`
- L13: * Ceiling: not ignition-activatable here; upgrade: either-turn interrupt. */

### `NEO_SPACIAN_DARK_PANTHER`
- path: `src_custom/activated_effects/neo_spacian_dark_panther.c`
- L13: * Ceiling: not ignition-activatable here; upgrade: permanent/name/effect copy. */

### `NIBIRU_THE_PRIMAL_BEING`
- path: `src_custom/activated_effects/nibiru_the_primal_being.c`
- L91: * Ceiling: FromHand wipe+SS if ≥5 face-up monsters on field. */

### `NUMBER_39_UTOPIA`
- path: `src_custom/activated_effects/number_39_utopia.c`
- L13: * hook and XYZ material system. Ceiling: not field-ignition activatable. */

### `OJAMA_KING`
- path: `src_custom/activated_effects/ojama_king.c`
- L54: PickZone for up to 3 empty zones + continuous lock gate. FirstEmptyZoneInRow today — same as Ground Collapse).

### `POSEIDRA_THE_ATLANTEAN_DRAGON`
- path: `src_custom/activated_effects/poseidra_the_atlantean_dragon.c`
- L284: /* hand SS uses FromHand path. Ceiling: GY ignition like Malicious. */

### `PREDAPLANT_VERTE_ANACONDA`
- path: `src_custom/activated_effects/predaplant_verte_anaconda.c`
- L130: * hooks. Ceiling: pay 2000 LP → destroy 1 field card. */

### `PUNISHMENT_DRAGON`
- path: `src_custom/activated_effects/punishment_dragon.c`
- L192: * effect-activation hook. Ceiling: pay 1000 → shuffle all banished into Decks. */

### `QUINTET_MAGICIAN`
- path: `src_custom/activated_effects/quintet_magician.c`
- L65: * fusion/summon hooks. Ceiling: once via usage destroy all opp cards. */

### `RAIDEN_HAND_OF_THE_LIGHTSWORN`
- path: `src_custom/activated_effects/raiden_hand_of_the_lightsworn.c`
- L61: /* EP mill via TryApplyRaidenEndPhase. Ceiling: Main Phase OPT mill 2. */

### `REPTILIANNE_LAMIA`
- path: `src_custom/activated_effects/reptilianne_lamia.c`
- L98: * Ceiling: not field-ignition; FromHand ATK-0 + SS + self-damage. */

### `RINYAN_LIGHTSWORN_ROGUE`
- path: `src_custom/activated_effects/rinyan_lightsworn_rogue.c`
- L41: /* FLIP trigger needs flip hook. Ceiling: once via usage if LS in GY. */

### `ROAD_SYNCHRON`
- path: `src_custom/activated_effects/road_synchron.c`
- L13: * synchro/battle hooks. Ceiling: not ignition-activatable here. */

### `ROYAL_MAGICAL_LIBRARY`
- path: `src_custom/activated_effects/royal_magical_library.c`
- L23: * Ceiling: ignition only when unk4>=3. */

### `RYKO_LIGHTSWORN_HUNTER`
- path: `src_custom/activated_effects/ryko_lightsworn_hunter.c`
- L107: /* FLIP trigger needs flip hook. Ceiling: once via usage. */

### `RYKO_TWILIGHTSWORN_FIGHTER`
- path: `src_custom/activated_effects/ryko_twilightsworn_fighter.c`
- L191: NS/flip + other-Lightsworn mill 3 need summon/chain hooks. OPT banish LS from hand/GY then banish 1 field card; EP mill 3 via TryApplyTwilightswornEndPhase.

### `SHADDOLL_DRAGON`
- path: `src_custom/activated_effects/shaddoll_dragon.c`
- L183: /* FLIP vs GY-sent exclusivity + trigger hooks deferred. Ceiling: bounce 1

### `SHADDOLL_SQUAMATA`
- path: `src_custom/activated_effects/shaddoll_squamata.c`
- L155: * Ceiling: destroy 1 opp monster OR mill 1 Shaddoll from Deck once via usage. */

### `SILENT_SWORDSMAN_ZERO`
- path: `src_custom/activated_effects/silent_swordsman_zero.c`
- L47: * tempStage unchanged. Ceiling: Sarcophagus negate needs chain hook. */

### `SKILLED_DARK_MAGICIAN`
- path: `src_custom/activated_effects/skilled_dark_magician.c`
- L81: * Ceiling: ignition when unk4>=3. */

### `SKILLED_WHITE_MAGICIAN`
- path: `src_custom/activated_effects/skilled_white_magician.c`
- L81: * Ceiling: ignition when unk4>=3. */

### `SOUL_ABSORBING_BONE_TOWER`
- path: `src_custom/activated_effects/soul_absorbing_bone_tower.c`
- L13: * SS need continuous/SS hooks. Ceiling: not ignition-activatable here. */

### `STARDUST_DRAGON`
- path: `src_custom/activated_effects/stardust_dragon.c`
- L13: * and EP hooks. Ceiling: not ignition-activatable here. */

### `T_G_HYPER_LIBRARIAN`
- path: `src_custom/activated_effects/t_g_hyper_librarian.c`
- L13: * Ceiling: not ignition-activatable here; upgrade: synchro summon gate. */

### `TATSUNOKO`
- path: `src_custom/activated_effects/tatsunoko.c`
- L13: * synchro/summon continuous hooks. Ceiling: not field-ignition here. */

### `THE_AGENT_OF_JUDGMENT_SATURN`
- path: `src_custom/activated_effects/the_agent_of_judgment_saturn.c`
- L39: /* skip Battle Phase this turn needs phase-lock hook. Ceiling: tribute

### `THE_AGENT_OF_LIFE_NEPTUNE`
- path: `src_custom/activated_effects/the_agent_of_life_neptune.c`
- L161: * Ceiling: FromHand discard self → SS Agent (or Hyperion if Sanctuary). */

### `THE_AGENT_OF_WISDOM_MERCURY`
- path: `src_custom/activated_effects/the_agent_of_wisdom_mercury.c`
- L21: * Ceiling: once via usage if hand empty; upgrade: standby/end-phase gate. */

### `THESTALOS_THE_FIRESTORM_MONARCH`
- path: `src_custom/activated_effects/thestalos_the_firestorm_monarch.c`
- L111: * Ceiling: field OPT repeat (usage-gated below). */

### `THUNDER_END_DRAGON`
- path: `src_custom/activated_effects/thunder_end_dragon.c`
- L60: * Ceiling: materials not checked; upgrade: overlay detach before destroy. */

### `TIME_MAGIC_HAMMER`
- path: `src_custom/activated_effects/time_magic_hammer.c`
- L13: * Ceiling: not field-ignition activatable here. */

### `TIMEAUS_THE_UNITED_DRAGON`
- path: `src_custom/activated_effects/timeaus_the_united_dragon.c`
- L148: * Ceiling: SS from hand via send cost uses FromHand path. */

### `TORNADO_BIRD`
- path: `src_custom/activated_effects/tornado_bird.c`
- L85: /* FLIP trigger needs flip hook. Ceiling: once via usage. */

### `TRISHULA_DRAGON_OF_THE_ICE_BARRIER`
- path: `src_custom/activated_effects/trishula_dragon_of_the_ice_barrier.c`
- L114: /* Synchro Summon trigger needs synchro hook. Ceiling: once via usage banish

### `TUNINGWARE`
- path: `src_custom/activated_effects/tuningware.c`
- L13: * Ceiling: not ignition-activatable here; upgrade: synchro summon gate. */

### `TURBO_SYNCHRON`
- path: `src_custom/activated_effects/turbo_synchron.c`
- L13: * hooks. Ceiling: not ignition-activatable here. */

### `TYRANT_BURST_DRAGON`
- path: `src_custom/activated_effects/tyrant_burst_dragon.c`
- L13: * Ceiling: not ignition-activatable here; upgrade: permanent battle/equip gate. */

### `ULTIMATE_OBEDIENT_FIEND`
- path: `src_custom/activated_effects/ultimate_obedient_fiend.c`
- L13: * Ceiling: not field-ignition activatable here. */

### `ULTIMATE_TYRANNO`
- path: `src_custom/activated_effects/ultimate_tyranno.c`
- L13: * Ceiling: not field-ignition activatable here. */

### `VISION_HERO_FARIS`
- path: `src_custom/activated_effects/vision_hero_faris.c`
- L148: Continuous Trap place + ED HERO lock need place/ED hooks. OPT add 1 Vision HERO from Deck to hand wired below.

### `VISION_HERO_GRAVITO`
- path: `src_custom/activated_effects/vision_hero_gravito.c`
- L64: no RemovedFromPlay_RemoveAt — shift RFP array in place after add. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- L113: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip zone API. OPT add 1 banished HERO monster to hand.

### `VISION_HERO_INCREASE`
- path: `src_custom/activated_effects/vision_hero_increase.c`
- L69: GY Continuous Trap place + tribute HERO SS-self FALSE. OPT SS Vision HERO Lv≤4 from Deck (ST-zone SS stand-in).

### `WEISS_LIGHTSWORN_ARCHFIEND`
- path: `src_custom/activated_effects/weiss_lightsworn_archfiend.c`
- L167: /* sent-from-Deck-to-GY trigger needs mill/send hook. Ceiling: field OPT

### `YAMORIMORI`
- path: `src_custom/activated_effects/yamorimori.c`
- L124: /* GY ignition needs GY-menu wire. Ceiling: banish self from GY +

## permanent (22)

### `ARCANA_FORCE_EX_THE_LIGHT_RULER`
- path: `src_custom/permanent_effects/arcana_force_ex_the_light_ruler.c`
- L100: Tails negate FALSE; Heads only when GY→hand legal.

### `ARCANA_FORCE_I_THE_MAGICIAN`
- path: `src_custom/permanent_effects/arcana_force_i_the_magician.c`
- L68: spell-trigger heads/tails not wired.

### `ARCANA_FORCE_III_THE_EMPRESS`
- path: `src_custom/permanent_effects/arcana_force_iii_the_empress.c`
- L48: opp Normal Summon SS/discard triggers need summon hooks; unk4 only.

### `ARCANA_FORCE_VI_THE_LOVERS`
- path: `src_custom/permanent_effects/arcana_force_vi_the_lovers.c`
- L48: tribute engine not wired — unk4 marks double-tribute / no-tribute only.

### `ARCANA_FORCE_XVIII_THE_MOON`
- path: `src_custom/permanent_effects/arcana_force_xviii_the_moon.c`
- L48: Standby Moon Token / End Phase give-control need turn hooks; unk4 only.

### `ARCANA_FORCE_XXI_THE_WORLD`
- path: `src_custom/permanent_effects/arcana_force_xxi_the_world.c`
- L48: skip-turn / opp GY-to-hand need turn hooks; unk4 marks coin only.

### `DARK_MAGICIAN_OF_DESTRUCTION`
- path: `src_custom/permanent_effects/dark_magician_of_destruction.c`
- L131: deck-first add; DM preferred by scan order, no picker.

### `DESTINY_HERO_DOOM_OVERLORD`
- path: `src_custom/permanent_effects/destiny_hero_doom_overlord.c`
- L327: banish-until-Standby = permanent banish; DARK HERO SS lock not wired.

### `DESTINY_HERO_DRAWHAND`
- path: `src_custom/permanent_effects/destiny_hero_drawhand.c`
- L140: HERO-effect SS gate not checked.

### `DESTINY_HERO_DREAD_SERVANT`
- path: `src_custom/permanent_effects/destiny_hero_dread_servant.c`
- L77: * Ceiling: NS Clock Tower counters need summon hook. */

### `DESTINY_HERO_DREADMASTER`
- path: `src_custom/permanent_effects/destiny_hero_dreadmaster.c`
- L284: Clock Tower Prison gate skipped. D-HERO battle protect + no BD via DestinyHeroDreadmaster_* while face-up.

### `EL_SHADDOLL_GRYSTA`
- path: `src_custom/permanent_effects/el_shaddoll_grysta.c`
- L126: negate opp Special Summon + send Shaddoll from hand need SS chain hook.

### `EL_SHADDOLL_SHEKHINAGA`
- path: `src_custom/permanent_effects/el_shaddoll_shekhinaga.c`
- L126: negate SS monster effect + send Shaddoll need effect-chain hook.

### `ELEMENTAL_HERO_ELECTRUM`
- path: `src_custom/permanent_effects/elemental_hero_electrum.c`
- L67: no removed-from-play zone yet — shuffle banished/exiled monsters back into each owner's deck once Duel_BanishZone exists. ATK overlay via ElementalHeroElectrum_ApplyDynamicZoneStats.

### `ELEMENTAL_HERO_FLASH`
- path: `src_custom/permanent_effects/elemental_hero_flash.c`
- L47: no banished-zone + no multi-card GY search yet — banish 3 E-Heroes and add Normal Spell from GY deferred until banish + GY targeting exist. Battle-destruction GY trigger wired above.

### `ELEMENTAL_HERO_THE_SHINING`
- path: `src_custom/permanent_effects/elemental_hero_the_shining.c`
- L64: return up to 2 banished E-HEROes to hand deferred — no multi-RFP return UI yet. ATK overlay via ElementalHeroTheShining_ApplyDynamicZoneStats.

### `EVIL_HERO_INFERNO_WING_BACKFIRE`
- path: `src_custom/permanent_effects/evil_hero_inferno_wing_backfire.c`
- L155: true trigger is Special Summon; on-summon stand-in covers SS path.

### `EVIL_HERO_WILD_CYCLONE`
- path: `src_custom/permanent_effects/evil_hero_wild_cyclone.c`
- L97: * Ceiling: attack S/T lock until end of Damage Step needs chain gate. */

### `GLADIATOR_BEAST_ESSEDARII`
- path: `src_custom/permanent_effects/gladiator_beast_essedarii.c`
- L8: Contact Fusion has no permanent ignition path.

### `HARPIES_PET_PHANTASMAL_DRAGON`
- path: `src_custom/permanent_effects/harpies_pet_phantasmal_dragon.c`
- L9: * Ceiling: Harpie protect + End Phase detach need battle/xyz hooks. */

### `HERO_KID`
- path: `src_custom/permanent_effects/hero_kid.c`
- L76: true trigger is Special Summon of Level 4 or lower HERO.

### `REPTILIANNE_SERVANT`
- path: `src_custom/permanent_effects/reptilianne_servant.c`
- L120: * Ceiling: spell-target destroy needs continuous hook. */
