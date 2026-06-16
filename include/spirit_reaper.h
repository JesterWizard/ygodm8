#ifndef GUARD_SPIRIT_REAPER_H
#define GUARD_SPIRIT_REAPER_H

#include "global.h"

#define SPIRIT_REAPER_DISCARD_PENDING_NONE 0xFF

extern u8 gPendingSpiritReaperDiscardDuelist;

void ApplySpiritReaperDiscardBattleEffect(void);
void ResolveSpiritReaperDiscardBattleEffect(void);
void ClearSpiritReaperDiscardPending(void);

#endif // GUARD_SPIRIT_REAPER_H
