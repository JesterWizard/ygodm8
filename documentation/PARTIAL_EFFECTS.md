# Partial Effects Backlog

Auto-generated living list of effect files with `ponytail:` ceilings (implemented, but missing hooks / engine pieces).
Find follow-up work here — stubs live in `STUB_EFFECTS.md`.
Rows vanish when all `ponytail:` comments are removed from the file.
Missing-surface tags: [`PARTIAL_EFFECTS_TAXONOMY.md`](PARTIAL_EFFECTS_TAXONOMY.md). Engine migration: [`effect-data-system.md`](effect-data-system.md).

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials + taxonomy
```

**Last updated:** 2026-07-21 22:39 UTC  
**Remaining partials:** `726`

## Counts by kind

| Kind | Count |
|------|------:|
| `spell` | 72 |
| `trap` | 88 |
| `activated` | 452 |
| `permanent` | 114 |
| **total** | **726** |

## spell (72)

### `ANCIENT_GEAR_FACTORY`
- path: `src_custom/spell_effects/ancient_gear_factory.c`
- L237: no multi-select GY UI — auto-pick an exact Level-sum mask. Ceiling: no player choice among valid GY sets; upgrade: DeckMenu multi-pick until sum == 2× revealed Level.

### `ARCANA_READING`
- path: `src_custom/spell_effects/arcana_reading.c`
- L142: no dedicated choice UI — A = Heads, B = Tails. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.

### `ARCANA_SPREAD`
- path: `src_custom/spell_effects/arcana_spread.c`
- L232: no dedicated choice UI — A = Heads, B = Tails. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.

### `AROMA_BLEND`
- path: `src_custom/spell_effects/aroma_blend.c`
- L291: GY effect (banish this → Fusion Summon Plant Fusion by banishing materials from hand/field, and GY Plants if LP higher) needs a GY-activate path + Plant Fusion recipe filter outside this file. Ceiling: discard + place Humid/Dried/Blessed Winds face-up only; upgrade: GY activate AROMA_BLEND → banish self → FusionDuel Plant Fusion pay
- L298: placed Winds are face-up/locked but their continuous trap effects are not auto-wired (trap stubs). Ceiling: card sits face-up; upgrade: call each Winds activate body after place, or wire trap dispatcher.

### `BOND_BETWEEN_TEACHER_AND_STUDENT`
- path: `src_custom/spell_effects/bond_between_teacher_and_student.c`
- L28: Dark Magic Twin Burst is not in trunk/card_ids — Set list is the three in-game Dark Magician support Spells only. Ceiling: misses Twin Burst; upgrade: add DARK_MAGIC_TWIN_BURST card + id.
- L172: no dedicated choice UI — A = SS Dark Magician, B = SS Dark Magician Girl. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `BOOK_OF_LIFE`
- path: `src_custom/spell_effects/book_of_life.c`
- L159: single-card GY model — banish removes opponent's top graveyard card.

### `CHAIN_STRIKE`
- path: `src_custom/spell_effects/chain_strike.c`
- L40: no Chain Link / chain-depth API — assume min Link 2, never same-name on chain. Ceiling: always legal at Link≥2 floor; upgrade: real chain counter.

### `CHAIN_SUMMONING`
- path: `src_custom/spell_effects/chain_summoning.c`
- L60: no Chain Link / chain-depth API — assume min Link 3. Ceiling: always legal at Link≥3 floor; upgrade: real chain counter.

### `CHICKEN_GAME`
- path: `src_custom/spell_effects/chicken_game.c`
- L95: no dedicated 3-way choice UI — nested A/B unlabeled. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `CHRYSALIS_NEO_SPACIAN`
- path: `src_custom/spell_effects/chrysalis_neo_spacian.c`
- L31: only the five Chrysalis in-trunk pairs are mapped.

### `COCOON_REBIRTH`
- path: `src_custom/spell_effects/cocoon_rebirth.c`
- L60: only the five Chrysalis in-trunk pairs are mapped.

### `COLD_WAVE`
- path: `src_custom/spell_effects/cold_wave.c`
- L30: no Main Phase 1-start / prior-action API — allow whenever unused this turn. Ceiling: can activate mid-MP1 after other actions; upgrade: wire ColdWave_CanActivateAtMainPhase1Start(isMp1Start, priorAction).

### `COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS`
- path: `src_custom/spell_effects/colosseum_cage_of_the_gladiator_beasts.c`
- L231: no labeled confirm menu - auto-discard when another copy is in hand.

### `DARK_CONTACT`
- path: `src_custom/spell_effects/dark_contact.c`
- L275: no dedicated choice UI — A = Dark Fusion FS, B = search. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `DARK_MAGIC_INHERITANCE`
- path: `src_custom/spell_effects/dark_magic_inheritance.c`
- L17: no card-description text search — approximate DM/DMG support S/T via name contains "Dark Magician"/"Dark Magic" plus a known support ID list. Ceiling: misses text-only mentions (e.g. cards that only list DM in effect text). Upgrade: description-string helper or generated support bitmask.

### `DARK_MAGIC_VEIL`
- path: `src_custom/spell_effects/dark_magic_veil.c`
- L110: no dedicated hand/GY choice UI — A = hand, B = GY. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `DE_SYNCHRO`
- path: `src_custom/spell_effects/de_synchro.c`
- L81: duel Extra Deck return is imperfect — ExtraDeck_AddCard writes the player's trunk Extra Deck only (deck-builder API). Ceiling: ClearZone off-field + best-effort ExtraDeck_AddCard when enable_extra_deck; upgrade: per-duelist mid-duel Extra Deck return for the Synchro's controller.
- L101: Synchro Summon materials are not recorded at summon time, so "if all materials are in your GY, SS all of them" cannot run. Ceiling: return-to-Extra-Deck only; upgrade: store material cardIds on the Synchro zone at SynchroDuel_Execute, then if each is in GY, SS from GY.

### `DIFFERENT_DIMENSION_CAPSULE`
- path: `src_custom/spell_effects/different_dimension_capsule.c`
- L209: RFP has no face-down flag — card is face-up in banished list. Ceiling: banished as normal RFP id; upgrade: face-down RFP bit.
- L257: RFP disabled — cannot banish from Deck. Ceiling: activation text only; upgrade: enable removed_from_play.

### `DIMENSION_FUSION`
- path: `src_custom/spell_effects/dimension_fusion.c`
- L130: RFP zone is id-list only (no face/position memory). Ceiling: SS face-up ATK via Duel_SpecialSummonMonsterId; upgrade: store zone state on banish + restore on return.

### `DOCTOR_D`
- path: `src_custom/spell_effects/doctor_d.c`
- L110: no dedicated hand/SS choice UI — A = add to hand, B = Special Summon. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L315: GY ignition "banish this card from GY, target 2 Destiny HERO; copy ATK until EOT" needs a GY-activate spell path + PickZone pair outside this file. Ceiling: on-field banish-cost recover only; upgrade: GY activate → banish DOCTOR_D → PickZone two Destiny HERO → set target ATK via temp stages / exact overlay until End Phase.

### `DOUBLE_SPELL`
- path: `src_custom/spell_effects/double_spell.c`
- L230: nested ActivateSpellEffect re-runs trap responses / field-spell specials; equips that need pre-set row2/col2 targets may fail. Ceiling: place + best-effort activate; upgrade: shared "resolve spell as if activated" helper that skips chain traps and supplies targeting for EQUIP/Field.

### `DRAGON_RAVINE`
- path: `src_custom/spell_effects/dragon_ravine.c`
- L187: no dedicated choice UI — A = add Dragunity, B = send Dragon to GY. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.

### `DRAGON_SHRINE`
- path: `src_custom/spell_effects/dragon_shrine.c`
- L177: no dedicated choice UI — A = send 1 more, B = stop. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L222: cancel on first pick auto-sends first Dragon (activation committed).

### `EN_ENGAGE_NEO_SPACE`
- path: `src_custom/spell_effects/en_engage_neo_space.c`
- L330: 1 stage ~= 500 ATK so +2 ≈ +1000.

### `END_OF_THE_WORLD`
- path: `src_custom/spell_effects/end_of_the_world.c`
- L16: Ruin, Queen of Oblivion is not in the trunk — only Demise is Ritual- Summonable via this card. Ceiling: Demise only; upgrade: add Ruin card + ID.

### `EVIL_ASSAULT`
- path: `src_custom/spell_effects/evil_assault.c`
- L148: no dedicated hand/SS choice UI — A = add to hand, B = Special Summon. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `EVIL_MIND`
- path: `src_custom/spell_effects/evil_mind.c`
- L211: no dedicated 3-way choice UI — nested A/B unlabeled. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `FACTORY_OF_ONE_HUNDRED_MACHINES`
- path: `src_custom/spell_effects/factory_of_one_hundred_machines.c`
- L148: stage unit is 500 ATK — applied +500×banished, not printed +200×. Ceiling: no fractional temp stages; upgrade: exact-ATK overlay cleared at End Phase (tempStage already clears EOT).

### `FUSION_DESTINY`
- path: `src_custom/spell_effects/fusion_destiny.c`
- L34: * ponytail: incomplete vs printed Destiny Fusion pool (Dystopia, Dangerous,

### `GADGET_BOX`
- path: `src_custom/spell_effects/gadget_box.c`
- L13: no dedicated Gadget Box Token card id — reuse MOON_TOKEN like other token spells. Ceiling: wrong printed name/stats; upgrade: real token card.

### `GENERATION_NEXT`
- path: `src_custom/spell_effects/generation_next.c`
- L185: no dedicated Deck/GY choice UI — A = Deck, B = GY. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L211: no dedicated hand/SS choice UI — A = add to hand, B = Special Summon. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `GRAVEKEEPERS_INSCRIPTION`
- path: `src_custom/spell_effects/gravekeepers_inscription.c`
- L33: no dedicated 3-way choice UI — A / B / START. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L112: "activate only at start of Main Phase 1" needs a phase/action counter outside this file (no Main Phase 1-start gate API). Ceiling: activable any time like a normal spell; upgrade: CanActivate → require MP1 + no prior play/set/summon this turn.

### `HARPIES_FEATHER_REST`
- path: `src_custom/spell_effects/harpies_feather_rest.c`
- L152: no multi-select GY UI — return 3 most recent Harpie Lady / Harpie Lady Sisters. Ceiling: no targeting; upgrade: DeckMenu multi-pick.

### `HYSTERIC_SIGN`
- path: `src_custom/spell_effects/hysteric_sign.c`
- L117: the End Phase search auto-selects the first three distinct Harpie cards. Ceiling: no player multi-pick; upgrade: DeckMenu multi-select.
- L168: no dedicated choice UI — A = Deck, B = GY. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.

### `ILLUSION_MAGIC`
- path: `src_custom/spell_effects/illusion_magic.c`
- L137: no dedicated Deck/GY choice UI — A = Deck, B = GY. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.

### `LEMURIA_THE_FORGOTTEN_CITY`
- path: `src_custom/spell_effects/lemuria_the_forgotten_city.c`
- L191: no per-zone Level overlay API — levels come from SetCardInfo / Legendary Ocean adjusters only. Ceiling: OPT marks used + shows text; Levels unchanged. Upgrade: turn-scoped level bonus on each controlled WATER (= waterCount) cleared at End Phase (card_hooks GetLegendaryOcean-style).

### `LEVEL_TUNING`
- path: `src_custom/spell_effects/level_tuning.c`
- L13: the marked target can feed the card-info UI through LevelTuning_ApplyLevelToCardInfo, but the duel engine has no dynamic Level query for tribute, Ritual, or Synchro rules. Ceiling: display-only -1 Level; upgrade: route all level consumers through this zone overlay.

### `LIGHTNING_STORM`
- path: `src_custom/spell_effects/lightning_storm.c`
- L132: no dedicated choice UI — A = monsters, B = Spells/Traps. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `LIGHTSWORN_SABRE`
- path: `src_custom/spell_effects/lightsworn_sabre.c`
- L81: Deck-to-GY re-equip (when milled) needs a mill/send-from-deck hook outside this file. Ceiling: equip-from-hand/field only; upgrade: mill path → if LIGHTSWORN_SABRE sent from Deck to GY then PickZone Lightsworn and RegisterDynamicEquip again.

### `LIGHTSWORN_SANCTUARY`
- path: `src_custom/spell_effects/lightsworn_sanctuary.c`
- L328: Shine Counters on Deck→GY mill / remove 2 instead of destroy need mill + destroy-gate + counter storage outside this file (DuelCard has no shine-counter field). Ceiling: continuous face-up + OPT recycle only; upgrade: mill hook → ++Shine; Duel_DestroyZone on Lightsworn → if counters >= 2*n then counters -= 2*n and skip destroy.

### `MAUSOLEUM_OF_THE_EMPEROR`
- path: `src_custom/spell_effects/mausoleum_of_the_emperor.c`
- L112: no dedicated Summon/Set UI — A = Summon, B = Set. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L224: SpecialSummonFromHandZone still hits ArchlordKristya SS lock and is not a true engine Normal Summon path. Ceiling: no-tribute placement + summoningBlocked; upgrade: dedicated NormalSummonWithoutTribute helper that skips GetNumRequiredTributes pay while using vanilla NS hooks.

### `MIRACLE_CONTACT`
- path: `src_custom/spell_effects/miracle_contact.c`
- L34: Cosmo Neos needs three Neo-Spacians with different Attributes, which the concrete FusionRecipe matcher cannot express. Ceiling: Cosmo Neos is not selectable. Upgrade: a predicate-based Contact Fusion material selector.

### `MYSTIK_WOK`
- path: `src_custom/spell_effects/mystik_wok.c`
- L93: no dedicated ATK/DEF choice UI — A = ATK, B = DEF. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `NECROVALLEY`
- path: `src_custom/spell_effects/necrovalley.c`
- L126: GY Type-Attribute change still needs SetCardInfo-in-GY gates. Ceiling: banish/move blocked via Necrovalley_Blocks*; upgrade: GY type/attr mutate → negate.

### `NECROVALLEY_THRONE`
- path: `src_custom/spell_effects/necrovalley_throne.c`
- L130: no dedicated choice UI — A = add Gravekeeper's, B = Normal Summon. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.

### `NEPHE_SHADDOLL_FUSION`
- path: `src_custom/spell_effects/nephe_shaddoll_fusion.c`
- L134: no attribute-name UI — A confirms, B cycles list. Ceiling: unlabeled; upgrade: effect-text attribute menu.

### `NEX`
- path: `src_custom/spell_effects/nex.c`
- L155: duel Extra Deck browser/SS missing (Trunk ExtraDeck_* is deck-builder only). Ceiling: spawn Lv4 Neo form by id when not in Main Deck; upgrade: Extra Deck pick + SS.

### `OBLITERATE_BLAZE`
- path: `src_custom/spell_effects/obliterate_blaze.c`
- L131: granted effects (pay half LP → destroy S/T + equip 5 Forbidden One as +2000 Equip; piercing) need activated monster hooks / equip system outside this file. Ceiling: marks target unk4=1 only; upgrade: copy Obliterate effects onto marked Exodia monster.

### `PAINFUL_CHOICE`
- path: `src_custom/spell_effects/painful_choice.c`
- L153: no committed multi-pick UI — pick 5 in a loop (snake_rain style). Cancel mid-loop auto-fills remaining in deck order.

### `POISON_OF_THE_OLD_MAN`
- path: `src_custom/spell_effects/poison_of_the_old_man.c`
- L27: no dedicated choice UI — A = burn 800, B = gain 1200 LP. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.

### `POT_OF_AVARICE`
- path: `src_custom/spell_effects/pot_of_avarice.c`
- L93: no multi-select GY UI — return 5 most recent monsters. Ceiling: no targeting; upgrade: DeckMenu multi-pick like Angels Tear.

### `POT_OF_EXTRAVAGANCE`
- path: `src_custom/spell_effects/pot_of_extravagance.c`
- L28: no dedicated choice UI — A = 3 banished (draw 1), B = 6 (draw 2). Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L71: Extra Deck face-down banish unsupported mid-duel (Trunk ExtraDeck_* APIs are deck-builder only). Also no "cannot draw by card effects this turn" lock. Ceiling: free draw 1/2 after A/B; upgrade: duel Extra Deck pick+banish FD + turn-scoped draw-lock flag.

### `PSEUDO_SPACE`
- path: `src_custom/spell_effects/pseudo_space.c`
- L241: name-become + replace effects until End Phase need copy-host / turn_effect hooks outside this file (no per-zone name/effect RAM here). Ceiling: OPT banish Field Spell from GY only; upgrade: store banished id → treat zone as that Field Spell until End Phase clear.
- L262: name-become + replace effects until End Phase — same ceiling as legacy-GY path above.

### `REALM_OF_LIGHT`
- path: `src_custom/spell_effects/realm_of_light.c`
- L14: Shine Counters on mill / +100 ATK per counter on Lightsworn / remove 2 counters instead of destroy need mill + destroy-gate + counter storage outside this file (DuelCard has no shine-counter field; no in-file Deck→GY or destroy dispatch). Ceiling: continuous face-up only; upgrade: mill hook → if face-up REALM_OF_LIGHT controller's Deck→GY then ++counters;

### `REASONING`
- path: `src_custom/spell_effects/reasoning.c`
- L63: no Level-declare UI — D-Pad cycles, A confirms (unlabeled). Ceiling: no on-screen Level readout; upgrade: effect-text Level picker.

### `REPTILIANNE_SPAWN`
- path: `src_custom/spell_effects/reptilianne_spawn.c`
- L13: no Reptilianne Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. Ceiling: wrong Type/Attribute (Fairy/LIGHT vs Reptile/EARTH); upgrade: add REPTILIANNE_TOKEN card data + art, then swap this define.

### `SCAPEGOAT`
- path: `src_custom/spell_effects/scapegoat.c`
- L10: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. Ceiling: wrong Type/Attribute (Fairy/LIGHT vs Beast/EARTH); upgrade: add SHEEP_TOKEN card data + art, then swap this define.
- L74: LockMonsterCardsInRow also blocks Normal Set of monsters. Ceiling: cannot allow Set while blocking Summon without a menu hook that distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.
- L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. Ceiling: best-effort lockMonster; upgrade: tribute validator excludes SCAPEGOAT_TOKEN_ID / token flag.

### `SECRETS_OF_DARK_MAGIC`
- path: `src_custom/spell_effects/secrets_of_dark_magic.c`
- L319: no dedicated choice UI — A = Fusion, B = Ritual. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `SHADDOLL_FUSION`
- path: `src_custom/spell_effects/shaddoll_fusion.c`
- L243: Extra Deck SS detection uses Fusion/Synchro/Xyz/Link color on opponent's field (no per-zone summon-origin flag). Ceiling: misses Main Deck monsters SS'd from Extra edge cases; upgrade: mark Extra Deck origin on SS.

### `SHINING_SARCOPHAGUS`
- path: `src_custom/spell_effects/shining_sarcophagus.c`
- L137: printed ignition is Main Phase OPT, not on-activate. Ceiling: one Deck search when this continuous is activated; upgrade: face-up ignition hook → same search with OPT reset.
- L170: opp GY Special Summon → discard Spell → send that monster to GY needs summon/trigger hook outside this file.
- L176: printed text is monster-effect destroy only; Duel_DestroyZone has no source tag so all card-effect destroys are blocked. Battle uses a different path.

### `SKYSCRAPER_2_HERO_CITY`
- path: `src_custom/spell_effects/skyscraper_2_hero_city.c`
- L244: no "destroyed by battle" GY filter — no destroy-reason memory on expanded GY cards. Ceiling: any Elemental HERO in GY is legal; upgrade: stamp battle-destroy on GY push / zone→GY, then filter IsElementalHeroMonster && wasDestroyedByBattle.

### `SNAKE_RAIN`
- path: `src_custom/spell_effects/snake_rain.c`
- L179: no committed multi-pick UI — cancel mid-loop auto-fills remaining reptiles in deck order. Ceiling: player cannot abort partial selection.

### `SOUL_SERVANT`
- path: `src_custom/spell_effects/soul_servant.c`
- L30: no card-description text search — approximate "lists DM/DMG" via name contains "Dark Magician" plus a known support ID list. Ceiling: misses text-only mentions. Upgrade: description-string helper.
- L161: no dedicated 3-way choice UI — nested A/B unlabeled. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `SPELL_CHRONICLE`
- path: `src_custom/spell_effects/spell_chronicle.c`
- L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished. Ceiling: cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.
- L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn. Ceiling: briefly hits GY; upgrade: direct deck→RFG.
- L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. Ceiling: activate discard+banish 5 only; unk4 counter slot unused.

### `SPELL_GEAR`
- path: `src_custom/spell_effects/spell_gear.c`
- L239: no committed multi-pick UI — cancel mid-loop auto-fills remaining Ancient Gear zones in row order. Ceiling: player cannot abort partial pick.

### `SUPREME_KINGS_CASTLE`
- path: `src_custom/spell_effects/supreme_kings_castle.c`
- L121: "Fusion Summon monsters that must be Special Summoned with Dark Fusion, with effects other than Dark Fusion" needs Evil HERO summon gates to check SupremeKingsCastle_IsActive. Ceiling: face-up field only.
- L216: Deck/Extra Evil HERO pick UI skipped — first Deck match auto-sent.

### `THE_CLAW_OF_HERMOS`
- path: `src_custom/spell_effects/the_claw_of_hermos.c`
- L192: no dedicated field/hand choice UI — A = field, B = hand. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L353: Set reveal has no dedicated flip UI — send face-down as-is. Ceiling: no reveal animation; upgrade: brief face-up before GY send.

### `THE_FANG_OF_CRITIAS`
- path: `src_custom/spell_effects/the_fang_of_critias.c`
- L153: no dedicated hand/field choice UI — A = hand, B = field. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `THE_SACRED_WATERS_IN_THE_SKY`
- path: `src_custom/spell_effects/the_sacred_waters_in_the_sky.c`
- L252: no dedicated choice UI — A = activate Sanctuary, B = search mention. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L535: battle-destruction protection ("banish this from GY instead") needs a battle/destroy redirect hook. Ceiling: activate + LP gain only; upgrade: battle_damage / destroy-protection hook checking GY Sacred Waters.

### `THE_SHALLOW_GRAVE`
- path: `src_custom/spell_effects/the_shallow_grave.c`
- L155: no DUEL_SUMMON_SPECIAL_FACE_DOWN_DEF — NORMAL_SET for face-down DEF, then mark unk4=2 as Special Summon. Ceiling: SS-locks that only gate SummonModeIsSpecial still apply via SpecialSummonMonsterId's Kristya check; CannotBeSpecialSummoned checked here. Upgrade: add face-down SS mode.

### `TWLIGHT_TWIN_DRAGONS`
- path: `src_custom/spell_effects/twlight_twin_dragons.c`
- L241: Deck-to-GY by Lightsworn → add Punishment Dragon from GY + banish top 4 needs a mill/send-from-deck hook outside this file. Ceiling: on-activate JD recycle + mill only; upgrade: if TWLIGHT_TWIN_DRAGONS sent Deck→GY by Lightsworn effect → PickZone PD in GY → hand, then banish top 4.

### `ULTRA_POLYMERIZATION`
- path: `src_custom/spell_effects/ultra_polymerization.c`
- L172: GY ignition "banish this card, target 1 Fusion Summoned by this card; SS all materials used from GY, ATK/DEF 0, effects negated" needs GY activation + material-memory outside this file. Ceiling: on-field Fusion only; upgrade: store material ids on summon tag → GY activate ULTRA_POLYMERIZATION → Duel_BanishGraveyard → SS materials with

## trap (88)

### `A_HERO_EMERGES`
- path: `src_custom/trap_effects/a_hero_emerges.c`
- L26: Extra Deck / Ritual need proper summon; treat as unsummonable from hand
- L62: Normal Trap must leave the backrow to prevent AI re-trigger loop

### `ACE_OF_WAND`
- path: `src_custom/trap_effects/ace_of_wand.c`
- L33: needs destroy-by-effect trigger wire + trapEffect ID.

### `AEGIS_OF_THE_OCEAN_DRAGON_LORD`
- path: `src_custom/trap_effects/aegis_of_the_ocean_dragon_lord.c`
- L37: battle/effect destroy protect until EP + trapEffect wire. Ceiling: marks unk4 on matching monsters; upgrade: destroy gates skip marked until End Phase clear + trap dispatcher.

### `AMAZONESS_HALL`
- path: `src_custom/trap_effects/amazoness_hall.c`
- L43: * ponytail: Extra Deck / Pendulum place + opp SS gain LP need hooks. */

### `AMAZONESS_HOT_SPRING`
- path: `src_custom/trap_effects/amazoness_hot_spring.c`
- L46: * ponytail: Pendulum Zone place + battle-damage gain LP OPT need hooks. */

### `AMAZONESS_ONSLAUGHT`
- path: `src_custom/trap_effects/amazoness_onslaught.c`
- L20: Battle Phase OPT SS + after-damage banish + leave GY search need battle/leave hooks. Ceiling: SS 1 Amazoness from hand +1 stage (~500 ATK).

### `AMAZONESS_WILLPOWER`
- path: `src_custom/trap_effects/amazoness_willpower.c`
- L62: must-attack + mutual destroy-on-leave need battle/leave hooks.

### `ANCIENT_GEAR_DUEL`
- path: `src_custom/trap_effects/ancient_gear_duel.c`
- L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks. Ceiling: mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand-in from Deck/hand.

### `ANGELS_TEAR`
- path: `src_custom/trap_effects/angels_tear.c`
- L342: need 4 banish targets plus 1 summon target.

### `ARCANA_CALL`
- path: `src_custom/trap_effects/arcana_call.c`
- L81: until EP, selected AF uses banished AF's coin effect — needs End Phase clear + Arcana effect dispatch override. Ceiling: marks field monster; GY Arcana banished.

### `ATTACK_AND_RECEIVE`
- path: `src_custom/trap_effects/attack_and_receive.c`
- L48: activate when you take damage. Ceiling: burn 700 + 300×GY copies.

### `BATTLE_MANIA`
- path: `src_custom/trap_effects/battle_mania.c`
- L16: activate only opp Standby. Ceiling: when Effect runs, flip opp monsters to ATK; forced-attack / cannot-change-position need battle gates.

### `BLESSED_WINDS`
- path: `src_custom/trap_effects/blessed_winds.c`
- L51: 3 OPT modes + once-per-turn flag need ignition menu. Ceiling on activate: prefer pay 1000 → SS Aroma from GY; else send Plant → +500 LP; else shuffle Plant from GY → +500 LP.

### `BREAK_THE_DESTINY`
- path: `src_custom/trap_effects/break_the_destiny.c`
- L34: skip opp next Main Phase 1 + GY search Destiny-mention S/T need phase/GY hooks. Ceiling: destroy 1 Lv8+ Destiny HERO / Destiny End Dragoon.

### `CHAIN_MATERIAL`
- path: `src_custom/trap_effects/chain_material.c`
- L15: Fusion material from Deck/hand/field/GY + cannot attack + End Phase destroy Fusion need fusion/battle/turn hooks. Ceiling: face-up continuous mark (unk4) that Fusion may banish materials broadly.

### `CROSS_DIMENSONAL_DUEL`
- path: `src_custom/trap_effects/cross_dimensonal_duel.c`
- L27: next Standby return at double ATK + GY protect Golem need turn/destroy hooks. Ceiling: banish 1 Ancient Gear you control.

### `D_TACTICS`
- path: `src_custom/trap_effects/d_tactics.c`
- L58: Standby HERO +400 + destroy-Set D-HERO Spell need turn/destroy hooks. Ceiling: +1 stage on HERO monsters; if Lv8+ D-HERO present, banish 1 opp card (field then GY then hand).

### `D_TIME`
- path: `src_custom/trap_effects/d_time.c`
- L61: when face-up E-HERO leaves field. Ceiling: when Effect runs, search Destiny HERO Lv ≤ origin level (or 4); upgrade: leave-field hook when Duel_IsElementalHeroCard.

### `DAMAGE_EQUALS_REPTILE`
- path: `src_custom/trap_effects/damage_equals_reptile.c`
- L71: battle-damage involving Reptile trigger + OPT.

### `DAMAGE_POLARIZER`
- path: `src_custom/trap_effects/damage_polarizer.c`
- L13: negate effect-damage activation needs damage-effect chain gate. Ceiling: both players draw 1 when Effect runs; upgrade: trapEffect on effect-damage activate → cancel damage + draw.

### `DAMAGE_REPTILE`
- path: `src_custom/trap_effects/damage_reptile.c`
- L49: OPT when take battle damage involving Reptile. Ceiling: when Effect runs, SS Reptile from Deck with ATK ≤ a stand-in damage amount (origin ATK if monster); upgrade: battle-damage hook stores damage.

### `DARK_RENEWAL`
- path: `src_custom/trap_effects/dark_renewal.c`
- L52: on opp NS/SS. Ceiling: send origin + your Spellcaster → GY, then SS DARK Spellcaster from Deck/GY; upgrade: summon trigger wire.

### `DARK_SUPREMACY`
- path: `src_custom/trap_effects/dark_supremacy.c`
- L38: "Spells that mention Dark Fusion" not scanned by text.
- L53: GY banish shuffle HERO need GY ignition OPT. Ceiling: negate up to count face-up opp cards (monsters first) via unk4.

### `DRAMATIC_RESCUE`
- path: `src_custom/trap_effects/dramatic_rescue.c`
- L41: printed trigger is card targeting an Amazoness. Ceiling: bounce origin-row monster if Amazoness + SS other from hand; upgrade: target-chain hook when target passes Duel_IsAmazonessCard.

### `DRIED_WINDS`
- path: `src_custom/trap_effects/dried_winds.c`
- L47: LP-gain destroy + OPT flags need LP-gain hook. Ceiling: if Aroma + LP≥opp+3000, pay difference and destroy opp face-up monsters while remaining budget covers printed ATK.

### `DUST_TORNADO`
- path: `src_custom/trap_effects/dust_tornado.c`
- L112: optional hand pick — B skips; upgrade path: shared helper in exchange_hand_selection

### `ETERNAL_SOUL`
- path: `src_custom/trap_effects/eternal_soul.c`
- L75: DM unaffected by opp + destroy all on leave need protection / leave hooks. Ceiling: OPT stand-in — SS Dark Magician from hand/GY, else search Dark Magic Attack / Thousand Knives.

### `EXCHANGE_OF_THE_SPIRIT`
- path: `src_custom/trap_effects/exchange_of_the_spirit.c`
- L32: full Deck↔GY swap is heavy — approximate by pushing all GY to deck bottom and rebuilding GY from current undrawn deck top chunk. Ceiling: incomplete swap if GY expand / deck sizes mismatch; upgrade: proper dual-buffer swap of entire Deck and GY stacks.

### `FAVOURITE_CONTACT`
- path: `src_custom/trap_effects/favourite_contact.c`
- L48: Extra Deck Fusion ignoring summon conditions + materials to Deck bottom need fusion recipe API. Ceiling: return up to 2 HERO/Neos/ Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free.

### `FORGOTTEN_TEMPLE_OF_THE_DEEP`
- path: `src_custom/trap_effects/forgotten_temple_of_the_deep.c`
- L34: name-becomes-Umi + End Phase return need field-name/turn hooks. Ceiling: once on activate, banish one Lv4- Fish/SS/Aqua you control.

### `FOSSIL_EXCAVATION`
- path: `src_custom/trap_effects/fossil_excavation.c`
- L78: negate SS effects + mutual destroy-on-leave need leave hooks.

### `GLADIATOR_BEAST_WAR_CHARIOT`
- path: `src_custom/trap_effects/gladiator_beast_war_chariot.c`
- L32: negate Effect Monster activation + destroy needs negation hook. Ceiling: destroys origin monster if present; upgrade: full negate.

### `GLADIATOR_BEASTS_MEDUSA_SHIELD`
- path: `src_custom/trap_effects/gladiator_beasts_medusa_shield.c`
- L46: cannot be destroyed by card effects / OPT negate opp monster / if sent GY this turn Set GB Trap from Deck need destroy/negate/GY hooks. Ceiling: continuous face-up + marks only.
- L55: needs trapEffect ID + dispatcher wire + PickZone.

### `GLADIATOR_NAUMACHIA`
- path: `src_custom/trap_effects/gladiator_naumachia.c`
- L44: forced attack + destroy-search GB from Deck need battle/destroy hooks. Ceiling: if GB on field, mark opp must-attack; shuffle 1 GB from hand/GY and boost 1 GB by +1 stage (~original DEF stand-in).

### `GLORIOUS_ILLUSION`
- path: `src_custom/trap_effects/glorious_illusion.c`
- L70: End Phase mill 2 + mutual destroy-on-leave need turn/leave hooks.

### `GRAVEKEEPERS_TRAP`
- path: `src_custom/trap_effects/gravekeepers_trap.c`
- L83: Exchange lock GY effects/SS + opp Draw Phase look + discard cost need GY/draw gates. Ceiling: if Exchange in GY mark unk4 lock; discard 1 → search Gravekeeper's / EARTH Fairy.

### `HALF_COUNTER`
- path: `src_custom/trap_effects/half_counter.c`
- L20: damage calculation when your monster attacked needs battle hook. Ceiling: when Effect runs, boost defender by ~half attacker original ATK via stages; upgrade: damage-calc targeting wire.
- L39: 1 stage ~= 500 ATK.

### `HARPIE_LADY_ELEGANCE`
- path: `src_custom/trap_effects/harpie_lady_elegance.c`
- L47: * ponytail: WIND-only SS lock this turn + destroy-search Harpie Spell need hooks. */

### `HARPIES_FEATHER_STORM`
- path: `src_custom/trap_effects/harpies_feather_storm.c`
- L107: opp monster-effect negate this turn + hand activate need gates. Ceiling: if WIND Winged Beast, mark continuous lock via unk4 on this resolve; if Harpie present, also try add Feather Duster (destroy-search stand-in when gate missing).

### `HUMID_WINDS`
- path: `src_custom/trap_effects/humid_winds.c`
- L103: each effect OPT as face-up ignition needs Main Phase hooks + turn reset. Ceiling: one search+heal path on activate flip.

### `HUNTING_INSTINCT`
- path: `src_custom/trap_effects/hunting_instinct.c`
- L27: printed trigger is opp Special Summon. Ceiling: when Effect runs, SS Dinosaur from hand; upgrade: SS-to-opp-field trigger wire.

### `HYSTERIC_PARTY`
- path: `src_custom/trap_effects/hysteric_party.c`
- L72: when this face-up leaves → destroy those SS'd Harpie Lady needs leave-field hook. Ceiling: continuous face-up + GY Harpie Lady SS; OPT trapEffect wire.

### `ICARUS_ATTACK`
- path: `src_custom/trap_effects/icarus_attack.c`
- L51: needs trapEffect wire + PickZone for 2 targets.

### `IMPERIAL_TOMBS_OF_NECROVALLEY`
- path: `src_custom/trap_effects/imperial_tombs_of_necrovalley.c`
- L41: negate need Spell/Trap/monster chain gate + once-per-turn flag. Ceiling: if Gravekeeper + Necrovalley present, destroy origin card.

### `INFINITE_IMPERMANENCE`
- path: `src_custom/trap_effects/infinite_impermanence.c`
- L17: hand-activate if empty field + column S/T negate need gates. Ceiling: mark 1 face-up opp monster (unk4) as effect-negated stand-in.

### `LIGHTSWORN_AEGIS`
- path: `src_custom/trap_effects/lightsworn_aegis.c`
- L63: until EP negate + mill-from-Deck Set this card + OPT need End Phase clear / mill hook / turn reset. Ceiling: exhausts up to LS-count opp face-ups.

### `LIGHTSWORN_JUDGEMENT`
- path: `src_custom/trap_effects/lightsworn_judgement.c`
- L45: if sent Deck→GY by Lightsworn effect → add Judgment Dragon needs mill/GY hook. Ceiling: places on Deck top only; upgrade: on LS mill of this card → search JUDGMENT_DRAGON to hand.

### `MACRO_COSMOS`
- path: `src_custom/trap_effects/macro_cosmos.c`
- L31: any card sent to GY is banished instead needs GY-send redirect while face-up MACRO_COSMOS. Ceiling: continuous + optional Helios SS.

### `MAGIC_CYLINDER`
- path: `src_custom/trap_effects/magic_cylinder.c`
- L22: Normal Trap must leave the backrow to prevent AI re-trigger loop

### `MAGICAL_ARM_SHIELD`
- path: `src_custom/trap_effects/magical_arm_shield.c`
- L23: attack declare + redirect damage calc need battle hooks. Ceiling: take control of 1 face-up opp monster except origin attacker (Change of Heart style move to our monster row).

### `MAGICAL_HATS`
- path: `src_custom/trap_effects/magical_hats.c`
- L34: face-down DEF 0/0 hat tokens + shuffle + End BP destroy need token zones / battle-phase gate. Ceiling: pull 2 S/T from Deck onto empty monster zones face-down DEF; Set 1 own monster face-down.

### `MAGICIAN_NAVIGATION`
- path: `src_custom/trap_effects/magician_navigation.c`
- L58: GY banish negate S/T needs GY ignition + face-up S/T target. Ceiling: SS Dark Magician from hand, then Deck SS Lv7− DARK Spellcaster.

### `MAGICIANS_CIRCLE`
- path: `src_custom/trap_effects/magicians_circle.c`
- L55: printed trigger is Spellcaster attack declare. Ceiling: when Effect runs, each player Deck SS Spellcaster ≤2000 ATK; upgrade: attack declare hook when attacker is Spellcaster.

### `MAGICIANS_COMBINATION`
- path: `src_custom/trap_effects/magicians_combination.c`
- L39: once-per-turn on any activation + negate need chain gate. Ceiling: Tribute 1 DM/DMG → SS the other from hand/GY.
- L74: GY destroy-1 when this leaves S/T zone needs leave hook.

### `METAVERSE`
- path: `src_custom/trap_effects/metaverse.c`
- L122: choose activate Field vs add to hand — always add to hand. Ceiling: no Field Zone activate path; upgrade: A/B choice → set gDuel.field.
- L132: needs trapEffect ID + dispatcher wire.

### `METEORAIN`
- path: `src_custom/trap_effects/meteorain.c`
- L23: this turn your monsters inflict piercing needs battle damage calc hook + End Phase leave. Ceiling: face-up continuous mark; upgrade: battle ATK>DEF vs Defense → piercing while METEORAIN face-up this turn.

### `MIRROR_FORCE`
- path: `src_custom/trap_effects/mirror_force.c`
- L21: destroy self after monsters so AI sim doesn't re-trigger

### `MORPHTRONIC_FORCEFIELD`
- path: `src_custom/trap_effects/morphtronic_forcefield.c`
- L81: negate ST that would destroy face-up Morphtronic needs destroy- targeting chain gate. Ceiling: destroy origin ST if present + search Morphtronic; upgrade: full negate + trapEffect.

### `MORPHTRONIC_IMPACT_RETURN`
- path: `src_custom/trap_effects/morphtronic_impact_return.c`
- L38: GY banish SS Morphtronic need GY ignition. Ceiling: shuffle 1 Morphtronic from hand into Deck, shuffle up to 2 opp S/T into Deck.

### `MORPHTRONIC_MIXUP`
- path: `src_custom/trap_effects/morphtronic_mixup.c`
- L75: PickZone for 2 targets + opp choice UI; trapEffect wire.

### `NECROVALLEY_TEMPLE`
- path: `src_custom/trap_effects/necrovalley_temple.c`
- L90: -500 ATK/DEF while GK+Necrovalley need stat overlay; destroy-Set Necrovalley S/T from Deck need destroy hook. Ceiling: if GK present, try place Necrovalley from hand/GY; mark opp monsters -1 stage.

### `NEXT`
- path: `src_custom/trap_effects/next.c`
- L42: negate effects + Extra Deck lock (Fusion only) need gates. Ceiling: SS distinct Neo-Spacians / Neos from hand then GY in DEF.

### `NUMINOUS_HEALER`
- path: `src_custom/trap_effects/numinous_healer.c`
- L48: activate when you take damage. Ceiling: when Effect runs, heal 1000 + 500×GY copies; upgrade: LP-damage trigger wire.

### `PROPHECY`
- path: `src_custom/trap_effects/prophecy.c`
- L68: player predict UI (bigger/smaller) + trapEffect wire. Ceiling: random opp hand card; AI random guess / player always higher.

### `QUEENS_PAWN`
- path: `src_custom/trap_effects/queens_pawn.c`
- L50: activate when Amazoness destroys by battle. Ceiling: when Effect runs, Deck SS Lv≤4 Amazoness; upgrade: battle-destroy hook when attacker passes Duel_IsAmazonessCard.

### `RAIGEKI_BREAK`
- path: `src_custom/trap_effects/raigeki_break.c`
- L74: needs trapEffect ID + CheckTrapActivationConditions / Effect dispatch + player PickZone for field target. Ceiling: Effect body only.

### `RED_REBOOT`
- path: `src_custom/trap_effects/red_reboot.c`
- L30: hand-activate by paying half LP + full Trap negate need gates. Ceiling: Set origin Trap face-down + optional Deck Set 1 Trap for opp; opp Trap lock this turn not wired.

### `REVERSAL_OF_FATE`
- path: `src_custom/trap_effects/reversal_of_fate.c`
- L43: Arcana Force coin result stored in unk4/effect flags — flip bit0. Ceiling: toggles unk4 bit0; upgrade: real coin-result invert hook.
- L52: needs trapEffect ID + dispatcher wire + PickZone.

### `RISE_OF_THE_SNAKE_DEITY`
- path: `src_custom/trap_effects/rise_of_the_snake_deity.c`
- L16: printed trigger is Vennominon destroyed except by battle. Ceiling: when Effect runs, SS Vennominaga from hand/Deck; upgrade: destroy hook gates activation to non-battle Vennominon leave.

### `RITE_OF_SPIRIT`
- path: `src_custom/trap_effects/rite_of_spirit.c`
- L61: unaffected by Necrovalley — already no Necrovalley gate here. PickZone for GY target + trapEffect wire.

### `SCRAP_IRON_SCARECROW`
- path: `src_custom/trap_effects/scrap_iron_scarecrow.c`
- L16: negate attack needs attack-declare hook (Negate Attack path). Ceiling: Set face-down again instead of GY; upgrade: NegateAttack + trapEffect wire.

### `SHADDOLL_CORE`
- path: `src_custom/trap_effects/shaddoll_core.c`
- L45: true trap-monster (still a Trap) + Attribute fusion substitute need Embodiment-style link. Ceiling: place SHADDOLL_CORE on monster row and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate.

### `SHADDOLL_SCHISM`
- path: `src_custom/trap_effects/shaddoll_schism.c`
- L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker. Ceiling: banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.

### `SIXTH_SENSE`
- path: `src_custom/trap_effects/sixth_sense.c`
- L43: no declare-2-numbers UI — fixed guess 2+5. Ceiling: AI/player always declare 2 and 5; upgrade: D-Pad number picker.

### `SNAKE_DEITYS_COMMAND`
- path: `src_custom/trap_effects/snake_deitys_command.c`
- L71: full Spell negate (prevent resolve) needs negation gate like Magic Jammer. Ceiling: destroys origin Spell zone; upgrade: trapEffect counter + cancel spell resolve.

### `SNAKE_WHISTLE`
- path: `src_custom/trap_effects/snake_whistle.c`
- L55: needs Reptile-destroyed trigger + trapEffect wire.

### `SOLEMN_JUDGMENT`
- path: `src_custom/trap_effects/solemn_judgment.c`
- L39: full Summon/ST negate needs summon/activation chain gates (like Magic Jammer / Solemn). Ceiling: pay half LP + destroy origin; upgrade: trapEffect counter → cancel resolve.

### `SOLEMN_WISHES`
- path: `src_custom/trap_effects/solemn_wishes.c`
- L89: InitBoard fills hands via TryDrawingCard before duel gfx; skip until past opening hand.

### `SPARK_BLASTER`
- path: `src_custom/trap_effects/spark_blaster.c`
- L40: Main Phase OPT change battle position of 1 face-up + destroy after 3 uses need ignition + counter. Ceiling: equips to Sparkman; unk4 use counter starts at 0.

### `TRAP_DUSTSHOOT`
- path: `src_custom/trap_effects/trap_dustshoot.c`
- L67: look at full hand + choose monster UI; trapEffect wire. Ceiling: auto first monster in opp hand → Deck shuffle.

### `TRAP_TRICK`
- path: `src_custom/trap_effects/trap_trick.c`
- L30: no Continuous/Counter trap type split — treat all traps as Normal.
- L102: "can activate this turn" — leave unlocked.
- L111: only 1 Trap activate rest of turn + OPT reset need gates.

### `TROJAN_GLADIATOR_BEAST`
- path: `src_custom/trap_effects/trojan_gladiator_beast.c`
- L50: summoned to controller's field not opponent — need cross-field SS. Ceiling: SS to own field then draw; upgrade: SS to ACTIVE monster row.
- L59: needs trapEffect ID + dispatcher wire.

### `TWILIGHT_CLOTH`
- path: `src_custom/trap_effects/twilight_cloth.c`
- L56: exact +200 ATK/DEF per banished until End Phase needs temp overlay. Ceiling: +1 perm stage (~500) per banished (capped).
- L70: Deck→GY Lightsworn protection mode needs mill-sent trigger.

### `TWILIGHT_ERASER`
- path: `src_custom/trap_effects/twilight_eraser.c`
- L110: PickZone for 2 field targets + mill→SS Lightsworn from hand.

### `TYRANT_WING`
- path: `src_custom/trap_effects/tyrant_wing.c`
- L58: second attack on monsters + End Phase self-destroy after attack need battle/turn hooks. Ceiling: Dragon equip + ~500 ATK stage.

### `URGENT_TUNING`
- path: `src_custom/trap_effects/urgent_tuning.c`
- L14: Synchro Summon during Battle Phase needs Synchro material/ED summon path outside this file (no in-file Synchro API). Ceiling: shows text + self-destroy; upgrade: collect Tuners + non-Tuners → Extra Deck Synchro SS.

### `VANQUISHING_LIGHT`
- path: `src_custom/trap_effects/vanquishing_light.c`
- L38: negate Summon + destroy summoned needs summon-negation hook. Ceiling: tributes a Lightsworn only; upgrade: cancel pending summon + destroy.

### `VENOM_BURN`
- path: `src_custom/trap_effects/venom_burn.c`
- L46: Venom Counters may live elsewhere than unk4; PickZone for target; trapEffect wire. Ceiling: first unk4>0 monster, burn ACTIVE (opp during response).

## activated (452)

### `A_CAT_OF_ILL_OMEN`
- path: `src_custom/activated_effects/a_cat_of_ill_omen.c`
- L71: FLIP trigger needs flip hook. Ceiling: once via usage if Trap in Deck.

### `ALECTOR_SOVEREIGN_OF_BIRDS`
- path: `src_custom/activated_effects/alector_sovereign_of_birds.c`
- L85: until end of turn clear needs EOT unk4 reset hook.
- L141: hand SS when opp has 2+ same Attribute uses FromHand path.

### `AMAZONESS_AUGUSTA`
- path: `src_custom/activated_effects/amazoness_augusta.c`
- L62: protect other Amazoness + second attack FALSE. Ceiling: OPT SS Amazoness from Deck (Fusion Summon trigger stand-in).

### `AMAZONESS_BABY_TIGER`
- path: `src_custom/activated_effects/amazoness_baby_tiger.c`
- L16: Amazoness-Tiger name + GY ATK boost need continuous hooks. Ceiling: SS from hand only; upgrade: on Amazoness summon trigger.

### `AMAZONESS_EMPRESS`
- path: `src_custom/activated_effects/amazoness_empress.c`
- L51: protect/pierce + leave-field SS Queen need permanent/leave hooks. Ceiling: OPT add Amazoness Queen (or Amazoness) from Deck to hand.
- L76: leave-field SS → Deck search stand-in (safer than Extra SS).

### `AMAZONESS_PET_LIGER`
- path: `src_custom/activated_effects/amazoness_pet_liger.c`
- L55: -800 ≈ -2 tempStage (~-1000); battle-after / cannot-attack Amazoness FALSE.
- L98: once-per-battle +500 / cannot-attack Amazoness need battle hooks. Ceiling: OPT −2 tempStage on 1 face-up opp monster.

### `AMAZONESS_PET_LIGER_KING`
- path: `src_custom/activated_effects/amazoness_pet_liger_king.c`
- L141: cannot-attack-this-turn needs attack-gate; mark unk4.
- L190: attack redirect FALSE. Ceiling: OPT destroy Amazoness → SS Warrior GY.

### `AMAZONESS_PRINCESS`
- path: `src_custom/activated_effects/amazoness_princess.c`
- L63: name=Queen + attack-send→SS need name/battle hooks. Ceiling: OPT add 1 Amazoness Spell/Trap from Deck.

### `AMAZONESS_QUEEN`
- path: `src_custom/activated_effects/amazoness_queen.c`
- L12: Amazoness cannot be destroyed by battle needs battle-destroy protection. Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.

### `AMAZONESS_SAGE`
- path: `src_custom/activated_effects/amazoness_sage.c`
- L98: end-of-Damage-Step-after-attack trigger needs battle hook. Ceiling: once via usage if opp Spell/Trap on field; upgrade: damage-step gate.

### `AMAZONESS_SCOUTS`
- path: `src_custom/activated_effects/amazoness_scouts.c`
- L22: either-player quick timing not wired; allow once via usage on your turn only. Ceiling: tribute self only; upgrade: Amazoness protection flags on face-up Amazoness monsters until EOT.
- L46: face-up Amazoness cannot be targeted/destroyed by effects this turn — no protection flag hook yet.

### `AMAZONESS_SPIRITUALIST`
- path: `src_custom/activated_effects/amazoness_spiritualist.c`
- L104: hand/GY bounce→SS + ED lock need GY/ED hooks. Ceiling: field OPT add Polymerization from Deck.

### `AMAZONESS_SPY`
- path: `src_custom/activated_effects/amazoness_spy.c`
- L34: battle destroy → return Amazoness from GY needs battle hook. Ceiling: SS from hand only; upgrade: reveal + battle recycle.

### `AMAZONESS_TRAINEE`
- path: `src_custom/activated_effects/amazoness_trainee.c`
- L12: battle shuffle-to-deck-bottom + +200 ATK need battle hooks. Ceiling: not ignition-activatable here; upgrade: battle destroy + stat overlay.

### `AMAZONESS_WAR_CHIEF`
- path: `src_custom/activated_effects/amazoness_war_chief.c`
- L118: on-NS/SS Set + Amazoness-only attack lock need summon/attack hooks. Ceiling: OPT Set 1 Amazoness S/T or Polymerization from Deck.

### `AMULET_DRAGON`
- path: `src_custom/activated_effects/amulet_dragon.c`
- L58: no multi-select GY UI — banish every Spell in both GYs (min.1 gate above).
- L254: on-summon text after field draw so Amulet Dragon is visible (fusion uses updateGfx=FALSE).

### `AN_OWL_OF_LUCK`
- path: `src_custom/activated_effects/an_owl_of_luck.c`
- L74: FLIP trigger needs flip hook. Ceiling: once via usage if Field Spell in Deck.

### `ANCIENT_FAIRY_DRAGON`
- path: `src_custom/activated_effects/ancient_fairy_dragon.c`
- L135: cannot conduct Battle Phase — unk4 lock stand-in.
- L196: true BP skip needs phase lock; unk4 stand-in. Ceiling: OPT SS Lv≤4 from hand; OPT destroy Field Spells + 1000 LP + add Field.

### `ANCIENT_GEAR_BEAST`
- path: `src_custom/activated_effects/ancient_gear_beast.c`
- L12: attack → opp cannot activate S/T until Damage Step + negate destroyed-in-battle monster effects need battle hooks. Ceiling: not ignition here.

### `ANCIENT_GEAR_CANNON`
- path: `src_custom/activated_effects/ancient_gear_cannon.c`
- L47: Battle Phase Trap lock not applied; upgrade: trap-activation gate.

### `ANCIENT_GEAR_COMMANDER`
- path: `src_custom/activated_effects/ancient_gear_commander.c`
- L202: NS stand-in → SS AG; GY banish SS Golem FALSE. Ceiling: OPT send AG Golem hand/field/Deck → SS AG hand/Deck.

### `ANCIENT_GEAR_DARK_GOLEM`
- path: `src_custom/activated_effects/ancient_gear_dark_golem.c`
- L60: name=AG Golem + cannot-Set lock FALSE. Ceiling: OPT add up to 2 Ancient Gear/Geartown from Deck then discard 1.

### `ANCIENT_GEAR_DRAGON`
- path: `src_custom/activated_effects/ancient_gear_dragon.c`
- L121: Quick negate + tribute-less NS need negate/summon hooks. Ceiling: OPT send Machine hand/field or AG Golem from Deck to GY.

### `ANCIENT_GEAR_ENGINEER`
- path: `src_custom/activated_effects/ancient_gear_engineer.c`
- L12: trap negate + attack lock + end-of-Damage-Step destroy need battle/trap hooks. Ceiling: not field-ignition activatable here.

### `ANCIENT_GEAR_FRAME`
- path: `src_custom/activated_effects/ancient_gear_frame.c`
- L68: attack S/T lock + leave-field SS FALSE. Ceiling: OPT discard 1 → add AG Golem or S/T mentioning Golem from Deck.

### `ANCIENT_GEAR_GADJILTRON_CHIMERA`
- path: `src_custom/activated_effects/ancient_gear_gadjiltron_chimera.c`
- L12: Green/Red/Yellow Gadget tribute branches (+300 ATK, direct burn, battle burn) need summon/tribute hooks. Ceiling: not ignition-activatable.

### `ANCIENT_GEAR_GADJILTRON_DRAGON`
- path: `src_custom/activated_effects/ancient_gear_gadjiltron_dragon.c`
- L106: pierce/burn/draw + attack S/T lock FALSE (lock elsewhere). Ceiling: OPT destroy 1 DEF opp (pierce stand-in) OR OPT burn 700.

### `ANCIENT_GEAR_GOLEM`
- path: `src_custom/activated_effects/ancient_gear_golem.c`
- L12: attack → opp cannot activate S/T until Damage Step + piercing need battle/attack hooks. Ceiling: not ignition-activatable here; upgrade: battle Spell/Trap lock while attacking + DEF-pierce damage step.

### `ANCIENT_GEAR_GOLEM_ULTIMATE_POUND`
- path: `src_custom/activated_effects/ancient_gear_golem_ultimate_pound.c`
- L58: piercing/multi-attack + destroy-trigger Poly FALSE. Ceiling: OPT discard Machine → unk4 extra-attack, else OPT add Poly.
- L85: real multi-attack needs battle hook; unk4=2 extra-attack stand-in.

### `ANCIENT_GEAR_KNIGHT`
- path: `src_custom/activated_effects/ancient_gear_knight.c`
- L12: Gemini Normal Monster treatment + attack S/T lock need summon/battle hooks. Ceiling: not ignition-activatable here.

### `ANCIENT_GEAR_MEGATON_GOLEM`
- path: `src_custom/activated_effects/ancient_gear_megaton_golem.c`
- L123: multi-attack + leave-field SS FALSE. Ceiling: OPT SS AG Golem from hand/GY.

### `ANCIENT_GEAR_SOLDIER`
- path: `src_custom/activated_effects/ancient_gear_soldier.c`
- L12: attack → opp cannot activate S/T until end of Damage Step needs battle lock hook. Ceiling: not ignition-activatable here; upgrade: battle phase Spell/Trap activation gate while this card is attacking.

### `ANCIENT_GEAR_STATUE`
- path: `src_custom/activated_effects/ancient_gear_statue.c`
- L111: ignore summoning conditions partial via CannotBeSS check. Ceiling: OPT tribute self → SS AG Golem / mentions-Golem from hand/Deck.
- L189: once-per-turn FromHand not tracked without turn flag.

### `ANCIENT_GEAR_TANKER`
- path: `src_custom/activated_effects/ancient_gear_tanker.c`
- L190: AG pierce mark for rest of turn FALSE.
- L234: pierce mark AG monsters FALSE. Ceiling: OPT SS AG from hand (GY if opp has monster), else OPT destroy your face-up. Separate OPTs share one MarkMonsterEffectUsed.

### `ANCIENT_SACRED_WYVERN`
- path: `src_custom/activated_effects/ancient_sacred_wyvern.c`
- L31: continuous LP→ATK + battle-reborn need permanent/battle hooks. Ceiling: OPT refresh tempStage from LP difference/500.

### `ANDRO_SPHINX`
- path: `src_custom/activated_effects/andro_sphinx.c`
- L32: battle burn half ATK + GY SS ban need battle/GY hooks. Ceiling: not field-ignition; FromHand pay 500 + Pyramid → SS.

### `APPRENTICE_ILLUSION_MAGICIAN`
- path: `src_custom/activated_effects/apprentice_illusion_magician.c`
- L120: on-NS/SS search auto + hand/field send +2000 Quick need summon/ damage hooks. Ceiling: OPT add Dark Magician from Deck.

### `ARCANA_FORCE_V_THE_HIEROPHANT`
- path: `src_custom/activated_effects/arcana_force_v_the_hierophant.c`
- L86: on-Summon coin + discard summon-lock need summon/FromHand paths. Ceiling: OPT coin → SS 1 Arcana Force from Deck.
- L153: discard only; opp cannot respond to Arcana Summons needs turn flag hook.

### `ARCANA_FORCE_XII_THE_HANGMAN`
- path: `src_custom/activated_effects/arcana_force_xii_the_hangman.c`
- L139: on-Summon coin should fire at summon; OPT stand-in here. Ceiling: OPT coin → destroy+burn (heads own / tails opp). FromHand SS AF.
- L170: coin targeting uses auto-pick highest ATK; upgrade: PickZone.

### `ARCANA_FORCE_XIX_THE_SUN`
- path: `src_custom/activated_effects/arcana_force_xix_the_sun.c`
- L81: on-Summon coin (Heads Set coin Spell / Tails wipe S/T) need summon hook. Ceiling: OPT coin → flip all opp monsters DEF or destroy half yours.
- L121: requires coin-toss card on field — skipped; SS anytime when legal.

### `ARCANA_FORCE_XV_THE_FIEND`
- path: `src_custom/activated_effects/arcana_force_xv_the_fiend.c`
- L206: on-Summon coin + discard search use summon/FromHand paths. Ceiling: OPT coin → destroy 1 monster or wipe field.

### `ARCANA_KNIGHT_JOKER`
- path: `src_custom/activated_effects/arcana_knight_joker.c`
- L12: discard matching type to negate activation needs chain/response hooks. Ceiling: not ignition-activatable here.

### `ARCANITE_MAGICIAN`
- path: `src_custom/activated_effects/arcanite_magician.c`
- L158: Synchro +2 Spell Counters + +1000 ATK/counter need synchro/stat hooks. Ceiling: OPT remove 1 unk4 counter (if >=1) → destroy 1 opp card.

### `ARCHLORD_KRISTYA`
- path: `src_custom/activated_effects/archlord_kristya.c`
- L322: engine treats level 5+ with no tribute as special-like (Cyber Dragon, etc.).

### `ARMED_DRAGON_LV5`
- path: `src_custom/activated_effects/armed_dragon_lv5.c`
- L135: EP send self → SS LV7 needs End Phase hook. Ceiling: OPT discard 1 hand monster → destroy 1 opp monster ATK≤.

### `ARMED_NEOS`
- path: `src_custom/activated_effects/armed_neos.c`
- L116: battle-destroy gain Extra tribute SS need battle/Extra hooks. Ceiling: OPT destroy opp monsters with Level ≤ highest Dragon Level in GY.

### `ARMITYLE_THE_CHAOS_PHANTASM`
- path: `src_custom/activated_effects/armityle_the_chaos_phantasm.c`
- L12: Extra Deck banish-fusion SS + battle indestructible + turn-only +10000 ATK need summon/permanent/battle hooks. Ceiling: not ignition here.

### `ARMORY_ARM`
- path: `src_custom/activated_effects/armory_arm.c`
- L12: monster-as-equip (+1000 / unequip SS / battle-destroy burn) needs monster Equip API beyond RegisterDynamicEquip spell links. Ceiling: FALSE.

### `AROMA_JAR`
- path: `src_custom/activated_effects/aroma_jar.c`
- L12: FLIP battle protection + End Phase LP gain need FLIP/continuous hooks. Ceiling: not ignition-activatable here; upgrade: flip + turn-end overlay.

### `AROMAGE_BERGAMOT`
- path: `src_custom/activated_effects/aromage_bergamot.c`
- L21: LP-higher Plant piercing + LP-gain gate + until opp EP clear need permanent/LP/battle hooks. Ceiling: OPT +2 tempStage (~1000 ATK/DEF).

### `AROMAGE_CANANGA`
- path: `src_custom/activated_effects/aromage_cananga.c`
- L126: continuous -500 ATK/DEF + LP-gain trigger need permanent/LP hooks. Ceiling: OPT bounce 1 opp Spell/Trap if hand room; upgrade: LP-gain gate + continuous stat overlay when your LP is higher.

### `AROMAGE_JASMINE`
- path: `src_custom/activated_effects/aromage_jasmine.c`
- L20: extra Plant Normal Summon while LP higher + draw-on-LP-gain need permanent/LP hooks. Ceiling: OPT draw 1 via usage; upgrade: LP-gain gate + extra Normal Summon overlay when your LP exceed opponent's.

### `AROMAGE_LAUREL`
- path: `src_custom/activated_effects/aromage_laurel.c`
- L66: LP-gain Tuner treat + sent-to-GY +500 LP need LP/send hooks. Ceiling: OPT add 1 Plant from Deck; upgrade: full Aroma branches.

### `AROMAGE_MARJORAM`
- path: `src_custom/activated_effects/aromage_marjoram.c`
- L97: FromHand SS on Plant destroy + LP-gain trigger need destroy/LP hooks. Ceiling: OPT banish up to Aroma-count cards from opp GY.

### `AROMAGE_ROSEMARY`
- path: `src_custom/activated_effects/aromage_rosemary.c`
- L125: LP-higher Plant attack → opp monster effects locked + LP-gain gate need permanent/LP hooks. Ceiling: OPT change 1 face-up battle position.

### `AROMALILITH_MAGNOLIA`
- path: `src_custom/activated_effects/aromalilith_magnolia.c`
- L100: Plant protect + LP-gain ATK need permanent/LP hooks. Ceiling: OPT pay 2000 → banish up to Humid/Dried/Blessed Winds count.
- L135: no multi-select UI — auto-banish up to winds count (opp rows first).

### `AROMALILITH_ROSALINA`
- path: `src_custom/activated_effects/aromalilith_rosalina.c`
- L106: discard quick LP + Plant-only SS lock need chain/SS hooks. Ceiling: OPT SS 1 non-Tuner Aroma from Deck in DEF.

### `AROMALILITH_ROSEMARY`
- path: `src_custom/activated_effects/aromalilith_rosemary.c`
- L57: SS-trigger search + LP-gain Link-point SS + pointed tribute banish need summon/LP/Link hooks. Ceiling: OPT search Aroma from Deck.

### `AROMASERAPHY_JASMINE`
- path: `src_custom/activated_effects/aromaseraphy_jasmine.c`
- L179: LP-higher battle protect + Link-point tribute + LP-gain search need Link/LP hooks. Ceiling: tribute 1 you control → SS Plant from Deck.

### `AROMASERAPHY_ROSEMARY`
- path: `src_custom/activated_effects/aromaseraphy_rosemary.c`
- L148: LP-higher Plant +500 ATK/DEF + LP-gain negate need permanent/LP hooks. Ceiling: OPT destroy 1 face-up opp card.

### `AROMASERAPHY_SWEET_MARJORAM`
- path: `src_custom/activated_effects/aromaseraphy_sweet_marjoram.c`
- L61: LP-higher Plant untargetable + Synchro Winds search + LP-gain destroy need continuous/summon/LP hooks. Ceiling: OPT search Aroma Plant.

### `ASH_BLOSSOM_AND_JOYOUS_SPRING`
- path: `src_custom/activated_effects/ash_blossom_and_joyous_spring.c`
- L50: chain negate for add/SS/mill from Deck not wired; upgrade: chain interrupt hook when one exists.

### `ATHENA`
- path: `src_custom/activated_effects/athena.c`
- L71: attack-position summons keep isFaceUp=0 until end-of-turn flip.
- L363: drop field-target cursor before GY deck menu — PickZone state + trunk view was crashing when the menu opened on confirm.

### `ATLANTEAN_ATTACK_SQUAD`
- path: `src_custom/activated_effects/atlantean_attack_squad.c`
- L12: continuous +800 ATK while controlling other Fish/SS/Aqua needs permanent overlay. Ceiling: not ignition-activatable here; upgrade: permanent ATK bonus check.

### `ATLANTEAN_DRAGOONS`
- path: `src_custom/activated_effects/atlantean_dragoons.c`
- L101: Lv3- Sea Serpent direct attack + sent-for-WATER-effect search need continuous/send hooks. Ceiling: OPT add 1 Sea Serpent except self from Deck.

### `ATLANTEAN_HEAVY_INFANTRY`
- path: `src_custom/activated_effects/atlantean_heavy_infantry.c`
- L111: extra Normal Summon Sea Serpent + sent-for-WATER destroy need summon/send hooks. Ceiling: OPT destroy 1 Set Spell/Trap.

### `ATLANTEAN_MARKSMAN`
- path: `src_custom/activated_effects/atlantean_marksman.c`
- L75: battle-damage trigger + sent-for-WATER destroy Set S/T need battle/send hooks. Ceiling: OPT SS Lv≤4 Atlantean Sea Serpent from Deck.

### `AZURE_EYES_SILVER_DRAGON`
- path: `src_custom/activated_effects/azure_eyes_silver_dragon.c`
- L47: until end of next turn clear needs EOT hook.
- L66: Special Summon protection + Standby SS Normal need summon/phase hooks. Ceiling: OPT mark your Dragons protected (unk4).

### `BABYCERASAURUS`
- path: `src_custom/activated_effects/babycerasaurus.c`
- L59: destroyed-by-effect→GY trigger needs destroy hook. Ceiling: once via usage if Lv≤4 Dino in Deck and open MMZ.

### `BARRIER_STATUE_OF_THE_STORMWINDS`
- path: `src_custom/activated_effects/barrier_statue_of_the_stormwinds.c`
- L12: no SS except WIND needs Special Summon lock gate. Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.

### `BAZOO_THE_SOUL_EATER`
- path: `src_custom/activated_effects/bazoo_the_soul_eater.c`
- L98: +1 tempStage per banished (~500 ATK each, not exact +300); until opp EP clear needs EP tempStage reset hook.

### `BEAST_KING_BARBAROS`
- path: `src_custom/activated_effects/beast_king_barbaros.c`
- L64: no-tribute 1900 ATK + tribute-3 summon gate need summon hooks. Ceiling: once via usage destroy all opp cards (tribute-3 stand-in).

### `BEAST_MACHINE_KING_BARBAROS_UR`
- path: `src_custom/activated_effects/beast_machine_king_barbaros_ur.c`
- L139: no battle damage to opp when this card battles needs battle hook. Ceiling: not field-ignition activatable; SS-from-hand uses FromHand path.
- L165: multi-zone banish picker not wired; require both types reachable.

### `BIRDFACE`
- path: `src_custom/activated_effects/birdface.c`
- L20: battle-destroy→GY trigger. Ceiling: once via usage if Harpie Lady in Deck and hand space.

### `BLACK_ROSE_DRAGON`
- path: `src_custom/activated_effects/black_rose_dragon.c`
- L158: Synchro Summon destroy-all needs summon hook. Ceiling: OPT banish 1 Plant from GY → opp DEF monster to ATK with 0 ATK (tempStage).

### `BLACK_WINGED_DRAGON`
- path: `src_custom/activated_effects/black_winged_dragon.c`
- L52: −700 ≈ −2 tempStage (~−1000); counter/damage-redirect FALSE.
- L95: damage redirect + Black Feather Counters + burn need damage hooks. Ceiling: OPT −2 tempStage on 1 face-up opp monster.

### `BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON`
- path: `src_custom/activated_effects/blue_eyes_alternative_ultimate_dragon.c`
- L55: cannot-attack-this-turn needs attack-gate; mark unk4.
- L98: protect + up-to-3-if-Alt-material need fusion/material hooks. Ceiling: OPT destroy 1 opp card; mark self unk4 cannot-attack.

### `BLUE_EYES_JET_DRAGON`
- path: `src_custom/activated_effects/blue_eyes_jet_dragon.c`
- L197: protect + destroy-trigger SS FALSE. Ceiling: field OPT bounce 1; FromHand if BEWD field/GY → SS.

### `BLUE_EYES_SOLID_DRAGON`
- path: `src_custom/activated_effects/blue_eyes_solid_dragon.c`
- L49: summon Quick shuffle→SS BEWD + per-effect usage need hooks.

### `BLUE_EYES_SPIRIT_DRAGON`
- path: `src_custom/activated_effects/blue_eyes_spirit_dragon.c`
- L65: OPT GY negate + Extra Synchro + EP destroy need chain/Extra hooks. Ceiling: OPT tribute self → SS LIGHT Dragon from Deck in DEF.

### `BLUE_EYES_TYRANT_DRAGON`
- path: `src_custom/activated_effects/blue_eyes_tyrant_dragon.c`
- L94: multi-attack + Trap immunity + battle-end Set need battle/permanent hooks. Ceiling: OPT Set 1 Trap from GY to backrow.

### `BLUE_EYES_ULTIMATE_SPIRIT_DRAGON`
- path: `src_custom/activated_effects/blue_eyes_ultimate_spirit_dragon.c`
- L23: Quick field negate + destroy-SS FALSE; GY banish-lock FALSE. Ceiling: OPT +2 tempStage (~+1000) as negate stand-in.

### `BOOT_UP_SOLDIER_DREAD_DYNAMO`
- path: `src_custom/activated_effects/boot_up_soldier_dread_dynamo.c`
- L39: continuous +2000 while Gadget on field needs permanent overlay. Ceiling: OPT apply +4 stages (~2000) if Gadget present.

### `BRIONAC_DRAGON_OF_THE_ICE_BARRIER`
- path: `src_custom/activated_effects/brionac_dragon_of_the_ice_barrier.c`
- L232: N-discard path auto-bounces N cards; upgrade: sequential PickZone.

### `CASTEL_THE_SKY_BLASTER_MUSKETEER`
- path: `src_custom/activated_effects/castel_the_sky_blaster_musketeer.c`
- L138: detach/material + face-down branch need overlay engine. Ceiling: OPT return 1 face-up monster to the Deck.

### `CELESTIA_LIGHTSWORN_ANGEL`
- path: `src_custom/activated_effects/celestia_lightsworn_angel.c`
- L89: Tribute Summon (by Lightsworn) trigger needs summon hook. Ceiling: once via usage — mill 4 then auto-destroy up to 2 opp cards (no player target pick; upgrade: PickZone for up to 2).

### `CELESTIAL_KNIGHTLORD_PARSHATH`
- path: `src_custom/activated_effects/celestial_knightlord_parshath.c`
- L104: Link material + GY banish Fairy → SS Fairy need send/banish hooks. Ceiling: OPT discard 1 → add Sanctuary/mention, or Fairy if Sanctuary on field.

### `CHAINSAW_INSECT`
- path: `src_custom/activated_effects/chainsaw_insect.c`
- L12: opp draws after Damage Step needs battle end hook. Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon gate outside this file.

### `CHAOS_ANCIENT_GEAR_GIANT`
- path: `src_custom/activated_effects/chaos_ancient_gear_giant.c`
- L12: Fusion-only + Spell/Trap immunity + battle-phase opp effect lock + multi-attack + piercing need fusion/battle hooks. Ceiling: not ignition-activatable here.

### `CHARM_OF_SHABTI`
- path: `src_custom/activated_effects/charm_of_shabti.c`
- L43: battle protection for Gravekeeper's monsters not applied. Ceiling: discard only; upgrade: battle-destroy immunity gate until EP.

### `CHIMERATECH_FORTRESS_DRAGON`
- path: `src_custom/activated_effects/chimeratech_fortress_dragon.c`
- L12: original ATK = 1000 x fusion material count needs fusion/summon stat overlay hook. Ceiling: not field-ignition activatable here.

### `CHIMERATECH_MEGAFLEET_DRAGON`
- path: `src_custom/activated_effects/chimeratech_megafleet_dragon.c`
- L12: original ATK = 1200 x fusion material count needs fusion/summon stat overlay hook. Ceiling: not ignition-activatable here.

### `CHIMERATECH_RAMPAGE_DRAGON`
- path: `src_custom/activated_effects/chimeratech_rampage_dragon.c`
- L86: on-Fusion destroy + multi-attack need fusion/battle hooks. Ceiling: OPT destroy up to 2 S/T on field.

### `CLEAR_VICE_DRAGON`
- path: `src_custom/activated_effects/clear_vice_dragon.c`
- L12: Clear World immunity + battle ATK double + discard-to-save need continuous/battle/destruction hooks. Ceiling: not ignition-activatable here.

### `COLOSSAL_FIGHTER`
- path: `src_custom/activated_effects/colossal_fighter.c`
- L119: +100 ATK per Warrior in any GY needs stat overlay; battle-destroy trigger deferred. Ceiling: OPT SS 1 Warrior from either GY once via usage.

### `CORAL_DRAGON`
- path: `src_custom/activated_effects/coral_dragon.c`
- L114: GY draw when Synchro Summoned card sent from field needs GY hook. Ceiling: OPT discard 1 → destroy 1 opp card.

### `CRIMSON_BLADER`
- path: `src_custom/activated_effects/crimson_blader.c`
- L12: battle destroy → opp cannot NS/SS Lv5+ next turn needs battle destroy + summon-lock hooks. Ceiling: not ignition-activatable here.

### `CRIMSON_DRAGON`
- path: `src_custom/activated_effects/crimson_dragon.c`
- L123: Extra Deck Synchro SS FALSE; Deck Dragon stand-in.
- L138: on-SS search + Extra Synchro return FALSE. Ceiling: OPT search mentioning Crimson Dragon S/T, else shuffle self → SS Dragon.

### `CROSS_KEEPER`
- path: `src_custom/activated_effects/cross_keeper.c`
- L145: GY draw-on-E-HERO-Fusion need Fusion/GY hooks. Ceiling: send self → SS Elemental HERO or Neo-Spacian from hand/GY.

### `CURIOUS_THE_LIGHTSWORN_DOMINION`
- path: `src_custom/activated_effects/curious_the_lightsworn_dominion.c`
- L33: Link Summon mill + leave-field GY add + mill-cascade need summon/ leave-field hooks. Ceiling: OPT mill 1 from Deck.

### `CYBER_DRAGON_INFINITY`
- path: `src_custom/activated_effects/cyber_dragon_infinity.c`
- L34: ATK summons keep isFaceUp=0 until EOT flip.
- L61: Xyz attach / negate FALSE. Ceiling: ClearZone absorb + +1 tempStage.
- L109: Xyz attach materials + negate FALSE. Ceiling: OPT ClearZone 1 face-up ATK monster (absorb) + tempStage self.

### `CYBER_ELTANIN`
- path: `src_custom/activated_effects/cyber_eltanin.c`
- L122: continuous ATK/DEF = banished×500 needs permanent overlay hook. Ceiling: not field-ignition activatable; use FromHand banish path.
- L188: permStage unit is ~500 ATK/DEF each, not exact banished×500 overlay.

### `CYBER_LASER_DRAGON`
- path: `src_custom/activated_effects/cyber_laser_dragon.c`
- L17: targets face-up monsters on opponent's side with ATK >= 2400 or DEF >= 2400. Upgrade path: scan backrow S/T cards if the card text ever changes.

### `CYBER_PHOENIX`
- path: `src_custom/activated_effects/cyber_phoenix.c`
- L12: Attack Position S/T negate + destroy-by-battle draw need continuous and battle hooks. Ceiling: not field-ignition activatable here.

### `CYBER_SLASH_HARPIE_LADY`
- path: `src_custom/activated_effects/cyber_slash_harpie_lady.c`
- L196: Quick on S/T activation + Synchro/name hooks missing. Ceiling: OPT bounce 1 opp card or your Harpie to hand.

### `CYBER_SLASH_HARPY_LADY`
- path: `src_custom/activated_effects/cyber_slash_harpy_lady.c`
- L196: Quick on S/T activation + Synchro/name hooks missing. Ceiling: OPT bounce 1 opp card or your Harpie to hand.

### `CYBER_VALLEY`
- path: `src_custom/activated_effects/cyber_valley.c`
- L107: end Battle Phase needs phase hook; draw 1 is attack-target stand-in.
- L128: attack-target banish + GY place-on-deck need battle/GY hooks. Ceiling: OPT banish self+1 face-up monster → draw 2; else banish self → draw 1.

### `CYBERNETIC_MAGICIAN`
- path: `src_custom/activated_effects/cybernetic_magician.c`
- L63: until End Phase clear needs EP tempStage reset hook.

### `D_D_WARRIOR`
- path: `src_custom/activated_effects/d_d_warrior.c`
- L12: after damage calc banish both needs battle hook. Ceiling: not ignition-activatable here; upgrade: permanent/tribute/battle gate outside this file.

### `DARK_ARMED_DRAGON`
- path: `src_custom/activated_effects/dark_armed_dragon.c`
- L174: allow self-target for faithful TCG simulation; player can choose suboptimally
- L317: auto-target. No GY picker (DeckMenu screen switch corrupts VRAM from inside monster effect handler) and no PickZone cursor state (200 conflicts with game loop after MonsterActionMenu case 4 returns). Picks the best field target via AiPickTarget logic. Upgrade path: dedicated cursor state + A/B handlers like Cannon Soldier.

### `DARK_BLADE_THE_DRAGON_KNIGHT`
- path: `src_custom/activated_effects/dark_blade_the_dragon_knight.c`
- L31: battle-damage trigger. Ceiling: once via usage if opp GY has monsters.

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

### `DARKBLAZE_DRAGON`
- path: `src_custom/activated_effects/darkblaze_dragon.c`
- L12: GY SS double stats + battle-destroy burn need SS/battle hooks. Ceiling: not ignition-activatable here.

### `DARKLORD_DESIRE`
- path: `src_custom/activated_effects/darklord_desire.c`
- L56: -2 tempStage (~1000 ATK, not exact); until EP clear needs EOT hook.
- L116: Fairy-only Tribute Summon + cannot SS need summon hooks. Ceiling: OPT -1000 ATK (tempStage) → send 1 opp monster to GY.

### `DARKNESS_NEOSPHERE`
- path: `src_custom/activated_effects/darkness_neosphere.c`
- L87: battle indestruct + trap bounce + attack-declare gate need battle/ phase hooks. Ceiling: not field-ignition activatable; SS uses FromHand path.
- L113: opp attack declare gate not wired; require 1 field + 1 hand Fiend.

### `DECOY_DRAGON`
- path: `src_custom/activated_effects/decoy_dragon.c`
- L181: attack-target redirect needs battle targeting hook. Ceiling: OPT SS Lv7+ Dragon from GY once via usage when legal.

### `DEEP_SEA_DIVA`
- path: `src_custom/activated_effects/deep_sea_diva.c`
- L58: Normal Summon trigger needs summon hook. Ceiling: once via usage while face-up if Lv≤3 Sea Serpent in Deck.

### `DESTINY_END_DRAGOON`
- path: `src_custom/activated_effects/destiny_end_dragoon.c`
- L65: cannot conduct Battle Phase — unk4 lock stand-in. GY revive FALSE.
- L105: GY revive FALSE. Ceiling: OPT destroy 1 opp monster + burn its ATK + cannot BP (unk4).

### `DESTINY_HERO_BLADE_MASTER`
- path: `src_custom/activated_effects/destiny_hero_blade_master.c`
- L58: +2 tempStage (~1000 ATK, not exact +800); until EP clear needs EP tempStage reset hook.
- L89: opponent Battle Phase gate not wired; allow when face-up D-HERO on field. Ceiling: discard anytime from hand; upgrade: opp BP phase hook.

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

### `DESTINY_HERO_DECIDER`
- path: `src_custom/activated_effects/destiny_hero_decider.c`
- L114: NS/SS → EP add + GY quick return-on-damage need summon/GY/chain hooks. Ceiling: OPT add 1 HERO from GY to hand.

### `DESTINY_HERO_DENIER`
- path: `src_custom/activated_effects/destiny_hero_denier.c`
- L189: GY SS when other D-HERO present needs GY/once-per-duel hooks. Ceiling: OPT put 1 D-HERO from Deck/GY/banished on top of Deck.

### `DESTINY_HERO_DESTROY_DOGMA`
- path: `src_custom/activated_effects/destiny_hero_destroy_dogma.c`
- L103: Quick destroy/negate FALSE; Standby burn → immediate burn. Ceiling: FromHand banish 3 Warrior/DARK → SS + burn 2000.

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

### `DESTINY_HERO_DOOM_LORD`
- path: `src_custom/activated_effects/destiny_hero_doom_lord.c`
- L66: cannot-attack-this-turn needs attack-gate on unk4; return-in-2-Standbys needs Standby hook. Ceiling: OPT banish 1 opp monster; mark self unk4.

### `DESTINY_HERO_DREADNOUGHT_MASTER`
- path: `src_custom/activated_effects/destiny_hero_dreadnought_master.c`
- L60: SS trigger → OPT ignition; cards-mentioning-D-HERO FALSE. Ceiling: OPT add up to 2 Destiny HERO from Deck.

### `DESTINY_HERO_DREADNOUGHT_SERVANT`
- path: `src_custom/activated_effects/destiny_hero_dreadnought_servant.c`
- L89: GY banish destroy on Lv8 D-HERO SS FALSE. Ceiling: FromHand if control D-HERO or Field Spell → SS, destroy 1, add Poly.

### `DESTINY_HERO_DREAMER`
- path: `src_custom/activated_effects/destiny_hero_dreamer.c`
- L45: Damage Step battle protect + banish-on-leave need battle/GY hooks. Ceiling: GY ignition SS when Dreamer in GY + empty monster zone.

### `DESTINY_HERO_DRILLDARK`
- path: `src_custom/activated_effects/destiny_hero_drilldark.c`
- L64: on-Summon trigger + piercing need summon/battle hooks. Ceiling: OPT SS 1 D-HERO from hand with ATK≤ this card's ATK.

### `DESTINY_HERO_DUSKTOPIA`
- path: `src_custom/activated_effects/destiny_hero_dusktopia.c`
- L45: Fusion on Summon + no battle damage need fusion/battle hooks. Ceiling: OPT mark target unk4 cannot destroy until EP clear hook.

### `DESTINY_HERO_DYNATAG`
- path: `src_custom/activated_effects/destiny_hero_dynatag.c`
- L15: Damage Step no-battle-damage + GY banish ATK boost use FromHand path. Ceiling: not field-ignition activatable here.
- L54: no battle damage from that battle not wired; both players 1000.

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

### `EHREN_LIGHTSWORN_MONK`
- path: `src_custom/activated_effects/ehren_lightsworn_monk.c`
- L12: battle shuffle + End Phase mill 3 need battle/phase hooks. Ceiling: not ignition-activatable here; upgrade: battle + EP mill.

### `EL_SHADDOLL_MESHAHRAIL`
- path: `src_custom/activated_effects/el_shaddoll_meshahrail.c`
- L74: unaffected-by-lower-Lv/R + GY SS Shaddoll need continuous/send hooks. Ceiling: OPT pay 800 → add 1 Shaddoll or Void S/T from Deck.

### `EL_SHADDOLL_WENDIGO`
- path: `src_custom/activated_effects/el_shaddoll_wendigo.c`
- L45: until end of turn clear + vs Special Summoned only need battle hooks. Ceiling: mark unk4 on own monster as battle-destroy stand-in.
- L87: quick battle protection + GY add Shaddoll S/T need chain/send hooks. Ceiling: OPT mark 1 own monster unk4.

### `ELDER_ENTITY_NORDEN`
- path: `src_custom/activated_effects/elder_entity_norden.c`
- L73: banish-when-leaves needs leave-field hook; unk4 marks negated.
- L124: SS-trigger timing + banish-when-leaves need summon/leave hooks. Ceiling: OPT SS Lv≤4 from GY face-up DEF with unk4 negated mark.

### `ELEMENTAL_HERO_AQUA_NEOS`
- path: `src_custom/activated_effects/elemental_hero_aqua_neos.c`
- L20: Contact fusion + End Phase Extra Deck shuffle need fusion/EP hooks. Ceiling: OPT discard 1, then destroy 1 random opponent hand card.

### `ELEMENTAL_HERO_BLAZEMAN`
- path: `src_custom/activated_effects/elemental_hero_blazeman.c`
- L222: on-summon does not consume effectUsedThisTurn — that flag is only for the menu activated effect (popup_2). Otherwise popup_2 can never fire the turn Blazeman is summoned.

### `ELEMENTAL_HERO_BRAVE_NEOS`
- path: `src_custom/activated_effects/elemental_hero_brave_neos.c`
- L67: +100 ATK per Neo-Spacian/HERO in GY + battle-destroy search gate need stat/battle hooks. Ceiling: OPT add 1 Neos/HERO Spell/Trap from Deck.

### `ELEMENTAL_HERO_CHAOS_NEOS`
- path: `src_custom/activated_effects/elemental_hero_chaos_neos.c`
- L88: EP shuffle/Set-all + exact 3H/2H/1H/0H branch table FALSE. Ceiling: OPT 3 coin → destroy heads-count opp monsters.

### `ELEMENTAL_HERO_COSMO_NEOS`
- path: `src_custom/activated_effects/elemental_hero_cosmo_neos.c`
- L72: activation lock / End Phase field wipe FALSE. Ceiling: OPT destroy all opp Spell/Trap.

### `ELEMENTAL_HERO_DARK_NEOS`
- path: `src_custom/activated_effects/elemental_hero_dark_neos.c`
- L50: contact Fusion + End Phase Extra shuffle need fusion/phase hooks.

### `ELEMENTAL_HERO_GAIA`
- path: `src_custom/activated_effects/elemental_hero_gaia.c`
- L49: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.

### `ELEMENTAL_HERO_GLOW_NEOS`
- path: `src_custom/activated_effects/elemental_hero_glow_neos.c`
- L47: cannot-attack mark via unk4.
- L50: direct-attack mark via unk4.
- L115: Contact Fusion + EP Extra return FALSE. Ceiling: OPT destroy 1 face-up opp + type-branch marks.

### `ELEMENTAL_HERO_GRAND_NEOS`
- path: `src_custom/activated_effects/elemental_hero_grand_neos.c`
- L95: Contact fusion + End Phase Extra Deck shuffle need fusion/EP hooks. Ceiling: OPT bounce 1 opponent monster to hand.

### `ELEMENTAL_HERO_GREAT_TORNADO`
- path: `src_custom/activated_effects/elemental_hero_great_tornado.c`
- L26: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.atk/def that the stat pipeline already computed for zone.

### `ELEMENTAL_HERO_ICE_EDGE`
- path: `src_custom/activated_effects/elemental_hero_ice_edge.c`
- L59: direct-attack grant this turn; cleared in UnlockCardsInRow.

### `ELEMENTAL_HERO_LADY_HEAT`
- path: `src_custom/activated_effects/elemental_hero_lady_heat.c`
- L45: CanActivate runs before the menu flips a face-down activator

### `ELEMENTAL_HERO_MAGMA_NEOS`
- path: `src_custom/activated_effects/elemental_hero_magma_neos.c`
- L42: continuous 400/field + EP shuffle/bounce field need permanent/EP hooks. Ceiling: OPT refresh tempStage from field card count.

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
- L86: contact Fusion + End Phase Extra shuffle + field shuffle need fusion/phase hooks. Ceiling: OPT destroy all S/T on field.

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

### `ENRAGED_BATTLE_OX`
- path: `src_custom/activated_effects/enraged_battle_ox.c`
- L12: piercing battle damage needs battle damage gate. Ceiling: not ignition-activatable here; upgrade: permanent/battle overlay.

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

### `EVIL_HERO_INFERNAL_GAINER`
- path: `src_custom/activated_effects/evil_hero_infernal_gainer.c`
- L57: second Standby Phase GY return needs turn/Standby hook; unk4=2 marks extra attack stand-in. Ceiling: banish self → target Fiend unk4=2.
- L110: Main Phase 1 gate + second Standby GY return need phase/Standby hooks. Ceiling: OPT banish self → mark 1 Fiend unk4 for extra attack stand-in.

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

### `GANDORA_X_THE_DRAGON_OF_DESTRUCTION`
- path: `src_custom/activated_effects/gandora_x_the_dragon_of_destruction.c`
- L101: on-NS/SS-from-hand wipe + EP self-destroy need summon/EP hooks. Ceiling: OPT destroy all other monsters + burn highest original ATK + set ATK.
- L129: set ATK = damage via tempStage (~500/unit); EP self-destroy FALSE.

### `GATE_GUARDIANS_COMBINED`
- path: `src_custom/activated_effects/gate_guardians_combined.c`
- L102: negate-on-target + leave-field SS FALSE. Ceiling: OPT destroy 1 opp card (negate stand-in).

### `GLADIATOR_BEAST_ANDABATA`
- path: `src_custom/activated_effects/gladiator_beast_andabata.c`
- L135: Extra Deck return + Lv≤7 GB Fusion Extra SS need ED/Fusion APIs.
- L158: contact Fusion SS Lv≤7 GB Fusion from Extra needs Extra API. Ceiling: OPT tag-out → SS 2 different GB from Deck.

### `GLADIATOR_BEAST_ATTORIX`
- path: `src_custom/activated_effects/gladiator_beast_attorix.c`
- L130: on-GB-SS name/Level copy + end-of-BP battled tag gate need summon/ battle hooks. Ceiling: OPT send 1 other GB from Deck to GY (unkTwo name copy) or tag-out shuffle→SS.
- L157: copied name/Level until End Phase needs name-override hook; unkTwo stores sent card id as stand-in.

### `GLADIATOR_BEAST_AUGUSTUS`
- path: `src_custom/activated_effects/gladiator_beast_augustus.c`
- L48: GB-SS trigger + end-of-BP tag-out need summon/battle hooks. Ceiling: OPT SS 1 other GB from hand in DEF.

### `GLADIATOR_BEAST_BESTIARI`
- path: `src_custom/activated_effects/gladiator_beast_bestiari.c`
- L192: GB-tag SS destroy trigger + end-of-BP battled gate need summon/ battle hooks. Ceiling: OPT destroy 1 opp S/T, else tag-out shuffle→SS.

### `GLADIATOR_BEAST_CLAUDIUS`
- path: `src_custom/activated_effects/gladiator_beast_claudius.c`
- L61: double BP + opp-effect trigger FALSE. Ceiling: OPT SS Gladiator Beast from Deck (opp effect stand-in).

### `GLADIATOR_BEAST_DAREIOS`
- path: `src_custom/activated_effects/gladiator_beast_dareios.c`
- L179: Link Summon trigger + BP protect + Link Material lock FALSE. Ceiling: OPT SS Lv≤4 GB from hand/GY, or any GB from Deck if opp has monster.

### `GLADIATOR_BEAST_DARIUS`
- path: `src_custom/activated_effects/gladiator_beast_darius.c`
- L175: GB-tag SS revive trigger + leave-field shuffle + end-BP tag need summon/leave/battle hooks. Ceiling: OPT SS GB from GY negated, else tag-out.

### `GLADIATOR_BEAST_DOMITIANUS`
- path: `src_custom/activated_effects/gladiator_beast_domitianus.c`
- L133: Quick negate/destroy + attack-redirect FALSE; end-BP battled gate missing. Ceiling: OPT tag-out → SS 1–2 GB from Deck.

### `GLADIATOR_BEAST_DRAGASES`
- path: `src_custom/activated_effects/gladiator_beast_dragases.c`
- L157: battle indestruct + opp chain block + end-of-BP battled gate need battle hooks. Ceiling: OPT GB tag-out → SS 2 different from Deck.

### `GLADIATOR_BEAST_EQUESTE`
- path: `src_custom/activated_effects/gladiator_beast_equeste.c`
- L158: on-GB-tag SS add trigger + end-of-BP battled gate need summon/battle hooks. Ceiling: OPT add 1 GB from GY to hand, else tag-out shuffle→SS.

### `GLADIATOR_BEAST_GISTEL`
- path: `src_custom/activated_effects/gladiator_beast_gistel.c`
- L162: on-GB-SS search + end-BP battled tag gate need summon/battle hooks. Ceiling: OPT search Gladiator S/T, else tag-out. FromHand: reveal+SS both.

### `GLADIATOR_BEAST_GYZARUS`
- path: `src_custom/activated_effects/gladiator_beast_gyzarus.c`
- L183: Extra Deck return needs ED API; deck-top stand-in like other GB tags.
- L308: Contact SS destroy trigger + end-BP Extra tag need summon/battle/ Extra hooks. Ceiling: OPT destroy up to 2 monsters, else tag-out → SS 2.

### `GLADIATOR_BEAST_HERAKLINOS`
- path: `src_custom/activated_effects/gladiator_beast_heraklinos.c`
- L148: either-turn chain negate needs chain hook. Ceiling: OPT discard 1 → destroy 1 opponent card.

### `GLADIATOR_BEAST_HOPLOMUS`
- path: `src_custom/activated_effects/gladiator_beast_hoplomus.c`
- L110: end-of-Battle-Phase + attacked/was-attacked gate + DEF 2400 on GB tag-SS need battle/end-BP hooks. Ceiling: OPT shuffle self into Deck then SS another Gladiator Beast from Deck.

### `GLADIATOR_BEAST_LANISTA`
- path: `src_custom/activated_effects/gladiator_beast_lanista.c`
- L154: on-SS name copy + end-of-BP tag gate need summon/battle hooks. Ceiling: OPT banish 1 GB from GY (unkTwo name copy) or tag-out.
- L181: copied name until End Phase needs name-override hook; unkTwo stores copied card id as stand-in.

### `GLADIATOR_BEAST_LAQUARI`
- path: `src_custom/activated_effects/gladiator_beast_laquari.c`
- L110: end-of-Battle-Phase + attacked/was-attacked gate + ATK 2100 on GB tag-SS need battle/end-BP hooks. Ceiling: OPT shuffle self into Deck then SS another Gladiator Beast from Deck.

### `GLADIATOR_BEAST_MURMILLO`
- path: `src_custom/activated_effects/gladiator_beast_murmillo.c`
- L235: GB-tag SS destroy trigger + end-of-BP battled gate need summon/ battle hooks. Ceiling: OPT destroy face-up monster, else tag-out shuffle→SS.

### `GLADIATOR_BEAST_NEROKIUS`
- path: `src_custom/activated_effects/gladiator_beast_nerokius.c`
- L135: Extra Deck return + battle protection need ED/battle hooks.
- L158: battle indestruct + opp chain block + end-of-BP gate need battle hooks. Ceiling: OPT tag-out → SS 2 different GB from Deck.

### `GLADIATOR_BEAST_NOXIOUS`
- path: `src_custom/activated_effects/gladiator_beast_noxious.c`
- L130: hand attack-redirect SS + battled tag gate need battle hooks. Ceiling: OPT mill 1 GB from Deck, else tag-out.

### `GLADIATOR_BEAST_SAGITTARII`
- path: `src_custom/activated_effects/gladiator_beast_sagittarii.c`
- L110: end-of-Battle-Phase + battled gate + discard-GB draw 2 on GB-SS need battle/summon hooks. Ceiling: OPT shuffle self into Deck then SS another Gladiator Beast from Deck.

### `GLADIATOR_BEAST_TAMER_EDITOR`
- path: `src_custom/activated_effects/gladiator_beast_tamer_editor.c`
- L70: Extra Deck Fusion SS + immunity + BP tag FALSE. Ceiling: OPT SS Lv≥5 GB from Deck (Extra stand-in).

### `GLADIATOR_BEAST_VESPASIUS`
- path: `src_custom/activated_effects/gladiator_beast_vespasius.c`
- L121: FromHand battle SS + continuous +500 while GB-SS'd + end-BP battled gate need battle/summon hooks. Ceiling: OPT tag-out shuffle→SS.

### `GODDESS_BOW`
- path: `src_custom/activated_effects/goddess_bow.c`
- L12: Hermos fusion + equip + battle-phase negate/second attack need fusion/equip/chain hooks. Ceiling: not ignition-activatable here.

### `GOLDEN_HOMUNCULUS`
- path: `src_custom/activated_effects/golden_homunculus.c`
- L47: continuous +300 ATK/DEF per banished needs permanent stat overlay. Ceiling: OPT refresh sets perm stages ≈ banished*300/500.

### `GORZ_THE_EMISSARY_OF_DARKNESS`
- path: `src_custom/activated_effects/gorz_the_emissary_of_darkness.c`
- L34: damage-gate + Token FALSE. Ceiling: FromHand empty-field SS.

### `GRANMARG_THE_ROCK_MONARCH`
- path: `src_custom/activated_effects/granmarg_the_rock_monarch.c`
- L105: Tribute Summon trigger. Ceiling: once via usage if Set target.

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

### `GRAVEKEEPERS_NOBLEMAN`
- path: `src_custom/activated_effects/gravekeepers_nobleman.c`
- L57: destroyed-by-battle trigger needs battle/destroy hook. Ceiling: OPT SS 1 GK from Deck face-down DEF except Nobleman.
- L87: no DUEL_SUMMON_SPECIAL_FACE_DOWN_DEF — NORMAL_SET stand-in.

### `GRAVEKEEPERS_ORACLE`
- path: `src_custom/activated_effects/gravekeepers_oracle.c`
- L93: Tribute Summon sequence (destroy/flip/ATK) FALSE. Ceiling: OPT destroy up to 2 cards on opp field.
- L110: multi-target picker not wired; auto-destroy up to 2 opp cards.

### `GRAVEKEEPERS_PRIESTESS`
- path: `src_custom/activated_effects/gravekeepers_priestess.c`
- L12: Necrovalley field treatment + GK ATK/DEF boost need continuous hooks. Ceiling: not ignition-activatable here; upgrade: permanent/field overlay.

### `GRAVEKEEPERS_RECRUITER`
- path: `src_custom/activated_effects/gravekeepers_recruiter.c`
- L102: sent-to-GY trigger needs destroy/send hook. Ceiling: once via usage if GK ≤1500 DEF in Deck and hand space.

### `GRAVEKEEPERS_SHAMAN`
- path: `src_custom/activated_effects/gravekeepers_shaman.c`
- L12: DEF per GK in GY + GY effect negate + Necrovalley Field Spell lock need permanent hooks. Ceiling: not ignition-activatable here.

### `GRAVEKEEPERS_SPEAR_SOLDIER`
- path: `src_custom/activated_effects/gravekeepers_spear_soldier.c`
- L12: piercing battle damage needs battle damage gate. Ceiling: not ignition-activatable here; upgrade: permanent/battle/summon gate outside this file.

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
- L49: +200 ATK per GK in GY + destroy-replace need stat/destroy hooks. Ceiling: OPT discard 1 GK monster from hand once via usage (save stand-in).

### `GRAVEKEEPERS_WATCHER`
- path: `src_custom/activated_effects/gravekeepers_watcher.c`
- L15: either-turn chain negate when opp discards needs chain/negation hooks. Ceiling: not field-ignition; discard-from-hand path below.
- L47: negate activation + destroy activated card not wired.

### `GREAT_POSEIDON_BEETLE`
- path: `src_custom/activated_effects/great_poseidon_beetle.c`
- L12: re-attack same target after surviving battle needs battle re-attack hook. Ceiling: not ignition-activatable here.

### `GREEN_BABOON_DEFENDER_OF_THE_FOREST`
- path: `src_custom/activated_effects/green_baboon_defender_of_the_forest.c`
- L81: hand/GY SS when your face-up Beast is destroyed needs destroy trigger hook. Ceiling: GY ignition like Malicious — pay 1000 LP then SS; hand path uses FromHand wire.

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

### `HELIOS_DUO_MEGISTUS`
- path: `src_custom/activated_effects/helios_duo_megistus.c`
- L58: battle-destroy End Phase SS Megistus needs battle/EP hooks. Ceiling: OPT refresh stages from banished-monster count.
- L146: permStage unit is ~500 ATK/DEF each, not exact banished×200 overlay.

### `HELIOS_THE_PRIMORDIAL_SUN`
- path: `src_custom/activated_effects/helios_the_primordial_sun.c`
- L41: continuous ATK/DEF = banished×100 needs permanent overlay. Ceiling: OPT stages ≈ (banished×100)/500.

### `HELIOS_TRICE_MEGISTUS`
- path: `src_custom/activated_effects/helios_trice_megistus.c`
- L58: extra battle + battle-destroy End Phase SS +500 need battle/EP hooks. Ceiling: OPT refresh permStage from banished-monster count.
- L146: permStage unit is ~500 ATK/DEF each, not exact banished×300 overlay.

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
- L12: either-turn Spell negate needs chain hook. Ceiling: not field- ignition activatable here.

### `HOURGLASS_OF_LIFE`
- path: `src_custom/activated_effects/hourglass_of_life.c`
- L11: updateGfx=FALSE — sub_8041CCC refreshes field after popup dismisses.

### `ILLUSION_OF_CHAOS`
- path: `src_custom/activated_effects/illusion_of_chaos.c`
- L135: field bounce→SS DM negate FALSE. Ceiling: FromHand search only.

### `JAIN_LIGHTSWORN_PALADIN`
- path: `src_custom/activated_effects/jain_lightsworn_paladin.c`
- L12: Damage Step +300 ATK and End Phase mill 2 need battle/phase hooks. Ceiling: not ignition-activatable here; upgrade: permanent/battle + EP mill.

### `JAIN_TWILIGHTSWORN_GENERAL`
- path: `src_custom/activated_effects/jain_twilightsworn_general.c`
- L151: until end of turn clear needs EOT tempStage reset hook.
- L229: other-Lightsworn-activated mill 2 needs chain/EP hook. Ceiling: OPT banish 1 Lightsworn from hand/GY → weaken 1 face-up monster.

### `JOWLS_OF_DARK_DEMISE`
- path: `src_custom/activated_effects/jowls_of_dark_demise.c`
- L70: Jowls direct-attack flag; cleared when zone resets

### `JUDGMENT_THE_DRAGON_OF_HEAVEN`
- path: `src_custom/activated_effects/judgment_the_dragon_of_heaven.c`
- L107: 4+ GY Tuners gate + Dragon-only SS lock + End Phase mill 4 need GY/phase hooks. Ceiling: pay half LP → destroy all other field cards.

### `JUNK_SYNCHRON`
- path: `src_custom/activated_effects/junk_synchron.c`
- L123: Normal Summon trigger needs summon hook. Ceiling: once via usage if GY Lv≤2.

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

### `LUMINA_LIGHTSWORN_SUMMONER`
- path: `src_custom/activated_effects/lumina_lightsworn_summoner.c`
- L236: End Phase mill 3 needs EP phase hook.

### `LUMINA_TWILIGHTSWORN_SHAMAN`
- path: `src_custom/activated_effects/lumina_twilightsworn_shaman.c`
- L226: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS.
- L314: EP mill 3 on other LS effect needs End Phase / LS trigger hook.

### `LYLA_LIGHTSWORN_SORCERESS`
- path: `src_custom/activated_effects/lyla_lightsworn_sorceress.c`
- L104: position-lock + End Phase mill 3 need battle/EP hooks. Ceiling: OPT from face-up ATK: change to face-up DEF and destroy 1 opp Spell/Trap.

### `LYLA_TWILIGHTSWORN_ENCHANTRESS`
- path: `src_custom/activated_effects/lyla_twilightsworn_enchantress.c`
- L205: quick effect on Spell/Trap activation + mill 3 when other LS activates need chain/mill hooks. Ceiling: OPT banish LS from hand/GY then destroy 1 face-up Spell/Trap.

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

### `MAGNA_DRAGO`
- path: `src_custom/activated_effects/magna_drago.c`
- L21: battle-damage trigger needs battle hook. Ceiling: OPT +1 stage (~500; printed +200) stand-in.

### `MAJESTIC_MECH_GORYU`
- path: `src_custom/activated_effects/majestic_mech_goryu.c`
- L12: 1-tribute EP self-send + piercing battle damage need summon/battle hooks. Ceiling: not ignition-activatable here.

### `MAJESTY_HYPERION`
- path: `src_custom/activated_effects/majesty_hyperion.c`
- L270: Fairy battle-damage share FALSE. Ceiling: OPT banish Fairy hand/GY → destroy 1 card. FromHand banish Agent → SS.

### `MAN_THRO_TRO`
- path: `src_custom/activated_effects/man_thro_tro.c`
- L21: Ojama Trio monster form is the only token-like field unit today

### `MANJU_OF_THE_TEN_THOUSAND_HANDS`
- path: `src_custom/activated_effects/manju_of_the_ten_thousand_hands.c`
- L113: Normal/Flip Summon trigger needs summon hook. Ceiling: once via usage if Ritual Monster or Ritual Spell in Deck and hand space.

### `MARSHMALLON`
- path: `src_custom/activated_effects/marshmallon.c`
- L12: battle destruction immunity + flip-attack burn need battle hooks. Ceiling: not ignition-activatable here; upgrade: battle damage / destroy gate.

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

### `MICHAEL_THE_ARCH_LIGHTSWORN`
- path: `src_custom/activated_effects/michael_the_arch_lightsworn.c`
- L137: destroy→shuffle Lightsworn + End Phase mill 3 need destroy/EP hooks. Ceiling: pay 1000 LP → banish 1 field card.

### `MILLENNIUM_EYES_RESTRICT`
- path: `src_custom/activated_effects/millennium_eyes_restrict.c`
- L88: chain equip/absorb opp Effect Monster needs chain/control hooks. Ceiling: OPT destroy 1 opp monster.

### `MINERVA_LIGHTSWORN_MAIDEN`
- path: `src_custom/activated_effects/minerva_lightsworn_maiden.c`
- L124: Normal Summon trigger + mill/End Phase branches need summon/phase hooks. Ceiling: field OPT search LIGHT Dragon Lv≤ distinct LS names in GY.

### `MINERVA_THE_ATHENIAN_LIGHTSWORN`
- path: `src_custom/activated_effects/minerva_the_athenian_lightsworn.c`
- L184: anti-banish continuous + Synchro material count need continuous/synchro hooks. Ceiling: OPT mill LS different Types (up to field LS count), or banish ≤4 LS GY → mill.

### `MINERVA_THE_EXHALTED_LIGHTSWORN`
- path: `src_custom/activated_effects/minerva_the_exhalted_lightsworn.c`
- L69: Xyz detach + destroy-on-death FALSE. Ceiling: OPT mill 3 → draw = Lightsworn among milled.

### `MIRAGE_DRAGON`
- path: `src_custom/activated_effects/mirage_dragon.c`
- L12: opp cannot activate Traps in Battle Phase needs trap-activation gate. Ceiling: not ignition-activatable from this file; upgrade: permanent / duel gate outside activated_effects.

### `MIRROR_FORCE_DRAGON`
- path: `src_custom/activated_effects/mirror_force_dragon.c`
- L12: when targeted for attack/effect trigger needs protection hook. Ceiling: not ignition-activatable here; upgrade: trigger destroy-all.

### `MOLTEN_ZOMBIE`
- path: `src_custom/activated_effects/molten_zombie.c`
- L18: printed trigger is SS from GY. Ceiling: once via usage when Activate runs (summon-dispatch or manual).

### `MONTAGE_DRAGON`
- path: `src_custom/activated_effects/montage_dragon.c`
- L39: ATK = combined sent Levels x 300 needs summon-stat overlay hook. Ceiling: not field-ignition activatable; SS-from-hand uses FromHand path.

### `MORPHTRONIC_BOARDEN`
- path: `src_custom/activated_effects/morphtronic_boarden.c`
- L12: Morphtronic direct attack / battle indestructible continuous need attack and battle hooks. Ceiling: not field-ignition activatable here.

### `MORPHTRONIC_BOOMBOXEN`
- path: `src_custom/activated_effects/morphtronic_boomboxen.c`
- L12: double attack in ATK + DEF negate-attack need battle/position hooks. Ceiling: not ignition-activatable here.

### `MORPHTRONIC_CAMERAN`
- path: `src_custom/activated_effects/morphtronic_cameran.c`
- L128: DEF cannot-be-targeted continuous + battle-destroy trigger need battle/continuous hooks. Ceiling: ATK OPT SS Lv4 Morphtronic from hand/GY.

### `MORPHTRONIC_CELFON`
- path: `src_custom/activated_effects/morphtronic_celfon.c`
- L136: reveal/look UI missing; die roll + SS/add among top N. Ceiling: ATK OPT die→SS Lv≤4 Morphtronic; DEF OPT die→add Morphtronic.

### `MORPHTRONIC_CLOCKEN`
- path: `src_custom/activated_effects/morphtronic_clocken.c`
- L26: +500 ATK per Morph Counter in ATK Position needs stat overlay hook. Ceiling: DEF OPT place unk4 counter, else tribute self → burn 1000*(unk4 or 1).

### `MORPHTRONIC_EARFON`
- path: `src_custom/activated_effects/morphtronic_earfon.c`
- L48: real Tuner flag / Equip double-attack need Synchro/equip hooks. Ceiling: OPT PickZone mark unk4 as Tuner stand-in.
- L95: on-SS Tuner mark + Equip 2-attacks FALSE. Ceiling: OPT PickZone treat face-up as Tuner (unk4).

### `MORPHTRONIC_LANTRON`
- path: `src_custom/activated_effects/morphtronic_lantron.c`
- L12: ATK redirect effect damage + DEF no battle damage when destroyed need damage-redirect and battle-destroy hooks. Ceiling: not ignition here.

### `MORPHTRONIC_MAGNEN`
- path: `src_custom/activated_effects/morphtronic_magnen.c`
- L12: ATK-position highest-ATK-only attack target + DEF-position redirect-attack need battle/position hooks. Ceiling: not ignition here.

### `MORPHTRONIC_MAGNEN_BAR`
- path: `src_custom/activated_effects/morphtronic_magnen_bar.c`
- L55: exactly-2-other ATK gate + DEF cannot-attack need battle hooks. Ceiling: ATK Position OPT refresh tempStage from other ATK/500.

### `MORPHTRONIC_RADION`
- path: `src_custom/activated_effects/morphtronic_radion.c`
- L12: position-based Morphtronic ATK/DEF boost needs continuous stat overlay. Ceiling: not ignition-activatable here; upgrade: permanent position gate.

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
- L92: ATK attack-redirect + DEF battle-immune / on-attack change need battle hooks. Ceiling: OPT change 1 opp ATK monster to DEF.

### `MORPHTRONIC_TELEFON`
- path: `src_custom/activated_effects/morphtronic_telefon.c`
- L176: reveal UI FALSE. Ceiling: ATK die→LP+SS Morph Lv≤roll; DEF die excavate add.

### `MORPHTRONIC_VACUUMEN`
- path: `src_custom/activated_effects/morphtronic_vacuumen.c`
- L24: send Equip → burn + DEF equip-take-control need equip hooks. Ceiling: ATK Position OPT burn 500.

### `MORPHTRONIC_VIDEON`
- path: `src_custom/activated_effects/morphtronic_videon.c`
- L12: position-based ATK/DEF per Equip needs continuous stat overlay. Ceiling: not ignition-activatable here; upgrade: permanent position/equip gate.

### `MUCUS_YOLK`
- path: `src_custom/activated_effects/mucus_yolk.c`
- L21: direct attack + Standby +1000 after battle damage need battle/EP hooks. Ceiling: OPT +2 tempStage (~1000 ATK stand-in for printed Standby gain).

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

### `NEOS_WISEMAN`
- path: `src_custom/activated_effects/neos_wiseman.c`
- L39: battle burn/heal + effect-destroy immunity FALSE. Ceiling: FromHand send Neos+Yubel → SS only.

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

### `ORICHALCOS_SHUNOROS`
- path: `src_custom/activated_effects/orichalcos_shunoros.c`
- L40: battle-trigger SS + Lv4 Normal indestructible need trigger/permanent hooks. Ceiling: OPT +2 tempStage per opp monster (~1000 ATK each).
- L85: SS only when your Normal Monster destroyed by battle needs battle hook. Ceiling: hand SS anytime when zone open.

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
- L59: End Phase mill 2 needs EP hook. Ceiling: Main Phase OPT mill 2.
- L82: +1 tempStage (~500 ATK, not exact +200); until opp EP clear needs hook.

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
- L191: NS/flip + other-Lightsworn mill 3 need summon/chain hooks. Ceiling: OPT banish LS from hand/GY then banish 1 field card; upgrade: NS/flip timing + mill-on-other-LS-effect hook.

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

### `SILENT_MAGICIAN_LV4`
- path: `src_custom/activated_effects/silent_magician_lv4.c`
- L70: Spell Counter place/ATK + Standby-after-5th counter need draw/ counter hooks. Ceiling: OPT send self → SS Silent Magician LV8 from hand/Deck.

### `SILENT_MAGICIAN_LV8`
- path: `src_custom/activated_effects/silent_magician_lv8.c`
- L12: continuous immunity to opponent Spell effects needs spell-target gate. Ceiling: not ignition-activatable here; upgrade: permanent spell-immune hook.

### `SILENT_SWORDSMAN`
- path: `src_custom/activated_effects/silent_swordsman.c`
- L113: Standby +500 + Quick Spell negate need phase/chain hooks. Ceiling: OPT +1 tempStage (~500 ATK), else OPT destroy 1 Spell.

### `SILENT_SWORDSMAN_LV3`
- path: `src_custom/activated_effects/silent_swordsman_lv3.c`
- L70: spell negate continuous + summon/flip turn gate need hooks. Ceiling: Standby OPT send self → SS LV5 from hand/Deck.

### `SILENT_SWORDSMAN_LV5`
- path: `src_custom/activated_effects/silent_swordsman_lv5.c`
- L70: unaffected by opp Spell effects + Standby-after-direct-damage gate need spell/phase hooks. Ceiling: OPT send self → SS LV7 from hand/Deck.

### `SILENT_SWORDSMAN_LV7`
- path: `src_custom/activated_effects/silent_swordsman_lv7.c`
- L12: continuous negate all Spell effects needs field-wide spell gate. Ceiling: not ignition-activatable here; upgrade: permanent spell-negate hook.

### `SILENT_SWORDSMAN_ZERO`
- path: `src_custom/activated_effects/silent_swordsman_zero.c`
- L23: Standby Level + Sarcophagus negate need phase/chain hooks. Ceiling: OPT +1 Level mark (unkTwo) + +1 tempStage ATK stand-in.

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

### `SPELL_STRIKER`
- path: `src_custom/activated_effects/spell_striker.c`
- L82: direct attack + no self battle damage need battle/attack hooks. Ceiling: not field-ignition activatable; SS-from-hand uses FromHand path.

### `SPINED_GILLMAN`
- path: `src_custom/activated_effects/spined_gillman.c`
- L32: continuous +400 ATK needs permanent overlay. Ceiling: OPT +1 stage (~500) to each Fish/SS/Aqua you control.

### `STARDUST_DRAGON`
- path: `src_custom/activated_effects/stardust_dragon.c`
- L12: Quick Effect tribute-negate-destroy + End Phase GY SS need chain and EP hooks. Ceiling: not ignition-activatable here.

### `SUBSTITOAD`
- path: `src_custom/activated_effects/substitoad.c`
- L103: Frog battle protection not applied; upgrade: battle-destroy immunity.

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

### `THE_CALCULATOR`
- path: `src_custom/activated_effects/the_calculator.c`
- L40: continuous ATK = levels×300 needs permanent overlay. Ceiling: OPT refresh perm stages ≈ (levels×300)/500.

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

### `THESTALOS_THE_FIRESTORM_MONARCH`
- path: `src_custom/activated_effects/thestalos_the_firestorm_monarch.c`
- L55: Tribute Summon trigger needs summon hook. Ceiling: once via usage if opp hand.

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

### `TREEBORN_FROG`
- path: `src_custom/activated_effects/treeborn_frog.c`
- L95: Standby Phase GY trigger needs phase hook + GY-menu wire. Ceiling: GY ignition when no S/T, no Treeborn on field, empty monster zone (Malicious pattern).

### `TRISHULA_DRAGON_OF_THE_ICE_BARRIER`
- path: `src_custom/activated_effects/trishula_dragon_of_the_ice_barrier.c`
- L114: Synchro Summon trigger needs synchro hook. Ceiling: once via usage banish random opp hand + 1 field + 1 GY when available.

### `TROOP_DRAGON`
- path: `src_custom/activated_effects/troop_dragon.c`
- L21: battle-destroy→GY trigger. Ceiling: once via usage.

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

### `TURBO_ROCKET`
- path: `src_custom/activated_effects/turbo_rocket.c`
- L12: battle destruction immunity + post-damage burn need battle hooks. Ceiling: not ignition-activatable here; upgrade: battle damage / destroy gate.

### `TURBO_SYNCHRON`
- path: `src_custom/activated_effects/turbo_synchron.c`
- L12: attack-target DEF change + battle-damage SS from hand need battle hooks. Ceiling: not ignition-activatable here.

### `TYRANNO_INFINITY`
- path: `src_custom/activated_effects/tyranno_infinity.c`
- L52: original ATK = banished Dinos×1000 needs permanent overlay. Ceiling: OPT stages ≈ (count×1000)/500.

### `TYRANT_BURST_DRAGON`
- path: `src_custom/activated_effects/tyrant_burst_dragon.c`
- L12: multi-attack + equip-to-monster need battle/equip continuous hooks. Ceiling: not ignition-activatable here; upgrade: permanent battle/equip gate.

### `ULTIMATE_ANCIENT_GEAR_GOLEM`
- path: `src_custom/activated_effects/ultimate_ancient_gear_golem.c`
- L51: piercing + attack S/T lock + on-destroy SS need battle/destroy hooks. Ceiling: OPT SS Ancient Gear Golem from GY.

### `ULTIMATE_CONDUCTOR_TYRANNO`
- path: `src_custom/activated_effects/ultimate_conductor_tyranno.c`
- L194: multi-attack + DEF burn/send need battle hooks. Ceiling: OPT destroy 1 of your monsters → flip all opp face-up monsters face-down DEF.

### `ULTIMATE_OBEDIENT_FIEND`
- path: `src_custom/activated_effects/ultimate_obedient_fiend.c`
- L12: solo-field + empty-hand attack restriction needs attack gate hook. Ceiling: not field-ignition activatable here.

### `ULTIMATE_TYRANNO`
- path: `src_custom/activated_effects/ultimate_tyranno.c`
- L12: multi-attack + Tyranno-only battle phase gate need battle hooks. Ceiling: not field-ignition activatable here.

### `VENOM_BOA`
- path: `src_custom/activated_effects/venom_boa.c`
- L87: cannot-attack-this-turn needs attack gate on unk4.

### `VENOM_SNAKE`
- path: `src_custom/activated_effects/venom_snake.c`
- L87: cannot-attack-this-turn needs attack gate on unk4.

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

### `WARM_WORM`
- path: `src_custom/activated_effects/warm_worm.c`
- L18: printed trigger is when destroyed. Ceiling: once via usage.

### `WEISS_LIGHTSWORN_ARCHFIEND`
- path: `src_custom/activated_effects/weiss_lightsworn_archfiend.c`
- L167: sent-from-Deck-to-GY trigger needs mill/send hook. Ceiling: field OPT SS 1 other Lightsworn from GY.

### `WHITE_HORNED_DRAGON`
- path: `src_custom/activated_effects/white_horned_dragon.c`
- L79: on-Normal/Special Summon trigger needs summon hook. Ceiling: OPT banish up to 5 opp GY Spells + tempStage once via usage.
- L101: +1 tempStage per banished (~500 ATK each, not exact +300).

### `X_SABER_AIRBELLUM`
- path: `src_custom/activated_effects/x_saber_airbellum.c`
- L12: direct-attack battle-damage trigger needs battle hook. Ceiling: not ignition-activatable here; upgrade: battle end discard.

### `YAMORIMORI`
- path: `src_custom/activated_effects/yamorimori.c`
- L124: GY ignition needs GY-menu wire. Ceiling: banish self from GY + own Reptile + opp face-up present → destroy opp face-up monster.

### `ZERADIAS_HERALD_OF_HEAVEN`
- path: `src_custom/activated_effects/zeradias_herald_of_heaven.c`
- L13: destroy self when Sanctuary absent needs continuous field check. Ceiling: not ignition-activatable here; upgrade: permanent maintenance hook.

## permanent (114)

### `AMAZONESS_TIGER`
- path: `src_custom/permanent_effects/amazoness_tiger.c`
- L30: normal hand summon copies isFaceUp=0; attack-position monsters still count

### `AMEBA`
- path: `src_custom/permanent_effects/ameba.c`
- L23: AI candidate sim runs real effect code but restores duel state; do not queue burns that survive into the chosen action.
- L72: skip nested UpdateDuelGfxExceptField; caller just refreshed field.

### `ARCANA_FORCE_0_THE_FOOL`
- path: `src_custom/permanent_effects/arcana_force_0_the_fool.c`
- L48: battle indestructible + targeting immunity need battle/target hooks.

### `ARCANA_FORCE_EX_THE_DARK_RULER`
- path: `src_custom/permanent_effects/arcana_force_ex_the_dark_ruler.c`
- L94: Heads second attack FALSE; Tails wipe only when other cards exist.
- L115: second attack + forced DEF at EP need battle hooks.

### `ARCANA_FORCE_EX_THE_LIGHT_RULER`
- path: `src_custom/permanent_effects/arcana_force_ex_the_light_ruler.c`
- L100: Tails negate FALSE; Heads only when GY→hand legal.
- L125: Tails Quick negate + battle add need chain/battle hooks.

### `ARCANA_FORCE_I_THE_MAGICIAN`
- path: `src_custom/permanent_effects/arcana_force_i_the_magician.c`
- L64: +1 tempStage (~500 ATK) on-summon; spell-trigger double ATK not wired.
- L69: tails LP heal on spell activation not wired; on-summon +500 opp LP only.

### `ARCANA_FORCE_III_THE_EMPRESS`
- path: `src_custom/permanent_effects/arcana_force_iii_the_empress.c`
- L48: opp Normal Summon SS/discard triggers need summon hooks; unk4 only.

### `ARCANA_FORCE_IV_THE_EMPEROR`
- path: `src_custom/permanent_effects/arcana_force_iv_the_emperor.c`
- L86: ±500 ATK uses tempStage (~500/stage); only your Arcana Force on field.

### `ARCANA_FORCE_THE_CHAOS_RULER`
- path: `src_custom/permanent_effects/arcana_force_the_chaos_ruler.c`
- L162: true trigger is Special Summon; on-summon coin stand-in covers SS path.
- L198: Light Barrier opp-activation lock needs continuous field hook.

### `ARCANA_FORCE_VI_THE_LOVERS`
- path: `src_custom/permanent_effects/arcana_force_vi_the_lovers.c`
- L48: tribute engine not wired — unk4 marks double-tribute / no-tribute only.

### `ARCANA_FORCE_VII_THE_CHARIOT`
- path: `src_custom/permanent_effects/arcana_force_vii_the_chariot.c`
- L125: battle SS destroyed monster needs battle-end hook; unk4=1 only.
- L130: tails control switch is immediate; heads steal not wired.

### `ARCANA_FORCE_XIV_TEMPERANCE`
- path: `src_custom/permanent_effects/arcana_force_xiv_temperance.c`
- L48: hand discard battle-damage cancel + halve damage need battle hooks.

### `ARCANA_FORCE_XVIII_THE_MOON`
- path: `src_custom/permanent_effects/arcana_force_xviii_the_moon.c`
- L48: Standby Moon Token / End Phase give-control need turn hooks; unk4 only.

### `ARCANA_FORCE_XXI_THE_WORLD`
- path: `src_custom/permanent_effects/arcana_force_xxi_the_world.c`
- L48: skip-turn / opp GY-to-hand need turn hooks; unk4 marks coin only.

### `AURKUS_LIGHTSWORN_DRUID`
- path: `src_custom/permanent_effects/aurkus_lightsworn_druid.c`
- L44: Lightsworn target protection + true End Phase mill need turn hooks; on-summon mill 2 is the End-Phase stand-in.

### `BLUE_EYES_ALTERNATIVE_WHITE_DRAGON`
- path: `src_custom/permanent_effects/blue_eyes_alternative_white_dragon.c`
- L50: BEWD stays in hand as a visible cost; only the alt card is cleared

### `BLUE_EYES_SHINING_DRAGON`
- path: `src_custom/permanent_effects/blue_eyes_shining_dragon.c`
- L68: in-place BEUD zone replacement; Duel_SpecialSummon* only fills empty zones

### `BREAKER_THE_MAGICAL_WARRIOR`
- path: `src_custom/permanent_effects/breaker_the_magical_warrior.c`
- L15: hand normal summon copies isFaceUp=0; attack-position monsters still count
- L40: placement hook is hand normal/tribute summon only — special summons use duel_helpers

### `CANNONBALL_SPEAR_SHELLFISH`
- path: `src_custom/permanent_effects/cannonball_spear_shellfish.c`
- L8: spell-immunity while Umi is face-up needs Duel_IsCardActivationBlocked / targeting gate for this zone; no self-activation hook exists.

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

### `DESTINY_HERO_DEFENDER`
- path: `src_custom/permanent_effects/destiny_hero_defender.c`
- L8: opp Standby draw while face-up DEF needs turn_effect hook.

### `DESTINY_HERO_DOGMA`
- path: `src_custom/permanent_effects/destiny_hero_dogma.c`
- L77: true trigger is opp next Standby after 3-tribute SS; on-summon halve LP once.

### `DESTINY_HERO_DOOM_OVERLORD`
- path: `src_custom/permanent_effects/destiny_hero_doom_overlord.c`
- L327: banish-until-Standby = permanent banish; DARK HERO SS lock not wired.

### `DESTINY_HERO_DOUBLE_DUDE`
- path: `src_custom/permanent_effects/destiny_hero_double_dude.c`
- L8: double attack + destroyed Standby 2 Tokens need battle/turn hooks.

### `DESTINY_HERO_DRAWHAND`
- path: `src_custom/permanent_effects/destiny_hero_drawhand.c`
- L70: next Standby GY revive + banish-on-leave need phase/GY hooks.
- L98: HERO-effect SS gate not checked; on-summon mutual draw stand-in.

### `DESTINY_HERO_DREAD_SERVANT`
- path: `src_custom/permanent_effects/destiny_hero_dread_servant.c`
- L8: Clock Tower counters + battle-destroy S/T need NS/battle hooks.

### `DESTINY_HERO_DREADMASTER`
- path: `src_custom/permanent_effects/destiny_hero_dreadmaster.c`
- L185: Clock Tower Prison gate + battle protection skipped; on-summon stand-in.
- L216: D-HERO indestructible + no battle damage this turn need continuous hooks.

### `DRAGON_MASTER_MAGIA`
- path: `src_custom/permanent_effects/dragon_master_magia.c`
- L8: Quick negate-by-card-type needs chain/OPT hooks.

### `DRAGON_SPIRIT_OF_WHITE`
- path: `src_custom/permanent_effects/dragon_spirit_of_white.c`
- L59: Quick Tribute → SS Blue-Eyes from hand needs tribute/summon hooks.

### `EL_SHADDOLL_ANOYATYLLIS`
- path: `src_custom/permanent_effects/el_shaddoll_anoyatyllis.c`
- L126: SS-from-hand/GY via S/T lock needs continuous summon gate.

### `EL_SHADDOLL_APKALLONE`
- path: `src_custom/permanent_effects/el_shaddoll_apkallone.c`
- L258: battle indestructible needs battle hook.

### `EL_SHADDOLL_CONSTRUCT`
- path: `src_custom/permanent_effects/el_shaddoll_construct.c`
- L194: battle vs SS monster destroy needs Damage Step hook.

### `EL_SHADDOLL_GRYSTA`
- path: `src_custom/permanent_effects/el_shaddoll_grysta.c`
- L126: negate opp Special Summon + send Shaddoll from hand need SS chain hook.

### `EL_SHADDOLL_SHEKHINAGA`
- path: `src_custom/permanent_effects/el_shaddoll_shekhinaga.c`
- L126: negate SS monster effect + send Shaddoll need effect-chain hook.

### `EL_SHADDOLL_WINDA`
- path: `src_custom/permanent_effects/el_shaddoll_winda.c`
- L126: opp destroy immunity + SS-once lock need continuous hooks.

### `ELEMENTAL_HERO_AIR_NEOS`
- path: `src_custom/permanent_effects/elemental_hero_air_neos.c`
- L44: End Phase shuffle to Extra Deck needs turn_effect hook — ApplyDynamicZoneStats only.

### `ELEMENTAL_HERO_CAPTAIN_GOLD`
- path: `src_custom/permanent_effects/elemental_hero_captain_gold.c`
- L68: with Skyscraper active, prefer normal summon as a 2100 beater

### `ELEMENTAL_HERO_ELECTRUM`
- path: `src_custom/permanent_effects/elemental_hero_electrum.c`
- L67: no removed-from-play zone yet — shuffle banished/exiled monsters back into each owner's deck once Duel_BanishZone (or equivalent) exists.

### `ELEMENTAL_HERO_FLARE_NEOS`
- path: `src_custom/permanent_effects/elemental_hero_flare_neos.c`
- L46: End Phase shuffle to Extra Deck needs turn_effect hook — ApplyDynamicZoneStats only.

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
- L22: no banished-zone storage yet — +300 ATK per banished E-HERO and return up to 2 banished E-HEROes to hand deferred until banish zone exists.

### `EVIL_DRAGON_ANANTA`
- path: `src_custom/permanent_effects/evil_dragon_ananta.c`
- L52: End Phase destroy 1 card needs turn_effect hook — ApplyDynamicZoneStats only.

### `EVIL_HERO_DARK_GAIA`
- path: `src_custom/permanent_effects/evil_hero_dark_gaia.c`
- L8: ATK = fusion materials + flip opp Defense→Attack need fusion/battle hooks.

### `EVIL_HERO_INFERNAL_PRODIGY`
- path: `src_custom/permanent_effects/evil_hero_infernal_prodigy.c`
- L8: empty-field hand SS is FromHand activated; End-Phase tribute draw needs turn hook.

### `EVIL_HERO_INFERNAL_SNIPER`
- path: `src_custom/permanent_effects/evil_hero_infernal_sniper.c`
- L8: spell immunity + Standby burn 1000 (face-up DEF) need continuous/phase hooks.

### `EVIL_HERO_INFERNO_WING`
- path: `src_custom/permanent_effects/evil_hero_inferno_wing.c`
- L8: piercing + battle-destroy burn need Damage Step / battle hooks.

### `EVIL_HERO_INFERNO_WING_BACKFIRE`
- path: `src_custom/permanent_effects/evil_hero_inferno_wing_backfire.c`
- L128: true trigger is Special Summon; on-summon stand-in covers SS path.
- L149: HERO battle-destroy 2100 burn needs battle-end hook.

### `EVIL_HERO_MALICIOUS_EDGE`
- path: `src_custom/permanent_effects/evil_hero_malicious_edge.c`
- L8: piercing + 1-tribute summon gate need battle/summon hooks.

### `EVIL_HERO_MALICIOUS_FIEND`
- path: `src_custom/permanent_effects/evil_hero_malicious_fiend.c`
- L8: forced attack + face-up Attack Position need battle redirect hooks.

### `EVIL_HERO_WILD_CYCLONE`
- path: `src_custom/permanent_effects/evil_hero_wild_cyclone.c`
- L8: attack S/T lock + battle-damage destroy face-down S/T need battle/chain hooks.

### `EXECUTOR_MAKYURA`
- path: `src_custom/permanent_effects/executor_makyura.c`
- L93: most non-zero trapEffect values are chain-only; allow continuous exceptions.

### `FIRE_PRINCESS`
- path: `src_custom/permanent_effects/fire_princess.c`
- L37: normal hand summon copies isFaceUp=0; attack-position monsters still count

### `GANDORA_X_THE_DRAGON_OF_DEMOLITION`
- path: `src_custom/permanent_effects/gandora_x_the_dragon_of_demolition.c`
- L118: End Phase half LP needs EP hook; on-summon wipe only here.
- L146: set ATK = damage via tempStage (~500/unit).

### `GARONITH_LIGHTSWORN_DRAGON`
- path: `src_custom/permanent_effects/garonith_lightsworn_dragon.c`
- L90: End Phase mill 3 + piercing need turn/battle hooks — ApplyDynamicZoneStats only.

### `GAROTH_LIGHTSWORN_WARRIOR`
- path: `src_custom/permanent_effects/garoth_lightsworn_warrior.c`
- L113: true trigger is other LS mills; on-summon mill 2 + draw LS is stand-in.

### `GLADIATOR_BEAST_ALEXANDER`
- path: `src_custom/permanent_effects/gladiator_beast_alexander.c`
- L8: spell immunity + GB tag-out need continuous/battle-end hooks.

### `GLADIATOR_BEAST_DIMACARI`
- path: `src_custom/permanent_effects/gladiator_beast_dimacari.c`
- L8: double attack + GB tag-out need battle-end/summon hooks.

### `GLADIATOR_BEAST_ESSEDARII`
- path: `src_custom/permanent_effects/gladiator_beast_essedarii.c`
- L8: Contact Fusion has no permanent ignition path.

### `GLADIATOR_BEAST_GAIODIAZ`
- path: `src_custom/permanent_effects/gladiator_beast_gaiodiaz.c`
- L8: battle DEF burn + GB tag-out need battle-end/destroy hooks.

### `GLADIATOR_BEAST_OCTAVIUS`
- path: `src_custom/permanent_effects/gladiator_beast_octavius.c`
- L139: GB-tag SS + battle-end tag-out need summon/battle-end hooks.

### `GLADIATOR_BEAST_RETIARI`
- path: `src_custom/permanent_effects/gladiator_beast_retiari.c`
- L110: GB tag-out after battle needs battle-end hook.

### `GLADIATOR_BEAST_SAMNITE`
- path: `src_custom/permanent_effects/gladiator_beast_samnite.c`
- L8: battle search + GB tag-out need battle-end/destroy hooks.

### `GLADIATOR_BEAST_SECUTOR`
- path: `src_custom/permanent_effects/gladiator_beast_secutor.c`
- L8: battle-end tag SS 2 GB from Deck needs battle-end hook.

### `GLADIATOR_BEAST_SPARTACUS`
- path: `src_custom/permanent_effects/gladiator_beast_spartacus.c`
- L95: Hoplomus-only SS + GB tag-out need summon/battle-end hooks.

### `GLADIATOR_BEAST_TORAX`
- path: `src_custom/permanent_effects/gladiator_beast_torax.c`
- L8: GB tag-out draw after battle needs battle-end hook.

### `GLADIATOR_BEAST_TYGERIUS`
- path: `src_custom/permanent_effects/gladiator_beast_tygerius.c`
- L110: GB tag-out + optional discard gate not wired; on-summon search stand-in.

### `GOYO_GUARDIAN`
- path: `src_custom/permanent_effects/goyo_guardian.c`
- L8: battle-destroy SS to your DEF needs battle-end hook.

### `GRANADORA`
- path: `src_custom/permanent_effects/granadora.c`
- L92: unk4==1 means summon effect already fired; 0/2 are fresh normal/special summon

### `GREAT_MAJU_GARZETT`
- path: `src_custom/permanent_effects/great_maju_garzett.c`
- L48: ram_map byte packing can leave u16 fields at odd EWRAM addresses;

### `GRINDER_GOLEM`
- path: `src_custom/permanent_effects/grinder_golem.c`
- L8: hand SS to opp field + Grinder Tokens + NS/Set lock need summon/token hooks.

### `HARPIE_PERFUMER`
- path: `src_custom/permanent_effects/harpie_perfumer.c`
- L134: name becomes Harpie Lady on field/GY needs name-override hook.

### `HARPIES_PET_PHANTASMAL_DRAGON`
- path: `src_custom/permanent_effects/harpies_pet_phantasmal_dragon.c`
- L8: direct attack + Harpie protect + End Phase detach need battle/xyz hooks.

### `HERO_KID`
- path: `src_custom/permanent_effects/hero_kid.c`
- L76: true trigger is Special Summon; on-summon stand-in covers SS path.

### `HORUS_THE_BLACK_FLAME_DRAGON_LV4`
- path: `src_custom/permanent_effects/horus_the_black_flame_dragon_lv4.c`
- L8: control lock + End Phase LV6 SS need continuous/battle-end hooks.

### `HORUS_THE_BLACK_FLAME_DRAGON_LV6`
- path: `src_custom/permanent_effects/horus_the_black_flame_dragon_lv6.c`
- L8: spell immunity + End Phase LV8 SS need continuous/battle-end hooks.

### `JENIS_LIGHTSWORN_MENDER`
- path: `src_custom/permanent_effects/jenis_lightsworn_mender.c`
- L8: End Phase heal/burn after LS mill needs turn_effect hook.

### `JUNK_WARRIOR`
- path: `src_custom/permanent_effects/junk_warrior.c`
- L75: tempStage (~500/stage) on-summon only; no continuous recompute.

### `KNIGHT_OF_PENTACLES`
- path: `src_custom/permanent_effects/knight_of_pentacles.c`
- L72: Tails "destroy when attacked" needs battle-step hook; unk4 tails = no attack only.

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

### `NEO_SPACIAN_FLARE_SCARAB`
- path: `src_custom/permanent_effects/neo_spacian_flare_scarab.c`
- L58: continuous +400 ATK per opp Spell/Trap — ApplyDynamicZoneStats only.

### `OSHALEON`
- path: `src_custom/permanent_effects/oshaleon.c`
- L109: must-attack-this restriction needs attack-gate hook.

### `PETEN_THE_DARK_CLOWN`
- path: `src_custom/permanent_effects/peten_the_dark_clown.c`
- L73: hand takes priority when both are available; deck is the fallback

### `RAVIEL_LORD_OF_PHANTASMS`
- path: `src_custom/permanent_effects/raviel_lord_of_phantasms.c`
- L137: triggers on any monster placement (Normal + Special). Card text says "Normal Summons" only — needs opts.markSpecialSummon check.

### `REPTILIANNE_GARDNA`
- path: `src_custom/permanent_effects/reptilianne_gardna.c`
- L8: destroyed→search Reptilianne needs destroy-to-GY permanent hook.

### `REPTILIANNE_NAGA`
- path: `src_custom/permanent_effects/reptilianne_naga.c`
- L8: battle immunity, ATK-to-0, and EP flip need battle/turn hooks.

### `REPTILIANNE_SERVANT`
- path: `src_custom/permanent_effects/reptilianne_servant.c`
- L74: cannot-be-attacked + NS lock + spell-target destroy need battle/continuous hooks.

### `SHATIEL`
- path: `src_custom/permanent_effects/shatiel.c`
- L51: GetTypeGroup/SetCardInfo would clobber gCardInfo mid-pipeline.

### `SHIRE_LIGHTSWORN_SPIRIT`
- path: `src_custom/permanent_effects/shire_lightsworn_spirit.c`
- L89: End Phase mill 2 needs turn_effect hook — ApplyDynamicZoneStats only.

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

### `THE_DESPAIR_URANUS`
- path: `src_custom/permanent_effects/the_despair_uranus.c`
- L19: GetTypeGroup → SetCardInfo clobbers gCardInfo.atk/def mid-pipeline.
- L96: gCardInfo is already set for this zone by the caller.

### `THE_TRIPPER_MERCURY`
- path: `src_custom/permanent_effects/the_tripper_mercury.c`
- L179: SetCardInfo would reset gCardInfo.atk/def back to printed base.

### `THE_TYRANT_NEPTUNE`
- path: `src_custom/permanent_effects/the_tyrant_neptune.c`
- L59: ram_map byte packing can leave u16 fields at odd EWRAM addresses;
- L455: draw Neptune on the field before popup / trunk picker.

### `THE_WICKED_AVATAR`
- path: `src_custom/permanent_effects/the_wicked_avatar.c`
- L177: after SwitchTurn(), zone POV is still the ended turn until the next UpdateDuelZonePtrs — use gWhoseTurn (new active) not INACTIVE_DUELIST.

### `THE_WICKED_DREADROOT`
- path: `src_custom/permanent_effects/the_wicked_dreadroot.c`
- L30: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.atk/def that the stat pipeline already computed for zone.

### `THUNDER_DRAGON_COLOSSUS`
- path: `src_custom/permanent_effects/thunder_dragon_colossus.c`
- L8: opp search lock + battle/effect destroy→GY-banish need continuous/battle hooks.

### `TIMEAEUS_THE_UNITED_MAGICAL_DRAGON`
- path: `src_custom/permanent_effects/timeaeus_the_united_magical_dragon.c`
- L121: unaffected-after-SS + battle ATK boost need continuous/battle hooks.

### `VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES`
- path: `src_custom/permanent_effects/vennominaga_the_deity_of_poisonous_snakes.c`
- L54: S/T + monster immunity + 3-counter win need continuous/battle hooks.

### `VENNOMINON_THE_KING_OF_POISONOUS_SNAKES`
- path: `src_custom/permanent_effects/vennominon_the_king_of_poisonous_snakes.c`
- L54: battle destroy → banish Reptile + SS self needs battle/GY hook.

### `WULF_LIGHTSWORN_BEAST`
- path: `src_custom/permanent_effects/wulf_lightsworn_beast.c`
- L8: milled-from-Deck Special Summon needs mill/deck-send hook.

### `YOWIE`
- path: `src_custom/permanent_effects/yowie.c`
- L51: opp skip Draw Phase needs turn hook; unk4 marks alone-summon only.

### `ZERIEL`
- path: `src_custom/permanent_effects/zeriel.c`
- L44: GetTypeGroup/SetCardInfo would clobber gCardInfo.atk already computed.
