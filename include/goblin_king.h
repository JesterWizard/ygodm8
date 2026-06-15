#ifndef GUARD_GOBLIN_KING_H
#define GUARD_GOBLIN_KING_H

#include "global.h"
#include "card.h"

u8 ApplyGoblinKingZoneStatsToCardInfo(struct DuelCard *zone);
u8 ApplyGoblinKingStatsToCardInfo(struct StatMod *ptr);
u8 GoblinKing_CanBeAttacked(struct DuelCard *zone);

#endif // GUARD_GOBLIN_KING_H
