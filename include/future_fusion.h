#ifndef GUARD_FUTURE_FUSION_H
#define GUARD_FUTURE_FUSION_H

#include "global.h"

u8 CanActivateFutureFusion(void);
u8 IsActivatedFutureFusionZone(const struct DuelCard *zone);
void EffectFutureFusion(void);
void TryApplyFutureFusionStandby(void);
void FutureFusion_OnZoneCleared(struct DuelCard *zone);
void TryApplyFutureFusionOnMonsterLeave(struct DuelCard *zone);

#endif // GUARD_FUTURE_FUSION_H
