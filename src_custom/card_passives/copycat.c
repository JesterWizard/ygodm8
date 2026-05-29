#include "global.h"
#include "copycat.h"

extern CopycatBoardStat gCopycatBoardStats[COPYCAT_BOARD_CELL_COUNT];

u8 GetCopycatBoardPosition(struct DuelCard *zone, u8 *row, u8 *col) {
  u8 r;
  u8 c;

  for (r = 0; r < 4; r++) {
    for (c = 0; c < MAX_ZONES_IN_ROW; c++) {
      if (&gDuel.board[r][c] == zone) {
        *row = r;
        *col = c;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static CopycatBoardStat *GetCopycatBoardStatEntry(u8 row, u8 col) {
  return &gCopycatBoardStats[row * MAX_ZONES_IN_ROW + col];
}

void ClearCopycatBoardStatsForZone(struct DuelCard *zone) {
  u8 row;
  u8 col;
  CopycatBoardStat *entry;

  if (GetCopycatBoardPosition(zone, &row, &col) == FALSE)
    return;

  entry = GetCopycatBoardStatEntry(row, col);
  entry->atk = 0;
  entry->def = 0;
  entry->active = FALSE;
}

void StoreCopycatBoardStats(struct DuelCard *zone, u16 atk, u16 def) {
  u8 row;
  u8 col;
  CopycatBoardStat *entry;

  if (GetCopycatBoardPosition(zone, &row, &col) == FALSE)
    return;

  entry = GetCopycatBoardStatEntry(row, col);
  entry->atk = atk;
  entry->def = def;
  entry->active = TRUE;
}

static u8 GetCopycatOwnerMonsterRow(const struct StatMod *ptr) {
  u8 row;
  u8 col;
  u8 matchCount = 0;
  u8 ownerRow = OPPONENT_MONSTER_ROW;
  u8 ownerRowMask = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *card = gFixedZones[row][col];

      if (card->id != COPYCAT)
        continue;

      ownerRowMask |= (1 << (row - OPPONENT_MONSTER_ROW));
      ownerRow = row;

      if (ptr != NULL && GetFinalStage(card) == ptr->stage)
        matchCount++;
    }
  }

  if (matchCount == 1) {
    for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
      for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
        if (gFixedZones[row][col]->id == COPYCAT && GetFinalStage(gFixedZones[row][col]) == ptr->stage)
          return row;
      }
    }
  }

  if (ownerRowMask == 1)
    return ownerRow;
  if (ownerRowMask == 2)
    return PLAYER_MONSTER_ROW;

  return OPPONENT_MONSTER_ROW;
}

static CopycatBoardStat *FindActivatedCopycatBoardStat(const struct StatMod *ptr) {
  u8 row;
  u8 col;
  u8 ownerRow;
  CopycatBoardStat *entry;

  ownerRow = GetCopycatOwnerMonsterRow(ptr);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[ownerRow][col]->id != COPYCAT)
      continue;

    if (ptr != NULL && GetFinalStage(gFixedZones[ownerRow][col]) != ptr->stage)
      continue;

    if (GetCopycatBoardPosition(gFixedZones[ownerRow][col], &row, &col) == FALSE)
      continue;

    entry = GetCopycatBoardStatEntry(row, col);
    if (entry->active == TRUE)
      return entry;
  }

  return NULL;
}

s8 FindStrongestEnemyMonsterZone(struct DuelCard **row) {
  s8 bestZone = -1;
  int bestAtk = -1;
  u8 i;

  gComputingCopycatStats = TRUE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *card = row[i];
    struct StatMod targetStatMod;
    int atk;

    if (card->id == CARD_NONE || card->id == COPYCAT)
      continue;
    if (IsGodCard(card->id) == TRUE)
      continue;

    targetStatMod.card = card->id;
    targetStatMod.field = gDuel.field;
    targetStatMod.stage = GetFinalStage(card);
    SetFinalStat(&targetStatMod);
    atk = gCardInfo.atk;

    if (atk > bestAtk) {
      bestAtk = atk;
      bestZone = i;
    }
  }

  gComputingCopycatStats = FALSE;
  return bestZone;
}

void ApplyCopycatStatsToCardInfo(struct StatMod *ptr) {
  CopycatBoardStat *entry;

  if (gComputingCopycatStats == TRUE)
    return;

  entry = FindActivatedCopycatBoardStat(ptr);
  if (entry == NULL)
    return;

  SetCardInfo(COPYCAT);
  gCardInfo.atk = entry->atk;
  gCardInfo.def = entry->def;
}
