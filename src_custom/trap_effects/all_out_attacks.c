#include "global.h"
#include "common-chax.h"
#include "all_out_attacks.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect.h"

static void ActivateALL_OUT_ATTACKSZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, ALL_OUT_ATTACKS) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateALL_OUT_ATTACKSOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(ALL_OUT_ATTACKS, ActivateALL_OUT_ATTACKSZone);
}

u8 Cond_AllOutAttacksOnSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL || ctx->event->zone == NULL)
    return FALSE;

  ev = ctx->event;
  if (GetTypeGroup(ev->cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_FindBackrowCard(DUEL_PLAYER, ALL_OUT_ATTACKS, TRUE) != NULL
      || Duel_FindBackrowCard(DUEL_OPPONENT, ALL_OUT_ATTACKS, TRUE) != NULL;
}

enum DuelActionResult Op_AllOutAttacksOnSummon(struct EffectCtx *ctx)
{
  struct DuelCard *zone;

  if (ctx == NULL || ctx->event == NULL || ctx->event->zone == NULL)
    return DUEL_ACTION_INVALID;

  zone = ctx->event->zone;
  zone->isDefending = FALSE;
  zone->isFaceUp = TRUE;
  Duel_ShowEffectText(ALL_OUT_ATTACKS);
  Duel_NotifyMonsterZoneChanged(zone);
  return DUEL_ACTION_OK;
}
