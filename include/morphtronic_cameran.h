#ifndef GUARD_MORPHTRONIC_CAMERAN_H
#define GUARD_MORPHTRONIC_CAMERAN_H

#include "global.h"

struct DuelCard;

void MorphtronicCameran_EnsureInit(void);
u8 MorphtronicCameran_ProtectsZoneFromTargeting(const struct DuelCard *zone);
u8 MorphtronicCameran_CanAttackMonsterZone(struct DuelCard *zone);

#endif /* GUARD_MORPHTRONIC_CAMERAN_H */
