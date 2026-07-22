#ifndef GUARD_GANDORA_X_H
#define GUARD_GANDORA_X_H

#include "global.h"

struct DuelCard;

u8 GandoraX_ApplyDynamicZoneStats(struct DuelCard *zone);
void TryApplyGandoraXEndPhase(void);

#endif /* GUARD_GANDORA_X_H */
