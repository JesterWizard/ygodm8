#ifndef GUARD_TORNADO_WALL_H
#define GUARD_TORNADO_WALL_H

#include "gba/types.h"

u8 TornadoWall_ShouldBlockBattleDamage(u8 damagedFixedDuelist);
void TornadoWall_CheckAfterFieldChange(void);
void TryActivateTORNADO_WALLOnOpponentTurnStart(void);

#endif /* GUARD_TORNADO_WALL_H */
