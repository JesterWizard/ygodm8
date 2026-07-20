# Partial Effects Backlog

Auto-generated living list of effect files with `ponytail:` ceilings (implemented, but missing hooks / engine pieces).
Find follow-up work here — stubs live in `STUB_EFFECTS.md`.
Rows vanish when all `ponytail:` comments are removed from the file.

```bash
python3 tools/stub_effect_queue.py --write-list   # stubs + partials
```

**Last updated:** 2026-07-20 17:26 UTC  
**Remaining partials:** `355`

## Counts by kind

| Kind | Count |
|------|------:|
| `spell` | 185 |
| `trap` | 115 |
| `activated` | 24 |
| `permanent` | 27 |
| `battle` | 3 |
| `turn` | 1 |
| **total** | **355** |

## spell (185)

### `ALLURING_MIRROR_SPLIT`
- path: `src_custom/spell_effects/alluring_mirror_split.c`
- L14: battle-destroy of Harpie Lady / Sisters → SS different-name Harpie from Deck needs a battle-destroy listener + OPT bit outside this file. Ceiling: continuous face-up only; upgrade: after battle destroy → if face-up ALLURING_MIRROR_SPLIT and destroyed is Harpie Lady / Sisters then Deck SS Harpie with original name != destroyed.
- L20: when this card is destroyed by a Harpie effect or opponent's effect → SS 1 Harpie from GY needs a destroy-reason hook outside this file. Ceiling: no floating on leave; upgrade: ClearZoneAndSendMonToGraveyard / destroy path → if id was ALLURING_MIRROR_SPLIT and reason matches, PickZone GY Harpie → Duel_SpecialSummonFromGrave.

### `AMAZONESS_CALL`
- path: `src_custom/spell_effects/amazoness_call.c`
- L24: OPT bit never cleared mid-duel without turn_effect reset hook. Ceiling: blocks 2nd Amazoness Call only until soft-reset / new duel BSS; upgrade: turn_effect Standby → sAmazonessCallUsedThisTurn = 0.
- L96: no dedicated hand/GY choice UI — A = add to hand, B = send to GY. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L281: GY banish → target 1 Amazoness you control; that monster can attack all opponent monsters once each, also other monsters cannot attack needs GY ignition + battle multi-attack hooks outside this file. Ceiling: on-field deck search only; upgrade: GY activate → banish AMAZONESS_CALL → PickZone Duel_IsAmazonessCard → mark zone for multi-attack

### `AMAZONESS_FIGHTING_SPIRIT`
- path: `src_custom/spell_effects/amazoness_fighting_spirit.c`
- L14: Amazoness vs higher-ATK +1000 during damage calculation only needs a battle_effects damage-calc hook (like skyscraper.c) outside this file. Ceiling: face-up continuous only; upgrade: ApplyAmazonessFightingSpiritBattleAtkBoost → if face-up AMAZONESS_FIGHTING_SPIRIT on controller's field, attacker passes Duel_IsAmazonessCard, and defender ATK > attacker ATK, then attacker ATK += 1000.

### `AMAZONESS_HEIRLOOM`
- path: `src_custom/spell_effects/amazoness_heirloom.c`
- L54: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add AMAZONESS_HEIRLOOM to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.
- L59: once-per-turn battle-destroy protection needs CanMonsterBeDestroyedByBattle / Duel_ApplyBattleDestroyProtection to check DynamicEquipTargetsMonsterWithSpell (zone, AMAZONESS_HEIRLOOM) + OPT bit. Ceiling: equip-only; upgrade: battle-protect flag cleared EOT / after one save.
- L64: after damage calc, if equipped attacks a monster → destroy defender needs a battle_effects post-damage hook outside this file. Ceiling: equip-only; upgrade: after damage calc → if DynamicEquipTargetsMonsterWithSpell(attacker, AMAZONESS_HEIRLOOM) then Duel_DestroyZone(defender).

### `AMAZONESS_SECRET_ARTS`
- path: `src_custom/spell_effects/amazoness_secret_arts.c`
- L15: OPT / GY ignition (banish → Extra Deck material) need hooks outside this file. Ceiling: field Fusion only once per BSS; upgrade: turn_effect reset + GY ignition → mark Amazoness Extra material flag.

### `AMAZONESS_VILLAGE`
- path: `src_custom/spell_effects/amazoness_village.c`
- L89: +200 ATK for Amazoness monsters needs a field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only covers monster ids registered in duel_helpers.c). Ceiling: face-up field only; upgrade: LynJump/stat overlay → if face-up AMAZONESS_VILLAGE and Duel_IsAmazonessCard(zone) then ATK += 200.
- L94: once-per-turn when an Amazoness is destroyed by battle/effect and sent to GY → SS 1 Amazoness from Deck with Level ≤ that GY monster needs a destroy/GY listener + OPT bit outside this file. Ceiling: continuous face-up only; upgrade: after-destroy hook → if face-up AMAZONESS_VILLAGE and Duel_IsAmazonessCard(destroyed) then PickZone deck SS filtered by level.

### `ANCIENT_GEAR_ADVANCE`
- path: `src_custom/spell_effects/ancient_gear_advance.c`
- L149: OPT Tribute 1 → draw + tribute-free NS for AGG / Lv5+ that mention it, and cannot-Set this turn need ignition + Normal Summon / Set gates outside this file. Ceiling: activate search only.

### `ANCIENT_GEAR_CASTLE`
- path: `src_custom/spell_effects/ancient_gear_castle.c`
- L17: +300 ATK for Ancient Gear monsters needs a continuous field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only covers registered monster ids; 1 stage ~= 500 ATK so printed +300 is not exact). Ceiling: continuous face-up only; upgrade: LynJump/stat overlay → if face-up ANCIENT_GEAR_CASTLE and Duel_CardNameContains(id, "Ancient Gear")
- L24: Counter on each Normal Summon/Set needs a summon/set hook outside this file (no in-file summon dispatch). Ceiling: unk4 stays 0; upgrade: after Normal Summon/Set → if face-up ANCIENT_GEAR_CASTLE on controller's field then zone->unk4++.
- L29: Tribute this card instead when Tribute Summoning an Ancient Gear (if counters >= required Tributes) needs a tribute-count / substitute hook outside this file. Ceiling: never substitutes; upgrade: tribute gate → if face-up ANCIENT_GEAR_CASTLE && unk4 >= required && summoning Ancient Gear then destroy this card as the Tribute(s).

### `ANCIENT_GEAR_DRILL`
- path: `src_custom/spell_effects/ancient_gear_drill.c`
- L196: no per-card same-turn activation lock. Ceiling: Set Spell can still be activated this turn. Upgrade: turn-scoped cardId/zone lock checked at Spell activation.

### `ANCIENT_GEAR_FACTORY`
- path: `src_custom/spell_effects/ancient_gear_factory.c`
- L195: no multi-select GY UI — auto-pick an exact Level-sum mask. Ceiling: no player choice among valid GY sets; upgrade: DeckMenu multi-pick until sum == 2× revealed Level.
- L203: "Normal Summon the revealed monster this turn without Tributing" needs a turn-scoped tribute-bypass (clone Necroshade) outside this file. Ceiling: reveal + GY banish only; upgrade: mark revealId + consume on NS.

### `ANCIENT_GEAR_FIST`
- path: `src_custom/spell_effects/ancient_gear_fist.c`
- L63: end of Damage Step destroy the monster it battled (if equipped still on field) needs a battle_effects Damage Step end hook outside this file. Ceiling: equip-only works; destroy trigger not wired from this file. Upgrade: end-of-Damage-Step → if DynamicEquipTargetsMonsterWithSpell (attacker/defender, ANCIENT_GEAR_FIST) and equip still face-up, then
- L70: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add ANCIENT_GEAR_FIST to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade: same as H_HEATED_HEART.

### `ANCIENT_GEAR_TANK`
- path: `src_custom/spell_effects/ancient_gear_tank.c`
- L61: stage unit is 500 ATK — applied +500, not printed +600. Ceiling: no fractional stages; upgrade: exact-ATK overlay like BIG_BANG_SHOT after listing ANCIENT_GEAR_TANK in IsActiveDynamicEquipSpellZone.
- L73: destroy→GY burn 600 to opponent needs a field/destroy hook outside this file (OnDynamicEquipZoneAboutToClear / GY send). Ceiling: equip-only works; destroy-burn not wired from this file. Upgrade: destroy-hook → Duel_ChangeLp(INACTIVE_DUELIST, -ANCIENT_GEAR_TANK_DESTROY_BURN).
- L79: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add ANCIENT_GEAR_TANK to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.

### `ARCANA_READING`
- path: `src_custom/spell_effects/arcana_reading.c`
- L108: no dedicated choice UI — A = Heads, B = Tails. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L270: GY banish → Normal Summon 1 Arcana Force needs a GY ignition hook outside this spell file (no in-file graveyard activation path). Ceiling: activation coin effect only; upgrade: GY ignition → banish ARCANA_READING then Duel_NormalSummonFromHand Arcana Force.

### `ARCANA_SPREAD`
- path: `src_custom/spell_effects/arcana_spread.c`
- L29: OPT bit never cleared mid-duel without turn_effect reset hook. Ceiling: blocks 2nd Arcana Spread only until soft-reset / new duel BSS; upgrade: turn_effect Standby → sArcanaSpreadUsedThisTurn = 0.
- L173: no dedicated choice UI — A = Heads, B = Tails. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L448: GY banish → add 1 coin-toss card from GY to hand needs a GY ignition path outside this spell file (no in-file graveyard activation). Ceiling: on-field coin SS only; upgrade: GY activate → banish ARCANA_SPREAD then DeckMenu pick IsCoinTossCard from GY → add to hand (OPT shared).

### `ARCANE_BARRIER`
- path: `src_custom/spell_effects/arcane_barrier.c`
- L173: Spell Counters when a face-up Spellcaster is destroyed need a destroy / leave-field hook outside this file (no in-file destroy dispatch). Ceiling: continuous face-up + ignition when unk4>0 (never rises alone); upgrade: on face-up Spellcaster destroy → if face-up ARCANE_BARRIER then zone->unk4++ (cap ARCANE_BARRIER_MAX_COUNTERS).
- L179: not in GetSpellType NORMAL override — face-up re-activation may need card_hooks GetSpellType + ARCANE_BARRIER listed (same as SHARD_OF_GREED / CALL_OF_THE_MUMMY).

### `AROMA_BLEND`
- path: `src_custom/spell_effects/aroma_blend.c`
- L291: GY effect (banish this → Fusion Summon Plant Fusion by banishing materials from hand/field, and GY Plants if LP higher) needs a GY-activate path + Plant Fusion recipe filter outside this file. Ceiling: discard + place Humid/Dried/Blessed Winds face-up only; upgrade: GY activate AROMA_BLEND → banish self → FusionDuel Plant Fusion pay
- L298: placed Winds are face-up/locked but their continuous trap effects are not auto-wired (trap stubs). Ceiling: card sits face-up; upgrade: call each Winds activate body after place, or wire trap dispatcher.

### `AROMA_GARDEN`
- path: `src_custom/spell_effects/aroma_garden.c`
- L79: printed "until end of opponent's next turn (even if this card leaves)" needs a multi-turn temp-stage / overlay tracker outside this file. Ceiling: +500 ATK/DEF via 1 temp stage (~clears at next ResetTempStages / EOT), not opponent's next End Phase; upgrade: stamp expiry turn counter on zones and skip ResetTempStages until that turn's End Phase.
- L112: "If a face-up Aroma you control is destroyed by battle or card effect and sent to the GY: Gain 1000 LP" needs a destroy→GY hook outside this file. Ceiling: OPT LP/+500 only; upgrade: on ClearZoneAndSendMonTo- Graveyard / battle destroy, if controller has face-up AROMA_GARDEN and destroyed card IsAromaMonster, Duel_ChangeLp(+1000).
- L121: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up OPT re-activation may need card_hooks GetSpellType + AROMA_GARDEN listed. Ceiling: first-activation OPT works; upgrade: add to NORMAL spell-type list.

### `AROMA_GARDENING`
- path: `src_custom/spell_effects/aroma_gardening.c`
- L16: OPT "NS/SS Aroma → +1000 LP" needs a summon hook outside this file (no in-file Normal/Special Summon dispatch). Ceiling: continuous face-up only; upgrade: after NS/SS (not Damage Step), if face-up AROMA_GARDENING and OPT bit clear and summoned monster name contains "Aroma", Duel_ChangeLp(+1000) and mark OPT.
- L22: OPT "opp attack declare while LP lower → SS Aroma from Deck" needs an attack-declare hook + deck pick outside this file. Ceiling: continuous face-up only; upgrade: on opp attack declare, if controller LP < opp LP and OPT clear and empty monster zone, PickZone/DeckMenu Aroma monster → Duel_SpecialSummonFromDeck.

### `ATTACK_PHEROMONES`
- path: `src_custom/spell_effects/attack_pheromones.c`
- L14: Reptile attacks DEF → flip to face-up ATK at end of Damage Step needs a battle_effects / Damage Step end hook outside this file. Ceiling: face-up continuous only; upgrade: end-of-Damage-Step → if face-up ATTACK_PHEROMONES on controller's field, attacker is Reptile (Duel_CardHasMonsterType TYPE_REPTILE), and defender was Defense Position,

### `BACKUP_SQUAD`
- path: `src_custom/spell_effects/backup_squad.c`
- L14: continuous face-up only — damage≥1000 draw listener needs a battle/LP-change hook outside this file (no in-file damage dispatch).

### `BERSERKER_SOUL`
- path: `src_custom/spell_effects/berserker_soul.c`
- L74: printed trigger is direct-attack damage ≤1500 — no battle-damage hook in-file. Ceiling: activatable as Normal Spell when hand+deck available; upgrade: battle_effects after direct dmg ≤1500 → allow activation.

