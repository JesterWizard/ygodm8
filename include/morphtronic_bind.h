#ifndef GUARD_MORPHTRONIC_BIND_H
#define GUARD_MORPHTRONIC_BIND_H

#include "gba/types.h"
#include "duel.h"

u8 MorphtronicBind_BlocksAttack(const struct DuelCard *attacker);
void TryActivateMORPHTRONIC_BINDOnOpponentTurnStart(void);

#endif /* GUARD_MORPHTRONIC_BIND_H */
