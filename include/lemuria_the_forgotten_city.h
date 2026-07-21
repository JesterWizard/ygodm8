#ifndef GUARD_LEMURIA_THE_FORGOTTEN_CITY_H
#define GUARD_LEMURIA_THE_FORGOTTEN_CITY_H

#include "gba/types.h"

struct DuelCard;

/* Wire into both field-info and battle-stat overlay pipelines. */
u8 Lemuria_IsActive(void);
void ApplyLemuriaFieldStatBoostForZone(struct DuelCard *zone);

#endif /* GUARD_LEMURIA_THE_FORGOTTEN_CITY_H */
