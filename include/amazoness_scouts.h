#ifndef GUARD_AMAZONESS_SCOUTS_H
#define GUARD_AMAZONESS_SCOUTS_H

#include "global.h"

u8 AmazonessScouts_PreventsDestroy(const struct DuelCard *zone);
u8 AmazonessScouts_IsTargetImmune(const struct DuelCard *zone);
void AmazonessScouts_ArmProtection(u8 controller);
void AmazonessScouts_ClearTurnState(void);

#endif /* GUARD_AMAZONESS_SCOUTS_H */
