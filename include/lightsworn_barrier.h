#ifndef GUARD_LIGHTSWORN_BARRIER_H
#define GUARD_LIGHTSWORN_BARRIER_H

#include "duel.h"

void LightswornBarrier_OnAttackDeclare(struct DuelCard *attacker, struct DuelCard *defender);
void TryActivateLIGHTSWORN_BARRIEROnOpponentTurnStart(void);

#endif
