#ifndef GUARD_DROP_OFF_H
#define GUARD_DROP_OFF_H

#include "gba/types.h"

extern u8 gDrawPhaseNormalDrawActive;

void BeginDrawPhaseNormalDraws(void);
void EndDrawPhaseNormalDraws(void);
void TryApplyDropOffOnDrawPhaseDraw(u8 duelist, u8 handSlot);

#endif // GUARD_DROP_OFF_H
