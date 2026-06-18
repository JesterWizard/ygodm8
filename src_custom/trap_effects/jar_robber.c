#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "jar_robber.h"

static u8 FindSetJarRobberCol(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];

    if (zone->id == JAR_ROBBER && zone->isFaceUp == FALSE)
      return i;
  }

  return 0xFF;
}

u8 TryJarRobberPotOfGreedCounter(void)
{
  u8 col;
  struct DuelCard *trapZone;
  struct DuelCard *potZone;

  if (gSpellEffectData.id != POT_OF_GREED)
    return FALSE;

  if (Duel_IsCardActivationBlocked(JAR_ROBBER))
    return FALSE;

  col = FindSetJarRobberCol();
  if (col == 0xFF)
    return FALSE;

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][col];
  potZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);

  if (potZone != NULL && potZone->id == POT_OF_GREED)
    Duel_DestroyZone(potZone, ACTIVE_DUELIST, FALSE);

  Duel_ShowTrapResponseText(JAR_ROBBER, POT_OF_GREED);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DrawCards(INACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  return TRUE;
}
