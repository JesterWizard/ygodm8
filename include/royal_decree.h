#ifndef GUARD_ROYAL_DECREE_H
#define GUARD_ROYAL_DECREE_H

#include "global.h"

#define TRAP_ROYAL_DECREE 29

u8 IsRoyalDecreeActiveOnField(void);
u8 IsRoyalDecreeNegatingTrap(u16 cardId);
void TryActivateRoyalDecreeOnTrapChain(void);
void TryActivateRoyalDecreeOnRespondingTrap(void);
void EffectRoyalDecree(void);

#endif // GUARD_ROYAL_DECREE_H
