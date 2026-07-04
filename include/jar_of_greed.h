#ifndef GUARD_JAR_OF_GREED_H
#define GUARD_JAR_OF_GREED_H

#include "gba/types.h"

struct DuelCard;

void ActivateJarOfGreedFromZone(struct DuelCard *zone, u8 drawTurnDuelist);
void TryActivateJarOfGreedOnOpponentTurnStart(void);

#endif
