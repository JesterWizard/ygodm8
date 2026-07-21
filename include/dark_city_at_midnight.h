#ifndef GUARD_DARK_CITY_AT_MIDNIGHT_H
#define GUARD_DARK_CITY_AT_MIDNIGHT_H

#include "effect.h"

u8 DarkCity_IsLevel8OrHigherDestinyHero(u16 cardId);
u8 Cond_DarkCityOnSummon(struct EffectCtx *ctx);
enum DuelActionResult Op_DarkCityOnSummon(struct EffectCtx *ctx);
u8 Cond_DarkCityOnDestroy(struct EffectCtx *ctx);
enum DuelActionResult Op_DarkCityOnDestroy(struct EffectCtx *ctx);

#endif /* GUARD_DARK_CITY_AT_MIDNIGHT_H */
