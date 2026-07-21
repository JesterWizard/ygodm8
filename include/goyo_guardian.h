#ifndef GUARD_GOYO_GUARDIAN_H
#define GUARD_GOYO_GUARDIAN_H

#include "global.h"

#define GOYO_GUARDIAN_PENDING_NONE 0xFF

extern u8 gGoyoGuardianPendingController;
extern u8 gGoyoGuardianPendingGraveyardDuelist;

void ApplyGoyoGuardianBattleEffect(void);
void ResolveGoyoGuardianBattleEffect(void);
void ClearGoyoGuardianPending(void);

#endif /* GUARD_GOYO_GUARDIAN_H */
