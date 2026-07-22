#ifndef GUARD_OSHALEON_H
#define GUARD_OSHALEON_H

#include "global.h"

struct DuelCard *Oshaleon_GetForcedAttackTarget(u8 defenderDuelist);
u8 Oshaleon_CanAttackMonsterZone(struct DuelCard *zone);

#endif /* GUARD_OSHALEON_H */
