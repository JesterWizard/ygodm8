#include "global.h"
#include "configs/runtime.h"
#include "duel.h"
#include "duel_helpers.h"
#include "removed_from_play.h"

extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

static u8 CountFromArray(u8 fixedDuelist)
{
  u8 i;

  for (i = 0; i < REMOVED_FROM_PLAY_CAPACITY; i++) {
    if (gRemovedFromPlay[fixedDuelist][i] == CARD_NONE)
      return i;
  }
  return REMOVED_FROM_PLAY_CAPACITY;
}

u8 RemovedFromPlay_IsEnabled(void)
{
  return gRuntimeConfig.enable_removed_from_play_zone == TRUE;
}

void RemovedFromPlay_Init(void)
{
  u8 duelist;
  u8 i;

  for (duelist = 0; duelist < 2; duelist++) {
    for (i = 0; i < REMOVED_FROM_PLAY_CAPACITY; i++)
      gRemovedFromPlay[duelist][i] = CARD_NONE;
  }
}

void RemovedFromPlay_PushFixed(u8 fixedDuelist, u16 cardId)
{
  u8 count;
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return;
  if (fixedDuelist > DUEL_OPPONENT || cardId == CARD_NONE)
    return;

  count = CountFromArray(fixedDuelist);
  if (count >= REMOVED_FROM_PLAY_CAPACITY) {
    /* ponytail: 40-card cap matches deck size; on overflow, drop oldest. */
    for (i = 1; i < REMOVED_FROM_PLAY_CAPACITY; i++)
      gRemovedFromPlay[fixedDuelist][i - 1] = gRemovedFromPlay[fixedDuelist][i];
    count = REMOVED_FROM_PLAY_CAPACITY - 1;
  }

  gRemovedFromPlay[fixedDuelist][count] = cardId;
}

static u8 FixedDuelistForZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 turnDuelist;
  u8 handCol;

  if (zone == NULL)
    return 0xFF;

  if (Duel_FindFixedZone(zone, &fixedRow, &col))
    return fixedRow <= OPPONENT_MONSTER_ROW ? DUEL_OPPONENT : DUEL_PLAYER;

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    for (handCol = 0; handCol < MAX_ZONES_IN_ROW; handCol++) {
      if (gTurnHands[turnDuelist][handCol] != zone)
        continue;
      if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
        return DUEL_OPPONENT;
      return DUEL_PLAYER;
    }
  }

  return 0xFF;
}

void RemovedFromPlay_PushZone(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u16 cardId;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  fixedDuelist = FixedDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  cardId = zone->id;
  RemovedFromPlay_PushFixed(fixedDuelist, cardId);
}

u8 RemovedFromPlay_GetCount(u8 fixedDuelist)
{
  if (fixedDuelist > DUEL_OPPONENT || !RemovedFromPlay_IsEnabled())
    return 0;
  return CountFromArray(fixedDuelist);
}

u16 RemovedFromPlay_GetCardAt(u8 fixedDuelist, u8 index)
{
  if (fixedDuelist > DUEL_OPPONENT || index >= RemovedFromPlay_GetCount(fixedDuelist))
    return CARD_NONE;
  return gRemovedFromPlay[fixedDuelist][index];
}

u8 RemovedFromPlay_RemoveAt(u8 fixedDuelist, u8 index)
{
  u8 count;
  u8 i;

  if (fixedDuelist > DUEL_OPPONENT || !RemovedFromPlay_IsEnabled())
    return FALSE;

  count = CountFromArray(fixedDuelist);
  if (index >= count)
    return FALSE;

  for (i = index + 1; i < count; i++)
    gRemovedFromPlay[fixedDuelist][i - 1] = gRemovedFromPlay[fixedDuelist][i];

  gRemovedFromPlay[fixedDuelist][count - 1] = CARD_NONE;
  return TRUE;
}

u8 RemovedFromPlay_RemoveMatching(u8 fixedDuelist, u16 cardId)
{
  u8 count;
  u8 i;

  if (fixedDuelist > DUEL_OPPONENT || cardId == CARD_NONE || !RemovedFromPlay_IsEnabled())
    return FALSE;

  count = CountFromArray(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (gRemovedFromPlay[fixedDuelist][i] != cardId)
      continue;
    return RemovedFromPlay_RemoveAt(fixedDuelist, i);
  }

  return FALSE;
}
