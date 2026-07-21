#ifndef GUARD_OVER_DESTINY_H
#define GUARD_OVER_DESTINY_H

#include "gba/types.h"

struct DuelCard;

void OverDestiny_StampSummonedZone(struct DuelCard *zone);
void TryApplyOverDestinyEndPhase(void);

#endif /* GUARD_OVER_DESTINY_H */
