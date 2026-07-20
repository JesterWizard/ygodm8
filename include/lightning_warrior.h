#ifndef GUARD_LIGHTNING_WARRIOR_H
#define GUARD_LIGHTNING_WARRIOR_H

#define LIGHTNING_WARRIOR_PENDING_NONE 0xFF

extern u8 gPendingLightningWarriorDuelist;
extern u16 gPendingLightningWarriorBurn;
extern u16 gPendingLightningWarriorEffectCardId;

void ApplyLightningWarriorBattleEffect(void);
void ResolveLightningWarriorBattleEffect(void);
void ClearLightningWarriorPending(void);

#endif
