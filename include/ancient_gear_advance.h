#ifndef GUARD_ANCIENT_GEAR_ADVANCE_H
#define GUARD_ANCIENT_GEAR_ADVANCE_H

#include "gba/types.h"

u8 AncientGearAdvance_CanNormalSummonWithoutTribute(u16 cardId);
u8 AncientGearAdvance_TryConsumeOnNormalSummon(u16 cardId);
u8 AncientGearAdvance_CannotSetThisTurn(void);
void AncientGearAdvance_OnTurnBoundary(void);

#endif /* GUARD_ANCIENT_GEAR_ADVANCE_H */
