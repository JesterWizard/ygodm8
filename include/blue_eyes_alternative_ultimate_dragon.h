#ifndef GUARD_BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON_H
#define GUARD_BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON_H

#include "global.h"

struct DuelCard;

void BlueEyesAlternativeUltimateDragon_OnFusionSummoned(struct DuelCard *zone,
                                                        const u16 *materialIds,
                                                        u8 materialCount);
u8 BlueEyesAlternativeUltimateDragon_PreventsDestroy(const struct DuelCard *zone);
u8 BlueEyesAlternativeUltimateDragon_IsTargetImmune(const struct DuelCard *zone);

#endif /* GUARD_BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON_H */
