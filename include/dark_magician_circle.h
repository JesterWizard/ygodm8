#ifndef GUARD_DARK_MAGICIAN_CIRCLE_H
#define GUARD_DARK_MAGICIAN_CIRCLE_H

#include "effect.h"

/* Register as ON_SUMMON TRIGGER; operation owns the PickZone/EffectOpt flow. */
u8 Cond_DarkMagicianCircleOnDarkMagicianSummon(struct EffectCtx *ctx);
enum DuelActionResult Op_DarkMagicianCircleOnDarkMagicianSummon(struct EffectCtx *ctx);

#endif /* GUARD_DARK_MAGICIAN_CIRCLE_H */
