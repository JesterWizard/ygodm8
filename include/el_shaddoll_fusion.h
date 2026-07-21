#ifndef GUARD_EL_SHADDOLL_FUSION_H
#define GUARD_EL_SHADDOLL_FUSION_H

#include "gba/types.h"

/* EffectOpt-backed OPT; EffectEvent_OnTurnBoundary clears the shared state. */
u8 ElShaddollFusion_IsOptUsed(void);
void ElShaddollFusion_MarkOptUsed(void);

#endif /* GUARD_EL_SHADDOLL_FUSION_H */
