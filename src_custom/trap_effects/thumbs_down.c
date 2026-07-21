#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect.h"
#include "thumbs_down.h"

#define THUMBS_DOWN_BURN 500

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 ControlsGladiatorBeast(u8 fixedDuelist)
{
  u8 row = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && Duel_CardNameContains(zone->id, sGladiatorBeastName))
      return TRUE;
  }
  return FALSE;
}

static void ActivateTHUMBS_DOWNZone(struct DuelCard *zone)
{
  u8 controller = GetDuelistForZone(zone);

  if (controller > DUEL_OPPONENT || !ControlsGladiatorBeast(controller))
    return;

  if (Duel_ActivateContinuousTrapPreamble(zone, THUMBS_DOWN) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateTHUMBS_DOWNOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(THUMBS_DOWN, ActivateTHUMBS_DOWNZone);
}

u8 Cond_ThumbsDownOnDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 duelist;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (GetTypeGroup(ev->cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  for (duelist = DUEL_PLAYER; duelist <= DUEL_OPPONENT; duelist++) {
    if (Duel_FindBackrowCard(duelist, THUMBS_DOWN, TRUE) != NULL)
      return TRUE;
  }
  return FALSE;
}

enum DuelActionResult Op_ThumbsDownOnDestroy(struct EffectCtx *ctx)
{
  u8 controllerTurn;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  controllerTurn = (gTurnDuelistBattleState[ACTIVE_DUELIST]
                        == &gDuel.duelistbattleState[ctx->event->controller])
                       ? ACTIVE_DUELIST
                       : INACTIVE_DUELIST;

  Duel_ShowEffectText(THUMBS_DOWN);
  return Duel_ChangeLp(controllerTurn, -THUMBS_DOWN_BURN, TRUE);
}