### `BIG_BANG_SHOT`
- path: `src_custom/spell_effects/big_bang_shot.c`
- L76: 3 copies max per side — reuse slot 0 if all busy

### `BIG_EVOLUTION_PILL`
- path: `src_custom/spell_effects/big_evolution_pill.c`
- L122: destroy on controller's opponent's 3rd End Phase needs a turn_effect End Phase hook outside this file (no in-file End Phase dispatch). Ceiling: continuous face-up only (unk4 stays 0); upgrade: turn_effect_hooks opponent End Phase → if face-up BIG_EVOLUTION_PILL then unk4++; if unk4 >= BIG_EVOLUTION_PILL_OPPONENT_END_PHASES destroy it.
- L127: Normal Summon Level 5+ Dinosaur without Tributing needs a GetNumRequiredTributes gate outside this file (clone Necroshade in tribute_hooks.c). Ceiling: continuous face-up only; upgrade: if face-up BIG_EVOLUTION_PILL for summoner and card is TYPE_DINOSAUR Level >= 5 then return 0 tributes.

### `BOND_BETWEEN_TEACHER_AND_STUDENT`
- path: `src_custom/spell_effects/bond_between_teacher_and_student.c`
- L26: Dark Magic Twin Burst is not in trunk/card_ids — Set list is the three in-game Dark Magician support Spells only. Ceiling: misses Twin Burst; upgrade: add DARK_MAGIC_TWIN_BURST card + id.
- L149: once-per-turn not tracked after this normal spell leaves the field (no shared turn-flag RAM editable from this file alone). Ceiling: multiple Bond per turn; upgrade: duel-state OPT bit.
- L170: no dedicated choice UI — A = SS Dark Magician, B = SS Dark Magician Girl. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `BOOK_OF_LIFE`
- path: `src_custom/spell_effects/book_of_life.c`
- L61: single-card GY model — banish removes opponent's top graveyard card

### `BUBBLE_BLASTER`
- path: `src_custom/spell_effects/bubble_blaster.c`
- L51: stage unit is 500 ATK — applied +1000, not printed +800. Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART after listing BUBBLE_BLASTER in IsActiveDynamicEquipSpellZone.
- L62: battle-destroy this instead + battle damage 0 needs CanMonsterBeDestroyedByBattle / Duel_ApplyBattleDestroyProtection + damage step hook outside this file. Ceiling: Bubbleman equip + ATK only; upgrade: if DynamicEquipTargetsMonsterWithSpell(zone, BUBBLE_BLASTER) would be battle- destroyed → destroy BUBBLE_BLASTER instead and set battle damage to 0.
- L68: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add BUBBLE_BLASTER to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.

### `BURDEN_OF_THE_MIGHTY`
- path: `src_custom/spell_effects/burden_of_the_mighty.c`
- L14: continuous -100 ATK × Level on each face-up opponent monster needs a field-stat / continuous ATK overlay outside this file (no in-file hook into Duel_TryApplyDynamicZoneStats or Refresh overlays). Ceiling: face-up continuous only; upgrade: stat overlay → if face-up BURDEN_OF_THE_MIGHTY then each face-up opp monster ATK -= 100 * level.

### `CALL_OF_THE_MUMMY`
- path: `src_custom/spell_effects/call_of_the_mummy.c`
- L97: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up OPT re-activation may need card_hooks GetSpellType + CALL_OF_THE_MUMMY listed. Ceiling: first-activation OPT works; upgrade: add to NORMAL spell-type list.

### `CELESTIAL_SWORD_EATOS`
- path: `src_custom/spell_effects/celestial_sword_eatos.c`
- L56: always treated as a Noble Arms card needs a name/archetype tag outside this file. Ceiling: equip +ATK only; upgrade: treat-as / name contains "Noble Arms" for Noble Arms support.
- L60: send-from-field-to-GY → target Guardian Eatos for +500 ATK per banished monster needs a leave-field / destroy hook outside this file (OnDynamicEquipZoneAboutToClear). Ceiling: equip +500 only; upgrade: leave- hook → PickZone GUARDIAN_EATOS then ApplyDynamicEquipStages / IncrementTempStage × banished count (CELESTIAL_SWORD_EATOS_GY_ATK_PER_BANISH_STAGES).
- L66: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add CELESTIAL_SWORD_EATOS to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.

### `CHAIN_STRIKE`
- path: `src_custom/spell_effects/chain_strike.c`
- L17: no Chain Link / chain-depth API in this engine (grep ChainLink empty). Ceiling: always unactivatable; upgrade: require link >= 2, burn 400 * link, and forbid activation when multiple copies of this card are already on the chain.

### `CHAIN_SUMMONING`
- path: `src_custom/spell_effects/chain_summoning.c`
- L22: Double Summon API only grants 1 extra NS (=2 total), not 3. Ceiling: up to 2 Normal Summons/Sets this turn; upgrade: chain-summoning pending counter of 2 extras in code_803F02C_hooks (like Double Summon unlock loop) so LockMonsterCardsInRow can unlock twice.
- L26: no Chain Link / chain-depth API (same as CHAIN_STRIKE). Ceiling: activable without Link≥3 or same-name-on-chain forbid; upgrade: require link >= 3 and reject when multiple same-name cards/effects already on chain.
- L35: Chain Link 3+ gate missing — see ResolveBody. Always offered.

### `CHARGE_OF_THE_LIGHT_BRIGADE`
- path: `src_custom/spell_effects/charge_of_the_light_brigade.c`
- L243: mill helper advances deck top only (no expanded-GY push), matching needle_worm / gravekeepers_servant. Ceiling: milled cards may not appear in GY UI.

### `CHICKEN_GAME`
- path: `src_custom/spell_effects/chicken_game.c`
- L34: no dedicated 3-way choice UI — nested A/B unlabeled. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L154: lowest-LP player takes no damage needs an LP/damage gate outside this file (no damage-immunity helper keyed to field spell). Ceiling: continuous face-up + OPT pay/draw/destroy/opp-gain only; upgrade: ChangeLp / battle-damage hook → if face-up CHICKEN_GAME and target has strictly lower LP (or tied-lowest), skip damage.
- L160: "neither player can activate cards/effects in response" needs a response-block flag outside this file. Ceiling: normal trap chain still possible on Effect entry; upgrade: skip TryResolveSpellThroughTraps for ignition / set activation-protect flag.
- L165: not in GetSpellType NORMAL/FIELD override — face-up OPT re-activation may need card_hooks GetSpellType + CHICKEN_GAME listed (same as CALL_OF_THE_MUMMY / WATERHAZARD).

### `CLOCK_TOWER_PRISON`
- path: `src_custom/spell_effects/clock_tower_prison.c`
- L20: Opp Standby Clock Counter placement needs a turn_effect Standby hook outside this file (no in-file Standby dispatch). Ceiling: continuous face-up + unk4 counter slot (never rises alone); upgrade: opp Standby → if face-up CLOCK_TOWER_PRISON then unk4++ (cap CLOCK_TOWER_PRISON_MAX_COUNTERS).
- L26: 4+ counters → no battle damage needs a battle-damage gate outside this file. Ceiling: continuous only; upgrade: battle LP calc → if face-up CLOCK_TOWER_PRISON with unk4 >= 4 then battle damage to controller = 0.
- L30: destroy with 4+ counters → SS Destiny HERO - Dreadmaster from hand/Deck needs a destroy/leave-field hook outside this file. Ceiling: continuous face-up only; upgrade: OnDestroy → if unk4 >= 4 then Duel_SpecialSummonFromHand/Deck(DESTINY_HERO_DREADMASTER).

### `COCOON_REBIRTH`
- path: `src_custom/spell_effects/cocoon_rebirth.c`
- L60: only the five Chrysalis in-trunk pairs are mapped.

### `COLD_WAVE`
- path: `src_custom/spell_effects/cold_wave.c`
- L16: "activate only at start of Main Phase 1" needs a phase/action counter outside this file (no Main Phase 1-start gate API). Ceiling: activable any time like a normal spell; upgrade: CanActivate → require MP1 + no prior play/set/summon this turn.
- L21: block play/Set of Spell/Trap until next turn needs a shared lock hooked into Duel_IsCardActivationBlocked / set-from-hand (like Wicked Avatar SpellTrap lock). Ceiling: show text + send to GY only; upgrade: arm a Cold Wave turn flag in Duel_IsCardActivationBlocked for TYPE_SPELL/TRAP and Set paths until activator's next Standby, then clear.

### `COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS`
- path: `src_custom/spell_effects/colosseum_cage_of_the_gladiator_beasts.c`
- L93: Counter on Special Summon from Deck needs a summon-listener outside this file (no in-file SS-from-Deck dispatch). Ceiling: face-up field + unk4 counter slot (never rises alone); upgrade: after SS from Deck → if face-up COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS then zone->unk4++.
- L98: +100 ATK/DEF per counter for all Gladiator Beast monsters needs a field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only covers monster ids registered in duel_helpers.c). Ceiling: face-up field only; upgrade: LynJump/stat overlay → if face-up COLOSSEUM and name contains "Gladiator Beast" then ATK/DEF += 100 * zone->unk4.
- L104: discard another Colosseum to prevent destroy by card effect needs a destroy-protection / replacement hook outside this file. Ceiling: no protect; upgrade: OnWouldDestroySpell → if hand has COLOSSEUM_CAGE then optional discard and skip destroy.

### `CONTACT`
- path: `src_custom/spell_effects/contact.c`
- L37: only the five Chrysalis in-trunk pairs are mapped.

### `CONTACT_GATE`
- path: `src_custom/spell_effects/contact_gate.c`
- L336: ED Fusion-only lock + GY ignition (banish this → SS banished Neo) need hooks outside this file. Ceiling: field SS path only.

### `CONTINUOUS_DESTRUCTION_PUNCH`
- path: `src_custom/spell_effects/continuous_destruction_punch.c`
- L14: post-damage-calc "DEF > ATK → destroy attacker" needs a battle_effects hook (clone des_kangaroo.c MarkPendingAttackerDestroy) outside this file. Ceiling: continuous face-up only; upgrade: after damage calc, if face-up CONTINUOUS_DESTRUCTION_PUNCH on defender's controller, defender is DEF position, and defender DEF > attacker ATK, destroy attacker (damage normal).

### `CONVERT_CONTACT`
- path: `src_custom/spell_effects/convert_contact.c`
- L191: cancel on deck pick auto-sends first Neo-Spacian (activation committed).

### `COURT_OF_JUSTICE`
- path: `src_custom/spell_effects/court_of_justice.c`
- L33: attack-position monsters keep isFaceUp=0 until EOT FlipAtkPosCardsFaceUp.

### `CYBERNETIC_ZONE`
- path: `src_custom/spell_effects/cybernetic_zone.c`
- L132: no RemovedFromPlay_RemoveAt — shift RFP after return.
- L166: stage unit is 500 ATK — double via +original/500 stages. Ceiling: non-multiples of 500 are floored; upgrade: exact ATK overlay.
- L307: End Phase return + ATK double + next Standby destroy need turn_effect_hooks calls to TryApplyCyberneticZoneEndPhase / TryApplyCyberneticZoneStandby (clone Power Bond / Capsule wiring). Ceiling: banished + state stored only until wired; upgrade: hook those TryApply* from TryActivatingTurnEffects.

### `D_BURST`
- path: `src_custom/spell_effects/d_burst.c`
- L184: GY ignition second attack needs battle End Damage Step hook.

### `D_FORCE`
- path: `src_custom/spell_effects/d_force.c`
- L119: While Plasma controlled — no Draw Phase draw / opp cannot target / Plasma +100 ATK per GY monster / destroy protect / second attack need continuous hooks outside this file. Ceiling: activate + Plasma search only.

### `DARK_CALLING`
- path: `src_custom/spell_effects/dark_calling.c`
- L159: "treated as a Fusion Summon with Dark Fusion" name/interaction checks (cards that look for Dark Fusion) need a summon-tag outside this file. Ceiling: Fiend Fusion via hand/GY banish only; upgrade: mark result zone / last-fusion-spell = DARK_FUSION for name-gated effects.

### `DARK_CITY_AT_MIDNIGHT`
- path: `src_custom/spell_effects/dark_city_at_midnight.c`
- L172: each Lv8+ Destiny HERO SS → Warriors +300 ATK, and destroy → Deck SS Destiny HERO need summon/destroy hooks outside this file. Ceiling: activate search only (printed: search if activated this turn).

### `DARK_CONTACT`
- path: `src_custom/spell_effects/dark_contact.c`
- L37: OPT flags never clear without a turn-end hook outside this file. Ceiling: each mode once per duel after first use; upgrade: turn_effect_hooks End Phase / turn-start → clear both flags.
- L271: no dedicated choice UI — A = Dark Fusion FS, B = search. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L426: no RemovedFromPlay_RemoveAt — shift RFP array in place. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- L567: "treated as a Fusion Summon with Dark Fusion" name/interaction checks need a summon-tag outside this file. Ceiling: Fiend Fusion via field/GY/banish shuffle only; upgrade: mark result zone / last-fusion-spell = DARK_FUSION for name-gated effects.

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

### `DARK_MAGICAL_CIRCLE`
- path: `src_custom/spell_effects/dark_magical_circle.c`
- L189: If DM NS/SS → target opp card banish needs summon trigger + PickZone outside this file. Ceiling: activate look/add only; upgrade: on DM summon → PickZone opp field → Duel_BanishZone. OPT flags need turn_effect reset.

### `DARK_MAGICIAN_CIRCLE`
- path: `src_custom/spell_effects/dark_magician_circle.c`
- L189: If DM NS/SS → target opp card banish needs summon trigger + PickZone outside this file. Ceiling: activate look/add only; upgrade: on DM summon → PickZone opp field → Duel_BanishZone. OPT flags need turn_effect reset.

