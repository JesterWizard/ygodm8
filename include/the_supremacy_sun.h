#ifndef GUARD_THE_SUPREMACY_SUN_H
#define GUARD_THE_SUPREMACY_SUN_H

#include "global.h"

extern u8 gTheSupremacySunArmed[2];
extern u8 gTheSupremacySunStandbyReady[2];
extern u8 gTheSupremacySunOwnEffectSummon;

void ClearTheSupremacySunState(void);
void MarkTheSupremacySunDestroyedFromField(struct DuelCard *zone);
void TheSupremacySun_AgeStandbyFlags(void);
void TheSupremacySun_TryResolveStandbyRevive(void);

#endif // GUARD_THE_SUPREMACY_SUN_H
