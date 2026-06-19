#ifndef GUARD_FIRE_PRINCESS_H
#define GUARD_FIRE_PRINCESS_H

#include "global.h"

#define FIRE_PRINCESS_DAMAGE 500
#define FIRE_PRINCESS_PENDING_NONE 0xFF

extern u8 gSuppressFirePrincessDamage;
extern u8 gPendingFirePrincessTarget;
extern u8 gFirePrincessLpGainHandled;
extern u16 gLastHandledLpGainLp[2];

void ClearFirePrincessPending(void);
void TryApplyFirePrincessAfterLpGain(u8 gainingDuelist);
void TryNotifyFirePrincessOnLpGainAction(void);
void ResolveFirePrincessEffect(void);

#endif // GUARD_FIRE_PRINCESS_H
