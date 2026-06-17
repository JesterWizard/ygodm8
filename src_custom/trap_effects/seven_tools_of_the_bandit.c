#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "seven_tools_of_the_bandit.h"

static struct DuelCard *GetTrapOriginZone(void)
{
  u8 row = gTrapEffectData.originRow;
  u8 col = gTrapEffectData.originCol;

  if (col >= MAX_ZONES_IN_ROW)
    return NULL;

  if (row <= PLAYER_HAND)
    return gFixedZones[row][col];

  if (row < 5)
    return gTurnZones[row][col];

  return NULL;
}

APPEND_TEXT void EffectSevenToolsOfTheBandit(void)
{
  struct DuelCard *originZone = GetTrapOriginZone();

  Duel_ShowTrapResponseText(SEVEN_TOOLS_OF_THE_BANDIT, gTrapEffectData.originCardId);

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);

  if (originZone != NULL)
    Duel_DestroyZone(originZone, ACTIVE_DUELIST, TRUE);
}
