#ifndef GUARD_MONSTER_EFFECT_USAGE_H
#define GUARD_MONSTER_EFFECT_USAGE_H

#include "constants/effect_usage.h"

u8 GetCardEffectUsage(u16 cardId);
u8 CanUseMonsterEffect(struct DuelCard *zone);
void MarkMonsterEffectUsed(struct DuelCard *zone);

#endif // GUARD_MONSTER_EFFECT_USAGE_H
