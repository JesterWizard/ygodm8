#ifndef GUARD_CLOCK_TOWER_PRISON_H
#define GUARD_CLOCK_TOWER_PRISON_H

#include "effect.h"

#define CLOCK_TOWER_PRISON_MAX_COUNTERS 4

struct DuelCard;

u8 ClockTowerPrison_FindFaceUpZone(u8 fixedDuelist, struct DuelCard **outZone);
u8 ClockTowerPrison_ShouldBlockBattleDamage(u8 damagedFixedDuelist);
u8 Cond_ClockTowerPrisonOnOppStandby(struct EffectCtx *ctx);
enum DuelActionResult Op_ClockTowerPrisonOnOppStandby(struct EffectCtx *ctx);
u8 Cond_ClockTowerPrisonOnDestroy(struct EffectCtx *ctx);
enum DuelActionResult Op_ClockTowerPrisonOnDestroy(struct EffectCtx *ctx);

#endif /* GUARD_CLOCK_TOWER_PRISON_H */
