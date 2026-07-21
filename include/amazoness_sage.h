#ifndef GUARD_AMAZONESS_SAGE_H
#define GUARD_AMAZONESS_SAGE_H

#include "global.h"

#define AMAZONESS_SAGE_PENDING_NONE 0xFF

extern u8 gAmazonessSagePendingRow;
extern u8 gAmazonessSagePendingCol;

void ApplyAmazonessSageBattleEffect(void);
void ResolveAmazonessSageBattleEffect(void);
void ClearAmazonessSagePending(void);

#endif /* GUARD_AMAZONESS_SAGE_H */
