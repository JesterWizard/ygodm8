#ifndef GUARD_COLD_WAVE_H
#define GUARD_COLD_WAVE_H

#include "gba/types.h"

u8 CanActivateCOLD_WAVE(void);
u8 ColdWave_CanActivateAtMainPhase1Start(u8 isMainPhase1Start, u8 priorMainPhaseActionThisTurn);
void ColdWave_ArmSpellTrapLock(void);
u8 ColdWave_IsSpellTrapPlayOrSetLocked(void);
void ColdWave_ClearLockAtControllerStandby(u8 controllerFixedDuelist);
void ColdWave_OnTurnBoundary(void);

#endif /* GUARD_COLD_WAVE_H */
