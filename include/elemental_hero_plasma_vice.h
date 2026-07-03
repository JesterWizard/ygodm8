#ifndef ELEMENTAL_HERO_PLASMA_VICE_H
#define ELEMENTAL_HERO_PLASMA_VICE_H

#include "global.h"

#define DUEL_CURSOR_ELEMENTAL_HERO_PLASMA_VICE_TARGET 38

void ApplyElementalHeroPlasmaVicePiercingBattleEffect(void);

unsigned char CanActivateElementalHeroPlasmaVice(void);
void ActivateElementalHeroPlasmaViceEffect(void);
void TrySelectElementalHeroPlasmaViceTarget(void);
void CancelElementalHeroPlasmaViceTargeting(void);

#endif
