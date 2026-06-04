#ifndef GUARD_GRAVEYARD_EFFECTS_H
#define GUARD_GRAVEYARD_EFFECTS_H

#include "global.h"

extern u8 gDeferGraveyardDrawBattleResolve;

u8 CardTriggersDrawOnFieldDestroy(u16 cardId);
unsigned char ShouldActivateGraveyardDrawOnDestroy(void);
void ActivateGraveyardDrawOnDestroy(void);
void FinishGraveyardDrawBattleResolve(void);

#endif
