#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "gyaku_gire_panda.h"

extern struct DuelCard *gSetFinalStatZone;

#define GYAKU_GIRE_PANDA_BASE_ATK 800
#define GYAKU_GIRE_PANDA_ATK_PER_OPPONENT_MONSTER 500

static u8 CountMonstersOnFixedRow(u8 row)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[row][col]->id != CARD_NONE)
      count++;
  }

  return count;
}

static u8 GetFixedRowColForZone(struct DuelCard *zone, u8 *fixedRow, u8 *col)
{
  u8 row;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gFixedZones[row][*col] == zone) {
        *fixedRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static u8 OpponentMonsterRowForZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (!GetFixedRowColForZone(zone, &fixedRow, &col))
    return OPPONENT_MONSTER_ROW;

  return fixedRow == PLAYER_MONSTER_ROW ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

static u16 GyakuGirePandaCurrentAtk(struct DuelCard *zone)
{
  u8 count = CountMonstersOnFixedRow(OpponentMonsterRowForZone(zone));
  u32 atk = (u32)GYAKU_GIRE_PANDA_BASE_ATK + (u32)count * GYAKU_GIRE_PANDA_ATK_PER_OPPONENT_MONSTER;

  if (atk > 0xFFFE)
    return 0xFFFE;
  return (u16)atk;
}

u8 ApplyGyakuGirePandaZoneStatsToCardInfo(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != GYAKU_GIRE_PANDA)
    return FALSE;

  SetCardInfo(GYAKU_GIRE_PANDA);
  gCardInfo.atk = GyakuGirePandaCurrentAtk(zone);
  return TRUE;
}

u8 ApplyGyakuGirePandaStatsToCardInfo(struct StatMod *ptr)
{
  u8 row;
  u8 col;

  if (ptr == NULL || ptr->card != GYAKU_GIRE_PANDA)
    return FALSE;

  if (gSetFinalStatZone != NULL && gSetFinalStatZone->id == GYAKU_GIRE_PANDA)
    return ApplyGyakuGirePandaZoneStatsToCardInfo(gSetFinalStatZone);

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id != GYAKU_GIRE_PANDA)
        continue;
      if (GetFinalStage(zone) != ptr->stage)
        continue;
      if (ApplyGyakuGirePandaZoneStatsToCardInfo(zone))
        return TRUE;
    }
  }

  return FALSE;
}

#if !defined(__GNUC__)
#error Gyaku Gire Panda stat hook self-check requires GCC
#elif __GNUC__
void GyakuGirePanda_SelfCheck(void)
{
  struct DuelCard zone;
  struct StatMod statMod;

  zone.id = GYAKU_GIRE_PANDA;
  ApplyGyakuGirePandaZoneStatsToCardInfo(&zone);

  statMod.card = GYAKU_GIRE_PANDA;
  statMod.field = 0;
  statMod.stage = 0;
  ApplyGyakuGirePandaStatsToCardInfo(&statMod);
}
#endif
