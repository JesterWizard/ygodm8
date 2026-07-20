#ifndef GUARD_DON_ZALOOG_H
#define GUARD_DON_ZALOOG_H

#define DON_ZALOOG_PENDING_NONE 0xFF

extern u8 gPendingDonZaloogTargetDuelist;

void ApplyDonZaloogBattleEffect(void);
void ResolveDonZaloogBattleEffect(void);
void ClearDonZaloogPending(void);

#endif
