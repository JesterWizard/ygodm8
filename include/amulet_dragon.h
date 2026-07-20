#ifndef GUARD_AMULET_DRAGON_H
#define GUARD_AMULET_DRAGON_H

#include "global.h"

#define AMULET_DRAGON_ATK_PER_BANISH 100

void TryAmuletDragonOnMonsterPlacement(struct DuelCard *zone);
u8 AmuletDragon_ApplyDynamicZoneStats(struct DuelCard *zone);

unsigned char ShouldActivateAmuletDragonDestroy(void);
void ActivateAmuletDragonDestroy(void);

#endif // GUARD_AMULET_DRAGON_H
