#ifndef GUARD_BOARD_PLACEMENT_H
#define GUARD_BOARD_PLACEMENT_H

#include "gba/types.h"
#include "duel.h"

u8 Board_IsMirroredFixedRow(u8 fixedRow);
u8 Board_PreferredEmptyFixedCol(u8 fixedRow);
u8 Board_PreferredEmptyTurnCol(u8 fixedRow, u8 turnRow);
u8 Board_TurnColForZone(u8 turnRow, struct DuelCard *zone);

u8 Board_PreferredEmptyMonsterTurnCol(void);
u8 Board_PreferredEmptyBackrowTurnCol(void);

#endif
