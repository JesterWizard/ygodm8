#ifndef GUARD_EVIL_MIND_H
#define GUARD_EVIL_MIND_H

#include "gba/types.h"

/* EffectOpt-backed OPT; EffectEvent_OnTurnBoundary clears the shared state. */
u8 EvilMind_IsOptUsed(void);
void EvilMind_MarkOptUsed(void);

#endif /* GUARD_EVIL_MIND_H */
