#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "jar_of_greed.h"

static void ActivateJarOfGreedZone(struct DuelCard *zone)
{
  Duel_ActivateContinuousZone(zone);

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(JAR_OF_GREED, 3);
  Duel_DrawCards(INACTIVE_DUELIST, 1, TRUE);
}

void TryActivateJarOfGreedOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != JAR_OF_GREED || zone->isFaceUp != FALSE)
      continue;

    ActivateJarOfGreedZone(zone);
    if (IsDuelOver() == TRUE)
      return;
  }
}
