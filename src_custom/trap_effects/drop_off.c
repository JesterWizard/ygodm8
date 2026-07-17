#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "drop_off.h"
#include "duel_helpers.h"
#include "royal_decree.h"
#include "six_card_hand.h"

void BeginDrawPhaseNormalDraws(void)
{
  gDrawPhaseNormalDrawActive = TRUE;
}

void EndDrawPhaseNormalDraws(void)
{
  gDrawPhaseNormalDrawActive = FALSE;
}

static struct DuelCard *FindFaceDownDropOff(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id == DROP_OFF && zone->isFaceUp == FALSE)
      return zone;
  }

  return NULL;
}

void TryApplyDropOffOnDrawPhaseDraw(u8 duelist, u8 handSlot)
{
  struct DuelCard *trapZone;
  struct DuelCard *drawnCard;

  if (duelist != WhoseTurn())
    return;

  if (IsRoyalDecreeActiveOnField())
    return;

  trapZone = FindFaceDownDropOff();
  if (trapZone == NULL)
    return;

  drawnCard = SixCardHand_GetFixed(duelist, handSlot);
  if (drawnCard == NULL || drawnCard->id == CARD_NONE)
    return;

  Duel_ActivateContinuousZone(trapZone);

  if (Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(DROP_OFF, 3);

  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(drawnCard, duelist, FALSE);
}
