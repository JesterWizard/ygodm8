#ifndef GUARD_BEAST_KING_BARBAROS_H
#define GUARD_BEAST_KING_BARBAROS_H

#include "global.h"

struct DuelCard;

u8 BeastKingBarbaros_CanNormalSummonWithoutTribute(u16 cardId);
u8 BeastKingBarbaros_ApplyDynamicZoneStats(struct DuelCard *zone);
void TryBeastKingBarbarosOnMonsterPlacement(struct DuelCard *zone);

#endif /* GUARD_BEAST_KING_BARBAROS_H */
