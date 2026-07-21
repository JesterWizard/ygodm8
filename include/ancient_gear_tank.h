#ifndef GUARD_ANCIENT_GEAR_TANK_H
#define GUARD_ANCIENT_GEAR_TANK_H

#include "effect.h"

#define ANCIENT_GEAR_TANK_ATK_BONUS 600

struct DuelCard;

u8 Cond_AncientGearTankOnDestroy(struct EffectCtx *ctx);
enum DuelActionResult Op_AncientGearTankOnDestroy(struct EffectCtx *ctx);
void ApplyAncientGearTankAtkBonusToCardInfo(const struct DuelCard *zone);

#endif /* GUARD_ANCIENT_GEAR_TANK_H */
