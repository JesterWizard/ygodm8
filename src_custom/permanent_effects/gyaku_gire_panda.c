#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define GYAKU_GIRE_PANDA_BASE_ATK 800
#define GYAKU_GIRE_PANDA_ATK_PER_OPPONENT_MONSTER 500

static u16 GyakuGirePandaCurrentAtk(struct DuelCard *zone)
{
  u8 count = Duel_CountMonstersOnFixedRow(Duel_OpponentMonsterRowForZone(zone));

  return Duel_StatFromCount(count, GYAKU_GIRE_PANDA_ATK_PER_OPPONENT_MONSTER,
                            GYAKU_GIRE_PANDA_BASE_ATK);
}

u8 GyakuGirePanda_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  SetCardInfo(zone->id);
  gCardInfo.atk = GyakuGirePandaCurrentAtk(zone);
  return TRUE;
}

#if !defined(__GNUC__)
#error Gyaku Gire Panda stat hook self-check requires GCC
#elif __GNUC__
void GyakuGirePanda_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = GYAKU_GIRE_PANDA;
  GyakuGirePanda_ApplyDynamicZoneStats(&zone);
}
#endif
