#ifndef GUARD_INSTANT_NEO_SPACE_H
#define GUARD_INSTANT_NEO_SPACE_H

#include "gba/types.h"

struct DuelCard;

/* Wire into the Neos Contact Fusion End Phase return check. */
u8 InstantNeoSpace_PreventsEndPhaseExtraDeckReturn(const struct DuelCard *zone);
/* Wire from OnDynamicEquipZoneAboutToClear before its link is discarded. */
u8 InstantNeoSpace_ShouldSpecialSummonNeosOnLeave(const struct DuelCard *zone);

#endif /* GUARD_INSTANT_NEO_SPACE_H */
