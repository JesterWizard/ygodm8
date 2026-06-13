#ifndef GUARD_CURSE_OF_DARKNESS_H
#define GUARD_CURSE_OF_DARKNESS_H

#include "gba/types.h"

void TryActivateCurseOfDarknessOnOpponentTurnStart(void);
void TryApplyCurseOfDarknessSpellDamage(void);
u8 IsActivatedCurseOfDarknessZone(const struct DuelCard *zone);

#endif
