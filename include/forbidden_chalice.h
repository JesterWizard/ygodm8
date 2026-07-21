#ifndef GUARD_FORBIDDEN_CHALICE_H
#define GUARD_FORBIDDEN_CHALICE_H

#include "global.h"

struct DuelCard;

#define FORBIDDEN_CHALICE_ATK_BOOST 400

u8 ForbiddenChalice_IsNegated(const struct DuelCard *zone);
void ForbiddenChalice_ClearOnTurnBoundary(void);

#endif /* GUARD_FORBIDDEN_CHALICE_H */
