#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateLIGHT_SPIRALZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, LIGHT_SPIRAL) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: Lightsworn mill → banish opp top Deck needs mill hook.
   * Ceiling: face-up continuous only. */
}

void TryActivateLIGHT_SPIRALOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(LIGHT_SPIRAL, ActivateLIGHT_SPIRALZone);
}
