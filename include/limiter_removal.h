#ifndef GUARD_LIMITER_REMOVAL_H
#define GUARD_LIMITER_REMOVAL_H

#include "gba/types.h"

extern u8 gLimiterRemovalDestroyMask;
extern u8 gLimiterRemovalFixedMonsterRow;

void EffectLimiterRemoval(void);
void DestroyLimiterRemovalMonstersAtEndOfTurn(void);
void ResetLimiterRemovalState(void);

#endif
