#ifndef GUARD_LIGHT_BARRIER_H
#define GUARD_LIGHT_BARRIER_H

#include "gba/types.h"

struct DuelCard;

u8 LightBarrier_IsActiveForDuelist(u8 fixedDuelist);
u8 LightBarrier_IsNegatedForDuelist(u8 fixedDuelist);
void LightBarrier_ResolveStandbyCoin(u8 fixedDuelist, u8 heads);
u8 LightBarrier_AllowsArcanaForceCoinChoice(u8 fixedDuelist);
u16 LightBarrier_GetArcanaForceBattleDestroyLp(u8 fixedDuelist,
                                                const struct DuelCard *attacker,
                                                const struct DuelCard *destroyed);
void ApplyLightBarrierBattleEffect(void);

#endif /* GUARD_LIGHT_BARRIER_H */
