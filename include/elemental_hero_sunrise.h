#ifndef ELEMENTAL_HERO_SUNRISE_H
#define ELEMENTAL_HERO_SUNRISE_H

#include "global.h"

extern u8 gElementalHeroSunriseSearchUsed;
extern u8 gElementalHeroSunriseDestroyUsed;
extern u8 gElementalHeroSunriseDestroyRow;
extern u8 gElementalHeroSunriseDestroyCol;

void ClearElementalHeroSunriseOptFlags(void);
void ClearElementalHeroSunriseDestroyPending(void);
void ApplyElementalHeroSunriseAtkBoost(const struct DuelCard *zone);
void ElementalHeroSunrise_OnZoneCleared(const struct DuelCard *zone);
void TryElementalHeroSunriseOnMonsterPlacement(struct DuelCard *zone);
void ElementalHeroSunrise_OnFusionSummoned(void);
void TryArmElementalHeroSunriseOnAttackDeclared(struct DuelCard *attacker,
                                                struct DuelCard *defender);
void ResolveElementalHeroSunriseDestroyEffect(void);

#endif // ELEMENTAL_HERO_SUNRISE_H
