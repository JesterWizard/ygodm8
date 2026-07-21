#ifndef GUARD_ANCIENT_GEAR_CASTLE_H
#define GUARD_ANCIENT_GEAR_CASTLE_H

#include "effect.h"

struct DuelCard;

void ApplyAncientGearCastleAtkBoostForZone(struct DuelCard *zone);
u8 AncientGearCastle_CanSubstituteTributes(u16 cardId, int requiredTributes);
u8 AncientGearCastle_TryConsumeOnNormalSummon(u16 cardId);
u8 Cond_AncientGearCastleOnSummon(struct EffectCtx *ctx);
enum DuelActionResult Op_AncientGearCastleOnSummon(struct EffectCtx *ctx);

#endif /* GUARD_ANCIENT_GEAR_CASTLE_H */
