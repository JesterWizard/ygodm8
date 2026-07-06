#ifndef CYBER_BARRIER_DRAGON_H
#define CYBER_BARRIER_DRAGON_H

#include "global.h"

extern u8 gCyberBarrierDragonUsedMask;

void ClearCyberBarrierDragonTurnState(void);
u8 TryNegateDeclaredAttackWithCyberBarrierDragon(void);

#endif
