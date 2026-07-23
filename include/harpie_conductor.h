#ifndef GUARD_HARPIE_CONDUCTOR_H
#define GUARD_HARPIE_CONDUCTOR_H

#include "global.h"

void HarpieConductor_EnsureInit(void);
void HarpieConductor_OnHarpieReturned(u8 controller, u16 cardId);
u8 HarpieConductor_TryProtectHarpie(struct DuelCard *zone);
u8 HarpieConductor_PreventsBattleDestroy(struct DuelCard *zone);
void HarpieConductor_ClearOnTurnBoundary(void);

#endif /* GUARD_HARPIE_CONDUCTOR_H */
