#ifndef GUARD_URIA_LORD_OF_SEARING_FLAMES_H
#define GUARD_URIA_LORD_OF_SEARING_FLAMES_H

#include "global.h"

#define URIA_ATK_PER_CONTINUOUS_TRAP 1000
#define URIA_COST_TRAPS 3

u8 CanSpecialSummonUriaLordOfSearingFlamesFromHand(u8 handZone);
u8 TrySpecialSummonUriaLordOfSearingFlamesFromHand(u8 handZone);
u8 UriaLordOfSearingFlames_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 CanActivateURIA_LORD_OF_SEARING_FLAMES(void);
void ActivateURIA_LORD_OF_SEARING_FLAMESEffect(void);

#endif
