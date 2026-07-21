#ifndef GUARD_CELESTIAL_SWORD_EATOS_H
#define GUARD_CELESTIAL_SWORD_EATOS_H

#include "effect.h"

struct DuelCard;

#define CELESTIAL_SWORD_EATOS_ATK_STAGES 1
#define CELESTIAL_SWORD_EATOS_GY_ATK_PER_BANISH_STAGES 1
#define CELESTIAL_SWORD_EATOS_BANISH_ATK_BOOST 500

u8 CanActivateCELESTIAL_SWORD_EATOS(void);
void ApplyCelestialSwordEatosOnLeave(struct DuelCard *zone);
u8 Cond_CelestialSwordEatosOnLeave(struct EffectCtx *ctx);
enum DuelActionResult Op_CelestialSwordEatosOnLeave(struct EffectCtx *ctx);

#endif /* GUARD_CELESTIAL_SWORD_EATOS_H */
