#ifndef ELEMENTAL_HERO_ABSOLUTE_ZERO_H
#define ELEMENTAL_HERO_ABSOLUTE_ZERO_H

#include "global.h"

extern u8 gAbsoluteZeroHandGyClearPending;
extern u8 gAbsoluteZeroHandSummonCleanupPending;
extern u8 gAbsoluteZeroSuppressLeave;

u8 ElementalHeroAbsoluteZero_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroAbsoluteZero_IsActiveOnField(void);
void ElementalHeroAbsoluteZero_RefreshStatsIfActive(void);
void TryElementalHeroAbsoluteZeroOnMonsterPlacement(struct DuelCard *zone);
void MarkAbsoluteZeroHandGraveyardClear(void);
void MarkAbsoluteZeroHandSummonCleanup(void);
void ElementalHeroAbsoluteZero_BeginSuppressLeave(void);
void ElementalHeroAbsoluteZero_EndSuppressLeave(void);
void ElementalHeroAbsoluteZero_ResetPendingState(void);
void ElementalHeroAbsoluteZero_OnZoneCleared(const struct DuelCard *zone);

#endif // ELEMENTAL_HERO_ABSOLUTE_ZERO_H
