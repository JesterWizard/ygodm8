#ifndef GUARD_ANCIENT_GEAR_FACTORY_H
#define GUARD_ANCIENT_GEAR_FACTORY_H

#include "gba/types.h"

u8 AncientGearFactory_CanNormalSummonWithoutTribute(u16 cardId);
u8 AncientGearFactory_TryConsumeOnNormalSummon(u16 cardId);
void AncientGearFactory_OnTurnBoundary(void);

#endif /* GUARD_ANCIENT_GEAR_FACTORY_H */
