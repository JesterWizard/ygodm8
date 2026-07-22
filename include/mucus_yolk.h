#ifndef GUARD_MUCUS_YOLK_H
#define GUARD_MUCUS_YOLK_H

#include "global.h"

u8 CanMucusYolkAttackDirectly(u16 cardId);
void ApplyMucusYolkBattleEffect(void);
void MucusYolk_EnsureInit(void);
u8 MucusYolk_ApplyDynamicZoneStats(struct DuelCard *zone);

#endif /* GUARD_MUCUS_YOLK_H */
