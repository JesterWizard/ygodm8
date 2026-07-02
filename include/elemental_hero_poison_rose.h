#ifndef GUARD_ELEMENTAL_HERO_POISON_ROSE_H
#define GUARD_ELEMENTAL_HERO_POISON_ROSE_H

#include "global.h"

u8 ElementalHeroPoisonRose_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroPoisonRose_CanAttackMonsterZone(struct DuelCard *zone);
struct DuelCard *ElementalHeroPoisonRose_GetForcedAttackTarget(u8 defenderDuelist);
void ApplyElementalHeroPoisonRoseBattleEffect(void);

#endif // GUARD_ELEMENTAL_HERO_POISON_ROSE_H
