#ifndef GUARD_COPYCAT_H
#define GUARD_COPYCAT_H

#include "global.h"

typedef struct {
  u16 atk;
  u16 def;
  u8 active;
} CopycatBoardStat;

#define COPYCAT_BOARD_CELL_COUNT (4 * MAX_ZONES_IN_ROW)

extern CopycatBoardStat gCopycatBoardStats[COPYCAT_BOARD_CELL_COUNT];
extern u8 gComputingCopycatStats;

u8 GetCopycatBoardPosition(struct DuelCard *zone, u8 *row, u8 *col);
void ClearCopycatBoardStatsForZone(struct DuelCard *zone);
void StoreCopycatBoardStats(struct DuelCard *zone, u16 atk, u16 def);
void ApplyCopycatStatsToCardInfo(struct StatMod *ptr);
s8 FindStrongestEnemyMonsterZone(struct DuelCard **row);
void ActivateCopycatEffect(void);

#endif // GUARD_COPYCAT_H