### `DE_SYNCHRO`
- path: `src_custom/spell_effects/de_synchro.c`
- L81: duel Extra Deck return is imperfect — ExtraDeck_AddCard writes the player's trunk Extra Deck only (deck-builder API). Ceiling: ClearZone off-field + best-effort ExtraDeck_AddCard when enable_extra_deck; upgrade: per-duelist mid-duel Extra Deck return for the Synchro's controller.
- L101: Synchro Summon materials are not recorded at summon time, so "if all materials are in your GY, SS all of them" cannot run. Ceiling: return-to-Extra-Deck only; upgrade: store material cardIds on the Synchro zone at SynchroDuel_Execute, then if each is in GY, SS from GY.

### `DEDICATION_THROUGH_LIGHT_AND_DARKNESS`
- path: `src_custom/spell_effects/dedication_through_light_and_darkness.c`
- L127: special-face-up sets unk4=2 and blocks DMoC's on-summon effect

### `DIFFERENT_DIMENSION_CAPSULE`
- path: `src_custom/spell_effects/different_dimension_capsule.c`
- L174: no RemovedFromPlay_RemoveAt — shift RFP after returning the capsule card. Ceiling: local mutate; upgrade: RemovedFromPlay_RemoveAt helper.
- L225: RFP has no face-down flag — card is face-up in banished list. Ceiling: banished as normal RFP id; upgrade: face-down RFP bit.
- L274: RFP disabled — cannot banish from Deck. Ceiling: activation text only; upgrade: enable removed_from_play.
- L297: 2nd Standby destroy+add needs turn_effect_hooks call to TryApplyDifferentDimensionCapsuleStandby (clone Future Fusion wiring). Ceiling: banished card stored + continuous face-up only until wired; upgrade: turn_effect_hooks Standby → TryApplyDifferentDimensionCapsuleStandby.

### `DIMENSION_FUSION`
- path: `src_custom/spell_effects/dimension_fusion.c`
- L88: no RemovedFromPlay_RemoveAt — shift RFP array in place after SS. Ceiling: local mutate of gRemovedFromPlay; upgrade: add RemoveAt to removed_from_play.c.
- L147: RFP zone is id-list only (no face/position memory). Ceiling: SS face-up ATK via Duel_SpecialSummonMonsterId; upgrade: store zone state on banish + restore on return.

### `DOCTOR_D`
- path: `src_custom/spell_effects/doctor_d.c`
- L110: no dedicated hand/SS choice UI — A = add to hand, B = Special Summon. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L315: GY ignition "banish this card from GY, target 2 Destiny HERO; copy ATK until EOT" needs a GY-activate spell path + PickZone pair outside this file. Ceiling: on-field banish-cost recover only; upgrade: GY activate → banish DOCTOR_D → PickZone two Destiny HERO → set target ATK via temp stages / exact overlay until End Phase.

### `DOUBLE_SPELL`
- path: `src_custom/spell_effects/double_spell.c`
- L230: nested ActivateSpellEffect re-runs trap responses / field-spell specials; equips that need pre-set row2/col2 targets may fail. Ceiling: place + best-effort activate; upgrade: shared "resolve spell as if activated" helper that skips chain traps and supplies targeting for EQUIP/Field.

### `DOUBLE_TOOL_C_AND_D`
- path: `src_custom/spell_effects/double_tool_c_and_d.c`
- L78: printed +1000 only on your turn + battle negate/redirect/destroy need turn/battle hooks. Ceiling: equip link only (no ATK yet); upgrade: apply +2 stages on controller's turn via Duel_ResolveEquipStatBoost or overlay.

### `DRAGON_RAVINE`
- path: `src_custom/spell_effects/dragon_ravine.c`
- L187: no dedicated choice UI — A = add Dragunity, B = send Dragon to GY. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L405: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up OPT re-activation may need card_hooks GetSpellType + DRAGON_RAVINE listed. Ceiling: first-activation OPT works; upgrade: add to NORMAL spell-type list.

### `DRAGON_SHRINE`
- path: `src_custom/spell_effects/dragon_shrine.c`
- L165: no dedicated choice UI — A = send 1 more, B = stop. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L209: cancel on first pick auto-sends first Dragon (activation committed).
- L246: once-per-turn activation not tracked after this normal spell leaves the field (no shared turn-flag RAM editable from this file alone). Ceiling: multiple Dragon Shrine per turn possible; upgrade: shared OPT RAM bit / effect_usage once_per_turn.

### `DYNAMIC_EQUIP`
- path: `src_custom/spell_effects/dynamic_equip.c`
- L34: gTurnZones uses mirrored columns on opponent rows

### `EL_SHADDOLL_FUSION`
- path: `src_custom/spell_effects/el_shaddoll_fusion.c`
- L98: once-per-turn activation not tracked (no BSS turn flag editable from this file alone). Ceiling: multiple El Shaddoll Fusion per turn possible; upgrade: shared OPT RAM bit / effect_usage once_per_turn.

### `EN_ENGAGE_NEO_SPACE`
- path: `src_custom/spell_effects/en_engage_neo_space.c`
- L312: 1 stage ~= 500 ATK so +2 ≈ +1000.
- L324: ED Fusion-only SS lock this turn needs SpecialSummon gate outside this file. Ceiling: no lock; upgrade: turn flag → ED non-Fusion blocked.

### `EN_SHUFFLE`
- path: `src_custom/spell_effects/en_shuffle.c`
- L15: OPT flags never clear without a turn-end hook outside this file. Ceiling: once per duel after first field use; upgrade: turn_effect_hooks End Phase / turn-start → sEnShuffleFieldUsedThisTurn = 0.
- L311: GY ignition (banish this; shuffle E-HERO+Neo OR Neos from GY → Deck, draw 1) needs a GY-activate spell path outside this file. Ceiling: on-field shuffle+SS only; upgrade: GY activate → banish EN_SHUFFLE → return pair/Neos → Duel_DrawCards(1).

### `EN_WAVE`
- path: `src_custom/spell_effects/en_wave.c`
- L16: OPT "E-HERO used as Fusion material → GY/banish (not Damage Step): SS 1 Neo-Spacian or ELEMENTAL_HERO_NEOS from Deck" needs a fusion-material send listener outside this file. Ceiling: continuous face-up only; upgrade: after Fusion material leave → if face-up EN_WAVE and OPT clear, DeckMenu Neo-Spacian / NEOS → Duel_SpecialSummonFromDeck.
- L22: OPT "Neo-Spacian or ELEMENTAL_HERO_NEOS shuffled from field/GY into Deck/Extra Deck (not Damage Step): SS 1 Elemental HERO from GY" needs a shuffle-into-deck listener + GY pick outside this file. Ceiling: continuous face-up only; upgrade: on shuffle → if face-up EN_WAVE and OPT clear, PickZone/DeckMenu E-HERO in GY → Duel_SpecialSummonFromGrave.

### `END_OF_THE_WORLD`
- path: `src_custom/spell_effects/end_of_the_world.c`
- L15: Ruin, Queen of Oblivion is not in the trunk — only Demise is Ritual- Summonable via this card. Ceiling: Demise only; upgrade: add Ruin card + ID.

### `EVIL_ASSAULT`
- path: `src_custom/spell_effects/evil_assault.c`
- L134: no dedicated hand/SS choice UI — A = add to hand, B = Special Summon. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L334: "cannot Special Summon from Extra Deck except HERO monsters this turn" needs a summon-lock flag outside this file. Ceiling: discard+search/SS only; upgrade: turn flag → Extra Deck SS gate allows only HERO name results.
- L338: GY ignition "except the turn sent; banish this; add Dark Fusion from GY" needs a GY-activate spell path outside this file. Ceiling: on-field effect only; upgrade: GY activate → banish EVIL_ASSAULT → recover DARK_FUSION from GY to hand.

### `EVIL_MIND`
- path: `src_custom/spell_effects/evil_mind.c`
- L196: no dedicated 3-way choice UI — nested A/B unlabeled. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L414: "only activate 1 Evil Mind per turn" needs a turn-scoped cardId lock outside this file (spell is already in GY). Ceiling: no OPT lock after destroy; upgrade: turn flag checked in CanActivateEVIL_MIND.

### `FACTORY_OF_ONE_HUNDRED_MACHINES`
- path: `src_custom/spell_effects/factory_of_one_hundred_machines.c`
- L148: stage unit is 500 ATK — applied +500×banished, not printed +200×. Ceiling: no fractional temp stages; upgrade: exact-ATK overlay cleared at End Phase (tempStage already clears EOT).

### `FIELD_BARRIER`
- path: `src_custom/spell_effects/field_barrier.c`
- L43: Field Spell destroy protection + block new Field Spell activation need destroy-gate and Field Spell activation hooks outside this file (no in-file destroy/activate dispatch). Ceiling: continuous face-up + 1-copy control check only; upgrade: LynJump Duel_DestroyZone / Field Spell activate → if face-up FIELD_BARRIER then skip Field Spell destroy and refuse new

### `FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS`
- path: `src_custom/spell_effects/flavian_colosseum_of_the_gladiator_beasts.c`
- L309: when opponent declares an attack → OPT SS 1 Gladiator Beast from Deck (cannot be destroyed by battle) needs an attack-declaration hook outside this file. Ceiling: face-up field + search ignition only; upgrade: on attack declare → if face-up FLAVIAN and !OPT2 then Duel_SpecialSummonFromDeck(GB) + battle-destroy protect flag.
- L315: End Phase Set 1 Gladiator Trap from Deck if a GB was SS from Deck this turn needs End Phase + summon-from-Deck tracking outside this file. Ceiling: no End Phase Set; upgrade: turn_effect End Phase → if face-up FLAVIAN && ssFromDeckFlag && !OPT3 then DeckMenu Set trap with name containing "Gladiator" and TYPE_GROUP_TRAP.
- L321: not in GetSpellType NORMAL/FIELD override — face-up OPT re-activation may need card_hooks GetSpellType + FLAVIAN listed (same as DRAGON_RAVINE / CHICKEN_GAME).

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

### `FUSION_DEPLOYMENT`
- path: `src_custom/spell_effects/fusion_deployment.c`
- L17: OPT flag never clears without a turn-end hook outside this file. Ceiling: once per duel after first activation; upgrade: turn_effect_hooks End Phase / turn-start → sFusionDeploymentUsedThisTurn = 0.
- L118: Extra Deck disabled — browse gFusionRecipes results instead. Ceiling: not a real ED reveal; upgrade: require enable_extra_deck.
- L367: "cannot Special Summon from Extra Deck except Fusion Monsters this turn" needs a summon-lock flag outside this file (no in-file Extra Deck summon gate). Ceiling: SS material only; upgrade: turn flag → Extra Deck SS gate allows only FUSION_CARD results while set.

### `FUSION_DESTINY`
- path: `src_custom/spell_effects/fusion_destiny.c`
- L19: OPT flag never clears without a turn-end hook outside this file. Ceiling: once per duel after first activation; upgrade: turn_effect_hooks End Phase / turn-start → sFusionDestinyUsedThisTurn = 0.
- L346: destroy summoned Fusion during End Phase of next turn needs a turn_effect hook + 2-turn stamp outside this file. Ceiling: Fusion Summon only; upgrade: mark result zone / BSS turn counter → End Phase destroy.
- L350: "cannot Special Summon except DARK HERO" this turn needs a summon lock flag outside this file (ATTRIBUTE_SHADOW + name contains HERO). Ceiling: no SS lock; upgrade: turn flag → SpecialSummon gate allows only DARK HERO while set.

### `FUSION_GATE`
- path: `src_custom/spell_effects/fusion_gate.c`
- L282: real text lets the turn player use either player's Fusion Gate. Ceiling: only the controller's face-up gate via this spell activation path; upgrade: turn-player Main Phase check for any face-up FUSION_GATE then run ResolveFusionGateIgnition for ACTIVE_DUELIST.
- L286: not in GetSpellType NORMAL override — face-up re-activation may need card_hooks GetSpellType + FUSION_GATE listed (same as DRAGON_RAVINE).

### `FUTURE_FUSION`
- path: `src_custom/spell_effects/future_fusion.c`
- L165: hand test copies of the fusion result are not valid materials.

### `GADGET_BOX`
- path: `src_custom/spell_effects/gadget_box.c`
- L9: no dedicated Gadget Box Token card id — reuse MOON_TOKEN like other token spells. Ceiling: wrong printed name/stats; upgrade: real token card.
- L23: OPT remove 1 Morph Counter → SS Gadget Box Token + ED Synchro-only lock while Token present need Main Phase ignition + SS gate outside this file. Ceiling: continuous face-up with unk4=3 counters only; upgrade: ignition → unk4-- → Duel_SpecialSummonMonsterId(GADGET_BOX_TOKEN_ID) + ED lock flag.

### `GEARTOWN`
- path: `src_custom/spell_effects/geartown.c`
- L87: -1 Tribute for Ancient Gear Normal Summons needs a summon_tribute hook outside this file (no in-file tribute-count dispatch). Ceiling: field face-up only; upgrade: LynJump tribute-count → if face-up GEARTOWN and Duel_CardNameContains(id, "Ancient Gear") then required-1.
- L91: destroy→GY SS 1 Ancient Gear from hand/Deck/GY needs a destroy/ send-to-GY listener outside this file. Ceiling: no trigger from spell file alone; upgrade: destroy-hook → if destroyed id==GEARTOWN then SS matching Ancient Gear.

