#ifndef GUARD_FIELD_BARRIER_H
#define GUARD_FIELD_BARRIER_H

#include "gba/types.h"

struct DuelCard;

u8 FieldBarrier_IsFieldSpellCard(u16 cardId);
u8 FieldBarrier_PreventsFieldSpellDestroy(const struct DuelCard *zone);
u8 FieldBarrier_BlocksNewFieldSpellActivation(u8 activatorFixed);

#endif /* GUARD_FIELD_BARRIER_H */
