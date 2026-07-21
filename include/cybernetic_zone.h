#ifndef GUARD_CYBERNETIC_ZONE_H
#define GUARD_CYBERNETIC_ZONE_H

#include "gba/types.h"

u8 CanActivateCYBERNETIC_ZONE(void);
void TryApplyCyberneticZoneEndPhase(void);
void TryApplyCyberneticZoneStandby(void);
void ApplyCyberneticZoneAtkBonusToCardInfo(const struct DuelCard *zone);

#endif /* GUARD_CYBERNETIC_ZONE_H */
