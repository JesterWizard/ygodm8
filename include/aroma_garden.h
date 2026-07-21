#ifndef GUARD_AROMA_GARDEN_H
#define GUARD_AROMA_GARDEN_H

#include "effect.h"

u8 Cond_AromaGardenOnDestroy(struct EffectCtx *ctx);
enum DuelActionResult Op_AromaGardenOnDestroy(struct EffectCtx *ctx);
void AromaGarden_OnEndPhase(void);
void AromaGarden_ReapplyTempBoostAfterReset(void);

#endif /* GUARD_AROMA_GARDEN_H */
