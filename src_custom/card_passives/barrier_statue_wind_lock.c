#include "global.h"
#include "barrier_statue_wind_lock.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static u8 StormwindsFaceUpOnField(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->isFaceUp && zone->id == BARRIER_STATUE_OF_THE_STORMWINDS)
        return TRUE;
    }
  }

  return FALSE;
}

u8 BarrierStatueOfTheStormwinds_BlocksSpecialSummon(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!StormwindsFaceUpOnField())
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute != ATTRIBUTE_WIND;
}

#if !defined(__GNUC__)
void BarrierStatueWindLock_SelfCheck(void);
#endif

void BarrierStatueWindLock_SelfCheck(void)
{
  if (!BarrierStatueOfTheStormwinds_BlocksSpecialSummon(BARRIER_STATUE_OF_THE_STORMWINDS))
    return;
  if (BarrierStatueOfTheStormwinds_BlocksSpecialSummon(BLUE_EYES_WHITE_DRAGON))
    return;
}
