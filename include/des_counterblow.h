#ifndef GUARD_DES_COUNTERBLOW_H
#define GUARD_DES_COUNTERBLOW_H

#include "gba/types.h"

void TryApplyDesCounterblowAfterDirectDamage(u8 damagedFixedDuelist);
void TryActivateDES_COUNTERBLOWOnOpponentTurnStart(void);

#endif /* GUARD_DES_COUNTERBLOW_H */
