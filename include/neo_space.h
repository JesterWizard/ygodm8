#ifndef GUARD_NEO_SPACE_H
#define GUARD_NEO_SPACE_H

#include "gba/types.h"

struct DuelCard;

u8 NeoSpace_IsAtkTarget(u16 cardId);
void ApplyNeoSpaceAtkBoostForZone(struct DuelCard *zone);
u8 NeoSpace_PreventsEndPhaseExtraDeckReturn(const struct DuelCard *zone);

#endif /* GUARD_NEO_SPACE_H */
