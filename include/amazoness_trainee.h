#ifndef GUARD_AMAZONESS_TRAINEE_H
#define GUARD_AMAZONESS_TRAINEE_H

#include "global.h"

#define AMAZONESS_TRAINEE_PENDING_NONE 0xFF

extern u8 gAmazonessTraineePendingDefenderRow;
extern u8 gAmazonessTraineePendingDefenderCol;
extern u8 gAmazonessTraineePendingAttackerRow;
extern u8 gAmazonessTraineePendingAttackerCol;

void ApplyAmazonessTraineeBattleEffect(void);
void ResolveAmazonessTraineeBattleEffect(void);
void ClearAmazonessTraineePending(void);

#endif /* GUARD_AMAZONESS_TRAINEE_H */
