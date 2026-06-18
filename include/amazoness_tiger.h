#ifndef GUARD_AMAZONESS_TIGER_H
#define GUARD_AMAZONESS_TIGER_H

#include "global.h"

void TryAmazonessTigerOnMonsterPlacement(struct DuelCard *zone);
void AmazonessTiger_EnforceUniquenessOnField(void);
u8 AmazonessTiger_CanAttackMonsterZone(struct DuelCard *zone);
u8 AmazonessTiger_ApplyDynamicZoneStats(struct DuelCard *zone);

#endif // GUARD_AMAZONESS_TIGER_H
