#ifndef GUARD_COST_DOWN_H
#define GUARD_COST_DOWN_H

#include "global.h"

#define COST_DOWN_LEVEL_REDUCTION 2

extern u8 gCostDownActive;
extern u8 gCostDownTargetDuelist;

void EnableCostDownForTurn(void);
void ClearCostDown(void);
u8 GetCostDownAdjustedLevel(u16 cardId, u8 baseLevel);
u8 ShouldApplyCostDownLevelForTribute(u16 cardId);
u8 ShouldApplyCostDownForHandSlot(u8 handSlot, u16 cardId);
int GetNumRequiredTributesWithCostDown(u16 cardId);
int GetNumRequiredTributesForHandSlot(u8 handSlot, u16 cardId);
void EffectCostDown(void);

#endif
