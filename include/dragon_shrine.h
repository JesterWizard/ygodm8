#ifndef GUARD_DRAGON_SHRINE_H
#define GUARD_DRAGON_SHRINE_H

#include "gba/types.h"

/* EffectOpt-backed OPT; EffectEvent_OnTurnBoundary clears the shared state. */
u8 DragonShrine_IsOptUsed(void);
void DragonShrine_MarkOptUsed(void);
u8 CanActivateDRAGON_SHRINE(void);

#endif /* GUARD_DRAGON_SHRINE_H */
