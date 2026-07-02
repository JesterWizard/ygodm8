#ifndef GUARD_ELEMENTAL_HERO_KNOSPE_H
#define GUARD_ELEMENTAL_HERO_KNOSPE_H

#include "global.h"

u8 ElementalHeroKnospe_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroKnospe_CanAttackMonsterZone(struct DuelCard *zone);
u8 CanElementalHeroKnospeAttackDirectly(u16 cardId);
void TryShowElementalHeroKnospeDirectAttackText(u16 cardId);
void ApplyElementalHeroKnospeBattleEffect(void);

#endif // GUARD_ELEMENTAL_HERO_KNOSPE_H
