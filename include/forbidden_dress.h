#ifndef GUARD_FORBIDDEN_DRESS_H
#define GUARD_FORBIDDEN_DRESS_H

#include "global.h"

u8 ForbiddenDress_IsTargetImmune(const struct DuelCard *zone);
u8 ForbiddenDress_IsDestroyImmune(const struct DuelCard *zone);
void ForbiddenDress_ClearOnTurnBoundary(void);

#endif /* GUARD_FORBIDDEN_DRESS_H */
