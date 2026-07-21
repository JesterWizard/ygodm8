#ifndef GUARD_AMAZONESS_VILLAGE_H
#define GUARD_AMAZONESS_VILLAGE_H

#include "effect.h"

struct DuelCard;

void ApplyAmazonessVillageFieldStatBoostForZone(struct DuelCard *zone);
u8 Cond_AmazonessVillageDestroySs(struct EffectCtx *ctx);
enum DuelActionResult Op_AmazonessVillageDestroySs(struct EffectCtx *ctx);

#endif /* GUARD_AMAZONESS_VILLAGE_H */
