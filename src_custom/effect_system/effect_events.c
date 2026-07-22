#include "global.h"
#include "common-chax.h"
#include "ancient_gear_advance.h"
#include "ancient_gear_drill.h"
#include "ancient_gear_factory.h"
#include "berserker_soul.h"
#include "chain_summoning.h"
#include "cold_wave.h"
#include "contact_gate.h"
#include "dark_contact.h"
#include "dark_fusion.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "en_engage_neo_space.h"
#include "effect_events.h"
#include "effect.h"
#include "amazoness_empress.h"
#include "evil_assault.h"
#include "forbidden_chalice.h"
#include "forbidden_dress.h"
#include "forbidden_lance.h"
#include "fusion_deployment.h"
#include "fusion_destiny.h"
#include "hidden_temples_of_necrovalley.h"
#include "parallel_world_fusion.h"
#include "second_coin_toss.h"
#include "spell_gear.h"
#include "supreme_kings_castle.h"
#include "tornado_wall.h"
#include "triangle_ecstasy_spark.h"
#include "destined_rivals.h"
#include "meteorain.h"
#include "harpies_feather_storm.h"
#include "harpie_lady_elegance_lock.h"
#include "alector_sovereign_of_birds.h"
#include "el_shaddoll_winda.h"
#include "amazoness_scouts.h"
#include "ancient_gear_cannon.h"
#include "el_shaddoll_wendigo.h"
#include "ancient_gear_frame.h"
#include "birdface.h"
#include "babycerasaurus.h"
#include "charm_of_shabti.h"
#include "colossal_fighter.h"
#include "gravekeepers_nobleman.h"
#include "morphtronic_cameran.h"
#include "mucus_yolk.h"
#include "spell_effects.h"
#include "troop_dragon.h"
#include "ultimate_ancient_gear_golem.h"
#include "warm_worm.h"
#include "zeradias_herald_of_heaven.h"
#include "gravekeepers_recruiter.h"
#include "green_baboon_defender_of_the_forest.h"
#include "crimson_blader.h"
#include "destiny_hero_captain_tenacious.h"
#include "aroma_lp_gain.h"
#include "destiny_hero_dreamer.h"
#include "necrovalley_temple.h"

extern EffectEventHandler gEffectEventHandlers[EFFECT_EVENT_COUNT][EFFECT_EVENT_MAX_SUBSCRIBERS];
extern u8 gEffectEventHandlerCounts[EFFECT_EVENT_COUNT];
extern u16 gEffectOptUsedIds[EFFECT_OPT_MAX_CARDS];
extern u8 gEffectOptUsedCount;
extern u8 gEffectActivationNegated;

void DestinyHeroFearMonger_EnsureInit(void);
void DestinyHeroCaptainTenacious_EnsureInit(void);
void TheWhiteStoneOfAncients_EnsureInit(void);
void AmazonessEmpress_EnsureInit(void);
void DestinyHeroDoubleDude_EnsureInit(void);
void EvilHeroDarkestKnight_EnsureInit(void);
void CuriousTheLightswornDominion_EnsureInit(void);
void DarkMagicianDestroyRevive_EnsureInit(void);
void ElderEntityNorden_EnsureInit(void);
void GladiatorBeastDarius_EnsureInit(void);
void EvilHeroViciousClaws_EnsureInit(void);

static u8 sEffectEventsInited APPEND_DATA = {0};

static void EffectEvent_OnFieldChangeHandler(const struct EffectEvent *ev)
{
  (void)ev;

  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();
  Duel_CheckAmazonessTigerAfterFieldChange();
  HiddenTemplesOfNecrovalley_CheckAfterFieldChange();
  TryMaintainZeradiasHeraldOfHeaven();

  /* Rivalry / Ring text flips skip AI-sim (gHideEffectText). */
  if (gHideEffectText)
    return;

  Duel_CheckRivalryOfWarlordsAfterFieldChange();
  Duel_CheckRingOfDestructionAfterFieldChange();
  TornadoWall_CheckAfterFieldChange();
}

