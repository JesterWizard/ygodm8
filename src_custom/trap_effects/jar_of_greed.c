#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "jar_of_greed.h"

void ActivateJarOfGreedFromZone(struct DuelCard *zone, u8 drawTurnDuelist)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, JAR_OF_GREED) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DrawCards(drawTurnDuelist, 1, TRUE);
}

static void ActivateJarOfGreedZone(struct DuelCard *zone)
{
  ActivateJarOfGreedFromZone(zone, INACTIVE_DUELIST);
}

void TryActivateJarOfGreedOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(JAR_OF_GREED, ActivateJarOfGreedZone);
}
