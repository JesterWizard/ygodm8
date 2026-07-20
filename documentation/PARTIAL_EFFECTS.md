# Partial Effects Backlog

Auto-generated living list of effect files with `ponytail:` ceilings (implemented, but missing hooks / engine pieces).
Find follow-up work here — stubs live in `STUB_EFFECTS.md`.
Rows vanish when all `ponytail:` comments are removed from the file.

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials
```

**Last updated:** 2026-07-20 15:18 UTC  
**Remaining partials:** `130`

## Counts by kind

| Kind | Count |
|------|------:|
| `spell` | 66 |
| `trap` | 9 |
| `activated` | 24 |
| `permanent` | 27 |
| `battle` | 3 |
| `turn` | 1 |
| **total** | **130** |

## spell (66)

### `AMAZONESS_FIGHTING_SPIRIT`
- path: `src_custom/spell_effects/amazoness_fighting_spirit.c`
- L14: Amazoness vs higher-ATK +1000 during damage calculation only needs a battle_effects damage-calc hook (like skyscraper.c) outside this file. Ceiling: face-up continuous only; upgrade: ApplyAmazonessFightingSpiritBattleAtkBoost → if face-up AMAZONESS_FIGHTING_SPIRIT on controller's field, attacker passes Duel_IsAmazonessCard, and defender ATK > attacker ATK, then attacker ATK += 1000.

### `ANCIENT_GEAR_DRILL`
- path: `src_custom/spell_effects/ancient_gear_drill.c`
- L196: no per-card same-turn activation lock. Ceiling: Set Spell can still be activated this turn. Upgrade: turn-scoped cardId/zone lock checked at Spell activation.

### `ANCIENT_GEAR_TANK`
- path: `src_custom/spell_effects/ancient_gear_tank.c`
- L61: stage unit is 500 ATK — applied +500, not printed +600. Ceiling: no fractional stages; upgrade: exact-ATK overlay like BIG_BANG_SHOT after listing ANCIENT_GEAR_TANK in IsActiveDynamicEquipSpellZone.
- L73: destroy→GY burn 600 to opponent needs a field/destroy hook outside this file (OnDynamicEquipZoneAboutToClear / GY send). Ceiling: equip-only works; destroy-burn not wired from this file. Upgrade: destroy-hook → Duel_ChangeLp(INACTIVE_DUELIST, -ANCIENT_GEAR_TANK_DESTROY_BURN).
- L79: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add ANCIENT_GEAR_TANK to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.

### `ARCANA_READING`
- path: `src_custom/spell_effects/arcana_reading.c`
- L108: no dedicated choice UI — A = Heads, B = Tails. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L270: GY banish → Normal Summon 1 Arcana Force needs a GY ignition hook outside this spell file (no in-file graveyard activation path). Ceiling: activation coin effect only; upgrade: GY ignition → banish ARCANA_READING then Duel_NormalSummonFromHand Arcana Force.

### `BACKUP_SQUAD`
- path: `src_custom/spell_effects/backup_squad.c`
- L14: continuous face-up only — damage≥1000 draw listener needs a battle/LP-change hook outside this file (no in-file damage dispatch).

### `BIG_BANG_SHOT`
- path: `src_custom/spell_effects/big_bang_shot.c`
- L76: 3 copies max per side — reuse slot 0 if all busy

### `BOOK_OF_LIFE`
- path: `src_custom/spell_effects/book_of_life.c`
- L61: single-card GY model — banish removes opponent's top graveyard card

### `BURDEN_OF_THE_MIGHTY`
- path: `src_custom/spell_effects/burden_of_the_mighty.c`
- L14: continuous -100 ATK × Level on each face-up opponent monster needs a field-stat / continuous ATK overlay outside this file (no in-file hook into Duel_TryApplyDynamicZoneStats or Refresh overlays). Ceiling: face-up continuous only; upgrade: stat overlay → if face-up BURDEN_OF_THE_MIGHTY then each face-up opp monster ATK -= 100 * level.

### `CALL_OF_THE_MUMMY`
- path: `src_custom/spell_effects/call_of_the_mummy.c`
- L97: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up OPT re-activation may need card_hooks GetSpellType + CALL_OF_THE_MUMMY listed. Ceiling: first-activation OPT works; upgrade: add to NORMAL spell-type list.

### `CHAIN_STRIKE`
- path: `src_custom/spell_effects/chain_strike.c`
- L17: no Chain Link / chain-depth API in this engine (grep ChainLink empty). Ceiling: always unactivatable; upgrade: require link >= 2, burn 400 * link, and forbid activation when multiple copies of this card are already on the chain.

### `CHARGE_OF_THE_LIGHT_BRIGADE`
- path: `src_custom/spell_effects/charge_of_the_light_brigade.c`
- L243: mill helper advances deck top only (no expanded-GY push), matching needle_worm / gravekeepers_servant. Ceiling: milled cards may not appear in GY UI.

### `COCOON_REBIRTH`
- path: `src_custom/spell_effects/cocoon_rebirth.c`
- L60: only the five Chrysalis in-trunk pairs are mapped.

### `COLD_WAVE`
- path: `src_custom/spell_effects/cold_wave.c`
- L16: "activate only at start of Main Phase 1" needs a phase/action counter outside this file (no Main Phase 1-start gate API). Ceiling: activable any time like a normal spell; upgrade: CanActivate → require MP1 + no prior play/set/summon this turn.
- L21: block play/Set of Spell/Trap until next turn needs a shared lock hooked into Duel_IsCardActivationBlocked / set-from-hand (like Wicked Avatar SpellTrap lock). Ceiling: show text + send to GY only; upgrade: arm a Cold Wave turn flag in Duel_IsCardActivationBlocked for TYPE_SPELL/TRAP and Set paths until activator's next Standby, then clear.

### `CONTACT`
- path: `src_custom/spell_effects/contact.c`
- L37: only the five Chrysalis in-trunk pairs are mapped.

### `CONVERT_CONTACT`
- path: `src_custom/spell_effects/convert_contact.c`
- L191: cancel on deck pick auto-sends first Neo-Spacian (activation committed).

### `COURT_OF_JUSTICE`
- path: `src_custom/spell_effects/court_of_justice.c`
- L33: attack-position monsters keep isFaceUp=0 until EOT FlipAtkPosCardsFaceUp.

### `DARK_FUSION`
- path: `src_custom/spell_effects/dark_fusion.c`
- L94: "opponent cannot target the Fusion this turn" needs a turn-scoped targeting-protect flag on the summoned zone (no in-file targeting gate). Ceiling: Fiend Fusion via Poly materials only; upgrade: mark result zone + spell/trap/monster target validators skip it until turn end.
- L124: targeting protect this turn — same ceiling as player path.

### `DARK_MAGIC_INHERITANCE`
- path: `src_custom/spell_effects/dark_magic_inheritance.c`
- L15: no card-description text search — approximate DM/DMG support S/T via name contains "Dark Magician"/"Dark Magic" plus a known support ID list. Ceiling: misses text-only mentions (e.g. cards that only list DM in effect text). Upgrade: description-string helper or generated support bitmask.
- L360: once-per-turn activation not tracked after this normal spell leaves the field (no shared turn-flag RAM editable from this file alone).

### `DARK_MAGIC_VEIL`
- path: `src_custom/spell_effects/dark_magic_veil.c`
- L109: no dedicated hand/GY choice UI — A = hand, B = GY. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `DEDICATION_THROUGH_LIGHT_AND_DARKNESS`
- path: `src_custom/spell_effects/dedication_through_light_and_darkness.c`
- L127: special-face-up sets unk4=2 and blocks DMoC's on-summon effect

### `DIMENSION_FUSION`
- path: `src_custom/spell_effects/dimension_fusion.c`
- L88: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS. Ceiling: local mutate of gRemovedFromPlay; upgrade: add RemoveAt to removed_from_play.c.
- L147: RFP zone is id-list only (no face/position memory). Ceiling: SS face-up ATK via Duel_SpecialSummonMonsterId; upgrade: store zone state on banish + restore on return.

### `DRAGON_RAVINE`
- path: `src_custom/spell_effects/dragon_ravine.c`
- L187: no dedicated choice UI — A = add Dragunity, B = send Dragon to GY. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L405: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up OPT re-activation may need card_hooks GetSpellType + DRAGON_RAVINE listed. Ceiling: first-activation OPT works; upgrade: add to NORMAL spell-type list.

### `DYNAMIC_EQUIP`
- path: `src_custom/spell_effects/dynamic_equip.c`
- L34: gTurnZones uses mirrored columns on opponent rows

### `EL_SHADDOLL_FUSION`
- path: `src_custom/spell_effects/el_shaddoll_fusion.c`
- L98: once-per-turn activation not tracked (no BSS turn flag editable from this file alone). Ceiling: multiple El Shaddoll Fusion per turn possible; upgrade: shared OPT RAM bit / effect_usage once_per_turn.

### `FIELD_BARRIER`
- path: `src_custom/spell_effects/field_barrier.c`
- L43: Field Spell destroy protection + block new Field Spell activation need destroy-gate and Field Spell activation hooks outside this file (no in-file destroy/activate dispatch). Ceiling: continuous face-up + 1-copy control check only; upgrade: LynJump Duel_DestroyZone / Field Spell activate → if face-up FIELD_BARRIER then skip Field Spell destroy and refuse new

### `FORBIDDEN_CHALICE`
- path: `src_custom/spell_effects/forbidden_chalice.c`
- L78: stage unit is 500 ATK — applied +500 until EOT, not printed +400. Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART.
- L81: no per-monster effect-negate flag until EOT (Skill Drain is field-wide only). Ceiling: ATK boost only; upgrade: turn_effect / zone negate bit cleared at ResetTempStagesForFieldCards.

### `FORBIDDEN_DRESS`
- path: `src_custom/spell_effects/forbidden_dress.c`
- L75: stage unit is 500 ATK — applied -500, not printed -600. Ceiling: no fractional stages; upgrade: exact-ATK overlay like ApplyHeatedHeartAtkBonusToCardInfo for -600.
- L84: "cannot be targeted or destroyed by other card effects" this turn needs targeting/destroy immunity flags or a turn_effect clear outside this file (no per-zone protection bit editable here). Ceiling: ATK loss only; upgrade: flag zone until EOT → Duel_SpellMayTargetMonsterZone / Duel_DestroyZone skip when flagged.

### `FORBIDDEN_LANCE`
- path: `src_custom/spell_effects/forbidden_lance.c`
- L75: stage unit is 500 ATK — applied -1000, not printed -800. Ceiling: no fractional temp stages; upgrade: exact-ATK overlay (Riryoku-style delta) cleared at End Phase.
- L85: "unaffected by other Spells/Traps this turn" needs a per-zone immunity flag checked from Duel_ZoneIsImmuneToSpellEffects / trap targeting (IsImmuneToSpellEffectsOnField is card-id permanent only). Ceiling: -ATK via tempStage (clears EOT) only; upgrade: mark zone → treat as immune until ResetTempStages / End Phase, then clear.

### `FUTURE_FUSION`
- path: `src_custom/spell_effects/future_fusion.c`
- L165: hand test copies of the fusion result are not valid materials.

### `GEARTOWN`
- path: `src_custom/spell_effects/geartown.c`
- L87: -1 Tribute for Ancient Gear Normal Summons needs a summon_tribute hook outside this file (no in-file tribute-count dispatch). Ceiling: field face-up only; upgrade: LynJump tribute-count → if face-up GEARTOWN and Duel_CardNameContains(id, "Ancient Gear") then required-1.
- L91: destroy→GY SS 1 Ancient Gear from hand/Deck/GY needs a destroy/ send-to-GY listener outside this file. Ceiling: no trigger from spell file alone; upgrade: destroy-hook → if destroyed id==GEARTOWN then SS matching Ancient Gear.

### `GLADIATOR_BEASTS_BATTLE_GLADIUS`
- path: `src_custom/spell_effects/gladiator_beasts_battle_gladius.c`
- L60: stage unit is 500 ATK — applied +500, not printed +300. Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART after listing GLADIATOR_BEASTS_BATTLE_GLADIUS in IsActiveDynamicEquipSpellZone.
- L72: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add GLADIATOR_BEASTS_BATTLE_GLADIUS to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade: same as H_HEATED_HEART.
- L78: recycle-to-hand when equipped monster returns to Deck (tag-out) and this card is sent to GY needs a return-to-deck / equip-send hook outside this file. Ceiling: equip +ATK only; upgrade: on GB return-to-deck → if linked GLADIATOR_BEASTS_BATTLE_GLADIUS hits GY then Duel_AddDeckCardToHand / GY→hand.

### `GROUND_COLLAPSE`
- path: `src_custom/spell_effects/ground_collapse.c`
- L86: continuous zone lock needs FirstEmptyZoneInRow / PlaceMonster / summon-set validators outside this file (empty isLocked is ignored). Ceiling: face-up continuous + marks/stash only; upgrade: LynJump FirstEmptyZoneInRow (+ AI/player summon cursors) → skip isLocked empty MMZ while face-up GROUND_COLLAPSE; clear marks when it leaves the field.

### `HYSTERIC_SIGN`
- path: `src_custom/spell_effects/hysteric_sign.c`
- L92: no dedicated choice UI — A = Deck, B = GY. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L189: End Phase "sent from hand/field this turn → add up to 3 different Harpie cards from Deck" needs a GY/sent-this-turn + End Phase hook. Ceiling: only on-activate Elegant Egotist search works; upgrade: turn_effect or GY send tracker that opens a multi-pick Harpie deck search.

### `ILLUSION_MAGIC`
- path: `src_custom/spell_effects/illusion_magic.c`
- L136: no dedicated Deck/GY choice UI — A = Deck, B = GY. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L322: once-per-turn activation not tracked (no BSS turn flag editable from this file alone). Ceiling: multiple Illusion Magic per turn possible; upgrade: shared OPT RAM bit / effect_usage once_per_turn.

### `INFERNO_TEMPEST`
- path: `src_custom/spell_effects/inferno_tempest.c`
- L105: activation gate "took ≥3000 Battle Damage from 1 attack" needs a battle-damage listener / flag outside this file (no mid-battle OPT hook editable here). Ceiling: resolve banish whenever activated from hand/backrow; upgrade: battle_damage_hooks → set flag on ≥3000 damage then gate CanActivate.

### `KNIGHTS_TITLE`
- path: `src_custom/spell_effects/knights_title.c`
- L109: special-face-up sets unk4=2 and blocks DMK's on-summon effect

### `LEV_SHADDOLL_FUSION`
- path: `src_custom/spell_effects/lev_shaddoll_fusion.c`
- L14: Extra Deck heavy — on-activate send 1 Fusion from Extra to GY, and ignition (Tribute Fusion / SS Shaddoll Fusion different Attr ATK 0 / OPT / no Extra SS that turn) all need a duel-time Extra Deck browser + SS path. Trunk ExtraDeck_* APIs are deck-builder only. Ceiling: continuous face-up text only; upgrade: Extra Deck pick/send + tribute+SS ignition with OPT flag.

### `LEVEL_TUNING`
- path: `src_custom/spell_effects/level_tuning.c`
- L50: no TempLevel / zone level-mod field (DuelCard has only tempStage; level lives in ROM card data via SetCardInfo). Cannot apply -1 Level here. End Phase restore also needs a turn hook outside this file. Ceiling: printed Level unchanged; upgrade: TempLevel overlay + turn_effect_hooks End Phase clear that restores marked zones.

### `LIGHTSWORN_SABRE`
- path: `src_custom/spell_effects/lightsworn_sabre.c`
- L60: stage unit is 500 ATK — applied +500, not printed +700. Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART (ApplyHeatedHeartAtkBonusToCardInfo) after listing LIGHTSWORN_SABRE in IsActiveDynamicEquipSpellZone.
- L72: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add LIGHTSWORN_SABRE to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.
- L77: Deck-to-GY re-equip (when milled) needs a mill/send-from-deck hook outside this file. Ceiling: equip-from-hand/field only; upgrade: mill path → if LIGHTSWORN_SABRE sent from Deck to GY then PickZone Lightsworn and RegisterDynamicEquip again.

### `MASK_OF_THE_ACCURSED`
- path: `src_custom/spell_effects/mask_of_the_accursed.c`
- L25: attack lock + Standby 500 burn need hooks outside this file. Ceiling: equip registers only (like Raregold Armor without force-target). Upgrade: wire DynamicEquipTargetsMonsterWithSpell(MASK_OF_THE_ACCURSED) into duel_attack_restrictions.c (CannotAttack) and turn_effect_hooks.c (Duel_ChangeLp controller, -MASK_OF_THE_ACCURSED_STANDBY_DAMAGE) — clone

### `METAMORPHOSIS`
- path: `src_custom/spell_effects/metamorphosis.c`
- L85: Extra Deck Special Summon (Fusion of matching Level) needs a duel-time Extra Deck browser + SS path. Trunk ExtraDeck_* APIs are deck-builder only and must not be used mid-duel. Ceiling: tribute-only; upgrade: ExtraDeck duel pick filtered by COLOR_FUSION + level == tributeLevel, then Duel_SpecialSummonMonsterId.

### `MORPHTRONIC_CORD`
- path: `src_custom/spell_effects/morphtronic_cord.c`
- L57: battle-position-change → destroy 1 S/T needs an external position-change hook (monster_action_menu / battle-position paths). Ceiling: equip-only works; destroy trigger not wired from this file. Upgrade: LynJump position-change → if DynamicEquipTargetsMonsterWithSpell (zone, MORPHTRONIC_CORD) then PickZone destroy one S/T.
- L113: not in GetSpellType EQUIP override — PickZone instead of vanilla equip targeting. Ceiling: add MORPHTRONIC_CORD to card_hooks GetSpellType EQUIP list for pre-target cursor; upgrade path: same as H_HEATED_HEART.

### `MORPHTRONIC_RUSTY_ENGINE`
- path: `src_custom/spell_effects/morphtronic_rusty_engine.c`
- L87: destroy-burn (orig ATK to both players) needs a field/destroy hook outside this file (e.g. battle_damage / OnDynamicEquipZoneAboutToClear).

### `MYSTIK_WOK`
- path: `src_custom/spell_effects/mystik_wok.c`
- L92: no dedicated ATK/DEF choice UI — A = ATK, B = DEF. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `NECROVALLEY_THRONE`
- path: `src_custom/spell_effects/necrovalley_throne.c`
- L128: no dedicated choice UI — A = add Gravekeeper's, B = Normal Summon. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L281: no once-per-turn tracker without file BSS / shared OPT flags. Ceiling: can activate multiple Throne copies per turn; upgrade: duel-state OPT bit.

### `NEX`
- path: `src_custom/spell_effects/nex.c`
- L155: duel Extra Deck browser/SS missing (Trunk ExtraDeck_* is deck-builder only). Ceiling: spawn Lv4 Neo form by id when not in Main Deck; upgrade: Extra Deck pick + SS.

### `OIL`
- path: `src_custom/spell_effects/oil.c`
- L232: once-per-turn activation not tracked (no BSS turn flag editable from this spell file alone). Ceiling: can activate multiple Oils per turn; upgrade: shared OPT RAM bit / effect_usage once_per_turn.

### `ONE_DAY_OF_PEACE`
- path: `src_custom/spell_effects/one_day_of_peace.c`
- L24: neither player takes damage until end of opponent's next turn needs an LP/damage gate outside this file (no damage-immunity helper). Ceiling: both draw only; upgrade: turn_effect / ChangeLp hook → skip damage while One Day of Peace lock is active through opponent's next End Phase.

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

### `POWER_FILTER`
- path: `src_custom/spell_effects/power_filter.c`
- L14: SS lock for monsters with ATK ≤1000 needs a CanSpecialSummon / PlaceMonster gate outside this file (no in-file summon dispatch). Ceiling: continuous face-up only; upgrade: LynJump Duel_CardCannotBeSpecialSummoned (or PlaceMonsterFromId) → if face-up POWER_FILTER on field and printed ATK ≤1000 then block.

### `REPTILANNE_RAGE`
- path: `src_custom/spell_effects/reptilanne_rage.c`
- L58: stage unit is 500 ATK — applied +1000, not printed +800. Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART after listing REPTILANNE_RAGE in IsActiveDynamicEquipSpellZone.
- L69: "becomes Reptile-Type" needs a temp-type overlay outside this file (DuelCard has no type field; type lives in ROM via SetCardInfo). Ceiling: equip-only-to-Reptile (already TYPE_REPTILE); upgrade: type overlay → treat equipped target as TYPE_REPTILE while link is active.
- L74: destroy→GY target opp face-up monster -800 ATK needs a field/ destroy hook outside this file (OnDynamicEquipZoneAboutToClear / GY send). Ceiling: equip-only works; GY trigger not wired from this file. Upgrade: destroy-hook → PickZone opp face-up monster → apply -800 ATK overlay (or -2 stages).
- L80: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add REPTILANNE_RAGE to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.

### `REPTILIANNE_SPAWN`
- path: `src_custom/spell_effects/reptilianne_spawn.c`
- L13: no Reptilianne Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. Ceiling: wrong Type/Attribute (Fairy/LIGHT vs Reptile/EARTH); upgrade: add REPTILIANNE_TOKEN card data + art, then swap this define.

### `RETURN_OF_THE_DRAGON_LORDS`
- path: `src_custom/spell_effects/return_of_the_dragon_lords.c`
- L191: GY protect ("banish this instead of destroy Dragon you control") needs a battle/destroy redirect hook checking this card in GY. Ceiling: SS only; upgrade: destroy-protection → if Dragon would be destroyed and RETURN_OF_THE_DRAGON_LORDS in GY, banish it instead.

### `SCAPEGOAT`
- path: `src_custom/spell_effects/scapegoat.c`
- L10: no Sheep Token card id in trunk — MOON_TOKEN is Lv1/0/0 stand-in. Ceiling: wrong Type/Attribute (Fairy/LIGHT vs Beast/EARTH); upgrade: add SHEEP_TOKEN card data + art, then swap this define.
- L74: LockMonsterCardsInRow also blocks Normal Set of monsters. Ceiling: cannot allow Set while blocking Summon without a menu hook that distinguishes Set vs Summon; upgrade: Set path unlocks hand briefly.
- L77: token tribute-lock is only via isLocked — not all tribute paths honor it, and Tokens can still be used for non-Tribute costs. Ceiling: best-effort lockMonster; upgrade: tribute validator excludes SCAPEGOAT_TOKEN_ID / token flag.

### `SILVERS_CRY`
- path: `src_custom/spell_effects/silvers_cry.c`
- L167: no once-per-turn tracker without file BSS / shared OPT flags. Ceiling: can activate multiple Silver's Cry per turn; upgrade: duel-state OPT bit.

### `SNAKE_RAIN`
- path: `src_custom/spell_effects/snake_rain.c`
- L179: no committed multi-pick UI — cancel mid-loop auto-fills remaining reptiles in deck order. Ceiling: player cannot abort partial selection.

### `SOLAR_RECHARGE`
- path: `src_custom/spell_effects/solar_recharge.c`
- L79: mill helper advances deck top only (no expanded-GY push), matching charge_of_the_light_brigade. Ceiling: milled cards may not appear in GY UI.

### `THE_A_FORCES`
- path: `src_custom/spell_effects/the_a_forces.c`
- L14: continuous +200 ATK per Warrior/Spellcaster you control on your Warriors needs a field-stat / continuous ATK overlay outside this file (no in-file hook into Duel_TryApplyDynamicZoneStats or Refresh overlays). Ceiling: face-up continuous only; upgrade: stat overlay → if face-up THE_A_FORCES then each face-up Warrior you control ATK += 200 *

### `THE_SACRED_WATERS_IN_THE_SKY`
- path: `src_custom/spell_effects/the_sacred_waters_in_the_sky.c`
- L252: no dedicated choice UI — A = activate Sanctuary, B = search mention. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L535: battle-destruction protection ("banish this from GY instead") needs a battle/destroy redirect hook. Ceiling: activate + LP gain only; upgrade: battle_damage / destroy-protection hook checking GY Sacred Waters.

### `THE_SHALLOW_GRAVE`
- path: `src_custom/spell_effects/the_shallow_grave.c`
- L155: no DUEL_SUMMON_SPECIAL_FACE_DOWN_DEF — NORMAL_SET for face-down DEF, then mark unk4=2 as Special Summon. Ceiling: SS-locks that only gate SummonModeIsSpecial still apply via SpecialSummonMonsterId's Kristya check; CannotBeSpecialSummoned checked here. Upgrade: add face-down SS mode.

### `TRIANGLE_ECSTASY_SPARK`
- path: `src_custom/spell_effects/triangle_ecstasy_spark.c`
- L65: stage unit is 500 ATK — Sisters (1950) become 2450 or 2950, not exact printed 2700. Ceiling: nearest-stage temp boost until EOT; upgrade: exact-ATK overlay (like riryoku) forced to 2700 until End Phase clear.
- L69: opponent cannot activate Trap Cards / negate opp Trap effects until EOT needs a trap-activation / trap-resolve gate outside this file. Ceiling: Sisters ATK approx only; upgrade: turn flag → block CanActivateTrap / trap effect resolve for INACTIVE_DUELIST until End Phase.

### `VENOM_SWAMP`
- path: `src_custom/spell_effects/venom_swamp.c`
- L14: End Phase Venom Counters / -500 ATK per counter / destroy at 0 ATK need an End Phase turn_effect hook + per-monster counter storage outside this file (DuelCard has no venom-counter field; no in-file End Phase dispatch). Ceiling: continuous face-up only; upgrade: turn_effect End Phase → if face-up VENOM_SWAMP then place 1 counter on each face-up non-Venom monster, apply

### `VIPERS_REBIRTH`
- path: `src_custom/spell_effects/vipers_rebirth.c`
- L221: End Phase destroy of the SS'd monster needs a turn_effect hook outside this file (no in-file End Phase destroy queue without BSS). Ceiling: SS only; upgrade: turn_effect_hooks End Phase → destroy marked zone.

### `WETLANDS`
- path: `src_custom/spell_effects/wetlands.c`
- L87: +1200 ATK for Aqua/WATER/Level≤2 needs a field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only covers monster ids registered in duel_helpers.c). Ceiling: face-up field only; upgrade: LynJump/stat overlay → if face-up WETLANDS and TYPE_AQUA + ATTRIBUTE_WATER + level≤2 then ATK += 1200.

## trap (9)

### `A_HERO_EMERGES`
- path: `src_custom/trap_effects/a_hero_emerges.c`
- L26: Extra Deck / Ritual need proper summon; treat as unsummonable from hand
- L62: Normal Trap must leave the backrow to prevent AI re-trigger loop

### `ANGELS_TEAR`
- path: `src_custom/trap_effects/angels_tear.c`
- L342: need 4 banish targets plus 1 summon target.

### `BOTTOMLESS_SHIFTING_SAND`
- path: `src_custom/trap_effects/bottomless_shifting_sand.c`
- L10: GBA hand cap is 5; TCG rule uses 4 — scale self-destruct threshold down

### `DUST_TORNADO`
- path: `src_custom/trap_effects/dust_tornado.c`
- L112: optional hand pick — B skips; upgrade path: shared helper in exchange_hand_selection

### `FAIRY_BOX`
- path: `src_custom/trap_effects/fairy_box.c`
- L96: age both fixed backrows so a trap set last turn is live when the other duelist attacks

### `GRAVITY_BIND`
- path: `src_custom/trap_effects/gravity_bind.c`
- L64: face-down GB still blocks the declare; AI sim restore keeps it face-down every trial

### `MAGIC_CYLINDER`
- path: `src_custom/trap_effects/magic_cylinder.c`
- L22: Normal Trap must leave the backrow to prevent AI re-trigger loop

### `MIRROR_FORCE`
- path: `src_custom/trap_effects/mirror_force.c`
- L21: destroy self after monsters so AI sim doesn't re-trigger

### `SOLEMN_WISHES`
- path: `src_custom/trap_effects/solemn_wishes.c`
- L89: InitBoard fills hands via TryDrawingCard before duel gfx; skip until past opening hand.

## activated (24)

### `AMULET_DRAGON`
- path: `src_custom/activated_effects/amulet_dragon.c`
- L58: no multi-select GY UI — banish every Spell in both GYs (min.1 gate above).
- L254: on-summon text after field draw so Amulet Dragon is visible (fusion uses updateGfx=FALSE).

### `ARCHLORD_KRISTYA`
- path: `src_custom/activated_effects/archlord_kristya.c`
- L322: engine treats level 5+ with no tribute as special-like (Cyber Dragon, etc.).

### `ATHENA`
- path: `src_custom/activated_effects/athena.c`
- L71: attack-position summons keep isFaceUp=0 until end-of-turn flip.
- L363: drop field-target cursor before GY deck menu — PickZone state + trunk view was crashing when the menu opened on confirm.

### `CYBER_LASER_DRAGON`
- path: `src_custom/activated_effects/cyber_laser_dragon.c`
- L17: targets face-up monsters on opponent's side with ATK >= 2400 or DEF >= 2400. Upgrade path: scan backrow S/T cards if the card text ever changes.

### `DARK_ARMED_DRAGON`
- path: `src_custom/activated_effects/dark_armed_dragon.c`
- L174: allow self-target for faithful TCG simulation; player can choose suboptimally
- L317: auto-target. No GY picker (DeckMenu screen switch corrupts VRAM from inside monster effect handler) and no PickZone cursor state (200 conflicts with game loop after MonsterActionMenu case 4 returns). Picks the best field target via AiPickTarget logic. Upgrade path: dedicated cursor state + A/B handlers like Cannon Soldier.

### `DARK_DUST_SPIRIT`
- path: `src_custom/activated_effects/dark_dust_spirit.c`
- L22: hand normal/tribute summon copies isFaceUp=0; attack-position still counts
- L63: GBA "face-up" = isFaceUp bit; attack-position keeps isFaceUp=0 until flip

### `ELEMENTAL_HERO_BLAZEMAN`
- path: `src_custom/activated_effects/elemental_hero_blazeman.c`
- L222: on-summon does not consume effectUsedThisTurn — that flag is only for the menu activated effect (popup_2). Otherwise popup_2 can never fire the turn Blazeman is summoned.

### `ELEMENTAL_HERO_GAIA`
- path: `src_custom/activated_effects/elemental_hero_gaia.c`
- L49: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.

### `ELEMENTAL_HERO_GREAT_TORNADO`
- path: `src_custom/activated_effects/elemental_hero_great_tornado.c`
- L26: GetTypeGroup calls SetCardInfo and would clobber gCardInfo.atk/def that the stat pipeline already computed for zone.

### `ELEMENTAL_HERO_ICE_EDGE`
- path: `src_custom/activated_effects/elemental_hero_ice_edge.c`
- L59: direct-attack grant this turn; cleared in UnlockCardsInRow.

### `ELEMENTAL_HERO_LADY_HEAT`
- path: `src_custom/activated_effects/elemental_hero_lady_heat.c`
- L45: CanActivate runs before the menu flips a face-down activator

### `ELEMENTAL_HERO_OCEAN`
- path: `src_custom/activated_effects/elemental_hero_ocean.c`
- L81: skip stale GY Ocean while the activator is still on field

### `ELEMENTAL_HERO_STRATOS`
- path: `src_custom/activated_effects/elemental_hero_stratos.c`
- L462: on-summon text after field draw so Stratos is visible.
- L465: no dedicated A/B choice UI — try search first; player can cancel the deck pick (B) to fall through to destroy when that option is legal.

### `ELEMENTAL_HERO_TERRA_FIRMA`
- path: `src_custom/activated_effects/elemental_hero_terra_firma.c`
- L41: fixed POV — only reveal the player's own monster row
- L69: attack-position summons stay isFaceUp=0 until end-of-turn flip

### `HOURGLASS_OF_LIFE`
- path: `src_custom/activated_effects/hourglass_of_life.c`
- L11: updateGfx=FALSE — sub_8041CCC refreshes field after popup dismisses.

### `JOWLS_OF_DARK_DEMISE`
- path: `src_custom/activated_effects/jowls_of_dark_demise.c`
- L70: Jowls direct-attack flag; cleared when zone resets

### `KAIBAMAN`
- path: `src_custom/activated_effects/kaibaman.c`
- L96: tribute-replacement in same zone; not a marked special summon (unk4 stays 0)

### `LEVIA_DRAGON_DAEDALUS`
- path: `src_custom/activated_effects/levia_dragon_daedalus.c`
- L124: walk gDuel.board directly; gFixedZones column order differs on opponent rows, so row/col checks against gMonEffect can skip the wrong slot.

### `MAN_THRO_TRO`
- path: `src_custom/activated_effects/man_thro_tro.c`
- L21: Ojama Trio monster form is the only token-like field unit today

### `TETHYS_GODDESS_OF_LIGHT`
- path: `src_custom/activated_effects/tethys_goddess_of_light.c`
- L50: opening hand is seeded before duel gfx; skip like Solemn Wishes.
- L54: unk18 != 0 means battle/damage resolution is active.

### `THE_BLAZING_MARS`
- path: `src_custom/activated_effects/the_blazing_mars.c`
- L48: no multi-select GY banish + hand/GY activation path yet — banish 3 other monsters to Special Summon deferred until expanded GY targeting exists.
- L63: no Main Phase 1 gate yet — field burn is activatable in any main phase.

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

## permanent (27)

### `AMAZONESS_TIGER`
- path: `src_custom/permanent_effects/amazoness_tiger.c`
- L30: normal hand summon copies isFaceUp=0; attack-position monsters still count

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
- L15: hand normal summon copies isFaceUp=0; attack-position monsters still count
- L40: placement hook is hand normal/tribute summon only — special summons use duel_helpers

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
- L22: no banished-zone storage yet — +300 ATK per banished E-HERO and return up to 2 banished E-HEROes to hand deferred until banish zone exists.

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

### `SHATIEL`
- path: `src_custom/permanent_effects/shatiel.c`
- L51: GetTypeGroup/SetCardInfo would clobber gCardInfo mid-pipeline.

### `SPIRIT_OF_THE_POT_OF_GREED`
- path: `src_custom/permanent_effects/spirit_of_the_pot_of_greed.c`
- L11: normal hand summon copies isFaceUp=0; attack-position monsters still count

### `THE_BIG_SATURN`
- path: `src_custom/permanent_effects/the_big_saturn.c`
- L96: custom targeted spells store fixed-row origins in row2.
- L257: GY permanent scan misses some opponent-turn effect destroys (Core pattern).

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

### `ZERIEL`
- path: `src_custom/permanent_effects/zeriel.c`
- L44: GetTypeGroup/SetCardInfo would clobber gCardInfo.atk already computed.

## battle (3)

### `CYBER_BARRIER_DRAGON`
- path: `src_custom/battle_effects/cyber_barrier_dragon.c`
- L48: Duel_ShowEffectText naturally skips during AI sim (gHideEffectText) but fires on real gameplay. No forced override — that would block the sim loop.

### `ELEMENTAL_HERO_CORE`
- path: `src_custom/battle_effects/elemental_hero_core.c`
- L233: gHideEffectText marks AI attack simulation; keep printed ATK at base.

### `ELEMENTAL_HERO_VOLTIC`
- path: `src_custom/battle_effects/elemental_hero_voltic.c`
- L76: no banished-zone / removed-from-play storage yet — show text only; optional target + special summon deferred until banish zone exists.

## turn (1)

### `YUBEL`
- path: `src_custom/turn_effects/yubel.c`
- L110: hand normal/tribute summon copies isFaceUp=0; attack-position still counts
