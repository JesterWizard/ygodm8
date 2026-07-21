#ifndef GUARD_AMAZONESS_HEIRLOOM_H
#define GUARD_AMAZONESS_HEIRLOOM_H

#define AMAZONESS_HEIRLOOM_PENDING_NONE 0xFF

extern u8 gPendingAmazonessHeirloomDefenderRow;
extern u8 gPendingAmazonessHeirloomDefenderCol;

void ApplyAmazonessHeirloomBattleProtection(void);
void ApplyAmazonessHeirloomBattleEffect(void);
void ResolveAmazonessHeirloomBattleEffect(void);
void ClearAmazonessHeirloomPending(void);

#endif /* GUARD_AMAZONESS_HEIRLOOM_H */
