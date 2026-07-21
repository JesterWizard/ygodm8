#ifndef GUARD_SHINING_SARCOPHAGUS_H
#define GUARD_SHINING_SARCOPHAGUS_H

#include "effect.h"

u8 ShiningSarcophagus_PreventsDestroy(const struct DuelCard *zone);
u8 Cond_ShiningSarcophagusOnSummon(struct EffectCtx *ctx);
enum DuelActionResult Op_ShiningSarcophagusOnSummon(struct EffectCtx *ctx);

#endif /* GUARD_SHINING_SARCOPHAGUS_H */
