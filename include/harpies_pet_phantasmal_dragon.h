#ifndef GUARD_HARPIES_PET_PHANTASMAL_DRAGON_H
#define GUARD_HARPIES_PET_PHANTASMAL_DRAGON_H

#include "global.h"

u8 HarpiesPetPhantasmalDragon_CanAttackDirectly(const struct DuelCard *zone);
u8 HarpiesPetPhantasmalDragon_CanAttackMonsterZone(struct DuelCard *zone);
u8 HarpiesPetPhantasmalDragon_IsTargetImmune(struct DuelCard *zone);
void TryApplyHarpiesPetPhantasmalDragonEndPhase(void);

#endif /* GUARD_HARPIES_PET_PHANTASMAL_DRAGON_H */
