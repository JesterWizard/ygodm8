#ifndef GUARD_PYRAMID_OF_LIGHT_H
#define GUARD_PYRAMID_OF_LIGHT_H

#include "global.h"

u8 IsPyramidOfLightActiveOnField(void);
u8 IsActivatedPyramidOfLightZone(const struct DuelCard *zone);
u8 ShouldBlockGodCardSummon(u16 cardId);
void EnforcePyramidOfLightGodBan(void);

#endif // GUARD_PYRAMID_OF_LIGHT_H
