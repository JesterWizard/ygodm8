#ifndef GUARD_EXTRA_ATTACK_UNK4_H
#define GUARD_EXTRA_ATTACK_UNK4_H

#include "global.h"

struct DuelCard;

void TryUnlockUnk4MarkedExtraAttack(struct DuelCard *attacker);
void TryMarkBuiltInExtraAttackOnPlacement(struct DuelCard *zone);

#endif /* GUARD_EXTRA_ATTACK_UNK4_H */
