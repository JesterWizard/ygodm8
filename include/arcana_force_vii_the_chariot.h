#ifndef GUARD_ARCANA_FORCE_VII_THE_CHARIOT_H
#define GUARD_ARCANA_FORCE_VII_THE_CHARIOT_H

#include "global.h"

#define ARCANA_FORCE_VII_THE_CHARIOT_PENDING_NONE 0xFF

extern u8 gArcanaForceViiChariotPendingController;
extern u8 gArcanaForceViiChariotPendingGraveyardDuelist;

void ApplyArcanaForceViiChariotBattleEffect(void);
void ResolveArcanaForceViiChariotBattleEffect(void);
void ClearArcanaForceViiChariotPending(void);

#endif /* GUARD_ARCANA_FORCE_VII_THE_CHARIOT_H */
