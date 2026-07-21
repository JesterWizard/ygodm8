#ifndef GUARD_THUMBS_DOWN_H
#define GUARD_THUMBS_DOWN_H

#include "effect.h"

u8 Cond_ThumbsDownOnDestroy(struct EffectCtx *ctx);
enum DuelActionResult Op_ThumbsDownOnDestroy(struct EffectCtx *ctx);
void TryActivateTHUMBS_DOWNOnOpponentTurnStart(void);

#endif /* GUARD_THUMBS_DOWN_H */
