#ifndef GUARD_PANDEMONIUM_H
#define GUARD_PANDEMONIUM_H

#include "effect.h"

u8 Pandemonium_IsFaceUpOnField(void);
u8 Pandemonium_ShouldSkipArchfiendMaintenance(u16 cardId);
u8 Cond_PandemoniumOnArchfiendDestroy(struct EffectCtx *ctx);
enum DuelActionResult Op_PandemoniumOnArchfiendDestroy(struct EffectCtx *ctx);

#endif /* GUARD_PANDEMONIUM_H */