### `GENERATION_NEXT`
- path: `src_custom/spell_effects/generation_next.c`
- L28: OPT / same-name lock need turn-scoped flags outside this file. Ceiling: multiple Generation Next / same-name activate allowed; upgrade: BSS turn bit + last-chosen cardId lock checked at activation.
- L171: no dedicated Deck/GY choice UI — A = Deck, B = GY. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L197: no dedicated hand/SS choice UI — A = add to hand, B = Special Summon. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `GLADIATOR_BEAST_BATTLE_HALBERD`
- path: `src_custom/spell_effects/gladiator_beast_battle_halberd.c`
- L63: when equipped attacks → destroy 1 S/T at end of Damage Step needs a battle_effects Damage Step end hook + S/T PickZone outside this file. Ceiling: equip-only works; destroy trigger not wired from this file. Upgrade: end-of-Damage-Step after equipped attacked → if DynamicEquipTargetsMonsterWithSpell(..., GLADIATOR_BEAST_BATTLE_HALBERD)
- L70: recycle-to-hand when equipped monster returns to Deck (tag-out) and this card is sent to GY needs a return-to-deck / equip-send hook outside this file. Ceiling: equip only; upgrade: on GB return-to-deck → if linked GLADIATOR_BEAST_BATTLE_HALBERD hits GY then GY→hand.
- L75: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add GLADIATOR_BEAST_BATTLE_HALBERD to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade: same as H_HEATED_HEART.

### `GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD`
- path: `src_custom/spell_effects/gladiator_beasts_battle_archfiend_shield.c`
- L63: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add GLADIATOR_BEASTS_BATTLE_ARCHFIEND_SHIELD to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade: same as H_HEATED_HEART.
- L69: "if equipped would be destroyed, destroy this instead" needs a destroy-substitute gate outside this file (no in-file Duel_DestroyZone redirect). Ceiling: equip link only; upgrade: Duel_DestroyZone → if DynamicEquipTargetsMonsterWithSpell(zone, ARCHFIEND_SHIELD) then destroy the equip spell instead.
- L75: recycle-to-hand when equipped monster returns to Deck (tag-out) and this card is sent to GY needs a return-to-deck / equip-send hook outside this file. Ceiling: equip only; upgrade: on GB return-to-deck → if linked ARCHFIEND_SHIELD hits GY then add it from GY to hand.

### `GLADIATOR_BEASTS_BATTLE_GLADIUS`
- path: `src_custom/spell_effects/gladiator_beasts_battle_gladius.c`
- L60: stage unit is 500 ATK — applied +500, not printed +300. Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART after listing GLADIATOR_BEASTS_BATTLE_GLADIUS in IsActiveDynamicEquipSpellZone.
- L72: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add GLADIATOR_BEASTS_BATTLE_GLADIUS to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade: same as H_HEATED_HEART.
- L78: recycle-to-hand when equipped monster returns to Deck (tag-out) and this card is sent to GY needs a return-to-deck / equip-send hook outside this file. Ceiling: equip +ATK only; upgrade: on GB return-to-deck → if linked GLADIATOR_BEASTS_BATTLE_GLADIUS hits GY then Duel_AddDeckCardToHand / GY→hand.

### `GLADIATOR_BEASTS_BATTLE_MANICA`
- path: `src_custom/spell_effects/gladiator_beasts_battle_manica.c`
- L63: battle destroy immunity needs CanMonsterBeDestroyedByBattle / battle_damage hook checking DynamicEquipTargetsMonsterWithSpell( GLADIATOR_BEASTS_BATTLE_MANICA). Ceiling: equip registers only; upgrade: wire into Duel_ApplyBattleDestroyProtection like Spirit Reaper / Tempest.
- L68: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add GLADIATOR_BEASTS_BATTLE_MANICA to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade: same as H_HEATED_HEART.
- L74: recycle-to-hand when equipped monster returns to Deck (tag-out) and this card is sent to GY needs a return-to-deck / equip-send hook outside this file. Ceiling: equip register only; upgrade: on GB return-to-deck → if linked GLADIATOR_BEASTS_BATTLE_MANICA hits GY then Duel_AddDeckCardToHand / GY→hand.

### `GRAVEKEEPERS_INSCRIPTION`
- path: `src_custom/spell_effects/gravekeepers_inscription.c`
- L33: no dedicated 3-way choice UI — A / B / START. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L97: "activate only at start of Main Phase 1" needs a phase/action counter outside this file (no Main Phase 1-start gate API). Ceiling: activable any time like a normal spell; upgrade: CanActivate → require MP1 + no prior play/set/summon this turn.
- L110: chosen lock until end of opponent's turn needs gates outside this file. Ceiling: mode stored in APPEND_DATA only (no enforcement alone); upgrade: Duel_IsCardActivationBlocked / banish / SS-from-GY hooks → if GravekeepersInscription_GetActiveMode() matches, block that path; End Phase → TryClearGravekeepersInscriptionEndPhase.

### `GROUND_COLLAPSE`
- path: `src_custom/spell_effects/ground_collapse.c`
- L86: continuous zone lock needs FirstEmptyZoneInRow / PlaceMonster / summon-set validators outside this file (empty isLocked is ignored). Ceiling: face-up continuous + marks/stash only; upgrade: LynJump FirstEmptyZoneInRow (+ AI/player summon cursors) → skip isLocked empty MMZ while face-up GROUND_COLLAPSE; clear marks when it leaves the field.

### `HARPIE_LADY_PHOENIX_FORMATION`
- path: `src_custom/spell_effects/harpie_lady_phoenix_formation.c`
- L103: cannot SS from Main/Extra Deck + cannot conduct Battle Phase this turn need summon/phase gates outside this file. Ceiling: destroy+burn only.

### `HARPIES_FEATHER_REST`
- path: `src_custom/spell_effects/harpies_feather_rest.c`
- L15: OPT bit never cleared mid-duel without turn_effect reset hook. Ceiling: blocks 2nd Rest only until soft-reset / new duel BSS; upgrade: turn_effect Standby → sHarpiesFeatherRestUsedThisTurn = 0.
- L143: no multi-select GY UI — return 3 most recent Harpie Lady / Harpie Lady Sisters. Ceiling: no targeting; upgrade: DeckMenu multi-pick.
- L188: "cannot Special Summon except WIND for the rest of this turn" needs a Special Summon lock hook outside this file (ArchlordKristya-style attribute gate). Ceiling: no SS lock after resolve; upgrade: turn flag → Duel_SpecialSummon* reject non-ATTRIBUTE_WIND until End Phase clear.

### `HARPIES_HUNTING_GROUND`
- path: `src_custom/spell_effects/harpies_hunting_ground.c`
- L88: +200 ATK/DEF for all Winged Beast monsters needs a field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only covers monster ids registered in duel_helpers.c). Ceiling: face-up field only; upgrade: LynJump/stat overlay → if face-up HARPIES_HUNTING_GROUND and TYPE_WINGED_BEAST then ATK/DEF += 200.
- L93: on Normal/Special Summon of Harpie Lady / Harpie Lady Sisters (name-treated), summoner destroys 1 S/T — needs a summon-listener outside this file. Ceiling: no trigger from spell file alone; upgrade: after-summon hook → if face-up HARPIES_HUNTING_GROUND and summoned id is HARPIE_LADY / HARPIE_LADY_1/2/3 / HARPIE_LADY_SISTERS (or name "Harpie Lady") then

### `HERO_FLASH`
- path: `src_custom/spell_effects/hero_flash.c`
- L222: direct-attack grant needs a Can*AttackDirectly hook in code_8043EF4_hooks / ai_attack_hooks (Infected Mail / Jowls pattern). Ceiling: marks zone->unkTwo only; upgrade: CanHeroFlashMonsterAttackDirectly → zone->unkTwo after HERO_FLASH resolution this turn.

### `HIDDEN_TEMPLES_OF_NECROVALLEY`
- path: `src_custom/spell_effects/hidden_temples_of_necrovalley.c`
- L53: SS lock "except Gravekeeper's" needs a CanSpecialSummon / Duel_CardCannotBeSpecialSummoned gate outside this file. Ceiling: continuous face-up only; upgrade: LynJump PlaceMonster / Duel_CardCannotBeSpecialSummoned → if face-up HIDDEN_TEMPLES_OF_NECROVALLEY on field and card is not Gravekeeper (Duel_CardNameContains "Gravekeeper"),
- L60: self-destroy when no Gravekeeper or no Necrovalley needs a field- change / permanent hook outside this file. Ceiling: activation condition only; upgrade: after monster/backrow change, if face-up HIDDEN_TEMPLES and (!FieldHasGravekeeper \|\| !NecrovalleyOnField), Duel_DestroyZone(this).

### `HYSTERIC_SIGN`
- path: `src_custom/spell_effects/hysteric_sign.c`
- L92: no dedicated choice UI — A = Deck, B = GY. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L189: End Phase "sent from hand/field this turn → add up to 3 different Harpie cards from Deck" needs a GY/sent-this-turn + End Phase hook. Ceiling: only on-activate Elegant Egotist search works; upgrade: turn_effect or GY send tracker that opens a multi-pick Harpie deck search.

### `ILLUSION_MAGIC`
- path: `src_custom/spell_effects/illusion_magic.c`
- L136: no dedicated Deck/GY choice UI — A = Deck, B = GY. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L322: once-per-turn activation not tracked (no BSS turn flag editable from this file alone). Ceiling: multiple Illusion Magic per turn possible; upgrade: shared OPT RAM bit / effect_usage once_per_turn.

### `INFECTED_MAIL`
- path: `src_custom/spell_effects/infected_mail.c`
- L65: direct-attack grant needs a Can*AttackDirectly hook in code_8043EF4_hooks / ai_attack_hooks (Ice Edge / Jowls pattern). Ceiling: marks zone->unkTwo only; upgrade: CanInfectedMailMonsterAttackDirectly → zone->unkTwo && controller has face-up INFECTED_MAIL.
- L71: "Send it to the Graveyard at the end of the Battle Phase" needs an end-of-BP hook outside this file. Ceiling: mark only; upgrade: BP-end → if zone still marked, Duel_DestroyZone to controller GY.
- L159: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up OPT re-activation may need card_hooks GetSpellType + INFECTED_MAIL listed. Ceiling: first-activation OPT works; upgrade: add to NORMAL spell-type list.

### `INFERNO_FIRE_BLAST`
- path: `src_custom/spell_effects/inferno_fire_blast.c`
- L90: "cannot attack the turn you activate this" — isLocked is honored by AI attack selection / some mini_card paths, not a dedicated CannotAttack hook. Ceiling: best-effort lock on the targeted Red-Eyes; upgrade: turn-scoped attack-restriction flag cleared EOT (clone NightmareWheel / Mask of the Accursed).

### `INFERNO_TEMPEST`
- path: `src_custom/spell_effects/inferno_tempest.c`
- L105: activation gate "took ≥3000 Battle Damage from 1 attack" needs a battle-damage listener / flag outside this file (no mid-battle OPT hook editable here). Ceiling: resolve banish whenever activated from hand/backrow; upgrade: battle_damage_hooks → set flag on ≥3000 damage then gate CanActivate.

### `INSTANT_CONTACT`
- path: `src_custom/spell_effects/instant_contact.c`
- L28: OPT bit never cleared mid-duel without turn_effect reset hook. Ceiling: blocks 2nd Instant Contact only until soft-reset / new duel BSS; upgrade: turn_effect Standby → sInstantContactUsedThisTurn = 0.
- L292: without Neos, effects negated + End Phase return to Extra need negate + turn_effect hooks outside this file. Ceiling: SS + attack-lock only when Neos absent; upgrade: mark zone / turn_effect End Phase → ExtraDeck return + effect-negate while marked.

### `INSTANT_FUSION`
- path: `src_custom/spell_effects/instant_fusion.c`
- L25: OPT bit never cleared mid-duel without turn_effect reset hook. Ceiling: blocks 2nd Instant Fusion only until soft-reset / new duel BSS; upgrade: turn_effect Standby → sInstantFusionUsedThisTurn = 0.
- L240: End Phase destroy of the Instant Fusion monster needs a turn_effect hook outside this file (no in-file End Phase destroy queue without BSS mark). Ceiling: SS + attack-lock only; upgrade: turn_effect_hooks End Phase → destroy zone marked by Instant Fusion this turn. Treated-as-Fusion-Summon name checks also need a summon-tag outside this file.

### `INSTANT_NEO_SPACE`
- path: `src_custom/spell_effects/instant_neo_space.c`
- L86: "does not shuffle into Extra Deck during End Phase" needs an End Phase Contact-return suppress flag outside this file (Neos Contact return hooks live in permanent/turn effects). Ceiling: equip link only; upgrade: if DynamicEquipTargetsMonsterWithSpell (INSTANT_NEO_SPACE) then skip End Phase Extra Deck shuffle for that zone.
- L92: leave-field → SS 1 ELEMENTAL_HERO_NEOS from hand/Deck/GY needs a destroy/leave hook outside this file (OnDynamicEquipZoneAboutToClear). Ceiling: equip-only works; revive not wired from this file. Upgrade: leave-hook → Duel_SpecialSummonFromHand/Deck/Grave(ELEMENTAL_HERO_NEOS).
- L97: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add INSTANT_NEO_SPACE to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.

### `KNIGHTS_TITLE`
- path: `src_custom/spell_effects/knights_title.c`
- L109: special-face-up sets unk4=2 and blocks DMK's on-summon effect

### `LEMURIA_THE_FORGOTTEN_CITY`
- path: `src_custom/spell_effects/lemuria_the_forgotten_city.c`
- L134: no per-zone Level overlay API — levels come from SetCardInfo / Legendary Ocean adjusters only. Ceiling: OPT marks used + shows text; Levels unchanged. Upgrade: turn-scoped level bonus on each controlled WATER (= waterCount) cleared at End Phase (card_hooks GetLegendaryOcean-style).
- L176: +200 ATK/DEF for all WATER monsters needs a field-stat applier outside this file (clone ApplyLegendaryOceanFieldStatBoostForZone). Ceiling: face-up field + FIELD_UMI only; upgrade: LynJump/stat overlay → if face-up LEMURIA and ATTRIBUTE_WATER then ATK/DEF += 200.
- L189: not in GetSpellType NORMAL override — face-up OPT re-activation may need card_hooks GetSpellType + LEMURIA listed (same as SKYSCRAPER_2).

