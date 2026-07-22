#ifndef GUARD_CANNOT_ATTACK_THIS_TURN_H
#define GUARD_CANNOT_ATTACK_THIS_TURN_H

#include "global.h"

#define DUEL_CANNOT_ATTACK_THIS_TURN_MARK 0x80

u8 CannotAttackThisTurn_CanDeclareAttack(const struct DuelCard *zone);
void CannotAttackThisTurn_ClearMarksAtEndPhase(void);

#endif /* GUARD_CANNOT_ATTACK_THIS_TURN_H */
