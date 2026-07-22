#ifndef GUARD_HELIOS_TRICE_MEGISTUS_H
#define GUARD_HELIOS_TRICE_MEGISTUS_H

#include "global.h"

u8 HeliosTriceMegistus_ApplyDynamicZoneStats(struct DuelCard *zone);
void ApplyHeliosTriceMegistusBattleDestroyPending(void);
void TryApplyHeliosTriceMegistusEndPhase(void);

#endif /* GUARD_HELIOS_TRICE_MEGISTUS_H */