### `LEV_SHADDOLL_FUSION`
- path: `src_custom/spell_effects/lev_shaddoll_fusion.c`
- L14: Extra Deck heavy — on-activate send 1 Fusion from Extra to GY, and ignition (Tribute Fusion / SS Shaddoll Fusion different Attr ATK 0 / OPT / no Extra SS that turn) all need a duel-time Extra Deck browser + SS path. Trunk ExtraDeck_* APIs are deck-builder only. Ceiling: continuous face-up text only; upgrade: Extra Deck pick/send + tribute+SS ignition with OPT flag.

### `LEVEL_TUNING`
- path: `src_custom/spell_effects/level_tuning.c`
- L50: no TempLevel / zone level-mod field (DuelCard has only tempStage; level lives in ROM card data via SetCardInfo). Cannot apply -1 Level here. End Phase restore also needs a turn hook outside this file. Ceiling: printed Level unchanged; upgrade: TempLevel overlay + turn_effect_hooks End Phase clear that restores marked zones.

### `LIGHT_BARRIER`
- path: `src_custom/spell_effects/light_barrier.c`
- L14: Standby coin (Tails → negate until next Standby), Arcana Force summon choose-without-coin, and battle-destroy LP gain need turn_effect / summon / battle_effects hooks outside this file. Ceiling: continuous face-up only (Arcana Reading already checks face-up LIGHT_BARRIER for choose-Heads path); upgrade:

### `LIGHT_FORCE`
- path: `src_custom/spell_effects/light_force.c`
- L283: "cannot Special Summon except Arcana Force for the rest of this turn" needs a CanSpecialSummon / Duel_CardCannotBeSpecialSummoned gate outside this file. Ceiling: discard+search OPT only; upgrade: turn flag → if set and card is not Arcana Force then block SS.
- L308: Standby coin (if LIGHT_BARRIER not in Field Zone; Tails → negate until next Standby) needs turn_effect_hooks outside this file. Ceiling: continuous face-up only; upgrade: Standby → if face-up LIGHT_FORCE and no face-up LIGHT_BARRIER then toss coin; Tails set negated flag.
- L313: Fairy monsters +300 ATK/DEF needs a field-stat applier outside this file (stage steps are 500). Ceiling: face-up continuous only; upgrade: LynJump/stat overlay → if face-up LIGHT_FORCE && !negated && TYPE_FAIRY then ATK/DEF += LIGHT_FORCE_FAIRY_STAT_BONUS.
- L318: not in GetSpellType NORMAL override — face-up OPT re-activation may need card_hooks GetSpellType + LIGHT_FORCE listed (same as CHICKEN_GAME).

### `LIGHTNING_STORM`
- path: `src_custom/spell_effects/lightning_storm.c`
- L118: once-per-turn not tracked after this normal spell leaves the field (no shared turn-flag RAM editable from this file alone). Ceiling: multiple Lightning Storm per turn; upgrade: duel-state OPT bit.
- L133: no dedicated choice UI — A = monsters, B = Spells/Traps. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `LIGHTSWORN_SABRE`
- path: `src_custom/spell_effects/lightsworn_sabre.c`
- L60: stage unit is 500 ATK — applied +500, not printed +700. Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART (ApplyHeatedHeartAtkBonusToCardInfo) after listing LIGHTSWORN_SABRE in IsActiveDynamicEquipSpellZone.
- L72: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add LIGHTSWORN_SABRE to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.
- L77: Deck-to-GY re-equip (when milled) needs a mill/send-from-deck hook outside this file. Ceiling: equip-from-hand/field only; upgrade: mill path → if LIGHTSWORN_SABRE sent from Deck to GY then PickZone Lightsworn and RegisterDynamicEquip again.

### `LIGHTSWORN_SANCTUARY`
- path: `src_custom/spell_effects/lightsworn_sanctuary.c`
- L323: Shine Counters on Deck→GY mill / remove 2 instead of destroy need mill + destroy-gate + counter storage outside this file (DuelCard has no shine-counter field). Ceiling: continuous face-up + OPT recycle only; upgrade: mill hook → ++Shine; Duel_DestroyZone on Lightsworn → if counters >= 2*n then counters -= 2*n and skip destroy.
- L332: not in GetSpellType NORMAL override — face-up OPT re-activation may need card_hooks GetSpellType + LIGHTSWORN_SANCTUARY listed.

### `MAGICIANS_LEFT_HAND`
- path: `src_custom/spell_effects/magicians_left_hand.c`
- L14: negate opponent's first Trap Card/effect each turn (while you control a Spellcaster) then destroy needs a trap-resolve gate + per-turn "first trap used" flag outside this file (no in-file trap negate dispatch; no turn-scoped counter on DuelCard/field). Ceiling: face-up continuous only; upgrade: trap-activate/resolve hook → if

### `MAGICIANS_RIGHT_HAND`
- path: `src_custom/spell_effects/magicians_right_hand.c`
- L14: negate opponent's first Spell Card/effect each turn (while you control a Spellcaster) then destroy needs a spell-resolve gate + per-turn "first spell used" flag outside this file (no in-file spell negate dispatch; no turn-scoped counter on DuelCard/field). Ceiling: face-up continuous only; upgrade: spell-activate/resolve hook → if

### `MARCH_OF_THE_DARK_BRIGADE`
- path: `src_custom/spell_effects/march_of_the_dark_brigade.c`
- L265: once-per-turn activation not tracked (no BSS turn flag editable from this spell file alone). Ceiling: can activate multiple Marches per turn; upgrade: shared OPT RAM bit / effect_usage once_per_turn.

### `MASK_OF_DISPEL`
- path: `src_custom/spell_effects/mask_of_dispel.c`
- L91: Standby Phase 500 burn to the selected Spell's controller needs a turn_effect_hooks Standby path outside this file (clone TryApplyNightmareWheelStandbyDamage). Ceiling: continuous face-up + target stash only; upgrade: Standby → if face-up MASK_OF_DISPEL with unk4 target still present then Duel_ChangeLp(controller, -MASK_OF_DISPEL_STANDBY_DAMAGE).
- L98: self-destroy when selected Spell leaves the field needs a destroy/leave-field listener outside this file. Ceiling: target stash only; upgrade: OnZoneClear → if id matches stashed MASK_OF_DISPEL target then Duel_DestroyZone(mask).

### `MASK_OF_THE_ACCURSED`
- path: `src_custom/spell_effects/mask_of_the_accursed.c`
- L25: attack lock + Standby 500 burn need hooks outside this file. Ceiling: equip registers only (like Raregold Armor without force-target). Upgrade: wire DynamicEquipTargetsMonsterWithSpell(MASK_OF_THE_ACCURSED) into duel_attack_restrictions.c (CannotAttack) and turn_effect_hooks.c (Duel_ChangeLp controller, -MASK_OF_THE_ACCURSED_STANDBY_DAMAGE) — clone

### `MAUSOLEUM_OF_THE_EMPEROR`
- path: `src_custom/spell_effects/mausoleum_of_the_emperor.c`
- L112: no dedicated Summon/Set UI — A = Summon, B = Set. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L224: SpecialSummonFromHandZone still hits ArchlordKristya SS lock and is not a true engine Normal Summon path. Ceiling: no-tribute placement + summoningBlocked; upgrade: dedicated NormalSummonWithoutTribute helper that skips GetNumRequiredTributes pay while using vanilla NS hooks.
- L249: not in GetSpellType NORMAL/FIELD override — face-up OPT re-activation may need card_hooks GetSpellType + MAUSOLEUM listed (same as CHICKEN_GAME / WATERHAZARD).

### `METAMORPHOSIS`
- path: `src_custom/spell_effects/metamorphosis.c`
- L85: Extra Deck Special Summon (Fusion of matching Level) needs a duel-time Extra Deck browser + SS path. Trunk ExtraDeck_* APIs are deck-builder only and must not be used mid-duel. Ceiling: tribute-only; upgrade: ExtraDeck duel pick filtered by COLOR_FUSION + level == tributeLevel, then Duel_SpecialSummonMonsterId.

### `MIRACLE_CONTACT`
- path: `src_custom/spell_effects/miracle_contact.c`
- L16: * ponytail: not in gFusionRecipes — local table only. Ceiling: misses newer Neos

### `MIRAGE_OF_NIGHTMARE`
- path: `src_custom/spell_effects/mirage_of_nightmare.c`
- L106: opponent-Standby draw / next-Standby discard need turn_effect_hooks call to TryApplyMirageOfNightmareStandby (clone Nightmare Wheel wiring). Ceiling: continuous face-up + unk4 pending-discard store only until wired; upgrade: turn_effect_hooks Standby → TryApplyMirageOfNightmareStandby.

### `MOLTING_ESCAPE`
- path: `src_custom/spell_effects/molting_escape.c`
- L62: OPT battle-protect + +300 ATK when applied needs a battle_effects / CanMonsterBeDestroyedByBattle / damage-step hook outside this file (like Spirit Reaper / Kishido via Duel_ApplyBattleDestroyProtection). Ceiling: Reptile equip register only; upgrade: if DynamicEquipTargetsMonsterWithSpell (zone, MOLTING_ESCAPE) and effectUsedThisTurn clear, skip battle destroy once,
- L69: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add MOLTING_ESCAPE to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.

### `MORALE_BOOST`
- path: `src_custom/spell_effects/morale_boost.c`
- L17: equip-on / equip-off LP swing needs field/equip hooks outside this file (RegisterDynamicEquip / OnDynamicEquipZoneAboutToClear / vanilla equip attach-detach). Ceiling: continuous face-up only; upgrade: when any Equip Spell equips → Duel_ChangeLp(controller, +MORALE_BOOST_LP_GAIN); when any Equip Spell leaves field → Duel_ChangeLp(controller, -MORALE_BOOST_DAMAGE).

### `MORPHTRONIC_CORD`
- path: `src_custom/spell_effects/morphtronic_cord.c`
- L57: battle-position-change → destroy 1 S/T needs an external position-change hook (monster_action_menu / battle-position paths). Ceiling: equip-only works; destroy trigger not wired from this file. Upgrade: LynJump position-change → if DynamicEquipTargetsMonsterWithSpell (zone, MORPHTRONIC_CORD) then PickZone destroy one S/T.
- L113: not in GetSpellType EQUIP override — PickZone instead of vanilla equip targeting. Ceiling: add MORPHTRONIC_CORD to card_hooks GetSpellType EQUIP list for pre-target cursor; upgrade path: same as H_HEATED_HEART.

### `MORPHTRONIC_ENGINE`
- path: `src_custom/spell_effects/morphtronic_engine.c`
- L88: stage unit is 500 ATK — nearest-stage double, not exact original×2 when ATK is not a multiple of 500. Ceiling: stage-approx only; upgrade: exact-ATK overlay while equipped (clone Power Bond / Big Bang Shot).
- L106: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting; link cleanup may not treat this as active equip. Ceiling: add MORPHTRONIC_ENGINE to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.
- L111: 2nd Standby destroy + burn original ATK needs turn_effect_hooks call to TryApplyMorphtronicEngineStandby (clone Capsule / Future Fusion wiring). Ceiling: equip + stage ATK only until wired; upgrade: Standby → TryApplyMorphtronicEngineStandby.

### `MORPHTRONIC_MAP`
- path: `src_custom/spell_effects/morphtronic_map.c`
- L107: Morph Counter on battle-position change needs a position-change hook outside this file (no in-file Flip/ChangeBattlePosition dispatch). Ceiling: face-up field + unk4 counter slot (never rises alone); upgrade: after battle position change → if face-up MORPHTRONIC_MAP then zone->unk4++.
- L112: +300 ATK per Morph Counter for Morphtronic monsters needs a field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only covers monster ids registered in duel_helpers.c). Ceiling: face-up field only; upgrade: LynJump/stat overlay → if face-up MORPHTRONIC_MAP and IsMorphtronicMonster(id) then ATK += 300 * zone->unk4
- L119: destroy→GY → optional SS Morphtronic from GY needs a destroy hook + PickZone/GY menu outside this file. Ceiling: field face-up only; upgrade: on ClearZoneAndSendMonToGraveyard of face-up MORPHTRONIC_MAP → PickZone Morphtronic in GY → Duel_SpecialSummonFromGrave.

### `MORPHTRONIC_REPAIR_UNIT`
- path: `src_custom/spell_effects/morphtronic_repair_unit.c`
- L203: cannot change Battle Position — lockMonster / isLocked is the nearest in-file flag (also blocks attack in some validators). Ceiling: battle-position change may still be allowed; upgrade: position-change gate → if DynamicEquipTargetsMonsterWithSpell(zone, MORPHTRONIC_REPAIR_UNIT) then forbid manual position change.
- L213: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone / OnDynamicEquipZoneAboutToClear destroy-equipped list. Ceiling: link may not clean up / destroy equipped on leave; upgrade: add MORPHTRONIC_REPAIR_UNIT beside PREMATURE_BURIAL in dynamic_equip.c.

### `MORPHTRONIC_RUSTY_ENGINE`
- path: `src_custom/spell_effects/morphtronic_rusty_engine.c`
- L87: destroy-burn (orig ATK to both players) needs a field/destroy hook outside this file (e.g. battle_damage / OnDynamicEquipZoneAboutToClear).

