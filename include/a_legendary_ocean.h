#ifndef GUARD_A_LEGENDARY_OCEAN_H
#define GUARD_A_LEGENDARY_OCEAN_H

#include "global.h"

struct DuelCard;

u8 IsLegendaryOceanActive(void);
u8 GetLegendaryOceanAdjustedLevel(u16 cardId, u8 baseLevel);
void ApplyLegendaryOceanFieldStatBoost(u16 cardId, u16 *atk, u16 *def);
void ApplyLegendaryOceanFieldStatBoostForZone(struct DuelCard *zone);

#endif // GUARD_A_LEGENDARY_OCEAN_H
