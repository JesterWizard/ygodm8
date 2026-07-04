#ifndef GUARD_THEBAN_NIGHTMARE_H
#define GUARD_THEBAN_NIGHTMARE_H

#include "global.h"

u8 ThebanNightmare_ApplyDynamicZoneStats(struct DuelCard *zone);
/* ATK added when another card has copied this effect (+1500 if hand/S/T empty). */
u16 ThebanNightmare_CopiedAtkBonus(struct DuelCard *hostZone);

#endif // GUARD_THEBAN_NIGHTMARE_H
