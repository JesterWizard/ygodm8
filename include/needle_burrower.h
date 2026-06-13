#ifndef GUARD_NEEDLE_BURROWER_H
#define GUARD_NEEDLE_BURROWER_H

#define NEEDLE_BURROWER_PENDING_NONE 0xFF

extern u8 gPendingNeedleBurrowerController;
extern u8 gPendingNeedleBurrowerLevel;

void ApplyNeedleBurrowerBattleEffect(void);
void ResolveNeedleBurrowerBattleEffect(void);
void ClearNeedleBurrowerPending(void);

#endif
