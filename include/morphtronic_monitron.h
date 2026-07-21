#ifndef GUARD_MORPHTRONIC_MONITRON_H
#define GUARD_MORPHTRONIC_MONITRON_H

#include "effect.h"

u8 Cond_MorphtronicMonitronOnSummon(struct EffectCtx *ctx);
enum DuelActionResult Op_MorphtronicMonitronOnSummon(struct EffectCtx *ctx);
void TryActivateMORPHTRONIC_MONITRONOnOpponentTurnStart(void);

#endif
