#ifndef GUARD_AROMA_GARDENING_H
#define GUARD_AROMA_GARDENING_H

#include "effect.h"

u8 Cond_AromaGardeningOnSummon(struct EffectCtx *ctx);
enum DuelActionResult Op_AromaGardeningOnSummon(struct EffectCtx *ctx);

void ApplyAromaGardeningAttackDeclare(void);

#endif /* GUARD_AROMA_GARDENING_H */
