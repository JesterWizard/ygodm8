# Partial Effects Backlog

Auto-generated living list of effect files with `ponytail:` or `Ceiling:` notes (implemented, but missing hooks / engine pieces).
Find follow-up work here — stubs live in `STUB_EFFECTS.md`.
Rows vanish when all `ponytail:` / `Ceiling:` comments are removed from the file.
Missing-surface tags: [`PARTIAL_EFFECTS_TAXONOMY.md`](PARTIAL_EFFECTS_TAXONOMY.md). Engine migration: [`effect-data-system.md`](effect-data-system.md).

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials + taxonomy
```

**Last updated:** 2026-07-22 21:19 UTC  
**Remaining partials:** `72`

## Counts by kind

| Kind | Count |
|------|------:|
| `spell` | 5 |
| `trap` | 9 |
| `activated` | 52 |
| `permanent` | 6 |
| **total** | **72** |

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

## activated (52)

### `AMAZONESS_PET_LIGER_KING`
- path: `src_custom/activated_effects/amazoness_pet_liger_king.c`
- L192: * Ceiling: attack redirect FALSE. */

### `AMAZONESS_SPIRITUALIST`
- path: `src_custom/activated_effects/amazoness_spiritualist.c`
- L105: * Ceiling: hand/GY bounce→SS + ED lock need GY/ED hooks. */

### `ANCIENT_GEAR_ENGINEER`
- path: `src_custom/activated_effects/ancient_gear_engineer.c`
- L14: * Ceiling: opp Trap activation negate on attack needs chain gate. */

### `ANCIENT_GEAR_KNIGHT`
- path: `src_custom/activated_effects/ancient_gear_knight.c`
- L13: * Ceiling: Gemini Normal Monster treatment need summon hook. */

### `ANCIENT_GEAR_MEGATON_GOLEM`
- path: `src_custom/activated_effects/ancient_gear_megaton_golem.c`
- L140: Extra Deck Ultimate AG Golem SS blocked — AG Golem from hand/GY/Deck instead.

### `ANDRO_SPHINX`
- path: `src_custom/activated_effects/andro_sphinx.c`
- L64: * Ceiling: GY SS ban needs summon gate. */

### `APPRENTICE_ILLUSION_MAGICIAN`
- path: `src_custom/activated_effects/apprentice_illusion_magician.c`
- L164: * Ceiling: hand/field send +2000 Quick need damage hooks. */

### `ARCANA_FORCE_V_THE_HIEROPHANT`
- path: `src_custom/activated_effects/arcana_force_v_the_hierophant.c`
- L198: discard only; opp cannot respond to Arcana Summons needs turn flag hook.

### `ARCANITE_MAGICIAN`
- path: `src_custom/activated_effects/arcanite_magician.c`
- L160: Synchro +2 Spell Counters + +1000 ATK/counter need synchro/stat hooks. OPT remove 1 unk4 counter → destroy 1 opp (EffectOpt).

### `ARMORY_ARM`
- path: `src_custom/activated_effects/armory_arm.c`
- L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE.

### `AROMAGE_JASMINE`
- path: `src_custom/activated_effects/aromage_jasmine.c`
- L58: * Ceiling: extra Plant Normal Summon needs second NS allowance. */

### `AROMAGE_ROSEMARY`
- path: `src_custom/activated_effects/aromage_rosemary.c`
- L127: LP-higher Plant attack → opp monster effects locked need permanent/battle hooks. LP-gain position change via aroma_lp_gain.c. OPT change 1 face-up battle position (EffectOpt).

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

### `BLUE_EYES_ULTIMATE_SPIRIT_DRAGON`
- path: `src_custom/activated_effects/blue_eyes_ultimate_spirit_dragon.c`
- L25: * Ceiling: Quick field negate + destroy-SS FALSE; GY banish-lock FALSE. */

### `CASTEL_THE_SKY_BLASTER_MUSKETEER`
- path: `src_custom/activated_effects/castel_the_sky_blaster_musketeer.c`
- L138: detach/material + face-down branch need overlay engine. OPT return 1 face-up monster to the Deck.

### `CROSS_KEEPER`
- path: `src_custom/activated_effects/cross_keeper.c`
- L171: Fusion leave ≈ E-HERO Fusion SS while CK in GY; draw1 stand-in for banish→draw2→bottom. Upgrade: true SS trigger + banish cost.

### `CURIOUS_THE_LIGHTSWORN_DOMINION`
- path: `src_custom/activated_effects/curious_the_lightsworn_dominion.c`
- L146: * Ceiling: Link Summon mill + mill-cascade need summon/send hooks.

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

### `DESTINY_HERO_DUSKTOPIA`
- path: `src_custom/activated_effects/destiny_hero_dusktopia.c`
- L47: * TryClearDestinyHeroDusktopiaProtectionEndPhase. Ceiling: Fusion on Summon

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

### `EL_SHADDOLL_MESHAHRAIL`
- path: `src_custom/activated_effects/el_shaddoll_meshahrail.c`
- L76: * Ceiling: unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks. */

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

### `EVIL_HERO_NEOS_LORD`
- path: `src_custom/activated_effects/evil_hero_neos_lord.c`
- L186: * Ceiling: indestructible + opp-GY-sent take-control need continuous/send hooks.

### `GAMECIAL_THE_SEA_TURTLE_KAIJU`
- path: `src_custom/activated_effects/gamecial_the_sea_turtle_kaiju.c`
- L69: * Ceiling: FromHand tribute 1 opp → SS to your field (or free SS if opp has Kaiju). */

### `GORZ_THE_EMISSARY_OF_DARKNESS`
- path: `src_custom/activated_effects/gorz_the_emissary_of_darkness.c`
- L35: * Ceiling: FromHand empty-field SS. */

### `HARPIE_CONDUCTOR`
- path: `src_custom/activated_effects/harpie_conductor.c`
- L133: any other Harpie leave ≈ return-to-hand; upgrade: true bounce-origin flag.
- L231: protect destroy redirect needs destroy-sub hook.

### `HORUS_THE_BLACK_FLAME_DRAGON_LV8`
- path: `src_custom/activated_effects/horus_the_black_flame_dragon_lv8.c`
- L13: * Ceiling: either-turn Spell negate needs chain hook. */

### `JAIN_TWILIGHTSWORN_GENERAL`
- path: `src_custom/activated_effects/jain_twilightsworn_general.c`
- L232: * EP mill 2 via TryApplyTwilightswornEndPhase. Ceiling: other-Lightsworn-

### `LEVEL_EATER`
- path: `src_custom/activated_effects/level_eater.c`
- L123: * Ceiling: SS self from GY; upgrade: TempLevel overlay on target. */
- L179: * Ceiling: cannot-be-Tributed-except-for-Tribute-Summon needs tribute hooks. */

### `LYLA_TWILIGHTSWORN_ENCHANTRESS`
- path: `src_custom/activated_effects/lyla_twilightsworn_enchantress.c`
- L208: * EP mill 3 via TryApplyTwilightswornEndPhase. Ceiling: quick effect on

### `MAGICAL_SCIENTIST`
- path: `src_custom/activated_effects/magical_scientist.c`
- L216: * Ceiling: pay 1000 → SS Lv≤6 Fusion from Extra/recipe list. */

### `MORPHTRONIC_EARFON`
- path: `src_custom/activated_effects/morphtronic_earfon.c`
- L53: real Tuner flag / Equip double-attack need Synchro/equip hooks. OPT PickZone mark unk4 as Tuner stand-in.
- L94: Equip 2-attacks FALSE. On-SS mark self as Tuner (unk4).

### `NIBIRU_THE_PRIMAL_BEING`
- path: `src_custom/activated_effects/nibiru_the_primal_being.c`
- L91: * Ceiling: FromHand wipe+SS if ≥5 face-up monsters on field. */

### `OJAMA_KING`
- path: `src_custom/activated_effects/ojama_king.c`
- L54: PickZone for up to 3 empty zones + continuous lock gate. FirstEmptyZoneInRow today — same as Ground Collapse).

### `RYKO_TWILIGHTSWORN_FIGHTER`
- path: `src_custom/activated_effects/ryko_twilightsworn_fighter.c`
- L204: NS mill 3 stand-in for other-LS effect→mill; upgrade: chain hook.

### `THE_AGENT_OF_JUDGMENT_SATURN`
- path: `src_custom/activated_effects/the_agent_of_judgment_saturn.c`
- L39: /* skip Battle Phase this turn needs phase-lock hook. Ceiling: tribute

### `THE_AGENT_OF_LIFE_NEPTUNE`
- path: `src_custom/activated_effects/the_agent_of_life_neptune.c`
- L161: * Ceiling: FromHand discard self → SS Agent (or Hyperion if Sanctuary). */

### `VISION_HERO_GRAVITO`
- path: `src_custom/activated_effects/vision_hero_gravito.c`
- L65: no RemovedFromPlay_RemoveAt — shift RFP array in place after add. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- L114: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip zone API. OPT add 1 banished HERO monster to hand (EffectOpt; on-summon stand-in).

## permanent (6)

### `EL_SHADDOLL_GRYSTA`
- path: `src_custom/permanent_effects/el_shaddoll_grysta.c`
- L126: negate opp Special Summon + send Shaddoll from hand need SS chain hook.

### `EL_SHADDOLL_SHEKHINAGA`
- path: `src_custom/permanent_effects/el_shaddoll_shekhinaga.c`
- L126: negate SS monster effect + send Shaddoll need effect-chain hook.

### `ELEMENTAL_HERO_FLASH`
- path: `src_custom/permanent_effects/elemental_hero_flash.c`
- L47: no banished-zone + no multi-card GY search yet — banish 3 E-Heroes and add Normal Spell from GY deferred until banish + GY targeting exist. Battle-destruction GY trigger wired above.

### `EVIL_HERO_WILD_CYCLONE`
- path: `src_custom/permanent_effects/evil_hero_wild_cyclone.c`
- L97: * Ceiling: attack S/T lock until end of Damage Step needs chain gate. */

### `HARPIES_PET_PHANTASMAL_DRAGON`
- path: `src_custom/permanent_effects/harpies_pet_phantasmal_dragon.c`
- L9: * Ceiling: Harpie protect + End Phase detach need battle/xyz hooks. */

### `REPTILIANNE_SERVANT`
- path: `src_custom/permanent_effects/reptilianne_servant.c`
- L120: * Ceiling: spell-target destroy needs continuous hook. */
