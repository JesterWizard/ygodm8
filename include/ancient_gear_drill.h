#ifndef GUARD_ANCIENT_GEAR_DRILL_H
#define GUARD_ANCIENT_GEAR_DRILL_H

#include "gba/types.h"

struct DuelCard;

u8 AncientGearDrill_BlocksSpellActivation(struct DuelCard *zone);
void AncientGearDrill_OnTurnBoundary(void);

#endif /* GUARD_ANCIENT_GEAR_DRILL_H */
