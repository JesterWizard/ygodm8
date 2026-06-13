#ifndef GUARD_GREAT_MAJU_GARZETT_H
#define GUARD_GREAT_MAJU_GARZETT_H

#include "global.h"

#define GREAT_MAJU_GARZETT_MONSTER_CELL_COUNT (2 * MAX_ZONES_IN_ROW)

extern u16 gGreatMajuGarzettTributeTotals[2];
extern u8 gGreatMajuGarzettPendingSummon;
extern u16 gGreatMajuGarzettBoardAtk[GREAT_MAJU_GARZETT_MONSTER_CELL_COUNT];
extern u16 gGreatMajuGarzettBoardDef[GREAT_MAJU_GARZETT_MONSTER_CELL_COUNT];
extern u8 gGreatMajuGarzettBoardActive[GREAT_MAJU_GARZETT_MONSTER_CELL_COUNT];

void SetGreatMajuGarzettPendingSummon(u8 pending);
void TryCaptureGreatMajuGarzettTributeFromZone(struct DuelCard *zone);
void ClearGreatMajuGarzettBoardStatsForZone(struct DuelCard *zone);
void StoreGreatMajuGarzettBoardStats(struct DuelCard *zone, u16 atk, u16 def);
u8 GreatMajuGarzettZoneHasCustomStats(struct DuelCard *zone);
u8 ApplyGreatMajuGarzettZoneStatsToCardInfo(struct DuelCard *zone);
u8 ApplyGreatMajuGarzettStatsToCardInfo(struct StatMod *ptr);
void FinishGreatMajuGarzettTributeSummon(struct DuelCard *zone, u8 fixedRow, u8 fixedCol);
unsigned char ShouldActivateGreatMajuGarzett(void);
void ActivateGreatMajuGarzett(void);
void TryCaptureGreatMajuGarzettAiTribute(void);

#endif // GUARD_GREAT_MAJU_GARZETT_H
