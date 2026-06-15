#ifndef GUARD_BURNING_LAND_H
#define GUARD_BURNING_LAND_H

#include "global.h"

u8 IsActivatedBurningLandZone(const struct DuelCard *zone);
u8 IsBurningLandActiveOnField(void);
void TryApplyBurningLandStandbyDamage(void);
void EffectBurningLand(void);

#endif // GUARD_BURNING_LAND_H
