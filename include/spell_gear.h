#ifndef GUARD_SPELL_GEAR_H
#define GUARD_SPELL_GEAR_H

#include "gba/types.h"

void SpellGear_ArmNormalSummonLock(u8 fixedDuelist);
u8 SpellGear_BlocksNormalSummon(u8 turnDuelist);
void SpellGear_OnTurnBoundary(void);

#endif /* GUARD_SPELL_GEAR_H */
