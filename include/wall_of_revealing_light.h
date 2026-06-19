#ifndef GUARD_WALL_OF_REVEALING_LIGHT_H
#define GUARD_WALL_OF_REVEALING_LIGHT_H

#include "global.h"

#define TRAP_WALL_OF_REVEALING_LIGHT 32

extern u16 gWallOfRevealingLightAttackThreshold;

u8 IsActivatedWallOfRevealingLightZone(const struct DuelCard *zone);
u8 IsWallOfRevealingLightActiveOnField(void);
u8 WallOfRevealingLight_ShouldActivateTrapOnAttack(const struct DuelCard *trapZone, u16 attackerCardId);
u8 WallOfRevealingLight_CanMonsterAttack(const struct DuelCard *zone);
void WallOfRevealingLight_ClearThreshold(void);
void EffectWallOfRevealingLight(void);

#endif // GUARD_WALL_OF_REVEALING_LIGHT_H
