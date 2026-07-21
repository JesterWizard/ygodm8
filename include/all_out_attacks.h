#ifndef GUARD_ALL_OUT_ATTACKS_H
#define GUARD_ALL_OUT_ATTACKS_H

#include "effect.h"

u8 Cond_AllOutAttacksOnSummon(struct EffectCtx *ctx);
enum DuelActionResult Op_AllOutAttacksOnSummon(struct EffectCtx *ctx);
void TryActivateALL_OUT_ATTACKSOnOpponentTurnStart(void);

#endif /* GUARD_ALL_OUT_ATTACKS_H */
