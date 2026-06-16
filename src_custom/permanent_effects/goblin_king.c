#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "goblin_king.h"

extern struct DuelCard *gSetFinalStatZone;

static u8 IsFiendMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_FIEND;
}

static u8 CountFiendMonstersOnField(void)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id == CARD_NONE)
        continue;
      if (!IsFiendMonster(zone->id))
        continue;
      count++;
    }
  }

  return count;
}

static u8 ControllerHasOtherFiendMonster(u8 turnRow, u8 exceptCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (col == exceptCol)
      continue;
    if (gTurnZones[turnRow][col]->id == CARD_NONE)
      continue;
    if (IsFiendMonster(gTurnZones[turnRow][col]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 GetTurnRowColForZone(struct DuelCard *zone, u8 *turnRow, u8 *col)
{
  u8 row;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gTurnZones[row][*col] == zone) {
        *turnRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static u16 GoblinKingCurrentStat(struct DuelCard *zone)
{
  u8 count = CountFiendMonstersOnField();
  u32 stat = (u32)count * 500;

  (void)zone;

  if (stat > 0xFFFE)
    return 0xFFFE;
  return (u16)stat;
}

u8 ApplyGoblinKingZoneStatsToCardInfo(struct DuelCard *zone)
{
  u16 stat;

  if (zone == NULL || zone->id != GOBLIN_KING)
    return FALSE;

  stat = GoblinKingCurrentStat(zone);
  SetCardInfo(GOBLIN_KING);
  gCardInfo.atk = stat;
  gCardInfo.def = stat;
  return TRUE;
}

u8 ApplyGoblinKingStatsToCardInfo(struct StatMod *ptr)
{
  u8 row;
  u8 col;

  if (ptr == NULL || ptr->card != GOBLIN_KING)
    return FALSE;

  if (gSetFinalStatZone != NULL && gSetFinalStatZone->id == GOBLIN_KING)
    return ApplyGoblinKingZoneStatsToCardInfo(gSetFinalStatZone);

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id != GOBLIN_KING)
        continue;
      if (GetFinalStage(zone) != ptr->stage)
        continue;
      if (ApplyGoblinKingZoneStatsToCardInfo(zone))
        return TRUE;
    }
  }

  return FALSE;
}

u8 GoblinKing_CanBeAttacked(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;

  if (zone == NULL || zone->id != GOBLIN_KING)
    return TRUE;

  if (!GetTurnRowColForZone(zone, &turnRow, &col))
    return TRUE;

  return !ControllerHasOtherFiendMonster(turnRow, col);
}

#if !defined(__GNUC__)
#error Goblin King stat hook self-check requires GCC
#elif __GNUC__
void GoblinKing_SelfCheck(void)
{
  struct DuelCard zone;
  struct StatMod statMod;

  zone.id = GOBLIN_KING;
  ApplyGoblinKingZoneStatsToCardInfo(&zone);

  statMod.card = GOBLIN_KING;
  statMod.field = 0;
  statMod.stage = 0;
  ApplyGoblinKingStatsToCardInfo(&statMod);
}
#endif
