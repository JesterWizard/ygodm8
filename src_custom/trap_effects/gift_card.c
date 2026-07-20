#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateGIFT_CARDZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, GIFT_CARD) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ChangeLp(ACTIVE_DUELIST, 3000, TRUE);
  Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE);
}

void TryActivateGIFT_CARDOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(GIFT_CARD, ActivateGIFT_CARDZone);
}

/* ponytail: TryActivateGIFT_CARDOnOpponentTurnStart must be called from
 * turn_effect_hooks (opp turn start). Ceiling: body ready, not wired; upgrade:
 * add call next to Jar of Greed turn-start activations. */
