#ifndef SERAPHIM_BLASTER_H
#define SERAPHIM_BLASTER_H

#include "global.h"

u8 SeraphimBlaster_ApplyDynamicZoneStats(struct DuelCard *zone);
void SeraphimBlaster_OnZoneCleared(const struct DuelCard *zone);

#endif // SERAPHIM_BLASTER_H
