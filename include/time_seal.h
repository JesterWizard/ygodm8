#ifndef GUARD_TIME_SEAL_H
#define GUARD_TIME_SEAL_H

#include "gba/types.h"

#define TIME_SEAL_SKIP_DRAW_NONE 0xFF

extern u8 gTimeSealSkipDrawDuelist;

void ResetTimeSealSkipDraw(void);
u8 ShouldSkipDrawPhaseForTimeSeal(u8 turn);
void ConsumeTimeSealSkipDraw(u8 turn);
void TryActivateTimeSealOnOpponentTurnStart(void);

#endif