### `MYSTIC_MINE`
- path: `src_custom/spell_effects/mystic_mine.c`
- L173: fewer-monsters lock (no monster effects / no attacks) needs CanActivateMonsterEffect + CanDeclareAttack gates outside this file. Ceiling: face-up field + MysticMine_GetLockedFixedDuelist helper only; upgrade: attack/monster-effect gates → if locked duelist matches controller then block.
- L179: End Phase same-count destroy needs turn_effect_hooks call to TryApplyMysticMineEndPhase. Ceiling: face-up field only until wired; upgrade: End Phase → TryApplyMysticMineEndPhase.

### `MYSTIK_WOK`
- path: `src_custom/spell_effects/mystik_wok.c`
- L92: no dedicated ATK/DEF choice UI — A = ATK, B = DEF. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `NECROVALLEY`
- path: `src_custom/spell_effects/necrovalley.c`
- L89: +500 ATK/DEF for Gravekeeper's needs a field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only covers monster ids registered in duel_helpers.c). Ceiling: face-up field only; upgrade: LynJump/stat overlay → if face-up NECROVALLEY and name contains "Gravekeeper" then ATK/DEF += 500.
- L94: GY cannot be banished / moved / Type-Attribute-changed needs GY-move + banish + SetCardInfo-in-GY gates outside this file. Ceiling: continuous face-up only; upgrade: Duel_BanishGraveyard* / GY-to-elsewhere / GY Type-Attribute change → if face-up NECROVALLEY then negate.

### `NECROVALLEY_THRONE`
- path: `src_custom/spell_effects/necrovalley_throne.c`
- L128: no dedicated choice UI — A = add Gravekeeper's, B = Normal Summon. Ceiling: unlabeled buttons; upgrade path: effect-text choice menu.
- L281: no once-per-turn tracker without file BSS / shared OPT flags. Ceiling: can activate multiple Throne copies per turn; upgrade: duel-state OPT bit.

### `NEO_SPACE`
- path: `src_custom/spell_effects/neo_space.c`
- L122: +500 ATK for ELEMENTAL_HERO_NEOS / Neos-listing Fusions needs a field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only covers monster ids registered in duel_helpers.c). Ceiling: face-up field only; upgrade: LynJump/stat overlay → if face-up NEO_SPACE and IsNeoSpaceAtkTarget(id) then ATK += 500.
- L127: Neos-listing Fusions skip End Phase Extra Deck shuffle needs a Contact-return suppress flag outside this file (same as INSTANT_NEO_SPACE). Ceiling: field face-up only; upgrade: End Phase → if face-up NEO_SPACE and IsNeoSpaceAtkTarget(zone) then skip Extra Deck shuffle.

### `NEPHE_SHADDOLL_FUSION`
- path: `src_custom/spell_effects/nephe_shaddoll_fusion.c`
- L134: no attribute-name UI — A confirms, B cycles list. Ceiling: unlabeled; upgrade: effect-text attribute menu.
- L402: declared Attribute is stored in unk4 only — fusion/material checks still use printed SetCardInfo attribute. Ceiling: equip + OPT fusion works; Attribute change cosmetic. Upgrade: MaterialMatches / SourceQualifies reads DynamicEquipTargetsMonsterWithSpell attribute override from unk4.
- L407: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting. Ceiling: add NEPHE_SHADDOLL_FUSION to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone.
- L487: not in GetSpellType NORMAL override — face-up OPT fusion re-activation may need card_hooks GetSpellType + NEPHE_SHADDOLL_FUSION listed (same as WEAPON_CHANGE / CHICKEN_GAME).

### `NEUTRON_BLAST`
- path: `src_custom/spell_effects/neutron_blast.c`
- L89: 2nd/3rd Battle Phase attacks need an attack-completion unlock outside this file (isLocked after attack; clone Cyber Twin / Tryce TryUnlock*ForSecondAttack wired in code_8043EF4 / ai_attack / draining_shield / call_of_the_haunted). Ceiling: mark unkThree only; upgrade: TryUnlockNeutronBlastForExtraAttack + turn-scoped remaining-attack counter
- L97: "opponent's cards and effects cannot be activated until end of Damage Step" when it attacks needs a battle-activation gate outside this file. Ceiling: no activation lock from this file; upgrade: attack-declare / damage-step flag while marked BEUD is attacker → block CanActivateSpell / Trap / monster effects for INACTIVE_DUELIST until Damage Step end.

### `NEX`
- path: `src_custom/spell_effects/nex.c`
- L155: duel Extra Deck browser/SS missing (Trunk ExtraDeck_* is deck-builder only). Ceiling: spawn Lv4 Neo form by id when not in Main Deck; upgrade: Extra Deck pick + SS.

### `OBLITERATE_BLAZE`
- path: `src_custom/spell_effects/obliterate_blaze.c`
- L131: granted effects (pay half LP → destroy S/T + equip 5 Forbidden One as +2000 Equip; piercing) need activated monster hooks / equip system outside this file. Ceiling: marks target unk4=1 only; upgrade: copy Obliterate effects onto marked Exodia monster.

### `OIL`
- path: `src_custom/spell_effects/oil.c`
- L232: once-per-turn activation not tracked (no BSS turn flag editable from this spell file alone). Ceiling: can activate multiple Oils per turn; upgrade: shared OPT RAM bit / effect_usage once_per_turn.

### `ONE_DAY_OF_PEACE`
- path: `src_custom/spell_effects/one_day_of_peace.c`
- L24: neither player takes damage until end of opponent's next turn needs an LP/damage gate outside this file (no damage-immunity helper). Ceiling: both draw only; upgrade: turn_effect / ChangeLp hook → skip damage while One Day of Peace lock is active through opponent's next End Phase.

### `OVER_DESTINY`
- path: `src_custom/spell_effects/over_destiny.c`
- L326: End Phase destroy of the SS'd monster needs a turn_effect hook outside this file (no in-file End Phase destroy queue without BSS). Ceiling: SS only; upgrade: turn_effect_hooks End Phase → destroy marked zone.

### `PAINFUL_CHOICE`
- path: `src_custom/spell_effects/painful_choice.c`
- L153: no committed multi-pick UI — pick 5 in a loop (snake_rain style). Cancel mid-loop auto-fills remaining in deck order.

### `PANDEMONIUM`
- path: `src_custom/spell_effects/pandemonium.c`
- L94: skip Archfiend Standby LP maintenance costs needs a Standby / maintenance-cost gate outside this file. Ceiling: face-up field only; upgrade: Archfiend maintenance pay → if face-up PANDEMONIUM on field then skip LP cost for that Archfiend.
- L99: when an Archfiend is destroyed (not by battle) → that player may add 1 lower-Level Archfiend from Deck needs a destroy/GY listener outside this file. Ceiling: continuous face-up only; upgrade: after-destroy hook → if face-up PANDEMONIUM and destroyed name contains "Archfiend" (not battle) then DeckMenu search Level < destroyed.level.

### `PARALLEL_WORLD_FUSION`
- path: `src_custom/spell_effects/parallel_world_fusion.c`
- L109: no RemovedFromPlay_RemoveAt — shift RFP array in place. Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt.
- L219: "cannot Special Summon except by this effect this turn" needs a turn-scoped SS lock outside this file. Ceiling: Fusion SS only; upgrade: set ArchlordKristya-style / turn flag that blocks other Special Summons.

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

### `PSEUDO_SPACE`
- path: `src_custom/spell_effects/pseudo_space.c`
- L241: name-become + replace effects until End Phase need copy-host / turn_effect hooks outside this file (no per-zone name/effect RAM here). Ceiling: OPT banish Field Spell from GY only; upgrade: store banished id → treat zone as that Field Spell until End Phase clear.
- L262: name-become + replace effects until End Phase — same ceiling as legacy-GY path above.
- L297: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up OPT re-activation may need card_hooks GetSpellType + PSEUDO_SPACE listed. Ceiling: first-activation OPT works; upgrade: add to NORMAL spell-type list.

### `REALM_OF_LIGHT`
- path: `src_custom/spell_effects/realm_of_light.c`
- L14: Shine Counters on mill / +100 ATK per counter on Lightsworn / remove 2 counters instead of destroy need mill + destroy-gate + counter storage outside this file (DuelCard has no shine-counter field; no in-file Deck→GY or destroy dispatch). Ceiling: continuous face-up only; upgrade: mill hook → if face-up REALM_OF_LIGHT controller's Deck→GY then ++counters;

### `REASONING`
- path: `src_custom/spell_effects/reasoning.c`
- L63: no Level-declare UI — D-Pad cycles, A confirms (unlabeled). Ceiling: no on-screen Level readout; upgrade: effect-text Level picker.

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

### `SECOND_COIN_TOSS`
- path: `src_custom/spell_effects/second_coin_toss.c`
- L14: redo coin toss (OPT) needs a shared coin-flip hook wrapping RandRangeU8(0,1) / multi-coin callers (cup_of_ace, suit_of_sword_x, etc.). Ceiling: continuous face-up only; upgrade: after coin resolve, if face-up SECOND_COIN_TOSS on controller's field and effectUsedThisTurn clear, offer redo (player confirm / AI heuristic), re-roll all flips, then mark OPT.

### `SECRET_VILLAGE_OF_THE_SPELLCASTERS`
- path: `src_custom/spell_effects/secret_village_of_the_spellcasters.c`
- L14: Spell activation lock based on Spellcaster control needs a Duel_IsCardActivationBlocked / CanActivateSpell gate outside this file (no in-file spell-activate dispatch). Ceiling: continuous face-up only; upgrade: if face-up SECRET_VILLAGE_OF_THE_SPELLCASTERS on field → count Spellcasters you control vs opponent; if only you control any Spellcaster

### `SECRETS_OF_DARK_MAGIC`
- path: `src_custom/spell_effects/secrets_of_dark_magic.c`
- L318: no dedicated choice UI — A = Fusion, B = Ritual. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.

### `SHADDOLL_FUSION`
- path: `src_custom/spell_effects/shaddoll_fusion.c`
- L241: once-per-turn activation not tracked (no BSS turn flag editable from this file alone). Ceiling: multiple Shaddoll Fusion per turn possible; upgrade: shared OPT RAM bit / effect_usage once_per_turn.
- L245: Extra Deck SS detection uses Fusion/Synchro/Xyz/Link color on opponent's field (no per-zone summon-origin flag). Ceiling: misses Main Deck monsters SS'd from Extra edge cases; upgrade: mark Extra Deck origin on SS.

### `SHARD_OF_GREED`
- path: `src_custom/spell_effects/shard_of_greed.c`
- L61: Greed Counters on normal Draw Phase draw need a draw-phase hook outside this file (no in-file normal-draw dispatch). Ceiling: continuous face-up + ignition when unk4>=2 (never rises alone); upgrade: Draw Phase normal-draw listener → if face-up SHARD_OF_GREED then zone->unk4++ (cap optional).
- L66: not in GetSpellType NORMAL override — face-up re-activation may need card_hooks GetSpellType + SHARD_OF_GREED listed (same as BACKUP_SQUAD / CALL_OF_THE_MUMMY).

### `SHINING_SARCOPHAGUS`
- path: `src_custom/spell_effects/shining_sarcophagus.c`
- L136: printed ignition is Main Phase OPT, not on-activate. Ceiling: one Deck search when this continuous is activated; upgrade: face-up ignition hook → same search with OPT reset.
- L168: cannot be destroyed by monster effects needs destroy-gate outside this file. Ceiling: face-up continuous only; upgrade: destroy validator → if zone id SHINING_SARCOPHAGUS skip monster-effect destroy.
- L172: opp GY Special Summon → discard Spell → send that monster to GY needs summon/trigger hook outside this file.

### `SILVERS_CRY`
- path: `src_custom/spell_effects/silvers_cry.c`
- L167: no once-per-turn tracker without file BSS / shared OPT flags. Ceiling: can activate multiple Silver's Cry per turn; upgrade: duel-state OPT bit.

### `SKYSCRAPER_2_HERO_CITY`
- path: `src_custom/spell_effects/skyscraper_2_hero_city.c`
- L244: no "destroyed by battle" GY filter — no destroy-reason memory on expanded GY cards. Ceiling: any Elemental HERO in GY is legal; upgrade: stamp battle-destroy on GY push / zone→GY, then filter IsElementalHeroMonster && wasDestroyedByBattle.
- L303: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up OPT re-activation may need card_hooks GetSpellType + SKYSCRAPER_2_HERO_CITY listed. Ceiling: first-activation OPT works; upgrade: add to NORMAL list.

### `SNAKE_RAIN`
- path: `src_custom/spell_effects/snake_rain.c`
- L179: no committed multi-pick UI — cancel mid-loop auto-fills remaining reptiles in deck order. Ceiling: player cannot abort partial selection.

### `SOLAR_RECHARGE`
- path: `src_custom/spell_effects/solar_recharge.c`
- L79: mill helper advances deck top only (no expanded-GY push), matching charge_of_the_light_brigade. Ceiling: milled cards may not appear in GY UI.

### `SOUL_SERVANT`
- path: `src_custom/spell_effects/soul_servant.c`
- L28: no card-description text search — approximate "lists DM/DMG" via name contains "Dark Magician" plus a known support ID list. Ceiling: misses text-only mentions. Upgrade: description-string helper.
- L159: no dedicated 3-way choice UI — nested A/B unlabeled. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L484: GY ignition "banish this; draw for distinct Palladium/DM/DMG on field+GYs" needs a GY-activate spell path outside this file. Ceiling: on-field stack-to-Deck only; upgrade: GY activate → banish SOUL_SERVANT → Duel_DrawCards(count distinct Palladium/DM/DMG names).

