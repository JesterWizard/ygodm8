#ifndef GUARD_BACKFIRE_H
#define GUARD_BACKFIRE_H

#include "effect.h"

u8 Cond_BackfireOnDestroy(struct EffectCtx *ctx);
enum DuelActionResult Op_BackfireOnDestroy(struct EffectCtx *ctx);
void TryActivateBACKFIREOnOpponentTurnStart(void);

#endif /* GUARD_BACKFIRE_H */
