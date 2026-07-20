#ifndef GUARD_EFFECT_SYSTEM_H
#define GUARD_EFFECT_SYSTEM_H

#include "global.h"

/* Effect data system: Phase 0 dispatch + Phase 1 ops (see effect_ops.h).
 * See documentation/effect-data-system.md.
 */

enum EffectDispatchKind {
  EFFECT_KIND_SPELL = 0,
  EFFECT_KIND_TRAP = 1,
  EFFECT_KIND_ACTIVATED = 2,
  EFFECT_KIND_PERMANENT = 3,
  EFFECT_KIND_TURN = 4,
};

/* TryActivate: TRUE = data system ran the effect; caller must return. */
#define EFFECT_DISPATCH_LEGACY 0
#define EFFECT_DISPATCH_HANDLED 1

/* QueryShouldActivate: LEGACY = fall through to old shouldActivate path. */
#define EFFECT_SHOULD_LEGACY 0
#define EFFECT_SHOULD_YES 1
#define EFFECT_SHOULD_NO 2

/* Optional context for later phases (ops / events). Phase 0 ignores it. */
struct EffectDispatchCtx {
  u8 unused;
};

u8 EffectDispatch_TryActivate(u16 cardId, u8 kind);
u8 EffectDispatch_QueryShouldActivate(u16 cardId, u8 kind);

#endif /* GUARD_EFFECT_SYSTEM_H */
