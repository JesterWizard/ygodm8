#ifndef GUARD_GUARDIAN_TREASURE_H
#define GUARD_GUARDIAN_TREASURE_H

#include "global.h"

u8 IsGuardianTreasureActiveOnField(void);
u8 CanActivateGuardianTreasure(void);
void PerformGuardianTreasureDrawPhaseDraws(u8 turn);

#endif // GUARD_GUARDIAN_TREASURE_H
