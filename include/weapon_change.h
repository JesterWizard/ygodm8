#ifndef GUARD_WEAPON_CHANGE_H
#define GUARD_WEAPON_CHANGE_H

#include "gba/types.h"

void TryApplyWeaponChangeStandby(void);
void TryClearWeaponChangeOnOpponentEndPhase(u8 endedFixedDuelist);
void ApplyWeaponChangeAtkDefSwapToCardInfo(const struct DuelCard *zone);

#endif /* GUARD_WEAPON_CHANGE_H */