void EffectEvent_EnsureInit(void)
{
  if (sEffectEventsInited)
    return;

  sEffectEventsInited = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_FIELD_CHANGE, EffectEvent_OnFieldChangeHandler);
  DestinyHeroFearMonger_EnsureInit();
  DestinyHeroCaptainTenacious_EnsureInit();
  TheWhiteStoneOfAncients_EnsureInit();
  AmazonessEmpress_EnsureInit();
  DestinyHeroDoubleDude_EnsureInit();
  EvilHeroDarkestKnight_EnsureInit();
  AncientGearFrame_EnsureInit();
  Birdface_EnsureInit();
  TroopDragon_EnsureInit();
  ColossalFighter_EnsureInit();
  MorphtronicCameran_EnsureInit();
  GravekeepersNobleman_EnsureInit();
  WarmWorm_EnsureInit();
  MucusYolk_EnsureInit();
  UltimateAncientGearGolem_EnsureInit();
  Babycerasaurus_EnsureInit();
  GravekeepersRecruiter_EnsureInit();
  GreenBaboon_EnsureInit();
  AromaLpGain_EnsureInit();
  NecrovalleyTemple_EnsureInit();
  CuriousTheLightswornDominion_EnsureInit();
  DarkMagicianDestroyRevive_EnsureInit();
  ElderEntityNorden_EnsureInit();
  GladiatorBeastDarius_EnsureInit();
  EvilHeroViciousClaws_EnsureInit();
  DestinyHeroDreamer_EnsureInit();
  /* Damage-calc ATK boosts: Effect_DispatchEvent → sEffectsExtra CONTINUOUS. */
}

void EffectEvent_Subscribe(u8 eventId, EffectEventHandler handler)
{
  u8 i;
  u8 n;

  if (eventId >= EFFECT_EVENT_COUNT || handler == NULL)
    return;

  n = gEffectEventHandlerCounts[eventId];
  for (i = 0; i < n; i++) {
    if (gEffectEventHandlers[eventId][i] == handler)
      return;
  }

  if (n >= EFFECT_EVENT_MAX_SUBSCRIBERS)
    return;

  gEffectEventHandlers[eventId][n] = handler;
  gEffectEventHandlerCounts[eventId] = n + 1;
}

void EffectEvent_Emit(const struct EffectEvent *ev)
{
  u8 i;
  u8 n;

  EffectEvent_EnsureInit();

  if (ev == NULL || ev->type >= EFFECT_EVENT_COUNT)
    return;

  /* Registered Effects (TRIGGER / CONTINUOUS) — YGOPRO-style by code. */
  Effect_DispatchEvent(ev);

  n = gEffectEventHandlerCounts[ev->type];
  for (i = 0; i < n; i++) {
    if (gEffectEventHandlers[ev->type][i] != NULL)
      gEffectEventHandlers[ev->type][i](ev);
  }
}

void EffectEvent_EmitSimple(u8 eventId, u16 cardId, struct DuelCard *zone)
{
  struct EffectEvent ev;
  u8 fixedRow;
  u8 col;

  ev.type = eventId;
  ev.cardId = cardId;
  ev.fixedRow = 0xFF;
  ev.col = 0xFF;
  ev.controller = 0xFF;
  ev.flags = 0;
  ev.param = 0;
  ev.zone = zone;

  if (zone != NULL && Duel_FindFixedZone(zone, &fixedRow, &col)) {
    ev.fixedRow = fixedRow;
    ev.col = col;
    if (Duel_IsFixedMonsterRow(fixedRow))
      ev.controller = Duel_FixedDuelistForMonsterRow(fixedRow);
    else
      ev.controller = GetDuelistForZone(zone);
  }

  EffectEvent_Emit(&ev);
}

void EffectEvent_EmitLpChange(u8 controller, s32 delta)
{
  struct EffectEvent ev;
  u32 mag;

  if (delta == 0 || controller > DUEL_OPPONENT)
    return;

  if (delta < 0)
    mag = (u32)(-delta);
  else
    mag = (u32)delta;
  if (mag > 0xFFFF)
    mag = 0xFFFF;

  ev.type = (delta > 0) ? EFFECT_EVENT_ON_LP_GAIN : EFFECT_EVENT_ON_LP_LOSS;
  ev.cardId = CARD_NONE;
  ev.fixedRow = 0xFF;
  ev.col = 0xFF;
  ev.controller = controller;
  ev.flags = 0;
  ev.param = (u16)mag;
  ev.zone = NULL;
  EffectEvent_Emit(&ev);
}

