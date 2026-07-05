#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "seraphim_blaster.h"

extern void UpdateDuelGfxExceptField(void);

#define SERAPHIM_BLASTER_BASE_ATK 1800
#define SERAPHIM_BLASTER_ATK_PER_OTHER_FAIRY 300

static u8 CountOtherFairiesOnField(const struct DuelCard *selfZone)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];
      u16 cardId;

      if (zone == selfZone || zone == NULL || zone->id == CARD_NONE)
        continue;

      cardId = zone->id;
      if (cardId >= NUM_TOTAL_CARDS)
        continue;

      if (gCardData_NEW[cardId].type != TYPE_FAIRY)
        continue;

      count++;
    }
  }

  return count;
}

static u8 RowHasSeraphimBlaster(u8 fixedMonsterRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[fixedMonsterRow][col]->id == SERAPHIM_BLASTER)
      return TRUE;
  }

  return FALSE;
}

u8 SeraphimBlaster_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 otherFairies;
  u32 atk;

  if (zone == NULL || zone->id != SERAPHIM_BLASTER)
    return FALSE;

  otherFairies = CountOtherFairiesOnField(zone);
  atk = (u32)SERAPHIM_BLASTER_BASE_ATK
      + (u32)otherFairies * SERAPHIM_BLASTER_ATK_PER_OTHER_FAIRY;

  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, Duel_ClampStat(atk), gCardInfo.def);
  return TRUE;
}

void SeraphimBlaster_OnZoneCleared(const struct DuelCard *zone)
{
  u8 row;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (zone->id == SERAPHIM_BLASTER) {
    UpdateDuelGfxExceptField();
    return;
  }

  if (zone->id >= NUM_TOTAL_CARDS || gCardData_NEW[zone->id].type != TYPE_FAIRY)
    return;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    if (RowHasSeraphimBlaster(row)) {
      UpdateDuelGfxExceptField();
      return;
    }
  }
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SeraphimBlaster_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = SERAPHIM_BLASTER;
  SeraphimBlaster_ApplyDynamicZoneStats(&zone);
}
#endif
