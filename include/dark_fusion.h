#ifndef GUARD_DARK_FUSION_H
#define GUARD_DARK_FUSION_H

#include "gba/types.h"

struct DuelCard;

/* Parent marks the Fusion result, rejects protected targets, and clears at turn boundary. */
void DarkFusion_MarkSummonedZone(struct DuelCard *zone);
u8 DarkFusion_IsTargetProtected(const struct DuelCard *zone);
void DarkFusion_ClearOnTurnBoundary(void);

#endif /* GUARD_DARK_FUSION_H */