### `SPELL_CHRONICLE`
- path: `src_custom/spell_effects/spell_chronicle.c`
- L68: no simple Deck→banish helper for arbitrary ST — mill to GY as stand-in for the 5 banished. Ceiling: cards go to GY not banished; upgrade: Duel_BanishDeckCardAt.
- L138: Deck banish pushes via GraveyardExpand then Banish top — approx by pushing GY then Duel_BanishGraveyardTopTurn. Ceiling: briefly hits GY; upgrade: direct deck→RFG.
- L151: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses banished add / leave-field burn need continuous hooks outside this file. Ceiling: activate discard+banish 5 only; unk4 counter slot unused.

### `SPELL_GEAR`
- path: `src_custom/spell_effects/spell_gear.c`
- L190: "cannot Normal Summon/Set until end of your next turn" needs a multi-turn NS lock outside this file. Ceiling: field send + AGG SS + cleanup only; upgrade: turn_effect flag blocking Normal Summon/Set for 2 turns.
- L203: no committed multi-pick UI — cancel mid-loop auto-fills remaining Ancient Gear zones in row order. Ceiling: player cannot abort partial pick.

### `SUPREME_KINGS_CASTLE`
- path: `src_custom/spell_effects/supreme_kings_castle.c`
- L89: "Fusion Summon monsters that must be Special Summoned with Dark Fusion, with effects other than Dark Fusion" needs a global Dark-Fusion- substitute flag checked by Evil HERO summon gates outside this file. Ceiling: face-up field only; upgrade: summon validators → if face-up SUPREME_KINGS_CASTLE then treat non-Dark-Fusion FS as Dark Fusion.
- L95: once-per-turn damage-calc send 1 Evil HERO from Deck/Extra → GY and battling Fiend gains Level×200 ATK needs a battle_effects damage-calc hook outside this file (like skyscraper.c). Ceiling: face-up field only; upgrade: ApplySupremeKingsCastleBattleAtkBoost → if face-up SUPREME_KINGS_CASTLE, !effectUsedThisTurn, attacker is Fiend

### `THE_A_FORCES`
- path: `src_custom/spell_effects/the_a_forces.c`
- L14: continuous +200 ATK per Warrior/Spellcaster you control on your Warriors needs a field-stat / continuous ATK overlay outside this file (no in-file hook into Duel_TryApplyDynamicZoneStats or Refresh overlays). Ceiling: face-up continuous only; upgrade: stat overlay → if face-up THE_A_FORCES then each face-up Warrior you control ATK += 200 *

### `THE_CLAW_OF_HERMOS`
- path: `src_custom/spell_effects/the_claw_of_hermos.c`
- L40: OPT needs turn-scoped flag cleared outside this file. Ceiling: multiple Claw per turn until soft-reset; upgrade: Standby clear.
- L193: no dedicated field/hand choice UI — A = field, B = hand. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L352: Set reveal has no dedicated flip UI — send face-down as-is. Ceiling: no reveal animation; upgrade: brief face-up before GY send.

### `THE_EYE_OF_TIMAEUS`
- path: `src_custom/spell_effects/the_eye_of_timaeus.c`
- L26: OPT bit never cleared mid-duel without turn_effect reset hook. Ceiling: blocks 2nd Eye of Timaeus only until soft-reset / new duel BSS; upgrade: turn_effect Standby → sEyeOfTimaeusUsedThisTurn = 0.
- L257: "also always treated as Legendary Dragon Timaeus" name-treat needs a name-alias outside this file. Ceiling: fusion via listed DM material only; upgrade: Duel_GetEffectiveCardId / name-contains Legendary Dragon Timaeus.

### `THE_FANG_OF_CRITIAS`
- path: `src_custom/spell_effects/the_fang_of_critias.c`
- L21: OPT bit never cleared mid-duel without turn_effect reset hook. Ceiling: blocks 2nd Fang only until soft-reset / new duel BSS; upgrade: turn_effect Standby → sFangOfCritiasUsedThisTurn = 0.
- L155: no dedicated hand/field choice UI — A = hand, B = field. Ceiling: unlabeled buttons; upgrade: effect-text choice menu.
- L358: "always treated as Legendary Dragon Critias" name/tag needs a treat-as outside this file. Ceiling: activation + trap-send + Extra Deck SS only; upgrade: name-contains / archetype tag = Legendary Dragon Critias.

### `THE_GAZE_OF_TIMAEUS`
- path: `src_custom/spell_effects/the_gaze_of_timaeus.c`
- L21: OPT flag never clears without a turn-end hook outside this file. Ceiling: once per duel after first activation; upgrade: turn_effect_hooks End Phase / turn-start → sGazeOfTimaeusUsedThisTurn = 0.
- L390: End Phase banish of the Fusion during the next turn needs a turn_effect queue outside this file. Ceiling: Fusion SS + shuffle only; upgrade: mark summoned zone + turn_effect End Phase (controller's next End Phase) → Duel_BanishZone. "Treated as Eye of Timaeus" name checks also need a summon-tag outside this file.

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

### `TWLIGHT_TWIN_DRAGONS`
- path: `src_custom/spell_effects/twlight_twin_dragons.c`
- L241: mill helper advances deck top only (no expanded-GY push), matching charge_of_the_light_brigade. Ceiling: milled cards may not appear in GY UI.
- L244: Deck-to-GY by Lightsworn → add Punishment Dragon from GY + banish top 4 needs a mill/send-from-deck hook outside this file. Ceiling: on-activate JD recycle + mill only; upgrade: if TWLIGHT_TWIN_DRAGONS sent Deck→GY by Lightsworn effect → PickZone PD in GY → hand, then banish top 4.

### `ULTRA_POLYMERIZATION`
- path: `src_custom/spell_effects/ultra_polymerization.c`
- L172: "neither player can activate cards/effects in response" needs a response-lock flag outside this file (trap/chain gate). Ceiling: LP pay + field-only 2-material Fusion; upgrade: set no-response flag around Duel_TryResolveSpellThroughTrapsEx / activation.
- L177: GY ignition "banish this card, target 1 Fusion Summoned by this card; SS all materials used from GY, ATK/DEF 0, effects negated" needs GY activation + material-memory outside this file. Ceiling: on-field Fusion only; upgrade: store material ids on summon tag → GY activate ULTRA_POLYMERIZATION → Duel_BanishGraveyard → SS materials with

### `UNSTABLE_EVOLUTION`
- path: `src_custom/spell_effects/unstable_evolution.c`
- L97: ApplyDynamicEquipStages / RemoveDynamicEquipStages only track positive IncrementPermStage equips (TRYCE is the sole negative special case, outside this file). Ceiling: ATK cut applied once; unequip does not restore the cut. Upgrade: list UNSTABLE_EVOLUTION in RemoveDynamicEquipStages like TRYCE (Decrement on apply / Increment on remove), or exact original-ATK
- L117: LP-conditional original ATK (2400 if lower / 1000 if higher) needs continuous refresh while equipped when LP changes, plus exact original-ATK overlay (stage unit is 500). Ceiling: one-shot nearest-stage adjust at equip from printed original; equal LP leaves ATK unchanged. Upgrade: card_info / RecalculateDynamicEquips → if DynamicEquipTargetsMonster
- L124: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone instead of vanilla equip targeting. Ceiling: add UNSTABLE_EVOLUTION to card_hooks GetSpellType EQUIP list and dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART.

### `VENOM_SHOT`
- path: `src_custom/spell_effects/venom_shot.c`
- L259: Venom Counters need per-monster counter storage + End Phase ATK drain (see venom_swamp.c). Ceiling: send Reptile + target only; upgrade: place VENOM_SHOT_COUNTERS on zone, apply -500 ATK per counter / destroy at 0.

### `VENOM_SWAMP`
- path: `src_custom/spell_effects/venom_swamp.c`
- L14: End Phase Venom Counters / -500 ATK per counter / destroy at 0 ATK need an End Phase turn_effect hook + per-monster counter storage outside this file (DuelCard has no venom-counter field; no in-file End Phase dispatch). Ceiling: continuous face-up only; upgrade: turn_effect End Phase → if face-up VENOM_SWAMP then place 1 counter on each face-up non-Venom monster, apply

### `VIPERS_REBIRTH`
- path: `src_custom/spell_effects/vipers_rebirth.c`
- L221: End Phase destroy of the SS'd monster needs a turn_effect hook outside this file (no in-file End Phase destroy queue without BSS). Ceiling: SS only; upgrade: turn_effect_hooks End Phase → destroy marked zone.

### `VISION_FUSION`
- path: `src_custom/spell_effects/vision_fusion.c`
- L18: OPT flag never clears without a turn-end hook outside this file. Ceiling: once per duel after first activation; upgrade: turn_effect_hooks End Phase / turn-start → sVisionFusionUsedThisTurn = 0.

### `WATERHAZARD`
- path: `src_custom/spell_effects/waterhazard.c`
- L104: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up OPT re-activation may need card_hooks GetSpellType + WATERHAZARD listed. Ceiling: first-activation OPT works; upgrade: add to NORMAL spell-type list.

### `WEAPON_CHANGE`
- path: `src_custom/spell_effects/weapon_change.c`
- L107: Riryoku only adjusts ATK — DEF does not become the old ATK from this file alone. Ceiling: ATK becomes current DEF; DEF unchanged. Upgrade: ShieldAndSword-style per-zone swap flag in SetFinalStat that swaps both stats until end of opponent's next turn.
- L111: duration is "until end of opponent's next turn" but Riryoku deltas clear every End Phase (ClearAllRiryokuAtkDeltas). Ceiling: lasts until next EOT clear; upgrade: turn_effect_hooks 2-End-Phase counter.
- L208: printed "once during each of your Standby Phases" needs a turn_effect_hooks Standby gate outside this file. Ceiling: face-up OPT ignition any phase (Main-style re-activate); upgrade: Standby-only CanActivate + auto-prompt, or GetSpellType NORMAL list like CALL_OF_THE_MUMMY.

### `WETLANDS`
- path: `src_custom/spell_effects/wetlands.c`
- L87: +1200 ATK for Aqua/WATER/Level≤2 needs a field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only covers monster ids registered in duel_helpers.c). Ceiling: face-up field only; upgrade: LynJump/stat overlay → if face-up WETLANDS and TYPE_AQUA + ATTRIBUTE_WATER + level≤2 then ATK += 1200.

## trap (115)

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

### `ALL_OUT_ATTACKS`
- path: `src_custom/trap_effects/all_out_attacks.c`
- L11: when monster(s) SS while face-up → change to ATK and must attack that turn. Ceiling: face-up continuous only; upgrade: SS hook → isDefending=FALSE + forced-attack flag. Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file.
- L22: TryActivateALL_OUT_ATTACKSOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `AMAZONESS_HALL`
- path: `src_custom/trap_effects/amazoness_hall.c`
- L72: TryActivateAMAZONESS_HALLOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `AMAZONESS_HOT_SPRING`
- path: `src_custom/trap_effects/amazoness_hot_spring.c`
- L77: TryActivateAMAZONESS_HOT_SPRINGOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `AMAZONESS_ONSLAUGHT`
- path: `src_custom/trap_effects/amazoness_onslaught.c`
- L20: Battle Phase OPT SS + after-damage banish + leave GY search need battle/leave hooks. Ceiling: SS 1 Amazoness from hand +1 stage (~500 ATK).
- L60: TryActivateAMAZONESS_ONSLAUGHTOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `AMAZONESS_WILLPOWER`
- path: `src_custom/trap_effects/amazoness_willpower.c`
- L62: must-attack + mutual destroy-on-leave need battle/leave hooks.

### `AMBUSH_FANGS`
- path: `src_custom/trap_effects/ambush_fangs.c`
- L17: printed trigger is face-up Venom targeted for attack. Ceiling: when Effect runs, place Venom Counter on origin attacker + self-destroy (negate/end BP not wired); upgrade: attack-target hook on Venom + NegateAttack + end Battle Phase.

