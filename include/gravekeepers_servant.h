#ifndef GUARD_GRAVEKEEPERS_SERVANT_H
#define GUARD_GRAVEKEEPERS_SERVANT_H

#include "gba/types.h"

struct DuelCard;

u8 IsActivatedGravekeepersServantZone(const struct DuelCard *zone);
u8 IsGravekeepersServantActiveAgainstAttacker(void);
u8 TryPayGravekeepersServantAttackCost(void);
void EffectGravekeepersServant(void);

#endif // GUARD_GRAVEKEEPERS_SERVANT_H
