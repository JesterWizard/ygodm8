#ifndef GUARD_ELEMENTAL_HERO_FLASH_H
#define GUARD_ELEMENTAL_HERO_FLASH_H

#include "global.h"

extern u8 gElementalHeroFlashBattleDestroyPending;

void MarkElementalHeroFlashBattleDestruction(u16 cardId);
unsigned char ShouldActivateElementalHeroFlash(void);
void ActivateElementalHeroFlash(void);
void ClearElementalHeroFlashBattleDestroyPending(void);

#endif
