#ifndef GUARD_MAJU_GARZETT_H
#define GUARD_MAJU_GARZETT_H

#include "global.h"

#define MAJU_GARZETT_MONSTER_CELL_COUNT (2 * MAX_ZONES_IN_ROW)

extern u16 gMajuGarzettTributeAtk;
extern u8 gMajuGarzettPendingSummon;
extern u16 gMajuGarzettBoardAtk[MAJU_GARZETT_MONSTER_CELL_COUNT];
extern u8 gMajuGarzettBoardActive[MAJU_GARZETT_MONSTER_CELL_COUNT];

void SetMajuGarzettPendingSummon(u8 pending);
void TryCaptureMajuGarzettTributeFromZone(struct DuelCard *zone);
void ClearMajuGarzettBoardStatsForZone(struct DuelCard *zone);
u8 MajuGarzettZoneHasCustomStats(struct DuelCard *zone);
void FinishMajuGarzettTributeSummon(struct DuelCard *zone, u8 fixedRow, u8 fixedCol);
unsigned char ShouldActivateMajuGarzett(void);
void ActivateMajuGarzett(void);
void TryCaptureMajuGarzettAiTribute(void);

#endif // GUARD_MAJU_GARZETT_H
