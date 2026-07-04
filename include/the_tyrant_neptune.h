#ifndef GUARD_THE_TYRANT_NEPTUNE_H
#define GUARD_THE_TYRANT_NEPTUNE_H

#include "global.h"

#define THE_TYRANT_NEPTUNE_MONSTER_CELL_COUNT (2 * MAX_ZONES_IN_ROW)
#define THE_TYRANT_NEPTUNE_MAX_TRIBUTES 3

extern u16 gTheTyrantNeptuneTributeTotals[2];
extern u8 gTheTyrantNeptunePendingSummon;
extern u16 gTheTyrantNeptuneBoardAtk[THE_TYRANT_NEPTUNE_MONSTER_CELL_COUNT];
extern u16 gTheTyrantNeptuneBoardDef[THE_TYRANT_NEPTUNE_MONSTER_CELL_COUNT];
extern u8 gTheTyrantNeptuneBoardActive[THE_TYRANT_NEPTUNE_MONSTER_CELL_COUNT];
extern u16 gTheTyrantNeptuneCopiedCardId[THE_TYRANT_NEPTUNE_MONSTER_CELL_COUNT];
extern u16 gTheTyrantNeptuneTributeIds[THE_TYRANT_NEPTUNE_MAX_TRIBUTES];
extern u8 gTheTyrantNeptuneTributeCount;

void SetTheTyrantNeptunePendingSummon(u8 pending);
void TryCaptureTheTyrantNeptuneTributeFromZone(struct DuelCard *zone);
void ClearTheTyrantNeptuneBoardStatsForZone(struct DuelCard *zone);
u8 TheTyrantNeptuneZoneHasCustomStats(struct DuelCard *zone);
u16 TheTyrantNeptune_GetCopiedCardId(struct DuelCard *zone);
u8 TheTyrantNeptune_HasCopiedEffect(struct DuelCard *zone);
/* THE_TYRANT_NEPTUNE when zone is Neptune, including identity-swapped copies. */
u16 TheTyrantNeptune_HostCardId(struct DuelCard *zone);
u8 TheTyrantNeptune_ApplyDynamicZoneStats(struct DuelCard *zone);
u16 TheTyrantNeptune_BeginEffectIdentity(struct DuelCard *zone);
void TheTyrantNeptune_EndEffectIdentity(struct DuelCard *zone, u16 savedId);
void FinishTheTyrantNeptuneTributeSummon(struct DuelCard *zone, u8 fixedRow, u8 fixedCol);
unsigned char ShouldActivateTheTyrantNeptune(void);
void ActivateTheTyrantNeptune(void);
void TryCaptureTheTyrantNeptuneAiTribute(void);

#endif // GUARD_THE_TYRANT_NEPTUNE_H
