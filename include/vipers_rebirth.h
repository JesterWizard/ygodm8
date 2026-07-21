#ifndef GUARD_VIPERS_REBIRTH_H
#define GUARD_VIPERS_REBIRTH_H

#include "gba/types.h"

struct DuelCard;

void VipersRebirth_StampSummonedZone(struct DuelCard *zone);
void TryApplyVipersRebirthEndPhase(void);

#endif /* GUARD_VIPERS_REBIRTH_H */
