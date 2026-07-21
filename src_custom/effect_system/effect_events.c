#include "global.h"
#include "common-chax.h"
#include "ancient_gear_advance.h"
#include "ancient_gear_drill.h"
#include "ancient_gear_factory.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "effect.h"

extern EffectEventHandler gEffectEventHandlers[EFFECT_EVENT_COUNT][EFFECT_EVENT_MAX_SUBSCRIBERS];
extern u8 gEffectEventHandlerCounts[EFFECT_EVENT_COUNT];
extern u16 gEffectOptUsedIds[EFFECT_OPT_MAX_CARDS];
extern u8 gEffectOptUsedCount;

void DestinyHeroFearMonger_EnsureInit(void);
void TheWhiteStoneOfAncients_EnsureInit(void);

static u8 sEffectEventsInited APPEND_DATA = {0};

static void EffectEvent_OnFieldChangeHandler(const struct EffectEvent *ev)
{
  (void)ev;

  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();
  Duel_CheckAmazonessTigerAfterFieldChange();

  /* Rivalry / Ring text flips skip AI-sim (gHideEffectText). */
  if (gHideEffectText)
    return;

  Duel_CheckRivalryOfWarlordsAfterFieldChange();
  Duel_CheckRingOfDestructionAfterFieldChange();
}

void EffectEvent_EnsureInit(void)
{
  if (sEffectEventsInited)
    return;

  sEffectEventsInited = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_FIELD_CHANGE, EffectEvent_OnFieldChangeHandler);
  DestinyHeroFearMonger_EnsureInit();
  TheWhiteStoneOfAncients_EnsureInit();
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

  ev.type = EFFECT_EVENT_ON_TURN_STANDBY;
  ev.cardId = CARD_NONE;
  ev.fixedRow = 0xFF;
  ev.col = 0xFF;
  ev.controller = WhoseTurn();
  ev.flags = 0;
  ev.zone = NULL;
  EffectEvent_Emit(&ev);
}
