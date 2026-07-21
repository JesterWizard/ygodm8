#ifndef GUARD_BUBBLE_BLASTER_H
#define GUARD_BUBBLE_BLASTER_H

#include "gba/types.h"

struct DuelCard;

#define BUBBLE_BLASTER_ATK_BOOST 800

u8 CanActivateBUBBLE_BLASTER(void);
void ApplyBubbleBlasterAtkBonusToCardInfo(const struct DuelCard *zone);
void ApplyBubbleBlasterBattleProtection(void);

#endif /* GUARD_BUBBLE_BLASTER_H */