void EffectEvent_EmitCardActivate(u16 cardId, struct DuelCard *zone, u8 activateFlags)
{
  struct EffectEvent ev;
  u8 fixedRow;
  u8 col;

  gEffectActivationNegated = FALSE;

  ev.type = EFFECT_EVENT_ON_CARD_ACTIVATE;
  ev.cardId = cardId;
  ev.fixedRow = 0xFF;
  ev.col = 0xFF;
  ev.controller = WhoseTurn();
  ev.flags = activateFlags;
  ev.param = 0;
  ev.zone = zone;

  if (zone != NULL && Duel_FindFixedZone(zone, &fixedRow, &col)) {
    ev.fixedRow = fixedRow;
    ev.col = col;
    if (Duel_IsFixedMonsterRow(fixedRow))
      ev.controller = Duel_FixedDuelistForMonsterRow(fixedRow);
    else
      ev.controller = GetDuelistForZone(zone);
  }

  EffectEvent_Emit(&ev);
}

void EffectEvent_RequestActivationNegate(void)
{
  gEffectActivationNegated = TRUE;
}

u8 EffectEvent_ConsumeActivationNegate(void)
{
  u8 negated = gEffectActivationNegated;

  gEffectActivationNegated = FALSE;
  return negated;
}

void EffectOpt_ClearAll(void)
{
  gEffectOptUsedCount = 0;
}

u8 EffectOpt_IsUsed(u16 cardId)
{
  u8 i;

  if (cardId == CARD_NONE)
    return FALSE;

  for (i = 0; i < gEffectOptUsedCount; i++) {
    if (gEffectOptUsedIds[i] == cardId)
      return TRUE;
  }

  return FALSE;
}

void EffectOpt_MarkUsed(u16 cardId)
{
  if (cardId == CARD_NONE || EffectOpt_IsUsed(cardId))
    return;

  if (gEffectOptUsedCount >= EFFECT_OPT_MAX_CARDS)
    return;

  gEffectOptUsedIds[gEffectOptUsedCount] = cardId;
  gEffectOptUsedCount++;
}

void EffectEvent_OnTurnBoundary(void)
{
  struct EffectEvent ev;

  EffectOpt_ClearAll();
  AncientGearAdvance_OnTurnBoundary();
  AncientGearDrill_OnTurnBoundary();
  AncientGearFactory_OnTurnBoundary();
  BerserkerSoul_OnTurnBoundary();
  ChainSummoning_ResetTurnState();
  ColdWave_OnTurnBoundary();
  ContactGate_OnTurnBoundary();
  DarkContact_ClearOnTurnBoundary();
  DarkFusion_ClearOnTurnBoundary();
  EN_ENGAGE_NEO_SPACE_ClearOnTurnBoundary();
  EvilAssault_OnTurnBoundary();
  ForbiddenChalice_ClearOnTurnBoundary();
  ForbiddenDress_ClearOnTurnBoundary();
  ForbiddenLance_ClearOnTurnBoundary();
  SecondCoinToss_ClearOnTurnBoundary();
  SpellGear_OnTurnBoundary();
  SupremeKingsCastle_ClearOnTurnBoundary();
  TriangleEcstasySpark_ClearOnTurnBoundary();
  ParallelWorldFusion_ClearOnTurnBoundary();
  FusionDeployment_ClearOnTurnBoundary();
  FusionDestiny_ClearDarkHeroSpecialSummonLock();
  GenerationNext_ClearOnTurnBoundary();
  LevelTuning_ClearAtTurnBoundary();
  LightForce_ClearTurnState();
  ElShaddollWinda_ClearTurnState();
  AmazonessScouts_ClearTurnState();
  AncientGearCannon_ClearTurnState();
  ElShaddollWendigo_ClearTurnMarks();
  CharmOfShabti_ClearOnTurnBoundary();
  DestinedRivals_ClearExhaustedOnTurnBoundary();
  Meteorain_ClearOnTurnBoundary();
  HarpiesFeatherStorm_ClearAtTurnBoundary();
  Alector_ClearNegateMarksAtTurnBoundary();
  CrimsonBlader_ClearOnTurnBoundary();
  HarpieLadyElegance_ClearOnTurnBoundary();

  ev.type = EFFECT_EVENT_ON_TURN_STANDBY;
  ev.cardId = CARD_NONE;
  ev.fixedRow = 0xFF;
  ev.col = 0xFF;
  ev.controller = WhoseTurn();
  ev.flags = 0;
  ev.param = 0;
  ev.zone = NULL;
  EffectEvent_Emit(&ev);
}
