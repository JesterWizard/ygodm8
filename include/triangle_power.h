#ifndef GUARD_TRIANGLE_POWER_H
#define GUARD_TRIANGLE_POWER_H

#include "gba/types.h"

extern u8 gTrianglePowerDestroyMaskPlayer;
extern u8 gTrianglePowerDestroyMaskOpponent;

void EffectTrianglePower(void);
void DestroyTrianglePowerMonstersAtEndOfTurn(void);
void ResetTrianglePowerState(void);

#endif
