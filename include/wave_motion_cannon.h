#ifndef GUARD_WAVE_MOTION_CANNON_H
#define GUARD_WAVE_MOTION_CANNON_H

#include "global.h"

u8 IsChargedWaveMotionCannon(const struct DuelCard *zone);
void RefreshAllWaveMotionCannonFieldCounters(void);
void AgeWaveMotionCannonTurns(void);

#endif // GUARD_WAVE_MOTION_CANNON_H
