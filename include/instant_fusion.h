#ifndef GUARD_INSTANT_FUSION_H
#define GUARD_INSTANT_FUSION_H

#include "gba/types.h"

struct DuelCard;

void InstantFusion_StampSummonedZone(struct DuelCard *zone);
/* Wire clear from every monster-zone leave path. */
void InstantFusion_ClearStampedZone(const struct DuelCard *zone);
/* Wire into the End Phase destruction scan. */
u8 InstantFusion_ShouldDestroyAtEndPhase(const struct DuelCard *zone);

#endif /* GUARD_INSTANT_FUSION_H */
