#ifndef GUARD_AMAZONESS_AUGUSTA_H
#define GUARD_AMAZONESS_AUGUSTA_H

#include "global.h"

struct DuelCard;

/* Fusion Summon trigger: optional Deck SS + Queen/Empress material → second attack. */
void AmazonessAugusta_OnFusionSummoned(struct DuelCard *zone, const u16 *materialIds,
                                      u8 materialCount);

/* Other Amazoness: cannot be targeted / destroyed by opponent card effects. */
u8 AmazonessAugusta_PreventsDestroy(const struct DuelCard *zone);
u8 AmazonessAugusta_IsTargetImmune(const struct DuelCard *zone);

#endif /* GUARD_AMAZONESS_AUGUSTA_H */