### `ANCIENT_GEAR_DUEL`
- path: `src_custom/trap_effects/ancient_gear_duel.c`
- L45: unaffected by opp monster effects + Extra Deck Fusion + 3 attacks need protection/fusion/battle hooks. Ceiling: mark AG Golem/mentioners (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY and SS Ultimate Ancient Gear Golem stand-in from Deck/hand.
- L110: TryActivateANCIENT_GEAR_DUELOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `ANGELS_TEAR`
- path: `src_custom/trap_effects/angels_tear.c`
- L342: need 4 banish targets plus 1 summon target.

### `ANTI_SPELL_FRAGRANCE`
- path: `src_custom/trap_effects/anti_spell_fragrance.c`
- L11: both players must Set Spells before activate (next turn) needs spell-activation gate. Ceiling: face-up continuous only; upgrade: spell activate validator requires prior Set + turn delay. Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file.
- L22: TryActivateANTI_SPELL_FRAGRANCEOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `APPARATION`
- path: `src_custom/trap_effects/apparation.c`
- L37: printed trigger is HERO destroy. Ceiling: if origin was a HERO monster OR we control a HERO, allow Deck SS.

### `APPROPRIATE`
- path: `src_custom/trap_effects/appropriate.c`
- L11: activate when opp draws outside Draw Phase; then each such draw → you draw 2. Ceiling: face-up continuous only; upgrade: non-Draw-Phase draw hook → Duel_DrawCards(controller, 2). Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file.
- L22: TryActivateAPPROPRIATEOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `ARCANA_CALL`
- path: `src_custom/trap_effects/arcana_call.c`
- L81: until EP, selected AF uses banished AF's coin effect — needs End Phase clear + Arcana effect dispatch override. Ceiling: marks field monster; GY Arcana banished.

### `ATTACK_AND_RECEIVE`
- path: `src_custom/trap_effects/attack_and_receive.c`
- L48: activate when you take damage. Ceiling: burn 700 + 300×GY copies.

### `ATTACK_GUIDANCE_ARMOR`
- path: `src_custom/trap_effects/attack_guidance_armor.c`
- L15: attack-declare choice Destroy OR redirect target. Ceiling: destroy declared attacker (origin) when Effect runs.

### `BACKFIRE`
- path: `src_custom/trap_effects/backfire.c`
- L11: FIRE monster destroyed → 500 to opp needs destroy hook. Ceiling: face-up continuous only; upgrade: OnDestroy FIRE face-up owned → Duel_ChangeLp(opp, -500). Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file.
- L22: TryActivateBACKFIREOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `BATTLE_MANIA`
- path: `src_custom/trap_effects/battle_mania.c`
- L16: activate only opp Standby. Ceiling: when Effect runs, flip opp monsters to ATK; forced-attack / cannot-change-position need battle gates.

### `BLESSED_WINDS`
- path: `src_custom/trap_effects/blessed_winds.c`
- L51: 3 OPT modes + once-per-turn flag need ignition menu. Ceiling on activate: prefer pay 1000 → SS Aroma from GY; else send Plant → +500 LP; else shuffle Plant from GY → +500 LP.
- L103: TryActivateBLESSED_WINDSOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `BOTTOMLESS_SHIFTING_SAND`
- path: `src_custom/trap_effects/bottomless_shifting_sand.c`
- L10: GBA hand cap is 5; TCG rule uses 4 — scale self-destruct threshold down

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
- L103: TryActivateD_TACTICSOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

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

### `DES_COUNTERBLOW`
- path: `src_custom/trap_effects/des_counterblow.c`
- L11: destroy monster that inflicts direct battle damage needs battle LP hook. Ceiling: face-up continuous only; upgrade: after direct battle damage → Duel_DestroyZone(attacker). Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file.
- L22: TryActivateDES_COUNTERBLOWOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `DESTINED_RIVALS`
- path: `src_custom/trap_effects/destined_rivals.c`
- L53: effectExhausted until EP + OPT turn reset need End Phase / turn_effect clear. Ceiling: marks opp face-up monsters exhausted.

### `DOPPELGANGER`
- path: `src_custom/trap_effects/doppelganger.c`
- L11: when you take monster-effect damage → mirror to opp needs LP/effect-damage hook. Ceiling: face-up continuous only; upgrade: after effect damage from opp monster → Duel_ChangeLp(opp, -same). Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file.
- L22: TryActivateDOPPELGANGEROnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `DRAGON_S_RAGE`
- path: `src_custom/trap_effects/dragon_s_rage.c`
- L11: Dragon piercing needs battle damage calc hook outside this file. Ceiling: face-up continuous only; upgrade: if face-up DRAGON_S_RAGE and attacker TYPE_DRAGON vs Defense Position → piercing.
- L21: wire TryActivate into turn_effect_hooks.

### `DRAMATIC_RESCUE`
- path: `src_custom/trap_effects/dramatic_rescue.c`
- L41: printed trigger is card targeting an Amazoness. Ceiling: bounce origin-row monster if Amazoness + SS other from hand; upgrade: target-chain hook when target passes Duel_IsAmazonessCard.

### `DRIED_WINDS`
- path: `src_custom/trap_effects/dried_winds.c`
- L47: LP-gain destroy + OPT flags need LP-gain hook. Ceiling: if Aroma + LP≥opp+3000, pay difference and destroy opp face-up monsters while remaining budget covers printed ATK.
- L90: TryActivateDRIED_WINDSOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `DUST_TORNADO`
- path: `src_custom/trap_effects/dust_tornado.c`
- L112: optional hand pick — B skips; upgrade path: shared helper in exchange_hand_selection

### `ETERNAL_SOUL`
- path: `src_custom/trap_effects/eternal_soul.c`
- L75: DM unaffected by opp + destroy all on leave need protection / leave hooks. Ceiling: OPT stand-in — SS Dark Magician from hand/GY, else search Dark Magic Attack / Thousand Knives.
- L111: TryActivateETERNAL_SOULOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `EXCHANGE_OF_THE_SPIRIT`
- path: `src_custom/trap_effects/exchange_of_the_spirit.c`
- L32: full Deck↔GY swap is heavy — approximate by pushing all GY to deck bottom and rebuilding GY from current undrawn deck top chunk. Ceiling: incomplete swap if GY expand / deck sizes mismatch; upgrade: proper dual-buffer swap of entire Deck and GY stacks.

### `FAIRY_BOX`
- path: `src_custom/trap_effects/fairy_box.c`
- L96: age both fixed backrows so a trap set last turn is live when the other duelist attacks

### `FAVOURITE_CONTACT`
- path: `src_custom/trap_effects/favourite_contact.c`
- L48: Extra Deck Fusion ignoring summon conditions + materials to Deck bottom need fusion recipe API. Ceiling: return up to 2 HERO/Neos/ Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free.

### `FORGOTTEN_TEMPLE_OF_THE_DEEP`
- path: `src_custom/trap_effects/forgotten_temple_of_the_deep.c`
- L34: name-becomes-Umi + End Phase return need field-name/turn hooks. Ceiling: once on activate, banish one Lv4- Fish/SS/Aqua you control.
- L56: TryActivateFORGOTTEN_TEMPLE_OF_THE_DEEPOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `FOSSIL_EXCAVATION`
- path: `src_custom/trap_effects/fossil_excavation.c`
- L78: negate SS effects + mutual destroy-on-leave need leave hooks.

### `GIFT_CARD`
- path: `src_custom/trap_effects/gift_card.c`
- L20: TryActivateGIFT_CARDOnOpponentTurnStart must be called from turn_effect_hooks (opp turn start). Ceiling: body ready, not wired; upgrade: add call next to Jar of Greed turn-start activations.

### `GLADIATOR_BEAST_WAR_CHARIOT`
- path: `src_custom/trap_effects/gladiator_beast_war_chariot.c`
- L32: negate Effect Monster activation + destroy needs negation hook. Ceiling: destroys origin monster if present; upgrade: full negate.

### `GLADIATOR_BEASTS_MEDUSA_SHIELD`
- path: `src_custom/trap_effects/gladiator_beasts_medusa_shield.c`
- L46: cannot be destroyed by card effects / OPT negate opp monster / if sent GY this turn Set GB Trap from Deck need destroy/negate/GY hooks. Ceiling: continuous face-up + marks only.
- L55: needs trapEffect ID + dispatcher wire + PickZone.

### `GLADIATOR_BEASTS_VALOR`
- path: `src_custom/trap_effects/gladiator_beasts_valor.c`
- L32: opp can only attack GB monsters needs attack-target gate. Ceiling: face-up continuous only.

### `GLADIATOR_NAUMACHIA`
- path: `src_custom/trap_effects/gladiator_naumachia.c`
- L44: forced attack + destroy-search GB from Deck need battle/destroy hooks. Ceiling: if GB on field, mark opp must-attack; shuffle 1 GB from hand/GY and boost 1 GB by +1 stage (~original DEF stand-in).
- L102: TryActivateGLADIATOR_NAUMACHIAOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `GLORIOUS_ILLUSION`
- path: `src_custom/trap_effects/glorious_illusion.c`
- L70: End Phase mill 2 + mutual destroy-on-leave need turn/leave hooks.

### `GRAVEKEEPERS_TRAP`
- path: `src_custom/trap_effects/gravekeepers_trap.c`
- L83: Exchange lock GY effects/SS + opp Draw Phase look + discard cost need GY/draw gates. Ceiling: if Exchange in GY mark unk4 lock; discard 1 → search Gravekeeper's / EARTH Fairy.
- L118: TryActivateGRAVEKEEPERS_TRAPOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `GRAVITY_BIND`
- path: `src_custom/trap_effects/gravity_bind.c`
- L64: face-down GB still blocks the declare; AI sim restore keeps it face-down every trial

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

### `LIGHT_OF_DESTRUCTION`
- path: `src_custom/trap_effects/light_of_destruction.c`
- L11: when opp effect mills their Deck → mill top 3 needs mill hook. Ceiling: face-up continuous only; upgrade: after opp Deck→GY by effect → send top 3 of that Deck to GY.

### `LIGHT_SPIRAL`
- path: `src_custom/trap_effects/light_spiral.c`
- L11: Lightsworn mill → banish opp top Deck needs mill hook. Ceiling: face-up continuous only.

### `LIGHTSWORN_AEGIS`
- path: `src_custom/trap_effects/lightsworn_aegis.c`
- L63: until EP negate + mill-from-Deck Set this card + OPT need End Phase clear / mill hook / turn reset. Ceiling: exhausts up to LS-count opp face-ups.

### `LIGHTSWORN_BARRIER`
- path: `src_custom/trap_effects/lightsworn_barrier.c`
- L13: LS targeted for attack → mill top 2 → negate attack needs attack- declaration hook. Ceiling: face-up continuous only; upgrade: on attack target if Duel_CardNameContains(defender, Lightsworn) → mill 2 + NegateAttack.

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
- L83: TryActivateMAGICIANS_COMBINATIONOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

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

### `MORPHTRONIC_BIND`
- path: `src_custom/trap_effects/morphtronic_bind.c`
- L13: while face-up Morphtronic controlled, opp Lv≥4 cannot attack or change battle position needs attack/position gates. Ceiling: face-up continuous only.

### `MORPHTRONIC_FORCEFIELD`
- path: `src_custom/trap_effects/morphtronic_forcefield.c`
- L81: negate ST that would destroy face-up Morphtronic needs destroy- targeting chain gate. Ceiling: destroy origin ST if present + search Morphtronic; upgrade: full negate + trapEffect.

### `MORPHTRONIC_IMPACT_RETURN`
- path: `src_custom/trap_effects/morphtronic_impact_return.c`
- L38: GY banish SS Morphtronic need GY ignition. Ceiling: shuffle 1 Morphtronic from hand into Deck, shuffle up to 2 opp S/T into Deck.

### `MORPHTRONIC_MIXUP`
- path: `src_custom/trap_effects/morphtronic_mixup.c`
- L75: PickZone for 2 targets + opp choice UI; trapEffect wire.

### `MORPHTRONIC_MONITRON`
- path: `src_custom/trap_effects/morphtronic_monitron.c`
- L14: when Morphtronic Summoned → optional to Defense needs summon hook. Ceiling: face-up continuous only.

### `NECROVALLEY_TEMPLE`
- path: `src_custom/trap_effects/necrovalley_temple.c`
- L90: -500 ATK/DEF while GK+Necrovalley need stat overlay; destroy-Set Necrovalley S/T from Deck need destroy hook. Ceiling: if GK present, try place Necrovalley from hand/GY; mark opp monsters -1 stage.
- L115: TryActivateNECROVALLEY_TEMPLEOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `NEEDLE_WALL`
- path: `src_custom/trap_effects/needle_wall.c`
- L44: TryActivateNEEDLE_WALLOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired. Standby re-roll not looped.

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

### `SERPENT_SUPPRESSION`
- path: `src_custom/trap_effects/serpent_suppression.c`
- L14: opp 0-ATK Attack Position cannot be destroyed by battle with Reptilianne needs battle-destroy gate. Ceiling: face-up continuous only.

### `SHADDOLL_CORE`
- path: `src_custom/trap_effects/shaddoll_core.c`
- L45: true trap-monster (still a Trap) + Attribute fusion substitute need Embodiment-style link. Ceiling: place SHADDOLL_CORE on monster row and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate.

### `SHADDOLL_SCHISM`
- path: `src_custom/trap_effects/shaddoll_schism.c`
- L40: full Fusion Summon from Extra by banishing listed materials + Attribute-match send need fusion recipe picker. Ceiling: banish up to 2 Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct attack mark via unk4.
- L83: TryActivateSHADDOLL_SCHISMOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

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

### `SOUL_LEVY`
- path: `src_custom/trap_effects/soul_levy.c`
- L11: only control 1 + each opp SS → mill top 3 opp Deck need unique- continuous + summon hook. Ceiling: face-up continuous only; upgrade: after opp Special Summon → send top 3 of opp Deck to GY.

### `SPARK_BLASTER`
- path: `src_custom/trap_effects/spark_blaster.c`
- L40: Main Phase OPT change battle position of 1 face-up + destroy after 3 uses need ignition + counter. Ceiling: equips to Sparkman; unk4 use counter starts at 0.

### `THUMBS_DOWN`
- path: `src_custom/trap_effects/thumbs_down.c`
- L31: destroy by battle/effect → controller takes 500 each needs destroy hook. Ceiling: face-up continuous only.

### `TORNADO_WALL`
- path: `src_custom/trap_effects/tornado_wall.c`
- L11: activate only while Umi on field; no battle damage while Umi face-up; destroy when Umi leaves. Ceiling: face-up continuous only; upgrade: Umi field check on activate + battle-damage gate + Umi leave destroy. Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file.
- L22: TryActivateTORNADO_WALLOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `TOUR_OF_DOOM`
- path: `src_custom/trap_effects/tour_of_doom.c`
- L11: opp Standby coin → Heads: opp cannot NS/Flip until EP; Tails: you cannot next turn. Ceiling: face-up continuous only; upgrade: Standby turn_effect → RandRange coin + summoningBlocked flags. Ceiling: face-up continuous only; upgrade: wire trigger/gate outside this file.
- L22: TryActivateTOUR_OF_DOOMOnOpponentTurnStart must be called from turn_effect_hooks. Ceiling: body ready, not wired.

### `TRAP_DUSTSHOOT`
- path: `src_custom/trap_effects/trap_dustshoot.c`
- L67: look at full hand + choose monster UI; trapEffect wire. Ceiling: auto first monster in opp hand → Deck shuffle.

### `TRAP_TRICK`
- path: `src_custom/trap_effects/trap_trick.c`
- L29: no Continuous/Counter trap type split — treat all traps as Normal.
- L101: "can activate this turn" — leave unlocked.
- L110: only 1 Trap activate rest of turn + OPT reset need gates.

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
