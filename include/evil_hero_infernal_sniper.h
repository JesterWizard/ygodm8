#ifndef GUARD_EVIL_HERO_INFERNAL_SNIPER_H
#define GUARD_EVIL_HERO_INFERNAL_SNIPER_H

#include "global.h"

u8 EvilHeroInfernalSniper_PreventsDestroy(const struct DuelCard *zone);
unsigned char ShouldActivateEvilHeroInfernalSniperTurnEffect(void);
void ActivateEvilHeroInfernalSniperTurnEffect(void);

#endif /* GUARD_EVIL_HERO_INFERNAL_SNIPER_H */
