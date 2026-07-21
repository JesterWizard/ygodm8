#ifndef GUARD_FORBIDDEN_LANCE_H
#define GUARD_FORBIDDEN_LANCE_H

#include "global.h"

u8 ForbiddenLance_IsImmuneToSpellTrapEffects(const struct DuelCard *zone);
void ForbiddenLance_ClearOnTurnBoundary(void);

#endif /* GUARD_FORBIDDEN_LANCE_H */
