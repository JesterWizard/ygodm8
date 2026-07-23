#ifndef GUARD_HARPIES_FEATHER_STORM_H
#define GUARD_HARPIES_FEATHER_STORM_H

#include "global.h"

u8 HarpiesFeatherStorm_BlocksMonsterEffects(u8 fixedDuelist);
void HarpiesFeatherStorm_ClearAtTurnBoundary(void);
void HarpiesFeatherStorm_EnsureInit(void);
u8 CanActivateHarpiesFeatherStormFromHand(u8 handZone);
u8 TryActivateHarpiesFeatherStormFromHand(u8 handZone);

#endif /* GUARD_HARPIES_FEATHER_STORM_H */
