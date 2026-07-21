#ifndef GUARD_GEARTOWN_H
#define GUARD_GEARTOWN_H

#include "effect.h"

u8 Geartown_ReduceRequiredTributes(u16 cardId, int requiredTributes);
u8 Cond_GeartownOnDestroy(struct EffectCtx *ctx);
enum DuelActionResult Op_GeartownOnDestroy(struct EffectCtx *ctx);

#endif /* GUARD_GEARTOWN_H */
