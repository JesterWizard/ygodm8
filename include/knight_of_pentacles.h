#ifndef GUARD_KNIGHT_OF_PENTACLES_H
#define GUARD_KNIGHT_OF_PENTACLES_H

#include "global.h"

#define KNIGHT_OF_PENTACLES_COIN_HEADS 1
#define KNIGHT_OF_PENTACLES_COIN_TAILS 2

u8 KnightOfPentacles_ProtectsBattleZone(u8 fixedRow, u8 fixedCol);
u8 KnightOfPentacles_CanAttackMonsterZone(struct DuelCard *zone);
void ApplyKnightOfPentaclesTailsWhenAttacked(void);

#endif /* GUARD_KNIGHT_OF_PENTACLES_H */
