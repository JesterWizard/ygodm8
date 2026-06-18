#ifndef GUARD_REAPER_ON_THE_NIGHTMARE_H
#define GUARD_REAPER_ON_THE_NIGHTMARE_H

#include "global.h"

#define REAPER_DISCARD_PENDING_NONE 0xFF

extern u8 gPendingReaperDiscardDuelist;

u8 CanReaperOnTheNightmareAttackDirectly(u16 cardId);
void ApplyReaperOnTheNightmareDirectDamageEffect(void);
void ResolveReaperOnTheNightmareDirectDamageEffect(void);
void ClearReaperDiscardPending(void);

#endif // GUARD_REAPER_ON_THE_NIGHTMARE_H
