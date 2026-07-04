#ifndef GUARD_LYRILUSC_INDEPENDENT_NIGHTINGALE_H
#define GUARD_LYRILUSC_INDEPENDENT_NIGHTINGALE_H

#include "global.h"

unsigned char CanActivateLyriluscIndependentNightingale(void);
void ActivateLyriluscIndependentNightingaleEffect(void);
u8 LyriluscIndependentNightingale_ApplyDynamicZoneStats(struct DuelCard *zone);
/* ATK added when another card has copied this effect (500 × host Level). */
u16 LyriluscIndependentNightingale_CopiedAtkBonus(struct DuelCard *hostZone);

#endif // GUARD_LYRILUSC_INDEPENDENT_NIGHTINGALE_H
