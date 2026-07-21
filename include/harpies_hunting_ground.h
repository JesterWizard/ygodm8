#ifndef GUARD_HARPIES_HUNTING_GROUND_H
#define GUARD_HARPIES_HUNTING_GROUND_H

#include "effect.h"

struct DuelCard;

#define HARPIES_HUNTING_GROUND_STAT_BONUS 200

/* Wire into both card-info stat paths after the base card stats are loaded. */
void ApplyHarpiesHuntingGroundStatBonusToCardInfo(const struct DuelCard *zone);

/* Register as an ON_SUMMON TRIGGER; operation owns the Spell/Trap PickZone flow. */
u8 Cond_HarpiesHuntingGroundOnHarpieSummon(struct EffectCtx *ctx);
enum DuelActionResult Op_HarpiesHuntingGroundOnHarpieSummon(struct EffectCtx *ctx);

#endif /* GUARD_HARPIES_HUNTING_GROUND_H */
