#ifndef GUARD_RED_DRAGON_ARCHFIEND_H
#define GUARD_RED_DRAGON_ARCHFIEND_H

#define RED_DRAGON_ARCHFIEND_PENDING_NONE 0xFF

extern u8 gPendingRedDragonArchfiendFixedRow;

void ApplyRedDragonArchfiendBattleEffect(void);
void ResolveRedDragonArchfiendBattleEffect(void);
void ClearRedDragonArchfiendPending(void);

#endif
