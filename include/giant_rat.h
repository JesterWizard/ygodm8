#ifndef GUARD_GIANT_RAT_H
#define GUARD_GIANT_RAT_H

#include "global.h"

extern u8 gGiantRatBattleDestroyMask;

void MarkGiantRatBattleDestruction(u8 fixedDuelist, u16 cardId);
unsigned char ShouldActivateGiantRat(void);
void ActivateGiantRat(void);

#endif
