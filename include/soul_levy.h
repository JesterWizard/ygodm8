#ifndef GUARD_SOUL_LEVY_H
#define GUARD_SOUL_LEVY_H

#include "effect.h"

u8 Cond_SoulLevyOnSummon(struct EffectCtx *ctx);
enum DuelActionResult Op_SoulLevyOnSummon(struct EffectCtx *ctx);
void TryActivateSOUL_LEVYOnOpponentTurnStart(void);

#endif /* GUARD_SOUL_LEVY_H */
