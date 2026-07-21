#ifndef GUARD_AMAZONESS_SPY_H
#define GUARD_AMAZONESS_SPY_H

#include "global.h"

#define AMAZONESS_SPY_PENDING_NONE 0xFF

extern u8 gAmazonessSpyPendingController;

void ApplyAmazonessSpyBattleEffect(void);
void ResolveAmazonessSpyBattleEffect(void);
void ClearAmazonessSpyPending(void);

#endif /* GUARD_AMAZONESS_SPY_H */
