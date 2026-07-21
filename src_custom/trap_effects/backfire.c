#include "global.h"
#include "common-chax.h"
#include "backfire.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect.h"

#define BACKFIRE_BURN 500

static u8 IsFireMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_FIRE;
}

static void ActivateBACKFIREZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, BACKFIRE) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateBACKFIREOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(BACKFIRE, ActivateBACKFIREZone);
}

u8 Cond_BackfireOnDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;

  if (!IsFireMonster(ev->cardId))
    return FALSE;

  return Duel_FindBackrowCard(ev->controller, BACKFIRE, TRUE) != NULL;
}

enum DuelActionResult Op_BackfireOnDestroy(struct EffectCtx *ctx)
{
  u8 oppTurn;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  oppTurn = (gTurnDuelistBattleState[ACTIVE_DUELIST]
                 == &gDuel.duelistbattleState[ctx->event->controller])
                ? INACTIVE_DUELIST
                : ACTIVE_DUELIST;

  Duel_ShowEffectText(BACKFIRE);
  return Duel_ChangeLp(oppTurn, -BACKFIRE_BURN, TRUE);
}
